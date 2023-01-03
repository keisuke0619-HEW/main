struct VS_IN
{
	float3 pos : POSITION0;
	float3 normal : NORMAL;
	float2 uv : TEXCOORD;
	float4 weight : WEIGHT;
	uint4 index : INDEX;
};
struct VS_OUT
{
	float4 pos : SV_POSITION;
	float2 uv : TEXCOORD0;
	float4 col : COLOR0;
};

cbuffer WVP : register(b0)
{
	float4x4 world;
	float4x4 view;
	float4x4 proj;
};
cbuffer Anime : register(b1)
{
	float4x4 bones[200];
};

VS_OUT main(VS_IN vin)
{
	VS_OUT vout;
	vout.pos = float4(vin.pos, 1.0f);
	float4x4 mat =
		bones[vin.index.x] * vin.weight.x +
		bones[vin.index.y] * vin.weight.y +
		bones[vin.index.z] * vin.weight.z +
		bones[vin.index.w] * vin.weight.w;
	vout.pos = mul(vout.pos, mat);

	vout.pos = mul(vout.pos, world);
	vout.pos = mul(vout.pos, view);
	vout.pos = mul(vout.pos, proj);
	vout.pos.x += vin.normal.x;
	vout.uv = vin.uv;

	float3 light = (-1, -1, 1);
	float col;
	float3 nor;
	nor = mul(vin.normal, world).xyz;
	nor = normalize(nor);
	light = normalize(light);
	col = dot(nor, light);
	col = saturate(col);
	col = col * 0.5f + 0.5f;
	vout.col = float4(col, col, col, 1.0f);

	return vout;
}