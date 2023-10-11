#ifndef __TREE_H__
#define __TREE_H__

#include<iostream>
#include <stdlib.h>

#include "C:\ma\include\building.h"
#include "C:\ma\include\method.h"
#include "C:\ma\include\poltree.h"
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>
#include<algorithm>


class tree
{
private:
    vector<vector<poltree>> pol_tree;
    vector<poltree> h;
public:
    tree(/* args */);
    void setPoltree(vector<vector<poltree>> pol_tree);
    void seth(vector<poltree> head);
    vector<vector<poltree>> getPoltree();
    vector<poltree> geth();
    void setch(bool bb,int n,int c);
    bool getch(int n,int c);
    ~tree();
};


    void createTree(int n,vector<building> p,double s);//建立索引

    vector<building> selectList(tree tree,int k,double ws,double we,double s,int psize);//选择层数

    vector<building> selectList_next(tree tree,int k,double ws,double we,double s,int psize);//选择下一层

    vector<building> selectList_pre(tree tree,int k,double ws,double we,double s,int psize);//选择上一层

    vector<building> merge(int k,vector<int> a,int c,double ws,double we,int psize);

    vector<building> precomIndex_sliding(int k,double s,double w,int psize);

    vector<building> selectList_i_2(tree tree,int k,double ws,double we,double s,int psize);

    vector<building> selectList_i_3(tree tree,int k,double ws,double we,double s,int psize);

    vector<building> selectList_next1(tree tree,int k,double ws,double we,double s,int psize);

    vector<building> selectList_next2(tree tree,int k,double ws,double we,double s,int psize);
    
    double calpol(vector<building> res);


#endif // __TREE_H__
