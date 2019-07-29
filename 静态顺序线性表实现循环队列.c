//队列也时一种特殊的线性表，与栈不同，队列是在一端插入，另一端删除。
//这里采取先对元素操作，再增加指针，故rear（插入端）指针总是指向空（这里尾端插入，头端删除）
//此队列为循环队列
//牺牲了一个存储单元

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 10

typedef struct SeQueue
{
	int Queue_array[MAX_SIZE];
	int front;
	int rear;
}SeQueue;

SeQueue Initialize();
void Print(SeQueue S);
void Insert(SeQueue* S);
void Delete(SeQueue* S);
int FilledCheck(SeQueue S);
int EmptyCheck(SeQueue S);



int main()
{
	int input, in;
	SeQueue S = Initialize();//函数开始执行时直接初始化
	while (1)
	{
		printf("请输入你想要进行的操作序号！\n\n");
		printf("0.打印循环队列\n");
		printf("1.初始化队列\n");
		printf("2.插入数据\n");
		printf("3.删除元素\n");
		printf("-1.退出本次操作\n");

		if (in = scanf_s("%d", &input) != 1)
		{
			printf("输入不合法！请重新输入！");
			getchar();
		}
		switch (input)
		{
		case 0:
		{
			Print(S);
			break;
		}
		case 1:
		{
			S = Initialize();
			break;
		}
		case 2:
		{
			Insert(&S);
			break;
		}
		case 3:
		{
			Delete(&S);
			break;
		}
		case -1:
			exit(0);
		default:
		{
			printf("输入有误！请重新输入！\n");
			break;
		}
		}
	}
	return 0;
}

SeQueue Initialize()
{
	SeQueue S;
	S.front = 0;
	S.rear = 0;
	printf("初始化成功！\n\n");
	return(S);
}

void Print(SeQueue S) //从头指针输出到尾指针，其中尾指针指向一个空
{
	while (S.front != S.rear)
	{
		printf("  %d  ", S.Queue_array[S.front]);
		S.front = (S.front + 1) % MAX_SIZE;
	}
}
/* 这是一段不能实现功能的代码，因为结构体传入后再子函数内为临时变量，子函数结束后就释放了
void Insert(SeQueue S)
{
	if (FilledCheck(S))
	{
		int e;
		printf("请输入你想插入的数据！\n");
		scanf_s("%d", &e);
		S.Queue_array[S.rear] = e;
		S.rear = (S.rear + 1) % MAX_SIZE;//因为是循环队列，这里数组有10个存储单元（总会空一个），所以指到9再+1应该是0，故采用取余
		/*  取模运算代替了if结构
		if(S.rear+1 == Max_SIZE)
			i=0;
		else
			i++;
		
		printf("  %d \n", S.Queue_array[S.rear]);
		printf("插入成功！\n\n");
	}
}
*/
void Insert(SeQueue* S)
{
	if (FilledCheck(*S))
	{
		int e;
		printf("请输入想要插入的数据！\n");
		scanf_s("%d", &e);
		S->Queue_array[S->rear] = e;
		S->rear = (S->rear + 1) % MAX_SIZE;
		printf("插入成功！\n\n");
	}
}

void Delete(SeQueue* S)//删除无需判断是否队满，这里front是指向有元素的单位，应该判断队空
{
	if (EmptyCheck(*S))
	{
		S->front = (S->front + 1) % MAX_SIZE;
		printf("删除成功！\n\n");
	}
}

int FilledCheck(SeQueue S)
{
	if ((S.rear + 1) % MAX_SIZE == S.front)
	{
		printf("队列已满！不可插入！\n\n");
		return 0;
	}
	else
		return 1;
}

int EmptyCheck(SeQueue S)
{
	if (S.front == S.rear)
	{
		printf("队列已为空！\n\n");
		return 0;
	}
	else
		return 1;
}