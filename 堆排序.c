//用数组来表示完全二叉树（大根堆）

#include <stdio.h>

#define MAX 100

void sift(int R[], int low, int high);//调整数组R中low位置的节点
void headSort(int R[], int n);

int main()
{
	int n; int R[MAX];
	printf("请输入元素个数！\n");
	scanf_s("%d", &n);
	printf("请输入元素！\n");
	for (int i = 0; i <= n-1; ++i)
	{
		scanf_s("%d", &R[i]);
	}
	headSort(R, n);
	printf("调整后的结果如下：\n");
	for (int i = 0; i <= n-1; i++)
	{
		printf("%d ", R[i]);
	}

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
		sift(R, i, n-1);//从最下最右的非叶子节点开始调整，依次向左，依次向上逐个调整
	//排序
	for (i = n-1; i >= 1; --i)//最后一次调整时R[0]已经是最小，不必再动它
	{
		temp = R[0];
		R[0] = R[i];
		R[i] = temp;//这三句完成了堆顶和最后一个元素的置换，此时最后一个元素已经是最大了，将前n-1个变成堆再重复上述过程
		sift(R, 0, i - 1);//因为只置换了R[0]，只有这一个节点可能不符合堆，所以调整它就行了，在sift函数里会自行向下调整，其他的都不用动
	}
}