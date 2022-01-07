#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <queue>
#include <stack>
#include <cstring>
using namespace std;

int main()
{
    char str[1000];
    char* token;
    int x,y,z;
    int temp;
    ifstream fp;
    ofstream of;
    string filename;
    cout << "please enter filename : ";
    cin >> filename;
    fp.open(filename.c_str());
    filename.erase(0,2);
    filename="out"+filename;
    of.open(filename.c_str());
    //fp>>x;
    //cout<<x<<endl;
    fp.getline(str,1000);
    x=atoi(str);
    //cout<<x<<endl;
    for(int i=0;i<x;i++)
    {
        int m[100][100]={0};        //adjacency matrix
        int isvisted[100]={0};  
        vector<int>order;
        fp.getline(str,1000);
        token=strtok(str," ");
        y=atoi(token);           //y= # of V
        token=strtok(NULL," ");
        z=atoi(token);           //z= starting V

        //create adjacency matrix
        for(int j=0;j<y;j++)
        {
            fp.getline(str,1000);
            token=strtok(str," ");
            for(int k=0;k<y;k++)
            {
                m[j][k]=atoi(token);
                token=strtok(NULL," ");
                //cout<<m[j][k]<<" ";
            }
        }

        //dfs
        isvisted[z]=1;
        stack<int>q;
        q.push(z);
        order.push_back(z);
        while(!q.empty())
        {
            temp=q.top();
            q.pop();
            for(int j=0;j<y;j++)
            {
                if(m[temp][j]==1 && isvisted[j]==0)
                {
                    isvisted[j]=1;
                    q.push(temp);
                    q.push(j);
                    order.push_back(j);
                    break;
                }
            }
            
        }

        //print order
        for(int j=0;j<order.size();j++)
        {
              cout<<order[j]<<" ";
              of<<order[j]<<" ";
        }
        cout<<endl;
        of<<endl;


    }
    fp.close();
    of.close();
}