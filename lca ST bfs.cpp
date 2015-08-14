/*
	author: z52527
	lca ST bfs/dfs
	poj1330
*/
#include <stdio.h>
#include <string.h>
#include <queue>
#include <algorithm>
#define DEG 20//2^20
#define maxn 10010
using namespace std;
struct node 
{
    int v, next;
}a[maxn*2];
int q[4*maxn], fa[maxn][DEG], root, n, m, u, v, tot, first[maxn*2], dis[maxn];
bool flag[maxn];
void addedge(int st, int end)
{
    a[tot].v = end;
    a[tot].next = first[st]; first[st] = tot++;
}
void init()
{
	tot = 0;
	memset(first, -1, sizeof(first));
	memset(flag, 0, sizeof(flag));
}
void bfs(int root)
{
	queue<int >que;
	dis[root] = 0;
	fa[root][0] = root;//root's 2^0 father is root
	que.push(root);
	//q[0] = root;
	//int head = 0,tail = 1;
	while (!que.empty())
	{
		//int u = q[head++];
		int u = que.front();que.pop();
		for (int i = 1; i < DEG; i++)/*the father from 2^1 ~ 2^DEG*/fa[u][i] = fa[fa[u][i-1]][i-1];//u's 2^i father is u's (2^(i-1))^(i-1)
		for (int e = first[u]; e != -1; e = a[e].next)
		{
			int v = a[e].v;
			if (v == fa[u][0])continue;//if u's father is v,continue, it can't vis his fahter
			dis[v] = dis[u] + 1;
			fa[v][0] = u;
			//q[++tail] = v;
			que.push(v);
		}
	}
}
int LCA(int u, int v)
{
	if (dis[u] > dis[v])swap(u, v);
	int du = dis[u], dv = dis[v];
	int tu = u, tv = v;
	for (int det = dv - du, i = 0;det; det>>=1, i++)
		if (det&1)//det if u's high - v's high;
		tv = fa[tv][i];//let deeper point up(2^i) until det = 1;
	if (tu == tv)return tu;
	for (int i = DEG - 1; i >= 0; i--)
	{
		if (fa[tu][i] == fa[tv][i])continue;
		tu = fa[tu][i];
		tv = fa[tv][i];
	}
	return fa[tu][0];
}
int main()
{
	freopen("1.in", "r", stdin);
	freopen("1.out", "w", stdout);
	int T;
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d", &n);
		init();
		for (int i = 1; i < n; i++)
		{
			scanf("%d %d", &u, &v);
			addedge(u, v);addedge(v, u);
			flag[v] = 1;
		}
		int root;
		for (int i = 1; i <= n; i++)
		{
			if (!flag[i])
			{
				root =  i;break;
			}
		}
		bfs(root);//dfs(root);
		scanf("%d %d", &u, &v);
		printf("%d\n", LCA(u,v));
	}
}
