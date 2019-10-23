#include <stdio.h>
#include <stdlib.h>

#define MAX 100

//邻接表需要的数据类型的定义

typedef struct ArcNode//链表结点
{
	int adjvex;//该边指向的节点位置
	struct ArcNode* nextarc;//指向下一条边的指针
	//int info;//该编的相关信息，如权值，用的不多
}ArcNode;

typedef struct//顶点
{
	char data;//顶点信息
	ArcNode* firstarc;
}VNode;

typedef struct//顶点数组
{
	VNode adjlist[MAX];//邻接表
	int n, e;//顶点数和边数
}AGraph;

int visit[MAX];

//子函数
AGraph* CreateAGraph();//初始化图，该图的存储方式是邻接表
void print(AGraph* p);//打印图
void DFS(AGraph* p,int v);//深度优先遍历

int main()
{
	AGraph* p = CreateAGraph();
	print(p);
	printf("你想从哪个节点开始访问？一共有 %d 个节点，数组下标从0开始\n", p->n);
	int v;
	scanf_s("%d", &v);
	DFS(p,v);
}

AGraph* CreateAGraph()
{
	int i, j;
	AGraph* p = (AGraph*)malloc(sizeof(AGraph));
	if (!p)
		return NULL;
	ArcNode* q;
	printf("请输入节点个数和边数！\n");
	scanf_s("%d %d", &p->n,&p->e);
	printf("请依次输入元素值！\n");
	for (int i = 0; i < p->n; ++i)
	{
		getchar();
		scanf_s("%c", &(p->adjlist[i].data));
		p->adjlist[i].firstarc = NULL;
	}
	printf("请输入节点的边！以下标标记！如1 3\n");
	for (int k = 0; k < p->e; k++)  //输入的变没有检测功能，如果下标溢出了会报错，下标从0开始
	{
		scanf_s("%d%d", &i, &j);
		q = (ArcNode*)malloc(sizeof(ArcNode));
		q->adjvex = j;                                  //存储弧头 
		q->nextarc = p->adjlist[i].firstarc;            //头插法插入边结点 
		p->adjlist[i].firstarc = q;

		//下面代码有向图无,无向图有 
		q = (ArcNode*)malloc(sizeof(ArcNode));
		q->adjvex = i;                                //存储弧头 
		q->nextarc = p->adjlist[j].firstarc;            //头插法插入边结点 
		p->adjlist[j].firstarc = q;
	}
	return p;
}

void print(AGraph* p)
{
	printf("邻接表为:\n");
	for (int i = 0; i < p->n; i++)
	{
		ArcNode* q = p->adjlist[i].firstarc;
		while (q)
		{
			printf("(%c,%c)", p->adjlist[i].data, p->adjlist[q->adjvex].data);
			q = q->nextarc;
		}
		printf("\n");
	}
}

void DFS(AGraph * p,int v)//以节点v作为起点，v为下标，下标从0开始，该算法不能实现深度遍历非连通图
{
	if (v >= p->n)
	{
		printf("下标溢出！\n");
		return;
	}
	//int visit[MAX] = { 0 }  递归时会重复置0，所以要放到全局变量上
	ArcNode* q;
	visit[v] = 1;
	printf("%c ", p->adjlist[v].data);
	q = p->adjlist[v].firstarc;
	while (q != NULL)
	{
		if (visit[q->adjvex] == 0)
			DFS(p,q->adjvex);//深度优先，递归访问，邻接表的定义是连接在同一个节点的节点串成一个链表，不是一个接着一个连
		q = q->nextarc;//指向顶点v的下一个节点
	}
}

