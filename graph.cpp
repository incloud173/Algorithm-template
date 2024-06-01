#include<bits/stdc++.h>
using namespace std;

namespace REPRESENT_GRAPH{
	struct edg {
		int to;
		int w;
		int next;
		edg(int _t, int _w, int _n) :to(_t), w(_w), next(_n) {};
	};
	struct e {
		int from;
		int to;
		int w;
	};
	vector<int> head;
	vector<edg> edgs;
	vector<e> es;

	int n;//点的数量
	int m;//边的数量

	void add(int from,int to,int w) {
		edgs.push_back(edg(to, w, head[from]));
		head[from] = edgs.size() - 1;
		return;
	}
	void initial() {
		head.resize(n);
		for (e e1 : es) {
			add(e1.from, e1.to, e1.w);
			//add(e1.to, e1.from, e1.w);undirected graph
		}
		return;
	}
}

namespace SHORTEST_PATH{
	using namespace REPRESENT_GRAPH;
	vector<int> dis;

	//堆优化的 Dijkstra 算法
	void Dijkstra() {
		priority_queue<pair<int,int>,vector<pair<int, int>>, greater<int> > heap;
		vector<bool> vis(n);
		heap.push({0,0});
		while (heap.size()) {
			pair<int,int> t = heap.top();
			heap.pop();
			if (vis[t.second])continue;
			vis[t.second]=1;
			for (int p = head[t.second]; p != -1; p = edgs[p].next) {
				if (dis[edgs[p].to] > dis[t.second] + edgs[p].w) {
					dis[edgs[p].to] = dis[t.second] + edgs[p].w;
					heap.push({ dis[edgs[p].to] ,edgs[p].to });
				}
			}
		}
		return;
	}

	// calculate min distance to given vertice :can judge Negative weight ring;
	void Bellman_Ford(){
		for (int i = 0; i < n-1; i++) {
			for (int j = 0; j < m; j++) {
				if (dis[es[j].to] > dis[es[j].from] + es[j].w) {
					dis[es[j].to] = dis[es[j].from] + es[j].w;
				}
			}
		}
	}


	//the optimization of bellman-ford algorithm 
	void spfa()
	{
		dis.resize(head.size(),INT_MAX);
		dis[0] = 0;
		queue<int> que;
		vector<bool> inque(dis.size(),false);
		que.push(0);
		while (que.size()) {
			int t = que.front();
			que.pop();
			inque[t] = 0;
			for (int p = head[t]; p != -1; p = edgs[p].next) {
				if (dis[t] + edgs[p].w < dis[edgs[p].to]) {
					dis[edgs[p].to] = dis[t] + edgs[p].w;
					if (!inque[edgs[p].to]) {
						que.push(edgs[p].to);
						inque[edgs[p].to] =1;
					}
				}
			}
		}
	}

	//calculate min distance between any vertices.
	void Floyd() {
		vector<vector<int>> dis;
		for (int k = 0; k < n; k++) {
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
				}
			}
		}
		return;
	}

}
