template <typename T>
elements_color_tb<T>::elements_color_tb()
{
    m_color =
    {
        T(1.000000f, 0.411765f, 0.705882f) // 0, Lp
    ,   T(1.000000f, 1.000000f, 1.000000f) // 1, H
    ,   T(0.839216f, 1.000000f, 1.000000f) // 2, He
    ,   T(0.800000f, 0.545098f, 1.000000f) // 3, Li
    ,   T(0.772549f, 0.964706f, 0.043137f) // 4, Be
    ,   T(1.000000f, 0.709804f, 0.709804f) // 5, B
    ,   T(0.580000f, 0.580000f, 0.580000f) // 6, C
    ,   T(0.000000f, 0.580000f, 0.800000f) // 7, N
    ,   T(0.890000f, 0.310000f, 0.310000f) // 8, O
    ,   T(0.580392f, 0.854902f, 0.407843f) // 9, F
    ,   T(0.678431f, 0.929412f, 0.956863f) // 10, Ne
    ,   T(0.658824f, 0.490196f, 0.843137f) // 11, Na
    ,   T(0.627451f, 0.850980f, 0.078431f) // 12, Mg
    ,   T(0.894118f, 0.631373f, 0.627451f) // 13, Al
    ,   T(0.941176f, 0.784314f, 0.627451f) // 14, Si
    ,   T(1.000000f, 0.501961f, 0.000000f) // 15, P
    ,   T(1.000000f, 0.790000f, 0.000000f) // 16, S
    ,   T(0.411765f, 0.933333f, 0.164706f) // 17, Cl
    ,   T(0.545098f, 0.847059f, 0.894118f) // 18, Ar
    ,   T(0.533333f, 0.419608f, 0.705882f) // 19, K
    ,   T(0.478431f, 0.745098f, 0.094118f) // 20, Ca
    ,   T(0.901961f, 0.901961f, 0.901961f) // 21, Sc
    ,   T(1.000000f, 0.000000f, 0.000000f) // 22, Ti
    ,   T(0.650980f, 0.650980f, 0.670588f) // 23, V
    ,   T(0.541176f, 0.600000f, 0.780392f) // 24, Cr
    ,   T(0.611765f, 0.478431f, 0.780392f) // 25, Mn
    ,   T(0.501961f, 0.501961f, 0.501961f) // 26, Fe
    ,   T(0.941176f, 0.564706f, 0.627451f) // 27, Co
    ,   T(0.313725f, 0.815686f, 0.313725f) // 28, Ni
    ,   T(0.784314f, 0.501961f, 0.200000f) // 29, Cu
    ,   T(0.490196f, 0.501961f, 0.690196f) // 30, Zn
    ,   T(0.800000f, 0.541176f, 0.533333f) // 31, Ga
    ,   T(0.603922f, 0.631373f, 0.576471f) // 32, Ge
    ,   T(0.741176f, 0.501961f, 0.890196f) // 33, As
    ,   T(0.917647f, 0.658824f, 0.070588f) // 34, Se
    ,   T(0.588235f, 0.219608f, 0.160784f) // 35, Br
    ,   T(0.427451f, 0.749020f, 0.811765f) // 36, Kr
    ,   T(0.423529f, 0.329412f, 0.584314f) // 37, Rb
    ,   T(0.325490f, 0.647059f, 0.094118f) // 38, Sr
    ,   T(0.529412f, 1.000000f, 1.000000f) // 39, Y
    ,   T(0.458824f, 0.917647f, 0.921569f) // 40, Zr
    ,   T(0.384314f, 0.835294f, 0.843137f) // 41, Nb
    ,   T(0.309804f, 0.752941f, 0.768627f) // 42, Mo
    ,   T(0.235294f, 0.670588f, 0.701961f) // 43, Tc
    ,   T(0.156863f, 0.588235f, 0.639216f) // 44, Ru
    ,   T(0.078431f, 0.501961f, 0.580392f) // 45, Rh
    ,   T(0.000000f, 0.419608f, 0.525490f) // 46, Pd
    ,   T(0.752941f, 0.752941f, 0.752941f) // 47, Ag
    ,   T(1.000000f, 0.850980f, 0.560784f) // 48, Cd
    ,   T(0.729412f, 0.439216f, 0.423529f) // 49, In
    ,   T(0.396078f, 0.490196f, 0.494118f) // 50, Sn
    ,   T(0.619608f, 0.388235f, 0.709804f) // 51, Sb
    ,   T(0.819608f, 0.450980f, 0.007843f) // 52, Te
    ,   T(0.580392f, 0.000000f, 0.580392f) // 53, I
    ,   T(0.317647f, 0.639216f, 0.709804f) // 54, Xe
    ,   T(0.333333f, 0.215686f, 0.482353f) // 55, Cs
    ,   T(0.164706f, 0.556863f, 0.078431f) // 56, Ba
    ,   T(0.929412f, 0.717647f, 0.329412f) // 57, La
    ,   T(0.898039f, 0.733333f, 0.325490f) // 58, Ce
    ,   T(0.866667f, 0.709804f, 0.313725f) // 59, Pr
    ,   T(0.839216f, 0.662745f, 0.301961f) // 60, Nd
    ,   T(0.811765f, 0.607843f, 0.286275f) // 61, Pm
    ,   T(0.811765f, 0.607843f, 0.286275f) // 62, Sm
    ,   T(0.764706f, 0.494118f, 0.250980f) // 63, Eu
    ,   T(0.745098f, 0.439216f, 0.231373f) // 64, Gd
    ,   T(0.725490f, 0.392157f, 0.215686f) // 65, Tb
    ,   T(0.701961f, 0.349020f, 0.200000f) // 66, Dy
    ,   T(0.682353f, 0.309804f, 0.184314f) // 67, Ho
    ,   T(0.650980f, 0.274510f, 0.176471f) // 68, Er
    ,   T(0.615686f, 0.250980f, 0.172549f) // 69, Tm
    ,   T(0.556863f, 0.235294f, 0.172549f) // 70, Yb
    ,   T(0.474510f, 0.227451f, 0.184314f) // 71, Lu
    ,   T(0.784314f, 0.717647f, 0.717647f) // 72, Hf
    ,   T(0.737255f, 0.545098f, 0.682353f) // 73, Ta
    ,   T(0.682353f, 0.360784f, 0.639216f) // 74, W
    ,   T(0.603922f, 0.368627f, 0.556863f) // 75, Re
    ,   T(0.521569f, 0.380392f, 0.470588f) // 76, Os
    ,   T(0.447059f, 0.372549f, 0.400000f) // 77, Ir
    ,   T(0.815686f, 0.815686f, 0.878431f) // 78, Pt
    ,   T(1.000000f, 0.819608f, 0.137255f) // 79, Au
    ,   T(0.721569f, 0.721569f, 0.815686f) // 80, Hg
    ,   T(0.650980f, 0.329412f, 0.301961f) // 81, Tl
    ,   T(0.341176f, 0.349020f, 0.380392f) // 82, Pb
    ,   T(0.619608f, 0.309804f, 0.709804f) // 83, Bi
    ,   T(0.670588f, 0.360784f, 0.000000f) // 84, Po
    ,   T(0.458824f, 0.309804f, 0.270588f) // 85, At
    ,   T(0.219608f, 0.517647f, 0.592157f) // 86, Rn
    ,   T(0.254902f, 0.086275f, 0.400000f) // 87, Fr
    ,   T(0.000000f, 0.474510f, 0.043137f) // 88, Ra
    ,   T(0.321569f, 0.717647f, 0.992157f) // 89, Ac
    ,   T(0.360784f, 0.670588f, 0.945098f) // 90, Th
    ,   T(0.396078f, 0.627451f, 0.901961f) // 91, Pa
    ,   T(0.431373f, 0.588235f, 0.858824f) // 92, U
    ,   T(0.462745f, 0.545098f, 0.815686f) // 93, Np
    ,   T(0.494118f, 0.505882f, 0.776471f) // 94, Pu
    ,   T(0.521569f, 0.470588f, 0.737255f) // 95, Am
    ,   T(0.549020f, 0.435294f, 0.698039f) // 96, Cm
    ,   T(0.572549f, 0.400000f, 0.662745f) // 97, Bk
    ,   T(0.596078f, 0.368627f, 0.627451f) // 98, Cf
    ,   T(0.615686f, 0.337255f, 0.592157f) // 99, Es
    ,   T(0.635294f, 0.305882f, 0.560784f) // 100, Fm
    ,   T(0.650980f, 0.278431f, 0.529412f) // 101, Md
    ,   T(0.662745f, 0.254902f, 0.501961f) // 102, No
    ,   T(0.674510f, 0.227451f, 0.470588f) // 103, Lr
    ,   T(0.686275f, 0.203922f, 0.447059f) // 104, Rf
    ,   T(0.694118f, 0.184314f, 0.419608f) // 105, Db
    ,   T(0.698039f, 0.164706f, 0.396078f) // 106, Sg
    ,   T(0.701961f, 0.145098f, 0.372549f) // 107, Bh
    ,   T(0.000000f, 0.000000f, 1.000000f) // 108, Hs
    ,   T(0.701961f, 0.117647f, 0.329412f) // 109, Mt
    ,   T(0.698039f, 0.101961f, 0.309804f) // 110, Ds
    ,   T(0.694118f, 0.090196f, 0.294118f) // 111, Rg
    ,   T(0.686275f, 0.082353f, 0.278431f) // 112, Cn
    ,   T(0.674510f, 0.074510f, 0.262745f) // 113, Nh
    ,   T(0.666667f, 0.066667f, 0.247059f) // 114, Fl
    ,   T(0.650980f, 0.062745f, 0.235294f) // 115, Mc
    ,   T(0.635294f, 0.058824f, 0.223529f) // 116, Lv
    ,   T(0.607843f, 0.054902f, 0.215686f) // 117, Ts
    ,   T(0.580392f, 0.054902f, 0.203922f) // 118, Og
    ,   T(0.537255f, 0.050980f, 0.188235f) // 119, Xx
    };
}