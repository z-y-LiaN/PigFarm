#pragma once
#include<iostream>
using namespace std;
struct pig {
	int species;
	int breedDay;
	int breedMon;
	double weight;
	int number;
	int isDead;
	pig* next;
};
//猪圈类 
class PigSty {
private:
	int thisSty_tot;
	pig* head;
	int isBlack;
	int state;
public:
	PigSty();
	void print();  //打印 
	void addOnePig(pig* p); //添加猪 
	void searchpig(int number); //查找一个猪圈里的某只猪 
	void sellpig();
	void insert(int species);
	double getPrice();   //获得价格

	int getSpecies(int i);
	int getBreedMon(int i);
	int getBreedDay(int i);

	double getWeight(int i);

	void clearStys();
	//   int getallpig(pigjuan pjuan[]);
	void setisBlackPig(int i);
	//获取小黑数量 
	int get_BlackNum();
	//获取小花数量 
	int get_SflowerNum();
	//获取大花数量 
	int get_BflowerNum();
	//获取总数量 
	int getTot();
	//判断是否为小黑 
	int isBlackPig();
	void save(ofstream& savefile);
	//获取猪圈头指针               
	pig* getHead();
	//刷新第二天体重 
	void next(int nexttime);
	//查找该个猪圈某个地方有没有猪 
	bool havePig(int number);
	// 
	int getState(); 
	void setisDead(int num);
	void Pro50();
	void Pro15();
	void setState();
	void deleteOne(int j);
};

