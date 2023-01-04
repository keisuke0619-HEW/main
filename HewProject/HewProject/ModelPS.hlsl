struct PS_IN {
	float4 pos : SV_POSITION;
	float2 uv : TEXCOORD0;
	float4 col : COLOR0;
};

Texture2D tex : register(t0);
SamplerState samp : register(s0);

float4 main(PS_IN pin) : SV_TARGET
{
	float4 color = tex.Sample(samp, pin.uv);
	return color;
	//color = mul(color, pin.col);
	//return pin.col;
}