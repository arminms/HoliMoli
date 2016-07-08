#pragma once

#include "..\Common\DeviceResources.h"
#include "..\Common\StepTimer.h"
#include "ShaderStructures.h"
#include "ElementsColor.h"
#include "vdWRadii.h"

namespace HoliMoli
{
    // This sample renderer instantiates a basic rendering pipeline
    class SpinningMoleculeRenderer
    {
    public:
        SpinningMoleculeRenderer(const std::shared_ptr<DX::DeviceResources>& deviceResources);
        void CreateDeviceDependentResources();
        void ReleaseDeviceDependentResources();
        void Update(const DX::StepTimer& timer);
        void Render();

        // Repositions the sample hologram
        void PositionHologram(Windows::UI::Input::Spatial::SpatialPointerPose^ pointerPose);

        // Property accessors
        void SetPosition(Windows::Foundation::Numerics::float3 pos) { m_position = pos;  }
        Windows::Foundation::Numerics::float3 GetPosition()         { return m_position; }

        void SetScaling(float sc) { m_scaling = sc; }
        void SetDefaultScaling() { m_scaling = m_defaultScaling; }
        float GetScaling() const { return m_scaling; }

        void SetDistance(float d) { m_distance = d < 0.5f ? 0.5f : d; }
        void SetDefaultDistance() { m_distance = 2.f; }
        float GetDistance() const { return m_distance; }

        void SetRotationSpeed(float a) { m_degreesPerFrame = a < 0.f ? 0.f : a; }
        void SetDefaultRotationSpeed() { m_degreesPerFrame = 0.05f; }
        float GetRotationSpeed() const { return m_degreesPerFrame; }

    private:
        // Cached pointer to device resources
        std::shared_ptr<DX::DeviceResources>            m_deviceResources;

        // Direct3D resources for molecule geometry
        Microsoft::WRL::ComPtr<ID3D11InputLayout>       m_inputLayout;
        Microsoft::WRL::ComPtr<ID3D11Buffer>            m_vertexBuffer;
        Microsoft::WRL::ComPtr<ID3D11Buffer>            m_indexBuffer;
        Microsoft::WRL::ComPtr<ID3D11VertexShader>      m_vertexShader;
        Microsoft::WRL::ComPtr<ID3D11HullShader>        m_hullShader;
        Microsoft::WRL::ComPtr<ID3D11DomainShader>      m_domainShader;
        Microsoft::WRL::ComPtr<ID3D11GeometryShader>    m_geometryShader;
        Microsoft::WRL::ComPtr<ID3D11PixelShader>       m_pixelShader;
        Microsoft::WRL::ComPtr<ID3D11Buffer>            m_modelConstantBuffer;

        // System resources for molecule geometry
        ModelConstantBuffer                             m_modelConstantBufferData;
        uint32                                          m_indexCount = 0;

        // Variables used with the rendering loop
        bool                                            m_loadingComplete = false;
        float                                           m_degreesPerFrame = 0.05f;
        double                                          m_totalRotation = 0.0;
        Windows::Foundation::Numerics::float3           m_position = { 0.f, 0.f, -2.f };
        float                                           m_distance = 2.f;
        float                                           m_scaling = 0.1f;
        float                                           m_defaultScaling = 0.1f;
        DirectX::XMFLOAT4X4                             m_atomsTranform;

        // If the current D3D Device supports VPRT, we can avoid using a geometry
        // shader just to set the render target array index
        bool                                            m_usingVprtShaders = false;

        // Elements color
        elements_color_tb<>                             m_elementsColors;

        // van der Waals radii
        vdw_radii_tb<>                                  m_vdwRadii;
    };
}
