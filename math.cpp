#include<bits/stdc++.h>
using namespace std;

namespace QPOW{
	#define ll long long
	//快速幂
	ll qpow(ll a,ll b,ll mod){
		ll res=1;
		for(;b;b>>=1,a*=a,a%=mod){
			if(b&1){
				res*=a;
				res%=mod;
			}
		}
		return res;
	}
}

namespace FIND_SIFT{
	//线性筛
	vector<bool> mark;
	vector<int> prime;
	//find primes which is not greater than n;
	void Euler_sift(int n) {
		mark.resize(n + 1);
		for (int i = 2; i <= n; i++) {
			if (!mark[i])prime.push_back(i);
			for (int j = 0; prime[j] <= n / i; j++) {
				mark[i * prime[j]] = 1;
				if (i % prime[j] == 0)break;
			}
		}
		return;
	}

}

namespace GCD{
	#define ll long long

	//greatest common devisor
	int gcd(int a,int b){
		return b==0?a:gcd(b,a%b);
	}

	//leastest commom multiple
	int lcm(int a,int b){
		return a/gcd(a,b)*b;
	}

	/*
	(1)... ax+by==gcd(a,b);
	(2)... bx1+a%by1==gcd(b,a%b);  (using Euclidean algorithm)
	(3)... gcd(a,b)==gcd(b,a%b);  (Euclidean algorithm)
	(4)... ax+by==bx1+a%b*y1;  (a%b==(a-a/b*b))
	(5)... ax+by==bx1+ay1-a/b*by1;
	(6)... ax+by==ay1+b(x1-a/b*y1);  (Consolidated Likes)
	(7)... x==y1,y==x1-a/b*y1;  (Conclusion)
	*/
	ll exgcd(ll a, ll b, ll& x, ll& y) {
		if (b == 0) {
			x = 1;
			y = 0;
			return a;
		}
		ll d = exgcd(b, a % b, y, x);
		y -= a / b * x;
		return d;
	}

	//贝祖定理： if(a,x,b,y 全为整数, ax+by=c) then gcd(a,b)|c;
	void Bezout_lemma(ll a,ll b,ll& x,ll& y,ll c){
		ll d=exgcd(a,b,x,y);
		c/=d,x*=c,y*=c;
		//任意解：x+=k*b/d, y-=k*a/d;
		return ;
	}

}

namespace Euler_totient_function{
	//公式求欧拉函数
	int direct_phi(int n)
	{
		int res = n;
		for (int i = 2; i * i <= n; i++) {
			if (n % i == 0) {
				res = res / i * (i - 1);
				while (n % i == 0) {
					n /= i;
				}
			}
		}
		if(n!=1)res=res/n*(n-1);
		return res;
	}

	//线性筛求欧拉函数
	const int MAXN=1e5;
	int mark[MAXN];
	int prime[MAXN];
	int phi[MAXN];
	int Euler_phi(int n) {
		int cnt = -1;
		for (int i = 2; i <= n; i++) {
			if (!mark[i]) {
				prime[++cnt] = i;
				phi[i] = i - 1;
			}
			for (int j = 0; prime[j] <= n / i; j++) {
				mark[i * prime[j]] = 1;
				if (i % prime[j] == 0) {
					phi[i * prime[j]] = prime[j] * phi[i];
					break;
				}
				phi[i * prime[j]] = phi[i] * phi[prime[j]];
			}
		}
		return;
	}
}

namespace Mod_Multi_Inv{
	#define ll long long
	using namespace GCD;
	using namespace QPOW;
	

	// gcd 求逆元
	ll gcd_inv(ll a,ll mod){
		ll x,y;
		ll d=exgcd(a,mod,x,y);
		if(d!=1)return -1;
		return x;
	}

	//if(mod is prime&& gcd(a,mod)==1)
	ll fermat_inv(ll a,ll mod){
		return qpow(a,mod-2,mod);
	}

	//the inverse of number which below and equal than n
	vector<ll> indective_inv(ll n,ll mod){
		vector<ll> inv(n+1);
		inv[1]=1;
		for(int i=2;i<=n;i++){
			inv[i]=(ll)(mod-mod/i)*inv[mod%i]%mod;
		}
		return inv;
	}

}

namespace CRT{
	using namespace Mod_Multi_Inv;
	

	#define ll long long
	//中国剩余定理
	ll crt(vector<ll> a,vector<ll> p){
		assert(a.size()==p.size());
		int n=a.size();
		ll M=1;
		ll ans=0;
		for(int i=0;i<n;i++){
			M*=p[i];
		}
		for(int i=0;i<n;i++){
			ll tm=M/p[i];
			ans+=tm*gcd_inv(tm,p[i])%M*a[i]%M;
			ans%=M;
		}
		return ans;
	}
	//扩展中国剩余定理
	ll excrt(vector<ll> a,vector<ll> m) {
    int n = a.size();
    ll ans=a[0];
    ll M = m[0];
    for (int i = 1; i < n; i++) {
        ll x, y;
        ll d = GCD::exgcd(M, m[i], x, y);
        if ((a[i] - ans) % d) {
            return -1;
        }
        m[i] /= d;
        x = (((a[i] - ans) / d ) % m[i] * x) % m[i];
        if (x < 0)x += m[i];
        ans = (M * x + ans) % (M * m[i]);
        M *= m[i];
    }
    return ans;
}
}

namespace COMBINATION
{
	#define ll long long

	//暴力组合
	ll combine(ll n,ll m){
		ll ans=1;
		for(int i=n-m+1;i<=n;i++){
			ans*=i;
		}
		for(int i=1;i<=m;i++){
			ans/=i;
		}
		return ans;
	}

	//卢卡斯定理
	int Lucas_Combine(int n,int m,int p){
		if(n<p&&m<p)return combine(n,m);
		return (ll)Lucas_Combine(n/p,m/p,p)*combine(n%p,m%p)%p;

	}
} 

