#ifndef BANK_H
#define BANK_H

#include<iostream>
#include<stdlib.h>
using namespace std;

const int NumOfResoure = 2;
const int NumOfProcess = 3;

class Bank
{
public:
	Bank()
	{}
	void Init()
	{
		InitAvailable();
		InitMax();
		InitAllocation();
		InitNeed();
	}
	bool IsSafe()
	{
		bool Finish[NumOfProcess] = { false };
		int Work[NumOfResoure];
		for (int i = 0; i < NumOfResoure; ++i)
		{
			Work[i] = Available[i];
		}

		int safeSequence[NumOfProcess];
		int SafeNum = 0;

		for (int j = 0; j < NumOfProcess; ++j)
		{
			int ret = findSafeProc(Finish, Work);
			if (ret == -1)
			{
				cout << "此状态不安全！！！，无法分配" << endl;
			//	return;
				return false;
			}
			else
			{
				Finish[ret] = true;
				safeSequence[SafeNum++] = ret;
				for (int k = 0; k < NumOfResoure; ++k)
				{
					Work[k] += Allocation[ret][k];
				}
			}
		}

		int ret = IsAllTrue(Finish, NumOfProcess);
		if (ret == 1)
		{
			cout << "此状态安全，安全序列为：";
			PrintSafeSequence(safeSequence, NumOfProcess);
			return true;
		}
		else
		{
			cout << "此状态不安全！！！" << endl;
			return false;
		}
	}
	void Request()
	{
		int Request[NumOfResoure];
		int procNum;
		cout << "请输入请求资源的进程编号 -->";
		cin >> procNum;

		cout << "请输入该进程所需要的" << NumOfResoure << "类资源(Request)数目 -->";
		for (int i = 0; i < NumOfResoure; ++i)
		{
			cin >> Request[i];
			if (Request[i] > Need[procNum][i])
			{
				cout << "错误！！ 请求的资源大于所需要的资源数目,无法分配" << endl;
				return;
			}
			else if (Request[i] > Available[i])
			{
				cout << "错误！！ 请求的资源大于可利用的资源数目,无法分配" << endl;
				return;
			}
		}
		cout << "暂时分配开始。。。。" << endl;
		for (int i = 0; i < NumOfResoure; ++i)
		{
			Available[i] -= Request[i];
			Allocation[procNum][i] += Request[i];
			Need[procNum][i] -= Request[i];
		}
		cout << "正在检查当前状态是否安全。。。" << endl;
		if (!IsSafe())
		{
			for (int i = 0; i < NumOfResoure; ++i)
			{
				Available[i] += Request[i];
				Allocation[procNum][i] -= Request[i];
				Need[procNum][i] += Request[i];
			}
		}
		////////////////////////////////////////////
		else
		{
			int flag = 1;
			for (int i = 0; i < NumOfResoure; ++i)
			{
				if (Need[procNum][i] != 0)
				{
					flag = 0;
				}
			}
			if (flag == 1)
			{
				for (int i = 0; i < NumOfResoure; ++i)
				{
					Available[i] += Allocation[procNum][i];
				}
				for (int i = 0; i < NumOfResoure; ++i)
				{
					Allocation[procNum][i] = 0;
				}
			}
		}
	}
	void meau()
	{
		cout << "------------> 银行家算法 <-------------" << endl;
		int choice;
		while (1)
		{
			cout << "          [1]:        Init				" << endl;
			cout << "          [2]:        Request			" << endl;
			cout << "          [3]:        IsSafe			" << endl;
			cout << "          [4]:        exit				" << endl;
			cout << "          [5]:        PrintAlloction   " << endl;
			cout << "          [6]:        PrintMax			" << endl;
			cout << "          [7]:        PrintNeed	    " << endl;
			cout << "          [8]:        PrintAvailable	" << endl;
			cout << "请输入您的选择：>";
			fflush(stdin);
			cin >> choice;
			fflush(stdin);
			switch (choice)
			{
			case 1:
				Init();
				break;
			case 2:
				Request();
				break;
			case 3:
				IsSafe();
				break;
			case 4:
				return;
			case 5:
				PrintAllocation();
				break;
			case 6:
				PrintMax();
				break;
			case 7:
				PrintNeed();
				break;
			case 8:
				PrintAvailable();
				break;
			}
		}
	}
protected:
	void InitAvailable()
	{
		cout << "初始化Available数组" << endl;
		for (int i = 0; i < NumOfResoure; ++i)
		{
			cout << "请输入Resoure" << i + 1 << "的可用资源(Avaliable)数目: --->";
			cin >> Available[i];
		}
	}
	void PrintAvailable()
	{
		cout << "打印Available数组" << endl;
		for (int i = 0; i < NumOfResoure; ++i)
		{
			cout<<Available[i]<<" ";
		}
		cout << endl;
	}
	void InitMax()
	{
		cout << "初始化Max数组" << endl;
		for (int i = 0; i < NumOfProcess; ++i)
		{
			cout << "请输入Proc" << i << "的" << NumOfResoure << "个最大需求资源(Max)数目 -->";
			for (int j = 0; j < NumOfResoure; ++j)
			{
				cin >> Max[i][j];
			}
		}
	}
	void PrintMax()
	{
		cout << "打印Max数组" << endl;
		for (int i = 0; i < NumOfProcess; ++i)
		{
			for (int j = 0; j < NumOfResoure; ++j)
			{
				cout<< Max[i][j]<<" ";
			}
			cout << endl;
		}
	}
	void InitAllocation()
	{
		cout << "初始化Allocation数组" << endl;
		for (int i = 0; i < NumOfProcess; ++i)
		{
			cout << "请输入Proc" << i << "的" << NumOfResoure << "个已分配资源(Allocation)数目 -->";
			for (int j = 0; j < NumOfResoure; ++j)
			{
				cin >> Allocation[i][j];
			}
		}
	}
	void PrintAllocation()
	{
		cout << "打印Allocation数组" << endl;
		for (int i = 0; i < NumOfProcess; ++i)
		{
			for (int j = 0; j < NumOfResoure; ++j)
			{
				cout<<Allocation[i][j]<<" ";
			}
			cout << endl;
		}
	}
	void InitNeed()
	{
		for (int i = 0; i < NumOfProcess; ++i)
		{
			for (int j = 0; j < NumOfResoure; ++j)
			{
				Need[i][j] = Max[i][j] - Allocation[i][j];
			}
		}

	}
	void PrintNeed()
	{
		cout << "打印Need数组" << endl;
		for (int i = 0; i < NumOfProcess; ++i)
		{
			for (int j = 0; j < NumOfResoure; ++j)
			{
				cout << Need[i][j] << " ";
			}
			cout << endl;
		}

	}

	int IsAllTrue(bool *arr, int size)//判断是否全部都能分配
	{
		for (int i = 0; i < size; ++i)
		{
			if (arr[i] == false)
				return 0;
		}
		return 1;
	}
	void PrintSafeSequence(int *arr, int size)
	{
		for (int i = 0; i < size; ++i)
		{
			cout << arr[i] << "-->";
		}
		cout <<"NULL"<< endl;
	}
	//寻找能够满足分配条件的进程，找到返回进程编号，失败返回-1
	int findSafeProc(bool *Finish,int *Work)
	{
		for (int i = 0; i < NumOfProcess; ++i)
		{
			if (Finish[i] == false)
			{
				int flag = 1;
				//若该进程的Need[][] > Available[],使 flag = 0
				for (int j = 0; j < NumOfResoure; ++j)
				{
					if (Need[i][j] > Work[j])
					{
						flag = 0;
					}
				}
				if (flag == 1)
				{
					return i;
				}
			}
		}
		return -1;
	}

private:
	int Available[NumOfResoure];
	int Max[NumOfProcess][NumOfResoure];
	int Allocation[NumOfProcess][NumOfResoure];
	int Need[NumOfProcess][NumOfResoure];
};

#endif