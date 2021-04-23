#include"fun.h"

//�ļ�����
void in(process* p, int process_num)
{
	const char* filename = "process.txt";
	ifstream ism;
	ism.open(filename);
	if (!ism.is_open())
	{
		cout << "hhhhhhhhh" << endl;
	}
	int i = 0;
	for (i; i < process_num; i++)
	{
		ism >> p[i].name;
	}
	for (int i = 0; i < process_num; i++)
	{
		ism >> p[i].come_time;
	}
	for (int i = 0; i < process_num; i++)
	{
		ism >> p[i].server_time;
	}
}

//�����ؽ��
void out(process* p, int process_num)
{
	sort_come(p, process_num);
	cout << "��������:" << "\t";
	for (int i = 0; i < process_num; i++)
	{
		cout << p[i].name << "\t";
	}
	cout << endl;
	cout << "����ʱ��:" << "\t";
	for (int i = 0; i < process_num; i++)
	{
		cout << p[i].come_time << "\t";
	}
	cout << endl;
	cout << "����ʱ��:" << "\t";
	for (int i = 0; i < process_num; i++)
	{
		cout << p[i].server_time << "\t";
	}
	cout << endl;
	cout << "���ʱ��:" << "\t";
	for (int i = 0; i < process_num; i++)
	{
		cout << p[i].fin_time << "\t";
	}
	cout << endl;
	cout << "��תʱ��:" << "\t";
	for (int i = 0; i < process_num; i++)
	{
		cout << p[i].turn_time << "\t";
	}
	cout << endl;
	cout << "��Ȩ��תʱ��:" << "\t";
	for (int i = 0; i < process_num; i++)
	{
		cout << r2(p[i].weight_turn_time) << "\t";
	}
	cout << endl << endl;
	cout << "ƽ����תʱ��:" << "\t";
	float total_turntime = 0;
	for (int i = 0; i < process_num; i++)
	{
		total_turntime += p[i].turn_time;
	}
	cout << r2(total_turntime / process_num) << endl << endl;

	cout << "ƽ����Ȩ��תʱ��:" << "\t";
	float total_weight_turntime = 0;
	for (int i = 0; i < process_num; i++)
	{
		total_weight_turntime += p[i].weight_turn_time;
	}
	cout << r2(total_weight_turntime / process_num) << endl;
}

//���յ���ʱ�������������
void sort_come(process* p, int process_num)
{
	for (int i = 0; i < process_num; i++)
	{
		for (int j = process_num - 1; j > i; j--)
		{
			if (p[j - 1].come_time > p[j].come_time)
			{
				process temp = p[0];
				temp = p[j - 1];
				p[j - 1] = p[j];
				p[j] = temp;
			}
		}
	}
}

//����cpu������㷨�����½������ݣ�
void server(process &p, int rr, int &time, int &result)
{
	//����ǰʱ��Ƭ������ɱ�����
	if (p.time_left <= rr)
	{
		//����������Ϣ
		p.fin_time = time + p.time_left;
		time = time + p.time_left;
		p.time_left = 0;
		p.turn_time = p.fin_time - p.come_time;
		p.weight_turn_time = p.turn_time / p.server_time;
		result = 1;
	}
	//�޷���ɵ�ǰ���̣����Ժ��������
	else
	{
		//���µ�ǰʱ���Լ�����ʣ��ʱ��
		p.time_left = p.time_left - rr;
		time = time + rr;
		result = 0;
	}
}

//��������������������λС�������������
float r2(float a)
{
	return(round(a * 100) / 100.0);
}


/*�߼�˳��
�жϵ�ǰʱ���Ƿ����µĽ��̵���
1.���µĽ��̵���������±�洢 �����жϵ�ǰ�����еĽ����Ƿ���Ҫ�ض�
2.�ޣ����µ�ǰʱ��+1
1.1.��Ҫ�ضӣ��洢���ڷ���Ľ��̵��±�
1.2.�Ѿ���ɷ���count++��
���з�������е�һ�����̡����¶��ס�

ֱ��count = process_num������ѭ������������
*/
void RR(process* p, int process_num,int rr)
{
	sort_come(p, process_num);
	int q[100];		//ģ����У������洢�����±�	
	int time = 0;	//��ǰʱ��	
	int in_num = 0;	//�ж��Ƿ����н��̾��ѽ���
	int count = 0;	//����ѭ������
	int result = -1;	//��һ������ӵĽ��̽������⴦��
	int i = 0;		//�����±�
	int j = 0;		//��β�±�
	//��ʼ��ÿ�����̵�ʣ��ʱ��
	for (int r = 0; r < process_num; r++)
	{
		p[r].time_left = p[r].server_time;
	}
	while (count < process_num)
	{
		if (in_num < process_num)	//�����н���û�н���
		{
			for (int s = 0; s < process_num; s++)	//�жϵ�ǰʱ���Ƿ����µĽ�����Ҫ����
			{
				if (p[s].come_time <= time && p[s].flag == 0)
				{
					q[j] = s;	//�����ӵĽ�����һ���뵽����β��
					p[s].flag = 1;	//���¸ս��ӵĽ��̵ı�־
					in_num++;	//���½��ӽ��̵�����
					j++;	//���¶�β�±�
				}
			}
			if (result == 0)	//����һ������û�з�����
			{
				q[j] = q[i-1];		//�����β
				j++;
			}
			else if (result == 1)	//�������
			{
				count++;	//�������+1
			}
			server(p[q[i]], rr, time, result);	//�Զ��׽��̽��з���
			i++;
		}
		//�����н��̾�����
		else 
		{
			if (result == 0)
			{
				q[j] = q[i - 1];
				j++;
			}
			else if (result == 1)
			{
				count++;
			}
			if (i != j)//���������д���2�����̣�����������¶����±�
			{
				i++;
			}
			server(p[q[i-1]], rr, time, result);
			
		}
	}
	


}

int main()
{
	int process_num = 5;
	process* p = new process[process_num];
	in(p, process_num);
	int a = 0;
	while (1)
	{
		cout << endl;
		cout << "pls input a number to select a function" << endl;
		cout << "1.RR" << endl;
		cout << "2.quit" << endl;

		cin >> a;
		if (a == 1)
		{
			cout << "-----RR-----" << endl;
			RR(p, process_num,2);
			out(p, process_num);
		}
		else if (a == 2)
		{
			break;
		}
		else
		{
			cout << "pls intput a ture number" << endl;
		}
	}



	return 0;
}
