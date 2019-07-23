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
LNode* Method1(LNode* head);//方法1实现约瑟夫环求解。即while遍历表，设置变量自加通过if语句判断是否为所在点
LNode* Method2(LNode* head);//通过双循环实现，外层循环为n-1次（只留下最后一个），内层循环为m次（循环m次直接到所在点）

//双循环暂时还没想出如何最快得到循环链表的长度（其实就是我懒了）这个以后什么时候不懒了更新，顺便优化代码

//代码功能：重复输入，一次初始化便只需插入，可重复插入
//虽然用不上这些功能，子函数功能在主函数里写一次就够了

int main()
{
	LNode* head = NULL;
	while (1)
	{
		printf("请输入你想要进行的操作！\n");
		printf("0.打印循环链表\n");
		printf("1.初始化并对链表赋值\n");
		printf("2.使用方法1求解约瑟夫环\n");
		printf("3.使用方法2求解约瑟夫环(双循环)\n");
		int input, j;
		if (j = scanf_s("%d", &input) != 1)
		{
			printf("输入操作有误！请重新输入！\n\n");
			getchar();
		}
		switch (input)
		{
		case 0:
		{
			Print_Linklist(head);
			break;
		}
		case 1:
		{
			head = Create_Linklist(head);
			break;
		}
		case 2:
		{
			head = Method1(head);
			break;
		}
		case 3:
		{
		//	Method2(head);
			break;
		}
		}
	}
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
				LNode* q = head;
				while (q->next != head)
				{
					q = q->next; //找到最后一个节点
				}
				if (ptr) //插入最后一个节点，并使最后一个节点的指针域指向第一个节点
				{
					ptr->data = input;
					q->next = ptr;
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

LNode* Method1(LNode* head) //此函数运行结束时的head节点已经不是进来时候的head节点，所以运行后再打印链表时的head已经被free掉了 所以修改为带返回值的函数
{
	printf("请输入循环值！\n");
	int input, j = 1; //第一个节点报的数字为1
	LNode* ptr;
	scanf_s("%d", &input);
	if (head)
	{
		while (head->next != head)
		{
			head = head->next;
			j++;
			if (j == input - 1)
			{
				ptr = head->next;//得到第input个节点
				printf("%d\n", ptr->data);
				head->next = ptr->next;
				free(ptr);//free掉淘汰掉的节点
				j = 0;
			}
		}
		printf("胜利者是：%d ！\n\n", head->data);
	}
	else
	{
		printf("链表为空\n\n");
	}
	return(head);
}

LNode* Method2(LNode* head) //暂时搁浅
{
	printf("请输入循环值！\n");
	int input, j;
	LNode* ptr;
	scanf_s("%d", &input);
	if (head)
	{
		
	}

}