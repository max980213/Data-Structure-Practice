//写在开头：此程序的头节点在主函数中设置并非设置为全局变量。一定要区分出形参与实参的传递关系。如创建头节点函数中的head为形参，实参按值传递进来之后便为形参再操作，函数运行完毕后就会释放形参。
//所以需要一个返回值。
//笔记中的两个函数对比，指针形参的操作为*p与*q之间的互换。这里的create函数中是对指针值进行直接操作，malloc函数申请的内存函数结束后不会释放，但申请到的head指针依然是形参，且实变量在主函数中，所以需要返回给实参。
//也可以理解为，插入函数中，只需把各结点指针链接起来即可，但是生成头节点需要返回一个确切的指针来指向头节点。
//或者，在插入函数中，是对形参head指针指向的内存单元进行操作，并不是对head指针本身进行操作。但在初始化头节点中，还是需要一个确切的指针值返回给实参，所以用一个返回值


#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef struct LNode
{
	int data;
	struct LNode* next;
}LNode;

LNode* Create_Linklist(LNode* head);//创建头节点
int Initialized_Check(LNode* head);//检测是否已初始化
void Print_Linklist(LNode* head);//打印链表
void Insert(LNode* head);//插入数据
void Head_Insert(LNode* head);//在链表表头插入数据
void Tail_Insert(LNode* head);//在表尾插入数据
void IDNumber_Delete(LNode* head);//按序号值删除节点
void Data_Delete(LNode* head);//按元素值删除节点
void Head_Delete(LNode* head);//头删
void Tail_Delete(LNode* head);//尾删
void Search_Linklist(LNode* head);//查找元素位置
void Clear_Linklist(LNode* head);//清空
LNode* Destroy_Linklist(LNode* head);//销毁

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
			Insert(head);
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
		case 5:
		{
			IDNumber_Delete(head);
			break;
		}
		case 6:
		{
			Data_Delete(head);
			break;
		}
		case 7:
		{
			Head_Delete(head);
			break;
		}
		case 8:
		{
			Tail_Delete(head);
			break;
		}
		case 9:
		{
			Search_Linklist(head);
			break;
		}
		case 10:
		{
			Clear_Linklist(head);
			break;
		}
		case 11:
		{
			head = Destroy_Linklist(head);
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
	LNode* ptr = head;//通过定义一个指针来保留原head。另一种实现方法是设置一个整型变量，每循环一次自加一次，最终结果即为元素个数 //也可直接对head操作，设置变量每循环一次自加，便可统计个数。
					  //这里是为了测试其他函数中对head->data的操作是否有误
	if (Initialized_Check(ptr))
	{
		while (ptr->next != NULL)//输出的是当前指针指向节点的后一个节点的数据域的值，当循环到指向倒数第二个节点，输出最后一个值，指针后移，此时ptr->next = NULL，跳出循环
		{
			printf("%d  ", ptr->next->data);//头节点中的元素为链表长度，若把头节点当作第一个节点，则输出第二个节点的数据域。头节点不算做链表长度的一部分。
			ptr = ptr->next;//这一句最关键，指针后移，指向下一个节点
		}
		printf("\n一共有： %d  个元素！\n\n", head->data);
	}
}

/*
void Print_Linklist(LNode* head)
{
	head = head->next;
	if (head != NULL)
	{
		printf("%d  ", head->data);
		Print_Linklist(head);
	}
	else
	{
		return;
	}
}
*/

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

void Insert(LNode* head)
{
	if (Initialized_Check(head))
	{
		if (head->data == 0)
		{
			printf("链表为空！请从链表头开始插入！\n\n");
		}
		else
		{
			int seq, input, j = 0;
			LNode* ptr = head, * q;
			printf("请输入你想要插入的位置（一共有 %d 个数据）： ",head->data);
			scanf_s("%d", &seq);
			if (seq <= 0 || seq > head->data)
			{
				printf("插入位置溢出！\n");
			}
			else
			{
				printf("请输入你想要插入的数据：");
				scanf_s("%d", &input);
				while (j < seq - 1)//找到要插入位置的前一个节点
				{
					ptr = ptr->next;
					j++;
				}
				q = (LNode*)malloc(sizeof(LNode));
				if (q)
				{
					q->data = input;
					q->next = ptr->next; //链接表
					ptr->next = q;
					head->data++; //长度自增
					printf("插入成功！\n\n");
				}
				else
					printf("插入失败！\n\n");
			}
		}
	}
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
			q->next = head->next;//链接链表
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
		LNode* q, * ptr;
		int input;
		printf("请输入你想要插入的数据：\n");
		scanf_s("%d", &input);
		q = (LNode*)malloc(sizeof(LNode));
		if (q)
		{
			ptr = head;
			//q->data = input;
			//head->data++; //也可设置指针ptr=head，然后通过ptr遍历链表，保留了head头指针，然后最后再head->data++
			while (ptr->next != NULL)//遍历节点，找到最后一个节点
			{
				ptr = ptr->next; //若不设ptr指针，则还为对形参head操作，故对实参head不影响。下次不要把实参形参弄成同名的了，不然不好去区分。 
			}
			ptr->next = q;//找到当前最后一个节点，并让它指向新一个最后的节点
			q->data = input;//跟笔记上对*p、*q进行操作是一个概念，对指针指向的内存单元进行修改
			q->next = NULL;//最后一个节点指向空
			head->data++;
			printf("插入成功！\n\n");
		}
		else
			printf("插入失败！\n\n");
	}
}

void IDNumber_Delete(LNode* head)
{
	if (Initialized_Check(head))
	{
		if (head->data == 0)
		{
			printf("链表啥都没有！你想删啥？\n\n");
		}
		else
		{
			int seq, j = 0;
			LNode* ptr = head, * q = head->next;
			printf("请输入你想要删除的元素序号（一共有 %d 个元素）：", head->data);
			scanf_s("%d", &seq);
			if (seq <= 0 || seq > head->data)
			{
				printf("位置溢出！\n\n");
			}
			else
			{
				while (j < seq - 1)//依然是找到前一个节点，必须找到前一个节点
				{
					ptr = ptr->next;
					q = q->next;
					j++;
				}
				ptr->next = q->next;  //如果是 p->next=p->next->next;free(p->next)，那么在修改p->next之后，就直接free掉了，即free掉了原来的p->next->next，导致了断链。所以需要设置中间指针变量,来保存要删除的节点
				free(q);
				head->data--;
				printf("删除成功！\n\n");
			}
		}
	}
}

void Data_Delete(LNode* head)
{
	if (Initialized_Check(head))
	{
		if (head->data == 0)
		{
			printf("链表为空！\n\n");
		}
		else
		{
			int input, number = 0;
			printf("请输入你想要删除的元素值： ");
			scanf_s("%d", &input);
			LNode* p = head, * q = head->next;
			while (q != NULL)//这里没有用j<=head->data的原因是此值可能会随时变化
			{
				if (q->data == input)
				{
					p->next = q->next;
					free(q);
					q = p->next;
					number++;
					head->data--;//头节点数据域存放了链表长度
				}
				else
				{
					p = p->next;
					q = q->next;
				}
			}
			printf("一共删除了 %d 个元素！\n\n", number);
		}
	}
}

void Head_Delete(LNode* head)
{
	if (Initialized_Check(head))
	{
		if (head->data == 0)
		{
			printf("链表为空！\n\n");
		}
		else 
		{
			LNode* ptr = head->next;
			head->next = ptr->next;
			free(ptr);
			head->data--;
			printf("删除成功！\n\n");
		}
	}
}

void Tail_Delete(LNode* head)
{
	if (Initialized_Check(head))
	{
		if (head->data == 0)
		{
			printf("链表为空！\n\n");
		}
		else
		{
			LNode* ptr = head->next;//或head，好像都行
			while (ptr->next->next != NULL)//找到最后一个节点的前一个节点
			{
				ptr = ptr->next;//指针后移
			}
			free(ptr->next);//释放掉最后一个节点
			ptr->next = NULL;//并使新最后一个节点指向Null
			head->data--;
			printf("删除成功！\n\n");
		}
	}
}

void Search_Linklist(LNode* head)
{
	if (Initialized_Check(head))
	{
		if (head->data == 0)
		{
			printf("链表为空！\n\n");
		}
		else
		{
			int input, amount = 0, flag = 1;
			LNode* ptr = head->next;
			printf("请输入你想要查找的元素值： ");
			scanf_s("%d", &input);
			printf("该值数据在链表中出现的位置：  ");
			while (ptr != NULL)//需要遍历到最后一个节点并比较其数据项，ptr->next虽然找到了最后一个节点，但跳出了循环，因为最后一个节点的指针域为NULL
			{
				if (ptr->data == input)
				{
					printf("%d  ", flag);
					amount++;
				}
				flag++;
				ptr = ptr->next;
			}
			printf("\n一共有： %d 个数据项！\n\n", amount);
		}
	}
}

void Clear_Linklist(LNode* head)
{
	if (Initialized_Check(head))
	{ 
		if (head->data == 0)
		{
			printf("链表已为空！\n\n");
		}
		else
		{
			LNode* ptr = head->next;
			int amount = head->data;
			while (head->next != NULL) //循环删掉第一个节点   //或先将头节点与链表断开，然后逐个释放节点，但最后一个节点处理稍麻烦。
			{
				head->next = ptr->next;
				free(ptr);
				ptr = head->next;
				head->data--;
			}
			printf("清空成功！一共清除了： %d 个数据！\n\n",amount);
		}
	}
}

LNode* Destroy_Linklist(LNode* head)
{
	if (Initialized_Check(head))
	{
		Clear_Linklist(head);//直接清空链表，再释放头节点
		free(head);
		head = NULL; //free掉之后这个指针就变成“野指针”，所以需要让它指向null，不然就不知道指哪去了
		printf("销毁成功！\n\n");
		return(head);
	}
}