#include<bits/stdc++.h>
using namespace std;



namespace KMP{

	/**
	 * @param s text string.
	 * @param p pattern
	 * @return  array, represent the index of s which can be matched by p.    
	*/
	vector<int> kmp(string s,string p){
		vector<int> prefix(p.size());
		prefix[0]=0;
		for(int i=1;i<p.size();i++){
			int j=prefix[i-1];
			while(j!=0&&p[i]!=p[j])j=prefix[j-1];
			if(p[j]==p[i])j++;
			prefix[i]=j;
		}
		vector<int> ans;
		int j=0;
		for(int i=0;i<s.size();i++){
			while(j!=0&&s[i]!=p[j])j=prefix[j-1];
			if(s[i]==p[j])j++;
			if(j==p.size()){
				ans.push_back(i-j+1);
				j=0;
			}
		}
		return ans;
	}
};

namespace STR_HASH{
	#define ll long long
	const int MOD=1e9+7;
	const int weight=233;

	int qpow(int a,int b,int mod){
		ll res=1;
		//if(mod is prime && gcd(b,mod)==1 && b>=mod-1) b%=(mod-1);
		for(;b;b>>=1,a*=a,a%=mod){
			if(b&1){
				res*=a;
				res%=mod;
			}
		}
		return (int)res;
	}

	vector<int> s_hash_arr(string s){
		vector<int> hash(s.size());
		hash[0]=s[0];
		for(int i=1;i<s.size();i++){
			hash[i]=((ll)hash[i-1]*(ll)weight+s[i])%MOD;
		}
		return hash;
	}

	int get_substr_hash_v(int l,int r,vector<int>& hash){
		return (hash[r]+MOD-((ll)hash[l-1]*qpow(weight,r-l+1,MOD))%MOD)%MOD;
	}

};

namespace TRIE{

	const int MAXN=1e5;
	
	int trie[MAXN][26]={0};
	bool end[MAXN]={0};
	int cnt=0;
	
	void insert_str(string s){
		int p=0;
		for(int i=0;i<s.size();i++){
			if(trie[p][s[i]-'a']==0){
				trie[p][s[i]-'a']=++cnt;
			}
			p=trie[p][s[i]-'a'];
		}
		end[p]=1;
	}

	bool find(string s){
		int p=0;
		for(int i=0;i<s.size();i++){
			if(trie[p][s[i]-'a']==0){
				return false;
			}
			p=trie[p][s[i]-'a'];
		}
		return end[p];
	}

}

namespace MANACHER{
	
}

namespace AC{

}

