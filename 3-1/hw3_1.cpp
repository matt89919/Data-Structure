#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <fstream>
#include <queue>
#include <stack>
#include <cstring>
using namespace std;



class node
{
public:

    int data;
    node *left;
    node *right;

    node(int a)
    {
        data=a;
        left=NULL;
        right=NULL;
    };
    int getdata(){  return data;}
};

int index;
node* getpost(int inorder[],int preorder[],int start,int end)
{
    if(start>end)   return NULL;

    int p=preorder[index];
    index++;
    //root node's order=preorder
    node* temp=new node(p);

    //distinguish left and right subtree
    int i=0;
    for(i=start;i<=end;i++)
        if(inorder[i]==temp->getdata())
            break;

    //left subtree
    temp->left=getpost(inorder,preorder,start,i-1);
    //right subtree
    temp->right=getpost(inorder,preorder,i+1,end);
    return temp;
}

node* getpre(int inorder[],int post[],int start,int end)
{
    if(start>end)   return NULL;

    int p=post[index];
    index--;
    //root node's order=preorder
    node* temp=new node(p);

    //distinguish left and right subtree
    int i=0;
    for(i=start;i<=end;i++)
        if(inorder[i]==temp->getdata())
            break;

    //right subtree
    temp->right=getpre(inorder,post,i+1,end);
    //left subtree
    temp->left=getpre(inorder,post,start,i-1);
    return temp;
}

void postorderT(node *node)
{
    if(node==NULL)  return;
    postorderT(node->left);
    postorderT(node->right);
    cout<<node->getdata()<<" ";
}

void preorderT(node *node)
{
    if(node==NULL)  return;
    cout<<node->getdata()<<" ";
    preorderT(node->left);
    preorderT(node->right);
}

int main()
{
    
    char str[2000];
    char* token;
    int preorder[1000]={0};
    int postorder[1000]={0};
    int inorder[1000]={0};
    int x,y,n;
    ifstream fp;
    string filename;
    cout << "pleas enter filename : ";
    cin >> filename;
    fp.open(filename.c_str());

    //readfile
    fp.getline(str,100);
    x=atoi(str);

    for(int i=0;i<x;i++)
    {
        index=0;
        //first line
        fp.getline(str,1000);
        if(str[1]=='r') y=1;
        else y=2;
        //cout<<y<<endl;

        //second line
        fp.getline(str,1000);
        n=atoi(str);
        //cout<<n<<endl;

        //third line
        fp.getline(str,1000);
        token=strtok(str," ");
        for(int k=0;k<n;k++)
        {
            if(y==1)  preorder[k]=atoi(token);     //pre-in
            else postorder[k]=atoi(token);         //post-in
            //cout<<preorder[k]<<" ";
            token=strtok(NULL," ");
        }
        //cout<<endl;
        //fourth line
        fp.getline(str,1000);
        token=strtok(str," ");
        for(int k=0;k<n;k++)
        {
            inorder[k]=atoi(token);
            //cout<<inorder[k]<<" ";
            token=strtok(NULL," ");
        }
        //cout<<endl;
        if(y==1)
        {
            index=0;
            node* root=getpost(inorder,preorder,0,n-1);
            postorderT(root);
        }
        if(y==2)
        {
            index=n-1;
            node *root=getpre(inorder,postorder,0,n-1);
            preorderT(root);
        }   
        cout<<endl; 
        
            
    }
    




    /*
    int inorder[] = { 4, 2, 1, 7, 5, 8, 3, 6 };
    int preorder[] = { 1, 2, 4, 3, 5, 7, 8, 6 };
    int post[] = {4,2,7,8,5,6,3,1};
    int n = sizeof(inorder)/sizeof(inorder[0]);
 
    index=0;
    node* root = getpost(inorder, preorder, 0,n-1);
    index=n-1;
    node* x=getpre(inorder,post,0,n-1);
    postorder(root);
    cout<<endl;
    preorderT(x);
 
    return 0;
    */

}