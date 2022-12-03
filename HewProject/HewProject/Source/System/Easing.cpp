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
    return 0.0f;
}

float Easing::OutCubic(float x)
{
    return 0.0f;
}

float Easing::InOutCubic(float x)
{
    return 0.0f;
}

float Easing::InQuint(float x)
{
    return 0.0f;
}

float Easing::OutQuint(float x)
{
    return 0.0f;
}

float Easing::InOutQuint(float x)
{
    return 0.0f;
}

float Easing::InCirc(float x)
{
    return 0.0f;
}

float Easing::OutCirc(float x)
{
    return 0.0f;
}

float Easing::InOutCirc(float x)
{
    return 0.0f;
}

float Easing::InQuad(float level)
{
    return 0.0f;
}

float Easing::OutQuad(float level)
{
    return 0.0f;
}

float Easing::InOutQuad(float level)
{
    return 0.0f;
}

float Easing::InQuart(float level)
{
    return 0.0f;
}

float Easing::OutQuart(float level)
{
    return 0.0f;
}

float Easing::InOutQuart(float level)
{
    return 0.0f;
}

float Easing::InExpo(float level)
{
    return 0.0f;
}

float Easing::OutExpo(float level)
{
    return 0.0f;
}

float Easing::InOutExpo(float level)
{
    return 0.0f;
}

float Easing::InBack(float level)
{
    return 0.0f;
}

float Easing::OutBack(float level)
{
    return 0.0f;
}

float Easing::InOutBack(float level)
{
    return 0.0f;
}

float Easing::InElastic(float level)
{
    return 0.0f;
}

float Easing::OutElastic(float level)
{
    return 0.0f;
}

float Easing::InOutElastic(float level)
{
    return 0.0f;
}

float Easing::InBounce(float level)
{
    return 0.0f;
}

float Easing::OutBounce(float level)
{
    return 0.0f;
}

float Easing::InOutBounce(float level)
{
    return 0.0f;
}
