#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    char data;
    node *lchild;
    node *rchild;
}node;

node* create(node *root)  //先序遍历建树，也可把读入的数据存如数组中
{
    char data=getchar();
    //getchar(); //读掉回车   //c++好像不用读掉回车
    if(data=='#')
    {
        root=NULL;
        return root;
    }
    root=new node;
    root->data=data;
    root->lchild=create(root->lchild);
    root->rchild=create(root->rchild);
    return root;
}

void printtree(node* root)
{
    if(root==NULL)
        return;
    printtree(root->lchild);
    printf("%c ",root->data);
    printtree(root->rchild);
}

int main()
{
    node* root=create(root);
    printtree(root);
    return 0;
}
