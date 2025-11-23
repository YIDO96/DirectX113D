#include "00.Global.fx"

float4 MaterialEmissive;


MeshOutput VS(VertexTetrueNormal input)
{
    MeshOutput output;
    output.position = mul(input.position, W);
    output.worldPosition = input.position;
    output.position = mul(output.position, VP);
    output.uv = input.uv;
    output.normal = mul(input.normal, (float3x3) W);
    
    return output;
}

// Emissive
// 외각선 구할때 사용(림라이트)

float4 PS(MeshOutput input) : SV_TARGET
{
    float3 cameraPosition = -V._41_42_43;
    float3 E = normalize(cameraPosition - input.worldPosition);
    
    float value = saturate(dot(E, input.normal));
    float emissive = 1.0f - value;
    
    // smoothstep(min, max , x) : x가 [min, max] 구간에 있을 때 0~1로 Hermite 보간, 두 값 사이를 부드럽게 전환
    // ex) 두 색상을 부드럽게 혼합
    emissive = smoothstep(0.0f, 1.0f, emissive);
    emissive = pow(emissive, 1.f); // 감마 보정
    
    
    float4 color = MaterialEmissive * emissive;
    return color;
}

technique11 T0
{
    PASS_VP(P0, VS, PS)
}