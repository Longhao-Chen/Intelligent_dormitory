/*
Copyright (c) 2021 Longhao-Chen. All rights reserved.
*/

#include "statistics.hpp"

template <typename T, size_t N>
float var(const T (&data)[N], float avg)
{
	float var = 0;
	for (int i = 0; i < N; ++i)
		var += data[i] * data[i];

	var /= N;
	var -= avg * avg;
	return var;
}

//计算平均值
template <typename T, size_t N>
float avg(const T (&data)[N])
{
	float avg = 0;
	for (int i = 0; i < N; ++i)
		avg += data[i];
	avg /= N;
	return avg;
}