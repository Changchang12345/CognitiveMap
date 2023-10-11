#ifndef __METHOD_H__
#define __METHOD_H__

#include "C:\ma\include\building.h"
#include<vector>
#include <string>

using namespace std;



vector<building> readCsvByCsvReader(string);

double getProfit(building ,vector<building>);

void update(building,vector<building>& );

// double calpl(vector<building> dn_s);


#endif // __METHOD_H__