#ifndef QUEUE_HPP
#define QUEUE_HPP

template <class T>
class queue128
{
private:
	T A[128];

	//指向当前第0块数据
	byte p_A = 0;

	//A或B是否被写满一次
	boolean full_A = false;

public:
	//写数据
	void write(T data)
	{
		this->A[this->p_A] = data;
		if (this->p_A != 127)
			this->p_A += 1;
		else
		{
			this->p_A = 0;
			this->full_A = true;
		}
	}

	//清理当前处于读状态的队列
	void clean()
	{
		this->p_A = 0;
		this->full_A = false;
	}

	T &operator[](int i)
	{
		return this->A[(this->p_A + i - 1) & 127];
	}

	//如果当前处于写状态的队列已写满，返回true
	boolean get_full()
	{
		return this->full_A;
	}
};
#endif