#include "00.Global.fx"

float3 LightDir;            // 조명의 방향
float4 LightSpecular;       // 조명의 반사광
float4 MaterialSpecular;    // 재질의 반사광 특성

Texture2D DiffuseMap;


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

// Specular (반사광)
// 한방향으로 완전히 반사되는 빛 (Phong)


float4 PS(MeshOutput input) : SV_TARGET
{
    //float3 R = reflect(LightDir, normalize(input.normal));
    // 빛의 반사벡터
    float3 R = LightDir - (2 * input.normal * dot(LightDir, input.normal));
    
    // 카메라 위치벡터
    float3 cameraPosition = -V._41_42_43;
    // 물체 -> 카메라 방향벡터
    float3 E = normalize(cameraPosition - input.worldPosition);
    
    float value = saturate(dot(R, E)); // saturate : clamp(0 ~ 1)
    float specular = pow(value, 5); // 값이 클수록 범위가 작아짐 -> 이유 : value값을 saturate로 제한
    
    float color = LightSpecular * MaterialSpecular * specular;
    return color;
}

technique11 T0
{
    PASS_VP(P0, VS, PS)
}