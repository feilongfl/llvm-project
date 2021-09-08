
def CC_V800 : CallingConv<[
    CCIfType<[i1, i8, i16], CCPromoteToType<i32>>,
    CCIfSRet<CCIfType<[i32], CCAssignToReg<[R6]>>>,
    CCIfType<[i32, i64, f32, f64], CCAssignToReg<[R7, R8, R9, R10, R11, R12, R13, R14]>>,
    CCAssignToStack<4, 4>
]>;

def RetCC_V800 : CallingConv<[
    CCIfType<[i32, f32], CCAssignToReg<[R7]>>,
    CCIfType<[i64, f64], CCAssignToReg<[R7, R8]>>,
]>;

def CSR_V800 : CalleeSavedRegs<(add (sequence "R%d", 24, 31))