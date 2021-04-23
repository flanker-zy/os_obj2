#pragma once
#include<iostream>
#include<fstream>

using namespace std;

typedef struct pro {
	int flag = 0;   //用来标记是否被服务过
	char name = 'A';	//进程名
	float come_time = 0;	//到达时间
	float server_time = 0;	//服务时间
	float fin_time = 0;		//结束服务时间
	float turn_time = 0;	//周转时间
	float weight_turn_time = 0;		//带权周转时间
	float time_left = 0;	//服务后剩余时间
}process;
void in(process* p, int process_num);
void out(process* p, int process_num);
void sort_come(process* p, int process_num);
void server(process& p, int rr, int& time, int& result);
float r2(float a);