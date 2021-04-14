//离散余弦变换，使用fft
#include "dsp.hpp"

//输出值保存在out[N-2]，除去直流分量和N/2项（为减少计算量），不乘以系数sqrt(2/N)
//警告：为节约储存空间，会修改输入变量！
template <size_t N>
void dct(int (&in)[N], int (&out)[N - 2])
{
	per_data(in);		   //数据预处理
	complex<int> Y[N / 2 - 1]; //用来保存实数fft的结果，无第0项和N/2项，只有1～N/2-1项
	real_fft(in, Y);
	Y2out(Y, out);
}

//数据预处理
template <size_t N>
inline void per_data(int (&in)[N])
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

//Re{e^(-i*n*pi/(2*N))*Y}
template <size_t N>
inline void Y2out(complex<int> (&Y)[N], int (&out)[])
{
	for (int i = 0; i < N; ++i)
	{
		out[i] = round(Y[i].re * fastcos(round(0.5 * (i + 1) / (4 * N + 4) * 128) & 127) + Y[i].im * fastsin(round(0.5 * (i + 1) / (4 * N + 4) * 128) & 127));
		out[2 * N - i - 1] = round(Y[i].re * fastcos(round(0.5 * (2 * N - i + 1) / (4 * N + 4) * 128) & 127) - Y[i].im * fastsin(round(0.5 * (2 * N - i + 1) / (4 * N + 4) * 128) & 127));
	}
}