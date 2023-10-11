#ifndef __POLTREE_H__
#define __POLTREE_H__

#include<iostream>
#include <stdlib.h>
#include "C:\ma\include\building.h"
// #include "C:\ma\include\method.h"
// #include "C:\ma\include\tree.h"
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>
#include<algorithm>


class poltree
{
private:
    int polidx;
    building b;
    bool head=false;
    
public:
    poltree(int polidx,building b);
    poltree(int polidx,building b,bool head);
    int getPolidx();
    bool getHead();
    building getProject();
    void setPolidx(int polidx);
    void setP(building p);
    void setHead(bool Head);
    ~poltree();
    poltree();
};





#endif // __POLTREE_H__