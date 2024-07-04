#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <cmath>
using namespace std ;

class Employee{
    public:
        int id ;
        string inorout;
        long long time ;
}e[130000] ;

class Output{
    public:
        int id = 0;
        int overtime = 0;
        int forget = 0;
}f[130000] ;

long long s_to_i(string str)
{
    long long result=0;
    for(int i=11;i>=0;i--) //12位數
    {
        result=result+(str[i]-'0')*pow(10,11-i);
    }
    return result;
}

bool compare(Employee a,Employee b)
{
    if(a.id==b.id)
    {
        return a.time<b.time;
    }
    else
    {
        return a.id<b.id;
    }
}

int main(int argv, char **argc){
    ifstream inputFile(argc[1]);
    string line;
    int n=0; //員工數量
    while(getline(inputFile,line))
    {
        stringstream ss(line);
        string tmp;

        getline(ss,tmp,',');
        e[n].id=stoi(tmp);

        getline(ss,tmp,',');
        e[n].inorout=tmp;

        getline(ss,tmp);
        e[n].time=s_to_i(tmp); //物
        
        n++;
    }
    sort(e,e+n,compare);//先將所有排序好


    int ii = 0;//員工數

    f[0].id = e[0].id ;
    int temp = 0;
    for(int i = 0; i<(n -1) ; i++){
        int aa = (e[i].time/10000); //日期
        int bb = (e[i+1].time/10000); //日期
        
        if(aa == bb && e[i].id == e[i+1].id){ //日期相同且id相同 //計算是否超時
            int aaa = ((e[i].time%10000)/100)*60 + (e[i].time%100);  //分鐘
            int bbb = ((e[i+1].time%10000)/100)*60 + (e[i+1].time%100);
            if(bbb - aaa > 480){
                f[ii].overtime++ ;
            }
            temp = 1;
        }
        else if(aa != bb && e[i].id == e[i+1].id){ //下一個還是同一個人但是日期不相同
            if(temp == 0){
                f[ii].forget++;
            }
            temp = 0 ;
        }
        else if(e[i].id != e[i+1].id){ //換員工了
            f[ii+1].id = e[i+1].id ;
            if(temp == 0){
                f[ii].forget++;
            }
            temp = 0;
            
            ii++;
        }

        if(i == n-2 && temp == 0){
            f[ii].forget++;
        }
    }

    //output
    for(int i=0;i<=ii;i++)
    {
        cout << f[i].id << ',' << f[i].overtime << ',' << f[i].forget << endl ;
    }
}