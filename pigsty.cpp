#include<iostream>
#include<fstream>
#include"pigsty.h"
#include<time.h>
#include<iomanip>
using namespace std;
//构造
PigFarm::PigFarm() {
	cntnum = 0;
	isblackspecies = 0;
	head = NULL;
}
//获取小黑数量 
int PigFarm::getspecies1() {
	int count = 0;
	for (int i = 0; i < cntnum; i++) {
		if (getspecies(i) == 1)
			count++;
	}
	return count;
}
//获取小花数量 
int PigFarm::getspecies2() {
	int count = 0;
	for (int i = 0; i < cntnum; i++) {
		if (getspecies(i) == 2)
			count++;
	}
	return count;
}
//获取大花数量 
int PigFarm::getspecies3() {
	int count = 0;
	for (int i = 0; i < cntnum; i++) {
		if (getspecies(i) == 3)
			count++;
	}
	return count;
}
//获取该猪圈的总数量 
int PigFarm::getcount() {
	return cntnum;
}
//判断是否为小黑 
int PigFarm::getisBlackPig() {
	return isblackspecies;
}
//获取猪圈头指针               
pig* PigFarm::gethead() {
	return head;
}
//添加猪，尾插法 
void PigFarm::addpig(pig* p) {
	cntnum++;
	p->next = NULL;
	if (head == NULL) {
		head = p;
	}
	else {
		pig* p1 = head;
		while (p1->next) {
			p1 = p1->next;
		}
		p1->next = p;
	}
}
//获取第i个猪的品种 
int PigFarm::getspecies(int i) {
	pig* p = head;
	for (int j = 0; j < i && p; j++) {
		p = p->next;
	}
	return p->species;
}

//获取第i个猪体重 
double PigFarm::getweight(int i) {
	pig* p = head;
	for (int j = 0; j < i && p; j++) {
		p = p->next;
	}
	return p->weight;
}
//获取第i个猪的生长月份 
int PigFarm::getgrowmonth(int i) {
	pig* p = head;
	for (int j = 0; j < i && p; j++) {
		p = p->next;
	}
	return p->growmonth;
}
//获取第i个猪生长日期 
int PigFarm::getgrowday(int i) {
	pig* p = head;
	for (int j = 0; j < i && p; j++) {
		p = p->next;
	}
	return p->growday;
}

//获取最终出价。出圈 
double PigFarm::getprice() {
	double sellprice = 0;
	if (head == 0)
		return 0;
	int month, day, flag = 0;
	pig* p = head, * p1 = p;
	//依次循环判断每头猪 
	while (p) {
		month = p->growmonth;
		day = p->growday;
		while (day >= 30) {
			day -= 30;
			month++;
		}
		//月份大于12，或者体重大于75kg 
		if (month >= 12 || p->weight > 75) {
			if (cntnum == 1) {
				setisBlackPig(0);
				head = NULL;
				delete p;
				cntnum--;
				break;
			}
			//如果最后只剩一头猪，且要出栏，最后释放指针，要跳出循环  
			// 小黑 
			if (p->species == 1) {
				sellprice += 30 * p->weight;
			}
			//小花 
			if (p->species == 2) {
				sellprice += 14 * p->weight;
			}
			//大花 
			if (p->species == 3) {
				sellprice += 12 * p->weight;
			}
			
			//挂空警告 
			p1->next = p->next;
			delete p;
			p = p1->next;
			cntnum--;
			continue;
		}
		else if (flag == 0) {
			flag = 1;
			head = p;
		}
		p1 = p;
		p = p1->next;
	}
	return sellprice;  //获得该个猪圈出栏总价 
}

//程序输出到文件 
void PigFarm::save(ofstream& savefile) {

	if (head == NULL) {
		savefile << '$' << endl;
		return;
	}
	else {
		pig* p = head;
		int i = 0;
		savefile << cntnum << endl;//向文件写入该个猪圈总数 ，换行 
		while (p) {
			savefile << getspecies(i) << "   " << getweight(i) << "   " << getgrowmonth(i) << "   " << getgrowday(i) << endl;
			//依次向文件写入品种，体重，月份，日子 
			i++;
			p = p->next;
		}
	}
}

//查询该个猪圈的信息 
void PigFarm::print() {
	if (cntnum == 0) {
		cout << "    属性：空猪圈 " << endl;
		return;
	}
	if (isblackspecies == 1) {
		cout << "    属性：黑猪圈 " <<"总量： "<< cntnum<<" 头"<<endl;
	}
	else
		cout << "    属性：花猪圈 " << "总量： " << cntnum << " 头"<< endl;
	pig* p = head;
	while (p) {
		int month = p->growmonth;
		int day = p->growday;
		while (day >= 30) {
			day -= 30;
			month++;
		}
		int i = p->number;
		cout <<"    "<< i << "号猪：";
		if (p->species == 1)cout << "黑猪     ";
		if (p->species == 2)cout << "小花猪   ";
		if (p->species == 3)cout << "大白花猪 ";
		cout<<"体重:"<<setw(5)<< p->weight << "Kg  ";
		cout << "饲养时间:  " << month << "月" << day << "天" << endl;
		p = p->next;
	}
}
//刷新第二天体重 
void PigFarm::next(int nexttime) {
	srand((unsigned)time(NULL));
	pig* p = head;
	while (p) {
		p->weight += (double)(rand() % 12) * nexttime / 10;//(直接取余1.2不行啊 
		if (nexttime == 1)	p->growday++;
		else p->growmonth++;
		p = p->next;  //存疑 
	}
}

//查找该个猪圈某个地方有没有猪 
bool PigFarm::search(int number) {
	pig* p = head;
	while (p) {
		if (p->number == number)
			return true;
		else
			p = p->next;
	}
	return false;
}

//猪圈全部清空
void PigFarm::clearpigjuan() {
	if (head == NULL) {
		return;
	}
	else {
		pig* p = head;
		pig* p1 = p;
		cntnum = 0;
		setisBlackPig(0);
		head = NULL;
		while (p) {
			p1 = p;
			p = p->next;
			delete p1;
		}
		delete p;
	}
}
//补充猪仔，按照品种补充猪仔 
void PigFarm::insert(int species) {
	pig* p = new pig;
	srand((unsigned)time(NULL));
	p->species = species;
	p->weight = double(rand() % 30 + 20);
	p->growmonth = 0;
	p->growday = 0;
	if (head == NULL) {
		p->number = 0;
		p->next = NULL;
		head = p;
		cntnum++;
		return;
	}
	if (head->number != 0) {
		p->number = 0;
		p->next = head;
		head = p;
		cntnum++;
		return;
	}
	else {
		pig* p1 = head, * p2 = p1;
		int k = 0;
		while (p1->number == k && p1->next) {
			k++;
			p2 = p1;
			p1 = p1->next;
		}
		if (p1->next == NULL) {
			p->number = cntnum;
			p->next = NULL;
			p1->next = p;
		}
		else {
			p->number = k;
			p2->next = p;
			p->next = p1;
		}
		cntnum++;
	}
}
void PigFarm::setisBlackPig(int i) {
	isblackspecies = i;
}
