#pragma once
#include<iostream>
#include<fstream>

using namespace std;

typedef struct pro {
	int flag = 0;   //��������Ƿ񱻷����
	char name = 'A';	//������
	float come_time = 0;	//����ʱ��
	float server_time = 0;	//����ʱ��
	float fin_time = 0;		//��������ʱ��
	float turn_time = 0;	//��תʱ��
	float weight_turn_time = 0;		//��Ȩ��תʱ��
	float time_left = 0;	//�����ʣ��ʱ��
}process;
void in(process* p, int process_num);
void out(process* p, int process_num);
void sort_come(process* p, int process_num);
void server(process& p, int rr, int& time, int& result);
float r2(float a);