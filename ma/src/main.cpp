#include<iostream>
#include<istream>
#include <stdlib.h>
#include "C:\ma\include\method_slidew.h"
#include "C:\ma\include\method_zoom.h"
#include "C:\ma\include\pre_selection.h"
#include "C:\ma\include\poltree.h"
#include "C:\ma\include\tree.h"
#include "C:\ma\include\building.h"
#include "C:\ma\include\method.h"
#include<vector>
#include <windows.h>


using namespace std;

int main(int argc, char *argv[])
{

    int choose = 0,time1,time2,cnt=0;
    vector<building> pi,po,pk_p,p,a,lb,res;
    int k=0,n,i=0;
    double w=0,s=0,we,ws,wie,wis,pl;
    building pi2,pi1;
    tree pol_tree;
    DWORD time_start, time_end;
    while (1)
    {
            //菜单栏
    cout << "********************************************" << endl;
    cout << "* ---请输入您想进行操作的数字---             *" << endl;
    cout << "* 1. 读取文件中的建筑物                     *" << endl;
    cout << "* 2. 在线滑动窗口查询                       *" << endl;//online grredy
    cout << "* 3. 在线zoom in查询                       *" << endl;
    cout << "* 4. 在线zoom out查询                      *" << endl;
    cout << "* 5. 全局预选择查询                         *" << endl;//precom greedy 
    cout << "* 6. 单窗口预选择查询(以5为输入，可用于zoom选择)             *" << endl;
    cout << "* 7. 构建POL索引树                          *" << endl;//前提5
    cout << "* 8. 通过索引树获得窗口对象集合（可用于zoom选择）              *" << endl;//preindex  前提7
    cout << "* 9. 通过索引树获得窗口对象集合i+1层          *" << endl;//preindex  前提7
    cout << "* 10. 通过索引树获得窗口对象集合i-1层          *" << endl;//preindex  前提7
    cout << "* 11. 通过预选择获取窗口内对象集(sliding选择) *" << endl;
    cout << "* 12. 通过预选择+索引树获取窗口内对象集(sliding选择) *" << endl;
    cout << "* 13. selectRank算法                           *" << endl;
    cout << "* 14. LocationRank算法                         *" << endl;
    cout << "* 15. 通过索引树获得窗口对象集合i-2层         *" << endl;//preindex  前提7
    cout << "* 16. 通过索引树获得窗口对象集合i-3层         *" << endl;//preindex  前提7
    cout << "* 17. 通过索引树获得窗口对象集合i+2层         *" << endl;//preindex  前提7
    cout << "* 18. 通过索引树获得窗口对象集合i+3层         *" << endl;//preindex  前提7
    cout << "********************************************" << endl;
        cout <<"请输入您的选择： " ;
        cin >> choose;
        switch (choose)
        {
        case 1:
            p=readCsvByCsvReader("C:\\ma\\src\\resource\\dist.csv");//Seg_score_150_no_12
            cout << "succeed!" << endl;
            break;
        case 2:
            cout << "请输入k值" <<endl;
            cin >> k;
            cout << "请输入w长度" <<endl;
            cin >> w;
            cout << "请输入s长度" <<endl;
            cin >> s;
            time_start = GetTickCount(); //从操作系统启动经过的毫秒数
            slidingW(k,w,s,p);
            time_end = GetTickCount();
            cout << "Time = " << (time_end - time_start) << "ms\n ";
            pl = calpl();
            cout<< "认知收益" <<pl<<endl;
            // cout <<  pl << endl;
            break;
        case 3://放大
            cout << "请输入k值" <<endl;
            cin >> k;
            cout << "请输入新w起始位置" <<endl;
            cin >> ws;
            cout << "请输入新w结束位置" <<endl;
            cin >> we;
            cout << "请输入上一w起始位置" <<endl;
            cin >> wis;
            cout << "请输入上一w结束位置" <<endl;
            cin >> wie;
            // vector<building> pi;
            pi = pre(wis,wie,k,wie-wis,pk_p);
            // pi.push_back(building(5,1250,751.8494487,498.1505513,2001.849449,0,1));
            // pi.push_back(building(8,1630,633.6695948,996.3304053,2263.669595,0,1));
            time_start = GetTickCount(); //从操作系统启动经过的毫秒数
            a = zoom_in(k,ws,we,pi,p,(wie-wis)/(we-ws));
            time_end = GetTickCount();
            cout << "Time = " << (time_end - time_start) << "ms\n ";
            for(building b:a){
                cout<<b.getId()<<endl;
            }
            pl = calplzi();
            cout << "认知收益" << pl << endl;
            break;
        case 4://缩小
            cout << "请输入k值" <<endl;
            cin >> k;
            cout << "请输入上一w起始位置" <<endl;
            cin >> ws;
            cout << "请输入上一w结束位置" <<endl;
            cin >> we;
            cout << "请输入新w起始位置" <<endl;
            cin >> wis;
            cout << "请输入新w结束位置" <<endl;
            cin >> wie;
            // vector<building> po;
            po = pre(ws,we,k,we-ws,pk_p);
            // po.push_back(building(8,1630,633.6695948,996.3304053,2263.669595,0,1));//
            // po.push_back(building(6,1370,478.5880545,891.4119455,1848.588055,0,1));
            time_start = GetTickCount(); //从操作系统启动经过的毫秒数
            a = zoom_out(k,ws,we,wis,wie,po,p,(wie-wis)/(we-ws));
            time_end = GetTickCount();
            cout << "Time = " << (time_end - time_start) << "ms\n ";
            for(building b:a){
                cout<<b.getId()<<endl;
            }
            pl = calplzo();
            cout << "认知收益" << pl << endl;
            break;
        case 5:
            // int k=0;
            // double s=0,w=0;
            cout << "请输入k值" <<endl;
            cin >> k;
            cout << "请输入w长度" <<endl;
            cin >> w;
            time_start = GetTickCount(); //从操作系统启动经过的毫秒数
            pk_p= preSelection(k,w,p);
            time_end = GetTickCount();
            cout << "Time = " << (time_end - time_start) << "ms\n ";
            
            pl = calplp();
            cout << "认知收益" << pl << endl;
            break;
        case 6:
            // int k=0;
            // double s=0,w=0;
            cout << "请输入k值" <<endl;
            cin >> k;
            cout << "请输入w长度" <<endl;
            cin >> w;
            cout << "请输入w起点位置" <<endl;
            cin >> ws;
            cout << "请输入w终点位置" <<endl;
            cin >> we;
            time_start = GetTickCount(); //从操作系统启动经过的毫秒数
            res = pre(ws,we,k,w,pk_p);
            time_end = GetTickCount();
            cout << "Time = " << (time_end - time_start) << "ms\n ";
            pl = calpre(res);
            cout << "认知收益" << pl << endl;
            break;
            
        case 7:
            cout << "请输入层数" <<endl;
            cin >> n;
            cout << "请输入s长度" <<endl;
            cin >> s;
            time_start = GetTickCount(); //从操作系统启动经过的毫秒数
            createTree(n,pk_p,s);
            time_end = GetTickCount();
            cout << "Time = " << (time_end - time_start) << "ms\n ";
            i=0;
            break;

        case 8:
            // double s=0,w=0;
            cout << "请输入k值" <<endl;
            cin >> k;
            cout << "请输入w起点位置" <<endl;
            cin >> ws;
            cout << "请输入w终点位置" <<endl;
            cin >> we;
            cout << "请输入s长度" <<endl;
            cin >> s;
            time_start = GetTickCount(); //从操作系统启动经过的毫秒数
            lb = selectList(pol_tree,k,ws,we,s,pk_p.size()); 
            time_end = GetTickCount();
            
            cout << "Time = " << (time_end - time_start) << "ms\n ";
            
            // for(building v:lb){
            //     cout << v.getId() << " " <<endl;
            //     cout << "Hello world!!!" << endl;
            // }
            pl = calpol(lb);
            cout << "认知收益" << pl << endl;
            break;
        case 9:
            // double s=0,w=0;
            cout << "请输入k值" <<endl;
            cin >> k;
            cout << "请输入w起点位置" <<endl;
            cin >> ws;
            cout << "请输入w终点位置" <<endl;
            cin >> we;
            cout << "请输入s长度" <<endl;
            cin >> s;
            time_start = GetTickCount(); //从操作系统启动经过的毫秒数
            lb = selectList_next(pol_tree,k,ws,we,s,pk_p.size()); 
            time_end = GetTickCount();
            cout << "Time = " << (time_end - time_start) << "ms\n ";
            
            // for(building v:lb){
            //     cout << v.getId() << " " <<endl;
            //     cout << "Hello world!!!" << endl;
            // }
            pl = calpol(lb);
            cout << "认知收益" << pl << endl;
            break;
        case 10:
            // double s=0,w=0;
            cout << "请输入k值" <<endl;
            cin >> k;
            cout << "请输入w起点位置" <<endl;
            cin >> ws;
            cout << "请输入w终点位置" <<endl;
            cin >> we;
            cout << "请输入s长度" <<endl;
            cin >> s;
            time_start = GetTickCount(); //从操作系统启动经过的毫秒数
            lb = selectList_pre(pol_tree,k,ws,we,s,pk_p.size()); 
            time_end = GetTickCount();
            cout << "Time = " << (time_end - time_start) << "ms\n ";
            
            // for(building v:lb){
            //     cout << v.getId() << " " <<endl;
            //     cout << "Hello world!!!" << endl;
            // }
            pl = calpol(lb);
            cout << "认知收益" << pl << endl;
            break;
        case 11:
            cout << "请输入k值" <<endl;
            cin >> k;
            cout << "请输入w长度" <<endl;
            cin >> w;
            cout << "请输入s长度" <<endl;
            cin >> s;
            time_start = GetTickCount(); //从操作系统启动经过的毫秒数
            preSliding(k,w,s,pk_p);
            time_end = GetTickCount();
            cout << "Time = " << (time_end - time_start) << "ms\n ";
            pl = calpl();
            cout<< "认知收益" <<pl<<endl;
            break;
        case 12:
            cout << "请输入k值" <<endl;
            cin >> k;
            cout << "请输入w长度" <<endl;
            cin >> w;
            cout << "请输入s长度" <<endl;
            cin >> s;
            time_start = GetTickCount(); //从操作系统启动经过的毫秒数
            lb = precomIndex_sliding(k,s,w,pk_p.size());
            time_end = GetTickCount();
            cout << "Time = " << (time_end - time_start) << "ms\n ";
            pl = calpol(lb);
            cout<< "认知收益" <<pl<<endl;
            break;
        case 13:
            cout << "请输入k值" <<endl;
            cin >> k;
            cout << "请输入w长度" <<endl;
            cin >> w;
            cout << "请输入s长度" <<endl;
            cin >> s;
            time_start = GetTickCount(); //从操作系统启动经过的毫秒数
            lb=rankSelect(k,w,s,p);
            time_end = GetTickCount();
            cout << "Time = " << (time_end - time_start) << "ms\n ";
            pl = calpl();
            cout<< "认知收益" <<pl<<endl;
            break;
        case 14:
            cout << "请输入k值" <<endl;
            cin >> k;
            cout << "请输入w长度" <<endl;
            cin >> w;
            cout << "请输入s长度" <<endl;
            cin >> s;
            time_start = GetTickCount(); //从操作系统启动经过的毫秒数
            lb=locationSelect(k,w,s,p);
            time_end = GetTickCount();
            cout << "Time = " << (time_end - time_start) << "ms\n ";
            pl = calpl();
            cout<< "认知收益" <<pl<<endl;
            break;
        case 15:
            // double s=0,w=0;
            cout << "请输入k值" <<endl;
            cin >> k;
            cout << "请输入w起点位置" <<endl;
            cin >> ws;
            cout << "请输入w终点位置" <<endl;
            cin >> we;
            cout << "请输入s长度" <<endl;
            cin >> s;
            time_start = GetTickCount(); //从操作系统启动经过的毫秒数
            lb = selectList_i_2(pol_tree,k,ws,we,s,pk_p.size()); 
            time_end = GetTickCount();
            cout << "Time = " << (time_end - time_start) << "ms\n ";
            // for(building v:lb){
            //     cout << v.getId() << " " <<endl;
            //     cout << "Hello world!!!" << endl;
            // }
            pl = calpol(lb);
            cout << "认知收益" << pl << endl;
            break;

        case 16:
            // double s=0,w=0;
            cout << "请输入k值" <<endl;
            cin >> k;
            cout << "请输入w起点位置" <<endl;
            cin >> ws;
            cout << "请输入w终点位置" <<endl;
            cin >> we;
            cout << "请输入s长度" <<endl;
            cin >> s;
            time_start = GetTickCount(); //从操作系统启动经过的毫秒数
            lb = selectList_i_3(pol_tree,k,ws,we,s,pk_p.size()); 
            time_end = GetTickCount();
            cout << "Time = " << (time_end - time_start) << "ms\n ";
            // for(building v:lb){
            //     cout << v.getId() << " " <<endl;
            //     cout << "Hello world!!!" << endl;
            // }
            pl = calpol(lb);
            cout << "认知收益" << pl << endl;
            break;
        case 17:
            // double s=0,w=0;
            cout << "请输入k值" <<endl;
            cin >> k;
            cout << "请输入w起点位置" <<endl;
            cin >> ws;
            cout << "请输入w终点位置" <<endl;
            cin >> we;
            cout << "请输入s长度" <<endl;
            cin >> s;
            time_start = GetTickCount(); //从操作系统启动经过的毫秒数
            lb = selectList_next1(pol_tree,k,ws,we,s,pk_p.size()); 
            time_end = GetTickCount();
            cout << "Time = " << (time_end - time_start) << "ms\n ";
            // for(building v:lb){
            //     cout << v.getId() << " " <<endl;
            //     cout << "Hello world!!!" << endl;
            // }
            pl = calpol(lb);
            cout << "认知收益" << pl << endl;
            break;
        case 18:
            // double s=0,w=0;
            cout << "请输入k值" <<endl;
            cin >> k;
            cout << "请输入w起点位置" <<endl;
            cin >> ws;
            cout << "请输入w终点位置" <<endl;
            cin >> we;
            cout << "请输入s长度" <<endl;
            cin >> s;
            time_start = GetTickCount(); //从操作系统启动经过的毫秒数
            lb = selectList_next2(pol_tree,k,ws,we,s,pk_p.size()); 
            time_end = GetTickCount();
            cout << "Time = " << (time_end - time_start) << "ms\n ";
            // for(building v:lb){
            //     cout << v.getId() << " " <<endl;
            //     cout << "Hello world!!!" << endl;
            // }
            pl = calpol(lb);
            cout << "认知收益" << pl << endl;
            break;
        default:
            break;
        }
    }
    
    
    /* k,p,w 滑动窗口 */
	// slidingW(3,1500,12560);
    // calpl();


    /* 放大 */
    /* vector<building> pi;
    pi.push_back(building(5,1250,751.8494487,498.1505513,2001.849449,0,1));
    pi.push_back(building(8,1630,633.6695948,996.3304053,2263.669595,0,1));
    vector<building> a = zoom_in(3,1300,1700,pi);
    for(building b:a){
        cout<<b.getId()<<endl;
    } */


    /* 缩小 */
/*     vector<building> pi;
    // pi.push_back(building(5,1250,751.8494487,498.1505513,2001.849449,0,1));
    pi.push_back(building(8,1630,633.6695948,996.3304053,2263.669595,0,1));//
    pi.push_back(building(6,1370,478.5880545,891.4119455,1848.588055,0,1));//
    vector<building> a = zoom_out(3,1300,1700,1000,2000,pi); */


    /* 全局预选择无索引结构 */
    // vector<building> pk = preSelection(3,900);
    // pre(1000,3000,5,1500);


    /* zoom预选择 */
    /* 建立树索引 */
    /* 全局预选择有索引结构 */
   /*  vector<vector<poltree>> pol_tree = createTree(4,pk,12560.0);
    int i=0;
    for(vector<poltree> v: pol_tree){
        cout<<i<<endl;
        for(poltree b:v){ 
            cout<<b.getPolidx()<<" "<< b.getHead() << " " << b.getProject().getId() << " ===";
            // cout<<b.getProject().getId()<<" ";
        }
        cout<<endl;
        i++;
    } */
    /* 选择层数 */
    /* vector<building> lb = selectList(pol_tree,3,1000,4000,12560);
    for(building v:lb){
        cout << v.getId() << " " <<endl;
        cout << "Hello world!!!" << endl;
    } */
	cout << "Hello world!!!" << endl;
    /* 树索引选择k个 */
    // vector<building> lb = getTurn(pol_tree,1000,3000,5);
    // for(building b:lb){
    //     cout << b.getOrd() << " " << endl;
    //     cout << "Hello world!!!" << endl;
    // }





}