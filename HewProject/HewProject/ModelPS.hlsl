struct PS_IN {
	float4 pos : SV_POSITION;
	float2 uv : TEXCOORD0;
	float3 normal : NORMAL;
};

Texture2D tex : register(t0);
SamplerState samp : register(s0);

float4 main(PS_IN pin) : SV_TARGET
{
	float4 color = tex.Sample(samp, pin.uv);
	float4 output = float4(pin.normal.x, pin.normal.y, pin.normal.z, 1);
	return output;
	//color = mul(color, pin.col);
	//return pin.col;
}