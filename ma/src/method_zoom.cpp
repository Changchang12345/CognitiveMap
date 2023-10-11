#include<iostream>
#include <stdlib.h>
#include "C:\ma\include\building.h"
#include "C:\ma\include\method.h"
// #include "D:\ma\include\method_zoom.h"
#include<vector>
#include<fstream>
#include <string>
#include <iomanip>
#include <sstream>
#include<algorithm>

using namespace std;


// extern vector<building> Pzoom;
vector<building> pt;
vector<building> dni;//合并的分段集
vector<building> dno;//合并的分段集
int cnt_in=0;//合并次数zoomin
int cnt_out=0;//合并次数zoomout

/* ---------method_zoom计算在线算法中的放大缩小操作--------------- */


building select_zoom(vector<building> dn){
    double max=1.0;
    int flag=0,i=0,idx=0;

    for(building p : pt)
    {
        //cout<<"pt.getChoose()---"<<pt.at(4).getChoose()<<"----pt.getID()---"<<pt.at(4).getId()<<endl;
        // cout<<"p.getChoose()---"<<p.getChoose()<<"----p.getID()---"<<p.getId()<<"----p.getprofit()---"<<getProfit(p,dn)<<endl;
        if(p.getChoose()!=true){
            double pr = getProfit(p,dn);
            if(max<pr){ 
                flag=1;  
                // cout<<"p.getChoose()---"<<p.getChoose()<<"----p.getID()---"<<p.getId()<<endl;
                max = pr;
                idx=i;
            }
            
        }
        i++;
        cnt_in++;
        cnt_out++;
    }
    if(pt.at(idx).getChoose()==false){
        pt.at(idx).setChoose(true);
        return pt.at(idx);
    }
    else{
        building b;
        b.setId(-5);
        return b;
    }
    
}

/* 算法4 ：zoom-in p为上一窗口的候选对象----放大----k,当前w起点，当前w终点，上一w起点，上一w终点，上一w已选对象集*/
vector<building> zoom_in(int k,double wi_start,double wi_end,vector<building> p,vector<building>& Pzoom,double bi){
    cnt_in=0;
    vector<building>().swap(dni);
    vector<building>().swap(pt);
    // Pzoom = readCsvByCsvReader("C:\\ma\\src\\resource\\Seg_score_150_no_12.csv");
    // vector<building> pt;
    //候选对象集
    vector<building> pk;//结果集
    
    int flag=0;
    for(building b:p){
        if ((b.getLocation()<=wi_end&&b.getLocation()>wi_start)){
            if((b.getLength()/bi)>b.getLength()){
                b.setLength(b.getLength()/bi);
                b.setStart(b.getLocation()-b.getLength()/2);
                b.setEnd(b.getLocation()+b.getLength()/2);
            }
            pk.push_back(b);
            if(flag==0){
                dni.push_back(b); 
                flag=1;
            }   
            else
            {
                update(b,dni);
            }
        }
        cnt_in++;
        
    }
    int f=0;
    for(building p:Pzoom){
        f=0;
        if ((p.getLocation()<=wi_end&&p.getLocation()>wi_start))
        {
            for(building pz:pk){
                if(pz.getId()==p.getId()){
                    f=1;
                    break;
                }
            }
            if(f==0){
                if((p.getLength()/bi)>p.getLength()){
                    p.setLength(p.getLength()*bi);
                    p.setStart(p.getLocation()-p.getLength()/2);
                    p.setEnd(p.getLocation()+p.getLength()/2);
                }
                p.setChoose(false);
                pt.push_back(p);
            }
            
        }
        if(p.getLocation()>wi_end){
            break;
        }
        cnt_in++;
    }
    if(pt.size()==0){
        return pk;
    }
    k = k-pk.size();
    for(int i=0;i<k;i++){
        building pl = select_zoom(dni);
        if(pl.getId()!=-5){
           pk.push_back(pl);
            update(pl,dni); 
        }
        // cout<<"pl.getChoose()---"<<pl.getChoose()<<"----pl.getID()---"<<pl.getId()<<"----pl.getprofit()---"<<getProfit(pl,dni)<<endl;
    }
    cout << "cnt_in:  " << cnt_in <<endl; 
    return pk;
}


/* 算法5 ：zoom-out p为上一窗口的候选对象----缩小----k,上一w起点，上一w终点，当前w起点，当前w终点，上一w已选对象集*/
vector<building> zoom_out(int k,double wi_start,double wi_end,double wi_1_start,double wi_1_end,vector<building> p,vector<building>& Pzoom,double bi){
    cnt_out=0;
    vector<building>().swap(dno);
    vector<building>().swap(pt);
    // Pzoom = readCsvByCsvReader("C:\\ma\\src\\resource\\Seg_score_150_no_12.csv");
    vector<building> pk;//结果集
    int flag=0;
    pt=p;
    for(building b:p){
        b.setLength(b.getLength()*bi);
        b.setStart(b.getLocation()-b.getLength()/2);
        b.setEnd(b.getLocation()+b.getLength()/2);
        update(b,dno);
        cnt_out++;
    }
    for(building b:Pzoom){
        if((b.getLocation()<=wi_1_end&&b.getLocation()>wi_1_start)&&(b.getLocation()<=wi_start||b.getLocation()>wi_end)){
            b.setLength(b.getLength()*bi);
            b.setStart(b.getLocation()-b.getLength()/2);
            b.setEnd(b.getLocation()+b.getLength()/2);
            pt.push_back(b);
        }
        if(b.getLocation()>wi_end){
            break;
        }
        cnt_out++;
    }
    for(int i=0;i<k;i++){
        building pl = select_zoom(dno);
        if(pl.getId()!=-5){
            pk.push_back(pl);
            // cout<<"pl.getChoose()---"<<pl.getChoose()<<"----pl.getID()---"<<pl.getId()<<"----pl.getprofit()---"<<getProfit(pl,dno)<<endl;
            update(pl,dno); 
        }
        cnt_out++;
       }
       cout << "cnt_out:  " << cnt_out <<endl; 
    return pk;
}


/* 计算认知收益值 */
double calplzi(){
    double res=0.0;
    for(building b:dni){
        res+=b.getRange();
    }
    return res;
}

double calplzo(){
    double res=0.0;
    for(building b:dno){
        res+=b.getRange();
    }
    return res;
}
