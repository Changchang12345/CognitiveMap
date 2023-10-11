#include<iostream>
#include <stdlib.h>
// #include "C:\ma\include\building.h"
// #include "C:\ma\include\method.h"
#include "C:\ma\include\poltree.h"
#include<vector>
#include<fstream>
#include <string>
#include <iomanip>
#include <sstream>
#include<algorithm>
#include<iterator>
#include <math.h>

using namespace std;




poltree::poltree(int polidx,building p)
{
    this->polidx = polidx;
    this->b = p;
}
poltree::poltree(int polidx,building p,bool head)
{
    this->polidx = polidx;
    this->b = p;
    this->head = head;
}
poltree::poltree()
{
}
int poltree::getPolidx(){
    return this->polidx;
}
building poltree::getProject(){
    return this->b;       
}
bool poltree::getHead(){
    return this->head;
}
void poltree::setPolidx(int polidx){
    this->polidx = polidx;
}
void poltree::setP(building p){
    this->b = p;
}
void poltree::setHead(bool Head){
    this->head = Head;
}
poltree::~poltree()
{
}
