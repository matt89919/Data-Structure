#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <queue>
#include <stack>
#include <cstring>
using namespace std;


struct weight
{   
    int edg1;
    int edg2;
    int w;
    weight(int a,int b,int c)
    {
        edg1=a;
        edg2=b;
        w=c;
    }
};

int unitable[1000000];
int size[1000000];

int root(int a)
{
    while(unitable[a]!=-1)
        a=unitable[a];
    //cout<<endl<<"a "<<a<<endl;
    return a;
}

void uni(int a,int b)
{
    int i=root(a);
    int j=root(b);
    if(i==j) return;
    if(size[i]>size[j]){
        size[i]+=size[j];
        unitable[j]=i;
    }else{
        size[j]+=size[i];
        unitable[i]=j;
    }
}

bool find(int a,int b)
{
    int i=root(a);
    int j=root(b);
    if(i==j) return true;
    return false;
}

bool sortweight(vector<weight>& v) 
{
    for(int i=0;i<v.size()-1;i++)
    {
        for(int j=0;j<v.size()-i-1;j++)
        {
            if(v[j].w > v[j+1].w)
            {
                swap(v[j],v[j+1]);
            }
        }
    }
}

int main()
{
    for(int i=0;i<1000002;i++)
    {
        unitable[i]=-1;
        size[i]=1;
    }
    char str[1000];
    char* token;
    int x,y,z;
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
    fp.getline(str,100);
    token=strtok(str," ");
    x=atoi(token);              //x=# of vertice
    token=strtok(NULL," ");
    y=atoi(token);              //y=# of edge

    vector<weight> w;
    weight *temp;
    int edg1,edg2,wt;


    //create edge weight table
    for(int i=0;i<y;i++)
    {
        fp.getline(str,100);
        token=strtok(str," ");
        edg1=atoi(token);
        token=strtok(NULL," ");
        edg2=atoi(token);
        token=strtok(NULL," ");
        wt=atoi(token);
        temp=new weight(edg1,edg2,wt);
        w.push_back(*temp);
        free(temp);
    }

    sortweight(w);      //sort w by increasing order
    

    int index=0;
    int sum=0;
    temp=new weight(-1,-1,-1);
    
    //cout<<"1";
    for(int i=0;i<x-1;i++)
    {
        while(1)
        {
            //cout<<"3"<<endl;
            *temp=w[index];
            //cout<<temp->edg1<<" "<<temp->edg2;
            if(!find(temp->edg1,temp->edg2))
            {
                //cout<<"4"<<endl;
                uni(temp->edg1,temp->edg2);
                sum+=temp->w;
                //cout<<temp->edg1<<" "<<temp->edg2<<endl;
                index++;
                break;
            }
            else index++;
        }

    }

    cout<<sum;
    of<<sum;
    fp.close();
    of.close();
/*
    temp=new weight(1,5,10);
    w.push_back(*temp);
    free(temp);
    temp=new weight(2,8,0);
    w.push_back(*temp);
    cout<<w[0].edg1<<w[0].edg2<<w[0].w<<" "<<w[1].edg1<<w[1].edg2<<w[1].w;
    */
}