//约瑟夫环问题描述：n人围成一个圆，首先从第1个人从1开始报数，报到第m个人淘汰，然后从下一个人再从1开始报数，以此类推，直到只剩下最后一个人
//解决方案：使用不带头尾节点的循环链表

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef struct LNode
{
	int data;
	struct LNode* next;
}LNode;

LNode* Create_Linklist(LNode* head);//初始化链表的同时插入数据
void Print_Linklist(LNode* head);
void Method1(LNode* head);//方法1实现约瑟夫环求解。即while遍历表，设置变量自加通过if语句判断是否为所在点
void Method2(LNode* head);//通过双循环实现，外层循环为n-1次（只留下最后一个），内层循环为m次（循环m次直接到所在点）

int main()
{
	LNode* head = NULL;
	head = Create_Linklist(head);
	Print_Linklist(head);
}

LNode* Create_Linklist(LNode* head)
{
	int input, j;
	printf("请输入你想插入的数据！-99退出！\n");
	j = scanf_s("%d", &input);
	while (input != -99)
	{
		if (j != 1)
		{
			printf("输入有误！请重新输入！\n");
			getchar();
		}
		else
		{
			if (head==NULL)
			{
				head = (LNode*)malloc(sizeof(LNode));
				if (head)
				{
					head->data = input;
					head->next = head;
				}
			}
			else
			{
				LNode* ptr = (LNode*)malloc(sizeof(LNode));
				if (ptr)
				{
					ptr->data = input;
					head->next = ptr;
					ptr->next = head;
				}
			}
		}
		j = scanf_s("%d", &input);
	}
	return(head);
}

void Print_Linklist(LNode* head)
{
	if (head)
	{
		LNode* ptr = head;
		while (ptr->next != head)
		{
			printf(" %d  ", ptr->data);
			ptr = ptr->next;
		}
		printf("%d  ", ptr->data);//因为在最后一个节点跳出了循环，所以再加一句
	}
}