#pragma once

namespace HoliMoli
{

    template <typename T = float>
    struct vdw_radii_tb
    {
        vdw_radii_tb();

        std::array<T, 120> m_radius;
    };

    #include "vdWRadii.ipp"

}   // HoliMoli