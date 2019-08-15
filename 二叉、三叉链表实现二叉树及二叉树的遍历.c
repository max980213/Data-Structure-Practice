#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define MAX_NODE 50

//二叉链表实现

typedef struct BTNode
{
	char data;
	struct BTNode* Lchild, * Rchild;
}BTNode;

BTNode* Create1(BTNode* root);//先序遍历创建树
BTNode* Create2();//按满二叉树创建树
void Depth_Print(BTNode* root);//层次遍历二叉树
void Preorder_Print_Recursion(BTNode* root);//先序遍历二叉树（递归）
void Preorder_Print(BTNode* root);//先序遍历二叉树（非递归）
void Preorder_Print2(BTNode* root);//先序遍历二叉树的第二种非递归方法
void Preorder_Print3(BTNode* root);//先序遍历二叉树的第三种非递归方法
void Inorder_Print_Recursion(BTNode* root);//中序遍历（递归）
void Inorder_Print(BTNode* root);//中序遍历二叉树（非递归）
void Postorder_Print_Recursion(BTNode* root);//后序遍历（递归）
void Postorder_Print(BTNode* root);//后序遍历（非递归）

int main()
{
	BTNode* root = NULL;
	int in, input;
	while (1)
	{
		printf("请输入想要进行的操作！-1为退出！\n\n");
		printf("1.先序遍历创建树 并：\n");
		printf("2.按满二叉树创建树 并：\n\n");
		printf("层次遍历二叉树\n");
		printf("先序遍历二叉树（递归）\n");
		printf("先序遍历二叉树（非递归1）\n");
		printf("先序遍历二叉树（非递归2）\n");
		printf("先序遍历二叉树（非递归3）\n");
		printf("-1.退出\n");
		if (in = scanf_s("%d", &input) != 1)
		{
			printf("输入有误！请重新输入！\n\n");//有时候我会按成一个字母输进去
		}
		rewind(stdin);//冲掉缓冲区中的回车
		switch (input)
		{
		case 1:
		{
			root = Create1(root);
			Depth_Print(root);
			printf("先序遍历（递归）：   ");
			Preorder_Print_Recursion(root);
			putchar('\n');
			Preorder_Print(root);
			Preorder_Print2(root);
			Preorder_Print3(root);
			printf("中序遍历（递归）：   ");
			Inorder_Print_Recursion(root);
			putchar('\n');
			Inorder_Print(root);
			printf("后序遍历（递归）：   ");
			Postorder_Print_Recursion(root);
			putchar('\n');
			break;
		}
		case 2:
		{
			root = Create2(root);
			Depth_Print(root);
			printf("先序遍历（递归）：   ");
			Preorder_Print_Recursion(root);
			putchar('\n');
			Preorder_Print(root);
			Preorder_Print2(root);
			Preorder_Print3(root);
			printf("中序遍历（递归）：   ");
			Inorder_Print_Recursion(root);
			putchar('\n');
			Inorder_Print(root);
			printf("后续遍历（递归）：   ");
			Postorder_Print_Recursion(root);
			putchar('\n');
			break;
		}

		case -1:
			exit(1);
		default:
		{
			printf("请输入正确序号！\n\n");
			break;
		}
		}
	}
}

BTNode* Create1(BTNode* root)
{
	char ch = getchar();
	//rewind(stdin); //冲掉缓冲区，因为编译器的原因fflush()不再起作用
	
	getchar();   //两个getchar()为了读掉回车，如果在一行里把数据全部输入则不需要两个getchar()

	if (ch == '#')
	{
		root = NULL;
		return (root);
	}

	else
	{ 
		root = (BTNode*)malloc(sizeof(BTNode));
		if (!root)
			exit(-1);
		root->data = ch;
		root->Lchild = Create1(root->Lchild);
		root->Rchild = Create1(root->Rchild);
		return (root);
	}
}//Create1 先序 递归

BTNode* Create2()//返回根
{
	BTNode* root = NULL, * p, * s[MAX_NODE] = { NULL };//利用指针数组，编号为i的指针存放于s[i]中
	char ch; int i, j;
	while (1)
	{
		scanf_s("%d", &i);//输入插入的位置序号，从上到下，从左至右从1开始一次累加
		//getchar();
		if (i == 0)
			break;//0作为结束标志
		else
		{
			ch = getchar();//也许是因为两次输入不连续，所以不需要读掉回车
			p = (BTNode*)malloc(sizeof(BTNode));
			if (!p)
				exit(-1);
			else
			{
				p->data = ch;
				p->Lchild = p->Rchild = NULL;
				s[i] = p;//将该节点存入数组中的相应位置处
				if (i == 1)
					root = p;
				else
				{
					j = i / 2;//得到父节点
					if (s[j] != NULL)
					{
						if (i % 2 == 0)//不是0就是1，0是左孩子，1是右孩子
							s[j]->Lchild = p;
						else
							s[j]->Rchild = p;
					}
					else //得判断一下父节点存不存在
					{
						printf("该节点的父节点不存在！\n\n");
						free(s[i]);//因为这个节点已经再数组里，但这个节点没什么用。所以把他free掉
						s[i] = NULL;//防止断树，之前此节点已经存入数组，但是这个节点没有跟树相连，为断树
						//break;
					}
					
				}
			}
		}
	}
	return(root);
}//Create2

void Depth_Print(BTNode* root)
{
	BTNode* Queue[MAX_NODE] = { NULL }, * p = root;
	int front = 0, rear = 0;
	printf("层次遍历：           ");
	if (p != NULL)
	{
		Queue[++rear] = p;//根入队
		while (front < rear)
		{
			p = Queue[++front];
			printf("  %c  ", p->data);//访问数据域
			if (p->Lchild != NULL)
				Queue[++rear] = p->Lchild;
			if (p->Rchild != NULL)
				Queue[++rear] = p->Rchild;
		}
	}
	printf("\n");
}//Depth_Print

void Preorder_Print_Recursion(BTNode* root)
{
	if (root != NULL)
	{
		printf("  %c  ", root->data);
		Preorder_Print_Recursion(root->Lchild);
		Preorder_Print_Recursion(root->Rchild);
	}
}//Preorder_Print_Recursion

void Preorder_Print(BTNode* root)//利用栈保存节点
{
	BTNode* Stack[MAX_NODE] = { NULL }, * p = root, * q;
	int top = 0;
	if (root == NULL)
		printf("树为空！\n\n");
	else
	{
		printf("先序遍历（非递归1）：");
		do
		{
			printf("  %c  ", p->data);//先访根
			q = p->Rchild;
			if (q != NULL)
				Stack[++top] = q;//把右子树的根存至栈中
			p = p->Lchild;//遍历左子树
			if (p == NULL)//左子树为空了，出栈一次访问最近一个子树的根的右节点
				p = Stack[top--];
		} while (top > 0 || p != NULL);
	}
	printf("\n");
}

void Preorder_Print2(BTNode* root)
{
	BTNode* Stack[MAX_NODE] = { NULL }, * p;
	int top = 0;
	if (root == NULL)
		printf("树为空！\n\n");
	else
	{
		printf("先序遍历（非递归2）：");
		Stack[top] = root;//根先入栈
		while (top > -1)//栈不为空时循环
		{
			p = Stack[top--];
			printf("  %c  ", p->data);
			if (p->Rchild != NULL)  //栈为后进先出，所以左孩子后进就会先访问，然后下一次循环又会把该左孩子的右左孩子入栈
				Stack[++top] = p->Rchild;
			if (p->Lchild != NULL)
				Stack[++top] = p->Lchild;
		}
	}
	putchar('\n');
}

void Preorder_Print3(BTNode* root)
{
	BTNode* Stack[MAX_NODE] = { NULL }, * p;
	int top = 0;
	if (root == NULL)
		printf("树为空！\n\n");
	else
	{
		printf("先序遍历（非递归3）：");
		p = root;
		while (top > 0 || p != NULL)
		{
			while (p != NULL)  //扫描所有子节点并进栈
			{
				printf("  %c  ", p->data);
				Stack[top++] = p;
				p = p->Lchild;
			}
			if (top > 0)  //栈非空，取最近子树的右孩子
			{
				p = Stack[--top];
				p = p->Rchild;
			}
		}
	}
	putchar('\n');
}

void Inorder_Print_Recursion(BTNode* root)
{
	if (root != NULL)
	{
		Inorder_Print_Recursion(root->Lchild);
		printf("  %c  ", root->data);
		Inorder_Print_Recursion(root->Rchild);
	}
}

void Inorder_Print(BTNode* root)
{
	BTNode* Stack[MAX_NODE] = { NULL }, * p = root;
	int top = 0;
	if (root == NULL)
		printf("树为空！\n\n");
	else
	{
		printf("中序遍历（非递归1）：");
		do
		{
			while (p != NULL)//循环寻找左子树到尽头并依次入栈
			{
				Stack[top++] = p;
				p = p->Lchild;
			}//跳出循环时p已经为空
			p = Stack[--top];//退栈一个节点便访问并向右走，然后再尝试寻找该节点左子树的尽头
			printf("  %c  ", p->data);//访问，因为（遍历到头就是叶子节点）左为空，便访问该叶，然后尝试往右走，但依然为空，然后再退栈，返回到该页的父节点并尝试想右走
			p = p->Rchild;
		} while (top > 0 || p != NULL);
	}
	printf("\n");
}

void Postorder_Print_Recursion(BTNode* root)
{
	if (root != NULL)
	{
		Postorder_Print_Recursion(root->Lchild);
		Postorder_Print_Recursion(root->Rchild);
		printf("  %c  ", root->data);
	}
}
