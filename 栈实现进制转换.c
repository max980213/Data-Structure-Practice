//利用链栈实现实数进制的转换
//做的很简陋，没有字符检测，人机交互不是很好
//另外，如果时转十六进制，10~15还没有增加输出字母的功能，如255会输出1515
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef struct SLNode
{
	int data;
	struct SLNode* next;
}SLNode;

SLNode* Initialize();
void push(SLNode* top , int e);
void pop(SLNode* top);
void transverse();

int main()
{
	transverse();
	return 0;
}

SLNode* Initialize()
{
	SLNode* top = (SLNode*)malloc(sizeof(SLNode));
	if (top)
	{
		top->data = 0;//这个地方也许可以用来存栈的长度，就是元素个数
		top->next = NULL;
		printf("初始化成功！\n\n");
		return (top);
	}
	else
	{
		printf("初始化失败！\n\n");
		return (NULL);
	}
}

void push(SLNode* top, int e)
{
	SLNode* p = (SLNode*)malloc(sizeof(SLNode));
	if (p)
	{
		p->data = e;
		p->next = top->next;
		top->next = p;//只在表头进行操作
		top->data++;
		//printf("插入成功！\n\n");
	}
	else
	{
		printf("插入失败！\n\n");
	}
}

void pop(SLNode* top)
{
	if (top->next == NULL)//栈空
		//printf("栈为空！\n\n");
		return;
	else
	{
		SLNode* p = top->next;
		printf("%d", p->data);
		top->next = p->next;
		free(p);
		top->data--;
		//printf("出栈成功！\n\n");
	}
}

void transverse()//你为转换的数字，d为转换的进制
{
	int n, d, j;
	SLNode* top = Initialize();
	printf("请输入转换的数字！均输入0为结束！\n\n");
	scanf_s("%d", &n);
	printf("请输入需要转换的进制！均输入0为结束！\n\n");
	scanf_s("%d", &d);
	while (n != 0 && d != 0)
	{
		while (n > 0)
		{
			int j = n % d;
			push(top, j);
			n = n / d;
		}
		while (top->next != NULL)
		{
			pop(top);
		}
		printf("\n\n请继续输入！均输入0为结束！\n");
		scanf_s("%d", &n);
		printf("请输入需要转换的进制！均输入0为结束！\n\n");
		scanf_s("%d", &d);
	}
}






