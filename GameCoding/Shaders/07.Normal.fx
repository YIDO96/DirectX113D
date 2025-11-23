matrix World;
matrix View;
matrix Projection;
Texture2D Texture0;
float3 LightDir;

struct VertexInput
{
    float4 position : POSITION;
    float2 uv : TEXCOORD;
    float3 normal : NORMAL;
};

struct VertexOutput
{
    float4 position : SV_POSITION; //SV : System Value
    float2 uv : TEXCOORD;
    float3 normal : NORMAL;
};

VertexOutput VS(VertexInput input)
{
    VertexOutput output;
    output.position = mul(input.position, World);
    output.position = mul(output.position, View);
    output.position = mul(output.position, Projection);
    
    
    output.uv = input.uv;
    output.normal = mul(input.normal, (float3x3) World);
    
    return output;
}

// Filter   : 확대/ 축소 시 텍스처 픽셀을 어떻게 보간할 것인지 결정
// Address  : 텍스처 좌표가 0~1 범위를 벗어날 때 어떻게 처리할 것인지 결정
SamplerState Sampler0;


float4 PS(VertexOutput input) : SV_TARGET
{
    float3 normal = normalize(input.normal);
    float3 light = -LightDir;
    
    //return float4(1, 1, 1, 1) * dot(light, normal); // 내적 연산
    
    return Texture0.Sample(Sampler0, input.uv) * dot(light, normal);
}

RasterizerState FillModeWireframe
{
    FillMode = Wireframe;
};


technique11 T0
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_5_0, VS() ) );
        SetPixelShader( CompileShader( ps_5_0, PS() ) );
    }
    pass P1
    {
        SetRasterizerState(FillModeWireframe);

        SetVertexShader( CompileShader( vs_5_0, VS() ) );
        SetPixelShader( CompileShader( ps_5_0, PS() ) );
    }
}