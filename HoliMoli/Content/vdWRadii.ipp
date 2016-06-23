template <typename T>
vdw_radii_tb<T>::vdw_radii_tb()
{   // data got from DOI: 10.1039/c3dt50599e
    m_radius =
    {
        T(1.50) // 0, Lp -> not from the above referennce
    ,   T(1.20) // 1, H
    ,   T(1.43) // 2, He
    ,   T(2.12) // 3, Li
    ,   T(1.98) // 4, Be
    ,   T(1.91) // 5, B
    ,   T(1.77) // 6, C
    ,   T(1.66) // 7, N
    ,   T(1.50) // 8, O
    ,   T(1.46) // 9, F
    ,   T(1.58) // 10, Ne
    ,   T(2.50) // 11, Na
    ,   T(2.51) // 12, Mg
    ,   T(2.25) // 13, Al
    ,   T(2.19) // 14, Si
    ,   T(1.90) // 15, P
    ,   T(1.89) // 16, S
    ,   T(1.82) // 17, Cl
    ,   T(1.83) // 18, Ar
    ,   T(2.73) // 19, K
    ,   T(2.62) // 20, Ca
    ,   T(2.58) // 21, Sc
    ,   T(2.46) // 22, Ti
    ,   T(2.42) // 23, V
    ,   T(2.45) // 24, Cr
    ,   T(2.45) // 25, Mn
    ,   T(2.44) // 26, Fe
    ,   T(2.40) // 27, Co
    ,   T(2.40) // 28, Ni
    ,   T(2.38) // 29, Cu
    ,   T(2.39) // 30, Zn
    ,   T(2.32) // 31, Ga
    ,   T(2.29) // 32, Ge
    ,   T(1.88) // 33, As
    ,   T(1.82) // 34, Se
    ,   T(1.86) // 35, Br
    ,   T(2.25) // 36, Kr
    ,   T(3.21) // 37, Rb
    ,   T(2.84) // 38, Sr
    ,   T(2.75) // 39, Y
    ,   T(2.52) // 40, Zr
    ,   T(2.56) // 41, Nb
    ,   T(2.45) // 42, Mo
    ,   T(2.44) // 43, Tc
    ,   T(2.46) // 44, Ru
    ,   T(2.44) // 45, Rh
    ,   T(2.15) // 46, Pd
    ,   T(2.53) // 47, Ag
    ,   T(2.49) // 48, Cd
    ,   T(2.43) // 49, In
    ,   T(2.42) // 50, Sn
    ,   T(2.47) // 51, Sb
    ,   T(1.99) // 52, Te
    ,   T(2.04) // 53, I
    ,   T(2.06) // 54, Xe
    ,   T(3.48) // 55, Cs
    ,   T(3.03) // 56, Ba
    ,   T(2.98) // 57, La
    ,   T(2.88) // 58, Ce
    ,   T(2.92) // 59, Pr
    ,   T(2.95) // 60, Nd
    ,   T(2.93) // 61, Pm -> missed in the above referennce
    ,   T(2.90) // 62, Sm
    ,   T(2.87) // 63, Eu
    ,   T(2.83) // 64, Gd
    ,   T(2.79) // 65, Tb
    ,   T(2.87) // 66, Dy
    ,   T(2.81) // 67, Ho
    ,   T(2.83) // 68, Er
    ,   T(2.79) // 69, Tm
    ,   T(2.80) // 70, Yb
    ,   T(2.74) // 71, Lu
    ,   T(2.63) // 72, Hf
    ,   T(2.53) // 73, Ta
    ,   T(2.57) // 74, W
    ,   T(2.49) // 75, Re
    ,   T(2.48) // 76, Os
    ,   T(2.41) // 77, Ir
    ,   T(2.29) // 78, Pt
    ,   T(2.32) // 79, Au
    ,   T(2.45) // 80, Hg
    ,   T(2.47) // 81, Tl
    ,   T(2.60) // 82, Pb
    ,   T(2.54) // 83, Bi
    ,   T(2.55) // 84, Po -> missed in the above referennce
    ,   T(2.56) // 85, At -> missed in the above referennce
    ,   T(2.57) // 86, Rn -> missed in the above referennce
    ,   T(3.50) // 87, Fr -> missed in the above referennce
    ,   T(3.10) // 88, Ra -> missed in the above referennce
    ,   T(2.80) // 89, Ac
    ,   T(2.93) // 90, Th
    ,   T(2.88) // 91, Pa
    ,   T(2.71) // 92, U
    ,   T(2.82) // 93, Np
    ,   T(2.81) // 94, Pu
    ,   T(2.83) // 95, Am
    ,   T(3.05) // 96, Cm
    ,   T(3.40) // 97, Bk
    ,   T(3.05) // 98, Cf
    ,   T(2.70) // 99, Es
    ,   T(2.75) // 100, Fm -> missed in the above referennce
    ,   T(2.75) // 101, Md -> missed in the above referennce
    ,   T(2.75) // 102, No -> missed in the above referennce
    ,   T(2.75) // 103, Lr -> missed in the above referennce
    ,   T(3.00) // 104, Rf -> missed in the above referennce
    ,   T(3.00) // 105, Db -> missed in the above referennce
    ,   T(3.00) // 106, Sg -> missed in the above referennce
    ,   T(3.00) // 107, Bh -> missed in the above referennce
    ,   T(3.00) // 108, Hs -> missed in the above referennce
    ,   T(3.00) // 109, Mt -> missed in the above referennce
    ,   T(3.00) // 110, Ds -> missed in the above referennce
    ,   T(3.00) // 111, Rg -> missed in the above referennce
    ,   T(3.00) // 112, Cn -> missed in the above referennce
    ,   T(3.00) // 113, Nh -> missed in the above referennce
    ,   T(3.00) // 114, Fl -> missed in the above referennce
    ,   T(3.00) // 115, Mc -> missed in the above referennce
    ,   T(3.00) // 116, Lv -> missed in the above referennce
    ,   T(3.00) // 117, Ts -> missed in the above referennce
    ,   T(3.00) // 118, Og -> missed in the above referennce
    ,   T(1.70) // 119, Xx -> not from the above referennce
    };
}