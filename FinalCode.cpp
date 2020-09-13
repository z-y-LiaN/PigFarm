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
	if (flag == 0)  
		StartNew(Stys); 
	else  
		StartfromLast(Stys); 
	infile.close();
	allPigsNum = getAllPigs(Stys);
	int MenuChoice;
	cout << "请输入你想要继续的操作：" << endl;
	cin >> MenuChoice;
	do {
		switch (MenuChoice) 
		{
		case 1: {//开始游戏
			Menu_initial();//初始化 
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
				//查询单个猪圈情况		
						case 1: {
							RequireOneSty(Stys);
							break;
						}
				//查询具体某只猪情况
						case 2: {
							RequireOnePig(Stys);
							break;
						}
			    //查询当前猪场每种猪的情况
						case 3: { 
							statistic(Stys);    
							break;
						}
		        //查询近五年销售和购入记录
			 			case 4: { 
							RequireSell(); 
							break;
						}
     		    //查询猪场每个猪圈所有猪的信息
						case 5: {
							RequireAllPigs(Stys);
							break;
						}
				//返回
						case 6: {
							break;
						}
				//输入错误
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
				case 2: {
					if (MonthCount + DayCount / 30 < 3) {
						cout << "上次出圈到现在饲养时间不足三月，请别着急出圈噢" << endl;
						break;
					}
					double sellprice = 0;
					for (int i = 0; i < 100; i++) {
						sellprice += Stys[i].getPrice();
					}
					int temp = getAllPigs(Stys), outpignum = allPigsNum - temp;
					allPigsNum = temp;
					cout << "-----------------------------------------------------" << endl;
					cout << "本次出圈数： " << outpignum << "头    总价:" << sellprice << "元\n";
					cout << "-----------------------------------------------------" << endl;
					TotMoney += sellprice;
					int blackpig = 0, empSty = 0, FlowerPigCnt = 0;
					for (int i = 0; i < 100; i++) {
						if (Stys[i].getTot() == 0) { empSty++; continue; }
						if (Stys[i].get_BlackNum())   blackpig += 10 - Stys[i].get_BlackNum();
						else FlowerPigCnt += 10 - Stys[i].getTot();
					}
					int bpig, lpig, wpig;
					printBuyPrice();
					cout << "请依次输入本次购入的黑猪，小花猪，大花白猪数：";
					cin >> bpig >> lpig >> wpig;
					//tmp填满未满的黑猪圈，在用了空猪圈后剩余的猪圈可装的花猪数量
					int tmp = (empSty - (bpig - blackpig) / 10)* 10;
					while (1) {
						if (bpig > blackpig + empSty * 10 || lpig > empSty * 10 + FlowerPigCnt || wpig > empSty * 10 + FlowerPigCnt || lpig + wpig > empSty * 10 + FlowerPigCnt)
							cout << "猪数超过猪场容纳量，请重新输入：\n";
						else if (TotMoney < (1500* bpig + 1300 * lpig + 1000 * wpig))
							cout << "余额不足，请重新输入\n";
						else if ((tmp < lpig + wpig) && bpig > blackpig)
							cout << "购猪组合不合理，黑猪与其他猪不能混养，请重新输入：\n";
						else if (TotMoney>= 10000000) {
							cout << "赚够一千万，win" << endl;
							exit(0);
						}
						else break;
						cin >> bpig >> lpig >> wpig;
					}
					TotMoney -=(1500* bpig + 1300* lpig + 1000* wpig);
					allPigsNum += bpig + lpig + wpig;
					
					buyPigs(bpig, lpig, wpig, Stys);
					cout << "购买成功，现在养猪场总猪数： " << allPigsNum << endl;
					save_SoldInfo(outpignum, sellprice, bpig, lpig, wpig,TotMoney);
					sell_Times_Count++;
					while (DayCount >= 30) {
						DayCount -= 30;
						MonthCount++;
					}
					MonthCount -= 3;
					cin.get();
					cin.get();
					Menu_initial();
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
				case 7: {
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
					cout << "第 " << i << " 个猪圈的编号为 " << j << " 的猪染病" << endl;
					cout << "是否采取隔离措施 1是 2否" << endl;
					int choose;
					cin >> choose;
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
		case 2: { exit(0); }
		default: {
			cout << "输入错误，请重新输入：";
		}
		}
	    cin >> MenuChoice;
	} while (1);
}