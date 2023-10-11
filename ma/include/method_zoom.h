#ifndef __METHOD_ZOOM_H__
#define __METHOD_ZOOM_H__


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





building select_zoom(vector<building> dn);

vector<building> zoom_in(int k,double wi_start,double wi_end,vector<building> p,vector<building>& Pzoom,double bi);//放大

vector<building> zoom_out(int k,double wi_start,double wi_end,double wi_1_start,double wi_1_end,vector<building> p,vector<building>& Pzoom,double bi);//缩小

double calplzi();

double calplzo();

#endif // __METHOD_ZOOM_H__