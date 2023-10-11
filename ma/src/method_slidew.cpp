#include<iostream>
#include <stdlib.h>
#include "C:\ma\include\building.h"
#include "C:\ma\include\method.h"
// #include "C:\ma\include\method_slidew.h"
#include<vector>
#include <string>
#include<algorithm>

using namespace std;

extern vector<building> dn_s;//无相交段
// extern vector<building> P;//所有候选集
// extern vector<building> pt_s;//每个窗口的动态对象集
int minloc,idx=0;

/* ------method_zoom计算在线算法中的滑动窗口操作-------- */

/* 算法2 ：在一系列建筑物中选择收益值最大的对象,P为所有候选，pa为不重复的 ，返回值只有一个对象*/
building select(vector<building> pa,vector<building>& pt_s){
    double max=1.0;
    int i=idx;
    int j=0,idj=0;
    int flag=0;
    for(building p : pt_s)
    {
        // cout<<"p.getChoose()---"<<p.getChoose()<<"----p.getID()---"<<p.getId()<<"----p.getprofit()---"<<getProfit(p,pa)<<endl;
        if(p.getChoose()!=true){
            double pr = getProfit(p,pa);
            if(max<pr){ 
                flag=1;  
                // cout<<"p.getChoose()---"<<p.getChoose()<<"----p.getID()---"<<p.getId()<<endl;
                max = pr;
                idx=i;
                idj=j;
            }
            
        }
        i++;j++;
    }
    if(flag==1){
        pt_s[idj].setChoose(true);
        // idx = idx;
        return pt_s[idj];
    }
    else{
        building b = building();
        b.setId(-2);
        // idx=-1;
        return b;
        
    } 
}


/* 重载sort函数 */
bool cmp(building x,building y)
{
    return x.getLocation() < y.getLocation();
}


/* 算法1 ：基本一个窗口选k个贪心算法 ,在P中从下标idx1开始 */
vector<building> greedyk(int k,vector<building>& pt_s,vector<building>& P){//idx是当前窗口起始对象坐标
    vector<building> pk;
    building b;
    int ii = idx+1;
    // cout <<"ii: "<< ii << endl;
    for(int i=0;i<k;i++){
        idx = ii;
        b = select(dn_s,pt_s);
        
        if(b.getId()!=-2){//有被选中的对象
            // cout<<idx<<endl;
            // cout<<"t->getId()"<<P[idx].getId()<<endl;
            // cout<< "t->getId()" << b.getId() <<endl;
            b.setChoose(true);
            pk.push_back(b);
            /* 获取下一窗口起点 */
            
            update(b,dn_s);
        }
        
    }
    int max=-4;
    for(building pp:pk){
        if(pp.getId()>max){
           max = pp.getId();
        }
    }
    if(max!=-4){
        idx = max;
    }
    
    return pk;
}


/* 算法3 ：基本滑动窗口算法 */
vector<building> slidingW(int k,double w,double s,vector<building>& P){
    vector<building>().swap(dn_s);
    vector<building> pk_s;
    vector<building> pt_s;
    vector<building> g;
    // P=readCsvByCsvReader("C:\\Users\\16123\\ma\\src\\resource\\test.csv");
    minloc=0.0;
    //sort(P.begin(),P.end(),cmp);//按照长度排序从大到小
    int t = 0,i=0;//窗口个数 遍历对象个数
    int odx = pk_s.size();//选完k个对象之前对象集个数

/* 先初始化k个,返回数据集中的第一个对象下标 */
    for(i=0;i<P.size();i++){
        if(w<P[i].getLocation()){
            break;
        }
        pt_s.push_back(P[i]);
        // cout << w <<endl;
        // cout<<"p.getChoose()---"<<P[i].getLocation()<<"----p.getID()---"<<P[i].getId()<<"----p.getprofit()---"<<endl;

    }
    // idx = pt_s.size()-1;//锁定当前窗口最后一个候选坐标位置（下一增量窗口候选坐标的起点）
    g = greedyk(k,pt_s,P);
    pk_s.insert(pk_s.end(),g.begin(),g.end());
    int ndx = pk_s.size();//选完k个对象之后对象集个数
    int wloc = w;
    
    minloc+=132.8899;//先写入第一个建筑物的坐标为最小坐标值
    sort(pk_s.begin(),pk_s.end(),cmp);//结果集按照坐标排序
/*     for(building ppp : pk){
        cout<<ppp.getLocation()<<endl;
    } */

/* 滑动窗口 */
    while(minloc+w<s){
        /* 获取增量窗口的对象集 */
        vector<building>().swap(pt_s);
        // cout<<"idx:"<<idx<<"-----odx:"<<odx<<"-------ndx:"<<ndx<<"-----start:"<<wloc<<"-----end:"<<minloc+w<<endl;
        for(i=i;i<P.size();i++){ 
            if((wloc<=P[i].getLocation()&&P[i].getLocation()<=w+minloc)&&P[i].getChoose()==false){
                pt_s.push_back(P[i]);
                
            }
            else{
                if(P[i].getLocation()>w+minloc){
                    break;
                }
            }
        }
        // cout<<"pt.size():"<<pt_s.size()<<endl;
        if(odx<ndx){
            odx++;
        }
        ndx = pk_s.size();
        g = greedyk(k-(ndx-odx),pt_s,P);
        pk_s.insert(pk_s.end(),g.begin(),g.end());
        
        //idx锁定当前窗口最后一个坐标位置
        //获取下一窗口起点
        if(k-(ndx-odx)+1>1){
            sort(pk_s.begin(),pk_s.end(),cmp);
        }
        t++;
        wloc=minloc+w;//上一窗口终点
        if(t<pk_s.size()){
            minloc = pk_s.at(t).getLocation();//当前窗口起点
        }
        else{
            ndx+=k;
            minloc = P[i].getLocation();
            wloc = P[i].getLocation(); 

        }
        
    }
    return pk_s;
}


vector<building> preSliding(int k,double w,double s,vector<building>& P){
    sort(P.begin(),P.end(),cmp);
    return slidingW(k,w,s,P);
}


/* 计算认知收益值 */
double calpl(){
    double res=0.0;
    for(building b:dn_s){
        // cout << b.getRange()<< endl;
        res+=b.getRange();
    }
    return res;
}


/* rankselect */
vector<building> rankSelect(int k,double w,double s,vector<building>& P){
    vector<building>().swap(dn_s);
    int i=0;
    vector<building> pt_r;
    vector<building> pk_r;
    vector<building> r;
    for(i=0;i<s/w;i++){
        for(building b:P){
            if(b.getLocation()>i*w&&b.getLocation()<=i*w+w){
                pt_r.push_back(b);
            }
        }
        r=greedyk(k,pt_r,P);
        pk_r.insert(pk_r.end(),r.begin(),r.end());
    }
    return pk_r;
}


/* loctionselect */
vector<building> locationSelect(int k,double w,double s,vector<building>& P){
    vector<building>().swap(dn_s);
    int i=0;
    vector<building> pt_l;
    vector<building> pk_l;
    building l;
    for(i=0;i<s/(w/k);i++){
        for(building b:P){
            if(b.getLocation()>i*(w/k)&&b.getLocation()<=i*(w/k)+w/k){
                pt_l.push_back(b);
            }
        }
        if(select(dn_s,pt_l).getId()!=-2){
            pk_l.push_back(select(dn_s,pt_l));
            update(select(dn_s,pt_l),dn_s);
        }
        
    }
    return pk_l;
}