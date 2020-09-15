#include"mfunc.h"
#include"printFunc.h"
#include<stdlib.h>
#include<time.h>
#include<iostream>
#include<fstream>
#include<iomanip>
//#include<string.h>
using namespace std;
void RequireSell() {
	ifstream read;
	read.open("Eachsale.txt");
	if (!read) {
		cout << "打开文件失败";
		exit(0);
	}
	char flag;
	read >> flag;
	if (flag == '#') {
		cout << "暂无出圈记录" << endl;
		return;
	}
	int times, outpigs, Bpig, SFpig, BFpig;
	double sellprice, money;
	while (read>>times) {
		if (read.eof()) break;
		read >> outpigs >> sellprice >> Bpig >> SFpig >> BFpig>>money;
		cout << "第" << times / 4 + 1 << "年";
		cout << "第" << (times % 4 + 1) << "次出圈：\n";
		cout << "     出圈猪数：" << outpigs << "     获得收益：￥" << sellprice << endl;
		cout << "     购进猪崽情况：" << endl;
		cout << "                  黑猪数:     " << setw(5)<<Bpig << endl;
		cout << "                  小花猪数：  " <<setw(5)<<SFpig << endl;
		cout << "                  大白花猪数：" << setw(5)<<BFpig<< endl;
		cout<< "      余额：￥" << money << endl;
		cout << "-----------------------------------------------------------\n";
	}
	read.close();
}
 
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
	testin.open("Eachsale.txt");
	char flag;
	testin >> flag;
	if (flag == '#') {
		testin.close();
		ofstream testout;
		testout.open("Eachsale.txt");
		testout << '$';
		testout.close();
	}
	else testin.close();
	ofstream save("Eachsale.txt", ios::app);
	save << sell_Times_Count << endl;
	save << outpignum << "   " << sellprice << "    " << bpig << "   " << lpig << "   " << wpig <<"  "<<money << endl;
	save.close();
}
//
bool is_all_BstyFull(PigSty* stys) {
	int bj = 0; int cnt = 0;
	for (int i = 0; i < 100; i++) {
		if (stys[i].isAllBlack() == 1) bj++;
	}
	for (int i = 0; i < 100; i++) {
		if (stys[i].isAllBlack() && stys[i].get_BlackNum()== 10)
			cnt++;
	}
	if (cnt == bj) return 1;
	else return 0;
}

void StartfromLast(PigSty*Stys) {
	ifstream getinfo;
	getinfo.open("Info.txt");   
	getinfo >> allPigsNum >> TotMoney >> MonthCount >> DayCount >> sell_Times_Count;
	getinfo.close();
	ifstream read; 
	read.open("isFirstGame.txt");
	if (!read) {
		cout << "读取数据失败！";
		exit(0);
	}
	int t, cntnum;
	pig* p;
	read >> t;
	for (int i = 0; i < 100; i++) {
		read >> cntnum;  
		for (int j = 0; j < cntnum; j++) {
			p = new pig;
			p->number = j;     
			read >> p->species;   
			if (p->species == '$') {     
				delete p;
				break;
			}
			else read >> p->weight >> p->breedMon >> p->breedDay; 
			Stys[i].addOnePig(p);  
		}
	}
	read.close();
}
//初始化猪圈 
void StartNew(PigSty* Stys) {
	allPigsNum = 1000;
	TotMoney = 500000;
	MonthCount = 0;
	DayCount = 0;
	sell_Times_Count = 0;
	ofstream f;
	f.open("isFirstGame.txt");//文件 
	f << 0; 
	f.close(); 
	f.open("Eachsale.txt"); //打开 
	f << '#'; 
	f.close(); 
	pig* p;
	int count = 1000;       //假设初始化有1000头猪 
	while (count--) {
		p = new pig;
		p->species = rand() % 3 + 1;  //随机初始化
		p->weight = double(rand() % 31 + 20);  
		p->breedMon = 0;
		p->breedDay = 0;
		p->isDead = 0;
		int i = rand() % 100;
		if (p->species == 1 && (Stys[i].isAllBlack() == 1 || Stys[i].getHead() == NULL) && Stys[i].getTot() < 10) {
			p->number = Stys[i].getTot();
			Stys[i].addOnePig(p);  
			Stys[i].setisBlackSty(1);  
			continue;
		}
		else if (p->species != 1 && Stys[i].isAllBlack() == 0 && Stys[i].getTot() < 10) {
			p->number = Stys[i].getTot();
			Stys[i].addOnePig(p);   
			continue;
		}
		else count++;
		delete p;
	}
	for (int i = 0; i < 100; i++)
		Stys[i].setState();
}
void savefile(PigSty*pigStys) {
	ofstream savefile;
	savefile.open("isFirstGame.txt");
	if (!savefile) {
		cout << "打开文件失败！";
		exit(0);
	}
	savefile << 1 << endl;
	for (int i = 0; i < 100; i++) {
		pigStys[i].save(savefile);
	}
	savefile.close();
} 
int getAllPigs(PigSty* pigStys) {
	int allPigs = 0;
	for (int i = 0; i < 100; i++) {
		allPigs += pigStys[i].getTot();
	}
	return allPigs;
}
void statistic(PigSty* pigStys)
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
void RequireOneSty(PigSty*Stys)
{
	int styNum;
	cout << "请输入想要查询的猪圈编号：";
	while (1) {
		int i = rightNum();
		if (i < 1 || i>100) {
			cout << "输入错误，请重新输入猪圈编号" << endl;
			continue;
		}
		else {
			styNum = i; break;
		}
	}
	cout << "------------------------------------------------------------------" << endl;
	cout << "该猪圈的猪总数     " << "黑猪数量           " << "小花猪数量         " << "大白花猪数量       " << endl;
	cout << ' ' << left << setw(20) << Stys[styNum].getTot() << left << setw(20) << Stys[styNum].get_BlackNum() << left << setw(20) << Stys[styNum].get_SflowerNum() << left << setw(20) << Stys[styNum].get_BflowerNum() << "\n\n";
	cout << "------------------------------------------------------------------" << endl;
}
void RequireOnePig(PigSty*Stys)
{
	int styNum, pigNum;
	cout << "请输入猪圈号：";
	while (1) {
		int i = rightNum();
		if (i < 1 || i>100) {
			cout << "输入错误，请重新输入正确猪圈编号" << endl;
			continue;
		}
		else {
			styNum = i; 
			if (Stys[styNum].getTot() != 0) break;
			else {
				cout << "抱歉，该猪圈为空猪圈，请重新输入："; continue;
			}
		}
	}
	cout << "此猪圈共有" << Stys[styNum].getTot() << "头猪 , 请输入查询编号 ： ";
	while (1) {
		int i = rightNum();
		if (i < 1 || i>10) {
			cout << "输入错误，请重新输入正确猪编号" << endl;
			continue;
		}
		else {
			pigNum = i;
			if (Stys[styNum].getHead() != NULL) break;
			else {
				cout << "抱歉，该猪圈为空猪圈，请重新输入："; continue;
			}
		}
	}
	cout <<"查询结果："<< endl;
	cout << "猪的品种            |            体重/kg               |         饲养时间" << endl;
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
void RequireAllPigs(PigSty*Stys) {
	for (int i = 0; i < 100; i++) {
		cout << "=============================================================" << endl;
		cout << i << "号圈:" << endl;
		Stys[i].print();
		if (i == 99) cout << "======================查询结束===============================" << endl;
	}
}
void OutPigs(PigSty* Stys) {
	double sellprice = 0;
	for (int i = 0; i < 100; i++) {
		sellprice += Stys[i].getPrice();
	}
	int temp = getAllPigs(Stys), outpignum = allPigsNum - temp;
	allPigsNum = temp;
	cout << endl;
	cout << "本次出圈数： " << outpignum << "头    总价:" << sellprice << "元\n";
	TotMoney += sellprice;
	int blackpig = 0, empSty = 0, FlowerPigCnt = 0;

	for (int i = 0; i < 100; i++) {
		if (Stys[i].getHead() == NULL) { empSty++; continue; }
		else {
			if (Stys[i].get_BlackNum())   blackpig += 10 - Stys[i].get_BlackNum();
			else FlowerPigCnt += 10 - Stys[i].getTot();
		}	
	}
	int rem = empSty * 10 + FlowerPigCnt + blackpig;
	cout << "出圈后，猪圈空位信息:\n";
	cout << "              ---------------------------\n";
	cout << "              | 猪圈总空位：     "<<setw(5) << rem <<"  |"<< endl;
	cout << "              | 未满黑猪圈余位： "<<setw(5)<< blackpig << "  |" << endl;
	cout << "              | 未满花猪圈余位:  " << setw(5) << FlowerPigCnt << "  |" << endl;
	cout << "              | 空猪圈总个数：   " <<setw(5)<< empSty << "  |" << endl;
	cout << "              ---------------------------\n";
	int Bpig, SFpig, BFpig;
	printBuyPrice();
	cout << "请按品种输入本次购入的猪崽数量\n";
	cout << "黑猪数量：";  cin.get();
	while (1) {
		while (1) {
			int i = rightNum();
			if (i < 1 || i>1000) {
				cout << "输入错误，请重新输入" << endl;
				continue;
			}
			else {
				Bpig = i; break;
			}
		}
		cout << "\n小花猪数量：";
		while (1) {
			int i = rightNum();
			if (i < 1 || i>1000) {
				cout << "输入错误，请重新输入" << endl;
				continue;
			}
			else {
				SFpig = i; break;
			}
		}
		cout << "\n大花白猪数量：";
		while (1) {
			int i = rightNum();
			if (i < 1 || i>1000) {
				cout << "输入错误，请重新输入" << endl;
				continue;
			}
			else {
				BFpig = i; break;
			}
		}
		int tmp = empSty - (Bpig - blackpig) / 10;
		if ((Bpig - blackpig) % 10 != 0)    tmp--;
		if ((Bpig > blackpig + empSty * 10) || (SFpig > empSty * 10 + FlowerPigCnt) || (BFpig > empSty * 10 + FlowerPigCnt) || (SFpig + BFpig > empSty * 10 + FlowerPigCnt) || ((BFpig + SFpig + Bpig) > rem))
		{
			cout << "超过猪场或指定类型猪圈的容纳量，请重新输入：\n"; continue;
		}
		else if (TotMoney < (1500 * Bpig + 1300 * SFpig + 1000 * BFpig)) {
			cout << "余额不足，请重新输入\n"; continue;
		}

		else if ((tmp * 10 + FlowerPigCnt < SFpig + BFpig) || Bpig > blackpig + 10 * empSty) {
			cout << "该组合无法合理分配猪圈，请重新输入：\n";
			continue;
		}
		else if (TotMoney >= 5000000) {
			cout << "！！！！！！！！恭喜你通过养猪赚够五百万啦！！！！！！！" << endl;
			exit(0);
		}
		else break;
	}
	TotMoney -= (1500 * Bpig + 1300 * SFpig + 1000 * BFpig);
	allPigsNum += Bpig + SFpig + BFpig;
	buyPigs(Bpig, SFpig, BFpig, Stys);
	cout << "购买成功，现在养猪场总猪数： " << allPigsNum << endl;
	cout << "请按任意键继续" << endl;
	save_SoldInfo(outpignum, sellprice, Bpig, SFpig, BFpig, TotMoney);
	sell_Times_Count++;
	while (DayCount >= 30) {
		DayCount -= 30;
		MonthCount++;
	}
	MonthCount -= 3;
	cin.get();
	cin.get();
	Menu_initial();
}
void buyPigs(int Bpig, int SFpig, int BFpig, PigSty*pigStys) {
	while (Bpig--) {
		for (int i = 0; i < 100; i++) {
			if (pigStys[i].isAllBlack() == 1 && pigStys[i].getTot() < 10) {
				pigStys[i].insert(1);
				break;
			}
			if ((is_all_BstyFull(pigStys)) && pigStys[i].getHead() == NULL) {
				pigStys[i].insert(1);
				pigStys[i].setisBlackSty(1);
				break;
			}
		}
	}
	int fl = 0; int allb = 0;
	for (int i = 0; i < 100; i++)
	{
		if (pigStys[i].getHead() == 0) fl++;
		else {
			if (pigStys[i].isAllBlack() == 0)  fl++;
			else allb += pigStys[i].get_BlackNum();
		}
	}
	int bjuan = 0;
	for (int i = 0; i < 100; i++)
		if (pigStys[i].isAllBlack() == 1)  bjuan++;
	/*cout << "分配完的黑猪总数：" << allb << endl;
	cout << "除黑猪以外的个数：" << allPigsNum - allb << endl;
	cout << "花猪最多可用圈：" << fl << " " << endl;
	cout << "黑猪现在占有的圈" << bjuan << " " << endl;*/
	int average = (allPigsNum - allb) / fl+1 ;
	//cout << "花猪圈不超过10之前平均 " << average << endl;
	if (average > 10) average = 10;
	
	while (1) {
		for (int i = 0; i < 100; i++) {
			if (pigStys[i].isAllBlack() == 0) {
				if (SFpig > 0 && (pigStys[i].getTot() < average || pigStys[i].getHead() == NULL)) {
					pigStys[i].insert(2);
					SFpig--;
				//	cout << "小花" << SFpig << endl;
				}
				if (BFpig > 0 && (pigStys[i].getTot() < average || pigStys[i].getHead() == NULL)) {
					pigStys[i].insert(3);
					BFpig--;
				//	cout << "大花：" << BFpig << endl;
				}

			}
		}
		if (SFpig == 0 && BFpig == 0)	break;
	}
}

int rightNum(){
	string str;
	/*getline(cin, str);*/
	cin >> str;
	for (int i = 0; i < str.size(); i++) {
		if (str[i] < '0' || str[i]>'9') return -1;
	}
	int out = 0;
	for (int i = 0; i < str.size(); i++) {
		int tmp = str[i] - '0';
		out = out * 10 + tmp;
	}
	if (out < 0) return -1;
	else 
	   return out;
}
