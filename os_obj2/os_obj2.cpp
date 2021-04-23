#include"fun.h"

//文件输入
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

//输出相关结果
void out(process* p, int process_num)
{
	sort_come(p, process_num);
	cout << "进程名字:" << "\t";
	for (int i = 0; i < process_num; i++)
	{
		cout << p[i].name << "\t";
	}
	cout << endl;
	cout << "到达时间:" << "\t";
	for (int i = 0; i < process_num; i++)
	{
		cout << p[i].come_time << "\t";
	}
	cout << endl;
	cout << "服务时间:" << "\t";
	for (int i = 0; i < process_num; i++)
	{
		cout << p[i].server_time << "\t";
	}
	cout << endl;
	cout << "完成时间:" << "\t";
	for (int i = 0; i < process_num; i++)
	{
		cout << p[i].fin_time << "\t";
	}
	cout << endl;
	cout << "周转时间:" << "\t";
	for (int i = 0; i < process_num; i++)
	{
		cout << p[i].turn_time << "\t";
	}
	cout << endl;
	cout << "带权周转时间:" << "\t";
	for (int i = 0; i < process_num; i++)
	{
		cout << r2(p[i].weight_turn_time) << "\t";
	}
	cout << endl << endl;
	cout << "平均周转时间:" << "\t";
	float total_turntime = 0;
	for (int i = 0; i < process_num; i++)
	{
		total_turntime += p[i].turn_time;
	}
	cout << r2(total_turntime / process_num) << endl << endl;

	cout << "平均带权周转时间:" << "\t";
	float total_weight_turntime = 0;
	for (int i = 0; i < process_num; i++)
	{
		total_weight_turntime += p[i].weight_turn_time;
	}
	cout << r2(total_weight_turntime / process_num) << endl;
}

//按照到达时间进行升序排序
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

//调入cpu服务的算法（更新进程数据）
void server(process &p, int rr, int &time, int &result)
{
	//若当前时间片可以完成本进程
	if (p.time_left <= rr)
	{
		//更新所有信息
		p.fin_time = time + p.time_left;
		time = time + p.time_left;
		p.time_left = 0;
		p.turn_time = p.fin_time - p.come_time;
		p.weight_turn_time = p.turn_time / p.server_time;
		result = 1;
	}
	//无法完成当前进程，需以后继续服务
	else
	{
		//更新当前时间以及进程剩余时间
		p.time_left = p.time_left - rr;
		time = time + rr;
		result = 0;
	}
}

//仅仅用来输出结果保留两位小数、看起来简洁
float r2(float a)
{
	return(round(a * 100) / 100.0);
}


/*逻辑顺序：
判断当前时间是否有新的进程到达
1.有新的进程到达：将进程下标存储 继续判断当前服务中的进程是否需要回队
2.无：更新当前时间+1
1.1.需要回队：存储正在服务的进程的下标
1.2.已经完成服务：count++。
进行服务队列中第一个进程、更新队首。

直到count = process_num，结束循环，输出结果。
*/
void RR(process* p, int process_num,int rr)
{
	sort_come(p, process_num);
	int q[100];		//模拟队列，用来存储进程下标	
	int time = 0;	//当前时间	
	int in_num = 0;	//判断是否所有进程均已进队
	int count = 0;	//控制循环结束
	int result = -1;	//对一个个入队的进程进行特殊处理
	int i = 0;		//队首下标
	int j = 0;		//队尾下标
	//初始化每个进程的剩余时间
	for (int r = 0; r < process_num; r++)
	{
		p[r].time_left = p[r].server_time;
	}
	while (count < process_num)
	{
		if (in_num < process_num)	//若还有进程没有进队
		{
			for (int s = 0; s < process_num; s++)	//判断当前时间是否有新的进程需要进队
			{
				if (p[s].come_time <= time && p[s].flag == 0)
				{
					q[j] = s;	//将进队的进程逐一插入到队列尾部
					p[s].flag = 1;	//更新刚进队的进程的标志
					in_num++;	//更新进队进程的数量
					j++;	//更新队尾下标
				}
			}
			if (result == 0)	//若上一个进程没有服务完
			{
				q[j] = q[i-1];		//插入队尾
				j++;
			}
			else if (result == 1)	//服务完毕
			{
				count++;	//完成数量+1
			}
			server(p[q[i]], rr, time, result);	//对队首进程进行服务
			i++;
		}
		//若所有进程均进队
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
			if (i != j)//当队列中有大于2个进程，仍需继续更新队首下标
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
