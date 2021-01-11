
cbuffer MatrixBuffer : register(b0)
{
    matrix mvp;
};

struct Light
{
	float3 position;
	float3 direction;
	float3 color;
	float intensity;
	int type;
};

StructuredBuffer<float4x4> transform : register(t0);
//StructuredBuffer<Light> light : register(t1);

struct Input {
	float4 position : POSITION;
	float4 uv : TEXCOORD;
	float4 color : COLOR;
	float4 normal : NORMAL;
};

struct Output {
	float4 position : SV_POSITION;
	float4 uv : TEXCOORD;
	float4 color : COLOR;
	float4 normal : NORMAL;
};

Output main(Input i, uint id : SV_InstanceID)
{
	Output o;
    //o.position = mul(transform[0] * transform[id+1], i.position);
	
    float4x4 finalMatrix = mul(transform[0], transform[id]);
	
    //float4x4 finalMatrix = transform[id + 1];
	o.position = mul(finalMatrix, i.position);
    o.position = mul(mvp, o.position);
    o.color = i.color;
    o.uv = i.uv;
	o.normal = normalize(i.normal);
		
    return o;
}