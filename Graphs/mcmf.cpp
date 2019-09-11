#include <bits/stdc++.h>
using namespace std;

#define INF
#define MAXN
#define mp make_pair

typedef pair<int, int> pii;

struct edge {
    int to, cap, cost, rev;
    edge(int _to, int _cap, int _cost, int _rev): to(_to), cap(_cap), cost(_cost), rev(_rev) {}
};

struct mcmf {
    // REMEMBER to check if long long is needed and if INF value is enough
    int dist[MAXN];
    vector<edge> graph[MAXN];
    int pre[MAXN], pre_e[MAXN], inq[MAXN];

    mcmf() {
        fill(graph, graph+MAXN, vector<edge>());
    }

    void add(int from, int to, int cap, int cost) {
        graph[from].push_back(edge(to, cap, cost, graph[to].size()));
        graph[to].push_back(edge(from, 0, -cost, graph[from].size()-1));
    }

    bool bfs(int source, int sink) {
        fill(dist, dist+MAXN, INF);
        fill(inq, inq+MAXN, 0);

        dist[source] = 0;
        queue<int> q;
        q.push(source);
        while( not q.empty() ) {
            int u = q.front();
            q.pop();

            inq[u] = 0;
            for(int i = 0; i < (int) graph[u].size(); i++) {
                int v = graph[u][i].to;
                int w = graph[u][i].cost;
                if(graph[u][i].cap > 0 && dist[v] > dist[u]+w) {
                    pre[v] = u;
                    pre_e[v] = i;
                    dist[v] = dist[u] + w;
                    if(!inq[v]){
                        inq[v] = true;
                        q.push(v);
                    }
                }
            }
        }

        return dist[sink] != INF;
    }

    pii flow(int source, int sink){
        int maxFlow = 0, minCost = 0;

        while( bfs(source, sink) ){
            int flowSent = INF;
            for(int v = sink, u, l; v != source; v = u) {
                u = pre[v];
                l = pre_e[v];
                flowSent = min(flowSent, graph[u][l].cap);
            }

            for(int v = sink, u, l; v != source; v = u) {
                u = pre[v];
                l = pre_e[v];
                graph[u][l].cap -= flowSent;
                graph[v][graph[u][l].rev].cap += flowSent;
            }

            minCost += flowSent * dist[sink];
            maxFlow += flowSent;
        }
        return mp(maxFlow, minCost);
    }
};