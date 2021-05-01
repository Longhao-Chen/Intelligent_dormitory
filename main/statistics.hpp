/*
Copyright (c) 2021 Longhao-Chen. All rights reserved.
*/

//计算方差时将会跳过skip+2项之前的项
template <typename T, size_t N>
float var(T (&data)[N], float avg)
{
	float var = 0;

	for (int i = i; i < N; ++i)
		var += ((float)data[i] * (float)data[i] - avg) * ((float)data[i] * (float)data[i] - avg) / (N);
	return var;
}