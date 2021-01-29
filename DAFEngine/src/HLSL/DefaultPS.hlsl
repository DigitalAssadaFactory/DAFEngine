struct Light
{
    float3 position;
    float3 direction;
    float3 color;
    float intensity;
    int type;
};

struct Input
{
    float4 position : SV_POSITION;
    float4 uv : TEXCOORD;
    float4 color : COLOR;
    float4 normal : NORMAL;
};

StructuredBuffer<Light> lights : register(t0);
Texture2D tex : register(t1);
Texture2D tex2 : register(t2);
SamplerState state : register(s0);

float4 main(Input i) : SV_TARGET
{
    return 1;

    float3 final = float3(0, 0, 0);
    float4 texNormal = float4(tex.Sample(state, float2(i.uv.x, i.uv.y)).rgb, 1.0f);
    float4 colorTex = float4(tex2.Sample(state, float2(i.uv.x, i.uv.y)).rgb, 1.0f);
    return texNormal;
    texNormal = normalize(texNormal);
    
    for (int it = 1; it < lights[0].type; ++it)
    {
        if (lights[it].type == 0) // directional
        {
            final +=
			(
			   lights[it].color
			   * max(dot(texNormal.rgb,normalize(lights[it].position)), 0)
			) * lights[it].intensity;
        }
        else if (lights[it].type == 1) // point
        {
            return float4(1, 1, 1, 1);
        }
        else if (lights[it].type == 1) // spot
        {
            return float4(1, 1, 1, 1);
        }

    }
        
    return float4(final, 1);

    //return tex.Sample(state, float2(i.uv.x, i.uv.y));
    //return tex.Sample(state, float2(i.uv.x, i.uv.y));
	//float4 light = normalize(float4(30.0f, 30.0f, 15.0f, 1.0f));
	//i.normal.w = 1.0f;
	//return saturate(i.color * normalize(dot(i.normal, light))) + i.color * float4(0.3f,0.3f,0.3f,1.0f);
}