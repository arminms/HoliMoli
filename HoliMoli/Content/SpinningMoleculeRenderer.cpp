#include "pch.h"
#include "SpinningMoleculeRenderer.h"
#include "Common\DirectXHelper.h"

using namespace HoliMoli;
using namespace Concurrency;
using namespace DirectX;
using namespace Windows::Foundation::Numerics;
using namespace Windows::UI::Input::Spatial;
using namespace Windows::Storage;

// Loads vertex and pixel shaders from files and instantiates the molecule geometry.
SpinningMoleculeRenderer::SpinningMoleculeRenderer(const std::shared_ptr<DX::DeviceResources>& deviceResources) :
    m_deviceResources(deviceResources)
{
    CreateDeviceDependentResources();
}

// This function uses a SpatialPointerPose to position the world-locked hologram
// two meters in front of the user's heading.
void SpinningMoleculeRenderer::PositionHologram(SpatialPointerPose^ pointerPose)
{
    if (pointerPose != nullptr)
    {
        // Get the gaze direction relative to the given coordinate system.
        const float3 headPosition    = pointerPose->Head->Position;
        const float3 headDirection   = pointerPose->Head->ForwardDirection;

        // The hologram is positioned two meters along the user's gaze direction.
        static const float distanceFromUser = 2.0f; // meters
        const float3 gazeAtTwoMeters        = headPosition + (distanceFromUser * headDirection);

        // This will be used as the translation component of the hologram's
        // model transform.
        SetPosition(gazeAtTwoMeters);
    }
}

// Called once per frame. Rotates the molecule, and calculates and sets the model matrix
// relative to the position transform indicated by hologramPositionTransform.
void SpinningMoleculeRenderer::Update(const DX::StepTimer& timer)
{
    // Rotate the molecule.
    // Convert degrees to radians, then convert seconds to rotation angle.
    const float    radiansPerSecond = XMConvertToRadians(m_degreesPerSecond);
    const double   totalRotation    = timer.GetTotalSeconds() * radiansPerSecond;
    const float    radians          = static_cast<float>(fmod(totalRotation, XM_2PI));
    const XMMATRIX modelRotation    = XMMatrixRotationY(-radians);

    // Position the molecule.
    const XMMATRIX modelTranslation = XMMatrixTranslationFromVector(XMLoadFloat3(&m_position));

    // Multiply to get the transform matrix.
    // Note that this transform does not enforce a particular coordinate system. The calling
    // class is responsible for rendering this content in a consistent manner.
    const XMMATRIX modelTransform   = XMMatrixMultiply(modelRotation, modelTranslation);

    // The view and projection matrices are provided by the system; they are associated
    // with holographic cameras, and updated on a per-camera basis.
    // Here, we provide the model transform for the sample hologram. The model transform
    // matrix is transposed to prepare it for the shader.
    XMStoreFloat4x4(&m_modelConstantBufferData.model, XMMatrixTranspose(modelTransform));

    // Loading is asynchronous. Resources must be created before they can be updated.
    if (!m_loadingComplete)
    {
        return;
    }

    // Use the D3D device context to update Direct3D device-based resources.
    const auto context = m_deviceResources->GetD3DDeviceContext();

    // Update the model transform buffer for the hologram.
    context->UpdateSubresource(
        m_modelConstantBuffer.Get(),
        0,
        nullptr,
        &m_modelConstantBufferData,
        0,
        0
        );
}

// Renders one frame using the vertex and pixel shaders.
// On devices that do not support the D3D11_FEATURE_D3D11_OPTIONS3::
// VPAndRTArrayIndexFromAnyShaderFeedingRasterizer optional feature,
// a pass-through geometry shader is also used to set the render 
// target array index.
void SpinningMoleculeRenderer::Render()
{
    // Loading is asynchronous. Resources must be created before drawing can occur.
    if (!m_loadingComplete)
    {
        return;
    }

    const auto context = m_deviceResources->GetD3DDeviceContext();

    // Each vertex is one instance of the VertexPositionColor struct.
    const UINT stride = sizeof(VertexPositionColor);
    const UINT offset = 0;
    context->IASetVertexBuffers(
        0,
        1,
        m_vertexBuffer.GetAddressOf(),
        &stride,
        &offset
        );
    context->IASetIndexBuffer(
        m_indexBuffer.Get(),
        DXGI_FORMAT_R16_UINT, // Each index is one 16-bit unsigned integer (short).
        0
        );
    context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_1_CONTROL_POINT_PATCHLIST);
    //context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    context->IASetInputLayout(m_inputLayout.Get());

    // Attach the vertex shader.
    context->VSSetShader(
        m_vertexShader.Get(),
        nullptr,
        0
        );
    // Apply the model constant buffer to the vertex shader.
    context->VSSetConstantBuffers(
        0,
        1,
        m_modelConstantBuffer.GetAddressOf()
        );

    // Attach the hull shader.
    context->HSSetShader(
        m_hullShader.Get(),
        nullptr,
        0
        );

    // Attach the domain shader.
    context->DSSetShader(
        m_domainShader.Get(),
        nullptr,
        0
        );

    // Apply the model constant buffer to the domain shader.
    context->DSSetConstantBuffers(
        0,
        1,
        m_modelConstantBuffer.GetAddressOf()
        );

    if (!m_usingVprtShaders)
    {
        // On devices that do not support the D3D11_FEATURE_D3D11_OPTIONS3::
        // VPAndRTArrayIndexFromAnyShaderFeedingRasterizer optional feature,
        // a pass-through geometry shader is used to set the render target 
        // array index.
        context->GSSetShader(
            m_geometryShader.Get(),
            nullptr,
            0
            );
    }

    // Attach the pixel shader.
    context->PSSetShader(
        m_pixelShader.Get(),
        nullptr,
        0
        );

    // Draw the objects.
    context->DrawIndexedInstanced(
        m_indexCount,   // Index count per instance.
        2,              // Instance count.
        0,              // Start index location.
        0,              // Base vertex location.
        0               // Start instance location.
        );
}

void SpinningMoleculeRenderer::CreateDeviceDependentResources()
{
    // Trying to read a PDB file
    using namespace Windows::Web::Http;
    HttpClient^ httpClient = ref new HttpClient();
    auto getPdbTask = create_task(httpClient->GetStringAsync(
        ref new Windows::Foundation::Uri(L"http://files.rcsb.org/download/1crn.pdb")))
    .then([] (task<Platform::String^> task)
    {
        using namespace maral;
        using namespace maral::bootstrap::pdb_multimodel;

        Platform::String^ text = task.get();
        std::wstring textW(text->Data());
        //OutputDebugString(textW.c_str());
        std::string textA(textW.begin(), textW.end());
        std::istringstream is(textA);
        auto rt = make<root>();
        is >> rt;
        //std::ostringstream os;
        //os << delimiters('[', ']') << separator(' ')
        //   << shallow << rt << std::endl;
        //auto temp = os.str();
        //std::wstring out(temp.begin(), temp.end());
        //OutputDebugString(out.c_str());
    });

    m_usingVprtShaders = m_deviceResources->GetDeviceSupportsVprt();

    // On devices that do support the D3D11_FEATURE_D3D11_OPTIONS3::
    // VPAndRTArrayIndexFromAnyShaderFeedingRasterizer optional feature
    // we can avoid using a pass-through geometry shader to set the render
    // target array index, thus avoiding any overhead that would be 
    // incurred by setting the geometry shader stage.
    std::wstring vertexShaderFileName = m_usingVprtShaders ? L"ms-appx:///VprtVertexShader.cso" : L"ms-appx:///VertexShader.cso";

    // Load shaders asynchronously.
    task<std::vector<byte>> loadVSTask = DX::ReadDataAsync(vertexShaderFileName);
    task<std::vector<byte>> loadHSTask = DX::ReadDataAsync(L"ms-appx:///HullShader.cso");
    task<std::vector<byte>> loadDSTask = DX::ReadDataAsync(L"ms-appx:///DomainShader.cso");
    task<std::vector<byte>> loadPSTask = DX::ReadDataAsync(L"ms-appx:///PixelShader.cso");

    task<std::vector<byte>> loadGSTask;
    if (!m_usingVprtShaders)
    {
        // Load the pass-through geometry shader.
        loadGSTask = DX::ReadDataAsync(L"ms-appx:///GeometryShader.cso");
    }

    // After the vertex shader file is loaded, create the shader and input layout.
    task<void> createVSTask = loadVSTask.then([this] (const std::vector<byte>& fileData)
    {
        DX::ThrowIfFailed(
            m_deviceResources->GetD3DDevice()->CreateVertexShader(
                &fileData[0],
                fileData.size(),
                nullptr,
                &m_vertexShader
                )
            );

        static const D3D11_INPUT_ELEMENT_DESC vertexDesc[] =
        {
            { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
            { "COLOR",    0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        };

        DX::ThrowIfFailed(
            m_deviceResources->GetD3DDevice()->CreateInputLayout(
                vertexDesc,
                ARRAYSIZE(vertexDesc),
                &fileData[0],
                fileData.size(),
                &m_inputLayout
                )
            );
    });

    // After the hull shader file is loaded, create the shader and input layout.
    task<void> createHSTask = loadHSTask.then([this] (const std::vector<byte>& fileData)
    {
        DX::ThrowIfFailed(
            m_deviceResources->GetD3DDevice()->CreateHullShader(
                &fileData[0],
                fileData.size(),
                nullptr,
                &m_hullShader
                )
            );
    });

    // After the domain shader file is loaded, create the shader and input layout.
    task<void> createDSTask = loadDSTask.then([this] (const std::vector<byte>& fileData)
    {
        DX::ThrowIfFailed(
            m_deviceResources->GetD3DDevice()->CreateDomainShader(
                &fileData[0],
                fileData.size(),
                nullptr,
                &m_domainShader
                )
            );
    });

    // After the pixel shader file is loaded, create the shader and constant buffer.
    task<void> createPSTask = loadPSTask.then([this] (const std::vector<byte>& fileData)
    {
        DX::ThrowIfFailed(
            m_deviceResources->GetD3DDevice()->CreatePixelShader(
                &fileData[0],
                fileData.size(),
                nullptr,
                &m_pixelShader
                )
            );

        const CD3D11_BUFFER_DESC constantBufferDesc(sizeof(ModelConstantBuffer), D3D11_BIND_CONSTANT_BUFFER);
        DX::ThrowIfFailed(
            m_deviceResources->GetD3DDevice()->CreateBuffer(
                &constantBufferDesc,
                nullptr,
                &m_modelConstantBuffer
                )
            );
    });

    task<void> createGSTask;
    if (!m_usingVprtShaders)
    {
        // After the pass-through geometry shader file is loaded, create the shader.
        createGSTask = loadGSTask.then([this] (const std::vector<byte>& fileData)
        {
            DX::ThrowIfFailed(
                m_deviceResources->GetD3DDevice()->CreateGeometryShader(
                    &fileData[0],
                    fileData.size(),
                    nullptr,
                    &m_geometryShader
                    )
                );
        });
    }

    // Once all shaders are loaded, create the mesh.
    task<void> shaderTaskGroup = m_usingVprtShaders ? (createPSTask && createVSTask) : (createPSTask && createVSTask && createGSTask);
    task<void> createMoleculeTask  = shaderTaskGroup.then([this] ()
    {
        // Load mesh vertices. Each vertex has a position and a color.
        // Note that the molecule size has changed from the default DirectX app
        // template. Windows Holographic is scaled in meters, so to draw the
        // molecule at a comfortable size we made the molecule width 0.2 m (20 cm).
        static const VertexPositionColor moleculeVertices[] =
        {
            { XMFLOAT3(-0.1f, -0.1f, -0.1f), XMFLOAT3(0.5f, 0.5f, 0.5f) },
            { XMFLOAT3(-0.1f, -0.1f,  0.1f), XMFLOAT3(0.0f, 0.0f, 1.0f) },
            { XMFLOAT3(-0.1f,  0.1f, -0.1f), XMFLOAT3(0.0f, 1.0f, 0.0f) },
            { XMFLOAT3(-0.1f,  0.1f,  0.1f), XMFLOAT3(0.0f, 1.0f, 1.0f) },
            { XMFLOAT3( 0.1f, -0.1f, -0.1f), XMFLOAT3(1.0f, 0.0f, 0.0f) },
            { XMFLOAT3( 0.1f, -0.1f,  0.1f), XMFLOAT3(1.0f, 0.0f, 1.0f) },
            { XMFLOAT3( 0.1f,  0.1f, -0.1f), XMFLOAT3(1.0f, 1.0f, 0.0f) },
            { XMFLOAT3( 0.1f,  0.1f,  0.1f), XMFLOAT3(1.0f, 1.0f, 1.0f) },
        };

        D3D11_SUBRESOURCE_DATA vertexBufferData = {0};
        vertexBufferData.pSysMem = moleculeVertices;
        vertexBufferData.SysMemPitch = 0;
        vertexBufferData.SysMemSlicePitch = 0;
        const CD3D11_BUFFER_DESC vertexBufferDesc(sizeof(moleculeVertices), D3D11_BIND_VERTEX_BUFFER);
        DX::ThrowIfFailed(
            m_deviceResources->GetD3DDevice()->CreateBuffer(
                &vertexBufferDesc,
                &vertexBufferData,
                &m_vertexBuffer
                )
            );

        // Load mesh indices. Each trio of indices represents
        // a triangle to be rendered on the screen.
        // For example: 2,1,0 means that the vertices with indexes
        // 2, 1, and 0 from the vertex buffer compose the
        // first triangle of this mesh.
        // Note that the winding order is clockwise by default.
        //static const unsigned short moleculeIndices [] =
        //{
        //    2,1,0, // -x
        //    2,3,1,

        //    6,4,5, // +x
        //    6,5,7,

        //    0,1,5, // -y
        //    0,5,4,

        //    2,6,7, // +y
        //    2,7,3,

        //    0,4,6, // -z
        //    0,6,2,

        //    1,3,7, // +z
        //    1,7,5,
        //};

        static const unsigned short moleculeIndices [] =
        {
            0,1,2,3,4,5,6,7,
        };

        m_indexCount = ARRAYSIZE(moleculeIndices);

        D3D11_SUBRESOURCE_DATA indexBufferData = {0};
        indexBufferData.pSysMem          = moleculeIndices;
        indexBufferData.SysMemPitch      = 0;
        indexBufferData.SysMemSlicePitch = 0;
        const CD3D11_BUFFER_DESC indexBufferDesc(sizeof(moleculeIndices), D3D11_BIND_INDEX_BUFFER);
        DX::ThrowIfFailed(
            m_deviceResources->GetD3DDevice()->CreateBuffer(
                &indexBufferDesc,
                &indexBufferData,
                &m_indexBuffer
                )
            );
    });

    // Once the molecule is loaded, the object is ready to be rendered.
    createMoleculeTask.then([this] ()
    {
        m_loadingComplete = true;
    });
}

void SpinningMoleculeRenderer::ReleaseDeviceDependentResources()
{
    m_loadingComplete  = false;
    m_usingVprtShaders = false;
    m_vertexShader.Reset();
    m_inputLayout.Reset();
    m_pixelShader.Reset();
    m_geometryShader.Reset();
    m_modelConstantBuffer.Reset();
    m_vertexBuffer.Reset();
    m_indexBuffer.Reset();
}
