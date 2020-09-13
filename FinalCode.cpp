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
	cin >> MenuChoice;
	do {
		switch (MenuChoice) 
		{
		case 1: {//开始游戏
			Menu_initial();
			int GameChoice;
			cin >> GameChoice;  
			do {
				switch (GameChoice) {
				//查询
				case 1: {  
					check();
					int RequireChoice;
					cin >> RequireChoice;
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
							default: {
								cout << "输入错误，请重新输入："; 
								break;
							}
						}
						if (RequireChoice == 6) break;
						if(RequireChoice<6&&RequireChoice>0)
						cout << "游戏继续，请选择操作：";
						cin >> RequireChoice;
					} while (1);
					Menu_initial();
					break;
				}
				case 2: {//出圈&购猪
					if (MonthCount + DayCount / 30 < 3) {
						cout << "上次出圈到现在饲养时间不足三月，请别着急出圈噢" << endl;
						break;
					}
					OutPigs(Stys);
					break;
				}
				case 3: {//重新游戏
					for (int i = 0; i < 100; i++) 
						Stys[i].clearStys();
					StartNew(Stys);
					Menu_initial();
					break;
				}
				case 4: { //保存游戏
					savefile(Stys);
					saveInfo();
					int ex;
					cin >> ex;
					if (ex == 0) 	
						exit(0);
					break;
				}
				case 5: {//下一天
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
				case 6: { //下个月
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
					int choose;	cin >> choose;
					if (choose == 2) {
						int deadday = epd(Stys,i,j);
						cout << deadday << "天后养猪场的猪全部死亡" << endl;
					}
					else if (choose == 1) {
						isolate(Stys,i,j);
						cout << "该病猪已被隔离完成" << endl;
					}
					break;
				}
				default: {
					cout << "输入错误，请重新输入" << endl;
					break;
				}
			}
				if(GameChoice>0&&GameChoice<8)
				 cout << "游戏继续，请选择操作：";
				cin >> GameChoice;
			} while (1);
			break;
		}
		case 2:  exit(0); 
		default: {	cout << "输入错误，请重新输入：";	}
		}
	    cin >> MenuChoice;
	} while (1);
}