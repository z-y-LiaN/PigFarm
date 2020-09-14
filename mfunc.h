#pragma once
#include"pigsty.h"
#include<string.h>
#include<iostream>
using namespace std;
extern double TotMoney;
extern int MonthCount;
extern int DayCount;
extern int sell_Times_Count;
extern int allPigsNum;
void RequireSell();
void saveInfo(); 
void save_SoldInfo(int outpignum, double sellprice, int Bpig, int SFpig, int BFpig,double money);
void buyPigs(int Bpig, int SFpig, int BFpig, PigSty*);
void StartfromLast(PigSty*);
void StartNew(PigSty*);
void savefile(PigSty*);
void Menu_initial();
void statistic(PigSty*);
void RequireOneSty(PigSty*);
void RequireOnePig(PigSty*);
int NotallDead(PigSty*);
void epd(PigSty* Stys,int i,int j);
void RequireAllPigs(PigSty*);
void isolate(PigSty* Stys,int i,int j);
void OutPigs(PigSty*);
bool is_all_BstyFull(PigSty*);
int getAllPigs(PigSty* pigStys);
////////////////////////////////////////
int rightNum(string str) {
	//获取长度
	for (int i = 0; i < str.size(); i++) {
		if (str[i] < '0' || str[i]>'9') return -1;
	}
	int out = 0;
	for (int i = 0; i < str.size(); i++) {
		int tmp =str[i] - '0';
		out = out * 10 + tmp;
	}
	return out;
}

