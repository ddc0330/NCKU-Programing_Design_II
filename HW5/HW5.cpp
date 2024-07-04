#include <bits/stdc++.h>
#include <map>
#include <string>
#include <vector>

using namespace std ;

int main(int argv, char **argc){
    map<int,string>myMap;
    ifstream inputFile1(argc[1]);
    string line;
    while(getline(inputFile1,line)){ //讀資料進到MAP 
        string tmp = "";
        int i=0,id;
        for(i=0;i<line.length();i++){
            if(line[i]==','){ //掃到逗號後就會去跑後面
                break;
            }
            else{
                tmp = tmp + line[i];
            }
        }
        id=stoi(tmp);
        tmp="";
        for(;i<line.length();i++){
            if(line[i]>='A'&&line[i]<='Z'){
                line[i]+=32;
                tmp = tmp + line[i];
            }
            else if((line[i]>='a'&& line[i]<='z') || line[i]==' ')
                tmp = tmp + line[i];
        }
        tmp += " ";
        myMap[id]=tmp;
    }
    
    vector<int>results;
    ifstream inputFile2(argc[2]);
    while(getline(inputFile2,line)){
        string tmp[3]={};
        int n=0;//一行的單字數量-1
        for(int i=0;i<line.length();i++){ //把單字存進tmp
            if(line[i]==' '){
                n++;
            }
            else if(line[i]>='A'&&line[i]<='Z'){
                line[i]+=32;
                tmp[n] += line[i];
            }
            else{
                tmp[n] += line[i];
            }
        }
        string tmpp[3]={};
        for(int i=0;i<=n;i++){
            tmpp[i] = " " + tmp[i] + " ";
        }
        int tof=0;
        int kk=0;
        int ss=0;
        for (auto it = myMap.begin(); it != myMap.end(); ++it) {
            tof=0;
            for(int i=0;i<=n;i++){
                if (it->second.find(tmpp[i]) == string::npos) { //沒找到
                    tof = 1;//表示其中一個單字不再這一行
                }
            }
            if(tof == 0 && ss==0){
                cout << it->first;
                kk=1;
                ss=1;
            }
            else if(tof == 0){
                cout << " " << it->first;
                kk=1;
            }
        }
        if(kk==0){
            cout << "-1" ;
        }
        cout << endl;
    }

    for (const auto& result : results) {
            cout << result << endl;
    }
    return 0 ;
}