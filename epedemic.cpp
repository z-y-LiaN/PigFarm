#include"mfunc.h"
int PigSty::getState() {
	return state;
}
//把某只猪设置为死猪 
void PigSty::setisDead(int num){
	pig* p = head;
	for (int i = 0; i < num && p; i++)
		p = p->next;
	p->isDead = 1;
}
//50%的概率患病
void PigSty::Pro50(){
	pig* p = head;
	while (p){
		int prob = rand() % 99 + 1;
		if (prob <= 50)
			p->isDead = 1;
		p = p->next;
	}
}
//15%的概率患病 
void PigSty::Pro15(){
	pig* p = head;
	while (p){
		int prob = rand() % 99 + 1;
		if (prob <= 15)
			p->isDead = 1;
		p = p->next;
	}
}
void PigSty::setState(){
	pig* p = head;
	int i;
	int flag = 0;
	for (i = 0; i <thisSty_tot && p; i++) {
		if (p->isDead == 1) {
			flag++;
		}
		p = p->next;
	}
	if (flag == thisSty_tot) state = 1;
	else if (flag == 0) state = 0;
	else if (flag > 0 && flag < thisSty_tot) state = 2;
}
void PigSty::deleteOne(int j) {
	pig* p = head;
	if (j == 0) {
		head = p->next;
		delete p;
		thisSty_tot--;
	}
	else if (j == thisSty_tot - 1) {
		for (int i = 0; i < j - 1; i++)
			p = p->next;
		pig* tmp = p->next;
		p->next = NULL;
		delete tmp;
		thisSty_tot--;
	}
	else {
		pig* pre = p;
		for (int i = 0; i < j; i++) {
			pre = p;
			p = p->next;
		}
		pre->next = p->next;
		delete p;
		thisSty_tot--;
	}
}
int NotallDead(PigSty* Stys) {
	for (int i = 0; i < 100; i++) {
		if (Stys[i].getHead() == NULL) continue;
		if (Stys[i].getState() != 1)
			return 1;
	}
	return 0;
}

void isolate(PigSty* Stys,int i,int j) {
	Stys[i].deleteOne(j);
}

int epd(PigSty* Stys,int i,int j){
	Stys[i].setisDead(j);
	Stys[i].setState();
	int allDeadDay = 1;
	int pd = NotallDead(Stys);
	while (pd != 0) {
		for (int k = 0; k < 100; k++) {
			if (Stys[k].getState() == 0)	continue;
			else {
				if (k > 0 && k < 99) {
					Stys[k - 1].Pro15();
					Stys[k + 1].Pro15();
				}
				else if (k == 0) {
					Stys[k + 1].Pro15();
				}
				else if (k == 99) {
					Stys[k - 1].Pro15();
				}
				if (Stys[k].getState() == 2)
					Stys[k].Pro50();
			}
		}
		for (int m = 0; m < 100; m++) {
			if (Stys[m].getHead() != NULL)
				Stys[m].setState();
		}
		allDeadDay++;
		pd = NotallDead(Stys);
	}
	return allDeadDay;
}
