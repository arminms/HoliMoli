// Per-vertex data from the domain shader.
struct GeometryShaderInput
{
    min16float4 screenPos : SV_POSITION;
    min16float3 worldPos  : POSITION0;
    min16float3 normal    : NORMAL0;
    min16float3 color     : COLOR0;
    uint        instId    : TEXCOORD0;
};

// Per-vertex data passed to the rasterizer.
struct GeometryShaderOutput
{
    min16float4 screenPos : SV_POSITION;
    min16float3 worldPos  : POSITION0;
    min16float3 normal    : NORMAL0;
    min16float3 color     : COLOR0;
    uint        rtvId     : SV_RenderTargetArrayIndex;
};

// This geometry shader is a pass-through that leaves the geometry unmodified 
// and sets the render target array index.
[maxvertexcount(3)]
void main(triangle GeometryShaderInput input[3], inout TriangleStream<GeometryShaderOutput> outStream)
{
    GeometryShaderOutput output;
    [unroll(3)]
    for (int i = 0; i < 3; ++i)
    {
        output.screenPos = input[i].screenPos;
        output.worldPos  = input[i].worldPos;
        output.normal    = input[i].normal;
        output.color     = input[i].color;
        output.rtvId     = input[i].instId;
        outStream.Append(output);
    }
}
