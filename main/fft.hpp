/*
Copyright (c) 2021 Longhao-Chen. All rights reserved.
*/

#include <Arduino.h>
#include "queue.hpp"

//e^(-i*2*pi*k/N)
complex<float> W(int k, int N)
{
	complex<float> res;
	uint8_t ang;
	ang = (int)round(k / N * 128) & 127; //对127取模

	//欧拉公式
	res.re = fastcos(ang);
	res.im = -fastsin(ang);

	return res;
}

//计算实数fft，只输出1～N/2-1项
template <typename T, typename T1, int N>
void real_fft(queue128<T>(&in), T1 (&out)[N])
{
	complex<float> H[(2 * N + 2) / 2];
	//预处理
	for (int i = 0; i < (2 * N + 2) / 2; ++i)
	{
		H[i].re = in[2 * i];
		H[i].im = in[2 * i + 1];
	}

	fft(H);

	//后处理
	for (int i = 0; i < (2 * N + 2) / 2 - 1; ++i)
	{
		out[i] = 0.5 * (H[i + 1] + conj(H[(2 * N + 2) / 2 - i - 1])) - 0.5 * mul_i(H[i + 1] - conj(H[(2 * N + 2) / 2 - i - 1])) * W(i + 1, (2 * N + 2));
	}
}

//处理倒位
template <typename T, int N>
void fft_per(complex<T> (&IN_X)[N])
{

	int row = log(N) / log(2); //row为FFT的N个输入对应的最大列数
	complex<T> temp;	   //临时交换变量
	unsigned short i = 0, j = 0, k = 0;
	double t;
	for (i = 0; i <= row; ++i) //从第0个序号到第N-1个序号
	{
		k = i;		  //当前第i个序号
		j = 0;		  //存储倒序后的序号，先初始化为0
		t = row;	  //共移位t次
		while ((t--) > 0) //利用按位与以及循环实现码位颠倒
		{
			j = j << 1;
			j |= (k & 1); //j左移一位然后加上k的最低位
			k = k >> 1;   //k右移一位，次低位变为最低位
			/*j为倒序，k为正序，
					从k右向左的值依次移位，
					j向左依次填入对应的k的右向位*/
		}
		if (j > i) //如果倒序后大于原序数，就将两个存储单元进行交换(判断j>i是为了防止重复交换)
		{
			temp = IN_X[i];
			IN_X[i] = IN_X[j];
			IN_X[j] = temp;
		}
	}
}

//离散傅立叶变换
template <typename T, int N>
void fft(complex<T> (&Data)[N])
{
	fft_per(Data);
	int step;
	complex<T> wn, temp, deltawn;
	int Log2N = log(N) / log(2);
	for (int ii = 1; ii <= Log2N; ii++)
	{
		wn.re = 1;
		wn.im = 0;
		step = 1 << ii;
		deltawn = W(1, step);
		for (int j = 0; j < step / 2; j++)
		{
			for (int i = 0; i < N / step; i++)
			{
				temp = Data[i * step + step / 2 + j] * wn;
				Data[i * step + step / 2 + j] = Data[i * step + j] - temp;
				Data[i * step + j] = Data[i * step + j] + temp;
			}
			wn = wn * deltawn;
		}
	}
}