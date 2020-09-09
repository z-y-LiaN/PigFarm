#include"pigsty.h"
#include"mfunc.h"
#include<iostream>
#include<fstream>
#include<iomanip>
using namespace std;
double money;
int month;
int day;
int sellcount ;
int allpig;
int main()
{
	PigFarm oneSty[100]; //创建一个类数组，每个数组元素都是一个猪圈 
	Menu();
	int flag;
	ifstream infile;   //读文件 
	infile.open("123.txt"); //123保存的是初始数据 
	infile >> flag; //把第一行的第一个数据放到flag里面 
	//如果是第一次打开程序的话，就要初始化 
	if (flag == 0) {  //如果flag为0；就是第一次打开文件 
		Menu_pigsty(oneSty);
	}
	else //如果不是的话，就要读取文件 
	{
		Menu_pigsty_byfile(oneSty);
	}
	infile.close();
	allpig = getallpig(oneSty);
	//	cout<<"test tot:"<<allpig<<endl; 
	int game;
	cout << "请输入你要的操作：" << endl;
	cin >> game;
	do {
		switch (game) {
		case 1: {//开始游戏
			Menu_initial();//初始化 
			int option;
			cin >> option;  
			do {
				switch (option) {
				case 1: {  //查询
					check();
					int choice;
					cin >> choice;
					do {
						switch (choice) {
						case 1: {
							int num;
							cout << "请输入想要查询的猪圈编号：";
							cin >> num;
							while (1)
							{
								if (num >= 0 && num < 100) break;
								else
								{
									cout << "输入有误，请重新输入";
									cin >> num;
								}
							}
							cout << "-----------------------------------------------------------------" << endl;
							cout << "该猪圈的猪总数     " << "黑猪数量           " << "小花猪数量         " << "大白花猪数量       " << endl;
							cout <<' '<<left<<setw(20)<<oneSty[num].getcount() << left << setw(20) << oneSty[num].getspecies1() << left << setw(20) << oneSty[num].getspecies2() << left << setw(20) << oneSty[num].getspecies3() << "\n\n";
							break;
						}
						case 2: {//查询
							int num1, num2;
							cout << "请输入猪圈号：";
							cin >> num1;
							while (1) {
								if (num1 >= 0 && num1 < 100)
								{
									if (oneSty[num1].getcount() != 0) break;
									else
									{
										cout << "该猪圈为空猪圈，请重新输入";
										cin >> num1;
									}
								}
								else { cout << "输入错误，请重新输入"; cin >> num1;}
							}
							cout << "此猪圈共有" << oneSty[num1].getcount() << "头猪,请输入不超过 "<< oneSty[num1].getcount()-1 <<" 的编号：";
							cin >> num2;
							while (1) {
								
								if (num2 >= 0 && num2 < oneSty[num1].getcount() )break;
								else
								{
									cout << "输入错误，请重新输入：";
									cin>>num2;
								}
				/*				if (!pjuan[num1].search(num2)) {
									cout << "输入错误，请按提示重新输入：";
									cin >> num2;
								}
								else break;*/
							}
							cout << "猪的品种                        体重/kg                        饲养时间" << endl;
							if (oneSty[num1].getspecies(num2) == 1)cout << " 黑猪    "<<"                         ";
							if (oneSty[num1].getspecies(num2) == 2)cout << " 小花猪  "<<"                         ";
							if (oneSty[num1].getspecies(num2) == 3)cout << "大白花猪 "<<"                         ";
							cout << oneSty[num1].getweight(num2)<<"                              ";
							int month = oneSty[num1].getgrowmonth(num2), day = oneSty[num1].getgrowday(num2);
							while (day >= 30) {
								day -= 30;
								month++;
							}
							if (month > 0)cout << month << "月"; cout << day << "天\n\n";
							break;
						}
						case 3: { //养猪场的情况
							statistic(oneSty);
							break;
						}
						case 4: { //近五年销售和购入记录
							read456();
							break;
						}
						case 5: {//当前猪场每个猪圈每头猪的信息
							for (int i = 0; i < 100; i++) {
								cout << "===============================================" << endl;
								cout << i << "号圈:" << endl;
								oneSty[i].print();
								if (i == 99) cout << "================over========================" << endl;
							}
							break;
						}
						default:break;
						}
						if (choice == 6) break;
						cout << "游戏继续，请选择操作：";
						cin >> choice;
					} while (1);
					Menu_initial();
					break;
				}
				case 2: {
					if (month + day / 30 < 3) {
						cout << "距离上次出圈后的饲养时间不足3月，请再饲养一段时间！" << endl;
						break;
					}
			//
					double sellprice = 0;
					for (int i = 0; i < 100; i++) {
						sellprice += oneSty[i].getprice();
					}
					int temp = getallpig(oneSty), outpignum = allpig - temp;
					allpig = temp;
					cout << "此次圈出猪" << outpignum << "头，总体售价为:" << sellprice << "元\n";
					money += sellprice;
			//
					int blackpig = 0, blankpigjuan = 0, count = 0;
					for (int i = 0; i < 100; i++) {
						if (oneSty[i].getcount() == 0) { blankpigjuan++; continue; }
						if (oneSty[i].getspecies1())blackpig += 10 - oneSty[i].getspecies1();
						else count += 10 - oneSty[i].getcount();
					}
					cout << "未满的黑猪圈可购入" << blackpig << "头黑猪，剩余空圈数：" << blankpigjuan << endl;
					int bpig, lpig, wpig;
					cout << "提示：每头黑猪2000元，每头小花猪1500元，每头大白花猪3000元，当前余额：" << money << endl;
					cout << "如果您有足够多的金币，建议购买" << blackpig << "头黑猪," << blankpigjuan * 10 + count << "头大白花猪\n";
					cout << "请依次输入本次购入的黑猪，小花猪，大花白猪数：";
					cin >> bpig >> lpig >> wpig;
					while (1) {
						if (bpig > blackpig + blankpigjuan * 10 || lpig > blankpigjuan * 10 + count || wpig > blankpigjuan * 10 + count || lpig + wpig > blankpigjuan * 10 + count)cout << "猪数超过猪场容纳量，请重新输入：\n";
						else if (money < 2000 * bpig + 1500 * lpig + 3000 * wpig)cout << "余额不足，请重新输入\n";
						else if (((blankpigjuan - (bpig - blackpig) / 10) * 10 <= lpig + wpig) && bpig > blackpig)cout << "购猪组合不合理，黑猪与其他猪不能混养，请重新输入：\n";
						else if (allpig + bpig + lpig + wpig >= 1000) {
							cout << "养满猪场，win" << endl;
							exit(0);
						}
						else break;
						cin >> bpig >> lpig >> wpig;
					}
					money -= 2000 * bpig + 1500 * lpig + 3000 * wpig;
					allpig += bpig + lpig + wpig;
					cout << "购入后的猪总数 "<<allpig << endl;
					buypig(bpig, lpig, wpig, oneSty);
					save_456(outpignum, sellprice, bpig, lpig, wpig);
//
				//	cout << "sellcount ==" << sellcount;
					sellcount++;
					while (day >= 30) {
						day -= 30;
						month++;
					}
					month -= 3;
					cin.get();
					cin.get();
					Menu_initial();
					break;
				}
				case 3: {//重新游戏
					for (int i = 0; i < 100; i++) oneSty[i].clearpigjuan();
					Menu_pigsty(oneSty);
					Menu_initial();
					break;
				}
				case 4: { //保存游戏
					savefile(oneSty);
					save_789();
					int ex;
					cin >> ex;
					if (ex == 0) 	
						exit(0);
					break;
				}
				case 5: {//下一天
					for (int i = 0; i < 100; i++) {
						oneSty[i].next(1);
					}
					day++;
					Menu_initial();
					break;
				}
				case 6: { //下个月
					for (int i = 0; i < 100; i++) {
						oneSty[i].next(30);
					}
					month++;
					Menu_initial();
					break;
				}
				default:break;
				}
				cout << "游戏继续，请选择操作：";
				cin >> option;
			} while (1);
			break;
		}
		case 2: {
			cout << "输赢条件：\n";
			cout << "养满猪场胜利\n";
			break;
		}
		}
		if (game == 3)exit(0);
		else cin >> game;
	} while (1);

}