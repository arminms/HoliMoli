#pragma once

namespace HoliMoli
{

    template <typename T = DirectX::XMFLOAT3>
    struct elements_color_db
    {
        elements_color_db();

        std::array<T, 120> m_color;
    };

    #include "ElementsColor.ipp"

}   // HoliMoli