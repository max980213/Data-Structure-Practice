//线性表，顺序存储的线性表

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define MAX_SIZE 100

typedef int Status;
typedef int ElemType;
typedef struct sqlist
{
	ElemType* elem_array;
	int length;
	int maxSize;
}SqList;

Status Initialized_Check(SqList* L);
Status Print_Sqlist(SqList* L);
Status Init_Sqlist(SqList* L);
Status Insert_Sqlist(SqList* L);
Status Head_Insert(SqList* L);
Status Tail_Insert(SqList* L);
Status Search_List(SqList* L);//done
Status Head_delete(SqList* L);
Status Tail_delete(SqList* L);
Status Delete_Sqlist(SqList* L);
Status Search_delete(SqList* L,ElemType e);
Status Clear_list(SqList* L);
Status Destroy_list(SqList* L);

SqList L;  //声明为全局变量，才能检测未初始化，原因未知
		   //原因查明，如果是全局变量声明则为0和NULL，局部变量则为随机

int input;

int main()                                                  //经思考，插入一个数据开辟内存，删除一个数据释放内存并不现实，而且造成了处理器浪费
{
	//SqList L;
	while (1)
	{
		printf("请输入操作序号！\n");
		printf("0.打印线性表\n");
		printf("1.初始化顺序线性表\n");
		printf("2.指定位置插入元素\n");
		printf("3.从线性表头插入元素\n");
		printf("4.从线性表尾插入元素\n");
		printf("5.查找线性表中的元素\n");
		printf("6.从线性表头删除一个元素\n");
		printf("7.从线性表尾删除一个元素\n");
		printf("8.指定位置删除一个元素\n");
		printf("9.删除指定元素值的元素\n");
		printf("10.将线性表清空\n");
		printf("11.销毁线性表\n");
		printf("-1.退出\n");
		//后续添加功能

		if (scanf_s("%d", &input)!=1)
		{
			//fflush(stdin); //清空缓冲区并不好用，原因未知
			printf("输入有误！请重新输入！\n\n");
			getchar();
		}
		else
		{ 
			switch (input)
			{
			case 0:
			{
				Print_Sqlist(&L);
				break;
			}
			case 1:
			{
				//SqList L;  若在此处声明。则为局部变量
				Init_Sqlist(&L);
				break;
			}
			case 2:
			{
				Insert_Sqlist(&L);
				break;
			}
			case 3:
			{
				Head_Insert(&L);
				break;
			}
			case 4:
			{
				Tail_Insert(&L);
				break;
			}
			case 5:
			{
				Search_List(&L);
				break;
			}
			case 6:
			{
				Head_delete(&L);
				break;
			}
			case 7:
			{
				Tail_delete(&L);
				break;
			}
			case 8:
			{
				Delete_Sqlist(&L);
				break;
			}
			case 9:
			{
				printf("请输入你想删除的数据项：\n");
				ElemType e;
				scanf_s("%d", &e);
				Search_delete(&L, e);
				break;
			}
			case 10:
			{
				Clear_list(&L);
				break;
			}
			case 11:
			{
				Destroy_list(&L);
				break;
			}
			default:
			{
				printf("输入内容不合法！\n\n");
				break;
			}
			case -1:
				exit(0);
			}
		}
	}
}

Status Initialized_Check(SqList* L)
{
	if (!L->elem_array)
	{
		printf("线性表还未初始化！\n\n");
		return 0;
	}
	else
		return 1;
}

Status Print_Sqlist(SqList* L)
{
	if (Initialized_Check(L))
	{
		for (int k = 0; k < L->length; k++)
		{
			printf("%d  ", L->elem_array[k]);
		}
		printf("\n当前线性表长度为： %d \n\n",L->length);
		return 1;
	}
}

Status Init_Sqlist(SqList* L)
{
	L->elem_array = (ElemType*)malloc(MAX_SIZE * sizeof(ElemType));
	if (!L->elem_array)//如果分配内存失败了
	{
		printf("初始化线性表失败！\n\n");
		return -1;
	}
	else
	{
		L->maxSize = MAX_SIZE;
		printf("初始化成功！\n\n");
		L->length = 0;
		return 1;
	}
}

Status Insert_Sqlist(SqList* L)//, int i, ElemType e)
{
	int j, i;
	ElemType e;
	if (Initialized_Check(L))
	{
		if (L->length == 0)
		{
			printf("线性表为空！不可插入！\n\n");
			return -1;
		}
		else if (L->length >= MAX_SIZE)
		{
			printf("线性表溢出！不可再插入！\n\n");
			return -1;
		}
		else
		{
			printf("请输入想要插入的位置\n");
			scanf_s("%d", &i);
			if (i<=0 || i>L->length) //插入第1个元素应从0开始，因为线性表为空 //此功能舍弃，更换为从表头插入
			{
				printf("插入位置溢出\n\n");
				return -1;
			}
			else
			{
				printf("请输入想要插入的数字\n");
				scanf_s("%d", &e);
				//Insert_Sqlist(&L, i, e);
				for (j = L->length - 1; j >= i - 1; j--)
				{
					L->elem_array[j + 1] = L->elem_array[j];
				}
				L->elem_array[i - 1] = e;
				L->length++;
				printf("插入成功！\n\n");
				return 1;
			}
		}
	}
}

Status Head_Insert(SqList* L)
{
	if (Initialized_Check(L))
	{
		if (L->length >= MAX_SIZE)
		{
			printf("线性表溢出！不可再插入！\n\n");
			return -1;
		}
		else
		{
			ElemType e;
			printf("请输入想插入的数字！\n");
			scanf_s("%d", &e);
			for (int k = L->length - 1; k >= 0; k--)
				L->elem_array[k + 1] = L->elem_array[k];
			L->elem_array[0] = e;
			L->length++;
			printf("插入成功！\n\n");
			return 1;
		}
	}
}

Status Tail_Insert(SqList* L)
{
	if (Initialized_Check(L))
	{
		if (L->length >= MAX_SIZE)
		{
			printf("线性表溢出！\n\n");
			return -1;
		}
		else
		{
			ElemType e;
			printf("请输入想要插入的数字！\n");
			scanf_s("%d", &e);
			L->elem_array[L->length] = e;
			L->length++;
			printf("插入成功！\n\n");
			return 1;
		}
	}
}

Status Search_List(SqList* L)
{	
	if (Initialized_Check(L))
	{
		ElemType e;
		int flag = 0;
		printf("请输入想要查询的数据值！\n");
		scanf_s("%d", &e);
		printf("此数据出现的位置：");
		for (int k = 0; k <= L->length - 1; k++)
		{
			if (L->elem_array[k] == e)
			{
				printf(" %d ", k + 1);
				//continue;
				flag++;
			}
		}
		printf("\n一共有 %d 个数据项！\n\n", flag);
		return 1;
	}
}

Status Head_delete(SqList* L)
{
	if (Initialized_Check(L))
	{
		for (int k = 1; k <= L->length - 1; k++)
		{
			L->elem_array[k - 1] = L->elem_array[k]; //对最后一个元素未操作，但使长度减1
		}			
		L->elem_array[L->length - 1] = NULL; //此语句也许有一点多余
		L->length--;
		printf("删除成功！\n\n");
		return 1;
	}
}

Status Tail_delete(SqList* L)
{
	if (Initialized_Check(L))
	{
		L->elem_array[L->length - 1] = NULL; //经测试，此语句会将数组该位置置0
		L->length--;
		printf("删除成功！\n\n");
		return 1;
	}
}

Status Delete_Sqlist(SqList* L)
{
	if (Initialized_Check(L))
	{
		printf("你想删掉第几个数据？\n");
		int i;
		scanf_s("%d", &i);
		if (i <= 0 || i > L->length)
		{
			printf("删除元素的位置溢出！\n\n");
			return -1;
		}
		else
		{
			for (int k = i; k <= L->length-1; k++)
			{
				L->elem_array[k - 1] = L->elem_array[k];
			}
			L->elem_array[L->length - 1] = NULL;
			L->length--;
			printf("删除成功！\n\n");
			return 1;
		}
	}
}

Status Search_delete(SqList* L,ElemType e)
{
	if (Initialized_Check(L))
	{
		int number = 0;
H1:		for (int k=0; k <= L->length-1; k++)  //或通过设立中间变量，实现从删除项位置再向后查找
		{
			if (L->elem_array[k] == e)
			{
				for (k; k <= L->length - 1 - number; k++)
				{
					L->elem_array[k] = L->elem_array[k + 1];
				}
				L->length--;
				number++;
				//Search_delete(L, e);
				goto H1;    //注释掉的递归可以实现该操作，但最终的汇总不好处理,且递归一次便输出一次，所以改用一个goto语句
			}
		}
		if (number == 0)
		{
			printf("该项值元素不存在！\n\n");
			return 0;
		}
		else
		{
			printf("删除成功！一共删除了： %d 个项！\n\n",number);
			return 1;
		}
	}
}

Status Clear_list(SqList* L)
{
	for (int k = 0; k <= L->length - 1; k++)
	{
		L->elem_array[k] = NULL;
	}
	L->length = 0;
	printf("线性表清空成功！\n\n");
	return 1;
}

Status Destroy_list(SqList* L)
{
	free(L->elem_array);
	L->elem_array = NULL;
	L->length = L->maxSize = 0;
	printf("线性表销毁成功！\n\n");
	return 1;
}