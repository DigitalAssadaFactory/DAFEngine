struct Input
{
    float4 position : SV_POSITION;
    float4 uv : TEXCOORD;
    float4 color : COLOR;
    float4 normal : NORMAL;
};

Texture2D tex : register(t0);
SamplerState state : register(s0);

float4 main(Input i) : SV_TARGET
{
    float4 sun = float4(0.0f, 1.0f, 0.0f, 1.0f);
    float4 white = float4(1.0f, 1.0f, 1.0f, 1.0f);
    float4 final = white * dot(i.normal, normalize(sun));
    final.a = 1.0f;
    return final;

    //return tex.Sample(state, float2(i.uv.x, i.uv.y));
	//float4 light = normalize(float4(30.0f, 30.0f, 15.0f, 1.0f));
	//i.normal.w = 1.0f;
	//return saturate(i.color * normalize(dot(i.normal, light))) + i.color * float4(0.3f,0.3f,0.3f,1.0f);
}