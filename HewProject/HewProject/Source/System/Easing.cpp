#include "Easing.hpp"
#include <math.h>
#include <macro.hpp>

// https://easings.net/ja

float Easing::InSine(float x)
{
    return 1.0f - cosf((x * PI) / 2);
}

float Easing::OutSine(float x)
{
    return sinf((x * PI) / 2);
}

float Easing::InOutSine(float x)
{
    return -(cosf(PI * x) - 1) / 2;
}

float Easing::InCubic(float x)
{
    return  x * x * x;
}

float Easing::OutCubic(float x)
{
    return  1 - powf(1 - x, 3);
}

float Easing::InOutCubic(float x)
{
    return x < 0.5f ? 4 * x * x * x : 1 - powf(-2 * x + 2, 3) / 2;
}

float Easing::InQuint(float x)
{
    return  x * x * x * x * x;
}

float Easing::OutQuint(float x)
{
    return 1 - powf(1 - x, 5);
}

float Easing::InOutQuint(float x)
{
    return x < 0.5f ? 16 * x * x * x * x * x : 1 - powf(-2 * x + 2, 5) / 2;
}

float Easing::InCirc(float x)
{
    return 1 - sqrtf(1 - powf(x, 2));
}

float Easing::OutCirc(float x)
{
    return sqrtf(1 - powf(x - 1, 2));
}

float Easing::InOutCirc(float x)
{
    return x < 0.5f
		? (1 - sqrtf(1 - powf(2 * x, 2))) / 2
		: (sqrtf(1 - powf(-2 * x + 2, 2)) + 1) / 2;
}

float Easing::InQuad(float x)
{
    return x * x;
}

float Easing::OutQuad(float x)
{
    return  1 - (1 - x) * (1 - x);
}

float Easing::InOutQuad(float x)
{
    return x < 0.5f ? 2 * x * x : 1 - powf(-2 * x + 2, 2) / 2;
}

float Easing::InQuart(float x)
{
    return x * x * x * x;
}

float Easing::OutQuart(float x)
{
    return  1 - powf(1 - x, 4);
}

float Easing::InOutQuart(float x)
{
    return x < 0.5f ? 8 * x * x * x * x : 1 - powf(-2 * x + 2, 4) / 2;
}

float Easing::InExpo(float x)
{
    return  x == 0 ? 0 : powf(2, 10 * x - 10);
}

float Easing::OutExpo(float x)
{
    return x ==  1 ? 1 : 1 - powf(2, -10 * x);
}

float Easing::InOutExpo(float x)
{
	return x == 0 ? 0 : x == 1 ? 1 
			: x < 0.5f ? powf(2, 20 * x - 10) / 2 
			: (2 - powf(2, -20 * x + 10)) / 2;
}

float Easing::InBack(float x)
{
	const float c1 = 1.70158f;
	const float c3 = c1 + 1;

	return c3 * x * x * x - c1 * x * x;
}

float Easing::OutBack(float x)
{
	const float c1 = 1.70158f;
	const float c3 = c1 + 1;

	return 1 + c3 * powf(x - 1, 3) + c1 * powf(x - 1, 2);
}

float Easing::InOutBack(float x)
{
	const float c1 = 1.70158f;
	const float c2 = c1 * 1.525f;

    return x < 0.5
		? (powf(2 * x, 2) * ((c2 + 1) * 2 * x - c2)) / 2
		: (powf(2 * x - 2, 2) * ((c2 + 1) * (x * 2 - 2) + c2) + 2) / 2;
}

float Easing::InElastic(float x)
{
	const float c4 = (2 * PI) / 3;

	return x == 0 ? 0
		: x == 1 ? 1
		: -powf(2, 10 * x - 10) * sinf((x * 10 - 10.75f) * c4);
}

float Easing::OutElastic(float x)
{
	const float c4 = (2 * PI) / 3;

	return x == 0 ? 0
		: x == 1 ? 1
		: powf(2, -10 * x) * sinf((x * 10 - 0.75f) * c4) + 1;
}

float Easing::InOutElastic(float x)
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

float Easing::InBounce(float x)
{
	return 1 - OutBounce(1 - x);
}

float Easing::OutBounce(float x)
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

float Easing::InOutBounce(float x)
{
	return x < 0.5f
		? (1 - OutBounce(1 - 2 * x)) / 2
		: (1 + OutBounce(2 * x - 1)) / 2;
}
