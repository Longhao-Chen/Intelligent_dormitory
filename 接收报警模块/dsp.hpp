/*
Copyright (c) 2021 Longhao-Chen. All rights reserved.
*/

#ifndef DSP_HPP
#define DSP_HPP

//复数
template <class T>
struct complex
{
	T re;
	T im;
};

template <typename T>
complex<T> add(const complex<T>, const complex<T>);
template <typename T>
complex<T> operator+(const complex<T> &a, const complex<T> &b);

template <typename T>
complex<T> sub(const complex<T>, const complex<T>);
template <typename T>
complex<T> operator-(const complex<T> &a, const complex<T> &b);

template <typename T>
complex<T> mul(const complex<T>, const complex<T>);
template <typename T>
complex<T> operator*(const complex<T> &a, const complex<T> &b);
template <typename T>
complex<T> operator*(const float &a, const complex<T> &b);

template <typename T>
complex<T> mul_i(const complex<T>);

template <typename T>
complex<T> conj(const complex<T>);

int16_t fastcos32767(uint8_t);
int16_t fastsin32767(uint8_t);
float fastsin(uint8_t);
float fastcos(uint8_t);

//实数fft
template <typename T, size_t N>
void real_fft(T (&in)[N], T (&out)[N / 2 - 2]);

template <size_t N>
void dct(int (&in)[N], int (&out)[N - 2]);

#include "complex.cpp"
#include "dct.hpp"
#include "fft.cpp"

#endif