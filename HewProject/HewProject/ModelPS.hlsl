struct PS_IN {
	float4 pos : SV_POSITION;
	float2 uv : TEXCOORD0;
	float3 normal : NORMAL0;
};

//cbuffer color
Texture2D tex : register(t0);
SamplerState samp : register(s0);

float4 main(PS_IN pin) : SV_TARGET
{
	float3 lightNormal = float3(1, 1, 0);
	lightNormal = normalize(lightNormal);

	float4 color = tex.Sample(samp, pin.uv);
	float tmp = dot(pin.normal, lightNormal);
	tmp *= 0.4f;
	tmp += 0.7f;
	color = float4(color.x * tmp, color.y * tmp, color.z * tmp, color.w);
	return color;
}