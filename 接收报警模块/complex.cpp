/*
Copyright (c) 2021 Longhao-Chen. All rights reserved.
*/

//复数运算
#include "dsp.hpp"

//复数乘法
template <typename T>
complex<T> mul(const complex<T> &a, const complex<T> &b)
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
template <typename T>
complex<T> operator*(const float &a, const complex<T> &b)
{
	complex<T> res;
	res.re = a * b.re;
	res.im = a * b.im;
	return res;
}

//乘i
template <typename T>
complex<T> mul_i(const complex<T> &a)
{
	complex<T> res;
	res.re = -a.im;
	res.im = a.re;
	return res;
}

//加法
template <typename T>
complex<T> add(const complex<T> &a, const complex<T> &b)
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
complex<T> sub(const complex<T> &a, const complex<T> &b)
{
	complex<T> res;
	res.re = a.re - b.re;
	res.im = a.im - b.im;
	return res;
}
template <typename T>
complex<T> operator-(const complex<T> &a, const complex<T> &b)
{
	return sub(a, b);
}

//共轭
template <typename T>
complex<T> conj(const complex<T> &a)
{
	complex<T> res;
	res.re = a.re;
	res.im = -a.im;
	return res;
}