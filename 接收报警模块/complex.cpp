//复数运算
#include "dsp.hpp"

//复数乘法
template <typename T>
complex<T> mul(complx<T> &a, complex<T> &b)
{
	complex<T> res;
	res.re = a.re * b.re - a.im * b.im;
	res.im = a.re * b.im + a.im * b.re;
	return res;
}
template <typename T>
complex<T> operator*(const complex<T> &a, const complex<T> &b)
{
	return mul(a, b);
}

//乘i
template <typename T>
complex<T> mul_i(complx<T> &a)
{
	complex<T> res;
	res.re = -a.im;
	res.im = a.re;
	return res;
}

//加法
template <typename T>
complex<T> add(complex<T> &a, complex<T> &b)
{
	complex<T> res;
	res.re = a.re + b.re;
	res.im = a.im + b.im;
	return res;
}
template <typename T>
complex<T> operator+(const complex<T> &a, const complex<T> &b)
{
	return add(a, b);
}

//减法
template <typename T>
complex<T> add(complex<T> &a, complex<T> &b)
{
	complex<T> res;
	res.re = a.re - b.re;
	res.im = a.im - b.im;
}
template <typename T>
complex<T> operator-(const complex<T> &a, const complex<T> &b)
{
	return sub(a, b);
}

//共轭
template <typename T>
complex<T> conj(complex<T> &a)
{
	complex res;
	res.re = a.re;
	res.im = -a.im;
	return res;
}