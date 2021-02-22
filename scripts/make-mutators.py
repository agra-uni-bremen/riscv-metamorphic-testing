#!/usr/bin/env python3
import re
import sys

# Which opcodes to mutate.
opcodes = [
    "ADDI",
    "SLTI",
    "SLTIU",
    "XORI",
    "ORI",
    "ANDI",
    "ADD",
    "SUB",
    "SLL",
    "SLT",
    "SLTU",
    "SRL",
    "SRA",
    "XOR",
    "OR",
    "AND",
    "SLLI",
    "SRLI",
    "SRAI",
    "LUI",
    "AUIPC",
    "JAL",
    "JALR",
    "SB",
    "SH",
    "SW",
    "LB",
    "LH",
    "LW",
    "LBU",
    "LHU",
    "BEQ",
    "BNE",
    "BLT",
    "BGE",
    "BLTU",
    "BGEU",
]


def read_source(path: str):
    try:
        source_file = open(path, "r")
        source = source_file.read()
        return source
    except Exception as e:
        print(f"Could not open input file for mutation: {e}.")


def make_mutator(opcode, impl, itest):
    mutator_pattern = """struct {0}_{1} : OperationMutation<Opcode::{0}, {0}_{1}> {{
            {0}_{1}() : OperationMutation<Opcode::{0}, {0}_{1}>("{0}_{1}") {{}}
            void apply(ISS &core) {{
                {2}
            }}
        }};"""
    need_prefix = [
        "regs.shamt(",
        "shamt()",
        "read_reg(",
        "write_reg(",
        "mem->",
        "last_pc",
        "B_imm()",
        "J_imm()",
        "U_imm()",
        "I_imm()",
        "S_imm()",
        "trap_check_pc_alignment",
        "trap_check_addr_alignment",
        "maybe_mutate_load_addr",
        "maybe_mutate_load_value",
        "maybe_mutate_store_access(",
        "rs1()",
        "rs2()",
        "rd()",
        "pc =",
        " pc;",
        " pc ",
    ]
    for s in need_prefix:
        impl = impl.replace(s, f"core.{s}")

    mutator = mutator_pattern.format(opcode, itest, impl)
    return mutator


def replace_operators(impl):
    op_groups = [
        {" + ", " - "},
        {" ^ ", " & ", " | "},
        {" << ", " >> "},
        {" > ", " < ", " >= ", " <= ", " == ", " != "},
        {"B_imm()", "I_imm()", "J_imm()", "U_imm()", "S_imm()"},
        {"rs1()", "rs2()", "rd()"},
        {" pc", " last_pc"},
        {"load_ubyte", "load_byte", "load_half", "load_uhalf", "load_word"},
        {"store_byte", "store_half", "store_word"},
        {"(uint32_t)", "(int32_t)"},
    ]

    for g in op_groups:
        for op in g:
            loc = impl.find(op)
            if loc > -1:
                for no in g.difference({op}):
                    print(f"/* {op} -> {no} */")
                    yield impl.replace(op, no).strip()


def make_mutators(source_file):
    source = read_source(source_file)
    itest = 1
    mutators = []
    for opcode in opcodes:
        pattern = f"case Opcode::{opcode}:\n*(.*?)\n*break;"
        match = re.search(pattern, source, re.DOTALL)
        if match == None:
            raise (f"Malformed implementation for opcode {opcode}.")
        impl = match.group(1)

        for i in replace_operators(impl):
            mutator = make_mutator(opcode, i, itest)
            sm = "std::make_shared<{0}_{1}>()".format(opcode, itest)
            mutators.append(sm)
            itest += 1
            print(mutator)

    print("std::vector<std::shared_ptr<exec_mutator_if>> mutators{")
    print(",\n".join(mutators))
    print("};")


if __name__ == "__main__":
    make_mutators(sys.argv[1])