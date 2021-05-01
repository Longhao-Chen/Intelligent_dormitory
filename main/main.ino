/*
Copyright (c) 2021 Longhao-Chen. All rights reserved.
*/

#include "queue.hpp"
#include "statistics.hpp"
#include "fast_trig.hpp"
#include "complex.hpp"
#include "dct.hpp"
#include "fft.hpp"

queue128<int> data;

void record()
{
	for (int i = 0; i < 128; ++i)
	{
		data.write(analogRead(A0));
		delay(1);
	}
}

void alarm(unsigned int input)
{
	for (int i = 0; i < 16; ++i)
	{
		if (input & (unsigned int)1)
			digitalWrite(9, HIGH);
		else
			digitalWrite(9, LOW);

		delay(200);
		input = input >> 1;
	}
	digitalWrite(9, LOW);
}

//因为无线电模块会安装一个巨大的滤波电容，如果直接加电可能会导致过载
void load_radio()
{
	for (int i = 0; i < 1000; ++i)
	{
		digitalWrite(2, HIGH);
		delayMicroseconds(500);
		digitalWrite(2, LOW);
		delayMicroseconds(500);
	}
	digitalWrite(2, HIGH);
	delay(2000);
}

void detect()
{
	float dct_out[126];
	if (data.get_full())
	{
		dct(data, dct_out);
		for (int i = 0; i < 126; ++i)
			dct_out[i] /= 256;

		float data_var = var(dct_out, 0);
		Serial.print(data_var);
		if (data_var > .45)
		{
			alarm(10773);
			delay(10000);
		}
		Serial.println();
		data.clean();
	}
}

void setup()
{
	Serial.begin(115200);
	pinMode(A0, INPUT); //无线电模块输入
	pinMode(9, OUTPUT); //蜂鸣器
	pinMode(2, OUTPUT); //无线电模块电源

	load_radio();
	digitalWrite(9, LOW);
}

void loop()
{
	record();
	detect();
}
