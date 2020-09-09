#include"mfunc.h"
#include<stdlib.h>
#include<time.h>
#include<iostream>
#include<fstream>
using namespace std;
void Menu() {
	cout << "\n\n\n\n\n\n\n";
	cout << "           ********************************************************\n";
	cout << '\n';
	cout << "                            来和猪猪们玩耍吧：                        \n";
	cout << '\n';
	cout << "                       请选择游戏操作：\n";
	cout << '\n';
	cout << "                                1.开始游戏\n";
	cout << '\n';
	cout << "                                2.帮助\n";
	cout << '\n';
	cout << "                                3.养猪比敲代码都无聊，不玩啦\n";
	cout << '\n';
	cout << "           ======================================================\n";
}
//读取出圈信息 
void read456() {
	ifstream read;
	read.open("456.txt");
	if (!read) {
		cout << "打开出圈信息文件失败";
		exit(0);
	}
	char flag;
	read >> flag;
	if (flag == '#') {
		cout << "无记录" << endl;
		return;
	}
	int times, outpigs, sellprice, bpig, lpig, wpig;
	while (read>>times) {
		if (read.eof()) break;
		read >> outpigs >> sellprice >> bpig >> lpig >> wpig;
		cout << "第" << times / 4 + 1 << "年";
		cout << "第" << (times % 4 + 1) << "个3月：\n";
		cout << "出圈猪数：" << outpigs << "     获得收益：" << sellprice << "   购进黑猪数：" << bpig << "   小花猪数：" << lpig << "   大白花猪数：" << wpig << endl;
	}
	read.close();
}
//保存猪 
void save_789() {
	ofstream save;
	save.open("789.txt");
	if (!save) {
		cout << "无法打开文件，保存全局变量失败！"; exit(0);
	}
	else {
		save << allpig << "   " << money << "   " << month << "   " << day << "   " << sellcount << endl;
		cout << "此次游戏保存成功！退出游戏请按0，继续游戏请按1：" << endl;
		save.close();
	}
}
//保存售卖出去的信息 
void save_456(int outpignum, double sellprice, int bpig, int lpig, int wpig) {
	ifstream testin;
	testin.open("456.txt");
	char flag;
	testin >> flag;
	if (flag == '#') {
		testin.close();
		ofstream testout;
		testout.open("456.txt");
		testout << '$';
		testout.close();
	}
	else testin.close();
	ofstream save("456.txt", ios::app);
	save << sellcount << endl;
	save << outpignum << "   " << sellprice << "    " << bpig << "   " << lpig << "   " << wpig  << endl;
	save.close();
}
//买新猪，放入养猪场 
void buypig(int bpig, int lpig, int wpig, PigFarm pjuan[]) {
	//小黑还是放在小黑圈 里 
	int average = allpig / 100 + 1;
	while (bpig--) {
		for (int i = 0; i < 100; i++) {
			if (pjuan[i].getisBlackPig() == 1 && pjuan[i].getcount() <=average) {
				pjuan[i].insert(1);
				break;
			}
			if (pjuan[i].gethead() == NULL) {
				pjuan[i].insert(1);
				pjuan[i].setisBlackPig(1);
				break;
			}
		}
	}
	//平均分配	
	
	while (1) {
		for (int i = 0; i < 100; i++) {
			if (pjuan[i].getisBlackPig() == 0) {
				if (lpig > 0 && pjuan[i].getcount() <= average) {
					pjuan[i].insert(2);
					lpig--;
				}
				if (wpig > 0 && pjuan[i].getcount() <= average) {
					pjuan[i].insert(3);
					wpig--;
				}
			}
		}
		if (lpig == 0 && wpig == 0)break;
	}
}

void Menu_pigsty_byfile(PigFarm pjuan[]) {
	ifstream getinfo;
	getinfo.open("789.txt");  // 789是保存的数据 
	getinfo >> allpig >> money >> month >> day >> sellcount;
	getinfo.close();
	ifstream read;    //123 
	read.open("123.txt");
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
			else read >> p->weight >> p->growmonth >> p->growday;  //读入 体重，月份，日期 
			pjuan[i].addpig(p);  //把猪添加到后面 
		}
	}
	read.close();
}
//初始化猪圈 
void Menu_pigsty(PigFarm pjuan[]) {
	allpig = 500;
	money = 20000;
	month = 0;
	day = 0;
	sellcount = 0;
	ofstream f;
	f.open("123.txt");//打开123文件 
	f << 0; //向文件里面写个0 ，写的时候不需要这个文件一定存在，不存在就在目录下面自动创建一个 
	f.close(); //关闭文件 
	f.open("456.txt"); //打开456文件 
	f << '#'; //写个# 
	f.close(); //关闭文件 
	pig* p;
	srand((unsigned)time(NULL));
	int count = 500;       //假设初始化有500头猪 
	while (count--) {
		p = new pig;
		p->species = rand() % 3 + 1;  //随机初始化品种 
		p->weight = double(rand() % 30 + 20);  //随机初始化体重 
		p->growmonth = 0;
		p->growday = 0;
		//cout << "count = " << count << "species " << p->species << "weight " << p->weight << endl;
		int i = rand() % 99;
		//	cout<<"      "<<pjuan[i].getcount()<<endl;	
		//	for(int i=0;i<100;i++){
				//如果一头猪是小黑，并且 这个圈是黑圈或者空圈  并且 圈没有满 
		if (p->species == 1 && (pjuan[i].getisBlackPig() == 1 || pjuan[i].gethead() == NULL) && pjuan[i].getcount() < 10) {
			p->number = pjuan[i].getcount();
			pjuan[i].addpig(p);  //把这个猪入圈 
			pjuan[i].setisBlackPig(1);  //标记这个为黑圈 
			continue;
		}
		//如果不是 小黑，并且这个圈全是花花    且没有满 
		else if (p->species != 1 && pjuan[i].getisBlackPig() == 0 && pjuan[i].getcount() < 10) {//<10???
			p->number = pjuan[i].getcount();
			pjuan[i].addpig(p);   // 
			continue;
		}
		else count++;
		delete p;
	}
	//for (int i = 0; i < 100; i++)
		//cout << "第" << i << "个猪圈总数" << pjuan[i].getcount() << endl;
}
//把程序数输出到文件里面 
void savefile(PigFarm pjuan[]) {
	ofstream savefile;
	savefile.open("123.txt");
	if (!savefile) {
		cout << "打开保存文件失败！";
		exit(0);
	}
	savefile << 1 << endl;//向文件里面写个1 
	for (int i = 0; i < 100; i++) {
		pjuan[i].save(savefile);
	}
	savefile.close();
}
//查询操作的选择 
void check() {
	system("cls");
	cout << "\n\n\n\n\n\n\n";
	cout << "            ======================================================\n";
	cout << "                                         查询                          \n";
	cout << '\n';
	cout << "                       请选择操作：\n";
	cout << '\n';
	cout << "                            1.查询当前某一猪圈猪的数量和种类\n";
	cout << "                            2.查询某猪圈某头猪的状态信息\n";
	cout << "                            3.统计每种猪的数量、体重、饲养时间分布\n";
	cout << "                            4.查询近5年猪的销售和购入记录\n";
	cout << "                            5.打印当前猪场猪的所有信息\n";
	cout << "                            6.返回\n";
	cout << '\n';
	cout << "            ======================================================\n";
}
//初始化 
void Menu_initial() {
	system("cls");
	cout << "\n\n\n\n\n\n\n";
	cout << "            ======================================================\n";
	cout << "                                          我的猪场                        \n";
	cout << '\n';
	cout << "                       请选择操作：\n";
	cout << '\n';
	cout << "                                 1.查询\n";
	cout << "                                 2.出圈并购猪\n";
	cout << "                                 3.重新游戏\n";
	cout << "                                 4.保存游戏\n";
	cout << "                    5.下一天                      6.下个月        \n";
	cout << '\n';
	cout << "               当前金币数：" << money << "    总猪数：" << allpig << "   饲养时间:"; if (month > 0)cout << month << "个月"; if (day >= 0)cout << day << "天";
	cout << '\n';
	cout << "           ======================================================\n";
}
//获得100个猪圈的总数 
int getallpig(PigFarm pjuan[]) {
	int allcount = 0;
	for (int i = 0; i < 100; i++) {
		allcount += pjuan[i].getcount();
	}
	return allcount;
}
//
void statistic(PigFarm pjuan[])
{
	int blackTot = 0; double Bget150 = 0; int Blt30 = 0; int Bm3_6 = 0; int Bm7_12 = 0;
	int sflowerTot = 0; double SFget150 = 0;  int SFlt30 = 0; int SFm3_6 = 0; int SFm7_12 = 0;
	int bflowerTot = 0;  double BFget150 = 0; int BFlt30 = 0; int BFm3_6 = 0; int BFm7_12 = 0;
	for (int i = 0; i < 100; i++)
	{
		pig* p = pjuan[i].gethead();
		while (p)
		{
			if (p->species == 1)
			{
				blackTot++;
				if (p->weight >= 150)	Bget150++;  //体重大于150 
				if (p->growday < 30)   Blt30++;    //饲养时间小于1个月 
				if (p->growmonth >= 3 && p->growmonth < 7) Bm3_6++;  //饲养时间3-6个月 
				if (p->growmonth >= 7) Bm7_12++;	  //饲养时间大于半年 
			}
			else if (p->species == 2)
			{
				sflowerTot++;
				if (p->weight >= 150)	SFget150++;  //体重大于150 
				if (p->growday < 30)   SFlt30++;    //饲养时间小于1个月 
				if (p->growmonth >= 3 && p->growmonth < 7) SFm3_6++;  //饲养时间3-6个月 
				if (p->growmonth >= 7) SFm7_12++;	  //饲养时间大于半年 

			}
			else if (p->species == 3)
			{
				bflowerTot++;
				if (p->weight >= 150)	BFget150++;  //体重大于150 
				if (p->growday < 30)   BFlt30++;    //饲养时间小于1个月 
				if (p->growmonth >= 3 && p->growmonth < 7) BFm3_6++;  //饲养时间3-6个月 
				if (p->growmonth >= 7) BFm7_12++;	  //饲养时间大于半年 	

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

