#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef struct Node
{
	int data;
	struct Node* next;
}Node;

typedef struct LinkQueue
{
	struct Node* front, * rear;
	int amount;//用来统计队列元素的数量
}LinkQueue;

LinkQueue* Initialize();
void Print();
int EmptyCheck();
void Insert();
void Delete();

int main()//此为不设立头节点的循环链表，但好像有头节点更方便一些
{
	LinkQueue* head = Initialize();
	int in, input;
	while (1)
	{
		printf("请输入想要进行的操作！-1为退出！\n\n");
		printf("0.打印队列\n");
		printf("1.插入元素\n");
		printf("2.删除元素\n");
		printf("-1.退出\n");
		if (in = scanf_s("%d", &input) != 1)
		{
			printf("输入有误！请重新输入！\n\n");//有时候我会按成一个字母输进去
		}
		switch (input)
		{
		case 0:
		{
			Print(head);
			break;
		}
		case 1:
		{
			Insert(head);
			break;
		}
		case 2:
		{
			Delete(head);
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

LinkQueue* Initialize()
{
	LinkQueue* head = (LinkQueue*)malloc(sizeof(LinkQueue));
	if (head)
	{
		head->front = head->rear = NULL;
		head->amount = 0;
		printf("初始化成功！\n\n");
	}
	else
	{
		printf("初始化失败！\n\n");
		exit(0);
	}
	return(head);
}

void Print(LinkQueue* head)
{
	Node* p = head->front;
	while (p != NULL)//遍历了所有元素，不需要再加打印最后一个节点的数据
	{
		printf("  %d  ", p->data);
		p = p->next;
	}
	printf("一共有  %d  个元素！\n\n", head->amount);
}

int EmptyCheck(LinkQueue* head)
{
	if (head->rear == NULL && head->amount == 0)//判断对amount和两个指针的操作是否有误
	{
		printf("队列为空！\n\n");
		return 0;
	}
	else
		return 1;
}

void Insert(LinkQueue* head)
{
	Node* p = (Node*)malloc(sizeof(Node));
	if (p)
	{
		int input;
		printf("请输入想要插入的数据！\n");
		scanf_s("%d", &input);
		p->data = input;
		p->next = NULL;
		if (head->rear == NULL)//因为没有头节点，初始时front、rear都指向null,所以有头节点似乎更方便，添加操作rear->next;删除操作front->next,front和rear都指向头节点
		{
			head->front = head->rear = p;//第一个节点不需钩链
		}
		else
		{
			head->rear->next = p;//钩链
			head->rear = p;//尾指针后移
		}
		head->amount++;
		printf("插入成功！\n\n");
	}
	else
		printf("插入失败！\n\n");
}

void Delete(LinkQueue* head)
{
	if (EmptyCheck(head))
	{
		printf("我们得到了元素：  %d  ！\n", head->front->data);
		Node* q = head->front;//取第一个元素节点给q
		if (head->front == head->rear)//in case队列中只剩一个元素了，free掉后rear指针将变成野指针
		{
			head->front = head->rear = NULL;//列表空了，重新指向空
		}
		else
			head->front = q->next;
		free(q);
		head->amount--;
		printf("删除成功！\n\n");
	}
}