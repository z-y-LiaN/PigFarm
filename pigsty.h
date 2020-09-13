#pragma once
#include<iostream>
using namespace std;
struct pig {
	int species;
	int breedDay;
	int breedMon;
	double weight;
	int number;
	int isDead;
	pig* next;
};
class PigSty {
private:
	int thisSty_tot;
	pig* head;
	int isBlack;
	int state;
public:
	PigSty();
	void print();            
	void addOnePig(pig* p); 
	void insert(int species);
	double getPrice();       
	int getSpecies(int i);    
	int getBreedMon(int i);   
	int getBreedDay(int i);
	double getWeight(int i);
	void clearStys();
	void setisBlackSty(int i);
	int get_BlackNum();
	int get_SflowerNum();
	int get_BflowerNum();
	int getTot();
	int isAllBlack();
	void save(ofstream& savefile);               
	pig* getHead();
	void next(int nexttime);
	bool havePig(int number);
	int getState(); 
	void setisDead(int num);
	void Pro50();
	void Pro15();
	void setState();
	void deleteOne(int j);
};

