#include <stdio.h>

#define MAX 100

//传入的参数n代表元素个数，数组元素从下标为0开始

void print(int R[], int n);//打印元素序列
//插入类排序
void InsertSort(int R[], int n);//直接插入排序
void HalfSort(int R[], int n);//折半插入，代码就不写了
void HillSort(int R[], int n);//希尔排序，同上一个了解运行流程即可
//交换类排序
void BubbleSort(int R[], int n);//冒泡排序
void QuickSort(int R[], int n);//快速排序
//选择类排序
void SelectSort(int R[], int n);//简单选择排序
//堆排序（属于选择类排序）
void sift(int R[], int low, int high);//调整数组R中low位置的节点
void headSort(int R[], int n);


int main()
{
	int n;
	int R[MAX];
	while (1)
	{		
		printf("请输入排序操作序号！0位重新输入！-1位退出！\n");
		printf("1.直接插入排序\n");
		printf("2.冒泡排序\n");	
		printf("3.快速排序\n");
		printf("4.简单选择排序\n");
		printf("5.堆排序\n");
		int e;
		scanf_s("%d", &e);
		if (e == -1)
			exit(1);
		printf("请输入元素个数！\n");
		scanf_s("%d", &n);
		printf("请输入序列！\n");
		for (int i = 0; i < n; ++i)
			scanf_s("%d", &R[i]);


		switch (e)
		{
		case 1:
		{
			InsertSort(R, n);
			break;
		}
		case 2:
		{
			BubbleSort(R, n);
			break;
		}
		case 3:
		{
			QuickSort(R, 0, n - 1);
			print(R, n);
			break;
		}
		case 4:
		{
			SelectSort(R, n);
			break;
		}
		case 5:
		{
			headSort(R, n);
			print(R, n);
			break;
		}
		case 0:
			break;
		/*case -1:
			exit(1);*/
		}
	}
}

void print(int R[], int n)
{
	for (int i = 0; i < n; ++i)
	{
		printf("%d ", R[i]);
	}
	printf("\n");
}
//打印序列

void InsertSort(int R[], int n)//直接插入排序依次将元素插入到有序序列，开始时第一个元素看成有序，从第二个元素开始插入，从右向左依次比较有序序列中的元素，找到相应位置并插入
{
	int i, j, temp;
	for (i = 1; i <= n - 1; i++)//因为第一个元素把它看成有序，从第二个元素开始挨个插入到有序序列
	{
		temp = R[i];//将待插入的元素存放到temp
		j = i - 1;
		while (j >= 0 && temp < R[j])//弱temp>R[j]，说明找到插入位置，则将待插关键字放到R[j+1}
		{
			R[j + 1] = R[j];//若有序序列最右的关键字大于待插入元素（存于temp中）便将该关键字后移，同时指针前移，比较序列中前面的关键字
			j--;
		}
		R[j + 1] = temp;//找到插入位置，将temp暂存的关键字放到合适的位置
	}
	print(R, n);
}
//直接插入排序

void BubbleSort(int R[], int n)//冒泡排序两两比较，将大的关键字沉底，每一趟比较都有一个新的大关键字沉底，比较n-1趟，即可得到序列
{
	int i, j, flag, temp;//可能存在不需要n-1趟就有序的好情况，所以设置一个flag变量用来标记本趟是否进行了排序，如果没有，则说明已经有序，剩下的趟数都不需要再比较了
	for (i=n-1; i >= 1; --i)//最坏的情况是循环n-1次，因为是将大的数沉底，所以设置n从n-1减到1
	{
		flag = 0;//用于标记本趟是否进行来排序
		for (j = 0; j < i; ++j)
		{
			if (R[j] > R[j + 1])
			{
				temp = R[j];
				R[j] = R[j + 1];
				R[j + 1] = temp;//两个数比较，如果左边的数比较大，则把它换到右边
				flag = 1;
			}
		}
		if (flag == 0)
			goto H2;
		//return;
	}
H2:		print(R, n);//经查阅资料，二层循环的跳出方法用goto会比较合适，也可改变最外层循环条件或循环内的判断条件，或设置判断标志，在外层循环后用if语句判断是否break
					//return直接让函数返回了，这样的话如果每一次都排了，最后flag不会为0，这样的话if里面的输出函数就不会执行
					//所以把它放到外面，用一个goto
}
//冒泡排序

void QuickSort(int R[], int low,int high)//快速排序，设置在序列的头和尾设置两个指针，依次移动两个指针并与关键字比较，一般关键字为序列的第一个元素，然后根据需要交换与关键字的位置
							  //每一趟排序实现将小于关键字的放到左边，大于关键字的放到右边，然后递归排序关键字左右两边的序列，所以函数的参数设置为2个，而不是简单的元素个数，以便递归调用
{
	int i = low, j = high;
	int temp;
	if (low < high)//当low和high相遇时，说明这一趟排序结束
	{
		temp = R[low];//取该序列第一个元素位关键字
		//该循环完成一趟排序，小于temp的在左边，大于temp的在右边
		while (i < j)
		{
			while (i < j && R[j] >= temp)//因为时循环条件，当大于关键字就接着找，直到找到一个小于关键字的，便打破了循环条件，或者ij相遇
				--j;//从右向左扫描，找到一个比temp小的
			if (i < j)//在不相遇的前提下交换，相遇则说明已经有序了
			{
				R[i] = R[j];
				++i;//i右移一位，因为换完后这个位置一定比temp小了
			}
			while (i < j && R[i] <= temp)
				++i;//从左向右扫描，找到一个比temp大的
			if (i < j)
			{
				R[j] = R[i];
				--j;
			}
		}
		R[i] = temp;//最后将temp放到合适的位置，到这里第一趟排序完成！
		QuickSort(R, low, i - 1);
		QuickSort(R, i + 1, high);//递归对左右两边都排序
	}
}
//快速排序

void SelectSort(int R[], int n)//与冒泡排序不同，选择排序每次在序列中找出最小的一个关键字，然后与序列中第一个交换，直到序列有序
{
	int i, j, head;
	int temp;
	for (i = 0; i < n; ++i)
	{
		head = i;
		for (j = i + 1; j < n; j++)
			if (R[j] < R[head])
				head = j;//找到并记录最小元素的位置
		temp = R[i];
		R[i] = R[head];
		R[head] = temp;//与第一个元素进行交换
	}
	print(R, n);
}

void sift(int R[], int low, int high)//数组的下标从0开始，high为数组的最高下标数
{
	int i = low, j = 2 * low + 1;//R[j]是R[i]的左孩子
	int temp = R[i];
	while (j <= high)//传进来的参数是最高下标数
	{
		if (j < high && R[j] < R[j + 1]) //如果j等于high了，说明是最后一个节点，没有j+1节点了
			++j; //如果右孩子比左孩子大，则换右孩子不换左孩子
		if (temp < R[j])//如果R[i]比这个右孩子小了，不符合大根堆的定义，需要交换
		{
			R[i] = R[j];
			i = j;
			j = 2 * i + 1;//修改i和j，以便向下修改，因为修改后可能不符合堆的定义了
		}
		else
			break;//如果满足定义，就跳出循环，不用调整，下层的肯定也符合
	}
	R[i] = temp;//修改的节点放到了合适最终位置上
}

void headSort(int R[], int n)//堆排序函数，n为元素个数
{
	int i, temp;
	//建堆
	for (i = n / 2 - 1; i >= 0; i--)//叶子节点必满足，所以直接从非叶子节点开始，n/2-1是因为数组是从0开始的，所以需要-1
		sift(R, i, n - 1);//从最下最右的非叶子节点开始调整，依次向左，依次向上逐个调整
	//排序
	for (i = n - 1; i >= 1; --i)//最后一次调整时R[0]已经是最小，不必再动它
	{
		temp = R[0];
		R[0] = R[i];
		R[i] = temp;//这三句完成了堆顶和最后一个元素的置换，此时最后一个元素已经是最大了，将前n-1个变成堆再重复上述过程
		sift(R, 0, i - 1);//因为只置换了R[0]，只有这一个节点可能不符合堆，所以调整它就行了，在递归sift函数里会自行向下调整，其他的都不用动
	}
}