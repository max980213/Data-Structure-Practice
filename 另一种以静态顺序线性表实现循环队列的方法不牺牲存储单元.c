#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define MAX_SIZE 10

typedef struct Suqueue
{
	int data[MAX_SIZE];
	int front;
	int rear;
	int count;//记录数据的数量
}Suqueue;

Suqueue Initialize();
void Print();
int EmptyCheck();//检查队列是否为空
int FilledCheck();//检查队列是否满
void Insert();
void Delete();

int main()
{
	Suqueue S = Initialize();
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
			Print(S);
			break;
		}
		case 1:
		{
			Insert(&S);
			break;
		}
		case 2:
		{
			Delete(&S);
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

Suqueue Initialize()//另一种初始化方式是定义结构体指针，通过malloc(sizeof(Suqueue))分配并对两个变量赋值
{
	Suqueue S;
	S.count = 0;
	S.front = 0;
	S.rear = 0;
	printf("初始化成功！\n\n");
	return(S);
}

void Print(Suqueue S)
{
	int i = 0;
	while (i != S.count)//使用count变量是想要判断下面函数的count变量是否发挥作用，从0开始到count-1，循环了count次，最后一次跳出
	{
		printf("  %d  ", S.data[S.front]);
		i++;
		S.front = (S.front + 1) % MAX_SIZE;
	}
}

int EmptyCheck(Suqueue S)
{
	if (S.count == 0)
	{
		printf("队列已为空！\n\n");
		return 0;
	}
	else
		return 1;
}

int FilledCheck(Suqueue S)
{
	if (S.count == MAX_SIZE)
	{
		printf("队列已满！\n\n");
		return 0;
	}
	else
		return 1;
}

void Insert(Suqueue* S)//先对指针指向的单元操作，然后再移动指针。若先动指针，应从-1开始
{
	if (FilledCheck(*S))
	{
		int input;
		printf("请输入想要插入的数据项！\n");
		scanf_s("%d", &input);
		S->data[S->rear] = input;//对rear指针指向的单元赋值                     若没有再结构体中定义rear变量
		S->rear = (S->rear + 1) % MAX_SIZE;//取模实现循环队列					则每次进行插入操作时都需要找到插入的位置
		S->count++;															  //具体算法为：int rear=(S->front+S->count)%MAX_SIZE
		printf("插入成功！\n\n");											  //因为这里是先对数据操作再对指针操作，所以这时得到的rear即为要插入的位置，不需要加1
	}																		  //也就是说，front指针总是指向有元素的单元
}

void Delete(Suqueue* S)
{
	if (EmptyCheck(*S))
	{
		printf("我们得到了数据  %d  ！删除成功！\n", S->data[S->front]);
		S->front = (S->front + 1) % MAX_SIZE;
		S->count--;
	}
}