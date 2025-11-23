#include "00.Global.fx"
#include "00.Light.fx"

float4 MaterialEmissive;


MeshOutput VS(VertexTetrueNormal input)
{
    MeshOutput output;
    output.position = mul(input.position, W);
    output.worldPosition = input.position.xyz;
    output.position = mul(output.position, VP);
    output.uv = input.uv;
    output.normal = mul(input.normal, (float3x3) W);
    
    return output;
}

// Emissive
// 외각선 구할때 사용(림라이트)

float4 PS(MeshOutput input) : SV_TARGET
{
    float4 color = ComputeLight(input.normal, input.uv, input.worldPosition);
    
    return color;
}

technique11 T0
{
    PASS_VP(P0, VS, PS)
}