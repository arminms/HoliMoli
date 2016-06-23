#pragma once

namespace HoliMoli
{

    template <typename T = DirectX::XMFLOAT3>
    struct elements_color_tb
    {
        elements_color_tb();

        std::array<T, 120> m_color;
    };

    #include "ElementsColor.ipp"

}   // HoliMoli