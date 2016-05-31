// Input control point
struct VS_CONTROL_POINT_OUTPUT
{
    float3 vPosition : WORLDPOS;
};

// Output control point
struct HS_CONTROL_POINT_OUTPUT
{
    float3 vPosition : WORLDPOS; 
};

// Output patch constant data.
struct HS_CONSTANT_DATA_OUTPUT
{
    float EdgeTessFactor[4]    : SV_TessFactor; // 4 for quad
    float InsideTessFactor[2]  : SV_InsideTessFactor;   // 2 for quad
};

#define NUM_CONTROL_POINTS 4

// Patch Constant Function
HS_CONSTANT_DATA_OUTPUT CalcHSPatchConstants(
    InputPatch<VS_CONTROL_POINT_OUTPUT, NUM_CONTROL_POINTS> ip,
    uint PatchID : SV_PrimitiveID)
{
    HS_CONSTANT_DATA_OUTPUT Output;

    Output.EdgeTessFactor[0] =
        Output.EdgeTessFactor[1] =
        Output.EdgeTessFactor[2] = 
        Output.EdgeTessFactor[3] =
        Output.InsideTessFactor[0] = 
        Output.InsideTessFactor[1] = 5; // calculate dynamic tessellation factors later

    return Output;
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
    HS_CONTROL_POINT_OUTPUT Output;

    Output.vPosition = ip[i].vPosition;

    return Output;
}
