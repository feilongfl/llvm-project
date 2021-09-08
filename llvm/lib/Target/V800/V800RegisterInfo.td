
class V800Reg<bits<5> Enc, string n> : Register<n> {
    let HWEncoding{15-5} = 0;
    let HWEncoding{4-0} = Enc;
    let Namespace = "V800";
}

class GRi<bits<5> Enc, string n> :V800Reg<Enc, n>;
foreach I = 0-31 in {
    def R#I : GRi<I, "r"#I>;
}
def GPR : RegisterClass<"V800", [i32], 32,
                (add (sequence "R%u", 0, 31))>;

def GPROpnd : RegisterOperand<GPR>
