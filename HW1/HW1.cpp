#include <iostream>
#include <string>
using namespace std;
int main(int argc, char** argv)
{
    int a = stoi(argv[1]) ;
    int max = 0;
    for(int i = 0 ; i <= a ; i++){
        cout << "(" << i << "," << a - i << ")" << endl;
        if((i * (a-i)) > max){
            max = i * (a-i) ;
        }
    }
    cout << max ;
    return 0 ;
}