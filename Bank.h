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
				cout << "��״̬����ȫ���������޷�����" << endl;
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
			cout << "��״̬��ȫ����ȫ����Ϊ��";
			PrintSafeSequence(safeSequence, NumOfProcess);
			return true;
		}
		else
		{
			cout << "��״̬����ȫ������" << endl;
			return false;
		}
	}
	void Request()
	{
		int Request[NumOfResoure];
		int procNum;
		cout << "������������Դ�Ľ��̱�� -->";
		cin >> procNum;

		cout << "������ý�������Ҫ��" << NumOfResoure << "����Դ(Request)��Ŀ -->";
		for (int i = 0; i < NumOfResoure; ++i)
		{
			cin >> Request[i];
			if (Request[i] > Need[procNum][i])
			{
				cout << "���󣡣� �������Դ��������Ҫ����Դ��Ŀ,�޷�����" << endl;
				return;
			}
			else if (Request[i] > Available[i])
			{
				cout << "���󣡣� �������Դ���ڿ����õ���Դ��Ŀ,�޷�����" << endl;
				return;
			}
		}
		cout << "��ʱ���俪ʼ��������" << endl;
		for (int i = 0; i < NumOfResoure; ++i)
		{
			Available[i] -= Request[i];
			Allocation[procNum][i] += Request[i];
			Need[procNum][i] -= Request[i];
		}
		cout << "���ڼ�鵱ǰ״̬�Ƿ�ȫ������" << endl;
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
		cout << "------------> ���м��㷨 <-------------" << endl;
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
			cout << "����������ѡ��>";
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
		cout << "��ʼ��Available����" << endl;
		for (int i = 0; i < NumOfResoure; ++i)
		{
			cout << "������Resoure" << i + 1 << "�Ŀ�����Դ(Avaliable)��Ŀ: --->";
			cin >> Available[i];
		}
	}
	void PrintAvailable()
	{
		cout << "��ӡAvailable����" << endl;
		for (int i = 0; i < NumOfResoure; ++i)
		{
			cout<<Available[i]<<" ";
		}
		cout << endl;
	}
	void InitMax()
	{
		cout << "��ʼ��Max����" << endl;
		for (int i = 0; i < NumOfProcess; ++i)
		{
			cout << "������Proc" << i << "��" << NumOfResoure << "�����������Դ(Max)��Ŀ -->";
			for (int j = 0; j < NumOfResoure; ++j)
			{
				cin >> Max[i][j];
			}
		}
	}
	void PrintMax()
	{
		cout << "��ӡMax����" << endl;
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
		cout << "��ʼ��Allocation����" << endl;
		for (int i = 0; i < NumOfProcess; ++i)
		{
			cout << "������Proc" << i << "��" << NumOfResoure << "���ѷ�����Դ(Allocation)��Ŀ -->";
			for (int j = 0; j < NumOfResoure; ++j)
			{
				cin >> Allocation[i][j];
			}
		}
	}
	void PrintAllocation()
	{
		cout << "��ӡAllocation����" << endl;
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
		cout << "��ӡNeed����" << endl;
		for (int i = 0; i < NumOfProcess; ++i)
		{
			for (int j = 0; j < NumOfResoure; ++j)
			{
				cout << Need[i][j] << " ";
			}
			cout << endl;
		}

	}

	int IsAllTrue(bool *arr, int size)//�ж��Ƿ�ȫ�����ܷ���
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
	//Ѱ���ܹ�������������Ľ��̣��ҵ����ؽ��̱�ţ�ʧ�ܷ���-1
	int findSafeProc(bool *Finish,int *Work)
	{
		for (int i = 0; i < NumOfProcess; ++i)
		{
			if (Finish[i] == false)
			{
				int flag = 1;
				//���ý��̵�Need[][] > Available[],ʹ flag = 0
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