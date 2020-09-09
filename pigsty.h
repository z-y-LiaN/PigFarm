#pragma once
#include<iostream>
using namespace std;
struct pig {
	int species;
	int growday;
	int growmonth;
	double weight;
	int number;
	pig* next;
};
//猪圈类 
class PigFarm {
private:
	int cntnum;
	pig* head;
	int isblackspecies;
public:

	//		pigjuan();
	//		int setcnt(int i){
	//			return i;
	//		} 
	PigFarm();
	void print();  //打印 
	void addpig(pig* p); //添加猪 
	void searchpig(int number); //查找一个猪圈里的某只猪 
	void sellpig();
	void insert(int species);
	double getprice();   //获得价格

	int getspecies(int i);
	int getgrowmonth(int i);
	int getgrowday(int i);

	double getweight(int i);

	void clearpigjuan();
	//   int getallpig(pigjuan pjuan[]);
	void setisBlackPig(int i);
	//获取小黑数量 
	int getspecies1();
	//获取小花数量 
	int getspecies2();
	//获取大花数量 
	int getspecies3();
	//获取总数量 
	int getcount();
	//判断是否为小黑 
	int getisBlackPig();
	void save(ofstream& savefile);
	//获取猪圈头指针               
	pig* gethead();
	//刷新第二天体重 
	void next(int nexttime);
	//查找该个猪圈某个地方有没有猪 
	bool search(int number);
	//如果猪圈空了， 

};

