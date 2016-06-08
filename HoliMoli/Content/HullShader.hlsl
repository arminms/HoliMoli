// A constant buffer that stores the model transform.
cbuffer ModelConstantBuffer : register(b0)
{
    float4x4 model;
};

// A constant buffer that stores each set of view and projection matrices in column-major format.
cbuffer ViewProjectionConstantBuffer : register(b1)
{
    float4x4 viewProjection[2];
};

// Input control point
struct VS_CONTROL_POINT_OUTPUT
{
    min16float4 pos     : POSITION;
    min16float3 color   : COLOR0;
    uint instId         : TEXCOORD0;
};

// Output control point
struct HS_CONTROL_POINT_OUTPUT
{
    min16float4 pos     : POSITION;
    min16float3 color   : COLOR0;
    uint instId         : TEXCOORD0;
};

// Output patch constant data.
struct HS_CONSTANT_DATA_OUTPUT
{
    float EdgeTessFactor[4]    : SV_TessFactor; // 4 for quad
    float InsideTessFactor[2]  : SV_InsideTessFactor;   // 2 for quad
};

// This value should match the call to IASetPrimitiveTopology()
#define NUM_CONTROL_POINTS 1

// TODO: adding dynamic tessellation factors
#define TESS_AMOUNT 15

// Patch Constant Function
HS_CONSTANT_DATA_OUTPUT CalcHSPatchConstants(
    InputPatch<VS_CONTROL_POINT_OUTPUT, NUM_CONTROL_POINTS> ip,
    uint PatchID : SV_PrimitiveID)
{
    HS_CONSTANT_DATA_OUTPUT output;

    float4 pos = mul(ip[0].pos, model);
    pos = mul(pos, viewProjection[ip[0].instId]);
    float tessFactor = clamp(-5.0f * pos[2] + 25.0f, 5, 25);

    // TODO: adding dynamic tessellation factors
    output.EdgeTessFactor[0] =
        output.EdgeTessFactor[1] =
        output.EdgeTessFactor[2] = 
        output.EdgeTessFactor[3] =
        output.InsideTessFactor[0] = 
        output.InsideTessFactor[1] = tessFactor;

    return output;
}

[domain("quad")]
[partitioning("fractional_odd")]
[outputtopology("triangle_cw")]
[outputcontrolpoints(NUM_CONTROL_POINTS)]
[patchconstantfunc("CalcHSPatchConstants")]
HS_CONTROL_POINT_OUTPUT main( 
    InputPatch<VS_CONTROL_POINT_OUTPUT, NUM_CONTROL_POINTS> ip, 
    uint i : SV_OutputControlPointID,
    uint PatchID : SV_PrimitiveID )
{
    HS_CONTROL_POINT_OUTPUT output;

    output.pos    = ip[i].pos;
    output.color  = ip[i].color;
    output.instId = ip[i].instId;

    return output;
}
