#include"mfunc.h"
#include<stdlib.h>
#include<time.h>
#include<iostream>
#include<fstream>
#include<iomanip>
using namespace std;
//读取出圈信息 
void RequireSell() {
	ifstream read;
	read.open("AllPigs.txt");
	if (!read) {
		cout << "打开文件失败";
		exit(0);
	}
	char flag;
	read >> flag;
	if (flag == '#') {
		cout << "无记录" << endl;
		return;
	}
	int times, outpigs, bpig, lpig, wpig;
	double sellprice, money;
	while (read>>times) {
		if (read.eof()) break;
		read >> outpigs >> sellprice >> bpig >> lpig >> wpig>>money;
		cout << "第" << times / 4 + 1 << "年";
		cout << "第" << (times % 4 + 1) << "个3月：\n";
		cout << "出圈猪数：" << outpigs << "     获得收益：" << sellprice << "   购进黑猪数：" << bpig << "   小花猪数：" << lpig << "   大白花猪数：" << wpig <<"   余额："<<money<< endl;
	}
	read.close();
}
//保存猪 
void saveInfo() {
	ofstream save;
	save.open("Info.txt");
	if (!save) {
		cout << "打开文件失败！"; exit(0);
	}
	else {
		save << allPigsNum << "   " << TotMoney << "   " << MonthCount << "   " << DayCount << "   " << sell_Times_Count << endl;
		cout << "本次游戏保存成功！退出游戏请按0，继续游戏请按1：" << endl;
		save.close();
	}
}
//保存售卖出去的信息 
void save_SoldInfo(int outpignum, double sellprice, int bpig, int lpig, int wpig,double money) {
	ifstream testin;
	testin.open("AllPigs.txt");
	char flag;
	testin >> flag;
	if (flag == '#') {
		testin.close();
		ofstream testout;
		testout.open("AllPigs.txt");
		testout << '$';
		testout.close();
	}
	else testin.close();
	ofstream save("Allpigs.txt", ios::app);
	save << sell_Times_Count << endl;
	save << outpignum << "   " << sellprice << "    " << bpig << "   " << lpig << "   " << wpig <<"  "<<money << endl;
	save.close();
}
//买新猪，放入养猪场 
void buyPigs(int bpig, int lpig, int wpig, PigSty pigStys[]) {
	//小黑还是放在小黑圈 里 
	int average = allPigsNum / 100 + 1;
	while (bpig--) {
		for (int i = 0; i < 100; i++) {
			if (pigStys[i].isAllBlack() == 1 && pigStys[i].getTot() <=average) {
				pigStys[i].insert(1);
				break;
			}
			if (pigStys[i].getHead() == NULL) {
				pigStys[i].insert(1);
				pigStys[i].setisBlackPig(1);
				break;
			}
		}
	}
	//平均分配	
	while (1) {
		for (int i = 0; i < 100; i++) {
			if (pigStys[i].isAllBlack() == 0) {
				if (lpig > 0 && pigStys[i].getTot() <= average) {
					pigStys[i].insert(2);
					lpig--;
				}
				if (wpig > 0 && pigStys[i].getTot() <= average) {
					pigStys[i].insert(3);
					wpig--;
				}
			}
		}
		if (lpig == 0 && wpig == 0)break;
	}
}

void StartfromLast(PigSty Stys[]) {
	ifstream getinfo;
	getinfo.open("Info.txt");   
	getinfo >> allPigsNum >> TotMoney >> MonthCount >> DayCount >> sell_Times_Count;
	getinfo.close();
	ifstream read; 
	read.open("isFirstGame.txt");
	if (!read) {
		cout << "读取保存的数据失败！";
		exit(0);
	}
	int t, cntnum;
	pig* p;
	read >> t;
	for (int i = 0; i < 100; i++) {
		read >> cntnum;  //读取每个猪圈数量  
		for (int j = 0; j < cntnum; j++) {
			p = new pig;
			p->number = j;     //每头猪编号 
			read >> p->species;   //读入品种 
			if (p->species == '$') {     //如果读到$就退出 
				delete p;
				break;
			}
			else read >> p->weight >> p->breedMon >> p->breedDay;  //读入 体重，月份，日期 
			Stys[i].addOnePig(p);  //把猪添加到后面 
		}
	}
	read.close();
}
//初始化猪圈 
void StartNew(PigSty Stys[]) {
	allPigsNum = 1000;
	TotMoney = 300000;
	MonthCount = 0;
	DayCount = 0;
	sell_Times_Count = 0;
	ofstream f;
	f.open("isFirstGame.txt");//文件 
	f << 0; //向文件里面写个0 ，写的时候不需要这个文件一定存在，不存在就在目录下面自动创建一个 
	f.close(); //关闭文件 
	f.open("Allpigs.txt"); //打开456文件 
	f << '#'; //写个# 
	f.close(); //关闭文件 
	pig* p;
	int count = 1000;       //假设初始化有1000头猪 
	while (count--) {
		p = new pig;
		p->species = rand() % 3 + 1;  //随机初始化品种 
		p->weight = double(rand() % 31 + 20);  //随机初始化体重 
		p->breedMon = 0;
		p->breedDay = 0;
		p->isDead = 0;
		int i = rand() % 100;
		if (p->species == 1 && (Stys[i].isAllBlack() == 1 || Stys[i].getHead() == NULL) && Stys[i].getTot() < 10) {
			p->number = Stys[i].getTot();
			Stys[i].addOnePig(p);  //把这个猪入圈 
			Stys[i].setisBlackPig(1);  //标记这个为黑圈 
			continue;
		}
		//如果不是 小黑，并且这个圈全是花花    且没有满 
		else if (p->species != 1 && Stys[i].isAllBlack() == 0 && Stys[i].getTot() < 10) {//<10???
			p->number = Stys[i].getTot();
			Stys[i].addOnePig(p);   // 
			continue;
		}
		else count++;
		delete p;
	}
	for (int i = 0; i < 100; i++)
		Stys[i].setState();
}

//把程序数输出到文件里面 
void savefile(PigSty pigStys[]) {
	ofstream savefile;
	savefile.open("isFirstGame.txt");
	if (!savefile) {
		cout << "打开文件失败！";
		exit(0);
	}
	savefile << 1 << endl;//向文件里面写个1 
	for (int i = 0; i < 100; i++) {
		pigStys[i].save(savefile);
	}
	savefile.close();
}


//获得100个猪圈的总数 
int getAllPigs(PigSty pigStys[]) {
	int allPigs = 0;
	for (int i = 0; i < 100; i++) {
		allPigs += pigStys[i].getTot();
	}
	return allPigs;
}

void statistic(PigSty pigStys[])
{
	int blackTot = 0; double Bget150 = 0; int Blt30 = 0; int Bm3_6 = 0; int Bm7_12 = 0;
	int sflowerTot = 0; double SFget150 = 0;  int SFlt30 = 0; int SFm3_6 = 0; int SFm7_12 = 0;
	int bflowerTot = 0;  double BFget150 = 0; int BFlt30 = 0; int BFm3_6 = 0; int BFm7_12 = 0;
	for (int i = 0; i < 100; i++)
	{
		pig* p = pigStys[i].getHead();
		while (p)
		{
			if (p->species == 1)
			{
				blackTot++;
				if (p->weight >= 150)	Bget150++;  //体重大于150 
				if (p->breedDay < 30)   Blt30++;    //饲养时间小于1个月 
				if (p->breedMon >= 3 && p->breedMon < 7) Bm3_6++;  //饲养时间3-6个月 
				if (p->breedMon >= 7) Bm7_12++;	  //饲养时间大于半年 
			}
			else if (p->species == 2)
			{
				sflowerTot++;
				if (p->weight >= 150)	SFget150++;  //体重大于150 
				if (p->breedDay < 30)   SFlt30++;    //饲养时间小于1个月 
				if (p->breedMon >= 3 && p->breedMon < 7) SFm3_6++;  //饲养时间3-6个月 
				if (p->breedMon >= 7) SFm7_12++;	  //饲养时间大于半年 

			}
			else if (p->species == 3)
			{
				bflowerTot++;
				if (p->weight >= 150)	BFget150++;  //体重大于150 
				if (p->breedDay < 30)   BFlt30++;    //饲养时间小于1个月 
				if (p->breedMon >= 3 && p->breedMon < 7) BFm3_6++;  //饲养时间3-6个月 
				if (p->breedMon >= 7) BFm7_12++;	  //饲养时间大于半年 	

			}
			p = p->next;
		}
	}
	cout << "该养猪场所有猪的养殖情况如下：" << endl;
	cout << "---------------------------------------------------------" << endl;
	cout << "    所有猪总数：" << blackTot + sflowerTot + bflowerTot << " 头" << endl;
	cout << "    黑猪：" << endl;
	cout << "         总数：    " << blackTot << " 头" << endl;
	cout << "         体重：    " << endl;
	cout << "                   " << "＜150斤:  " << blackTot - Bget150 << " 头" << endl;
	cout << "                   " << "≥150斤： " << Bget150 << " 头" << endl;
	cout << "         饲养时间: " << endl;
	cout << "                   " << "＜1个月： " << Blt30 << " 头" << endl;
	cout << "                   " << "3-6个月： " << Bm3_6 << " 头" << endl;
	cout << "                   " << "≥半年 :  " << Bm7_12 << " 头" << endl;
	cout << "---------------------------------------------------------" << endl;
	cout << "    小花猪：" << endl;
	cout << "         总数：    " << sflowerTot << " 头" << endl;
	cout << "         体重：    " << endl;
	cout << "                   " << "＜150斤:  " << sflowerTot - SFget150 << " 头" << endl;
	cout << "                   " << "≥150斤： " << SFget150 << " 头" << endl;
	cout << "         饲养时间: " << endl;
	cout << "                   " << "＜1个月： " << SFlt30 << " 头" << endl;
	cout << "                   " << "3-6个月： " << SFm3_6 << " 头" << endl;
	cout << "                   " << "≥半年 :  " << SFm7_12 << " 头" << endl;
	cout << "---------------------------------------------------------" << endl;
	cout << "    大花白猪：" << endl;
	cout << "         总数：    " << bflowerTot << " 头" << endl;
	cout << "         体重：    " << endl;
	cout << "                   " << "＜150斤:  " << bflowerTot - BFget150 << " 头" << endl;
	cout << "                   " << "≥150斤： " << BFget150 << " 头" << endl;
	cout << "         饲养时间: " << endl;
	cout << "                   " << "＜1个月： " << BFlt30 << " 头" << endl;
	cout << "                   " << "3-6个月： " << BFm3_6 << " 头" << endl;
	cout << "                   " << "≥半年 :  " << BFm7_12 << " 头" << endl;
	cout << "---------------------------------------------------------" << endl;
}
//
void RequireOneSty(PigSty Stys[])
{
	int styNum;
	cout << "请输入想要查询的猪圈编号：";
	cin >> styNum;
	while (1)
	{
		if (styNum >= 0 && styNum < 100) break;
		else
		{
			cout << "输入有误，请重新输入： ";
			cin >> styNum;
		}
	}
	cout << "------------------------------------------------------------------" << endl;
	cout << "该猪圈的猪总数     " << "黑猪数量           " << "小花猪数量         " << "大白花猪数量       " << endl;
	cout << ' ' << left << setw(20) << Stys[styNum].getTot() << left << setw(20) << Stys[styNum].get_BlackNum() << left << setw(20) << Stys[styNum].get_SflowerNum() << left << setw(20) << Stys[styNum].get_BflowerNum() << "\n\n";
	cout << "------------------------------------------------------------------" << endl;
}
//
void RequireOnePig(PigSty Stys[])
{
	int styNum, pigNum;
	cout << "请输入猪圈号：";
	cin >> styNum;
	while (1) {
		if (styNum >= 0 && styNum < 100)
		{
			if (Stys[styNum].getTot() != 0) break;
			else
			{
				cout << "该猪圈为空猪圈，请重新输入：";
				cin >> styNum;
			}
		}
		else { cout << "输入错误，请重新输入："; cin >> styNum; }
	}
	cout << "此猪圈共有" << Stys[styNum].getTot() << "头猪 , 请输入查询编号 "<<endl;
	cin >> pigNum;
	while (1) {

		if (Stys[styNum].havePig(pigNum)) {
		//	cout << "编号" << pigNum << " 的猪圈有猪" << endl;
		//	cout << "品种是" << Stys[styNum].getSpecies(pigNum) << endl;
		//	cout << "体重是" << Stys[styNum].getWeight(pigNum) << endl;
		////	cout << "饲养时间是" << Stys[styNum].getSpecies(pigNum) << endl;
			break;
		}
		else
		{
			if (pigNum < 0 || pigNum>9)
				cout << "输入错误，请重新输入：";
			else
				cout << "不存在编号为"<<pigNum<<"的猪，请重新输入" << endl;
			cin >> pigNum;
		}
	}
	cout << "猪的品种                        体重/kg                        饲养时间" << endl;
	if (Stys[styNum].getSpecies(pigNum) == 1)   cout << " 黑猪    " << "                         ";
	if (Stys[styNum].getSpecies(pigNum) == 2)   cout << " 小花猪  " << "                         ";
	if (Stys[styNum].getSpecies(pigNum) == 3)	cout << "大白花猪 " << "                         ";
	cout << Stys[styNum].getWeight(pigNum) << "                              ";
	int month = Stys[styNum].getBreedMon(pigNum), day = Stys[styNum].getBreedDay(pigNum);
	while (day >= 30) {
		day -= 30;
		month++;
	}
	if (month > 0)cout << month << "月";
	cout << day << "天\n\n";
}


///////
void RequireAllPigs(PigSty*Stys) {
	for (int i = 0; i < 100; i++) {
		cout << "================================================" << endl;
		cout << i << "号圈:" << endl;
		Stys[i].print();
		if (i == 99) cout << "=================查询结束=======================" << endl;
	}
}
