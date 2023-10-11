#ifndef __METHOD_SLIDEW_H__
#define __METHOD_SLIDEW_H__

#include<iostream>
#include <stdlib.h>
#include "C:\ma\include\building.h"
#include "C:\ma\include\method.h"
#include<vector>


using namespace std;


vector<building> dn_s;



building select(vector<building> pa,vector<building>& pt_s);

bool cmp(building x,building y);

vector<building> greedyk(int k,vector<building>& pt_s,vector<building>& P);

vector<building> slidingW(int k,double w,double s,vector<building>& P);

double calpl();

vector<building> preSliding(int k,double w,double s,vector<building>& P);

vector<building> rankSelect(int k,double w,double s,vector<building>& P);

vector<building> locationSelect(int k,double w,double s,vector<building>& P);

#endif // __METHOD_SLIDEW_H__