// #include "myshader.hlsli"

struct Input
{
    float4 Pos : POSITION;
    float4 Tex : TEXCOORD;
};

struct Output
{
    float4 Pos : SV_POSITION;
    float4 Tex : TEXCOORD;
};

Output OldFilm_VS(Input _Input)
{
    Output NewOutPut = (Output)0;
    NewOutPut.Pos = _Input.Pos;
    NewOutPut.Tex = _Input.Tex;
    return NewOutPut;
}

Texture2D Tex : register(t0);
SamplerState Smp : register(s0);
float4 OldFilm_PS(Output _Input) : SV_Target0
{
    float2 CurUV = _Input.Tex.xy;

	float4 Test = Tex.Sample(Smp, CurUV);

    return Test;
}
