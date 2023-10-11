#include<iostream>
#include <stdlib.h>
#include "C:\ma\include\building.h"
#include "C:\ma\include\method.h"
#include<vector>
#include<fstream>
#include <string>
#include <iomanip>
#include <sstream>
#include<algorithm>

using namespace std;

// vector<building> dn_p;
// vector<building> pk_p;

bool cmp2(building x,building y);

bool cmp1(building x,building y);

vector<building> preSelection(int k,double w,vector<building>& P);

bool check(vector<building> pw,int k,building p,double w);

vector<building> pre(double ws,double we,int k,double w,vector<building>& P);

double calplp();

double calpre(vector<building> res);