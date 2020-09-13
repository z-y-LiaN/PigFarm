#pragma once
#include"pigsty.h"
#include<iostream>
using namespace std;
extern double TotMoney;
extern int MonthCount;
extern int DayCount;
extern int sell_Times_Count;
extern int allPigsNum;
void RequireSell();//读取出圈信息 
void saveInfo();  //保存所有猪的数量，余额，月份 

//保存售卖出去的信息 
void save_SoldInfo(int outpignum, double sellprice, int bpig, int lpig, int wpig,double money);
//买新猪，放入养猪场 
void buyPigs(int bpig, int lpig, int wpig, PigSty pjuan[]);
//补充猪仔，按照品种补充猪仔 
void StartfromLast(PigSty pjuan[]);
//初始化猪圈 
void StartNew(PigSty pjuan[]);
//把程序数输出到文件里面 
void savefile(PigSty pjuan[]);
//初始化 
void Menu_initial();
//获得100个猪圈的总数 
int getAllPigs(PigSty pjuan[]);
//养猪场情况
void statistic(PigSty pjuan[]);
//
void RequireOneSty(PigSty Stys[]);
//
void RequireOnePig(PigSty Stys[]);

int NotallDead(PigSty* Stys);

int epd(PigSty* Stys,int i,int j);

void RequireAllPigs(PigSty*Stys);

void isolate(PigSty* Stys,int i,int j);

void OutPigs(PigSty* Stys);

