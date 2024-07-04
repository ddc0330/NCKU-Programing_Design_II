#include <bits/stdc++.h>
#include <ctime>
using namespace std ;

class Employee{
    public:
        int id ;
        string inorout;
        long long time ;
}e[10000000] ;

class Output{
    public:
        int id ;
        int days=1;
        long long start ;
        long long end ;
}f[100000] ;

long long s_to_i(string str){
    long long result=0;
    for(int i=11;i>=0;i--) //12位數
    {
        result=result+(str[i]-'0')*pow(10,11-i);
    }
    return result;
}

bool compare(Employee a,Employee b){
    if(a.id==b.id)
    {
        return a.time<b.time;
    }
    else
    {
        return a.id<b.id;
    }
}

bool final(Output a , Output b){
    if(a.days==b.days){
        return a.id < b.id;
    }
    else{
        return a.days > b.days ;
    }

}

int daycoday(long long a , long long b){ //1表示兩者差一天 0表示兩者同一天
    struct tm start = {0};
    start.tm_year = (a/100000000) - 1900 ;
    start.tm_mon = ((a/1000000)%100) - 1 ;
    start.tm_mday = (a/10000)%100 ;

    struct tm end = {0};
    end.tm_year = (b/100000000) - 1900 ;
    end.tm_mon = ((b/1000000)%100) - 1 ;
    end.tm_mday = (b/10000)%100 ;

    // 轉換為 time_t 格式
    time_t start_time = mktime(&start);
    time_t end_time = mktime(&end);

    // 計算兩個日期之間的天數
    double diff_seconds = difftime(end_time, start_time);
    int days = diff_seconds / (60 * 60 * 24);
    return days ;
}

int main(int argv, char **argc){
    ifstream inputFile(argc[1]);
    string line;
    int n=0; //資料數量
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

    //判斷(將連續工作的天數找出來)
    int nn = 0; //員工數量
    int temp = 1 ; //算我此時看得連續天數
    f[0].id = e[0].id ;
    int kk = 0 ; //算我在temp時前後兩天同一天的天數
    for(int i=0;i<n-1;i++){
        if(e[i].id == e[i+1].id){ //前後同員工
            if(daycoday(e[i].time ,e[i+1].time) == 1){
                temp++ ;
            }
            else if(daycoday(e[i].time ,e[i+1].time) == 0){
                kk++;
            }
            else{ //斷掉
                if(temp >= f[nn].days){
                    f[nn].days = temp ;
                    f[nn].start = e[i-kk-temp+1].time/10000;
                    f[nn].end = e[i].time/10000 ;
                    temp = 1 ;
                    kk = 0;
                }
            }
        }
        else{//換下一個員工了
            if(temp >= f[nn].days){
                f[nn].days = temp ;
                f[nn].start = e[i-kk-temp+1].time/10000 ;
                f[nn].end = e[i].time/10000 ;
                kk = 0;
            }
            temp = 1 ;
            nn++ ;
            f[nn].id = e[i+1].id ;
        }
    }

    //判斷(找出最前面的三個人)
    
    //先將他們依照連續天數大小排序//接著再將同天數的人id由小排到大
    sort(f,f+nn+1,final);
    //接著找最前面的三個人
    Output g[3];
    g[0] = f[0] ;
    int ss = 1;
    int jj = 1 ;
    while(ss<3){
        if(f[jj-1].id != f[jj].id){
            g[ss] = f[jj];
            ss++;
        }
        jj++;
    }

    //output
    for(int i=0;i<3;i++){
        cout << g[i].id << ',' << g[i].days << ',' << g[i].start<< ',' << g[i].end << endl;
    }
}