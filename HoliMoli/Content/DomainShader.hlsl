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

struct DS_OUTPUT
{
    min16float4 pos     : SV_POSITION;
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
    float EdgeTessFactor[4]   : SV_TessFactor; // 4 for quad
    float InsideTessFactor[2] : SV_InsideTessFactor; // 2 for quad
};

#define NUM_CONTROL_POINTS 1

[domain("quad")]
DS_OUTPUT main(
    HS_CONSTANT_DATA_OUTPUT input,
    float2 UV : SV_DomainLocation,
    const OutputPatch<HS_CONTROL_POINT_OUTPUT, NUM_CONTROL_POINTS> quad)
{
    DS_OUTPUT output;

    float pi2 = 6.28318530;
    float pi = pi2 / 2.0f;
    float R = 0.1;
    float fi = pi * UV.x;
    float theta = pi2 * UV.y;
    float sinFi, cosFi, sinTheta, cosTheta;
    sincos(fi, sinFi, cosFi);
    sincos(theta, sinTheta, cosTheta);

    float3 spherePosition = float3(R * sinFi * cosTheta, R * sinFi * sinTheta, R * cosFi);

    // Note which view this vertex has been sent to. Used for matrix lookup.
    // Taking the modulo of the instance ID allows geometry instancing to be used
    // along with stereo instanced drawing; in that case, two copies of each 
    // instance would be drawn, one for left and one for right.
    int idx = quad[0].instId;

    float4 pos = float4(spherePosition, 1.0f);
    pos += quad[0].pos;
    pos = mul(pos, model);
    pos = mul(pos, viewProjection[idx]);

    output.pos = (min16float4)pos;
    //output.color = (min16float3)(normalize(spherePosition) + 0.4);
    output.color  = quad[0].color;
    output.instId = quad[0].instId;

    return output;
}
