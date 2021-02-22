#include "mutations.h"

/*  +  ->  -  */
struct ADDI_1 : OperationMutation<Opcode::ADDI, ADDI_1> {
    ADDI_1() : OperationMutation<Opcode::ADDI, ADDI_1>("ADDI_1") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg(core.rs1()) - core.I_imm());
    }
};
/* I_imm() -> B_imm() */
struct ADDI_2 : OperationMutation<Opcode::ADDI, ADDI_2> {
    ADDI_2() : OperationMutation<Opcode::ADDI, ADDI_2>("ADDI_2") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg(core.rs1()) + core.B_imm());
    }
};
/* I_imm() -> U_imm() */
struct ADDI_3 : OperationMutation<Opcode::ADDI, ADDI_3> {
    ADDI_3() : OperationMutation<Opcode::ADDI, ADDI_3>("ADDI_3") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg(core.rs1()) + core.U_imm());
    }
};
/* I_imm() -> J_imm() */
struct ADDI_4 : OperationMutation<Opcode::ADDI, ADDI_4> {
    ADDI_4() : OperationMutation<Opcode::ADDI, ADDI_4>("ADDI_4") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg(core.rs1()) + core.J_imm());
    }
};
/* I_imm() -> S_imm() */
struct ADDI_5 : OperationMutation<Opcode::ADDI, ADDI_5> {
    ADDI_5() : OperationMutation<Opcode::ADDI, ADDI_5>("ADDI_5") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg(core.rs1()) + core.S_imm());
    }
};
/* rs1() -> rd() */
struct ADDI_6 : OperationMutation<Opcode::ADDI, ADDI_6> {
    ADDI_6() : OperationMutation<Opcode::ADDI, ADDI_6>("ADDI_6") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg(core.rd()) + core.I_imm());
    }
};
/* rs1() -> rs2() */
struct ADDI_7 : OperationMutation<Opcode::ADDI, ADDI_7> {
    ADDI_7() : OperationMutation<Opcode::ADDI, ADDI_7>("ADDI_7") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg(core.rs2()) + core.I_imm());
    }
};
/* rd() -> rs1() */
struct ADDI_8 : OperationMutation<Opcode::ADDI, ADDI_8> {
    ADDI_8() : OperationMutation<Opcode::ADDI, ADDI_8>("ADDI_8") {}
    void apply(ISS &core) {
        core.write_reg(core.rs1(), core.read_reg(core.rs1()) + core.I_imm());
    }
};
/* rd() -> rs2() */
struct ADDI_9 : OperationMutation<Opcode::ADDI, ADDI_9> {
    ADDI_9() : OperationMutation<Opcode::ADDI, ADDI_9>("ADDI_9") {}
    void apply(ISS &core) {
        core.write_reg(core.rs2(), core.read_reg(core.rs1()) + core.I_imm());
    }
};
/*  <  ->  ==  */
struct SLTI_10 : OperationMutation<Opcode::SLTI, SLTI_10> {
    SLTI_10() : OperationMutation<Opcode::SLTI, SLTI_10>("SLTI_10") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg(core.rs1()) == core.I_imm());
    }
};
/*  <  ->  >  */
struct SLTI_11 : OperationMutation<Opcode::SLTI, SLTI_11> {
    SLTI_11() : OperationMutation<Opcode::SLTI, SLTI_11>("SLTI_11") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg(core.rs1()) > core.I_imm());
    }
};
/*  <  ->  <=  */
struct SLTI_12 : OperationMutation<Opcode::SLTI, SLTI_12> {
    SLTI_12() : OperationMutation<Opcode::SLTI, SLTI_12>("SLTI_12") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg(core.rs1()) <= core.I_imm());
    }
};
/*  <  ->  !=  */
struct SLTI_13 : OperationMutation<Opcode::SLTI, SLTI_13> {
    SLTI_13() : OperationMutation<Opcode::SLTI, SLTI_13>("SLTI_13") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg(core.rs1()) != core.I_imm());
    }
};
/*  <  ->  >=  */
struct SLTI_14 : OperationMutation<Opcode::SLTI, SLTI_14> {
    SLTI_14() : OperationMutation<Opcode::SLTI, SLTI_14>("SLTI_14") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg(core.rs1()) >= core.I_imm());
    }
};
/* I_imm() -> B_imm() */
struct SLTI_15 : OperationMutation<Opcode::SLTI, SLTI_15> {
    SLTI_15() : OperationMutation<Opcode::SLTI, SLTI_15>("SLTI_15") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg(core.rs1()) < core.B_imm());
    }
};
/* I_imm() -> U_imm() */
struct SLTI_16 : OperationMutation<Opcode::SLTI, SLTI_16> {
    SLTI_16() : OperationMutation<Opcode::SLTI, SLTI_16>("SLTI_16") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg(core.rs1()) < core.U_imm());
    }
};
/* I_imm() -> J_imm() */
struct SLTI_17 : OperationMutation<Opcode::SLTI, SLTI_17> {
    SLTI_17() : OperationMutation<Opcode::SLTI, SLTI_17>("SLTI_17") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg(core.rs1()) < core.J_imm());
    }
};
/* I_imm() -> S_imm() */
struct SLTI_18 : OperationMutation<Opcode::SLTI, SLTI_18> {
    SLTI_18() : OperationMutation<Opcode::SLTI, SLTI_18>("SLTI_18") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg(core.rs1()) < core.S_imm());
    }
};
/* rs1() -> rd() */
struct SLTI_19 : OperationMutation<Opcode::SLTI, SLTI_19> {
    SLTI_19() : OperationMutation<Opcode::SLTI, SLTI_19>("SLTI_19") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg(core.rd()) < core.I_imm());
    }
};
/* rs1() -> rs2() */
struct SLTI_20 : OperationMutation<Opcode::SLTI, SLTI_20> {
    SLTI_20() : OperationMutation<Opcode::SLTI, SLTI_20>("SLTI_20") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg(core.rs2()) < core.I_imm());
    }
};
/* rd() -> rs1() */
struct SLTI_21 : OperationMutation<Opcode::SLTI, SLTI_21> {
    SLTI_21() : OperationMutation<Opcode::SLTI, SLTI_21>("SLTI_21") {}
    void apply(ISS &core) {
        core.write_reg(core.rs1(), core.read_reg(core.rs1()) < core.I_imm());
    }
};
/* rd() -> rs2() */
struct SLTI_22 : OperationMutation<Opcode::SLTI, SLTI_22> {
    SLTI_22() : OperationMutation<Opcode::SLTI, SLTI_22>("SLTI_22") {}
    void apply(ISS &core) {
        core.write_reg(core.rs2(), core.read_reg(core.rs1()) < core.I_imm());
    }
};
/*  <  ->  ==  */
struct SLTIU_23 : OperationMutation<Opcode::SLTIU, SLTIU_23> {
    SLTIU_23() : OperationMutation<Opcode::SLTIU, SLTIU_23>("SLTIU_23") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), ((uint32_t)core.read_reg(core.rs1())) == ((uint32_t)core.I_imm()));
    }
};
/*  <  ->  >  */
struct SLTIU_24 : OperationMutation<Opcode::SLTIU, SLTIU_24> {
    SLTIU_24() : OperationMutation<Opcode::SLTIU, SLTIU_24>("SLTIU_24") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), ((uint32_t)core.read_reg(core.rs1())) > ((uint32_t)core.I_imm()));
    }
};
/*  <  ->  <=  */
struct SLTIU_25 : OperationMutation<Opcode::SLTIU, SLTIU_25> {
    SLTIU_25() : OperationMutation<Opcode::SLTIU, SLTIU_25>("SLTIU_25") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), ((uint32_t)core.read_reg(core.rs1())) <= ((uint32_t)core.I_imm()));
    }
};
/*  <  ->  !=  */
struct SLTIU_26 : OperationMutation<Opcode::SLTIU, SLTIU_26> {
    SLTIU_26() : OperationMutation<Opcode::SLTIU, SLTIU_26>("SLTIU_26") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), ((uint32_t)core.read_reg(core.rs1())) != ((uint32_t)core.I_imm()));
    }
};
/*  <  ->  >=  */
struct SLTIU_27 : OperationMutation<Opcode::SLTIU, SLTIU_27> {
    SLTIU_27() : OperationMutation<Opcode::SLTIU, SLTIU_27>("SLTIU_27") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), ((uint32_t)core.read_reg(core.rs1())) >= ((uint32_t)core.I_imm()));
    }
};
/* I_imm() -> B_imm() */
struct SLTIU_28 : OperationMutation<Opcode::SLTIU, SLTIU_28> {
    SLTIU_28() : OperationMutation<Opcode::SLTIU, SLTIU_28>("SLTIU_28") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), ((uint32_t)core.read_reg(core.rs1())) < ((uint32_t)core.B_imm()));
    }
};
/* I_imm() -> U_imm() */
struct SLTIU_29 : OperationMutation<Opcode::SLTIU, SLTIU_29> {
    SLTIU_29() : OperationMutation<Opcode::SLTIU, SLTIU_29>("SLTIU_29") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), ((uint32_t)core.read_reg(core.rs1())) < ((uint32_t)core.U_imm()));
    }
};
/* I_imm() -> J_imm() */
struct SLTIU_30 : OperationMutation<Opcode::SLTIU, SLTIU_30> {
    SLTIU_30() : OperationMutation<Opcode::SLTIU, SLTIU_30>("SLTIU_30") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), ((uint32_t)core.read_reg(core.rs1())) < ((uint32_t)core.J_imm()));
    }
};
/* I_imm() -> S_imm() */
struct SLTIU_31 : OperationMutation<Opcode::SLTIU, SLTIU_31> {
    SLTIU_31() : OperationMutation<Opcode::SLTIU, SLTIU_31>("SLTIU_31") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), ((uint32_t)core.read_reg(core.rs1())) < ((uint32_t)core.S_imm()));
    }
};
/* rs1() -> rd() */
struct SLTIU_32 : OperationMutation<Opcode::SLTIU, SLTIU_32> {
    SLTIU_32() : OperationMutation<Opcode::SLTIU, SLTIU_32>("SLTIU_32") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), ((uint32_t)core.read_reg(core.rd())) < ((uint32_t)core.I_imm()));
    }
};
/* rs1() -> rs2() */
struct SLTIU_33 : OperationMutation<Opcode::SLTIU, SLTIU_33> {
    SLTIU_33() : OperationMutation<Opcode::SLTIU, SLTIU_33>("SLTIU_33") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), ((uint32_t)core.read_reg(core.rs2())) < ((uint32_t)core.I_imm()));
    }
};
/* rd() -> rs1() */
struct SLTIU_34 : OperationMutation<Opcode::SLTIU, SLTIU_34> {
    SLTIU_34() : OperationMutation<Opcode::SLTIU, SLTIU_34>("SLTIU_34") {}
    void apply(ISS &core) {
        core.write_reg(core.rs1(), ((uint32_t)core.read_reg(core.rs1())) < ((uint32_t)core.I_imm()));
    }
};
/* rd() -> rs2() */
struct SLTIU_35 : OperationMutation<Opcode::SLTIU, SLTIU_35> {
    SLTIU_35() : OperationMutation<Opcode::SLTIU, SLTIU_35>("SLTIU_35") {}
    void apply(ISS &core) {
        core.write_reg(core.rs2(), ((uint32_t)core.read_reg(core.rs1())) < ((uint32_t)core.I_imm()));
    }
};
/* (uint32_t) -> (int32_t) */
struct SLTIU_36 : OperationMutation<Opcode::SLTIU, SLTIU_36> {
    SLTIU_36() : OperationMutation<Opcode::SLTIU, SLTIU_36>("SLTIU_36") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), ((int32_t)core.read_reg(core.rs1())) < ((int32_t)core.I_imm()));
    }
};
/*  ^  ->  |  */
struct XORI_37 : OperationMutation<Opcode::XORI, XORI_37> {
    XORI_37() : OperationMutation<Opcode::XORI, XORI_37>("XORI_37") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg(core.rs1()) | core.I_imm());
    }
};
/*  ^  ->  &  */
struct XORI_38 : OperationMutation<Opcode::XORI, XORI_38> {
    XORI_38() : OperationMutation<Opcode::XORI, XORI_38>("XORI_38") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg(core.rs1()) & core.I_imm());
    }
};
/* I_imm() -> B_imm() */
struct XORI_39 : OperationMutation<Opcode::XORI, XORI_39> {
    XORI_39() : OperationMutation<Opcode::XORI, XORI_39>("XORI_39") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg(core.rs1()) ^ core.B_imm());
    }
};
/* I_imm() -> U_imm() */
struct XORI_40 : OperationMutation<Opcode::XORI, XORI_40> {
    XORI_40() : OperationMutation<Opcode::XORI, XORI_40>("XORI_40") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg(core.rs1()) ^ core.U_imm());
    }
};
/* I_imm() -> J_imm() */
struct XORI_41 : OperationMutation<Opcode::XORI, XORI_41> {
    XORI_41() : OperationMutation<Opcode::XORI, XORI_41>("XORI_41") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg(core.rs1()) ^ core.J_imm());
    }
};
/* I_imm() -> S_imm() */
struct XORI_42 : OperationMutation<Opcode::XORI, XORI_42> {
    XORI_42() : OperationMutation<Opcode::XORI, XORI_42>("XORI_42") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg(core.rs1()) ^ core.S_imm());
    }
};
/* rs1() -> rd() */
struct XORI_43 : OperationMutation<Opcode::XORI, XORI_43> {
    XORI_43() : OperationMutation<Opcode::XORI, XORI_43>("XORI_43") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg(core.rd()) ^ core.I_imm());
    }
};
/* rs1() -> rs2() */
struct XORI_44 : OperationMutation<Opcode::XORI, XORI_44> {
    XORI_44() : OperationMutation<Opcode::XORI, XORI_44>("XORI_44") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg(core.rs2()) ^ core.I_imm());
    }
};
/* rd() -> rs1() */
struct XORI_45 : OperationMutation<Opcode::XORI, XORI_45> {
    XORI_45() : OperationMutation<Opcode::XORI, XORI_45>("XORI_45") {}
    void apply(ISS &core) {
        core.write_reg(core.rs1(), core.read_reg(core.rs1()) ^ core.I_imm());
    }
};
/* rd() -> rs2() */
struct XORI_46 : OperationMutation<Opcode::XORI, XORI_46> {
    XORI_46() : OperationMutation<Opcode::XORI, XORI_46>("XORI_46") {}
    void apply(ISS &core) {
        core.write_reg(core.rs2(), core.read_reg(core.rs1()) ^ core.I_imm());
    }
};
/*  |  ->  ^  */
struct ORI_47 : OperationMutation<Opcode::ORI, ORI_47> {
    ORI_47() : OperationMutation<Opcode::ORI, ORI_47>("ORI_47") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg(core.rs1()) ^ core.I_imm());
    }
};
/*  |  ->  &  */
struct ORI_48 : OperationMutation<Opcode::ORI, ORI_48> {
    ORI_48() : OperationMutation<Opcode::ORI, ORI_48>("ORI_48") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg(core.rs1()) & core.I_imm());
    }
};
/* I_imm() -> B_imm() */
struct ORI_49 : OperationMutation<Opcode::ORI, ORI_49> {
    ORI_49() : OperationMutation<Opcode::ORI, ORI_49>("ORI_49") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg(core.rs1()) | core.B_imm());
    }
};
/* I_imm() -> U_imm() */
struct ORI_50 : OperationMutation<Opcode::ORI, ORI_50> {
    ORI_50() : OperationMutation<Opcode::ORI, ORI_50>("ORI_50") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg(core.rs1()) | core.U_imm());
    }
};
/* I_imm() -> J_imm() */
struct ORI_51 : OperationMutation<Opcode::ORI, ORI_51> {
    ORI_51() : OperationMutation<Opcode::ORI, ORI_51>("ORI_51") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg(core.rs1()) | core.J_imm());
    }
};
/* I_imm() -> S_imm() */
struct ORI_52 : OperationMutation<Opcode::ORI, ORI_52> {
    ORI_52() : OperationMutation<Opcode::ORI, ORI_52>("ORI_52") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg(core.rs1()) | core.S_imm());
    }
};
/* rs1() -> rd() */
struct ORI_53 : OperationMutation<Opcode::ORI, ORI_53> {
    ORI_53() : OperationMutation<Opcode::ORI, ORI_53>("ORI_53") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg(core.rd()) | core.I_imm());
    }
};
/* rs1() -> rs2() */
struct ORI_54 : OperationMutation<Opcode::ORI, ORI_54> {
    ORI_54() : OperationMutation<Opcode::ORI, ORI_54>("ORI_54") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg(core.rs2()) | core.I_imm());
    }
};
/* rd() -> rs1() */
struct ORI_55 : OperationMutation<Opcode::ORI, ORI_55> {
    ORI_55() : OperationMutation<Opcode::ORI, ORI_55>("ORI_55") {}
    void apply(ISS &core) {
        core.write_reg(core.rs1(), core.read_reg(core.rs1()) | core.I_imm());
    }
};
/* rd() -> rs2() */
struct ORI_56 : OperationMutation<Opcode::ORI, ORI_56> {
    ORI_56() : OperationMutation<Opcode::ORI, ORI_56>("ORI_56") {}
    void apply(ISS &core) {
        core.write_reg(core.rs2(), core.read_reg(core.rs1()) | core.I_imm());
    }
};
/*  &  ->  ^  */
struct ANDI_57 : OperationMutation<Opcode::ANDI, ANDI_57> {
    ANDI_57() : OperationMutation<Opcode::ANDI, ANDI_57>("ANDI_57") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg(core.rs1()) ^ core.I_imm());
    }
};
/*  &  ->  |  */
struct ANDI_58 : OperationMutation<Opcode::ANDI, ANDI_58> {
    ANDI_58() : OperationMutation<Opcode::ANDI, ANDI_58>("ANDI_58") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg(core.rs1()) | core.I_imm());
    }
};
/* I_imm() -> B_imm() */
struct ANDI_59 : OperationMutation<Opcode::ANDI, ANDI_59> {
    ANDI_59() : OperationMutation<Opcode::ANDI, ANDI_59>("ANDI_59") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg(core.rs1()) & core.B_imm());
    }
};
/* I_imm() -> U_imm() */
struct ANDI_60 : OperationMutation<Opcode::ANDI, ANDI_60> {
    ANDI_60() : OperationMutation<Opcode::ANDI, ANDI_60>("ANDI_60") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg(core.rs1()) & core.U_imm());
    }
};
/* I_imm() -> J_imm() */
struct ANDI_61 : OperationMutation<Opcode::ANDI, ANDI_61> {
    ANDI_61() : OperationMutation<Opcode::ANDI, ANDI_61>("ANDI_61") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg(core.rs1()) & core.J_imm());
    }
};
/* I_imm() -> S_imm() */
struct ANDI_62 : OperationMutation<Opcode::ANDI, ANDI_62> {
    ANDI_62() : OperationMutation<Opcode::ANDI, ANDI_62>("ANDI_62") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg(core.rs1()) & core.S_imm());
    }
};
/* rs1() -> rd() */
struct ANDI_63 : OperationMutation<Opcode::ANDI, ANDI_63> {
    ANDI_63() : OperationMutation<Opcode::ANDI, ANDI_63>("ANDI_63") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg(core.rd()) & core.I_imm());
    }
};
/* rs1() -> rs2() */
struct ANDI_64 : OperationMutation<Opcode::ANDI, ANDI_64> {
    ANDI_64() : OperationMutation<Opcode::ANDI, ANDI_64>("ANDI_64") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg(core.rs2()) & core.I_imm());
    }
};
/* rd() -> rs1() */
struct ANDI_65 : OperationMutation<Opcode::ANDI, ANDI_65> {
    ANDI_65() : OperationMutation<Opcode::ANDI, ANDI_65>("ANDI_65") {}
    void apply(ISS &core) {
        core.write_reg(core.rs1(), core.read_reg(core.rs1()) & core.I_imm());
    }
};
/* rd() -> rs2() */
struct ANDI_66 : OperationMutation<Opcode::ANDI, ANDI_66> {
    ANDI_66() : OperationMutation<Opcode::ANDI, ANDI_66>("ANDI_66") {}
    void apply(ISS &core) {
        core.write_reg(core.rs2(), core.read_reg(core.rs1()) & core.I_imm());
    }
};
/*  +  ->  -  */
struct ADD_67 : OperationMutation<Opcode::ADD, ADD_67> {
    ADD_67() : OperationMutation<Opcode::ADD, ADD_67>("ADD_67") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg(core.rs1()) - core.read_reg(core.rs2()));
    }
};
/* rs1() -> rd() */
struct ADD_68 : OperationMutation<Opcode::ADD, ADD_68> {
    ADD_68() : OperationMutation<Opcode::ADD, ADD_68>("ADD_68") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg(core.rd()) + core.read_reg(core.rs2()));
    }
};
/* rs1() -> rs2() */
struct ADD_69 : OperationMutation<Opcode::ADD, ADD_69> {
    ADD_69() : OperationMutation<Opcode::ADD, ADD_69>("ADD_69") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg(core.rs2()) + core.read_reg(core.rs2()));
    }
};
/* rd() -> rs1() */
struct ADD_70 : OperationMutation<Opcode::ADD, ADD_70> {
    ADD_70() : OperationMutation<Opcode::ADD, ADD_70>("ADD_70") {}
    void apply(ISS &core) {
        core.write_reg(core.rs1(), core.read_reg(core.rs1()) + core.read_reg(core.rs2()));
    }
};
/* rd() -> rs2() */
struct ADD_71 : OperationMutation<Opcode::ADD, ADD_71> {
    ADD_71() : OperationMutation<Opcode::ADD, ADD_71>("ADD_71") {}
    void apply(ISS &core) {
        core.write_reg(core.rs2(), core.read_reg(core.rs1()) + core.read_reg(core.rs2()));
    }
};
/* rs2() -> rs1() */
struct ADD_72 : OperationMutation<Opcode::ADD, ADD_72> {
    ADD_72() : OperationMutation<Opcode::ADD, ADD_72>("ADD_72") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg(core.rs1()) + core.read_reg(core.rs1()));
    }
};
/* rs2() -> rd() */
struct ADD_73 : OperationMutation<Opcode::ADD, ADD_73> {
    ADD_73() : OperationMutation<Opcode::ADD, ADD_73>("ADD_73") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg(core.rs1()) + core.read_reg(core.rd()));
    }
};
/*  -  ->  +  */
struct SUB_74 : OperationMutation<Opcode::SUB, SUB_74> {
    SUB_74() : OperationMutation<Opcode::SUB, SUB_74>("SUB_74") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg(core.rs1()) + core.read_reg(core.rs2()));
    }
};
/* rs1() -> rd() */
struct SUB_75 : OperationMutation<Opcode::SUB, SUB_75> {
    SUB_75() : OperationMutation<Opcode::SUB, SUB_75>("SUB_75") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg(core.rd()) - core.read_reg(core.rs2()));
    }
};
/* rs1() -> rs2() */
struct SUB_76 : OperationMutation<Opcode::SUB, SUB_76> {
    SUB_76() : OperationMutation<Opcode::SUB, SUB_76>("SUB_76") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg(core.rs2()) - core.read_reg(core.rs2()));
    }
};
/* rd() -> rs1() */
struct SUB_77 : OperationMutation<Opcode::SUB, SUB_77> {
    SUB_77() : OperationMutation<Opcode::SUB, SUB_77>("SUB_77") {}
    void apply(ISS &core) {
        core.write_reg(core.rs1(), core.read_reg(core.rs1()) - core.read_reg(core.rs2()));
    }
};
/* rd() -> rs2() */
struct SUB_78 : OperationMutation<Opcode::SUB, SUB_78> {
    SUB_78() : OperationMutation<Opcode::SUB, SUB_78>("SUB_78") {}
    void apply(ISS &core) {
        core.write_reg(core.rs2(), core.read_reg(core.rs1()) - core.read_reg(core.rs2()));
    }
};
/* rs2() -> rs1() */
struct SUB_79 : OperationMutation<Opcode::SUB, SUB_79> {
    SUB_79() : OperationMutation<Opcode::SUB, SUB_79>("SUB_79") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg(core.rs1()) - core.read_reg(core.rs1()));
    }
};
/* rs2() -> rd() */
struct SUB_80 : OperationMutation<Opcode::SUB, SUB_80> {
    SUB_80() : OperationMutation<Opcode::SUB, SUB_80>("SUB_80") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg(core.rs1()) - core.read_reg(core.rd()));
    }
};
/*  <<  ->  >>  */
struct SLL_81 : OperationMutation<Opcode::SLL, SLL_81> {
    SLL_81() : OperationMutation<Opcode::SLL, SLL_81>("SLL_81") {}
    void apply(ISS &core) {
        // TODO: Is it correct that this uses signed while SRL uses unsigned?
        core.write_reg(core.rd(), core.read_reg(core.rs1()) >> core.regs.shamt(core.rs2()));
    }
};
/* rs1() -> rd() */
struct SLL_82 : OperationMutation<Opcode::SLL, SLL_82> {
    SLL_82() : OperationMutation<Opcode::SLL, SLL_82>("SLL_82") {}
    void apply(ISS &core) {
        // TODO: Is it correct that this uses signed while SRL uses unsigned?
        core.write_reg(core.rd(), core.read_reg(core.rd()) << core.regs.shamt(core.rs2()));
    }
};
/* rs1() -> rs2() */
struct SLL_83 : OperationMutation<Opcode::SLL, SLL_83> {
    SLL_83() : OperationMutation<Opcode::SLL, SLL_83>("SLL_83") {}
    void apply(ISS &core) {
        // TODO: Is it correct that this uses signed while SRL uses unsigned?
        core.write_reg(core.rd(), core.read_reg(core.rs2()) << core.regs.shamt(core.rs2()));
    }
};
/* rd() -> rs1() */
struct SLL_84 : OperationMutation<Opcode::SLL, SLL_84> {
    SLL_84() : OperationMutation<Opcode::SLL, SLL_84>("SLL_84") {}
    void apply(ISS &core) {
        // TODO: Is it correct that this uses signed while SRL uses unsigned?
        core.write_reg(core.rs1(), core.read_reg(core.rs1()) << core.regs.shamt(core.rs2()));
    }
};
/* rd() -> rs2() */
struct SLL_85 : OperationMutation<Opcode::SLL, SLL_85> {
    SLL_85() : OperationMutation<Opcode::SLL, SLL_85>("SLL_85") {}
    void apply(ISS &core) {
        // TODO: Is it correct that this uses signed while SRL uses unsigned?
        core.write_reg(core.rs2(), core.read_reg(core.rs1()) << core.regs.shamt(core.rs2()));
    }
};
/* rs2() -> rs1() */
struct SLL_86 : OperationMutation<Opcode::SLL, SLL_86> {
    SLL_86() : OperationMutation<Opcode::SLL, SLL_86>("SLL_86") {}
    void apply(ISS &core) {
        // TODO: Is it correct that this uses signed while SRL uses unsigned?
        core.write_reg(core.rd(), core.read_reg(core.rs1()) << core.regs.shamt(core.rs1()));
    }
};
/* rs2() -> rd() */
struct SLL_87 : OperationMutation<Opcode::SLL, SLL_87> {
    SLL_87() : OperationMutation<Opcode::SLL, SLL_87>("SLL_87") {}
    void apply(ISS &core) {
        // TODO: Is it correct that this uses signed while SRL uses unsigned?
        core.write_reg(core.rd(), core.read_reg(core.rs1()) << core.regs.shamt(core.rd()));
    }
};
/*  <  ->  ==  */
struct SLT_88 : OperationMutation<Opcode::SLT, SLT_88> {
    SLT_88() : OperationMutation<Opcode::SLT, SLT_88>("SLT_88") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg(core.rs1()) == core.read_reg(core.rs2()));
    }
};
/*  <  ->  >  */
struct SLT_89 : OperationMutation<Opcode::SLT, SLT_89> {
    SLT_89() : OperationMutation<Opcode::SLT, SLT_89>("SLT_89") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg(core.rs1()) > core.read_reg(core.rs2()));
    }
};
/*  <  ->  <=  */
struct SLT_90 : OperationMutation<Opcode::SLT, SLT_90> {
    SLT_90() : OperationMutation<Opcode::SLT, SLT_90>("SLT_90") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg(core.rs1()) <= core.read_reg(core.rs2()));
    }
};
/*  <  ->  !=  */
struct SLT_91 : OperationMutation<Opcode::SLT, SLT_91> {
    SLT_91() : OperationMutation<Opcode::SLT, SLT_91>("SLT_91") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg(core.rs1()) != core.read_reg(core.rs2()));
    }
};
/*  <  ->  >=  */
struct SLT_92 : OperationMutation<Opcode::SLT, SLT_92> {
    SLT_92() : OperationMutation<Opcode::SLT, SLT_92>("SLT_92") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg(core.rs1()) >= core.read_reg(core.rs2()));
    }
};
/* rs1() -> rd() */
struct SLT_93 : OperationMutation<Opcode::SLT, SLT_93> {
    SLT_93() : OperationMutation<Opcode::SLT, SLT_93>("SLT_93") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg(core.rd()) < core.read_reg(core.rs2()));
    }
};
/* rs1() -> rs2() */
struct SLT_94 : OperationMutation<Opcode::SLT, SLT_94> {
    SLT_94() : OperationMutation<Opcode::SLT, SLT_94>("SLT_94") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg(core.rs2()) < core.read_reg(core.rs2()));
    }
};
/* rd() -> rs1() */
struct SLT_95 : OperationMutation<Opcode::SLT, SLT_95> {
    SLT_95() : OperationMutation<Opcode::SLT, SLT_95>("SLT_95") {}
    void apply(ISS &core) {
        core.write_reg(core.rs1(), core.read_reg(core.rs1()) < core.read_reg(core.rs2()));
    }
};
/* rd() -> rs2() */
struct SLT_96 : OperationMutation<Opcode::SLT, SLT_96> {
    SLT_96() : OperationMutation<Opcode::SLT, SLT_96>("SLT_96") {}
    void apply(ISS &core) {
        core.write_reg(core.rs2(), core.read_reg(core.rs1()) < core.read_reg(core.rs2()));
    }
};
/* rs2() -> rs1() */
struct SLT_97 : OperationMutation<Opcode::SLT, SLT_97> {
    SLT_97() : OperationMutation<Opcode::SLT, SLT_97>("SLT_97") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg(core.rs1()) < core.read_reg(core.rs1()));
    }
};
/* rs2() -> rd() */
struct SLT_98 : OperationMutation<Opcode::SLT, SLT_98> {
    SLT_98() : OperationMutation<Opcode::SLT, SLT_98>("SLT_98") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg(core.rs1()) < core.read_reg(core.rd()));
    }
};
/*  <  ->  ==  */
struct SLTU_99 : OperationMutation<Opcode::SLTU, SLTU_99> {
    SLTU_99() : OperationMutation<Opcode::SLTU, SLTU_99>("SLTU_99") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), ((uint32_t)core.read_reg(core.rs1())) == ((uint32_t)core.read_reg(core.rs2())));
    }
};
/*  <  ->  >  */
struct SLTU_100 : OperationMutation<Opcode::SLTU, SLTU_100> {
    SLTU_100() : OperationMutation<Opcode::SLTU, SLTU_100>("SLTU_100") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), ((uint32_t)core.read_reg(core.rs1())) > ((uint32_t)core.read_reg(core.rs2())));
    }
};
/*  <  ->  <=  */
struct SLTU_101 : OperationMutation<Opcode::SLTU, SLTU_101> {
    SLTU_101() : OperationMutation<Opcode::SLTU, SLTU_101>("SLTU_101") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), ((uint32_t)core.read_reg(core.rs1())) <= ((uint32_t)core.read_reg(core.rs2())));
    }
};
/*  <  ->  !=  */
struct SLTU_102 : OperationMutation<Opcode::SLTU, SLTU_102> {
    SLTU_102() : OperationMutation<Opcode::SLTU, SLTU_102>("SLTU_102") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), ((uint32_t)core.read_reg(core.rs1())) != ((uint32_t)core.read_reg(core.rs2())));
    }
};
/*  <  ->  >=  */
struct SLTU_103 : OperationMutation<Opcode::SLTU, SLTU_103> {
    SLTU_103() : OperationMutation<Opcode::SLTU, SLTU_103>("SLTU_103") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), ((uint32_t)core.read_reg(core.rs1())) >= ((uint32_t)core.read_reg(core.rs2())));
    }
};
/* rs1() -> rd() */
struct SLTU_104 : OperationMutation<Opcode::SLTU, SLTU_104> {
    SLTU_104() : OperationMutation<Opcode::SLTU, SLTU_104>("SLTU_104") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), ((uint32_t)core.read_reg(core.rd())) < ((uint32_t)core.read_reg(core.rs2())));
    }
};
/* rs1() -> rs2() */
struct SLTU_105 : OperationMutation<Opcode::SLTU, SLTU_105> {
    SLTU_105() : OperationMutation<Opcode::SLTU, SLTU_105>("SLTU_105") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), ((uint32_t)core.read_reg(core.rs2())) < ((uint32_t)core.read_reg(core.rs2())));
    }
};
/* rd() -> rs1() */
struct SLTU_106 : OperationMutation<Opcode::SLTU, SLTU_106> {
    SLTU_106() : OperationMutation<Opcode::SLTU, SLTU_106>("SLTU_106") {}
    void apply(ISS &core) {
        core.write_reg(core.rs1(), ((uint32_t)core.read_reg(core.rs1())) < ((uint32_t)core.read_reg(core.rs2())));
    }
};
/* rd() -> rs2() */
struct SLTU_107 : OperationMutation<Opcode::SLTU, SLTU_107> {
    SLTU_107() : OperationMutation<Opcode::SLTU, SLTU_107>("SLTU_107") {}
    void apply(ISS &core) {
        core.write_reg(core.rs2(), ((uint32_t)core.read_reg(core.rs1())) < ((uint32_t)core.read_reg(core.rs2())));
    }
};
/* rs2() -> rs1() */
struct SLTU_108 : OperationMutation<Opcode::SLTU, SLTU_108> {
    SLTU_108() : OperationMutation<Opcode::SLTU, SLTU_108>("SLTU_108") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), ((uint32_t)core.read_reg(core.rs1())) < ((uint32_t)core.read_reg(core.rs1())));
    }
};
/* rs2() -> rd() */
struct SLTU_109 : OperationMutation<Opcode::SLTU, SLTU_109> {
    SLTU_109() : OperationMutation<Opcode::SLTU, SLTU_109>("SLTU_109") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), ((uint32_t)core.read_reg(core.rs1())) < ((uint32_t)core.read_reg(core.rd())));
    }
};
/* (uint32_t) -> (int32_t) */
struct SLTU_110 : OperationMutation<Opcode::SLTU, SLTU_110> {
    SLTU_110() : OperationMutation<Opcode::SLTU, SLTU_110>("SLTU_110") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), ((int32_t)core.read_reg(core.rs1())) < ((int32_t)core.read_reg(core.rs2())));
    }
};
/*  >>  ->  <<  */
struct SRL_111 : OperationMutation<Opcode::SRL, SRL_111> {
    SRL_111() : OperationMutation<Opcode::SRL, SRL_111>("SRL_111") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), ((uint32_t)core.read_reg(core.rs1())) << core.regs.shamt(core.rs2()));
    }
};
/* rs1() -> rd() */
struct SRL_112 : OperationMutation<Opcode::SRL, SRL_112> {
    SRL_112() : OperationMutation<Opcode::SRL, SRL_112>("SRL_112") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), ((uint32_t)core.read_reg(core.rd())) >> core.regs.shamt(core.rs2()));
    }
};
/* rs1() -> rs2() */
struct SRL_113 : OperationMutation<Opcode::SRL, SRL_113> {
    SRL_113() : OperationMutation<Opcode::SRL, SRL_113>("SRL_113") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), ((uint32_t)core.read_reg(core.rs2())) >> core.regs.shamt(core.rs2()));
    }
};
/* rd() -> rs1() */
struct SRL_114 : OperationMutation<Opcode::SRL, SRL_114> {
    SRL_114() : OperationMutation<Opcode::SRL, SRL_114>("SRL_114") {}
    void apply(ISS &core) {
        core.write_reg(core.rs1(), ((uint32_t)core.read_reg(core.rs1())) >> core.regs.shamt(core.rs2()));
    }
};
/* rd() -> rs2() */
struct SRL_115 : OperationMutation<Opcode::SRL, SRL_115> {
    SRL_115() : OperationMutation<Opcode::SRL, SRL_115>("SRL_115") {}
    void apply(ISS &core) {
        core.write_reg(core.rs2(), ((uint32_t)core.read_reg(core.rs1())) >> core.regs.shamt(core.rs2()));
    }
};
/* rs2() -> rs1() */
struct SRL_116 : OperationMutation<Opcode::SRL, SRL_116> {
    SRL_116() : OperationMutation<Opcode::SRL, SRL_116>("SRL_116") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), ((uint32_t)core.read_reg(core.rs1())) >> core.regs.shamt(core.rs1()));
    }
};
/* rs2() -> rd() */
struct SRL_117 : OperationMutation<Opcode::SRL, SRL_117> {
    SRL_117() : OperationMutation<Opcode::SRL, SRL_117>("SRL_117") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), ((uint32_t)core.read_reg(core.rs1())) >> core.regs.shamt(core.rd()));
    }
};
/* (uint32_t) -> (int32_t) */
struct SRL_118 : OperationMutation<Opcode::SRL, SRL_118> {
    SRL_118() : OperationMutation<Opcode::SRL, SRL_118>("SRL_118") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), ((int32_t)core.read_reg(core.rs1())) >> core.regs.shamt(core.rs2()));
    }
};
/*  >>  ->  <<  */
struct SRA_119 : OperationMutation<Opcode::SRA, SRA_119> {
    SRA_119() : OperationMutation<Opcode::SRA, SRA_119>("SRA_119") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg(core.rs1()) << core.regs.shamt(core.rs2()));
    }
};
/* rs1() -> rd() */
struct SRA_120 : OperationMutation<Opcode::SRA, SRA_120> {
    SRA_120() : OperationMutation<Opcode::SRA, SRA_120>("SRA_120") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg(core.rd()) >> core.regs.shamt(core.rs2()));
    }
};
/* rs1() -> rs2() */
struct SRA_121 : OperationMutation<Opcode::SRA, SRA_121> {
    SRA_121() : OperationMutation<Opcode::SRA, SRA_121>("SRA_121") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg(core.rs2()) >> core.regs.shamt(core.rs2()));
    }
};
/* rd() -> rs1() */
struct SRA_122 : OperationMutation<Opcode::SRA, SRA_122> {
    SRA_122() : OperationMutation<Opcode::SRA, SRA_122>("SRA_122") {}
    void apply(ISS &core) {
        core.write_reg(core.rs1(), core.read_reg(core.rs1()) >> core.regs.shamt(core.rs2()));
    }
};
/* rd() -> rs2() */
struct SRA_123 : OperationMutation<Opcode::SRA, SRA_123> {
    SRA_123() : OperationMutation<Opcode::SRA, SRA_123>("SRA_123") {}
    void apply(ISS &core) {
        core.write_reg(core.rs2(), core.read_reg(core.rs1()) >> core.regs.shamt(core.rs2()));
    }
};
/* rs2() -> rs1() */
struct SRA_124 : OperationMutation<Opcode::SRA, SRA_124> {
    SRA_124() : OperationMutation<Opcode::SRA, SRA_124>("SRA_124") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg(core.rs1()) >> core.regs.shamt(core.rs1()));
    }
};
/* rs2() -> rd() */
struct SRA_125 : OperationMutation<Opcode::SRA, SRA_125> {
    SRA_125() : OperationMutation<Opcode::SRA, SRA_125>("SRA_125") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg(core.rs1()) >> core.regs.shamt(core.rd()));
    }
};
/*  ^  ->  |  */
struct XOR_126 : OperationMutation<Opcode::XOR, XOR_126> {
    XOR_126() : OperationMutation<Opcode::XOR, XOR_126>("XOR_126") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg(core.rs1()) | core.read_reg(core.rs2()));
    }
};
/*  ^  ->  &  */
struct XOR_127 : OperationMutation<Opcode::XOR, XOR_127> {
    XOR_127() : OperationMutation<Opcode::XOR, XOR_127>("XOR_127") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg(core.rs1()) & core.read_reg(core.rs2()));
    }
};
/* rs1() -> rd() */
struct XOR_128 : OperationMutation<Opcode::XOR, XOR_128> {
    XOR_128() : OperationMutation<Opcode::XOR, XOR_128>("XOR_128") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg(core.rd()) ^ core.read_reg(core.rs2()));
    }
};
/* rs1() -> rs2() */
struct XOR_129 : OperationMutation<Opcode::XOR, XOR_129> {
    XOR_129() : OperationMutation<Opcode::XOR, XOR_129>("XOR_129") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg(core.rs2()) ^ core.read_reg(core.rs2()));
    }
};
/* rd() -> rs1() */
struct XOR_130 : OperationMutation<Opcode::XOR, XOR_130> {
    XOR_130() : OperationMutation<Opcode::XOR, XOR_130>("XOR_130") {}
    void apply(ISS &core) {
        core.write_reg(core.rs1(), core.read_reg(core.rs1()) ^ core.read_reg(core.rs2()));
    }
};
/* rd() -> rs2() */
struct XOR_131 : OperationMutation<Opcode::XOR, XOR_131> {
    XOR_131() : OperationMutation<Opcode::XOR, XOR_131>("XOR_131") {}
    void apply(ISS &core) {
        core.write_reg(core.rs2(), core.read_reg(core.rs1()) ^ core.read_reg(core.rs2()));
    }
};
/* rs2() -> rs1() */
struct XOR_132 : OperationMutation<Opcode::XOR, XOR_132> {
    XOR_132() : OperationMutation<Opcode::XOR, XOR_132>("XOR_132") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg(core.rs1()) ^ core.read_reg(core.rs1()));
    }
};
/* rs2() -> rd() */
struct XOR_133 : OperationMutation<Opcode::XOR, XOR_133> {
    XOR_133() : OperationMutation<Opcode::XOR, XOR_133>("XOR_133") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg(core.rs1()) ^ core.read_reg(core.rd()));
    }
};
/*  |  ->  ^  */
struct OR_134 : OperationMutation<Opcode::OR, OR_134> {
    OR_134() : OperationMutation<Opcode::OR, OR_134>("OR_134") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg(core.rs1()) ^ core.read_reg(core.rs2()));
    }
};
/*  |  ->  &  */
struct OR_135 : OperationMutation<Opcode::OR, OR_135> {
    OR_135() : OperationMutation<Opcode::OR, OR_135>("OR_135") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg(core.rs1()) & core.read_reg(core.rs2()));
    }
};
/* rs1() -> rd() */
struct OR_136 : OperationMutation<Opcode::OR, OR_136> {
    OR_136() : OperationMutation<Opcode::OR, OR_136>("OR_136") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg(core.rd()) | core.read_reg(core.rs2()));
    }
};
/* rs1() -> rs2() */
struct OR_137 : OperationMutation<Opcode::OR, OR_137> {
    OR_137() : OperationMutation<Opcode::OR, OR_137>("OR_137") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg(core.rs2()) | core.read_reg(core.rs2()));
    }
};
/* rd() -> rs1() */
struct OR_138 : OperationMutation<Opcode::OR, OR_138> {
    OR_138() : OperationMutation<Opcode::OR, OR_138>("OR_138") {}
    void apply(ISS &core) {
        core.write_reg(core.rs1(), core.read_reg(core.rs1()) | core.read_reg(core.rs2()));
    }
};
/* rd() -> rs2() */
struct OR_139 : OperationMutation<Opcode::OR, OR_139> {
    OR_139() : OperationMutation<Opcode::OR, OR_139>("OR_139") {}
    void apply(ISS &core) {
        core.write_reg(core.rs2(), core.read_reg(core.rs1()) | core.read_reg(core.rs2()));
    }
};
/* rs2() -> rs1() */
struct OR_140 : OperationMutation<Opcode::OR, OR_140> {
    OR_140() : OperationMutation<Opcode::OR, OR_140>("OR_140") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg(core.rs1()) | core.read_reg(core.rs1()));
    }
};
/* rs2() -> rd() */
struct OR_141 : OperationMutation<Opcode::OR, OR_141> {
    OR_141() : OperationMutation<Opcode::OR, OR_141>("OR_141") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg(core.rs1()) | core.read_reg(core.rd()));
    }
};
/*  &  ->  ^  */
struct AND_142 : OperationMutation<Opcode::AND, AND_142> {
    AND_142() : OperationMutation<Opcode::AND, AND_142>("AND_142") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg(core.rs1()) ^ core.read_reg(core.rs2()));
    }
};
/*  &  ->  |  */
struct AND_143 : OperationMutation<Opcode::AND, AND_143> {
    AND_143() : OperationMutation<Opcode::AND, AND_143>("AND_143") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg(core.rs1()) | core.read_reg(core.rs2()));
    }
};
/* rs1() -> rd() */
struct AND_144 : OperationMutation<Opcode::AND, AND_144> {
    AND_144() : OperationMutation<Opcode::AND, AND_144>("AND_144") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg(core.rd()) & core.read_reg(core.rs2()));
    }
};
/* rs1() -> rs2() */
struct AND_145 : OperationMutation<Opcode::AND, AND_145> {
    AND_145() : OperationMutation<Opcode::AND, AND_145>("AND_145") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg(core.rs2()) & core.read_reg(core.rs2()));
    }
};
/* rd() -> rs1() */
struct AND_146 : OperationMutation<Opcode::AND, AND_146> {
    AND_146() : OperationMutation<Opcode::AND, AND_146>("AND_146") {}
    void apply(ISS &core) {
        core.write_reg(core.rs1(), core.read_reg(core.rs1()) & core.read_reg(core.rs2()));
    }
};
/* rd() -> rs2() */
struct AND_147 : OperationMutation<Opcode::AND, AND_147> {
    AND_147() : OperationMutation<Opcode::AND, AND_147>("AND_147") {}
    void apply(ISS &core) {
        core.write_reg(core.rs2(), core.read_reg(core.rs1()) & core.read_reg(core.rs2()));
    }
};
/* rs2() -> rs1() */
struct AND_148 : OperationMutation<Opcode::AND, AND_148> {
    AND_148() : OperationMutation<Opcode::AND, AND_148>("AND_148") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg(core.rs1()) & core.read_reg(core.rs1()));
    }
};
/* rs2() -> rd() */
struct AND_149 : OperationMutation<Opcode::AND, AND_149> {
    AND_149() : OperationMutation<Opcode::AND, AND_149>("AND_149") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg(core.rs1()) & core.read_reg(core.rd()));
    }
};
/*  <<  ->  >>  */
struct SLLI_150 : OperationMutation<Opcode::SLLI, SLLI_150> {
    SLLI_150() : OperationMutation<Opcode::SLLI, SLLI_150>("SLLI_150") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg(core.rs1()) >> core.shamt());
    }
};
/* rs1() -> rd() */
struct SLLI_151 : OperationMutation<Opcode::SLLI, SLLI_151> {
    SLLI_151() : OperationMutation<Opcode::SLLI, SLLI_151>("SLLI_151") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg(core.rd()) << core.shamt());
    }
};
/* rs1() -> rs2() */
struct SLLI_152 : OperationMutation<Opcode::SLLI, SLLI_152> {
    SLLI_152() : OperationMutation<Opcode::SLLI, SLLI_152>("SLLI_152") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg(core.rs2()) << core.shamt());
    }
};
/* rd() -> rs1() */
struct SLLI_153 : OperationMutation<Opcode::SLLI, SLLI_153> {
    SLLI_153() : OperationMutation<Opcode::SLLI, SLLI_153>("SLLI_153") {}
    void apply(ISS &core) {
        core.write_reg(core.rs1(), core.read_reg(core.rs1()) << core.shamt());
    }
};
/* rd() -> rs2() */
struct SLLI_154 : OperationMutation<Opcode::SLLI, SLLI_154> {
    SLLI_154() : OperationMutation<Opcode::SLLI, SLLI_154>("SLLI_154") {}
    void apply(ISS &core) {
        core.write_reg(core.rs2(), core.read_reg(core.rs1()) << core.shamt());
    }
};
/*  >>  ->  <<  */
struct SRLI_155 : OperationMutation<Opcode::SRLI, SRLI_155> {
    SRLI_155() : OperationMutation<Opcode::SRLI, SRLI_155>("SRLI_155") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), ((uint32_t)core.read_reg(core.rs1())) << core.shamt());
    }
};
/* rs1() -> rd() */
struct SRLI_156 : OperationMutation<Opcode::SRLI, SRLI_156> {
    SRLI_156() : OperationMutation<Opcode::SRLI, SRLI_156>("SRLI_156") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), ((uint32_t)core.read_reg(core.rd())) >> core.shamt());
    }
};
/* rs1() -> rs2() */
struct SRLI_157 : OperationMutation<Opcode::SRLI, SRLI_157> {
    SRLI_157() : OperationMutation<Opcode::SRLI, SRLI_157>("SRLI_157") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), ((uint32_t)core.read_reg(core.rs2())) >> core.shamt());
    }
};
/* rd() -> rs1() */
struct SRLI_158 : OperationMutation<Opcode::SRLI, SRLI_158> {
    SRLI_158() : OperationMutation<Opcode::SRLI, SRLI_158>("SRLI_158") {}
    void apply(ISS &core) {
        core.write_reg(core.rs1(), ((uint32_t)core.read_reg(core.rs1())) >> core.shamt());
    }
};
/* rd() -> rs2() */
struct SRLI_159 : OperationMutation<Opcode::SRLI, SRLI_159> {
    SRLI_159() : OperationMutation<Opcode::SRLI, SRLI_159>("SRLI_159") {}
    void apply(ISS &core) {
        core.write_reg(core.rs2(), ((uint32_t)core.read_reg(core.rs1())) >> core.shamt());
    }
};
/* (uint32_t) -> (int32_t) */
struct SRLI_160 : OperationMutation<Opcode::SRLI, SRLI_160> {
    SRLI_160() : OperationMutation<Opcode::SRLI, SRLI_160>("SRLI_160") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), ((int32_t)core.read_reg(core.rs1())) >> core.shamt());
    }
};
/*  >>  ->  <<  */
struct SRAI_161 : OperationMutation<Opcode::SRAI, SRAI_161> {
    SRAI_161() : OperationMutation<Opcode::SRAI, SRAI_161>("SRAI_161") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg(core.rs1()) << core.shamt());
    }
};
/* rs1() -> rd() */
struct SRAI_162 : OperationMutation<Opcode::SRAI, SRAI_162> {
    SRAI_162() : OperationMutation<Opcode::SRAI, SRAI_162>("SRAI_162") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg(core.rd()) >> core.shamt());
    }
};
/* rs1() -> rs2() */
struct SRAI_163 : OperationMutation<Opcode::SRAI, SRAI_163> {
    SRAI_163() : OperationMutation<Opcode::SRAI, SRAI_163>("SRAI_163") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg(core.rs2()) >> core.shamt());
    }
};
/* rd() -> rs1() */
struct SRAI_164 : OperationMutation<Opcode::SRAI, SRAI_164> {
    SRAI_164() : OperationMutation<Opcode::SRAI, SRAI_164>("SRAI_164") {}
    void apply(ISS &core) {
        core.write_reg(core.rs1(), core.read_reg(core.rs1()) >> core.shamt());
    }
};
/* rd() -> rs2() */
struct SRAI_165 : OperationMutation<Opcode::SRAI, SRAI_165> {
    SRAI_165() : OperationMutation<Opcode::SRAI, SRAI_165>("SRAI_165") {}
    void apply(ISS &core) {
        core.write_reg(core.rs2(), core.read_reg(core.rs1()) >> core.shamt());
    }
};
/* U_imm() -> B_imm() */
struct LUI_166 : OperationMutation<Opcode::LUI, LUI_166> {
    LUI_166() : OperationMutation<Opcode::LUI, LUI_166>("LUI_166") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.B_imm());
    }
};
/* U_imm() -> I_imm() */
struct LUI_167 : OperationMutation<Opcode::LUI, LUI_167> {
    LUI_167() : OperationMutation<Opcode::LUI, LUI_167>("LUI_167") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.I_imm());
    }
};
/* U_imm() -> J_imm() */
struct LUI_168 : OperationMutation<Opcode::LUI, LUI_168> {
    LUI_168() : OperationMutation<Opcode::LUI, LUI_168>("LUI_168") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.J_imm());
    }
};
/* U_imm() -> S_imm() */
struct LUI_169 : OperationMutation<Opcode::LUI, LUI_169> {
    LUI_169() : OperationMutation<Opcode::LUI, LUI_169>("LUI_169") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.S_imm());
    }
};
/* rd() -> rs1() */
struct LUI_170 : OperationMutation<Opcode::LUI, LUI_170> {
    LUI_170() : OperationMutation<Opcode::LUI, LUI_170>("LUI_170") {}
    void apply(ISS &core) {
        core.write_reg(core.rs1(), core.U_imm());
    }
};
/* rd() -> rs2() */
struct LUI_171 : OperationMutation<Opcode::LUI, LUI_171> {
    LUI_171() : OperationMutation<Opcode::LUI, LUI_171>("LUI_171") {}
    void apply(ISS &core) {
        core.write_reg(core.rs2(), core.U_imm());
    }
};
/*  +  ->  -  */
struct AUIPC_172 : OperationMutation<Opcode::AUIPC, AUIPC_172> {
    AUIPC_172() : OperationMutation<Opcode::AUIPC, AUIPC_172>("AUIPC_172") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.last_pc - core.U_imm());
    }
};
/* U_imm() -> B_imm() */
struct AUIPC_173 : OperationMutation<Opcode::AUIPC, AUIPC_173> {
    AUIPC_173() : OperationMutation<Opcode::AUIPC, AUIPC_173>("AUIPC_173") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.last_pc + core.B_imm());
    }
};
/* U_imm() -> I_imm() */
struct AUIPC_174 : OperationMutation<Opcode::AUIPC, AUIPC_174> {
    AUIPC_174() : OperationMutation<Opcode::AUIPC, AUIPC_174>("AUIPC_174") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.last_pc + core.I_imm());
    }
};
/* U_imm() -> J_imm() */
struct AUIPC_175 : OperationMutation<Opcode::AUIPC, AUIPC_175> {
    AUIPC_175() : OperationMutation<Opcode::AUIPC, AUIPC_175>("AUIPC_175") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.last_pc + core.J_imm());
    }
};
/* U_imm() -> S_imm() */
struct AUIPC_176 : OperationMutation<Opcode::AUIPC, AUIPC_176> {
    AUIPC_176() : OperationMutation<Opcode::AUIPC, AUIPC_176>("AUIPC_176") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.last_pc + core.S_imm());
    }
};
/* rd() -> rs1() */
struct AUIPC_177 : OperationMutation<Opcode::AUIPC, AUIPC_177> {
    AUIPC_177() : OperationMutation<Opcode::AUIPC, AUIPC_177>("AUIPC_177") {}
    void apply(ISS &core) {
        core.write_reg(core.rs1(), core.last_pc + core.U_imm());
    }
};
/* rd() -> rs2() */
struct AUIPC_178 : OperationMutation<Opcode::AUIPC, AUIPC_178> {
    AUIPC_178() : OperationMutation<Opcode::AUIPC, AUIPC_178>("AUIPC_178") {}
    void apply(ISS &core) {
        core.write_reg(core.rs2(), core.last_pc + core.U_imm());
    }
};
/*  last_pc ->  pc */
struct AUIPC_179 : OperationMutation<Opcode::AUIPC, AUIPC_179> {
    AUIPC_179() : OperationMutation<Opcode::AUIPC, AUIPC_179>("AUIPC_179") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.pc + core.U_imm());
    }
};
/*  +  ->  -  */
struct JAL_180 : OperationMutation<Opcode::JAL, JAL_180> {
    JAL_180() : OperationMutation<Opcode::JAL, JAL_180>("JAL_180") {}
    void apply(ISS &core) {
        {
            auto link = core.pc;
            core.pc = core.last_pc - core.J_imm();
            core.trap_check_pc_alignment();
            core.write_reg(core.rd(), link);
        }
    }
};
/* J_imm() -> B_imm() */
struct JAL_181 : OperationMutation<Opcode::JAL, JAL_181> {
    JAL_181() : OperationMutation<Opcode::JAL, JAL_181>("JAL_181") {}
    void apply(ISS &core) {
        {
            auto link = core.pc;
            core.pc = core.last_pc + core.B_imm();
            core.trap_check_pc_alignment();
            core.write_reg(core.rd(), link);
        }
    }
};
/* J_imm() -> U_imm() */
struct JAL_182 : OperationMutation<Opcode::JAL, JAL_182> {
    JAL_182() : OperationMutation<Opcode::JAL, JAL_182>("JAL_182") {}
    void apply(ISS &core) {
        {
            auto link = core.pc;
            core.pc = core.last_pc + core.U_imm();
            core.trap_check_pc_alignment();
            core.write_reg(core.rd(), link);
        }
    }
};
/* J_imm() -> I_imm() */
struct JAL_183 : OperationMutation<Opcode::JAL, JAL_183> {
    JAL_183() : OperationMutation<Opcode::JAL, JAL_183>("JAL_183") {}
    void apply(ISS &core) {
        {
            auto link = core.pc;
            core.pc = core.last_pc + core.I_imm();
            core.trap_check_pc_alignment();
            core.write_reg(core.rd(), link);
        }
    }
};
/* J_imm() -> S_imm() */
struct JAL_184 : OperationMutation<Opcode::JAL, JAL_184> {
    JAL_184() : OperationMutation<Opcode::JAL, JAL_184>("JAL_184") {}
    void apply(ISS &core) {
        {
            auto link = core.pc;
            core.pc = core.last_pc + core.S_imm();
            core.trap_check_pc_alignment();
            core.write_reg(core.rd(), link);
        }
    }
};
/* rd() -> rs1() */
struct JAL_185 : OperationMutation<Opcode::JAL, JAL_185> {
    JAL_185() : OperationMutation<Opcode::JAL, JAL_185>("JAL_185") {}
    void apply(ISS &core) {
        {
            auto link = core.pc;
            core.pc = core.last_pc + core.J_imm();
            core.trap_check_pc_alignment();
            core.write_reg(core.rs1(), link);
        }
    }
};
/* rd() -> rs2() */
struct JAL_186 : OperationMutation<Opcode::JAL, JAL_186> {
    JAL_186() : OperationMutation<Opcode::JAL, JAL_186>("JAL_186") {}
    void apply(ISS &core) {
        {
            auto link = core.pc;
            core.pc = core.last_pc + core.J_imm();
            core.trap_check_pc_alignment();
            core.write_reg(core.rs2(), link);
        }
    }
};
/*  last_pc ->  pc */
struct JAL_187 : OperationMutation<Opcode::JAL, JAL_187> {
    JAL_187() : OperationMutation<Opcode::JAL, JAL_187>("JAL_187") {}
    void apply(ISS &core) {
        {
            auto link = core.pc;
            core.pc = core.pc + core.J_imm();
            core.trap_check_pc_alignment();
            core.write_reg(core.rd(), link);
        }
    }
};
/*  pc ->  last_pc */
struct JAL_188 : OperationMutation<Opcode::JAL, JAL_188> {
    JAL_188() : OperationMutation<Opcode::JAL, JAL_188>("JAL_188") {}
    void apply(ISS &core) {
        {
            auto link = core.last_pc;
            core.pc = core.last_pc + core.J_imm();
            core.trap_check_pc_alignment();
            core.write_reg(core.rd(), link);
        }
    }
};
/*  +  ->  -  */
struct JALR_189 : OperationMutation<Opcode::JALR, JALR_189> {
    JALR_189() : OperationMutation<Opcode::JALR, JALR_189>("JALR_189") {}
    void apply(ISS &core) {
        {
            auto link = core.pc;
            core.pc = (core.read_reg(core.rs1()) - core.I_imm()) & ~1;
            core.trap_check_pc_alignment();
            core.write_reg(core.rd(), link);
        }
    }
};
/*  &  ->  ^  */
struct JALR_190 : OperationMutation<Opcode::JALR, JALR_190> {
    JALR_190() : OperationMutation<Opcode::JALR, JALR_190>("JALR_190") {}
    void apply(ISS &core) {
        {
            auto link = core.pc;
            core.pc = (core.read_reg(core.rs1()) + core.I_imm()) ^ ~1;
            core.trap_check_pc_alignment();
            core.write_reg(core.rd(), link);
        }
    }
};
/*  &  ->  |  */
struct JALR_191 : OperationMutation<Opcode::JALR, JALR_191> {
    JALR_191() : OperationMutation<Opcode::JALR, JALR_191>("JALR_191") {}
    void apply(ISS &core) {
        {
            auto link = core.pc;
            core.pc = (core.read_reg(core.rs1()) + core.I_imm()) | ~1;
            core.trap_check_pc_alignment();
            core.write_reg(core.rd(), link);
        }
    }
};
/* I_imm() -> B_imm() */
struct JALR_192 : OperationMutation<Opcode::JALR, JALR_192> {
    JALR_192() : OperationMutation<Opcode::JALR, JALR_192>("JALR_192") {}
    void apply(ISS &core) {
        {
            auto link = core.pc;
            core.pc = (core.read_reg(core.rs1()) + core.B_imm()) & ~1;
            core.trap_check_pc_alignment();
            core.write_reg(core.rd(), link);
        }
    }
};
/* I_imm() -> U_imm() */
struct JALR_193 : OperationMutation<Opcode::JALR, JALR_193> {
    JALR_193() : OperationMutation<Opcode::JALR, JALR_193>("JALR_193") {}
    void apply(ISS &core) {
        {
            auto link = core.pc;
            core.pc = (core.read_reg(core.rs1()) + core.U_imm()) & ~1;
            core.trap_check_pc_alignment();
            core.write_reg(core.rd(), link);
        }
    }
};
/* I_imm() -> J_imm() */
struct JALR_194 : OperationMutation<Opcode::JALR, JALR_194> {
    JALR_194() : OperationMutation<Opcode::JALR, JALR_194>("JALR_194") {}
    void apply(ISS &core) {
        {
            auto link = core.pc;
            core.pc = (core.read_reg(core.rs1()) + core.J_imm()) & ~1;
            core.trap_check_pc_alignment();
            core.write_reg(core.rd(), link);
        }
    }
};
/* I_imm() -> S_imm() */
struct JALR_195 : OperationMutation<Opcode::JALR, JALR_195> {
    JALR_195() : OperationMutation<Opcode::JALR, JALR_195>("JALR_195") {}
    void apply(ISS &core) {
        {
            auto link = core.pc;
            core.pc = (core.read_reg(core.rs1()) + core.S_imm()) & ~1;
            core.trap_check_pc_alignment();
            core.write_reg(core.rd(), link);
        }
    }
};
/* rs1() -> rd() */
struct JALR_196 : OperationMutation<Opcode::JALR, JALR_196> {
    JALR_196() : OperationMutation<Opcode::JALR, JALR_196>("JALR_196") {}
    void apply(ISS &core) {
        {
            auto link = core.pc;
            core.pc = (core.read_reg(core.rd()) + core.I_imm()) & ~1;
            core.trap_check_pc_alignment();
            core.write_reg(core.rd(), link);
        }
    }
};
/* rs1() -> rs2() */
struct JALR_197 : OperationMutation<Opcode::JALR, JALR_197> {
    JALR_197() : OperationMutation<Opcode::JALR, JALR_197>("JALR_197") {}
    void apply(ISS &core) {
        {
            auto link = core.pc;
            core.pc = (core.read_reg(core.rs2()) + core.I_imm()) & ~1;
            core.trap_check_pc_alignment();
            core.write_reg(core.rd(), link);
        }
    }
};
/* rd() -> rs1() */
struct JALR_198 : OperationMutation<Opcode::JALR, JALR_198> {
    JALR_198() : OperationMutation<Opcode::JALR, JALR_198>("JALR_198") {}
    void apply(ISS &core) {
        {
            auto link = core.pc;
            core.pc = (core.read_reg(core.rs1()) + core.I_imm()) & ~1;
            core.trap_check_pc_alignment();
            core.write_reg(core.rs1(), link);
        }
    }
};
/* rd() -> rs2() */
struct JALR_199 : OperationMutation<Opcode::JALR, JALR_199> {
    JALR_199() : OperationMutation<Opcode::JALR, JALR_199>("JALR_199") {}
    void apply(ISS &core) {
        {
            auto link = core.pc;
            core.pc = (core.read_reg(core.rs1()) + core.I_imm()) & ~1;
            core.trap_check_pc_alignment();
            core.write_reg(core.rs2(), link);
        }
    }
};
/*  pc ->  last_pc */
struct JALR_200 : OperationMutation<Opcode::JALR, JALR_200> {
    JALR_200() : OperationMutation<Opcode::JALR, JALR_200>("JALR_200") {}
    void apply(ISS &core) {
        {
            auto link = core.last_pc;
            core.pc = (core.read_reg(core.rs1()) + core.I_imm()) & ~1;
            core.trap_check_pc_alignment();
            core.write_reg(core.rd(), link);
        }
    }
};
/*  +  ->  -  */
struct SB_201 : OperationMutation<Opcode::SB, SB_201> {
    SB_201() : OperationMutation<Opcode::SB, SB_201>("SB_201") {}
    void apply(ISS &core) {
        {
            uint32_t addr = core.read_reg(core.rs1()) - core.S_imm();
            uint32_t val = core.read_reg(core.rs2());
            core.maybe_mutate_store_access(addr, val);
            core.mem->store_byte(addr, val);
        }
    }
};
/* S_imm() -> B_imm() */
struct SB_202 : OperationMutation<Opcode::SB, SB_202> {
    SB_202() : OperationMutation<Opcode::SB, SB_202>("SB_202") {}
    void apply(ISS &core) {
        {
            uint32_t addr = core.read_reg(core.rs1()) + core.B_imm();
            uint32_t val = core.read_reg(core.rs2());
            core.maybe_mutate_store_access(addr, val);
            core.mem->store_byte(addr, val);
        }
    }
};
/* S_imm() -> U_imm() */
struct SB_203 : OperationMutation<Opcode::SB, SB_203> {
    SB_203() : OperationMutation<Opcode::SB, SB_203>("SB_203") {}
    void apply(ISS &core) {
        {
            uint32_t addr = core.read_reg(core.rs1()) + core.U_imm();
            uint32_t val = core.read_reg(core.rs2());
            core.maybe_mutate_store_access(addr, val);
            core.mem->store_byte(addr, val);
        }
    }
};
/* S_imm() -> I_imm() */
struct SB_204 : OperationMutation<Opcode::SB, SB_204> {
    SB_204() : OperationMutation<Opcode::SB, SB_204>("SB_204") {}
    void apply(ISS &core) {
        {
            uint32_t addr = core.read_reg(core.rs1()) + core.I_imm();
            uint32_t val = core.read_reg(core.rs2());
            core.maybe_mutate_store_access(addr, val);
            core.mem->store_byte(addr, val);
        }
    }
};
/* S_imm() -> J_imm() */
struct SB_205 : OperationMutation<Opcode::SB, SB_205> {
    SB_205() : OperationMutation<Opcode::SB, SB_205>("SB_205") {}
    void apply(ISS &core) {
        {
            uint32_t addr = core.read_reg(core.rs1()) + core.J_imm();
            uint32_t val = core.read_reg(core.rs2());
            core.maybe_mutate_store_access(addr, val);
            core.mem->store_byte(addr, val);
        }
    }
};
/* rs1() -> rd() */
struct SB_206 : OperationMutation<Opcode::SB, SB_206> {
    SB_206() : OperationMutation<Opcode::SB, SB_206>("SB_206") {}
    void apply(ISS &core) {
        {
            uint32_t addr = core.read_reg(core.rd()) + core.S_imm();
            uint32_t val = core.read_reg(core.rs2());
            core.maybe_mutate_store_access(addr, val);
            core.mem->store_byte(addr, val);
        }
    }
};
/* rs1() -> rs2() */
struct SB_207 : OperationMutation<Opcode::SB, SB_207> {
    SB_207() : OperationMutation<Opcode::SB, SB_207>("SB_207") {}
    void apply(ISS &core) {
        {
            uint32_t addr = core.read_reg(core.rs2()) + core.S_imm();
            uint32_t val = core.read_reg(core.rs2());
            core.maybe_mutate_store_access(addr, val);
            core.mem->store_byte(addr, val);
        }
    }
};
/* rs2() -> rs1() */
struct SB_208 : OperationMutation<Opcode::SB, SB_208> {
    SB_208() : OperationMutation<Opcode::SB, SB_208>("SB_208") {}
    void apply(ISS &core) {
        {
            uint32_t addr = core.read_reg(core.rs1()) + core.S_imm();
            uint32_t val = core.read_reg(core.rs1());
            core.maybe_mutate_store_access(addr, val);
            core.mem->store_byte(addr, val);
        }
    }
};
/* rs2() -> rd() */
struct SB_209 : OperationMutation<Opcode::SB, SB_209> {
    SB_209() : OperationMutation<Opcode::SB, SB_209>("SB_209") {}
    void apply(ISS &core) {
        {
            uint32_t addr = core.read_reg(core.rs1()) + core.S_imm();
            uint32_t val = core.read_reg(core.rd());
            core.maybe_mutate_store_access(addr, val);
            core.mem->store_byte(addr, val);
        }
    }
};
/* store_byte -> store_half */
struct SB_210 : OperationMutation<Opcode::SB, SB_210> {
    SB_210() : OperationMutation<Opcode::SB, SB_210>("SB_210") {}
    void apply(ISS &core) {
        uint32_t addr = core.read_reg(core.rs1()) + core.S_imm();
        uint32_t val = core.read_reg(core.rs2());
        core.maybe_mutate_store_access(addr, val);
        core.mem->store_half(addr, val);
    }
};
/* store_byte -> store_word */
struct SB_211 : OperationMutation<Opcode::SB, SB_211> {
    SB_211() : OperationMutation<Opcode::SB, SB_211>("SB_211") {}
    void apply(ISS &core) {
        uint32_t addr = core.read_reg(core.rs1()) + core.S_imm();
        uint32_t val = core.read_reg(core.rs2());
        core.maybe_mutate_store_access(addr, val);
        core.mem->store_word(addr, val);
    }
};
/*  +  ->  -  */
struct SH_212 : OperationMutation<Opcode::SH, SH_212> {
    SH_212() : OperationMutation<Opcode::SH, SH_212>("SH_212") {}
    void apply(ISS &core) {
        uint32_t addr = core.read_reg(core.rs1()) - core.S_imm();
        core.trap_check_addr_alignment<2, false>(addr);
        uint32_t val = core.read_reg(core.rs2());
        core.maybe_mutate_store_access(addr, val);
        core.mem->store_half(addr, val);
    }
};
/* S_imm() -> B_imm() */
struct SH_213 : OperationMutation<Opcode::SH, SH_213> {
    SH_213() : OperationMutation<Opcode::SH, SH_213>("SH_213") {}
    void apply(ISS &core) {
        uint32_t addr = core.read_reg(core.rs1()) + core.B_imm();
        core.trap_check_addr_alignment<2, false>(addr);
        uint32_t val = core.read_reg(core.rs2());
        core.maybe_mutate_store_access(addr, val);
        core.mem->store_half(addr, val);
    }
};
/* S_imm() -> U_imm() */
struct SH_214 : OperationMutation<Opcode::SH, SH_214> {
    SH_214() : OperationMutation<Opcode::SH, SH_214>("SH_214") {}
    void apply(ISS &core) {
        {
            uint32_t addr = core.read_reg(core.rs1()) + core.U_imm();
            core.trap_check_addr_alignment<2, false>(addr);
            uint32_t val = core.read_reg(core.rs2());
            core.maybe_mutate_store_access(addr, val);
            core.mem->store_half(addr, val);
        }
    }
};
/* S_imm() -> I_imm() */
struct SH_215 : OperationMutation<Opcode::SH, SH_215> {
    SH_215() : OperationMutation<Opcode::SH, SH_215>("SH_215") {}
    void apply(ISS &core) {
        {
            uint32_t addr = core.read_reg(core.rs1()) + core.I_imm();
            core.trap_check_addr_alignment<2, false>(addr);
            uint32_t val = core.read_reg(core.rs2());
            core.maybe_mutate_store_access(addr, val);
            core.mem->store_half(addr, val);
        }
    }
};
/* S_imm() -> J_imm() */
struct SH_216 : OperationMutation<Opcode::SH, SH_216> {
    SH_216() : OperationMutation<Opcode::SH, SH_216>("SH_216") {}
    void apply(ISS &core) {
        {
            uint32_t addr = core.read_reg(core.rs1()) + core.J_imm();
            core.trap_check_addr_alignment<2, false>(addr);
            uint32_t val = core.read_reg(core.rs2());
            core.maybe_mutate_store_access(addr, val);
            core.mem->store_half(addr, val);
        }
    }
};
/* rs1() -> rd() */
struct SH_217 : OperationMutation<Opcode::SH, SH_217> {
    SH_217() : OperationMutation<Opcode::SH, SH_217>("SH_217") {}
    void apply(ISS &core) {
        {
            uint32_t addr = core.read_reg(core.rd()) + core.S_imm();
            core.trap_check_addr_alignment<2, false>(addr);
            uint32_t val = core.read_reg(core.rs2());
            core.maybe_mutate_store_access(addr, val);
            core.mem->store_half(addr, val);
        }
    }
};
/* rs1() -> rs2() */
struct SH_218 : OperationMutation<Opcode::SH, SH_218> {
    SH_218() : OperationMutation<Opcode::SH, SH_218>("SH_218") {}
    void apply(ISS &core) {
        {
            uint32_t addr = core.read_reg(core.rs2()) + core.S_imm();
            core.trap_check_addr_alignment<2, false>(addr);
            uint32_t val = core.read_reg(core.rs2());
            core.maybe_mutate_store_access(addr, val);
            core.mem->store_half(addr, val);
        }
    }
};
/* rs2() -> rs1() */
struct SH_219 : OperationMutation<Opcode::SH, SH_219> {
    SH_219() : OperationMutation<Opcode::SH, SH_219>("SH_219") {}
    void apply(ISS &core) {
        {
            uint32_t addr = core.read_reg(core.rs1()) + core.S_imm();
            core.trap_check_addr_alignment<2, false>(addr);
            uint32_t val = core.read_reg(core.rs1());
            core.maybe_mutate_store_access(addr, val);
            core.mem->store_half(addr, val);
        }
    }
};
/* rs2() -> rd() */
struct SH_220 : OperationMutation<Opcode::SH, SH_220> {
    SH_220() : OperationMutation<Opcode::SH, SH_220>("SH_220") {}
    void apply(ISS &core) {
        {
            uint32_t addr = core.read_reg(core.rs1()) + core.S_imm();
            core.trap_check_addr_alignment<2, false>(addr);
            uint32_t val = core.read_reg(core.rd());
            core.maybe_mutate_store_access(addr, val);
            core.mem->store_half(addr, val);
        }
    }
};
/* store_half -> store_word */
struct SH_221 : OperationMutation<Opcode::SH, SH_221> {
    SH_221() : OperationMutation<Opcode::SH, SH_221>("SH_221") {}
    void apply(ISS &core) {
        uint32_t addr = core.read_reg(core.rs1()) + core.S_imm();
        core.trap_check_addr_alignment<2, false>(addr);
        uint32_t val = core.read_reg(core.rs2());
        core.maybe_mutate_store_access(addr, val);
        core.mem->store_word(addr, val);
    }
};
/* store_half -> store_byte */
struct SH_222 : OperationMutation<Opcode::SH, SH_222> {
    SH_222() : OperationMutation<Opcode::SH, SH_222>("SH_222") {}
    void apply(ISS &core) {
        {
            uint32_t addr = core.read_reg(core.rs1()) + core.S_imm();
            core.trap_check_addr_alignment<2, false>(addr);
            uint32_t val = core.read_reg(core.rs2());
            core.maybe_mutate_store_access(addr, val);
            core.mem->store_byte(addr, val);
        }
    }
};
/*  +  ->  -  */
struct SW_223 : OperationMutation<Opcode::SW, SW_223> {
    SW_223() : OperationMutation<Opcode::SW, SW_223>("SW_223") {}
    void apply(ISS &core) {
        {
            uint32_t addr = core.read_reg(core.rs1()) - core.S_imm();
            core.trap_check_addr_alignment<4, false>(addr);
            uint32_t val = core.read_reg(core.rs2());
            core.maybe_mutate_store_access(addr, val);
            core.mem->store_word(addr, val);
        }
    }
};
/* S_imm() -> B_imm() */
struct SW_224 : OperationMutation<Opcode::SW, SW_224> {
    SW_224() : OperationMutation<Opcode::SW, SW_224>("SW_224") {}
    void apply(ISS &core) {
        {
            uint32_t addr = core.read_reg(core.rs1()) + core.B_imm();
            core.trap_check_addr_alignment<4, false>(addr);
            uint32_t val = core.read_reg(core.rs2());
            core.maybe_mutate_store_access(addr, val);
            core.mem->store_word(addr, val);
        }
    }
};
/* S_imm() -> U_imm() */
struct SW_225 : OperationMutation<Opcode::SW, SW_225> {
    SW_225() : OperationMutation<Opcode::SW, SW_225>("SW_225") {}
    void apply(ISS &core) {
        {
            uint32_t addr = core.read_reg(core.rs1()) + core.U_imm();
            core.trap_check_addr_alignment<4, false>(addr);
            uint32_t val = core.read_reg(core.rs2());
            core.maybe_mutate_store_access(addr, val);
            core.mem->store_word(addr, val);
        }
    }
};
/* S_imm() -> I_imm() */
struct SW_226 : OperationMutation<Opcode::SW, SW_226> {
    SW_226() : OperationMutation<Opcode::SW, SW_226>("SW_226") {}
    void apply(ISS &core) {
        {
            uint32_t addr = core.read_reg(core.rs1()) + core.I_imm();
            core.trap_check_addr_alignment<4, false>(addr);
            uint32_t val = core.read_reg(core.rs2());
            core.maybe_mutate_store_access(addr, val);
            core.mem->store_word(addr, val);
        }
    }
};
/* S_imm() -> J_imm() */
struct SW_227 : OperationMutation<Opcode::SW, SW_227> {
    SW_227() : OperationMutation<Opcode::SW, SW_227>("SW_227") {}
    void apply(ISS &core) {
        {
            uint32_t addr = core.read_reg(core.rs1()) + core.J_imm();
            core.trap_check_addr_alignment<4, false>(addr);
            uint32_t val = core.read_reg(core.rs2());
            core.maybe_mutate_store_access(addr, val);
            core.mem->store_word(addr, val);
        }
    }
};
/* rs1() -> rd() */
struct SW_228 : OperationMutation<Opcode::SW, SW_228> {
    SW_228() : OperationMutation<Opcode::SW, SW_228>("SW_228") {}
    void apply(ISS &core) {
        {
            uint32_t addr = core.read_reg(core.rd()) + core.S_imm();
            core.trap_check_addr_alignment<4, false>(addr);
            uint32_t val = core.read_reg(core.rs2());
            core.maybe_mutate_store_access(addr, val);
            core.mem->store_word(addr, val);
        }
    }
};
/* rs1() -> rs2() */
struct SW_229 : OperationMutation<Opcode::SW, SW_229> {
    SW_229() : OperationMutation<Opcode::SW, SW_229>("SW_229") {}
    void apply(ISS &core) {
        {
            uint32_t addr = core.read_reg(core.rs2()) + core.S_imm();
            core.trap_check_addr_alignment<4, false>(addr);
            uint32_t val = core.read_reg(core.rs2());
            core.maybe_mutate_store_access(addr, val);
            core.mem->store_word(addr, val);
        }
    }
};
/* rs2() -> rs1() */
struct SW_230 : OperationMutation<Opcode::SW, SW_230> {
    SW_230() : OperationMutation<Opcode::SW, SW_230>("SW_230") {}
    void apply(ISS &core) {
        {
            uint32_t addr = core.read_reg(core.rs1()) + core.S_imm();
            core.trap_check_addr_alignment<4, false>(addr);
            uint32_t val = core.read_reg(core.rs1());
            core.maybe_mutate_store_access(addr, val);
            core.mem->store_word(addr, val);
        }
    }
};
/* rs2() -> rd() */
struct SW_231 : OperationMutation<Opcode::SW, SW_231> {
    SW_231() : OperationMutation<Opcode::SW, SW_231>("SW_231") {}
    void apply(ISS &core) {
        {
            uint32_t addr = core.read_reg(core.rs1()) + core.S_imm();
            core.trap_check_addr_alignment<4, false>(addr);
            uint32_t val = core.read_reg(core.rd());
            core.maybe_mutate_store_access(addr, val);
            core.mem->store_word(addr, val);
        }
    }
};
/* store_word -> store_half */
struct SW_232 : OperationMutation<Opcode::SW, SW_232> {
    SW_232() : OperationMutation<Opcode::SW, SW_232>("SW_232") {}
    void apply(ISS &core) {
        {
            uint32_t addr = core.read_reg(core.rs1()) + core.S_imm();
            core.trap_check_addr_alignment<4, false>(addr);
            uint32_t val = core.read_reg(core.rs2());
            core.maybe_mutate_store_access(addr, val);
            core.mem->store_half(addr, val);
        }
    }
};
/* store_word -> store_byte */
struct SW_233 : OperationMutation<Opcode::SW, SW_233> {
    SW_233() : OperationMutation<Opcode::SW, SW_233>("SW_233") {}
    void apply(ISS &core) {
        {
            uint32_t addr = core.read_reg(core.rs1()) + core.S_imm();
            core.trap_check_addr_alignment<4, false>(addr);
            uint32_t val = core.read_reg(core.rs2());
            core.maybe_mutate_store_access(addr, val);
            core.mem->store_byte(addr, val);
        }
    }
};
/*  +  ->  -  */
struct LB_234 : OperationMutation<Opcode::LB, LB_234> {
    LB_234() : OperationMutation<Opcode::LB, LB_234>("LB_234") {}
    void apply(ISS &core) {
        {
            uint32_t addr = core.read_reg(core.rs1()) - core.I_imm();
            addr = core.maybe_mutate_load_addr(addr);
            auto val = core.mem->load_byte(addr);
            core.write_reg(core.rd(), core.maybe_mutate_load_value(addr, val));
        }
    }
};
/* I_imm() -> B_imm() */
struct LB_235 : OperationMutation<Opcode::LB, LB_235> {
    LB_235() : OperationMutation<Opcode::LB, LB_235>("LB_235") {}
    void apply(ISS &core) {
        {
            uint32_t addr = core.read_reg(core.rs1()) + core.B_imm();
            addr = core.maybe_mutate_load_addr(addr);
            auto val = core.mem->load_byte(addr);
            core.write_reg(core.rd(), core.maybe_mutate_load_value(addr, val));
        }
    }
};
/* I_imm() -> U_imm() */
struct LB_236 : OperationMutation<Opcode::LB, LB_236> {
    LB_236() : OperationMutation<Opcode::LB, LB_236>("LB_236") {}
    void apply(ISS &core) {
        {
            uint32_t addr = core.read_reg(core.rs1()) + core.U_imm();
            addr = core.maybe_mutate_load_addr(addr);
            auto val = core.mem->load_byte(addr);
            core.write_reg(core.rd(), core.maybe_mutate_load_value(addr, val));
        }
    }
};
/* I_imm() -> J_imm() */
struct LB_237 : OperationMutation<Opcode::LB, LB_237> {
    LB_237() : OperationMutation<Opcode::LB, LB_237>("LB_237") {}
    void apply(ISS &core) {
        {
            uint32_t addr = core.read_reg(core.rs1()) + core.J_imm();
            addr = core.maybe_mutate_load_addr(addr);
            auto val = core.mem->load_byte(addr);
            core.write_reg(core.rd(), core.maybe_mutate_load_value(addr, val));
        }
    }
};
/* I_imm() -> S_imm() */
struct LB_238 : OperationMutation<Opcode::LB, LB_238> {
    LB_238() : OperationMutation<Opcode::LB, LB_238>("LB_238") {}
    void apply(ISS &core) {
        {
            uint32_t addr = core.read_reg(core.rs1()) + core.S_imm();
            addr = core.maybe_mutate_load_addr(addr);
            auto val = core.mem->load_byte(addr);
            core.write_reg(core.rd(), core.maybe_mutate_load_value(addr, val));
        }
    }
};
/* rs1() -> rd() */
struct LB_239 : OperationMutation<Opcode::LB, LB_239> {
    LB_239() : OperationMutation<Opcode::LB, LB_239>("LB_239") {}
    void apply(ISS &core) {
        {
            uint32_t addr = core.read_reg(core.rd()) + core.I_imm();
            addr = core.maybe_mutate_load_addr(addr);
            auto val = core.mem->load_byte(addr);
            core.write_reg(core.rd(), core.maybe_mutate_load_value(addr, val));
        }
    }
};
/* rs1() -> rs2() */
struct LB_240 : OperationMutation<Opcode::LB, LB_240> {
    LB_240() : OperationMutation<Opcode::LB, LB_240>("LB_240") {}
    void apply(ISS &core) {
        {
            uint32_t addr = core.read_reg(core.rs2()) + core.I_imm();
            addr = core.maybe_mutate_load_addr(addr);
            auto val = core.mem->load_byte(addr);
            core.write_reg(core.rd(), core.maybe_mutate_load_value(addr, val));
        }
    }
};
/* rd() -> rs1() */
struct LB_241 : OperationMutation<Opcode::LB, LB_241> {
    LB_241() : OperationMutation<Opcode::LB, LB_241>("LB_241") {}
    void apply(ISS &core) {
        {
            uint32_t addr = core.read_reg(core.rs1()) + core.I_imm();
            addr = core.maybe_mutate_load_addr(addr);
            auto val = core.mem->load_byte(addr);
            core.write_reg(core.rs1(), core.maybe_mutate_load_value(addr, val));
        }
    }
};
/* rd() -> rs2() */
struct LB_242 : OperationMutation<Opcode::LB, LB_242> {
    LB_242() : OperationMutation<Opcode::LB, LB_242>("LB_242") {}
    void apply(ISS &core) {
        {
            uint32_t addr = core.read_reg(core.rs1()) + core.I_imm();
            addr = core.maybe_mutate_load_addr(addr);
            auto val = core.mem->load_byte(addr);
            core.write_reg(core.rs2(), core.maybe_mutate_load_value(addr, val));
        }
    }
};
/* load_byte -> load_uhalf */
struct LB_243 : OperationMutation<Opcode::LB, LB_243> {
    LB_243() : OperationMutation<Opcode::LB, LB_243>("LB_243") {}
    void apply(ISS &core) {
        uint32_t addr = core.read_reg(core.rs1()) + core.I_imm();
        addr = core.maybe_mutate_load_addr(addr);
        auto val = core.mem->load_uhalf(addr);
        core.write_reg(core.rd(), core.maybe_mutate_load_value(addr, val));
    }
};
/* load_byte -> load_half */
struct LB_244 : OperationMutation<Opcode::LB, LB_244> {
    LB_244() : OperationMutation<Opcode::LB, LB_244>("LB_244") {}
    void apply(ISS &core) {
        {
            uint32_t addr = core.read_reg(core.rs1()) + core.I_imm();
            addr = core.maybe_mutate_load_addr(addr);
            auto val = core.mem->load_half(addr);
            core.write_reg(core.rd(), core.maybe_mutate_load_value(addr, val));
        }
    }
};
/* load_byte -> load_ubyte */
struct LB_245 : OperationMutation<Opcode::LB, LB_245> {
    LB_245() : OperationMutation<Opcode::LB, LB_245>("LB_245") {}
    void apply(ISS &core) {
        {
            uint32_t addr = core.read_reg(core.rs1()) + core.I_imm();
            addr = core.maybe_mutate_load_addr(addr);
            auto val = core.mem->load_ubyte(addr);
            core.write_reg(core.rd(), core.maybe_mutate_load_value(addr, val));
        }
    }
};
/* load_byte -> load_word */
struct LB_246 : OperationMutation<Opcode::LB, LB_246> {
    LB_246() : OperationMutation<Opcode::LB, LB_246>("LB_246") {}
    void apply(ISS &core) {
        {
            uint32_t addr = core.read_reg(core.rs1()) + core.I_imm();
            addr = core.maybe_mutate_load_addr(addr);
            auto val = core.mem->load_word(addr);
            core.write_reg(core.rd(), core.maybe_mutate_load_value(addr, val));
        }
    }
};
/*  +  ->  -  */
struct LH_247 : OperationMutation<Opcode::LH, LH_247> {
    LH_247() : OperationMutation<Opcode::LH, LH_247>("LH_247") {}
    void apply(ISS &core) {
        {
            uint32_t addr = core.read_reg(core.rs1()) - core.I_imm();
            core.trap_check_addr_alignment<2, true>(addr);
            addr = core.maybe_mutate_load_addr(addr);
            auto val = core.mem->load_half(addr);
            core.write_reg(core.rd(), core.maybe_mutate_load_value(addr, val));
        }
    }
};
/* I_imm() -> B_imm() */
struct LH_248 : OperationMutation<Opcode::LH, LH_248> {
    LH_248() : OperationMutation<Opcode::LH, LH_248>("LH_248") {}
    void apply(ISS &core) {
        {
            uint32_t addr = core.read_reg(core.rs1()) + core.B_imm();
            core.trap_check_addr_alignment<2, true>(addr);
            addr = core.maybe_mutate_load_addr(addr);
            auto val = core.mem->load_half(addr);
            core.write_reg(core.rd(), core.maybe_mutate_load_value(addr, val));
        }
    }
};
/* I_imm() -> U_imm() */
struct LH_249 : OperationMutation<Opcode::LH, LH_249> {
    LH_249() : OperationMutation<Opcode::LH, LH_249>("LH_249") {}
    void apply(ISS &core) {
        {
            uint32_t addr = core.read_reg(core.rs1()) + core.U_imm();
            core.trap_check_addr_alignment<2, true>(addr);
            addr = core.maybe_mutate_load_addr(addr);
            auto val = core.mem->load_half(addr);
            core.write_reg(core.rd(), core.maybe_mutate_load_value(addr, val));
        }
    }
};
/* I_imm() -> J_imm() */
struct LH_250 : OperationMutation<Opcode::LH, LH_250> {
    LH_250() : OperationMutation<Opcode::LH, LH_250>("LH_250") {}
    void apply(ISS &core) {
        {
            uint32_t addr = core.read_reg(core.rs1()) + core.J_imm();
            core.trap_check_addr_alignment<2, true>(addr);
            addr = core.maybe_mutate_load_addr(addr);
            auto val = core.mem->load_half(addr);
            core.write_reg(core.rd(), core.maybe_mutate_load_value(addr, val));
        }
    }
};
/* I_imm() -> S_imm() */
struct LH_251 : OperationMutation<Opcode::LH, LH_251> {
    LH_251() : OperationMutation<Opcode::LH, LH_251>("LH_251") {}
    void apply(ISS &core) {
        {
            uint32_t addr = core.read_reg(core.rs1()) + core.S_imm();
            core.trap_check_addr_alignment<2, true>(addr);
            addr = core.maybe_mutate_load_addr(addr);
            auto val = core.mem->load_half(addr);
            core.write_reg(core.rd(), core.maybe_mutate_load_value(addr, val));
        }
    }
};
/* rs1() -> rd() */
struct LH_252 : OperationMutation<Opcode::LH, LH_252> {
    LH_252() : OperationMutation<Opcode::LH, LH_252>("LH_252") {}
    void apply(ISS &core) {
        {
            uint32_t addr = core.read_reg(core.rd()) + core.I_imm();
            core.trap_check_addr_alignment<2, true>(addr);
            addr = core.maybe_mutate_load_addr(addr);
            auto val = core.mem->load_half(addr);
            core.write_reg(core.rd(), core.maybe_mutate_load_value(addr, val));
        }
    }
};
/* rs1() -> rs2() */
struct LH_253 : OperationMutation<Opcode::LH, LH_253> {
    LH_253() : OperationMutation<Opcode::LH, LH_253>("LH_253") {}
    void apply(ISS &core) {
        {
            uint32_t addr = core.read_reg(core.rs2()) + core.I_imm();
            core.trap_check_addr_alignment<2, true>(addr);
            addr = core.maybe_mutate_load_addr(addr);
            auto val = core.mem->load_half(addr);
            core.write_reg(core.rd(), core.maybe_mutate_load_value(addr, val));
        }
    }
};
/* rd() -> rs1() */
struct LH_254 : OperationMutation<Opcode::LH, LH_254> {
    LH_254() : OperationMutation<Opcode::LH, LH_254>("LH_254") {}
    void apply(ISS &core) {
        {
            uint32_t addr = core.read_reg(core.rs1()) + core.I_imm();
            core.trap_check_addr_alignment<2, true>(addr);
            addr = core.maybe_mutate_load_addr(addr);
            auto val = core.mem->load_half(addr);
            core.write_reg(core.rs1(), core.maybe_mutate_load_value(addr, val));
        }
    }
};
/* rd() -> rs2() */
struct LH_255 : OperationMutation<Opcode::LH, LH_255> {
    LH_255() : OperationMutation<Opcode::LH, LH_255>("LH_255") {}
    void apply(ISS &core) {
        {
            uint32_t addr = core.read_reg(core.rs1()) + core.I_imm();
            core.trap_check_addr_alignment<2, true>(addr);
            addr = core.maybe_mutate_load_addr(addr);
            auto val = core.mem->load_half(addr);
            core.write_reg(core.rs2(), core.maybe_mutate_load_value(addr, val));
        }
    }
};
/* load_half -> load_uhalf */
struct LH_256 : OperationMutation<Opcode::LH, LH_256> {
    LH_256() : OperationMutation<Opcode::LH, LH_256>("LH_256") {}
    void apply(ISS &core) {
        {
            uint32_t addr = core.read_reg(core.rs1()) + core.I_imm();
            core.trap_check_addr_alignment<2, true>(addr);
            addr = core.maybe_mutate_load_addr(addr);
            auto val = core.mem->load_uhalf(addr);
            core.write_reg(core.rd(), core.maybe_mutate_load_value(addr, val));
        }
    }
};
/* load_half -> load_byte */
struct LH_257 : OperationMutation<Opcode::LH, LH_257> {
    LH_257() : OperationMutation<Opcode::LH, LH_257>("LH_257") {}
    void apply(ISS &core) {
        {
            uint32_t addr = core.read_reg(core.rs1()) + core.I_imm();
            core.trap_check_addr_alignment<2, true>(addr);
            addr = core.maybe_mutate_load_addr(addr);
            auto val = core.mem->load_byte(addr);
            core.write_reg(core.rd(), core.maybe_mutate_load_value(addr, val));
        }
    }
};
/* load_half -> load_ubyte */
struct LH_258 : OperationMutation<Opcode::LH, LH_258> {
    LH_258() : OperationMutation<Opcode::LH, LH_258>("LH_258") {}
    void apply(ISS &core) {
        {
            uint32_t addr = core.read_reg(core.rs1()) + core.I_imm();
            core.trap_check_addr_alignment<2, true>(addr);
            addr = core.maybe_mutate_load_addr(addr);
            auto val = core.mem->load_ubyte(addr);
            core.write_reg(core.rd(), core.maybe_mutate_load_value(addr, val));
        }
    }
};
/* load_half -> load_word */
struct LH_259 : OperationMutation<Opcode::LH, LH_259> {
    LH_259() : OperationMutation<Opcode::LH, LH_259>("LH_259") {}
    void apply(ISS &core) {
        {
            uint32_t addr = core.read_reg(core.rs1()) + core.I_imm();
            core.trap_check_addr_alignment<2, true>(addr);
            addr = core.maybe_mutate_load_addr(addr);
            auto val = core.mem->load_word(addr);
            core.write_reg(core.rd(), core.maybe_mutate_load_value(addr, val));
        }
    }
};
/*  +  ->  -  */
struct LW_260 : OperationMutation<Opcode::LW, LW_260> {
    LW_260() : OperationMutation<Opcode::LW, LW_260>("LW_260") {}
    void apply(ISS &core) {
        {
            uint32_t addr = core.read_reg(core.rs1()) - core.I_imm();
            core.trap_check_addr_alignment<4, true>(addr);
            addr = core.maybe_mutate_load_addr(addr);
            auto val = core.mem->load_word(addr);
            core.write_reg(core.rd(), core.maybe_mutate_load_value(addr, val));
        }
    }
};
/* I_imm() -> B_imm() */
struct LW_261 : OperationMutation<Opcode::LW, LW_261> {
    LW_261() : OperationMutation<Opcode::LW, LW_261>("LW_261") {}
    void apply(ISS &core) {
        {
            uint32_t addr = core.read_reg(core.rs1()) + core.B_imm();
            core.trap_check_addr_alignment<4, true>(addr);
            addr = core.maybe_mutate_load_addr(addr);
            auto val = core.mem->load_word(addr);
            core.write_reg(core.rd(), core.maybe_mutate_load_value(addr, val));
        }
    }
};
/* I_imm() -> U_imm() */
struct LW_262 : OperationMutation<Opcode::LW, LW_262> {
    LW_262() : OperationMutation<Opcode::LW, LW_262>("LW_262") {}
    void apply(ISS &core) {
        {
            uint32_t addr = core.read_reg(core.rs1()) + core.U_imm();
            core.trap_check_addr_alignment<4, true>(addr);
            addr = core.maybe_mutate_load_addr(addr);
            auto val = core.mem->load_word(addr);
            core.write_reg(core.rd(), core.maybe_mutate_load_value(addr, val));
        }
    }
};
/* I_imm() -> J_imm() */
struct LW_263 : OperationMutation<Opcode::LW, LW_263> {
    LW_263() : OperationMutation<Opcode::LW, LW_263>("LW_263") {}
    void apply(ISS &core) {
        {
            uint32_t addr = core.read_reg(core.rs1()) + core.J_imm();
            core.trap_check_addr_alignment<4, true>(addr);
            addr = core.maybe_mutate_load_addr(addr);
            auto val = core.mem->load_word(addr);
            core.write_reg(core.rd(), core.maybe_mutate_load_value(addr, val));
        }
    }
};
/* I_imm() -> S_imm() */
struct LW_264 : OperationMutation<Opcode::LW, LW_264> {
    LW_264() : OperationMutation<Opcode::LW, LW_264>("LW_264") {}
    void apply(ISS &core) {
        {
            uint32_t addr = core.read_reg(core.rs1()) + core.S_imm();
            core.trap_check_addr_alignment<4, true>(addr);
            addr = core.maybe_mutate_load_addr(addr);
            auto val = core.mem->load_word(addr);
            core.write_reg(core.rd(), core.maybe_mutate_load_value(addr, val));
        }
    }
};
/* rs1() -> rd() */
struct LW_265 : OperationMutation<Opcode::LW, LW_265> {
    LW_265() : OperationMutation<Opcode::LW, LW_265>("LW_265") {}
    void apply(ISS &core) {
        {
            uint32_t addr = core.read_reg(core.rd()) + core.I_imm();
            core.trap_check_addr_alignment<4, true>(addr);
            addr = core.maybe_mutate_load_addr(addr);
            auto val = core.mem->load_word(addr);
            core.write_reg(core.rd(), core.maybe_mutate_load_value(addr, val));
        }
    }
};
/* rs1() -> rs2() */
struct LW_266 : OperationMutation<Opcode::LW, LW_266> {
    LW_266() : OperationMutation<Opcode::LW, LW_266>("LW_266") {}
    void apply(ISS &core) {
        {
            uint32_t addr = core.read_reg(core.rs2()) + core.I_imm();
            core.trap_check_addr_alignment<4, true>(addr);
            addr = core.maybe_mutate_load_addr(addr);
            auto val = core.mem->load_word(addr);
            core.write_reg(core.rd(), core.maybe_mutate_load_value(addr, val));
        }
    }
};
/* rd() -> rs1() */
struct LW_267 : OperationMutation<Opcode::LW, LW_267> {
    LW_267() : OperationMutation<Opcode::LW, LW_267>("LW_267") {}
    void apply(ISS &core) {
        {
            uint32_t addr = core.read_reg(core.rs1()) + core.I_imm();
            core.trap_check_addr_alignment<4, true>(addr);
            addr = core.maybe_mutate_load_addr(addr);
            auto val = core.mem->load_word(addr);
            core.write_reg(core.rs1(), core.maybe_mutate_load_value(addr, val));
        }
    }
};
/* rd() -> rs2() */
struct LW_268 : OperationMutation<Opcode::LW, LW_268> {
    LW_268() : OperationMutation<Opcode::LW, LW_268>("LW_268") {}
    void apply(ISS &core) {
        {
            uint32_t addr = core.read_reg(core.rs1()) + core.I_imm();
            core.trap_check_addr_alignment<4, true>(addr);
            addr = core.maybe_mutate_load_addr(addr);
            auto val = core.mem->load_word(addr);
            core.write_reg(core.rs2(), core.maybe_mutate_load_value(addr, val));
        }
    }
};
/* load_word -> load_uhalf */
struct LW_269 : OperationMutation<Opcode::LW, LW_269> {
    LW_269() : OperationMutation<Opcode::LW, LW_269>("LW_269") {}
    void apply(ISS &core) {
        {
            uint32_t addr = core.read_reg(core.rs1()) + core.I_imm();
            core.trap_check_addr_alignment<4, true>(addr);
            addr = core.maybe_mutate_load_addr(addr);
            auto val = core.mem->load_uhalf(addr);
            core.write_reg(core.rd(), core.maybe_mutate_load_value(addr, val));
        }
    }
};
/* load_word -> load_byte */
struct LW_270 : OperationMutation<Opcode::LW, LW_270> {
    LW_270() : OperationMutation<Opcode::LW, LW_270>("LW_270") {}
    void apply(ISS &core) {
        {
            uint32_t addr = core.read_reg(core.rs1()) + core.I_imm();
            core.trap_check_addr_alignment<4, true>(addr);
            addr = core.maybe_mutate_load_addr(addr);
            auto val = core.mem->load_byte(addr);
            core.write_reg(core.rd(), core.maybe_mutate_load_value(addr, val));
        }
    }
};
/* load_word -> load_half */
struct LW_271 : OperationMutation<Opcode::LW, LW_271> {
    LW_271() : OperationMutation<Opcode::LW, LW_271>("LW_271") {}
    void apply(ISS &core) {
        {
            uint32_t addr = core.read_reg(core.rs1()) + core.I_imm();
            core.trap_check_addr_alignment<4, true>(addr);
            addr = core.maybe_mutate_load_addr(addr);
            auto val = core.mem->load_half(addr);
            core.write_reg(core.rd(), core.maybe_mutate_load_value(addr, val));
        }
    }
};
/* load_word -> load_ubyte */
struct LW_272 : OperationMutation<Opcode::LW, LW_272> {
    LW_272() : OperationMutation<Opcode::LW, LW_272>("LW_272") {}
    void apply(ISS &core) {
        {
            uint32_t addr = core.read_reg(core.rs1()) + core.I_imm();
            core.trap_check_addr_alignment<4, true>(addr);
            addr = core.maybe_mutate_load_addr(addr);
            auto val = core.mem->load_ubyte(addr);
            core.write_reg(core.rd(), core.maybe_mutate_load_value(addr, val));
        }
    }
};
/*  +  ->  -  */
struct LBU_273 : OperationMutation<Opcode::LBU, LBU_273> {
    LBU_273() : OperationMutation<Opcode::LBU, LBU_273>("LBU_273") {}
    void apply(ISS &core) {
        {
            uint32_t addr = core.read_reg(core.rs1()) - core.I_imm();
            addr = core.maybe_mutate_load_addr(addr);
            auto val = core.mem->load_ubyte(addr);
            core.write_reg(core.rd(), core.maybe_mutate_load_value(addr, val));
        }
    }
};
/* I_imm() -> B_imm() */
struct LBU_274 : OperationMutation<Opcode::LBU, LBU_274> {
    LBU_274() : OperationMutation<Opcode::LBU, LBU_274>("LBU_274") {}
    void apply(ISS &core) {
        {
            uint32_t addr = core.read_reg(core.rs1()) + core.B_imm();
            addr = core.maybe_mutate_load_addr(addr);
            auto val = core.mem->load_ubyte(addr);
            core.write_reg(core.rd(), core.maybe_mutate_load_value(addr, val));
        }
    }
};
/* I_imm() -> U_imm() */
struct LBU_275 : OperationMutation<Opcode::LBU, LBU_275> {
    LBU_275() : OperationMutation<Opcode::LBU, LBU_275>("LBU_275") {}
    void apply(ISS &core) {
        {
            uint32_t addr = core.read_reg(core.rs1()) + core.U_imm();
            addr = core.maybe_mutate_load_addr(addr);
            auto val = core.mem->load_ubyte(addr);
            core.write_reg(core.rd(), core.maybe_mutate_load_value(addr, val));
        }
    }
};
/* I_imm() -> J_imm() */
struct LBU_276 : OperationMutation<Opcode::LBU, LBU_276> {
    LBU_276() : OperationMutation<Opcode::LBU, LBU_276>("LBU_276") {}
    void apply(ISS &core) {
        {
            uint32_t addr = core.read_reg(core.rs1()) + core.J_imm();
            addr = core.maybe_mutate_load_addr(addr);
            auto val = core.mem->load_ubyte(addr);
            core.write_reg(core.rd(), core.maybe_mutate_load_value(addr, val));
        }
    }
};
/* I_imm() -> S_imm() */
struct LBU_277 : OperationMutation<Opcode::LBU, LBU_277> {
    LBU_277() : OperationMutation<Opcode::LBU, LBU_277>("LBU_277") {}
    void apply(ISS &core) {
        {
            uint32_t addr = core.read_reg(core.rs1()) + core.S_imm();
            addr = core.maybe_mutate_load_addr(addr);
            auto val = core.mem->load_ubyte(addr);
            core.write_reg(core.rd(), core.maybe_mutate_load_value(addr, val));
        }
    }
};
/* rs1() -> rd() */
struct LBU_278 : OperationMutation<Opcode::LBU, LBU_278> {
    LBU_278() : OperationMutation<Opcode::LBU, LBU_278>("LBU_278") {}
    void apply(ISS &core) {
        {
            uint32_t addr = core.read_reg(core.rd()) + core.I_imm();
            addr = core.maybe_mutate_load_addr(addr);
            auto val = core.mem->load_ubyte(addr);
            core.write_reg(core.rd(), core.maybe_mutate_load_value(addr, val));
        }
    }
};
/* rs1() -> rs2() */
struct LBU_279 : OperationMutation<Opcode::LBU, LBU_279> {
    LBU_279() : OperationMutation<Opcode::LBU, LBU_279>("LBU_279") {}
    void apply(ISS &core) {
        {
            uint32_t addr = core.read_reg(core.rs2()) + core.I_imm();
            addr = core.maybe_mutate_load_addr(addr);
            auto val = core.mem->load_ubyte(addr);
            core.write_reg(core.rd(), core.maybe_mutate_load_value(addr, val));
        }
    }
};
/* rd() -> rs1() */
struct LBU_280 : OperationMutation<Opcode::LBU, LBU_280> {
    LBU_280() : OperationMutation<Opcode::LBU, LBU_280>("LBU_280") {}
    void apply(ISS &core) {
        {
            uint32_t addr = core.read_reg(core.rs1()) + core.I_imm();
            addr = core.maybe_mutate_load_addr(addr);
            auto val = core.mem->load_ubyte(addr);
            core.write_reg(core.rs1(), core.maybe_mutate_load_value(addr, val));
        }
    }
};
/* rd() -> rs2() */
struct LBU_281 : OperationMutation<Opcode::LBU, LBU_281> {
    LBU_281() : OperationMutation<Opcode::LBU, LBU_281>("LBU_281") {}
    void apply(ISS &core) {
        {
            uint32_t addr = core.read_reg(core.rs1()) + core.I_imm();
            addr = core.maybe_mutate_load_addr(addr);
            auto val = core.mem->load_ubyte(addr);
            core.write_reg(core.rs2(), core.maybe_mutate_load_value(addr, val));
        }
    }
};
/* load_ubyte -> load_uhalf */
struct LBU_282 : OperationMutation<Opcode::LBU, LBU_282> {
    LBU_282() : OperationMutation<Opcode::LBU, LBU_282>("LBU_282") {}
    void apply(ISS &core) {
        {
            uint32_t addr = core.read_reg(core.rs1()) + core.I_imm();
            addr = core.maybe_mutate_load_addr(addr);
            auto val = core.mem->load_uhalf(addr);
            core.write_reg(core.rd(), core.maybe_mutate_load_value(addr, val));
        }
    }
};
/* load_ubyte -> load_byte */
struct LBU_283 : OperationMutation<Opcode::LBU, LBU_283> {
    LBU_283() : OperationMutation<Opcode::LBU, LBU_283>("LBU_283") {}
    void apply(ISS &core) {
        {
            uint32_t addr = core.read_reg(core.rs1()) + core.I_imm();
            addr = core.maybe_mutate_load_addr(addr);
            auto val = core.mem->load_byte(addr);
            core.write_reg(core.rd(), core.maybe_mutate_load_value(addr, val));
        }
    }
};
/* load_ubyte -> load_half */
struct LBU_284 : OperationMutation<Opcode::LBU, LBU_284> {
    LBU_284() : OperationMutation<Opcode::LBU, LBU_284>("LBU_284") {}
    void apply(ISS &core) {
        {
            uint32_t addr = core.read_reg(core.rs1()) + core.I_imm();
            addr = core.maybe_mutate_load_addr(addr);
            auto val = core.mem->load_half(addr);
            core.write_reg(core.rd(), core.maybe_mutate_load_value(addr, val));
        }
    }
};
/* load_ubyte -> load_word */
struct LBU_285 : OperationMutation<Opcode::LBU, LBU_285> {
    LBU_285() : OperationMutation<Opcode::LBU, LBU_285>("LBU_285") {}
    void apply(ISS &core) {
        {
            uint32_t addr = core.read_reg(core.rs1()) + core.I_imm();
            addr = core.maybe_mutate_load_addr(addr);
            auto val = core.mem->load_word(addr);
            core.write_reg(core.rd(), core.maybe_mutate_load_value(addr, val));
        }
    }
};
/*  +  ->  -  */
struct LHU_286 : OperationMutation<Opcode::LHU, LHU_286> {
    LHU_286() : OperationMutation<Opcode::LHU, LHU_286>("LHU_286") {}
    void apply(ISS &core) {
        {
            uint32_t addr = core.read_reg(core.rs1()) - core.I_imm();
            core.trap_check_addr_alignment<2, true>(addr);
            addr = core.maybe_mutate_load_addr(addr);
            auto val = core.mem->load_uhalf(addr);
            core.write_reg(core.rd(), core.maybe_mutate_load_value(addr, val));
        }
    }
};
/* I_imm() -> B_imm() */
struct LHU_287 : OperationMutation<Opcode::LHU, LHU_287> {
    LHU_287() : OperationMutation<Opcode::LHU, LHU_287>("LHU_287") {}
    void apply(ISS &core) {
        {
            uint32_t addr = core.read_reg(core.rs1()) + core.B_imm();
            core.trap_check_addr_alignment<2, true>(addr);
            addr = core.maybe_mutate_load_addr(addr);
            auto val = core.mem->load_uhalf(addr);
            core.write_reg(core.rd(), core.maybe_mutate_load_value(addr, val));
        }
    }
};
/* I_imm() -> U_imm() */
struct LHU_288 : OperationMutation<Opcode::LHU, LHU_288> {
    LHU_288() : OperationMutation<Opcode::LHU, LHU_288>("LHU_288") {}
    void apply(ISS &core) {
        {
            uint32_t addr = core.read_reg(core.rs1()) + core.U_imm();
            core.trap_check_addr_alignment<2, true>(addr);
            addr = core.maybe_mutate_load_addr(addr);
            auto val = core.mem->load_uhalf(addr);
            core.write_reg(core.rd(), core.maybe_mutate_load_value(addr, val));
        }
    }
};
/* I_imm() -> J_imm() */
struct LHU_289 : OperationMutation<Opcode::LHU, LHU_289> {
    LHU_289() : OperationMutation<Opcode::LHU, LHU_289>("LHU_289") {}
    void apply(ISS &core) {
        {
            uint32_t addr = core.read_reg(core.rs1()) + core.J_imm();
            core.trap_check_addr_alignment<2, true>(addr);
            addr = core.maybe_mutate_load_addr(addr);
            auto val = core.mem->load_uhalf(addr);
            core.write_reg(core.rd(), core.maybe_mutate_load_value(addr, val));
        }
    }
};
/* I_imm() -> S_imm() */
struct LHU_290 : OperationMutation<Opcode::LHU, LHU_290> {
    LHU_290() : OperationMutation<Opcode::LHU, LHU_290>("LHU_290") {}
    void apply(ISS &core) {
        {
            uint32_t addr = core.read_reg(core.rs1()) + core.S_imm();
            core.trap_check_addr_alignment<2, true>(addr);
            addr = core.maybe_mutate_load_addr(addr);
            auto val = core.mem->load_uhalf(addr);
            core.write_reg(core.rd(), core.maybe_mutate_load_value(addr, val));
        }
    }
};
/* rs1() -> rd() */
struct LHU_291 : OperationMutation<Opcode::LHU, LHU_291> {
    LHU_291() : OperationMutation<Opcode::LHU, LHU_291>("LHU_291") {}
    void apply(ISS &core) {
        {
            uint32_t addr = core.read_reg(core.rd()) + core.I_imm();
            core.trap_check_addr_alignment<2, true>(addr);
            addr = core.maybe_mutate_load_addr(addr);
            auto val = core.mem->load_uhalf(addr);
            core.write_reg(core.rd(), core.maybe_mutate_load_value(addr, val));
        }
    }
};
/* rs1() -> rs2() */
struct LHU_292 : OperationMutation<Opcode::LHU, LHU_292> {
    LHU_292() : OperationMutation<Opcode::LHU, LHU_292>("LHU_292") {}
    void apply(ISS &core) {
        {
            uint32_t addr = core.read_reg(core.rs2()) + core.I_imm();
            core.trap_check_addr_alignment<2, true>(addr);
            addr = core.maybe_mutate_load_addr(addr);
            auto val = core.mem->load_uhalf(addr);
            core.write_reg(core.rd(), core.maybe_mutate_load_value(addr, val));
        }
    }
};
/* rd() -> rs1() */
struct LHU_293 : OperationMutation<Opcode::LHU, LHU_293> {
    LHU_293() : OperationMutation<Opcode::LHU, LHU_293>("LHU_293") {}
    void apply(ISS &core) {
        {
            uint32_t addr = core.read_reg(core.rs1()) + core.I_imm();
            core.trap_check_addr_alignment<2, true>(addr);
            addr = core.maybe_mutate_load_addr(addr);
            auto val = core.mem->load_uhalf(addr);
            core.write_reg(core.rs1(), core.maybe_mutate_load_value(addr, val));
        }
    }
};
/* rd() -> rs2() */
struct LHU_294 : OperationMutation<Opcode::LHU, LHU_294> {
    LHU_294() : OperationMutation<Opcode::LHU, LHU_294>("LHU_294") {}
    void apply(ISS &core) {
        {
            uint32_t addr = core.read_reg(core.rs1()) + core.I_imm();
            core.trap_check_addr_alignment<2, true>(addr);
            addr = core.maybe_mutate_load_addr(addr);
            auto val = core.mem->load_uhalf(addr);
            core.write_reg(core.rs2(), core.maybe_mutate_load_value(addr, val));
        }
    }
};
/* load_uhalf -> load_byte */
struct LHU_295 : OperationMutation<Opcode::LHU, LHU_295> {
    LHU_295() : OperationMutation<Opcode::LHU, LHU_295>("LHU_295") {}
    void apply(ISS &core) {
        {
            uint32_t addr = core.read_reg(core.rs1()) + core.I_imm();
            core.trap_check_addr_alignment<2, true>(addr);
            addr = core.maybe_mutate_load_addr(addr);
            auto val = core.mem->load_byte(addr);
            core.write_reg(core.rd(), core.maybe_mutate_load_value(addr, val));
        }
    }
};
/* load_uhalf -> load_half */
struct LHU_296 : OperationMutation<Opcode::LHU, LHU_296> {
    LHU_296() : OperationMutation<Opcode::LHU, LHU_296>("LHU_296") {}
    void apply(ISS &core) {
        {
            uint32_t addr = core.read_reg(core.rs1()) + core.I_imm();
            core.trap_check_addr_alignment<2, true>(addr);
            addr = core.maybe_mutate_load_addr(addr);
            auto val = core.mem->load_half(addr);
            core.write_reg(core.rd(), core.maybe_mutate_load_value(addr, val));
        }
    }
};
/* load_uhalf -> load_ubyte */
struct LHU_297 : OperationMutation<Opcode::LHU, LHU_297> {
    LHU_297() : OperationMutation<Opcode::LHU, LHU_297>("LHU_297") {}
    void apply(ISS &core) {
        {
            uint32_t addr = core.read_reg(core.rs1()) + core.I_imm();
            core.trap_check_addr_alignment<2, true>(addr);
            addr = core.maybe_mutate_load_addr(addr);
            auto val = core.mem->load_ubyte(addr);
            core.write_reg(core.rd(), core.maybe_mutate_load_value(addr, val));
        }
    }
};
/* load_uhalf -> load_word */
struct LHU_298 : OperationMutation<Opcode::LHU, LHU_298> {
    LHU_298() : OperationMutation<Opcode::LHU, LHU_298>("LHU_298") {}
    void apply(ISS &core) {
        {
            uint32_t addr = core.read_reg(core.rs1()) + core.I_imm();
            core.trap_check_addr_alignment<2, true>(addr);
            addr = core.maybe_mutate_load_addr(addr);
            auto val = core.mem->load_word(addr);
            core.write_reg(core.rd(), core.maybe_mutate_load_value(addr, val));
        }
    }
};
/*  +  ->  -  */
struct BEQ_299 : OperationMutation<Opcode::BEQ, BEQ_299> {
    BEQ_299() : OperationMutation<Opcode::BEQ, BEQ_299>("BEQ_299") {}
    void apply(ISS &core) {
        if (core.read_reg(core.rs1()) == core.read_reg(core.rs2())) {
            core.pc = core.last_pc - core.B_imm();
            core.trap_check_pc_alignment();
        }
    }
};
/*  ==  ->  >  */
struct BEQ_300 : OperationMutation<Opcode::BEQ, BEQ_300> {
    BEQ_300() : OperationMutation<Opcode::BEQ, BEQ_300>("BEQ_300") {}
    void apply(ISS &core) {
        if (core.read_reg(core.rs1()) > core.read_reg(core.rs2())) {
            core.pc = core.last_pc + core.B_imm();
            core.trap_check_pc_alignment();
        }
    }
};
/*  ==  ->  <  */
struct BEQ_301 : OperationMutation<Opcode::BEQ, BEQ_301> {
    BEQ_301() : OperationMutation<Opcode::BEQ, BEQ_301>("BEQ_301") {}
    void apply(ISS &core) {
        if (core.read_reg(core.rs1()) < core.read_reg(core.rs2())) {
            core.pc = core.last_pc + core.B_imm();
            core.trap_check_pc_alignment();
        }
    }
};
/*  ==  ->  <=  */
struct BEQ_302 : OperationMutation<Opcode::BEQ, BEQ_302> {
    BEQ_302() : OperationMutation<Opcode::BEQ, BEQ_302>("BEQ_302") {}
    void apply(ISS &core) {
        if (core.read_reg(core.rs1()) <= core.read_reg(core.rs2())) {
            core.pc = core.last_pc + core.B_imm();
            core.trap_check_pc_alignment();
        }
    }
};
/*  ==  ->  !=  */
struct BEQ_303 : OperationMutation<Opcode::BEQ, BEQ_303> {
    BEQ_303() : OperationMutation<Opcode::BEQ, BEQ_303>("BEQ_303") {}
    void apply(ISS &core) {
        if (core.read_reg(core.rs1()) != core.read_reg(core.rs2())) {
            core.pc = core.last_pc + core.B_imm();
            core.trap_check_pc_alignment();
        }
    }
};
/*  ==  ->  >=  */
struct BEQ_304 : OperationMutation<Opcode::BEQ, BEQ_304> {
    BEQ_304() : OperationMutation<Opcode::BEQ, BEQ_304>("BEQ_304") {}
    void apply(ISS &core) {
        if (core.read_reg(core.rs1()) >= core.read_reg(core.rs2())) {
            core.pc = core.last_pc + core.B_imm();
            core.trap_check_pc_alignment();
        }
    }
};
/* B_imm() -> U_imm() */
struct BEQ_305 : OperationMutation<Opcode::BEQ, BEQ_305> {
    BEQ_305() : OperationMutation<Opcode::BEQ, BEQ_305>("BEQ_305") {}
    void apply(ISS &core) {
        if (core.read_reg(core.rs1()) == core.read_reg(core.rs2())) {
            core.pc = core.last_pc + core.U_imm();
            core.trap_check_pc_alignment();
        }
    }
};
/* B_imm() -> I_imm() */
struct BEQ_306 : OperationMutation<Opcode::BEQ, BEQ_306> {
    BEQ_306() : OperationMutation<Opcode::BEQ, BEQ_306>("BEQ_306") {}
    void apply(ISS &core) {
        if (core.read_reg(core.rs1()) == core.read_reg(core.rs2())) {
            core.pc = core.last_pc + core.I_imm();
            core.trap_check_pc_alignment();
        }
    }
};
/* B_imm() -> J_imm() */
struct BEQ_307 : OperationMutation<Opcode::BEQ, BEQ_307> {
    BEQ_307() : OperationMutation<Opcode::BEQ, BEQ_307>("BEQ_307") {}
    void apply(ISS &core) {
        if (core.read_reg(core.rs1()) == core.read_reg(core.rs2())) {
            core.pc = core.last_pc + core.J_imm();
            core.trap_check_pc_alignment();
        }
    }
};
/* B_imm() -> S_imm() */
struct BEQ_308 : OperationMutation<Opcode::BEQ, BEQ_308> {
    BEQ_308() : OperationMutation<Opcode::BEQ, BEQ_308>("BEQ_308") {}
    void apply(ISS &core) {
        if (core.read_reg(core.rs1()) == core.read_reg(core.rs2())) {
            core.pc = core.last_pc + core.S_imm();
            core.trap_check_pc_alignment();
        }
    }
};
/* rs1() -> rd() */
struct BEQ_309 : OperationMutation<Opcode::BEQ, BEQ_309> {
    BEQ_309() : OperationMutation<Opcode::BEQ, BEQ_309>("BEQ_309") {}
    void apply(ISS &core) {
        if (core.read_reg(core.rd()) == core.read_reg(core.rs2())) {
            core.pc = core.last_pc + core.B_imm();
            core.trap_check_pc_alignment();
        }
    }
};
/* rs1() -> rs2() */
struct BEQ_310 : OperationMutation<Opcode::BEQ, BEQ_310> {
    BEQ_310() : OperationMutation<Opcode::BEQ, BEQ_310>("BEQ_310") {}
    void apply(ISS &core) {
        if (core.read_reg(core.rs2()) == core.read_reg(core.rs2())) {
            core.pc = core.last_pc + core.B_imm();
            core.trap_check_pc_alignment();
        }
    }
};
/* rs2() -> rs1() */
struct BEQ_311 : OperationMutation<Opcode::BEQ, BEQ_311> {
    BEQ_311() : OperationMutation<Opcode::BEQ, BEQ_311>("BEQ_311") {}
    void apply(ISS &core) {
        if (core.read_reg(core.rs1()) == core.read_reg(core.rs1())) {
            core.pc = core.last_pc + core.B_imm();
            core.trap_check_pc_alignment();
        }
    }
};
/* rs2() -> rd() */
struct BEQ_312 : OperationMutation<Opcode::BEQ, BEQ_312> {
    BEQ_312() : OperationMutation<Opcode::BEQ, BEQ_312>("BEQ_312") {}
    void apply(ISS &core) {
        if (core.read_reg(core.rs1()) == core.read_reg(core.rd())) {
            core.pc = core.last_pc + core.B_imm();
            core.trap_check_pc_alignment();
        }
    }
};
/*  last_pc ->  pc */
struct BEQ_313 : OperationMutation<Opcode::BEQ, BEQ_313> {
    BEQ_313() : OperationMutation<Opcode::BEQ, BEQ_313>("BEQ_313") {}
    void apply(ISS &core) {
        if (core.read_reg(core.rs1()) == core.read_reg(core.rs2())) {
            core.pc = core.pc + core.B_imm();
            core.trap_check_pc_alignment();
        }
    }
};
/*  +  ->  -  */
struct BNE_314 : OperationMutation<Opcode::BNE, BNE_314> {
    BNE_314() : OperationMutation<Opcode::BNE, BNE_314>("BNE_314") {}
    void apply(ISS &core) {
        if (core.read_reg(core.rs1()) != core.read_reg(core.rs2())) {
            core.pc = core.last_pc - core.B_imm();
            core.trap_check_pc_alignment();
        }
    }
};
/*  !=  ->  ==  */
struct BNE_315 : OperationMutation<Opcode::BNE, BNE_315> {
    BNE_315() : OperationMutation<Opcode::BNE, BNE_315>("BNE_315") {}
    void apply(ISS &core) {
        if (core.read_reg(core.rs1()) == core.read_reg(core.rs2())) {
            core.pc = core.last_pc + core.B_imm();
            core.trap_check_pc_alignment();
        }
    }
};
/*  !=  ->  >  */
struct BNE_316 : OperationMutation<Opcode::BNE, BNE_316> {
    BNE_316() : OperationMutation<Opcode::BNE, BNE_316>("BNE_316") {}
    void apply(ISS &core) {
        if (core.read_reg(core.rs1()) > core.read_reg(core.rs2())) {
            core.pc = core.last_pc + core.B_imm();
            core.trap_check_pc_alignment();
        }
    }
};
/*  !=  ->  <  */
struct BNE_317 : OperationMutation<Opcode::BNE, BNE_317> {
    BNE_317() : OperationMutation<Opcode::BNE, BNE_317>("BNE_317") {}
    void apply(ISS &core) {
        if (core.read_reg(core.rs1()) < core.read_reg(core.rs2())) {
            core.pc = core.last_pc + core.B_imm();
            core.trap_check_pc_alignment();
        }
    }
};
/*  !=  ->  <=  */
struct BNE_318 : OperationMutation<Opcode::BNE, BNE_318> {
    BNE_318() : OperationMutation<Opcode::BNE, BNE_318>("BNE_318") {}
    void apply(ISS &core) {
        if (core.read_reg(core.rs1()) <= core.read_reg(core.rs2())) {
            core.pc = core.last_pc + core.B_imm();
            core.trap_check_pc_alignment();
        }
    }
};
/*  !=  ->  >=  */
struct BNE_319 : OperationMutation<Opcode::BNE, BNE_319> {
    BNE_319() : OperationMutation<Opcode::BNE, BNE_319>("BNE_319") {}
    void apply(ISS &core) {
        if (core.read_reg(core.rs1()) >= core.read_reg(core.rs2())) {
            core.pc = core.last_pc + core.B_imm();
            core.trap_check_pc_alignment();
        }
    }
};
/* B_imm() -> U_imm() */
struct BNE_320 : OperationMutation<Opcode::BNE, BNE_320> {
    BNE_320() : OperationMutation<Opcode::BNE, BNE_320>("BNE_320") {}
    void apply(ISS &core) {
        if (core.read_reg(core.rs1()) != core.read_reg(core.rs2())) {
            core.pc = core.last_pc + core.U_imm();
            core.trap_check_pc_alignment();
        }
    }
};
/* B_imm() -> I_imm() */
struct BNE_321 : OperationMutation<Opcode::BNE, BNE_321> {
    BNE_321() : OperationMutation<Opcode::BNE, BNE_321>("BNE_321") {}
    void apply(ISS &core) {
        if (core.read_reg(core.rs1()) != core.read_reg(core.rs2())) {
            core.pc = core.last_pc + core.I_imm();
            core.trap_check_pc_alignment();
        }
    }
};
/* B_imm() -> J_imm() */
struct BNE_322 : OperationMutation<Opcode::BNE, BNE_322> {
    BNE_322() : OperationMutation<Opcode::BNE, BNE_322>("BNE_322") {}
    void apply(ISS &core) {
        if (core.read_reg(core.rs1()) != core.read_reg(core.rs2())) {
            core.pc = core.last_pc + core.J_imm();
            core.trap_check_pc_alignment();
        }
    }
};
/* B_imm() -> S_imm() */
struct BNE_323 : OperationMutation<Opcode::BNE, BNE_323> {
    BNE_323() : OperationMutation<Opcode::BNE, BNE_323>("BNE_323") {}
    void apply(ISS &core) {
        if (core.read_reg(core.rs1()) != core.read_reg(core.rs2())) {
            core.pc = core.last_pc + core.S_imm();
            core.trap_check_pc_alignment();
        }
    }
};
/* rs1() -> rd() */
struct BNE_324 : OperationMutation<Opcode::BNE, BNE_324> {
    BNE_324() : OperationMutation<Opcode::BNE, BNE_324>("BNE_324") {}
    void apply(ISS &core) {
        if (core.read_reg(core.rd()) != core.read_reg(core.rs2())) {
            core.pc = core.last_pc + core.B_imm();
            core.trap_check_pc_alignment();
        }
    }
};
/* rs1() -> rs2() */
struct BNE_325 : OperationMutation<Opcode::BNE, BNE_325> {
    BNE_325() : OperationMutation<Opcode::BNE, BNE_325>("BNE_325") {}
    void apply(ISS &core) {
        if (core.read_reg(core.rs2()) != core.read_reg(core.rs2())) {
            core.pc = core.last_pc + core.B_imm();
            core.trap_check_pc_alignment();
        }
    }
};
/* rs2() -> rs1() */
struct BNE_326 : OperationMutation<Opcode::BNE, BNE_326> {
    BNE_326() : OperationMutation<Opcode::BNE, BNE_326>("BNE_326") {}
    void apply(ISS &core) {
        if (core.read_reg(core.rs1()) != core.read_reg(core.rs1())) {
            core.pc = core.last_pc + core.B_imm();
            core.trap_check_pc_alignment();
        }
    }
};
/* rs2() -> rd() */
struct BNE_327 : OperationMutation<Opcode::BNE, BNE_327> {
    BNE_327() : OperationMutation<Opcode::BNE, BNE_327>("BNE_327") {}
    void apply(ISS &core) {
        if (core.read_reg(core.rs1()) != core.read_reg(core.rd())) {
            core.pc = core.last_pc + core.B_imm();
            core.trap_check_pc_alignment();
        }
    }
};
/*  last_pc ->  pc */
struct BNE_328 : OperationMutation<Opcode::BNE, BNE_328> {
    BNE_328() : OperationMutation<Opcode::BNE, BNE_328>("BNE_328") {}
    void apply(ISS &core) {
        if (core.read_reg(core.rs1()) != core.read_reg(core.rs2())) {
            core.pc = core.pc + core.B_imm();
            core.trap_check_pc_alignment();
        }
    }
};
/*  +  ->  -  */
struct BLT_329 : OperationMutation<Opcode::BLT, BLT_329> {
    BLT_329() : OperationMutation<Opcode::BLT, BLT_329>("BLT_329") {}
    void apply(ISS &core) {
        if (core.read_reg(core.rs1()) < core.read_reg(core.rs2())) {
            core.pc = core.last_pc - core.B_imm();
            core.trap_check_pc_alignment();
        }
    }
};
/*  <  ->  ==  */
struct BLT_330 : OperationMutation<Opcode::BLT, BLT_330> {
    BLT_330() : OperationMutation<Opcode::BLT, BLT_330>("BLT_330") {}
    void apply(ISS &core) {
        if (core.read_reg(core.rs1()) == core.read_reg(core.rs2())) {
            core.pc = core.last_pc + core.B_imm();
            core.trap_check_pc_alignment();
        }
    }
};
/*  <  ->  >  */
struct BLT_331 : OperationMutation<Opcode::BLT, BLT_331> {
    BLT_331() : OperationMutation<Opcode::BLT, BLT_331>("BLT_331") {}
    void apply(ISS &core) {
        if (core.read_reg(core.rs1()) > core.read_reg(core.rs2())) {
            core.pc = core.last_pc + core.B_imm();
            core.trap_check_pc_alignment();
        }
    }
};
/*  <  ->  <=  */
struct BLT_332 : OperationMutation<Opcode::BLT, BLT_332> {
    BLT_332() : OperationMutation<Opcode::BLT, BLT_332>("BLT_332") {}
    void apply(ISS &core) {
        if (core.read_reg(core.rs1()) <= core.read_reg(core.rs2())) {
            core.pc = core.last_pc + core.B_imm();
            core.trap_check_pc_alignment();
        }
    }
};
/*  <  ->  !=  */
struct BLT_333 : OperationMutation<Opcode::BLT, BLT_333> {
    BLT_333() : OperationMutation<Opcode::BLT, BLT_333>("BLT_333") {}
    void apply(ISS &core) {
        if (core.read_reg(core.rs1()) != core.read_reg(core.rs2())) {
            core.pc = core.last_pc + core.B_imm();
            core.trap_check_pc_alignment();
        }
    }
};
/*  <  ->  >=  */
struct BLT_334 : OperationMutation<Opcode::BLT, BLT_334> {
    BLT_334() : OperationMutation<Opcode::BLT, BLT_334>("BLT_334") {}
    void apply(ISS &core) {
        if (core.read_reg(core.rs1()) >= core.read_reg(core.rs2())) {
            core.pc = core.last_pc + core.B_imm();
            core.trap_check_pc_alignment();
        }
    }
};
/* B_imm() -> U_imm() */
struct BLT_335 : OperationMutation<Opcode::BLT, BLT_335> {
    BLT_335() : OperationMutation<Opcode::BLT, BLT_335>("BLT_335") {}
    void apply(ISS &core) {
        if (core.read_reg(core.rs1()) < core.read_reg(core.rs2())) {
            core.pc = core.last_pc + core.U_imm();
            core.trap_check_pc_alignment();
        }
    }
};
/* B_imm() -> I_imm() */
struct BLT_336 : OperationMutation<Opcode::BLT, BLT_336> {
    BLT_336() : OperationMutation<Opcode::BLT, BLT_336>("BLT_336") {}
    void apply(ISS &core) {
        if (core.read_reg(core.rs1()) < core.read_reg(core.rs2())) {
            core.pc = core.last_pc + core.I_imm();
            core.trap_check_pc_alignment();
        }
    }
};
/* B_imm() -> J_imm() */
struct BLT_337 : OperationMutation<Opcode::BLT, BLT_337> {
    BLT_337() : OperationMutation<Opcode::BLT, BLT_337>("BLT_337") {}
    void apply(ISS &core) {
        if (core.read_reg(core.rs1()) < core.read_reg(core.rs2())) {
            core.pc = core.last_pc + core.J_imm();
            core.trap_check_pc_alignment();
        }
    }
};
/* B_imm() -> S_imm() */
struct BLT_338 : OperationMutation<Opcode::BLT, BLT_338> {
    BLT_338() : OperationMutation<Opcode::BLT, BLT_338>("BLT_338") {}
    void apply(ISS &core) {
        if (core.read_reg(core.rs1()) < core.read_reg(core.rs2())) {
            core.pc = core.last_pc + core.S_imm();
            core.trap_check_pc_alignment();
        }
    }
};
/* rs1() -> rd() */
struct BLT_339 : OperationMutation<Opcode::BLT, BLT_339> {
    BLT_339() : OperationMutation<Opcode::BLT, BLT_339>("BLT_339") {}
    void apply(ISS &core) {
        if (core.read_reg(core.rd()) < core.read_reg(core.rs2())) {
            core.pc = core.last_pc + core.B_imm();
            core.trap_check_pc_alignment();
        }
    }
};
/* rs1() -> rs2() */
struct BLT_340 : OperationMutation<Opcode::BLT, BLT_340> {
    BLT_340() : OperationMutation<Opcode::BLT, BLT_340>("BLT_340") {}
    void apply(ISS &core) {
        if (core.read_reg(core.rs2()) < core.read_reg(core.rs2())) {
            core.pc = core.last_pc + core.B_imm();
            core.trap_check_pc_alignment();
        }
    }
};
/* rs2() -> rs1() */
struct BLT_341 : OperationMutation<Opcode::BLT, BLT_341> {
    BLT_341() : OperationMutation<Opcode::BLT, BLT_341>("BLT_341") {}
    void apply(ISS &core) {
        if (core.read_reg(core.rs1()) < core.read_reg(core.rs1())) {
            core.pc = core.last_pc + core.B_imm();
            core.trap_check_pc_alignment();
        }
    }
};
/* rs2() -> rd() */
struct BLT_342 : OperationMutation<Opcode::BLT, BLT_342> {
    BLT_342() : OperationMutation<Opcode::BLT, BLT_342>("BLT_342") {}
    void apply(ISS &core) {
        if (core.read_reg(core.rs1()) < core.read_reg(core.rd())) {
            core.pc = core.last_pc + core.B_imm();
            core.trap_check_pc_alignment();
        }
    }
};
/*  last_pc ->  pc */
struct BLT_343 : OperationMutation<Opcode::BLT, BLT_343> {
    BLT_343() : OperationMutation<Opcode::BLT, BLT_343>("BLT_343") {}
    void apply(ISS &core) {
        if (core.read_reg(core.rs1()) < core.read_reg(core.rs2())) {
            core.pc = core.pc + core.B_imm();
            core.trap_check_pc_alignment();
        }
    }
};
/*  +  ->  -  */
struct BGE_344 : OperationMutation<Opcode::BGE, BGE_344> {
    BGE_344() : OperationMutation<Opcode::BGE, BGE_344>("BGE_344") {}
    void apply(ISS &core) {
        if (core.read_reg(core.rs1()) >= core.read_reg(core.rs2())) {
            core.pc = core.last_pc - core.B_imm();
            core.trap_check_pc_alignment();
        }
    }
};
/*  >=  ->  ==  */
struct BGE_345 : OperationMutation<Opcode::BGE, BGE_345> {
    BGE_345() : OperationMutation<Opcode::BGE, BGE_345>("BGE_345") {}
    void apply(ISS &core) {
        if (core.read_reg(core.rs1()) == core.read_reg(core.rs2())) {
            core.pc = core.last_pc + core.B_imm();
            core.trap_check_pc_alignment();
        }
    }
};
/*  >=  ->  >  */
struct BGE_346 : OperationMutation<Opcode::BGE, BGE_346> {
    BGE_346() : OperationMutation<Opcode::BGE, BGE_346>("BGE_346") {}
    void apply(ISS &core) {
        if (core.read_reg(core.rs1()) > core.read_reg(core.rs2())) {
            core.pc = core.last_pc + core.B_imm();
            core.trap_check_pc_alignment();
        }
    }
};
/*  >=  ->  <  */
struct BGE_347 : OperationMutation<Opcode::BGE, BGE_347> {
    BGE_347() : OperationMutation<Opcode::BGE, BGE_347>("BGE_347") {}
    void apply(ISS &core) {
        if (core.read_reg(core.rs1()) < core.read_reg(core.rs2())) {
            core.pc = core.last_pc + core.B_imm();
            core.trap_check_pc_alignment();
        }
    }
};
/*  >=  ->  <=  */
struct BGE_348 : OperationMutation<Opcode::BGE, BGE_348> {
    BGE_348() : OperationMutation<Opcode::BGE, BGE_348>("BGE_348") {}
    void apply(ISS &core) {
        if (core.read_reg(core.rs1()) <= core.read_reg(core.rs2())) {
            core.pc = core.last_pc + core.B_imm();
            core.trap_check_pc_alignment();
        }
    }
};
/*  >=  ->  !=  */
struct BGE_349 : OperationMutation<Opcode::BGE, BGE_349> {
    BGE_349() : OperationMutation<Opcode::BGE, BGE_349>("BGE_349") {}
    void apply(ISS &core) {
        if (core.read_reg(core.rs1()) != core.read_reg(core.rs2())) {
            core.pc = core.last_pc + core.B_imm();
            core.trap_check_pc_alignment();
        }
    }
};
/* B_imm() -> U_imm() */
struct BGE_350 : OperationMutation<Opcode::BGE, BGE_350> {
    BGE_350() : OperationMutation<Opcode::BGE, BGE_350>("BGE_350") {}
    void apply(ISS &core) {
        if (core.read_reg(core.rs1()) >= core.read_reg(core.rs2())) {
            core.pc = core.last_pc + core.U_imm();
            core.trap_check_pc_alignment();
        }
    }
};
/* B_imm() -> I_imm() */
struct BGE_351 : OperationMutation<Opcode::BGE, BGE_351> {
    BGE_351() : OperationMutation<Opcode::BGE, BGE_351>("BGE_351") {}
    void apply(ISS &core) {
        if (core.read_reg(core.rs1()) >= core.read_reg(core.rs2())) {
            core.pc = core.last_pc + core.I_imm();
            core.trap_check_pc_alignment();
        }
    }
};
/* B_imm() -> J_imm() */
struct BGE_352 : OperationMutation<Opcode::BGE, BGE_352> {
    BGE_352() : OperationMutation<Opcode::BGE, BGE_352>("BGE_352") {}
    void apply(ISS &core) {
        if (core.read_reg(core.rs1()) >= core.read_reg(core.rs2())) {
            core.pc = core.last_pc + core.J_imm();
            core.trap_check_pc_alignment();
        }
    }
};
/* B_imm() -> S_imm() */
struct BGE_353 : OperationMutation<Opcode::BGE, BGE_353> {
    BGE_353() : OperationMutation<Opcode::BGE, BGE_353>("BGE_353") {}
    void apply(ISS &core) {
        if (core.read_reg(core.rs1()) >= core.read_reg(core.rs2())) {
            core.pc = core.last_pc + core.S_imm();
            core.trap_check_pc_alignment();
        }
    }
};
/* rs1() -> rd() */
struct BGE_354 : OperationMutation<Opcode::BGE, BGE_354> {
    BGE_354() : OperationMutation<Opcode::BGE, BGE_354>("BGE_354") {}
    void apply(ISS &core) {
        if (core.read_reg(core.rd()) >= core.read_reg(core.rs2())) {
            core.pc = core.last_pc + core.B_imm();
            core.trap_check_pc_alignment();
        }
    }
};
/* rs1() -> rs2() */
struct BGE_355 : OperationMutation<Opcode::BGE, BGE_355> {
    BGE_355() : OperationMutation<Opcode::BGE, BGE_355>("BGE_355") {}
    void apply(ISS &core) {
        if (core.read_reg(core.rs2()) >= core.read_reg(core.rs2())) {
            core.pc = core.last_pc + core.B_imm();
            core.trap_check_pc_alignment();
        }
    }
};
/* rs2() -> rs1() */
struct BGE_356 : OperationMutation<Opcode::BGE, BGE_356> {
    BGE_356() : OperationMutation<Opcode::BGE, BGE_356>("BGE_356") {}
    void apply(ISS &core) {
        if (core.read_reg(core.rs1()) >= core.read_reg(core.rs1())) {
            core.pc = core.last_pc + core.B_imm();
            core.trap_check_pc_alignment();
        }
    }
};
/* rs2() -> rd() */
struct BGE_357 : OperationMutation<Opcode::BGE, BGE_357> {
    BGE_357() : OperationMutation<Opcode::BGE, BGE_357>("BGE_357") {}
    void apply(ISS &core) {
        if (core.read_reg(core.rs1()) >= core.read_reg(core.rd())) {
            core.pc = core.last_pc + core.B_imm();
            core.trap_check_pc_alignment();
        }
    }
};
/*  last_pc ->  pc */
struct BGE_358 : OperationMutation<Opcode::BGE, BGE_358> {
    BGE_358() : OperationMutation<Opcode::BGE, BGE_358>("BGE_358") {}
    void apply(ISS &core) {
        if (core.read_reg(core.rs1()) >= core.read_reg(core.rs2())) {
            core.pc = core.pc + core.B_imm();
            core.trap_check_pc_alignment();
        }
    }
};
/*  +  ->  -  */
struct BLTU_359 : OperationMutation<Opcode::BLTU, BLTU_359> {
    BLTU_359() : OperationMutation<Opcode::BLTU, BLTU_359>("BLTU_359") {}
    void apply(ISS &core) {
        if ((uint32_t)core.read_reg(core.rs1()) < (uint32_t)core.read_reg(core.rs2())) {
            core.pc = core.last_pc - core.B_imm();
            core.trap_check_pc_alignment();
        }
    }
};
/*  <  ->  ==  */
struct BLTU_360 : OperationMutation<Opcode::BLTU, BLTU_360> {
    BLTU_360() : OperationMutation<Opcode::BLTU, BLTU_360>("BLTU_360") {}
    void apply(ISS &core) {
        if ((uint32_t)core.read_reg(core.rs1()) == (uint32_t)core.read_reg(core.rs2())) {
            core.pc = core.last_pc + core.B_imm();
            core.trap_check_pc_alignment();
        }
    }
};
/*  <  ->  >  */
struct BLTU_361 : OperationMutation<Opcode::BLTU, BLTU_361> {
    BLTU_361() : OperationMutation<Opcode::BLTU, BLTU_361>("BLTU_361") {}
    void apply(ISS &core) {
        if ((uint32_t)core.read_reg(core.rs1()) > (uint32_t)core.read_reg(core.rs2())) {
            core.pc = core.last_pc + core.B_imm();
            core.trap_check_pc_alignment();
        }
    }
};
/*  <  ->  <=  */
struct BLTU_362 : OperationMutation<Opcode::BLTU, BLTU_362> {
    BLTU_362() : OperationMutation<Opcode::BLTU, BLTU_362>("BLTU_362") {}
    void apply(ISS &core) {
        if ((uint32_t)core.read_reg(core.rs1()) <= (uint32_t)core.read_reg(core.rs2())) {
            core.pc = core.last_pc + core.B_imm();
            core.trap_check_pc_alignment();
        }
    }
};
/*  <  ->  !=  */
struct BLTU_363 : OperationMutation<Opcode::BLTU, BLTU_363> {
    BLTU_363() : OperationMutation<Opcode::BLTU, BLTU_363>("BLTU_363") {}
    void apply(ISS &core) {
        if ((uint32_t)core.read_reg(core.rs1()) != (uint32_t)core.read_reg(core.rs2())) {
            core.pc = core.last_pc + core.B_imm();
            core.trap_check_pc_alignment();
        }
    }
};
/*  <  ->  >=  */
struct BLTU_364 : OperationMutation<Opcode::BLTU, BLTU_364> {
    BLTU_364() : OperationMutation<Opcode::BLTU, BLTU_364>("BLTU_364") {}
    void apply(ISS &core) {
        if ((uint32_t)core.read_reg(core.rs1()) >= (uint32_t)core.read_reg(core.rs2())) {
            core.pc = core.last_pc + core.B_imm();
            core.trap_check_pc_alignment();
        }
    }
};
/* B_imm() -> U_imm() */
struct BLTU_365 : OperationMutation<Opcode::BLTU, BLTU_365> {
    BLTU_365() : OperationMutation<Opcode::BLTU, BLTU_365>("BLTU_365") {}
    void apply(ISS &core) {
        if ((uint32_t)core.read_reg(core.rs1()) < (uint32_t)core.read_reg(core.rs2())) {
            core.pc = core.last_pc + core.U_imm();
            core.trap_check_pc_alignment();
        }
    }
};
/* B_imm() -> I_imm() */
struct BLTU_366 : OperationMutation<Opcode::BLTU, BLTU_366> {
    BLTU_366() : OperationMutation<Opcode::BLTU, BLTU_366>("BLTU_366") {}
    void apply(ISS &core) {
        if ((uint32_t)core.read_reg(core.rs1()) < (uint32_t)core.read_reg(core.rs2())) {
            core.pc = core.last_pc + core.I_imm();
            core.trap_check_pc_alignment();
        }
    }
};
/* B_imm() -> J_imm() */
struct BLTU_367 : OperationMutation<Opcode::BLTU, BLTU_367> {
    BLTU_367() : OperationMutation<Opcode::BLTU, BLTU_367>("BLTU_367") {}
    void apply(ISS &core) {
        if ((uint32_t)core.read_reg(core.rs1()) < (uint32_t)core.read_reg(core.rs2())) {
            core.pc = core.last_pc + core.J_imm();
            core.trap_check_pc_alignment();
        }
    }
};
/* B_imm() -> S_imm() */
struct BLTU_368 : OperationMutation<Opcode::BLTU, BLTU_368> {
    BLTU_368() : OperationMutation<Opcode::BLTU, BLTU_368>("BLTU_368") {}
    void apply(ISS &core) {
        if ((uint32_t)core.read_reg(core.rs1()) < (uint32_t)core.read_reg(core.rs2())) {
            core.pc = core.last_pc + core.S_imm();
            core.trap_check_pc_alignment();
        }
    }
};
/* rs1() -> rd() */
struct BLTU_369 : OperationMutation<Opcode::BLTU, BLTU_369> {
    BLTU_369() : OperationMutation<Opcode::BLTU, BLTU_369>("BLTU_369") {}
    void apply(ISS &core) {
        if ((uint32_t)core.read_reg(core.rd()) < (uint32_t)core.read_reg(core.rs2())) {
            core.pc = core.last_pc + core.B_imm();
            core.trap_check_pc_alignment();
        }
    }
};
/* rs1() -> rs2() */
struct BLTU_370 : OperationMutation<Opcode::BLTU, BLTU_370> {
    BLTU_370() : OperationMutation<Opcode::BLTU, BLTU_370>("BLTU_370") {}
    void apply(ISS &core) {
        if ((uint32_t)core.read_reg(core.rs2()) < (uint32_t)core.read_reg(core.rs2())) {
            core.pc = core.last_pc + core.B_imm();
            core.trap_check_pc_alignment();
        }
    }
};
/* rs2() -> rs1() */
struct BLTU_371 : OperationMutation<Opcode::BLTU, BLTU_371> {
    BLTU_371() : OperationMutation<Opcode::BLTU, BLTU_371>("BLTU_371") {}
    void apply(ISS &core) {
        if ((uint32_t)core.read_reg(core.rs1()) < (uint32_t)core.read_reg(core.rs1())) {
            core.pc = core.last_pc + core.B_imm();
            core.trap_check_pc_alignment();
        }
    }
};
/* rs2() -> rd() */
struct BLTU_372 : OperationMutation<Opcode::BLTU, BLTU_372> {
    BLTU_372() : OperationMutation<Opcode::BLTU, BLTU_372>("BLTU_372") {}
    void apply(ISS &core) {
        if ((uint32_t)core.read_reg(core.rs1()) < (uint32_t)core.read_reg(core.rd())) {
            core.pc = core.last_pc + core.B_imm();
            core.trap_check_pc_alignment();
        }
    }
};
/*  last_pc ->  pc */
struct BLTU_373 : OperationMutation<Opcode::BLTU, BLTU_373> {
    BLTU_373() : OperationMutation<Opcode::BLTU, BLTU_373>("BLTU_373") {}
    void apply(ISS &core) {
        if ((uint32_t)core.read_reg(core.rs1()) < (uint32_t)core.read_reg(core.rs2())) {
            core.pc = core.pc + core.B_imm();
            core.trap_check_pc_alignment();
        }
    }
};
/* (uint32_t) -> (int32_t) */
struct BLTU_374 : OperationMutation<Opcode::BLTU, BLTU_374> {
    BLTU_374() : OperationMutation<Opcode::BLTU, BLTU_374>("BLTU_374") {}
    void apply(ISS &core) {
        if ((int32_t)core.read_reg(core.rs1()) < (int32_t)core.read_reg(core.rs2())) {
            core.pc = core.last_pc + core.B_imm();
            core.trap_check_pc_alignment();
        }
    }
};
/*  +  ->  -  */
struct BGEU_375 : OperationMutation<Opcode::BGEU, BGEU_375> {
    BGEU_375() : OperationMutation<Opcode::BGEU, BGEU_375>("BGEU_375") {}
    void apply(ISS &core) {
        if ((uint32_t)core.read_reg(core.rs1()) >= (uint32_t)core.read_reg(core.rs2())) {
            core.pc = core.last_pc - core.B_imm();
            core.trap_check_pc_alignment();
        }
    }
};
/*  >=  ->  ==  */
struct BGEU_376 : OperationMutation<Opcode::BGEU, BGEU_376> {
    BGEU_376() : OperationMutation<Opcode::BGEU, BGEU_376>("BGEU_376") {}
    void apply(ISS &core) {
        if ((uint32_t)core.read_reg(core.rs1()) == (uint32_t)core.read_reg(core.rs2())) {
            core.pc = core.last_pc + core.B_imm();
            core.trap_check_pc_alignment();
        }
    }
};
/*  >=  ->  >  */
struct BGEU_377 : OperationMutation<Opcode::BGEU, BGEU_377> {
    BGEU_377() : OperationMutation<Opcode::BGEU, BGEU_377>("BGEU_377") {}
    void apply(ISS &core) {
        if ((uint32_t)core.read_reg(core.rs1()) > (uint32_t)core.read_reg(core.rs2())) {
            core.pc = core.last_pc + core.B_imm();
            core.trap_check_pc_alignment();
        }
    }
};
/*  >=  ->  <  */
struct BGEU_378 : OperationMutation<Opcode::BGEU, BGEU_378> {
    BGEU_378() : OperationMutation<Opcode::BGEU, BGEU_378>("BGEU_378") {}
    void apply(ISS &core) {
        if ((uint32_t)core.read_reg(core.rs1()) < (uint32_t)core.read_reg(core.rs2())) {
            core.pc = core.last_pc + core.B_imm();
            core.trap_check_pc_alignment();
        }
    }
};
/*  >=  ->  <=  */
struct BGEU_379 : OperationMutation<Opcode::BGEU, BGEU_379> {
    BGEU_379() : OperationMutation<Opcode::BGEU, BGEU_379>("BGEU_379") {}
    void apply(ISS &core) {
        if ((uint32_t)core.read_reg(core.rs1()) <= (uint32_t)core.read_reg(core.rs2())) {
            core.pc = core.last_pc + core.B_imm();
            core.trap_check_pc_alignment();
        }
    }
};
/*  >=  ->  !=  */
struct BGEU_380 : OperationMutation<Opcode::BGEU, BGEU_380> {
    BGEU_380() : OperationMutation<Opcode::BGEU, BGEU_380>("BGEU_380") {}
    void apply(ISS &core) {
        if ((uint32_t)core.read_reg(core.rs1()) != (uint32_t)core.read_reg(core.rs2())) {
            core.pc = core.last_pc + core.B_imm();
            core.trap_check_pc_alignment();
        }
    }
};
/* B_imm() -> U_imm() */
struct BGEU_381 : OperationMutation<Opcode::BGEU, BGEU_381> {
    BGEU_381() : OperationMutation<Opcode::BGEU, BGEU_381>("BGEU_381") {}
    void apply(ISS &core) {
        if ((uint32_t)core.read_reg(core.rs1()) >= (uint32_t)core.read_reg(core.rs2())) {
            core.pc = core.last_pc + core.U_imm();
            core.trap_check_pc_alignment();
        }
    }
};
/* B_imm() -> I_imm() */
struct BGEU_382 : OperationMutation<Opcode::BGEU, BGEU_382> {
    BGEU_382() : OperationMutation<Opcode::BGEU, BGEU_382>("BGEU_382") {}
    void apply(ISS &core) {
        if ((uint32_t)core.read_reg(core.rs1()) >= (uint32_t)core.read_reg(core.rs2())) {
            core.pc = core.last_pc + core.I_imm();
            core.trap_check_pc_alignment();
        }
    }
};
/* B_imm() -> J_imm() */
struct BGEU_383 : OperationMutation<Opcode::BGEU, BGEU_383> {
    BGEU_383() : OperationMutation<Opcode::BGEU, BGEU_383>("BGEU_383") {}
    void apply(ISS &core) {
        if ((uint32_t)core.read_reg(core.rs1()) >= (uint32_t)core.read_reg(core.rs2())) {
            core.pc = core.last_pc + core.J_imm();
            core.trap_check_pc_alignment();
        }
    }
};
/* B_imm() -> S_imm() */
struct BGEU_384 : OperationMutation<Opcode::BGEU, BGEU_384> {
    BGEU_384() : OperationMutation<Opcode::BGEU, BGEU_384>("BGEU_384") {}
    void apply(ISS &core) {
        if ((uint32_t)core.read_reg(core.rs1()) >= (uint32_t)core.read_reg(core.rs2())) {
            core.pc = core.last_pc + core.S_imm();
            core.trap_check_pc_alignment();
        }
    }
};
/* rs1() -> rd() */
struct BGEU_385 : OperationMutation<Opcode::BGEU, BGEU_385> {
    BGEU_385() : OperationMutation<Opcode::BGEU, BGEU_385>("BGEU_385") {}
    void apply(ISS &core) {
        if ((uint32_t)core.read_reg(core.rd()) >= (uint32_t)core.read_reg(core.rs2())) {
            core.pc = core.last_pc + core.B_imm();
            core.trap_check_pc_alignment();
        }
    }
};
/* rs1() -> rs2() */
struct BGEU_386 : OperationMutation<Opcode::BGEU, BGEU_386> {
    BGEU_386() : OperationMutation<Opcode::BGEU, BGEU_386>("BGEU_386") {}
    void apply(ISS &core) {
        if ((uint32_t)core.read_reg(core.rs2()) >= (uint32_t)core.read_reg(core.rs2())) {
            core.pc = core.last_pc + core.B_imm();
            core.trap_check_pc_alignment();
        }
    }
};
/* rs2() -> rs1() */
struct BGEU_387 : OperationMutation<Opcode::BGEU, BGEU_387> {
    BGEU_387() : OperationMutation<Opcode::BGEU, BGEU_387>("BGEU_387") {}
    void apply(ISS &core) {
        if ((uint32_t)core.read_reg(core.rs1()) >= (uint32_t)core.read_reg(core.rs1())) {
            core.pc = core.last_pc + core.B_imm();
            core.trap_check_pc_alignment();
        }
    }
};
/* rs2() -> rd() */
struct BGEU_388 : OperationMutation<Opcode::BGEU, BGEU_388> {
    BGEU_388() : OperationMutation<Opcode::BGEU, BGEU_388>("BGEU_388") {}
    void apply(ISS &core) {
        if ((uint32_t)core.read_reg(core.rs1()) >= (uint32_t)core.read_reg(core.rd())) {
            core.pc = core.last_pc + core.B_imm();
            core.trap_check_pc_alignment();
        }
    }
};
/*  last_pc ->  pc */
struct BGEU_389 : OperationMutation<Opcode::BGEU, BGEU_389> {
    BGEU_389() : OperationMutation<Opcode::BGEU, BGEU_389>("BGEU_389") {}
    void apply(ISS &core) {
        if ((uint32_t)core.read_reg(core.rs1()) >= (uint32_t)core.read_reg(core.rs2())) {
            core.pc = core.pc + core.B_imm();
            core.trap_check_pc_alignment();
        }
    }
};
/* (uint32_t) -> (int32_t) */
struct BGEU_390 : OperationMutation<Opcode::BGEU, BGEU_390> {
    BGEU_390() : OperationMutation<Opcode::BGEU, BGEU_390>("BGEU_390") {}
    void apply(ISS &core) {
        if ((int32_t)core.read_reg(core.rs1()) >= (int32_t)core.read_reg(core.rs2())) {
            core.pc = core.last_pc + core.B_imm();
            core.trap_check_pc_alignment();
        }
    }
};

std::vector<std::shared_ptr<exec_mutator_if>> mutators{
    std::make_shared<EmptyMutation>(),
    std::make_shared<ADDI_2>(),
    std::make_shared<ADDI_3>(),
    std::make_shared<ADDI_4>(),
    std::make_shared<ADDI_5>(),
    std::make_shared<ADDI_6>(),
    std::make_shared<ADDI_7>(),
    std::make_shared<ADDI_8>(),
    std::make_shared<ADDI_9>(),
    std::make_shared<SLTI_10>(),
    std::make_shared<SLTI_11>(),
    std::make_shared<SLTI_12>(),
    std::make_shared<SLTI_13>(),
    std::make_shared<SLTI_14>(),
    std::make_shared<SLTI_15>(),
    std::make_shared<SLTI_16>(),
    std::make_shared<SLTI_17>(),
    std::make_shared<SLTI_18>(),
    std::make_shared<SLTI_19>(),
    std::make_shared<SLTI_20>(),
    std::make_shared<SLTI_21>(),
    std::make_shared<SLTI_22>(),
    std::make_shared<SLTIU_23>(),
    std::make_shared<SLTIU_24>(),
    std::make_shared<SLTIU_25>(),
    std::make_shared<SLTIU_26>(),
    std::make_shared<SLTIU_27>(),
    std::make_shared<SLTIU_28>(),
    std::make_shared<SLTIU_29>(),
    std::make_shared<SLTIU_30>(),
    std::make_shared<SLTIU_31>(),
    std::make_shared<SLTIU_32>(),
    std::make_shared<SLTIU_33>(),
    std::make_shared<SLTIU_34>(),
    std::make_shared<SLTIU_35>(),
    std::make_shared<SLTIU_36>(),
    std::make_shared<XORI_37>(),
    std::make_shared<XORI_38>(),
    std::make_shared<XORI_39>(),
    std::make_shared<XORI_40>(),
    std::make_shared<XORI_41>(),
    std::make_shared<XORI_42>(),
    std::make_shared<XORI_43>(),
    std::make_shared<XORI_44>(),
    std::make_shared<XORI_45>(),
    std::make_shared<XORI_46>(),
    std::make_shared<ORI_47>(),
    std::make_shared<ORI_48>(),
    std::make_shared<ORI_49>(),
    std::make_shared<ORI_50>(),
    std::make_shared<ORI_51>(),
    std::make_shared<ORI_52>(),
    std::make_shared<ORI_53>(),
    std::make_shared<ORI_54>(),
    std::make_shared<ORI_55>(),
    std::make_shared<ORI_56>(),
    std::make_shared<ANDI_57>(),
    std::make_shared<ANDI_58>(),
    std::make_shared<ANDI_59>(),
    std::make_shared<ANDI_60>(),
    std::make_shared<ANDI_61>(),
    std::make_shared<ANDI_62>(),
    std::make_shared<ANDI_63>(),
    std::make_shared<ANDI_64>(),
    std::make_shared<ANDI_65>(),
    std::make_shared<ANDI_66>(),
    std::make_shared<ADD_67>(),
    std::make_shared<ADD_68>(),
    std::make_shared<ADD_69>(),
    std::make_shared<ADD_70>(),
    std::make_shared<ADD_71>(),
    std::make_shared<ADD_72>(),
    std::make_shared<ADD_73>(),
    std::make_shared<SUB_74>(),
    std::make_shared<SUB_75>(),
    std::make_shared<SUB_76>(),
    std::make_shared<SUB_77>(),
    std::make_shared<SUB_78>(),
    std::make_shared<SUB_79>(),
    std::make_shared<SUB_80>(),
    std::make_shared<SLL_81>(),
    std::make_shared<SLL_82>(),
    std::make_shared<SLL_83>(),
    std::make_shared<SLL_84>(),
    std::make_shared<SLL_85>(),
    std::make_shared<SLL_86>(),
    std::make_shared<SLL_87>(),
    std::make_shared<SLT_88>(),
    std::make_shared<SLT_89>(),
    std::make_shared<SLT_90>(),
    std::make_shared<SLT_91>(),
    std::make_shared<SLT_92>(),
    std::make_shared<SLT_93>(),
    std::make_shared<SLT_94>(),
    std::make_shared<SLT_95>(),
    std::make_shared<SLT_96>(),
    std::make_shared<SLT_97>(),
    std::make_shared<SLT_98>(),
    std::make_shared<SLTU_99>(),
    std::make_shared<SLTU_100>(),
    std::make_shared<SLTU_101>(),
    std::make_shared<SLTU_102>(),
    std::make_shared<SLTU_103>(),
    std::make_shared<SLTU_104>(),
    std::make_shared<SLTU_105>(),
    std::make_shared<SLTU_106>(),
    std::make_shared<SLTU_107>(),
    std::make_shared<SLTU_108>(),
    std::make_shared<SLTU_109>(),
    std::make_shared<SLTU_110>(),
    std::make_shared<SRL_111>(),
    std::make_shared<SRL_112>(),
    std::make_shared<SRL_113>(),
    std::make_shared<SRL_114>(),
    std::make_shared<SRL_115>(),
    std::make_shared<SRL_116>(),
    std::make_shared<SRL_117>(),
    std::make_shared<SRL_118>(),
    std::make_shared<SRA_119>(),
    std::make_shared<SRA_120>(),
    std::make_shared<SRA_121>(),
    std::make_shared<SRA_122>(),
    std::make_shared<SRA_123>(),
    std::make_shared<SRA_124>(),
    std::make_shared<SRA_125>(),
    std::make_shared<XOR_126>(),
    std::make_shared<XOR_127>(),
    std::make_shared<XOR_128>(),
    std::make_shared<XOR_129>(),
    std::make_shared<XOR_130>(),
    std::make_shared<XOR_131>(),
    std::make_shared<XOR_132>(),
    std::make_shared<XOR_133>(),
    std::make_shared<OR_134>(),
    std::make_shared<OR_135>(),
    std::make_shared<OR_136>(),
    std::make_shared<OR_137>(),
    std::make_shared<OR_138>(),
    std::make_shared<OR_139>(),
    std::make_shared<OR_140>(),
    std::make_shared<OR_141>(),
    std::make_shared<AND_142>(),
    std::make_shared<AND_143>(),
    std::make_shared<AND_144>(),
    std::make_shared<AND_145>(),
    std::make_shared<AND_146>(),
    std::make_shared<AND_147>(),
    std::make_shared<AND_148>(),
    std::make_shared<AND_149>(),
    std::make_shared<SLLI_150>(),
    std::make_shared<SLLI_151>(),
    std::make_shared<SLLI_152>(),
    std::make_shared<SLLI_153>(),
    std::make_shared<SLLI_154>(),
    std::make_shared<SRLI_155>(),
    std::make_shared<SRLI_156>(),
    std::make_shared<SRLI_157>(),
    std::make_shared<SRLI_158>(),
    std::make_shared<SRLI_159>(),
    std::make_shared<SRLI_160>(),
    std::make_shared<SRAI_161>(),
    std::make_shared<SRAI_162>(),
    std::make_shared<SRAI_163>(),
    std::make_shared<SRAI_164>(),
    std::make_shared<SRAI_165>(),
    std::make_shared<LUI_166>(),
    std::make_shared<LUI_167>(),
    std::make_shared<LUI_168>(),
    std::make_shared<LUI_169>(),
    std::make_shared<LUI_170>(),
    std::make_shared<LUI_171>(),
    std::make_shared<AUIPC_172>(),
    std::make_shared<AUIPC_173>(),
    std::make_shared<AUIPC_174>(),
    std::make_shared<AUIPC_175>(),
    std::make_shared<AUIPC_176>(),
    std::make_shared<AUIPC_177>(),
    std::make_shared<AUIPC_178>(),
    std::make_shared<AUIPC_179>(),
    std::make_shared<JAL_180>(),
    std::make_shared<JAL_181>(),
    std::make_shared<JAL_182>(),
    std::make_shared<JAL_183>(),
    std::make_shared<JAL_184>(),
    std::make_shared<JAL_185>(),
    std::make_shared<JAL_186>(),
    std::make_shared<JAL_187>(),
    std::make_shared<JAL_188>(),
    std::make_shared<JALR_189>(),
    std::make_shared<JALR_190>(),
    std::make_shared<JALR_191>(),
    std::make_shared<JALR_192>(),
    std::make_shared<JALR_193>(),
    std::make_shared<JALR_194>(),
    std::make_shared<JALR_195>(),
    std::make_shared<JALR_196>(),
    std::make_shared<JALR_197>(),
    std::make_shared<JALR_198>(),
    std::make_shared<JALR_199>(),
    std::make_shared<JALR_200>(),
    std::make_shared<SB_201>(),
    std::make_shared<SB_202>(),
    std::make_shared<SB_203>(),
    std::make_shared<SB_204>(),
    std::make_shared<SB_205>(),
    std::make_shared<SB_206>(),
    std::make_shared<SB_207>(),
    std::make_shared<SB_208>(),
    std::make_shared<SB_209>(),
    std::make_shared<SB_210>(),
    std::make_shared<SB_211>(),
    std::make_shared<SH_212>(),
    std::make_shared<SH_213>(),
    std::make_shared<SH_214>(),
    std::make_shared<SH_215>(),
    std::make_shared<SH_216>(),
    std::make_shared<SH_217>(),
    std::make_shared<SH_218>(),
    std::make_shared<SH_219>(),
    std::make_shared<SH_220>(),
    std::make_shared<SH_221>(),
    std::make_shared<SH_222>(),
    std::make_shared<SW_223>(),
    std::make_shared<SW_224>(),
    std::make_shared<SW_225>(),
    std::make_shared<SW_226>(),
    std::make_shared<SW_227>(),
    std::make_shared<SW_228>(),
    std::make_shared<SW_229>(),
    std::make_shared<SW_230>(),
    std::make_shared<SW_231>(),
    std::make_shared<SW_232>(),
    std::make_shared<SW_233>(),
    std::make_shared<LB_234>(),
    std::make_shared<LB_235>(),
    std::make_shared<LB_236>(),
    std::make_shared<LB_237>(),
    std::make_shared<LB_238>(),
    std::make_shared<LB_239>(),
    std::make_shared<LB_240>(),
    std::make_shared<LB_241>(),
    std::make_shared<LB_242>(),
    std::make_shared<LB_243>(),
    std::make_shared<LB_244>(),
    std::make_shared<LB_245>(),
    std::make_shared<LB_246>(),
    std::make_shared<LH_247>(),
    std::make_shared<LH_248>(),
    std::make_shared<LH_249>(),
    std::make_shared<LH_250>(),
    std::make_shared<LH_251>(),
    std::make_shared<LH_252>(),
    std::make_shared<LH_253>(),
    std::make_shared<LH_254>(),
    std::make_shared<LH_255>(),
    std::make_shared<LH_256>(),
    std::make_shared<LH_257>(),
    std::make_shared<LH_258>(),
    std::make_shared<LH_259>(),
    std::make_shared<LW_260>(),
    std::make_shared<LW_261>(),
    std::make_shared<LW_262>(),
    std::make_shared<LW_263>(),
    std::make_shared<LW_264>(),
    std::make_shared<LW_265>(),
    std::make_shared<LW_266>(),
    std::make_shared<LW_267>(),
    std::make_shared<LW_268>(),
    std::make_shared<LW_269>(),
    std::make_shared<LW_270>(),
    std::make_shared<LW_271>(),
    std::make_shared<LW_272>(),
    std::make_shared<LBU_273>(),
    std::make_shared<LBU_274>(),
    std::make_shared<LBU_275>(),
    std::make_shared<LBU_276>(),
    std::make_shared<LBU_277>(),
    std::make_shared<LBU_278>(),
    std::make_shared<LBU_279>(),
    std::make_shared<LBU_280>(),
    std::make_shared<LBU_281>(),
    std::make_shared<LBU_282>(),
    std::make_shared<LBU_283>(),
    std::make_shared<LBU_284>(),
    std::make_shared<LBU_285>(),
    std::make_shared<LHU_286>(),
    std::make_shared<LHU_287>(),
    std::make_shared<LHU_288>(),
    std::make_shared<LHU_289>(),
    std::make_shared<LHU_290>(),
    std::make_shared<LHU_291>(),
    std::make_shared<LHU_292>(),
    std::make_shared<LHU_293>(),
    std::make_shared<LHU_294>(),
    std::make_shared<LHU_295>(),
    std::make_shared<LHU_296>(),
    std::make_shared<LHU_297>(),
    std::make_shared<LHU_298>(),
    std::make_shared<BEQ_299>(),
    std::make_shared<BEQ_300>(),
    std::make_shared<BEQ_301>(),
    std::make_shared<BEQ_302>(),
    std::make_shared<BEQ_303>(),
    std::make_shared<BEQ_304>(),
    std::make_shared<BEQ_305>(),
    std::make_shared<BEQ_306>(),
    std::make_shared<BEQ_307>(),
    std::make_shared<BEQ_308>(),
    std::make_shared<BEQ_309>(),
    std::make_shared<BEQ_310>(),
    std::make_shared<BEQ_311>(),
    std::make_shared<BEQ_312>(),
    std::make_shared<BEQ_313>(),
    std::make_shared<BNE_314>(),
    std::make_shared<BNE_315>(),
    std::make_shared<BNE_316>(),
    std::make_shared<BNE_317>(),
    std::make_shared<BNE_318>(),
    std::make_shared<BNE_319>(),
    std::make_shared<BNE_320>(),
    std::make_shared<BNE_321>(),
    std::make_shared<BNE_322>(),
    std::make_shared<BNE_323>(),
    std::make_shared<BNE_324>(),
    std::make_shared<BNE_325>(),
    std::make_shared<BNE_326>(),
    std::make_shared<BNE_327>(),
    std::make_shared<BNE_328>(),
    std::make_shared<BLT_329>(),
    std::make_shared<BLT_330>(),
    std::make_shared<BLT_331>(),
    std::make_shared<BLT_332>(),
    std::make_shared<BLT_333>(),
    std::make_shared<BLT_334>(),
    std::make_shared<BLT_335>(),
    std::make_shared<BLT_336>(),
    std::make_shared<BLT_337>(),
    std::make_shared<BLT_338>(),
    std::make_shared<BLT_339>(),
    std::make_shared<BLT_340>(),
    std::make_shared<BLT_341>(),
    std::make_shared<BLT_342>(),
    std::make_shared<BLT_343>(),
    std::make_shared<BGE_344>(),
    std::make_shared<BGE_345>(),
    std::make_shared<BGE_346>(),
    std::make_shared<BGE_347>(),
    std::make_shared<BGE_348>(),
    std::make_shared<BGE_349>(),
    std::make_shared<BGE_350>(),
    std::make_shared<BGE_351>(),
    std::make_shared<BGE_352>(),
    std::make_shared<BGE_353>(),
    std::make_shared<BGE_354>(),
    std::make_shared<BGE_355>(),
    std::make_shared<BGE_356>(),
    std::make_shared<BGE_357>(),
    std::make_shared<BGE_358>(),
    std::make_shared<BLTU_359>(),
    std::make_shared<BLTU_360>(),
    std::make_shared<BLTU_361>(),
    std::make_shared<BLTU_362>(),
    std::make_shared<BLTU_363>(),
    std::make_shared<BLTU_364>(),
    std::make_shared<BLTU_365>(),
    std::make_shared<BLTU_366>(),
    std::make_shared<BLTU_367>(),
    std::make_shared<BLTU_368>(),
    std::make_shared<BLTU_369>(),
    std::make_shared<BLTU_370>(),
    std::make_shared<BLTU_371>(),
    std::make_shared<BLTU_372>(),
    std::make_shared<BLTU_373>(),
    std::make_shared<BLTU_374>(),
    std::make_shared<BGEU_375>(),
    std::make_shared<BGEU_376>(),
    std::make_shared<BGEU_377>(),
    std::make_shared<BGEU_378>(),
    std::make_shared<BGEU_379>(),
    std::make_shared<BGEU_380>(),
    std::make_shared<BGEU_381>(),
    std::make_shared<BGEU_382>(),
    std::make_shared<BGEU_383>(),
    std::make_shared<BGEU_384>(),
    std::make_shared<BGEU_385>(),
    std::make_shared<BGEU_386>(),
    std::make_shared<BGEU_387>(),
    std::make_shared<BGEU_388>(),
    std::make_shared<BGEU_389>(),
    std::make_shared<BGEU_390>()};

/* Hand written mutations */
struct ADD_Mutation1 : OperationMutation<Opcode::ADD, ADD_Mutation1> {
    ADD_Mutation1() : OperationMutation<Opcode::ADD, ADD_Mutation1>("Add 1") {}
    void apply(ISS &core) {
        printf("ADD Mutation\n");
        auto x = core.read_reg(core.rs1()) - core.read_reg(core.rs2());
        core.write_reg(core.rd(), x);
    }
};
struct ADD_Mutation2 : OperationMutation<Opcode::ADD, ADD_Mutation2> {
    ADD_Mutation2() : OperationMutation<Opcode::ADD, ADD_Mutation2>("Add 2") {}
    void apply(ISS &core) {
        auto x = core.read_reg(core.rs1()) + core.read_reg(core.rs2()) + 1;
        core.write_reg(core.rd(), x);
    }
};
struct ADD_Mutation3 : OperationMutation<Opcode::ADD, ADD_Mutation3> {
    ADD_Mutation3() : OperationMutation<Opcode::ADD, ADD_Mutation3>("Add 3") {}
    void apply(ISS &core) {
        auto x = (core.read_reg(core.rs1()) + core.read_reg(core.rs2())) & ((1 << 30) - 1);
        core.write_reg(core.rd(), x);
    }
};
struct AND_Mutation1 : OperationMutation<Opcode::ADD, AND_Mutation1> {
    AND_Mutation1() : OperationMutation<Opcode::ADD, AND_Mutation1>("AND & to |") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg(core.rs1()) | core.read_reg(core.rs2()));
    }
};
struct XOR_Mutation1 : OperationMutation<Opcode::ADD, XOR_Mutation1> {
    XOR_Mutation1() : OperationMutation<Opcode::ADD, XOR_Mutation1>("AND ^ to &") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg(core.rs1()) & core.read_reg(core.rs2()));
    }
};
struct OR_Mutation1 : OperationMutation<Opcode::ADD, OR_Mutation1> {
    OR_Mutation1() : OperationMutation<Opcode::ADD, OR_Mutation1>("OR | to &") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg(core.rs1()) & core.read_reg(core.rs2()));
    }
};
struct BLT_Mutation1 : OperationMutation<Opcode::BLT, BLT_Mutation1> {
    BLT_Mutation1() : OperationMutation<Opcode::BLT, BLT_Mutation1>("BLT < to <=") {}
    void apply(ISS &core) {
        if (core.read_reg(core.rs1()) <= core.read_reg(core.rs2())) {
            core.pc = core.last_pc + core.B_imm();
            core.trap_check_pc_alignment();
        }
    }
};
struct BLT_Mutation2 : OperationMutation<Opcode::BLT, BLT_Mutation2> {
    BLT_Mutation2() : OperationMutation<Opcode::BLT, BLT_Mutation2>("BLT < to >") {}
    void apply(ISS &core) {
        if (core.read_reg(core.rs1()) > core.read_reg(core.rs2())) {
            core.pc = core.last_pc + core.B_imm();
            core.trap_check_pc_alignment();
        }
    }
};
struct BGE_Mutation1 : OperationMutation<Opcode::BGE, BGE_Mutation1> {
    BGE_Mutation1() : OperationMutation<Opcode::BGE, BGE_Mutation1>("BGE >= to <=") {}
    void apply(ISS &core) {
        if (core.read_reg(core.rs1()) <= core.read_reg(core.rs2())) {
            core.pc = core.last_pc + core.B_imm();
            core.trap_check_pc_alignment();
        }
    }
};
struct BGE_Mutation2 : OperationMutation<Opcode::BGE, BGE_Mutation2> {
    BGE_Mutation2() : OperationMutation<Opcode::BGE, BGE_Mutation2>("BGE >= to <=") {}
    void apply(ISS &core) {
        if (core.read_reg(core.rs2()) >= core.read_reg(core.rs1())) {
            core.pc = core.last_pc + core.B_imm();
            core.trap_check_pc_alignment();
        }
    }
};
struct SLL_Mutation1 : OperationMutation<Opcode::SLL, SLL_Mutation1> {
    SLL_Mutation1() : OperationMutation<Opcode::SLL, SLL_Mutation1>("SLL << to >>") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg(core.rs1()) >> core.regs.shamt(core.rs2()));
    }
};
struct SRL_Mutation1 : OperationMutation<Opcode::SRL, SRL_Mutation1> {
    SRL_Mutation1() : OperationMutation<Opcode::SRL, SRL_Mutation1>("SRL >> to <<") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg(core.rs1()) << core.regs.shamt(core.rs2()));
    }
};
struct SRAI_Mutation1 : OperationMutation<Opcode::SRL, SRAI_Mutation1> {
    SRAI_Mutation1() : OperationMutation<Opcode::SRL, SRAI_Mutation1>("SRAI signed to unsigned") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg((uint32_t)core.rs1()) >> core.shamt());
    }
};
struct JAL_Mutation1 : OperationMutation<Opcode::JAL, JAL_Mutation1> {
    JAL_Mutation1() : OperationMutation<Opcode::JAL, JAL_Mutation1>("JAL + to -") {}
    void apply(ISS &core) {
        auto link = core.pc;
        core.pc = core.last_pc - core.J_imm();
        core.trap_check_pc_alignment();
        core.write_reg(core.rd(), link);
    }
};
struct SLT_Mutation1 : OperationMutation<Opcode::JAL, SLT_Mutation1> {
    SLT_Mutation1() : OperationMutation<Opcode::JAL, SLT_Mutation1>("SLT < to >") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg(core.rs1()) > core.read_reg(core.rs2()));
    }
};

std::vector<std::shared_ptr<exec_mutator_if>> mutators2{
    std::make_shared<EmptyMutation>(),
    std::make_shared<SUB_74>(),
    std::make_shared<ADD_Mutation1>(),
    //std::make_shared<ADD_Mutation2>(),
    //std::make_shared<ADD_Mutation3>(),
    //std::make_shared<AND_Mutation1>(),
    //std::make_shared<BGE_Mutation1>(),
    //std::make_shared<BGE_Mutation2>(),
    //std::make_shared<BLT_Mutation1>(),
    //std::make_shared<BLT_Mutation2>(),
    //std::make_shared<JAL_Mutation1>(),
    //std::make_shared<OR_Mutation1>(),
    //std::make_shared<SLL_Mutation1>(),
    //std::make_shared<SLT_Mutation1>(),
    //std::make_shared<SRAI_Mutation1>(),
    //std::make_shared<SRL_Mutation1>(),
    //std::make_shared<XOR_Mutation1>(),
};
std::vector<std::shared_ptr<exec_mutator_if>> get_mutators() {
    //mutators.insert(mutators.end(), mutators2.begin(), mutators2.end());
    return mutators;
}
