//from pks

#include<bits/stdc++.h>
using namespace std;
#define ll long long
inline ll read() {char ch = getchar(); ll x = 0, f = 1;while(ch < '0' || ch > '9') {if(ch == '-') f = -1;ch = getchar();}while('0' <= ch && ch <= '9') {x = x * 10 + ch - '0';ch = getchar();} return x * f;}
int fastmi(int i,int b,const int &p){ll ans=1,now=i;while (b)	{if (b&1)  ans=now*ans%p;now=now*now%p;b>>=1;}return ans;}
int ra(int low,int hi){return rand()%(hi-low+1)+low;}
void assi(){
	freopen("1.in","r",stdin);
	}
const int N=5e5;
int a[N],dp[N],V[N],Q[N],bac[N];
int nowl,nowr,now1l,now1i,now1r,MI;
int main(){
	//assi();
	int n=read();
	for (int i=1;i<=n;i++) a[i]=read();
	for (int i=n;(i);--i) bac[i]=bac[i+1]+a[i];
	nowl=0;
	nowr=0;
	for (int i=n;(i);--i)
	{
		if (bac[i]>=MI)
		{
			now1l=nowl;
			now1r=nowr;
			dp[i]=dp[now1l]+1;
			for (int j=nowl;j<nowr;j++)
				Q[j+1]=min(Q[j+1],Q[j]);
			for (int j=nowr;j>=nowl;--j)
			if (bac[i]>=Q[j])
			{
				V[i]=bac[i]-bac[j];
				now1i=j;
			}
			Q[i]=bac[i]+V[i];
			nowl=i;
			nowr=i;	
			MI=Q[i];
		}
		else
		{
			while (now1i>now1l && bac[i]>=Q[now1i]) now1i--;
			V[i]=bac[i]-bac[now1i];
			Q[i]=bac[i]+V[i];
			MI=min(MI,Q[i]);
			dp[i]=dp[now1i]+1;
			nowl=i;
		}
	}
/*	for (int i=1;i<=n;i++)
		printf("%d %d %d\n",i,dp[i],V[i]);*/
	printf("%d",dp[1]);
}
