matrix World;
matrix View;
matrix Projection;
Texture2D Texture0;
uint Address;

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

SamplerState Sampler0;

SamplerState SamplerAddressWrap
{
    AddressU = Wrap;
    AddressV = Wrap;
};

SamplerState SamplerAddressMirror
{
    AddressU = Mirror;
    AddressV = Mirror;
};

SamplerState SamplerAddressClamp
{
    AddressU = Clamp;
    AddressV = Clamp;
};

SamplerState SamplerAddressBorder
{
    AddressU = Border;
    AddressV = Border;
    BorderColor = float4(1.0f, 0.0f, 0.0f, 1.0f); // Red
};

float4 PS(VertexOutput input) : SV_TARGET
{
    if (Address == 0)
    {
        return Texture0.Sample(SamplerAddressWrap, input.uv);
    }
    if (Address == 1)
    {
        return Texture0.Sample(SamplerAddressMirror, input.uv);
    }
    if (Address == 2)
    {
        return Texture0.Sample(SamplerAddressClamp, input.uv);
    }
    if (Address == 3)
    {
        return Texture0.Sample(SamplerAddressBorder, input.uv);
    }
    
    return Texture0.Sample(Sampler0, input.uv);
}




technique11 T0
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_5_0, VS() ) );
        SetPixelShader( CompileShader( ps_5_0, PS() ) );
    }
}