#pragma once

#define PI (3.1415f)
#define DegToRad (PI / 180.0f)
#define RadToDeg (180.0f / PI)

/// <summary>
/// 大きいほうの値を返します
/// </summary>
/// <param name="x">値１</param>
/// <param name="y">値２</param>
/// <returns>大きい方の値</returns>
inline int GetMax(int x, int y)			{ return x > y ? x : y; }
/// <summary>
/// 大きいほうの値を返します
/// </summary>
/// <param name="x">値１</param>
/// <param name="y">値２</param>
/// <returns>大きい方の値</returns>
inline float GetMax(float x, float y)	{ return x > y ? x : y; }
/// <summary>
/// 小さいほうの値を返します
/// </summary>
/// <param name="x">値１</param>
/// <param name="y">値２</param>
/// <returns>小さい方の値</returns>
inline int GetMin(int x, int y)			{ return x < y ? x : y; }
/// <summary>
/// 小さいほうの値を返します
/// </summary>
/// <param name="x">値１</param>
/// <param name="y">値２</param>
/// <returns>小さい方の値</returns>
inline float GetMin(float x, float y)	{ return x < y ? x : y; }