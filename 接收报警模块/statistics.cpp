/*
Copyright (c) 2021 Longhao-Chen. All rights reserved.
*/

#include "statistics.hpp"

//计算方差时将会跳过skip-1、skip、skip+1项
template <typename T, size_t N>
float var(const T (&data)[N], float avg, int skip)
{
	float var = 0;
	for (int i = 0; i < skip - 1; ++i)
		var += data[i] * data[i];

	for (int i = skip + 2; i < N; ++i)
		var += data[i] * data[i];

	var /= N - 3;
	var -= avg * avg;
	return var;
}

//计算平均值
//计算平均值时将会跳过skip-1、skip、skip+1项
template <typename T, size_t N>
float avg(const T (&data)[N], int skip)
{
	float avg = 0;
	for (int i = 0; i < skip - 1; ++i)
		avg += data[i];

	for (int i = skip + 2; i < N; ++i)
		avg += data[i];

	avg /= N - 3;
	return avg;
}