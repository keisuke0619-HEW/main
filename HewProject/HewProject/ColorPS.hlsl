struct PS_IN {
	float4 pos : SV_POSITION;
	float2 uv : TEXCOORD0;
	float4 wPos : TEXCOORD1;
};

cbuffer Color : register (b0)
{
	float r;
	float g;
	float b;
	float a;
}
float4 main(PS_IN pin) : SV_TARGET
{
	float4 color = float4(r, g, b, a);
	return color;
}