#include <bits/stdc++.h>
using namespace std;

class Ans
{
    public:
        int sid;
        double idf_sum;
};
bool compare(Ans a,Ans b)
{
    if(a.idf_sum==b.idf_sum)
    {
        return a.sid<b.sid;
    }
    else
    {
        return a.idf_sum>b.idf_sum;
    }
}

int main(int argv, char **argc)
{
    map<string,set<int>> s_id_map; //corpus的單字,他在的s_id
    ifstream corpus(argc[1]);
    ifstream query(argc[2]);
    int k=stoi(argc[3]);
    string line;
    long int strnum=0; //整個corpus的單字數
    while(getline(corpus,line))
    {
        //存取當前行的s_id
        stringstream ss(line);
        string tmp;
        int s_id;
        getline(ss,tmp,',');
        s_id=stoi(tmp);
        //把corpus單字放進s_id_map
        while(getline(ss,tmp,' '))
        {
            string word="";
            for(int i=0;i<tmp.length();i++)
            {
                if(tmp[i]>='A' && tmp[i]<='Z')
                {
                    tmp[i]=tmp[i]+32;
                    word=word+ tmp[i];
                }
                else if(tmp[i]>='a' && tmp[i]<='z')
                {
                    word=word+tmp[i];
                }
            }
            if(word!="")
            {
                 //s_id_map[word]=所在s_id形成的set
            }
        }
        strnum++;
    }

    while(getline(query,line))
    {
        map<int,double> id_idfsum_map;//id,idfsum
        stringstream ss(line);
        string tmp;
        vector<Ans> ans;
        while(getline(ss,tmp,' '))
        {
            string word="";
            for(int i=0;i<tmp.length();i++)
            {
                if(tmp[i]>='A' && tmp[i]<='Z')
                {
                    tmp[i]=tmp[i]+32;
                    word=word+tmp[i];
                }
                else if(tmp[i]>='a' && tmp[i]<='z')
                {
                    word=word+tmp[i];
                }
            }
            for(const auto& data : s_id_map[word]) //遍歷s_id_map中string對應的所有id
            {
                id_idfsum_map[data]+=log10((double)strnum/(double)s_id_map[word].size());
            }
        }

        for(const auto& data : id_idfsum_map)
        {
            Ans tmp;
            tmp.sid = data.first;
            tmp.idf_sum = data.second;
            ans.push_back(tmp);
        }

        sort(ans.begin(),ans.end(),compare);

        for(int i=0;i<k;i++)
        {
            if(i<=((int)ans.size()-1)&&(ans[i].idf_sum!=0)) //ans.size()是unsigned int
            {
                cout << ans[i].sid;
            }
            else
            {
                cout << "-1";
            }
            if(i!=k-1){
                cout<<" ";
            }
        }
        cout << endl;
    }
    
    return 0;
}
