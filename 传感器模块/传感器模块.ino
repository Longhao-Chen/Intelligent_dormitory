/*
Copyright (c) 2021 Longhao-Chen. All rights reserved.
*/

//报警，10ms高电平+10ms低电平，重复500ms
void go_off()
{
	digitalWrite(13, HIGH);	    //调试指示灯
	for (int i = 0; i < 25; ++i)
	{
		digitalWrite(3, HIGH);
		delay(10);
		digitalWrite(3, LOW);
		delay(10);
	}
	digitalWrite(13, LOW);
}

//检测
void detect()
{
	int high_i = 0;	   //之前检测到传感器高电平数
	int read_data = 0; //读取到的电压值
	while (1)
	{
		read_data = analogRead(A0);
		if (read_data > 614)
			++high_i;
		else
			high_i = 0;

		if (high_i >= 5)
		{
			go_off();
		}
		delay(2);
	}
}

void setup()
{
	pinMode(A0, INPUT);  //红外传感器data
	pinMode(2, OUTPUT);  //无线模块Vcc
	pinMode(3, OUTPUT);  //无线模块data
	pinMode(5, OUTPUT);  //红外传感器Vcc
	pinMode(13, OUTPUT); //调试指示灯

	digitalWrite(5, HIGH);	//红外传感器加电
	digitalWrite(2, HIGH);	//无线电模块加电

	detect();
}

void loop() {}