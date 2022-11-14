#pragma once

#define PI (3.1415f)
#define DegToRad (PI / 180.0f)
#define RadToDeg (180.0f / PI)

/// <summary>
/// �傫���ق��̒l��Ԃ��܂�
/// </summary>
/// <param name="x">�l�P</param>
/// <param name="y">�l�Q</param>
/// <returns>�傫�����̒l</returns>
inline int GetMax(int x, int y)			{ return x > y ? x : y; }
/// <summary>
/// �傫���ق��̒l��Ԃ��܂�
/// </summary>
/// <param name="x">�l�P</param>
/// <param name="y">�l�Q</param>
/// <returns>�傫�����̒l</returns>
inline float GetMax(float x, float y)	{ return x > y ? x : y; }
/// <summary>
/// �������ق��̒l��Ԃ��܂�
/// </summary>
/// <param name="x">�l�P</param>
/// <param name="y">�l�Q</param>
/// <returns>���������̒l</returns>
inline int GetMin(int x, int y)			{ return x < y ? x : y; }
/// <summary>
/// �������ق��̒l��Ԃ��܂�
/// </summary>
/// <param name="x">�l�P</param>
/// <param name="y">�l�Q</param>
/// <returns>���������̒l</returns>
inline float GetMin(float x, float y)	{ return x < y ? x : y; }