#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <queue>
#include <stack>
#include <cstring>
using namespace std;

struct node
{
    int endV;
    int w;
    node *list;
    node(int a,int wt)
    {
        endV=a;
        w=wt;
        list=NULL;
    }
};

vector<int> visited(1000001,0);
vector<int> order(1000001,0);
vector<node*>root(1000001,NULL);
vector<node*>buff(1000001,NULL);

void dfs(int start)
{
    if(visited[start]==1)   return;

    visited[start]=1;
    node *temp=root[start];

    while(temp!=NULL)
    {
        if(visited[temp->endV])
        {
            temp=temp->list;
        }
        else
        {
            order[temp->endV]=order[start]+temp->w;
            dfs(temp->endV);
            temp=temp->list;
        }
    }
}

int main()
{
    char str[1000000];
    char* token;
    int x,y,z;
    int edg1,edg2,w;
    ifstream fp;
    ofstream of;
    string filename;
    cout << "please enter filename : ";
    cin >> filename;
    fp.open(filename.c_str());
    filename.erase(0,2);
    filename="out"+filename;
    of.open(filename.c_str());
    fp.getline(str,100);
    x=atoi(str);

    //create adjacency list
    for(int i=0;i<x-1;i++)
    {
        fp.getline(str,1000000);
        token=strtok(str," ");
        edg1=atoi(token);
        token=strtok(NULL," ");
        edg2=atoi(token);
        token=strtok(NULL," ");
        w=atoi(token);
        
        //both root of edg1 and edg2 have to be initialized
        if(root[edg1]==NULL)
        {
            root[edg1]=new node(edg2,w);
            buff[edg1]=root[edg1];
        }
        else
        {
            buff[edg1]->list=new node(edg2,w);
            buff[edg1]=buff[edg1]->list;
        }

        if(root[edg2]==NULL)
        {
            root[edg2]=new node(edg1,w);
            buff[edg2]=root[edg2];
        }
        else
        {
            buff[edg2]->list=new node(edg1,w);
            buff[edg2]=buff[edg2]->list;
        }
    }

    fp.getline(str,1000000);
    z=atoi(str);        //z=starting vertix
    
    dfs(z);

    for(int i=1;i<x+1;i++)
    {
        cout<<i<<" "<<order[i]<<endl;
        of<<i<<" "<<order[i]<<endl;
    }

    fp.close();
    of.close();

}