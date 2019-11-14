#include <stdio.h>

#define MAX 10

int midSearch(int R[], int low, int high, int x);
int flag = 0;//统计递归次数需要使用全局变量

int main()
{
	int R[MAX];
	printf("请有序输入10个数据！\n");
	for (int i = 0; i < 10; i++)
	{
		scanf_s("%d", &R[i]);
	}
	getchar();
	int x;
	printf("请输入你想要查找的数字\n");
	scanf_s("%d", &x);
	midSearch(R, 0, MAX - 1, x);
	printf("一共递归了 %d 次", flag);
}

int midSearch(int R[], int low, int high, int x)
{
	int i = (low + high) / 2;
	flag++;
	if (R[i] == x)
	{
		printf("找到了！它在 %d 位置上\n", i+1);
		return 1;
	}
	else if (x > R[i] && low != high)
	{
		return midSearch(R, i + 1, high, x);
		//flag++;
	}
	else if (x < R[i] && low != high)
	{
		return midSearch(R, low, i - 1, x);
		//flag++;
	}
	else
	{
		printf("并没有找到\n");
		return -1;
	}
}