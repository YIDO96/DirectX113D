#ifndef _GLOBAL_FX_ // if not define
#define _GLOBAL_FX_

/////////////////
// ConstBuffer //
/////////////////

// 자주 바뀌지 않는 전역 변수들을 위한 상수 버퍼
cbuffer GlobalBuffer
{
    matrix V;
    matrix P;
    matrix VP;
    matrix VInv;
};

// 자주 바뀌는 개체별 전역 변수들을 위한 상수 버퍼
cbuffer TransformBuffer
{
    matrix W;
};


////////////////
// VertexData //
////////////////

struct Vertex
{
    float4 position : POSITION;
};

struct VertexTexture
{
    float4 position : POSITION;
    float2 uv : TEXCOORD;
};

struct VertexColor
{
    float4 position : POSITION;
    float4 color : COLOR;
};

struct VertexTetrueNormal
{
    float4 position : POSITION;
    float2 uv : TEXCOORD;
    float3 normal : NOERMAL;
};

struct VertexTetrueNormalTangent
{
    float4 position : POSITION;
    float2 uv : TEXCOORD;
    float3 normal : NOERMAL;
    float3 tangent : TANGENT;
};

struct VertexTetrueNormalTangentBlend
{
    float4 position : POSITION;
    float2 uv : TEXCOORD;
    float3 normal : NOERMAL;
    float3 tangent : TANGENT;
    float4 blendIndices : BLENDINDICES;
    float4 blendWeights : BLENDWEIGHT;
};


//////////////////
// VertexOutput //
//////////////////

struct VertexOutput
{
    float4 position : SV_POSITION; //SV : System Value
    float2 uv : TEXCOORD;
    float3 normal : NORMAL;
};

struct MeshOutput
{
    float4 position : SV_POSITION; //SV : System Value
    float3 worldPosition : POSITION1; 
    float2 uv : TEXCOORD;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
};


//////////////////
// SamplerState //
//////////////////

SamplerState LinearSampler
{
    Filter = MIN_MAG_MIP_LINEAR;
    AddressU = Wrap;
    AddressV = Wrap;
};

SamplerState PointSampler
{
    Filter = MIN_MAG_MIP_POINT;
    AddressU = Wrap;
    AddressV = Wrap;
};


/////////////////////
// RasterizerState //
/////////////////////

RasterizerState FillModeWireFrame
{
    FillMode = Wireframe;
};

RasterizerState FrontCounterClockwiseTrue
{
    FrontCounterClockwise = true;
};

///////////
// Macro //
///////////

#define PASS_VP(name, vs, ps)                               \
pass name                                                   \
    {                                                       \
        SetVertexShader( CompileShader( vs_5_0, vs() ) );   \
        SetPixelShader( CompileShader( ps_5_0, ps() ) );    \
    }

#define PASS_RS_VP(name, rs, vs, ps)                        \
pass name                                                   \
{                                                           \
    SetRasterizerState(rs);                                 \
    SetVertexShader(CompileShader(vs_5_0, vs()));           \
    SetPixelShader(CompileShader(ps_5_0, ps()));            \
}

//////////////
// Function //
//////////////

float3 CameraPosition()
{
    return VInv._41_42_43;
}

#endif