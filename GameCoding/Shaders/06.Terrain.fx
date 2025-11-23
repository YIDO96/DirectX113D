matrix World;
matrix View;
matrix Projection;
Texture2D Texture0;

struct VertexInput
{
    float4 position : POSITION;
    float2 uv : TEXCOORD;
};

struct VertexOutput
{
    float4 position : SV_POSITION; //SV : System Value
    float2 uv : TEXCOORD;
};

VertexOutput VS(VertexInput input)
{
    VertexOutput output;
    output.position = mul(input.position, World);
    output.position = mul(output.position, View);
    output.position = mul(output.position, Projection);
    
    
    output.uv = input.uv;
    
    
    return output;
}

// Filter   : 확대/ 축소 시 텍스처 픽셀을 어떻게 보간할 것인지 결정
// Address  : 텍스처 좌표가 0~1 범위를 벗어날 때 어떻게 처리할 것인지 결정
SamplerState Sampler0
{
    AddressU = Wrap;
    AddressV = Wrap;
};

float4 PS(VertexOutput input) : SV_TARGET
{
    return Texture0.Sample(Sampler0, input.uv);
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