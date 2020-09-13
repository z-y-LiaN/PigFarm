#include "printFunc.h"
void Prompt() {
	cout << "\n\n\n\n\n\n\n";
	cout << "           ********************************************************\n";
	cout << '\n';
	cout << "                            养猪模拟游戏：                        \n";
	cout << '\n';
	cout << "                       请选择：\n";
	cout << '\n';
	cout << "                                1.开始养猪成为百万富翁吧\n";
	cout << '\n';
	cout << "                                2.养猪好无聊，不玩啦\n";
	cout << '\n';
	cout << "          ********************************************************\n";
}
//查询操作的选择 
void check() {
	system("cls");
	cout << "\n\n\n\n\n\n\n";
	cout << "            ======================================================\n";
	cout << "                                         查询                          \n";
	cout << '\n';
	cout << "                       请选择查询内容：\n";
	cout << '\n';
	cout << "                            1——当前某一猪圈猪的数量和种类\n\n";
	cout << "                            2——当前某一猪圈某号猪的信息\n\n";
	cout << "                            3——当前猪场每种猪的数量、体重、饲养时间分布\n\n";
	cout << "                            4——近5年猪场的销售和购入记录\n\n";
	cout << "                            5——当前猪场的猪的所有信息\n\n";
	cout << "                            6——返回上一级\n\n";
	cout << '\n';
	cout << "            ======================================================\n";
}
//初始化 
void Menu_initial() {
	system("cls");
	cout << "\n\n\n\n\n\n\n";
	cout << "            ================================================================" << endl;
	cout << "                                          我的猪场                        \n";
	cout << "            ---------------------------------------------------------------" << endl;
	cout << endl;
	cout << "              当前财富：" << TotMoney << "    总猪数：" << allPigsNum << "   上一次出圈后至此的饲养时间:"; if (MonthCount > 0)cout << MonthCount << "月"; if (DayCount >= 0)cout << DayCount << "天";
	cout << endl;
	cout << "            --------------------------------------------------------------" << endl;
	cout << '\n';
	cout << "                       请选择操作：\n";
	cout << '\n';
	cout << "                                 1 —— 查询猪场各项信息\n\n";
	cout << "                                 2 —— 出圈并购猪\n\n";
	cout << "                                 3 —— 重新开始\n\n";
	cout << "                                 4 —— 保存游戏\n\n";
	cout << "                                 5 —— 一天后\n\n";
	cout << "                                 6 —— 一月后\n\n";
	cout << "                                 7 —— 重新开始游戏并进行疫情模拟" << endl;
	cout << "            ================================================================" << endl;

}
void printBuyPrice() {
	cout << "进购猪崽价目表：" << endl;
	cout << "              ------------------------------" << endl;
	cout << "              | 黑猪崽       ￥1500/头     |" << endl;
	cout << "              | 小花猪崽     ￥1300/头     |" << endl;
	cout << "              | 大白花猪崽   ￥1000/头     |" << endl;
	cout << "              ------------------------------" << endl;
	cout << "当前余额：" << TotMoney << endl;
}