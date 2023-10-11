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



extern vector<building> P;
extern int cnt_out;
extern int cnt_in;



/* 获取单个对象带来的认知收益新增值 */
double getProfit(building p,vector<building> pa){
    // cout<<"p.getId()---"<<p.getLocation()<<endl;
    double ls = p.getStart();
    double le = p.getEnd();
    double profit = le-ls;
    for(building paa : pa)
    {
        // cout<<"pa.size()---"<<pa.size()<<endl;
        if(paa.getEnd()<ls||paa.getStart()>le){//两段无交集
            profit-=0;
            continue;
        }
        
        if(paa.getStart()>ls&&paa.getEnd()<le){//paa被包含
            profit-=paa.getRange();
            continue;
        }
        
        if(paa.getStart()<=ls&&paa.getEnd()>=le){//p被包含
            profit=0.0;
            break;
        }
        
        if(paa.getStart()<ls&&paa.getEnd()<le){//-------- paa
            profit-=(paa.getEnd()-ls);         //   --------  p
            continue;
        }

        if(paa.getStart()>ls&&paa.getEnd()>le){//   --------  paa
            profit-=(le-paa.getStart());       //--------   p
            continue;
        }
    }
        return profit;
    }



/* 将所有建筑物段变成互不相交的段 */
void update(building pt,vector<building>& dn){
    vector<int> aa;
        int k=0;
        double s=pt.getStart();
        double e=pt.getEnd();
        // cout<<"s----"<<s<<"----e------"<<e<<"   id:  "<<pt.getId()<<endl;

        for(building l:dn){//System.out.println(l.start+"==="+l.end);
            //l包含a完整建筑物
            if(l.getStart()<s&&l.getEnd()>e){
                return ;
            }
            //a包含l完整建筑物
            if((l.getStart()>=s&&l.getEnd()<=e)){
                aa.push_back(k);
            }
            else
            {//a包含l不完整建筑物（部分交叠）

                if (l.getEnd()>s&&l.getEnd()<e){//左部分交叠
                    s=l.getStart();aa.push_back(k);
                }
                if(l.getStart()<e&&l.getStart()>s){//右部分交叠
                    e=l.getEnd();aa.push_back(k);
                }

            }
            k++;
            cnt_out++;
            cnt_in++;
        }
        auto it = dn.begin();
        for(int i:aa){
            dn.erase(it+i);
            cnt_out++;
        }
        building b = building();
        b.setEnd(e);
        b.setStart(s);
        b.setLength(b.getEnd()- b.getStart());
        dn.push_back(b);
        /* for(building b:dn){
            cout << "b.getRange()---" << b.getRange() << "  b.getId()-----" << b.getId() << endl;
            
        } */
        return ;
}



/* 读取文件数据，写入P */
vector<building> readCsvByCsvReader(string filePath){

    

    vector<building> bs;
    ifstream inFile(filePath, ios::in);
    if (!inFile)
    {
        cout << "无法打开文件" << endl;
        exit(1);
    }
    int i = 0;
    string line;
    string field;
    getline(inFile, line);
    while (getline(inFile, line))//getline(inFile, line)表示按行读取CSV文件中的数据
    {
        
        string field;
        istringstream sin(line); //将整行字符串line读入到字符串流sin中

        getline(sin, field, ','); //将字符串流sin中的字符读入到field字符串中，以逗号为分隔符 
        //cout<<field.c_str()<<" ";//将刚刚读取的字符串转换成int

        getline(sin, field, ','); //将字符串流sin中的字符读入到field字符串中，以逗号为分隔符 
        int id = atoi(field.c_str());
        //cout << atoi(field.c_str()) << " ";//将刚刚读取的字符串转换成int

        getline(sin, field, ','); //将字符串流sin中的字符读入到field字符串中，以逗号为分隔符 
        int location = atoi(field.c_str());
        //cout << atoi(field.c_str()) << " ";//将刚刚读取的字符串转换成int

        getline(sin, field, ','); //将字符串流sin中的字符读入到field字符串中，以逗号为分隔符 
        //cout << atof(field.c_str()) << " ";//将刚刚读取的字符串转换成int

        getline(sin, field, ','); //将字符串流sin中的字符读入到field字符串中，以逗号为分隔符 
        // double range = atof(field.c_str());
        //cout << atof(field.c_str()) << " ";//将刚刚读取的字符串转换成int

        getline(sin, field, ','); //将字符串流sin中的字符读入到field字符串中，以逗号为分隔符 
        double start = atof(field.c_str());
        if(start<0)start=0.0;
        //cout << atof(field.c_str()) <<" ";//将刚刚读取的字符串转换成int
        //cout << start <<" ";//将刚刚读取的字符串转换成int

        getline(sin, field); //将字符串流sin中的字符读入到field字符串中，以逗号为分隔符 
        double end = atof(field.c_str());
        //cout << end << endl;//将刚刚读取的字符串转换成int 
        double range = end-start;
        building b = building(id,location,range,start,end,0,false);
        // cout<<b.getLocation()<<endl;
        bs.push_back(b);
        i++; 
    }
    inFile.close();
    cout << "共读取了：" << i << "行" << endl;
    cout << "读取数据完成" << endl;
    return bs;
}


