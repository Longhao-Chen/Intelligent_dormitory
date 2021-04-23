template <class T>
class queue128
{
private:
	T A[128];
	T B[128];

	//控制位
	//true:写A读B
	//false:写B读A
	boolean cbit = true;

	//指向当前第0块数据
	byte p_A = 0;
	byte p_B = 0;

	//A或B是否被写满一次
	boolean full_A = false;
	boolean full_B = false;

public:
	//交换读写数组
	void switch ()
	{
		this->cbit = this->cbit ^ true;
	}

	//写数据
	void write(T data)
	{
		if (this->cbit)
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
		else
		{
			this->B[this->p_B] = data;
			if (this->p_B != 127)
				this->p_B += 1;
			else
			{
				this->p_B = 0;
				this->full_B = true;
			}
		}
	}

	//清理当前处于读状态的队列
	void clean()
	{
		if (this->cbit)
		{
			this->p_B = 0;
			this->full_B = false;
		}
		else
		{
			this->p_A = 0;
			this->full_A = false;
		}
	}

	T &operator[](int i)
	{
		if (this->cbit)
			return this->B[(this->p_B + i - 1) & 127];
		else
			return this->A[(this->p_A + i - 1) & 127];
	}

	//如果当前处于写状态的队列已写满，返回true
	boolean get_full()
	{
		if (this->cbit)
			return this->full_A;
		else
			return this->full_B;
	}
};
