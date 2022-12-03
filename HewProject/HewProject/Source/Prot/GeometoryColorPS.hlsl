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
	float gridU;
	float gridV;
	float d[2];
}
float4 main(PS_IN pin) : SV_TARGET
{
	float4 color = float4(r, g, b, a);
	float2 mGrid;
	mGrid.x = floor(abs(pin.uv.x) * gridU);
	mGrid.y = floor(abs(pin.uv.y) * gridV);

	float mid = fmod(mGrid.x + mGrid.y, 2.0f);

	color.rgb = color.rgb - mid * 0.2f;



	//color.rgb = mul(colorGrid, color.rgb);
	return color;
}