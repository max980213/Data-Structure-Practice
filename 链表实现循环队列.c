#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef struct CLNode
{
	int data;
	struct CLNode* next;
}CLNode;

CLNode* Initialize();
void Print();
int EmptyCheck();
void Insert();
void Delete();

int main()//此为设立头节点的循环链表
{
	CLNode* front = Initialize();
}

CLNode* Initialize()
{
	CLNode* front = (CLNode*)malloc(sizeof(CLNode));
	while (!front)
	{
		printf("初始化失败！\n\n");
		front = (CLNode*)malloc(sizeof(CLNode));
	}
	front->data = 0;
	front->next = front;//因为是循环队列，所以重新指向自身
	printf("初始化成功！\n\n");
	return(front);
}

void Print(CLNode* front)
{
	while (front->next != front)
	{
		printf("  %d  ", front->data);
		front = front->next;
	}
	printf("%d\n", front->data);//因为遍历到最后一个节点便跳出了循环，所以再加一句输出
}

int EmptyCheck(CLNode* front)
{

}