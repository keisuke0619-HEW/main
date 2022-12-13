#include "Easing.hpp"
#include <math.h>
#include <macro.hpp>
#include<Windows.h>

// https://easings.net/ja



float Utility::InSine(float x)
{
    return 1.0f - cosf((x * PI) / 2);
}

float Utility::OutSine(float x)
{
    return sinf((x * PI) / 2);
}

float Utility::InOutSine(float x)
{
    return -(cosf(PI * x) - 1) / 2;
}

float Utility::InCubic(float x)
{
    return  x * x * x;
}

float Utility::OutCubic(float x)
{
    return  1 - powf(1 - x, 3);
}

float Utility::InOutCubic(float x)
{
    return x < 0.5f ? 4 * x * x * x : 1 - powf(-2 * x + 2, 3) / 2;
}

float Utility::InQuint(float x)
{
    return  x * x * x * x * x;
}

float Utility::OutQuint(float x)
{
    return 1 - powf(1 - x, 5);
}

float Utility::InOutQuint(float x)
{
    return x < 0.5f ? 16 * x * x * x * x * x : 1 - powf(-2 * x + 2, 5) / 2;
}

float Utility::InCirc(float x)
{
    return 1 - sqrtf(1 - powf(x, 2));
}

float Utility::OutCirc(float x)
{
    return sqrtf(1 - powf(x - 1, 2));
}

float Utility::InOutCirc(float x)
{
    return x < 0.5f
		? (1 - sqrtf(1 - powf(2 * x, 2))) / 2
		: (sqrtf(1 - powf(-2 * x + 2, 2)) + 1) / 2;
}

float Utility::InQuad(float x)
{
    return x * x;
}

float Utility::OutQuad(float x)
{
    return  1 - (1 - x) * (1 - x);
}

float Utility::InOutQuad(float x)
{
    return x < 0.5f ? 2 * x * x : 1 - powf(-2 * x + 2, 2) / 2;
}

float Utility::InQuart(float x)
{
    return x * x * x * x;
}

float Utility::OutQuart(float x)
{
    return  1 - powf(1 - x, 4);
}

float Utility::InOutQuart(float x)
{
    return x < 0.5f ? 8 * x * x * x * x : 1 - powf(-2 * x + 2, 4) / 2;
}

float Utility::InExpo(float x)
{
    return  x == 0 ? 0 : powf(2, 10 * x - 10);
}

float Utility::OutExpo(float x)
{
    return x ==  1 ? 1 : 1 - powf(2, -10 * x);
}

float Utility::InOutExpo(float x)
{
	return x == 0 ? 0 : x == 1 ? 1 
			: x < 0.5f ? powf(2, 20 * x - 10) / 2 
			: (2 - powf(2, -20 * x + 10)) / 2;
}

float Utility::InBack(float x)
{
	const float c1 = 1.70158f;
	const float c3 = c1 + 1;

	return c3 * x * x * x - c1 * x * x;
}

float Utility::OutBack(float x)
{
	const float c1 = 1.70158f;
	const float c3 = c1 + 1;

	return 1 + c3 * powf(x - 1, 3) + c1 * powf(x - 1, 2);
}

float Utility::InOutBack(float x)
{
	const float c1 = 1.70158f;
	const float c2 = c1 * 1.525f;
    return x < 0.5
		? (powf(2 * x, 2) * ((c2 + 1) * 2 * x - c2)) / 2
		: (powf(2 * x - 2, 2) * ((c2 + 1) * (x * 2 - 2) + c2) + 2) / 2;
}

float Utility::InElastic(float x)
{
	const float c4 = (2 * PI) / 3;

	return x == 0 ? 0
		: x == 1 ? 1
		: -powf(2, 10 * x - 10) * sinf((x * 10 - 10.75f) * c4);
}

float Utility::OutElastic(float x)
{
	const float c4 = (2 * PI) / 3;

	return x == 0 ? 0
		: x == 1 ? 1
		: powf(2, -10 * x) * sinf((x * 10 - 0.75f) * c4) + 1;
}

float Utility::InOutElastic(float x)
{
	const float c5 = (2 * PI) / 4.5f;

	return x ==  0
		? 0
		: x ==  1
		? 1
		: x < 0.5f
		? -(powf(2, 20 * x - 10) * sinf((20 * x - 11.125f) * c5)) / 2
		: (powf(2, -20 * x + 10) * sinf((20 * x - 11.125f) * c5)) / 2 + 1;
}

float Utility::InBounce(float x)
{
	return 1 - OutBounce(1 - x);
}

float Utility::OutBounce(float x)
{
	const float n1 = 7.5625f;
	const float d1 = 2.75f;

	if (x < 1 / d1) {
		return n1 * x * x;
	}
	else if (x < 2 / d1) {
		return n1 * (x -= 1.5f / d1) * x + 0.75f;
	}
	else if (x < 2.5f / d1) {
		return n1 * (x -= 2.25f / d1) * x + 0.9375f;
	}
	else {
		return n1 * (x -= 2.625f / d1) * x + 0.984375f;
	}
}

float Utility::InOutBounce(float x)
{
	return x < 0.5f
		? (1 - OutBounce(1 - 2 * x)) / 2
		: (1 + OutBounce(2 * x - 1)) / 2;
}

