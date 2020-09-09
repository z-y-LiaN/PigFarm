#pragma once
#include"pigsty.h"
#include<iostream>
using namespace std;
extern double money;
extern int month;
extern int day;
extern int sellcount;
extern int allpig;

void Menu();//菜单的初始化

void read456();//读取出圈信息 
void save_789();  //保存所有猪的数量，余额，月份 

//保存售卖出去的信息 
void save_456(int outpignum, double sellprice, int bpig, int lpig, int wpig);
//买新猪，放入养猪场 
void buypig(int bpig, int lpig, int wpig, PigFarm pjuan[]);
//补充猪仔，按照品种补充猪仔 
void Menu_pigsty_byfile(PigFarm pjuan[]);
//初始化猪圈 
void Menu_pigsty(PigFarm pjuan[]);
//把程序数输出到文件里面 
void savefile(PigFarm pjuan[]);
//查询操作的选择 
void check();
//初始化 
void Menu_initial();
//获得100个猪圈的总数 
int getallpig(PigFarm pjuan[]);
//养猪场情况
void statistic(PigFarm pjuan[]);

