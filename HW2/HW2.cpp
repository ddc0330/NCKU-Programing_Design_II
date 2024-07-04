#include<fstream>
#include<iostream>
#include<algorithm>
using namespace std ;

class Employee{
    public:
        int id;
        int age;
        char gender;
        int salary;
}e[100000];

int main(int argv, char **argc){
    ifstream inputFile(argc[1]); //找時間重看
    int i = 0;
    char tmp ;
    while(inputFile >> e[i].id >> tmp >> e[i].age >> tmp >> e[i].gender >> tmp >> e[i].salary){
        i++;
    } 
    //sort //照年齡遞增 //若年齡相同則女士優先 //先全部排列好最後輸出再換行
    for(int j = 0 ; j < i - 1 ; j++){
        for(int k = 0 ; j < i-j-1 ; k++){
            Employee temp;
            if(e[j].salary > e[j].salary){
                temp = e[j] ;
                e[j+1] = e[j] ;
                e[j] = temp ;     
            }
            else if(e[j].salary == e[j].salary && e[j].age > e[j].age){
                temp = e[j] ;
                e[j+1] = e[j] ;
                e[j] = temp ;
            }
            else if(e[j].salary == e[j].salary && e[j].age == e[j].age && e[j].gender == 'm' && e[j].gender == 'f'){
                temp = e[j] ;
                e[j+1] = e[j] ;
                e[j] = temp ;
            }
            else if(){
                
            }
        }
    }
    //outpout
    cout << e[0].salary << ',' << e[0].id;
	for(int j = 1; j < i; j++){
		if(e[j-1].salary != e[j].salary){
			cout << endl;
			cout << e[j].salary;
		}
		cout << ',' << e[j].id;
	}
	cout << endl;
}