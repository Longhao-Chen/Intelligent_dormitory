/*
Copyright (c) 2021 Longhao-Chen. All rights reserved.
*/

//离散余弦变换，使用fft
#include "queue.hpp"
//输出值保存在out[N-2]，除去直流分量和N/2项（为减少计算量），不乘以系数sqrt(2/N)
//警告：为节约储存空间，会修改输入变量！

//数据预处理
template <int N, typename T>
inline void per_data(queue128<T>(&in))
{
	int tmp[N / 2]; //保存in中2i+1的元素
	for (int i = 0; i < N / 2; ++i)
	{
		tmp[i] = in[2 * i + 1];
		in[i] = in[2 * i];
	}
	for (int i = 0; i < N / 2; ++i)
		in[N - i - 1] = tmp[i];
}

template <typename T, int N>
void dct(queue128<T>(&in), float (&out)[N])
{
	per_data<N>(in);		 //数据预处理
	complex<float> Y[(N + 2) / 2 - 1]; //用来保存实数fft的结果，无第0项和N/2项，只有1～N/2-1项
	real_fft(in, Y);

	for (int i = 0; i < (N + 2) / 2 - 1; ++i)
	{
		out[i] = round(Y[i].re * fastcos((int)round(0.5 * (i + 1) / (4 * (N + 2) + 4) * 128) & 127) + Y[i].im * fastsin((int)round(0.5 * (i + 1) / (4 * (N + 2) + 4) * 128) & 127));
		out[(N + 2) - i - 3] = round(Y[i].re * fastcos((int)round(0.5 * ((N + 2) - i - 1) / (2 * (N + 2)) * 128) & 127) - Y[i].im * fastsin((int)round(0.5 * ((N + 2) - i - 1) / (2 * (N + 2)) * 128) & 127)); //共轭复数，所以中间取负
	}
}
