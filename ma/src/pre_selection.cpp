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
#include <math.h>

using namespace std;
// extern vector<building> P;
vector<building> dn_p;
vector<building> pk_p;


bool cmp2(building x,building y)
{
    return x.getRange() > y.getRange();
}

bool cmp1(building x,building y)
{
    return x.getLocation() < y.getLocation();
}

bool check(vector<building> pw,int k,building p,double w){
    int cnt=0;
    for(building b:pw){
        cnt=0;
        if(b.getLocation()>p.getLocation()-w){
            for(building b1:pw){
                if(b1.getLocation()>b.getLocation()&&b1.getLocation()<=b.getLocation()+w){//在右窗口范围内
                    cnt++;
                }
            }
        }
        if(cnt>k){
            return false;
        }
        if(b.getLocation()>p.getLocation())break;
    }
    return true;
}

vector<building> preSelection(int k,double w,vector<building>& P){
    vector<building>().swap(dn_p);
    // P=readCsvByCsvReader("C:\\Users\\16123\\ma\\src\\resource\\test.csv");
    vector<building> pk;
    vector<building> pw;
    sort(P.begin(),P.end(),cmp2);
    pk.push_back(P.at(0));
    dn_p.push_back(P.at(0));
    double max=0;
    int i=0,idx=0,ord=0;
    sort(P.begin(),P.end(),cmp1);
    while (true)
    {
        i=0;
        for(building b:P){
            if(b.getChoose()==false&&max<getProfit(b,dn_p)){
                max = getProfit(b,dn_p);
                idx=i;
            }
            i++;
        }
        // cout<<"p.getChoose()---"<<P.at(idx).getChoose()<<"----p.getID()---"<<P.at(idx).getId()<<"----p.getprofit()---"<<getProfit(P.at(idx),dn_p)<<endl;
        /* 退出条件 */
        if(max==0||pk.size()==P.size()){
            
            break;
        }
        
        double wps = P.at(idx).getLocation()-w;
        double wpe = P.at(idx).getLocation()+w;

        /* 将最大值对象窗口范围内的建筑物加入候选pw */
        for (building b:P)
        {
            if((b.getLocation()>wps && b.getLocation()<=wpe)&&(b.getChoose()==true)){
                pw.push_back(b);
            }
            if(b.getLocation()>wpe){
                break;
            }
            
        }
        /* check */
        bool ck = check(pw,k,P.at(idx),w);
        if(ck==true){
            update(P.at(idx),dn_p);
            P.at(idx).setOrder(++ord);
            pk.push_back(P.at(idx));
            // cout<<"pk.getChoose()---"<<P.at(idx).getChoose()<<"----pk.getID()---"<<P.at(idx).getId()<<"----pk.getprofit()---"<<P.at(idx).getOrd()<<endl;
            P.at(idx).setChoose(true);
        }
        else{
            P.at(idx).setChoose(true);
        }
        max=0;
    }
    return pk;
}


/* 借助预计算|指定窗口内选择k个对象 */

bool cmp6(building x,building y)
{
    return x.getOrd() < y.getOrd();
}

vector<building> pre(double ws,double we,int k,double w,vector<building>& P){//现在窗口的起点和终点ws、we,w是预选择窗口长度
    // P = preSelection(k,w);//k,w
    int cnt=0;
    vector<building> r,res;
    sort(P.begin(),P.end(),cmp1);
    for(building b:P){
        if(b.getLocation()<=we&&b.getLocation()>ws){
            r.push_back(b);
        }
        if(b.getLocation()>we){
            break;
        }
        cnt++;
    }
    sort(r.begin(),r.end(),cmp6);
    for(building b:r){
        res.push_back(b);
        // cout<<b.getId()<<endl;
        if(--k==0)
            break;
        cnt++;
    }
    cout << "cnt:  " << cnt+(r.size()*log(r.size())) <<endl; 
    return res;
}




/* 计算全局认知收益值 */
double calplp(){
    double res=0.0;
    for(building b:dn_p){
        res+=b.getRange();
    }
    return res;
}

vector<building> dn_pre;
/* 计算局部pre函数认知收益值 */
double calpre(vector<building> res){
    vector<building>().swap(dn_pre);
    double pl = 0.0;
    for(int i=0;i<res.size();i++){
        update(res[i],dn_pre);
    }
    for (building pp:dn_pre)
    {
        pl+=pp.getRange();
    }
    return pl;
}


