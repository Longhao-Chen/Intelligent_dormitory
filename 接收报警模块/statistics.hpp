/*
Copyright (c) 2021 Longhao-Chen. All rights reserved.
*/

template <typename T, size_t N>
float var(const T (&data)[N], float avg, int skip);

template <typename T, size_t N>
float avg(const T (&data)[N], int skip);