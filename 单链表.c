//写在开头：此程序的头节点在主函数中设置并非设置为全局变量。一定要区分出形参与实参的传递关系。如创建头节点函数中的head为形参，实参按值传递进来之后便为形参再操作，函数运行完毕后就会释放形参。
//所以需要一个返回值。
//笔记中的两个函数对比，指针形参的操作为*p与*q之间的互换。这里的create函数中是对指针值进行直接操作，malloc函数申请的内存函数结束后不会释放，但申请到的head指针依然是形参，且实变量在主函数中，所以需要返回给实参。
//也可以理解为，插入函数中，只需把各结点指针链接起来即可，但是生成头节点需要返回一个确切的指针来指向头节点。
//或者，在插入函数中，是对形参head指针指向的内存单元进行操作，并不是对head指针本身进行操作。但在初始化头节点中，还是需要一个确切的指针值返回给实参，所以用一个返回值


#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef int ElemType;
typedef struct LNode
{
	ElemType data;
	struct LNode* next;
}LNode;

LNode* Create_Linklist(LNode* head);//创建头节点
int Initialized_Check(LNode* head);//检测是否已初始化
void Print_Linklist(LNode* head);//打印链表
void Insert();//插入数据
void Head_Insert(LNode* head);//在链表表头插入数据
void Tail_Insert();//在表尾插入数据
void IDNumber_Delete();//按序号值删除节点
void Data_Delete();//按元素值删除节点
void Head_Delete();//头删
void Tail_Delete();//尾删
void Clear_Linklist();//清空
void Destroy_Linklist();//销毁

//LNode* head = NULL;

int main()
{
	int input,in;
	LNode* head = NULL;
	while (1)
	{
		printf("请输入你想要进行的操作序号！\n\n");
		printf("0.打印链表\n");
		printf("1.初始化链表（创建头节点）\n");
		printf("2.插入数据\n");
		printf("3.在链表头部插入元素\n");
		printf("4.在链表尾部插入数据\n");
		printf("5.以序列号删除元素\n");
		printf("6.以元素值删除元素\n");
		printf("7.删除链表的头元素\n");
		printf("8.删除链表的尾元素\n");
		printf("9.查找链表中的元素\n");
		printf("10.清空链表\n"); //保留头节点
		printf("11.销毁链表\n");
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
			Print_Linklist(head);
			break;
		}
		case 1:
		{
			head = Create_Linklist(head);  //如果没有head = ***，那么参数不会传递到main中的*head中
			break;
		}
		case 2:
		{
			break;
		}
		case 3:
		{
			Head_Insert(head);
			break;
		}
		case 4:
		{
			Tail_Insert(head);
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
}

int Initialized_Check(LNode* head)
{
	if (head)  //如果if语句内为指针，则为判断该指针是否非空。若空返回false，非空返回true.若为if(!head),若为空指针则返回true。
		return 1;//ptr指针非空返回1
	else
	{
		printf("链表还未创建！\n");
		return 0;
	}
}

void Print_Linklist(LNode* head)
{
	LNode* ptr = head;//通过定义一个指针来保留原head。另一种实现方法是设置一个整型变量，每循环一次自加一次，最终结果即为元素个数
	if (Initialized_Check(ptr))
	{
		while (ptr->next != NULL)
		{
			printf("%d  ", ptr->next->data);
			ptr = ptr->next;//这一句最关键，指针后移，指向下一个节点
		}
		printf("\n一共有： %d  个元素！\n\n", head->data);
	}
}

LNode* Create_Linklist(LNode* head)  //依然需要注意函数内部的局部参数问题，所以通过返回值来传递数据
{
	head = (LNode*)malloc(sizeof(LNode));
	if (!head)
	{
		printf("初始化失败！\n\n");
	}
	else
	{
		head->data = 0;//头节点的数据域可用来存放链表长度
		head->next = NULL;				//皆为对形参的head指向的内存单元进行操作，但需要返回一个指针值给实参，表明头节点位置，从而确认链表。若不返回，则实参的head仍为null，形参虽然存在，但未知
		printf("初始化成功！\n\n");
	}
	return(head);
}

void Insert()
{

}

void Head_Insert(LNode* head)
{
	if (Initialized_Check(head))
	{
		LNode* q;
		int input;
		printf("请输入你想要插入的数据：\n");
		scanf_s("%d", &input);
		q = (LNode*)malloc(sizeof(LNode));
		if (q)
		{
			q->data = input;
			q->next = head->next;
			head->next = q;           //皆为对形参的head指向的内存单元进行操作，若head已初始化，则head指针可传进来，head指向的内存单元有效
			head->data++;
			printf("插入成功！\n\n");
		}
		else
		{
			printf("插入失败！\n\n");
		}
	}
}

void Tail_Insert(LNode* head)
{
	if (Initialized_Check(head))
	{
		LNode* q;
		int input;
		printf("请输入你想要插入的数据：\n");
		scanf_s("%d", &input);
		q = (LNode*)malloc(sizeof(LNode));
		if (q)
		{
			q->data = input;
			head->data++;
			while (head->next != NULL)
			{
				head = head->next; //此处依然为对形参head操作，故对实参head不影响。下次不要把实参形参弄成同名的了，不然不好去区分。 //跟笔记上对*p、*q进行操作是一个概念。
			}
			head->next = q;
			q->next = NULL;
			printf("插入成功！\n\n");
		}
		else
			printf("插入失败！\n\n");
	}
}
