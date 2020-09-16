#include"pigsty.h"
#include"mfunc.h"
#include"printFunc.h"
#include<iostream>
#include<fstream>
#include<iomanip>
using namespace std;
double TotMoney;
int MonthCount;
int DayCount;
int sell_Times_Count ;
int allPigsNum;
int main()
{
	srand((unsigned)time(NULL));
	PigSty Stys[100]; //创建一个类数组，每个数组元素都是一个猪圈 
	Prompt();
	ifstream infile;   //读文件 
	infile.open("isFirstGame.txt"); //保存的是0
	int flag;   
	infile >> flag; 
	if (flag == 0)		StartNew(Stys); 
	else	StartfromLast(Stys); 
	infile.close();
	allPigsNum = getAllPigs(Stys);
	int MenuChoice;
	cout << "请输入你想要继续的操作：" << endl;
	while (1) {
		int i = rightNum();
		if (i<1||i>2) {
			cout << "输入错误，请重新输入"<<endl;
			continue;
		}
		else {
			MenuChoice = i; break;
		}
	}
	do {
		switch (MenuChoice) 
		{
		case 1: {//开始游戏
			Menu_initial();
			int GameChoice;
			while (1) {
				int i = rightNum();
				if (i < 1 || i>7) {
					cout << "输入错误，请重新输入" << endl;
					continue;
				}
				else {
					GameChoice = i; break;
				}
			}
			do {
				switch (GameChoice) {
				//查询
				case 1: {  
					check();
					int RequireChoice;
					while (1) {
						int i = rightNum();
						if (i < 1 || i>6) {
							cout << "输入错误，请重新输入" << endl;
							continue;
						}
						else {
							RequireChoice = i; break;
						}
					}
					do {
						switch (RequireChoice) {		
							case 1: {
								RequireOneSty(Stys);  //查询单个猪圈情况
								break;
							}
							case 2: {
								RequireOnePig(Stys);  //查询具体某只猪情况
								break;
							}
							case 3: { 
								statistic(Stys);      //查询当前猪场每种猪的情况
								break;
							}
			 				case 4: { 
								RequireSell();		  //查询近五年销售和购入记录
								break;
							}
							case 5: {
								RequireAllPigs(Stys); //查询猪场每个猪圈所有猪的信息
								break;
							}
							case 6: {
								break;               //返回上一级
							}
							/*default: {
								cout << "输入错误，请重新输入："; 
								break;
							}*/
						}
						if (RequireChoice == 6) break;
						//if(RequireChoice<6&&RequireChoice>1)
						cout << "游戏继续，请选择操作：";
						while (1) {
							int i = rightNum();
							if (i < 1 || i>6) {
								cout << "输入错误，请重新输入" << endl;
								continue;
							}
							else {
								RequireChoice = i; break;
							}
						}
					} while (1);
					
					Menu_initial();
					break;
				}
				case 2: {//出圈&购猪
					if (MonthCount + DayCount / 30 < 3) {
						cout << "上次出圈到现在饲养时间不足三月，请别着急出圈噢\n" << endl;
						break;
					}
					OutPigs(Stys);
					
					break;
				}
				case 5: {//重新游戏
					for (int i = 0; i < 100; i++) 
						Stys[i].clearStys();
					StartNew(Stys);
					Menu_initial();
					break;
				}
				case 6: { //保存游戏
					savefile(Stys);
					saveInfo();
					int ex;
					while (1) {
						int i = rightNum();
						if (i<0||i>1) {
							cout << "输入错误，请重新输入" << endl;
							continue;
						}
						else {
							ex= i; break;
						}
					}
					if (ex == 0) 	
						exit(0);
					break;
				}
				case 3: {//下一天
					if (MonthCount == 3)
					{
						cout << "已经三个月啦，请先出圈" << endl;
						break;
					}
					for (int i = 0; i < 100; i++) {
						Stys[i].next(1);
					}
					DayCount++;
					if (DayCount > 30) {
						DayCount -= 30;
						MonthCount++;
					}
					Menu_initial();
					break;
				}
				case 4: { //下个月
					if (MonthCount == 3)
					{
						cout << "已经三个月啦，请先出圈" << endl;
						break;
					}
					for (int i = 0; i < 100; i++) {
						Stys[i].next(30);
					}
					MonthCount++;
					Menu_initial();
					break;
				}
				case 7: {//疫情模拟
					for (int i = 0; i < 100; i++)
						Stys[i].clearStys();
					StartNew(Stys);
					int i, j;  //第i个圈，第j值猪 
					while (1) {
						i = rand() % 100;
						j = rand() % 10;
						bool have = Stys[i].havePig(j);
						if (have)
							break;
						else continue;
					}
					cout <<"------------疫情发生--------------"<< endl;
					cout << "第 " << i << " 个猪圈的编号为 " << j << " 的猪染病" << endl;
					cout << "是否采取隔离措施:" << endl;
					cout << "          1 - 是\n          2 - 否  :   ";
					int choose; cin.get();
					while (1) {
						int i = rightNum();
						if (i < 1 || i>2) {
							cout << "输入错误，请重新输入正确选择" << endl;
							continue;
						}
						else {
							choose = i; break;
						}
					}
					if (choose == 2) {
						epd(Stys, i, j);
					}
					else if (choose == 1) {
						isolate(Stys,i,j);
						cout << "   该病猪已被隔离完成" << endl;
						if (Stys[i].getState() == 0) cout << "   隔离即时，该猪圈的猪全部健康" << endl;
						cout << "显示第" << i << "个猪圈情况：" << endl;
						Stys[i].print();
					}
					break;
				}
			}
				if(GameChoice>0&&GameChoice<8)
				 cout << "游戏继续，请选择操作：";
				while (1) {
					int i = rightNum();
					if (i < 1 || i>7) {
						cout << "输入错误，请重新输入" << endl;
						continue;
					}
					else {
						GameChoice = i; break;
					}
				}
			} while (1);
			break;
		}
		case 2:  exit(0); 
		}
	} while (1);
}