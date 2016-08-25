/**********************************************************************************************//**
 * @file	Graph.cpp
 *
 * Implements the graph class.
 **************************************************************************************************/
#include <iostream>
#include <queue>
#include <stack>
#include <algorithm>
using namespace std;
#define MAXV 100
#define MAXSIZE 1000
using InfoType = char;
using VertexType = char;
/** 邻接矩阵 */
//typedef struct{
//	int no;
//	InfoType info;
//}VertexType;
typedef struct{
	int edge[MAXV][MAXV];
	int n, e;
	VertexType vexs[MAXV];
}MGraph;
/** 邻接表 */
typedef struct ANode{
	int adjvex;
	struct ANode *nextarc;
	InfoType info;
}ArcNode;
typedef struct Vnode{
	VertexType data;
	int count;          //仅拓扑排序使用
	ArcNode *firstarc;
}VNode;
typedef VNode AdjList[MAXV];
typedef struct{
	AdjList adjlist;
	int n, e;
}ALGraph;
void MatToList(MGraph g, ALGraph *&G){
	int i, j, n = g.n;
	ArcNode *p;
	G = new ALGraph;
	for (i = 0; i < n; i++)
		G->adjlist[i].firstarc = NULL;
	for (i = 0; i < n; i++){
		for (j = n - 1; j >= 0; j--){
			if (g.edge[i][j] != 0){
				p = new ArcNode;
				p->adjvex = j;
				p->nextarc = G->adjlist[i].firstarc;
				G->adjlist[i].firstarc = p;
			}
		}
	}
	G->n = n; G->e = g.e;
}
void ListToMat(ALGraph *G, MGraph &g){
	int i, n = G->n;
	ArcNode *p;
	for (i = 0; i < n; i++){
		p = G->adjlist[i].firstarc;
		while (p != NULL){
			g.edge[i][p->adjvex] = 1;
			p = p->nextarc;
		}
	}
	g.n = n; g.e = G->e;
}

int visited[MAXV];
void DFS(ALGraph *G, int v){
	ArcNode *p;
	visited[v] = 1;
	cout << v << "\t";
	p = G->adjlist[v].firstarc;
	while (p != NULL){
		if (visited[p->adjvex] == 0)
			DFS(G, p->adjvex);
		p = p->nextarc;
	}
}
void DFS1(ALGraph *g){
	for (auto i = 0; i < g->n; i++)
		if (visited[i] == 0)
			DFS(g, i);
}
void BFS(ALGraph *G, int v){
	ArcNode *p;
	queue<int> q;
	int w, i;
	for (i = 0; i < G->n; i++) visited[i] = 0;
	cout << v << "\t";
	visited[v] = 1;
	q.push(v);
	while (!q.empty()){
		w = q.front();
		p = G->adjlist[w].firstarc;
		while (p != NULL){
			if (visited[p->adjvex] == 0){
				cout << p->adjvex << "\t";
				visited[p->adjvex] = 1;
				q.push(p->adjvex);
			}
			p = p->nextarc;
		}
		q.pop();
	}
	cout << endl;
}
void BFS1(ALGraph *g){
	for (auto i = 0; i < g->n; i++)
		if (visited[i] == 0)
			BFS(g, i);
}
//无向图G是否连同，1连通，0不连通，用DFS
int connect(ALGraph *G){
	for (auto i = 0; i < G->n; i++)
		visited[i] = 0;
	DFS(G, 0);
	for (auto i = 0; i < G->n; i++){
		if (visited[i] == 0)
			return 0;
	}
	return 1;
}
//输出图G中u到v的长度为l的所有简单路径
void PathAll(ALGraph *G, int u, int v, int l, int path[], int d){
	int m;
	ArcNode *p;
	visited[u] = 1;
	d++;
	path[d] = u;
	if (u == v && d == l){
		cout << " ";
		for (auto i = 0; i <= d; i++)
			cout << path[i]<<" ";
		cout << endl;
	}
	p = G->adjlist[u].firstarc;
	while (p != NULL){
		m = p->adjvex;
		if (visited[m] == 0)
			PathAll(G, m, v, l, path, d);
		p = p->nextarc;
	}
	visited[u] = 0;
	d--;
}
// 输出邻接表
void DispAdj(ALGraph* G)
{
	ArcNode* p;
	cout << "Graph G:" << endl;
	for (auto i = 0; i < G->n; i++)
	{
		cout << " " << i << ": ";
		p = G->adjlist[i].firstarc;
		while (p != NULL)
		{
			cout << p->adjvex << " ";
			p = p->nextarc;
		}
		cout << endl;
	}
}
//最小生成树PRIM
#define INF 32767
void Prim(MGraph g, int v)
{
	int lowcost[MAXV], closest[MAXV];
	int min;
	auto k = 0;
	for (auto i = 0; i < g.n; i++)
	{
		lowcost[i] = g.edge[v][i];
		closest[i] = v;
	}
	for (auto i = 1; i < g.n; i++)
	{
		min = INF;
		for (auto j = 0; j < g.n; j++)
		{
			if (lowcost[j] != 0 && lowcost[j] < min)
			{
				min = lowcost[j];
				k = j;
			}
		}
		cout << "边(" << closest[k] << "," << k << ")权值为" << min << endl;
		lowcost[k] = 0;
		for (auto j = 0; j < g.n; j++)
		{
			if (g.edge[k][j] != 0 && g.edge[k][j] < lowcost[j])
			{
				lowcost[j] = g.edge[k][j];
				closest[j] = k;
			}
		}
	}
}

//Kruskal
typedef struct
{
	int u;
	int v;
	int w;
}Edge;
typedef struct node{
	int rank;
	int parent;
}UFSTree;
void MAKE_SET(UFSTree t[],int n)
{
	for (auto i = 0; i < n; i++)
	{
		t[i].rank = 0;
		t[i].parent = i;
	}
}
int FIND_SET(UFSTree t[], int x)
{
	if (x != t[x].parent)
		return FIND_SET(t, t[x].parent);
	else
		return x;
}
void UNION(UFSTree t[], int x, int y)
{
	x = FIND_SET(t, x);
	y = FIND_SET(t, y);
	if (t[x].rank > t[y].rank)
		t[y].parent = x;
	else
	{
		t[x].parent = y;
		if (t[x].rank == t[y].rank)
			t[y].rank++;
	}
}
int comp(Edge a,Edge b)
{
	if (a.w != b.w)
		return a.w < b.w;
	else if (a.u != b.u)
		return a.u < b.u;
	else
		return a.v <= b.v;		
}
void Kruskal(MGraph g)
{
	UFSTree t[MAXSIZE];
	Edge E[MAXSIZE];
	auto k = 1;
	for (auto i = 0; i < g.n; i++)
		for (auto j = 0; j < g.n; j++)
		{
			if (g.edge[i][j] != 0 && g.edge[i][j] != INF)
			{
				E[k].u = i; E[k].v = j; E[k].w = g.edge[i][j];
				k++;        //?
			}
		}
	sort(E, E+k, comp);
	MAKE_SET(t, g.n);
	k = 1;
	auto j = 1;
	while (k<g.n)
	{
		auto u1 = E[j].u;
		auto u2 = E[j].v;
		auto sn1 = FIND_SET(t, u1);
		auto sn2 = FIND_SET(t, u2);
		if (sn1 != sn2)
		{
			cout << "边(" << u1 << "," << u2 << ")权值为" << E[j].w << endl;
			k++;
			UNION(t, u1, u2);
		}
		j++;
	}
}

void test_Prim_Kruskal()
{
	int A[MAXV][MAXV] = {
		{ 0, 6, 1, 5, INF, INF },
		{ 6, 0, 5, INF, 3, INF },
		{ 1, 5, 0, 5, 6, 4 },
		{ 5, INF, 5, 0, INF, 2 },
		{ INF, 3, 6, INF, 0, 6 },
		{ INF, INF, 4, 2, 6, 0 }
	};
	MGraph g;
	g.n = 6; g.e = 9;
	for (auto i = 0; i < g.n; i++)
		for (auto j = 0; j < g.n; j++)
			g.edge[i][j] = A[i][j];
	cout << "Prim:" << endl;
	Prim(g, 0); cout << endl;
	cout << "Kruskal:" << endl;
	Kruskal(g); cout << endl;
}

//Dijkstra
void Ppath(int path[], int i, int v)
{
	int k;
	k = path[i];
	if (k == v) return;
	Ppath(path, k, v);
	cout << k << ", ";
}
void Dispath(int dist[], int path[], int s[], int n, int v)
{
	for (auto i = 0; i < n; i++){
		if (s[i] == 1)
		{
			cout << "从" << v << "到" << i << "的最短路径长度为：" << dist[i] << "\t";
			cout << "路径为：" << v<<", ";
			Ppath(path, i, v);
			cout << i << endl;
		}
		else
			cout << "从" << v << "到" << i << "不存在路径" << endl;
	}
}
void Dijkstra(MGraph g, int v)
{
	int dist[MAXV], path[MAXV];
	int s[MAXV];
	int mindis, u;
	for (auto i = 0; i < g.n; i++)
	{
		dist[i] = g.edge[v][i];
		s[i] = 0;
		if (g.edge[v][i] < INF)
			path[i] = v;
		else
			path[i] = -1;
	}
	s[v] = 1; path[v] = 0;
	for (auto i = 0; i < g.n; i++)
	{
		mindis = INF;
		for (auto j = 0; j < g.n; j++)
		{
			if (s[j] == 0 && dist[j]<mindis)
			{
				u = j;
				mindis = dist[j];
			}
		}
		s[u] = 1;
		for (auto j = 0; j < g.n; j++)
		{
			if (s[j] == 0)
			{
				if (g.edge[u][j]<INF && dist[u] + g.edge[u][j]<dist[j])
				{
					dist[j] = dist[u] + g.edge[u][j];
					path[j] = u;
				}
			}
		}
	}
	Dispath(dist, path, s, g.n, v);
}

//Floyd
void Ppath2(int path[][MAXV],int i,int j)
{
	int k;
	k = path[i][j];
	if (k == -1) return;
	Ppath2(path, i, k);
	cout << k << ", ";
	Ppath2(path, k, j);
}
void Dispath2(int A[][MAXV],int path[][MAXV],int n)
{
	for (auto i = 0; i < n; i++)
	{
		for (auto j = 0; j < n; j++)
		{
			if (A[i][j] == INF)
			{
				if (i != j)
					cout << "从" << i << "到" << j << "没有路径\n";
			}
			else
			{
				cout << "从" << i << "到" << j << "路径长度为：" << A[i][j];
				cout << " 路径：" << i << ", ";
				Ppath2(path, i, j);
				cout << j << endl;
			}
		}
	}
}
void Floyd(MGraph g)
{
	int A[MAXV][MAXV], path[MAXV][MAXV];
	for (auto i = 0; i < g.n; i++)
	{
		for (auto j = 0; j < g.n; j++)
		{
			A[i][j] = g.edge[i][j];
			path[i][j] = -1;
		}
	}
	for (auto k = 0; k < g.n; k++)
	{
		for (auto i = 0; i < g.n; i++)
		{
			for (auto j = 0; j < g.n; j++)
			{
				if (A[i][j]>A[i][k] + A[k][j])
				{
					A[i][j] = A[i][k] + A[k][j];
					path[i][j] = k;
				}
			}
		}
	}
	Dispath2(A, path, g.n);
}
void test_Dijkstra()
{
	int A[MAXV][MAXV] = {
		{ 0, 4, 6, 6, INF, INF, INF },
		{ INF, 0, INF, 7, INF, INF, INF },
		{ INF, INF, 0, INF, 6, 4, INF },
		{ INF, INF, 2, 0, INF, 5, INF },
		{ INF, INF, INF, INF, 0, INF, 6 },
		{ INF, INF, INF, INF, 1, 0, 8 },
		{ INF, INF, INF, INF, INF, INF, 0 }
	};
	MGraph g;
	g.n = 7; g.e = 12;
	for (auto i = 0; i < g.n; i++)
		for (auto j = 0; j < g.n; j++)
			g.edge[i][j] = A[i][j];
	cout << "Dijkstra:" << endl;
	Dijkstra(g, 0); cout << endl;
	cout << "Floyd:" << endl;
	Floyd(g); cout << endl;
}
//拓扑排序
void TopSort(ALGraph *G)
{
	ArcNode *p;
	stack<int> St;
	for (auto i = 0; i < G->n; i++)
		G->adjlist[i].count = 0;
	for (auto i = 0; i < G->n; i++)
	{
		p = G->adjlist[i].firstarc;
		while (p != NULL)
		{
			G->adjlist[p->adjvex].count++;
			p = p->nextarc;
		}
	}
	for (auto i = 0; i < G->n; i++)
		if (G->adjlist[i].count == 0)
			St.push(i);
	while (!St.empty())
	{
		auto tmp = St.top();
		cout << tmp << " ";
		St.pop();
		p = G->adjlist[tmp].firstarc;
		while (p != NULL)
		{
			auto j = p->adjvex;
			G->adjlist[j].count--;
			if (G->adjlist[j].count == 0)
				St.push(j);
			p = p->nextarc;
		}
	}
}
void test_topsort()
{
	int A[MAXV][MAXV] = {
		{ 0, 1, 0, 0, 0, 0 },
		{ 0, 0, 1, 0, 0, 0 },
		{ 0, 0, 0, 1, 0, 0 },
		{ 0, 0, 0, 0, 0, 0 },
		{ 0, 1, 0, 0, 0, 1 },
		{ 0, 0 ,0 ,1, 0, 0 }
	};
	MGraph g;
	ALGraph *G;
	g.n = 6; g.e = 6;
	for (auto i = 0; i < g.n; i++)
		for (auto j = 0; j < g.n; j++)
			g.edge[i][j] = A[i][j];
	MatToList(g, G);
	DispAdj(G);
	cout << "拓扑排序:" << endl;
	TopSort(G);
	cout << endl;
}
int main(){
	int A[MAXV][MAXV] = {
		{0,1,0,1,0},
		{1,0,1,0,0},
		{0,1,0,1,1},
		{1,0,1,0,1},
		{0,0,1,1,0}
	};
	MGraph g;
	ALGraph *G;
	g.n = 5; g.e = 6;
	for (auto i = 0; i < g.n; i++)
		for (auto j = 0; j < g.n; j++)
			g.edge[i][j] = A[i][j];
	MatToList(g, G);
	DispAdj(G);
	for (auto i = 0; i < g.n; i++)
		visited[i] = 0;
	cout<<endl << "DFS: ";
	DFS(G, 0);cout << endl;
	cout << "BFS: ";
	BFS(G, 2); cout << endl;

	//PATHALL
	int path[MAXV], u = 1, v = 4, d = 3;
	for (auto i = 0; i < g.n; i++)
		visited[i] = 0;
	cout << "从" << u << "到" << v << "长度为" << d << "路径为:" << endl;
	PathAll(G, u, v, d, path, -1);
	cout << endl;

	//PRIM Kruskal
	test_Prim_Kruskal();
	//Dijkstra
	test_Dijkstra();
	//拓扑排序
	test_topsort();
	cin.get();
	return 0;
}

