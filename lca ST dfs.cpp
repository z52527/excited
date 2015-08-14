//poj1330
#include <stdio.h>
#include <string.h>
#include <queue>
#include <algorithm>
using namespace std; 
#define N 10010  
#define M 20  
int d[N],f[N][M]; 
vector<int>ch[N]; 
void dfs(int x){//求出所有结点深度  
    d[x]=d[f[x][0]]+1; 
    for(int i=1;i<M;i++)f[x][i]=f[f[x][i-1]][i-1];//倍增祖先  
    for(int i=ch[x].size()-1;i>=0;i--) 
        dfs(ch[x][i]);//遍历儿子  
} 
int lca(int x,int y){//求x,y最小公共祖先  
        if(d[x]<d[y])swap(x,y);//保证x的深度不小于y  
        int k=d[x]-d[y]; 
        for(int i=0;i<M;i++) 
            if((1<<i)&k) 
                x=f[x][i]; 
    if(x==y)return x;//x==y时为最小公共祖先  
        for(int i=M-1;i>=0;i--) 
            if(f[x][i]!=f[y][i]){ 
                x=f[x][i];y=f[y][i]; 
            } 
    return f[x][0]; 
} 
int main(){ 
    int T,n,i,x,y; 
    scanf("%d",&T); 
    while(T--){ 
        scanf("%d",&n); 
        memset(d,0,sizeof(d)); 
        memset(f,0,sizeof(f)); 
        memset(ch,0,sizeof(ch)); 
        for(i=1;i<n;i++){ 
            scanf("%d%d",&x,&y); 
            ch[x].push_back(y); 
            f[y][0]=x; 
        } 
        for(i=1;i<=n;i++) 
            if(f[i][0]==0){//找到根遍历  
                dfs(i);break; 
            } 
            scanf("%d%d",&x,&y); 
            printf("%d\n",lca(x,y)); 
    } 
return 0; 
} 
