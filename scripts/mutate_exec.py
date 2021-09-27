#!/usr/bin/env python3
import fileinput
import sys
import re

raw_mode = False
if len(sys.argv) > 3:
    if sys.argv[3] == "raw":
        raw_mode = True  # dump the mutation only

mutation_class = None
if len(sys.argv) > 4:
    mutation_class = sys.argv[4]

choice = int(sys.argv[1])
pos = 0

state = "skip"
opcode = None
body = None


imm_kinds = ["instr.I_imm()", "instr.J_imm()", "instr.B_imm()",
             "instr.U_imm()", "instr.S_imm()"]

reg_kinds = ["instr.rs1()", "instr.rs2()", "instr.rd()", " 0 "]

arithmetic_ops = [" + ", " - ", " >> ", " << "]
logic_ops = [" ^ ", " | ", " & "]
computational_ops = arithmetic_ops + logic_ops
relational_ops = [" < ", " <= ", " == ", " != ", " > ", " >= "]

load_ops = ["load_ubyte", "load_byte", "load_half", "load_uhalf", "load_word"]
store_ops = ["store_byte", "store_half", "store_word"]

pc_ops = ["cur_pc", "last_pc"]
cast_ops = ["(uint32_t)", "(int32_t)"]
unary_ops = ["~CONSTANT", "!CONSTANT", "-CONSTANT", "NOP"]


mask_constants_1 = ["CONSTANT(0b1)", "CONSTANT(0b0)",
                    "CONSTANT(0b10)", "CONSTANT(0b11)"]

mask_constants_5 = ["CONSTANT(0b11111)", "CONSTANT(0b111110)", "CONSTANT(0b1111)", "CONSTANT(0b11110)",
                    "CONSTANT(0b01111)", "CONSTANT(0b10111)", "CONSTANT(0b11011)", "CONSTANT(0b11101)"]

shift_6_constants_1 = ["regs[instr.rs1()] << (regs[instr.rs2()] & CONSTANT(0b11111))",
                       "((int64_t)regs[instr.rs1()]) << (regs[instr.rs2()] & CONSTANT(0b111111))"]
shift_6_constants_2 = ["((uint32_t)regs[instr.rs1()]) >> (regs[instr.rs2()] & CONSTANT(0b11111))",
                       "((uint64_t)((uint32_t)regs[instr.rs1()])) >> (regs[instr.rs2()] & CONSTANT(0b111111))"]
shift_6_constants_3 = ["regs[instr.rs1()] >> (regs[instr.rs2()] & CONSTANT(0b11111))",
                       "((int64_t)regs[instr.rs1()]) >> (regs[instr.rs2()] & CONSTANT(0b111111))"]


# provide start and end!?
def gen_xlen_single_bit_masks(s, beg=0, end=32, is_signed=False):
    ans = [s]
    for i in range(beg, end):
        mask = "0b" + "1"*(31-i) + "0" + "1"*i
        x = "({} & {})".format(s, mask)
        ans.append(x)
    if is_signed and end < 32:
        x = "0b" + (32-end)*"1" + "0"*end   # keep negative part
        ans.append("({} & {})".format(s, x))
        x = "0b" + end*"1"   # keep positive part
        ans.append("({} & {})".format(s, x))
    return ans


i_imm_masks = gen_xlen_single_bit_masks("instr.I_imm()", 0, 12, True)
b_imm_masks = gen_xlen_single_bit_masks("instr.B_imm()", 1, 13, True)
s_imm_masks = gen_xlen_single_bit_masks("instr.S_imm()", 0, 12, True)
j_imm_masks = gen_xlen_single_bit_masks("instr.J_imm()", 1, 21, True)
u_imm_masks = gen_xlen_single_bit_masks("instr.U_imm()", 12, 32, False)
shamt_imm_masks = gen_xlen_single_bit_masks("instr.shamt()", 0, 5, False)

shamt_imm_6_masks_1 = ["regs[instr.rs1()] << instr.shamt()",
                       "((int64_t)regs[instr.rs1()]) << (instr.shamt() & 0b111111)"]
shamt_imm_6_masks_2 = ["((uint32_t)regs[instr.rs1()]) >> instr.shamt()",
                       "((uint64_t)((uint32_t)regs[instr.rs1()])) >> (instr.shamt() & 0b111111)"]
shamt_imm_6_masks_3 = ["regs[instr.rs1()] >> instr.shamt()",
                       "((int64_t)regs[instr.rs1()]) >> (instr.shamt() & 0b111111)"]

rs1_masks = gen_xlen_single_bit_masks("regs[instr.rs1()]")
rs2_masks = gen_xlen_single_bit_masks("regs[instr.rs2()]")

rd_masks = gen_xlen_single_bit_masks("regs[instr.rd()]")

mutators = [
    # > M6) replace immediate
    #    imm_kinds,

    # > M5) replace register
    #    reg_kinds,

    # > M8) replace binary ops
    #    computational_ops,
    #    relational_ops,

    # > M4) replace load / store
    #    load_ops,
    #    store_ops,

    # > M7) unary ops
    #    pc_ops,
    #    cast_ops,
    #    unary_ops,

    # > M3) replace constant
    #    mask_constants_1,
    #    mask_constants_5,

    # > M1) mask register
    #    rs1_masks,
    #    rs2_masks,

    # > M2) mask immediate
    #    i_imm_masks,
    #    b_imm_masks,
    #    s_imm_masks,
    #    j_imm_masks,
    #    u_imm_masks,
    #    shamt_imm_masks,
]

use_rd_mutators = False
use_trap_order_mutators = False  # > M9) move trap check


if mutation_class is not None:
    if mutation_class == "M1":
        mutators = [
            rs1_masks,
            rs2_masks,
        ]
    elif mutation_class == "M2":
        mutators = [
            i_imm_masks,
            b_imm_masks,
            s_imm_masks,
            j_imm_masks,
            u_imm_masks,
            shamt_imm_masks,
            shamt_imm_6_masks_1,
            shamt_imm_6_masks_2,
            shamt_imm_6_masks_3,
        ]
    elif mutation_class == "M3":
        mutators = [
            mask_constants_1,
            mask_constants_5,
            shift_6_constants_1,
            shift_6_constants_2,
            shift_6_constants_3,
        ]
    elif mutation_class == "M4":
        mutators = [
            load_ops,
            store_ops,
        ]
    elif mutation_class == "M5":
        mutators = [
            reg_kinds,
        ]
    elif mutation_class == "M6":
        mutators = [
            imm_kinds,
        ]
    elif mutation_class == "M7":
        mutators = [
            pc_ops,
            #            cast_ops,
            unary_ops,
        ]
    elif mutation_class == "M8":
        mutators = [
            computational_ops,
            relational_ops,
        ]
    elif mutation_class == "M9":
        use_trap_order_mutators = True
    else:
        raise RuntimeError(
            "unknown mutation class: '{}'".format(mutation_class))


def choose_mutation():
    global pos
    pos += 1
    return pos == choice


def completed():
    return pos >= choice


def is_branch(op):
    return opcode in ["BEQ", "BNE", "BLT", "BLTU", "BGE", "BGEU"]


def iterate_rd_mutators():
    if not use_rd_mutators:
        return
    if opcode in ["SLTIU", "SLTI", "SLTU", "SLT", "JAL", "JALR", "LUI", "AUIPC", "BEQ", "BNE", "BLT", "BLTU", "BGE", "BGEU"]:
        return
    for x in rd_masks[1:]:
        yield "// >>>>>  insert RD result mutation\nregs[instr.rd()] = " + x + ";\n"


def replace_occurrence(line, match, string):
    return line[:match.start()] + string + line[match.end():]


def is_enabled(line, match, string):
    #    if opcode not in ["SLL", "SRL", "SRA"]:
    #        return False

    if ("(regs[instr.rs1()] & 0b" in string) and (string.rfind("0") < 43) and (opcode in ["JALR", "SB", "SH", "SW", "LB", "LBU", "LH", "LHU", "LW"]):
        return False
    elif ("(regs[instr.rs2()] & 0b" in string):
        if (string.rfind("0") < 50) and (opcode in ["SLL", "SRL", "SRA"]):
            return False
        elif (string.rfind("0") < 39) and (opcode == "SH"):
            return False
        elif (string.rfind("0") < 47) and (opcode == "SB"):
            return False
    return True


def try_apply_mutation(choices, selection, line):
    for x in choices:
        if x != selection:
            # iterate through all occurences of selection and try to replace one of them with x
            for n, match in enumerate(re.finditer(re.escape(selection), line), 1):
                if is_enabled(line, match, x) and choose_mutation():
                    print("// >>>>> replace: occurrence {} of '{}' with '{}' in line '{}'".format(
                        n, selection, x, line.strip()))
                    return replace_occurrence(line, match, x)
    return line


def try_generate_mutation(body):
    ans = []
    done = False

    for line in body:
        for m in mutators:
            for s in m:
                if s in line:
                    res = try_apply_mutation(m, s, line)
                    if not done and line != res:
                        done = True
                    line = res
        ans.append(line)

    if done:
        return ans

    for x in iterate_rd_mutators():
        if choose_mutation():
            ans.append(x)
            done = True

    if done:
        return ans

    assert body == ans
    if use_trap_order_mutators:
        trap_check = None
        ans = []
        for line in body:
            if not is_branch(opcode) and "trap_check_" in line and choose_mutation():
                trap_check = line
            else:
                ans.append(line)
        if trap_check is not None:
            ans.append(trap_check)
            return ans

    return None


def print_body(body):
    for line in body:
        print(line, end="")


def parse_opcode(s):
    m = re.search("case Opcode::(.*):", s)
    assert m is not None
    return m.group(1)


def process_line(s):
    global state
    global body
    global opcode

    if state == "collect":
        if "break;" in s:
            mutation = try_generate_mutation(body)
            if mutation is not None:
                if raw_mode:
                    print_body(mutation)
                else:
                    print("if (mutation_begin()) {")
                    print_body(mutation)
                    print("} else {")
                    print_body(body)
                    print("}")
                    print("mutation_end();")
            else:
                print_body(body)
            print(s, end="")
            state = "scan"
        else:
            body.append(s)
        return

    if state == "scan":
        if "case Opcode::" in s:
            body = []
            opcode = parse_opcode(s)
            state = "collect"
        elif "END:MUTATE" in s:
            state = "skip"

    if state == "skip":
        if "BEGIN:MUTATE" in s:
            state = "scan"

    print(s, end="")


with open(sys.argv[2]) as f:
    for line in f:
        process_line(line)

# return non-zero exit code if no mutation has been inserted (i.e. mutation number has reached the end)
sys.exit(0 if completed() else 1)
