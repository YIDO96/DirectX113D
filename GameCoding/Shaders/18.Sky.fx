#include "00.Global.fx"
#include "00.Light.fx"

struct VS_OUT
{
    float4 position : SV_POSITION;
    float2 uv : TEXCOORD;
};


VS_OUT VS(VertexTetrueNormalTangent input)
{
    VS_OUT output;
	
    // Local -> World -> View -> Projection
    
    // 회전값을 고정시키기 위해서 w값은 0으로 가져가기
    float4 viewPos = mul(float4(input.position.xyz, 0), V);
    float4 clipSpacePos = mul(viewPos, P);
    
    output.position = clipSpacePos.xyzw;
    // Rasterizer단계에서 xyzw에다가 w를 나눠주기 때문에 z값에 w값을 넣어서 z값을 무조건 1이 나오게끔 설정
    output.position.z = output.position.w * 0.9999999f;
    
    output.uv = input.uv;
	
	return output;
}

float4 PS(VS_OUT input) : SV_TARGET
{
	float4 color = DiffuseMap.Sample(LinearSampler, input.uv);
	
	return color;
}

technique11 T0
{
    pass P0
    {
        SetRasterizerState(FrontCounterClockwiseTrue);
        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetPixelShader(CompileShader(ps_5_0, PS()));
    }
};