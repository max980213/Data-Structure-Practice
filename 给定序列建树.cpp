/*题目描述：给定仅由0、1、2组成的序列S，构建一棵树
0表示无子节点，1S1表示有一个子节点，S1为其子树的二叉树序列，2S1S2表示有两个子节点，S1S2为其两个子树的序列
*/

#include <stdio.h>
#include <stack>

using namespace std;

typedef struct node
{
    ndoe* lchild,rchild;
}node;

node* create(int S[],int n)
{
    if(n==0||S[0]==0)
        return NULL; //空树
    node* root=new node;
    stack <node> st;
    st.push(root);  //根结点入栈
    for(int i=0;i<n;i++)
    {
        node* temp=st.top();
        st.pop();
        if(s[i]==2)
        {
            temp->lchild=new node;
            temp->rchild=new node;
            st.push(temp->rchild);
            st.push(temp->lchild);  //一定先入右
        }
        else if(s[i]==1)
        {
            temp->lchild=new node;
            st.push(temp->lchild);
        }
        else
            continue;
    }
    return root; //返回根结结点
}

int main()
{
    int n;
    scanf("%d",&n);
    int S[n};
    for(int i=0;i<n;i++)
        scanf("%d",&S[i]);
    create(S,n);
    return 0;
}
    
