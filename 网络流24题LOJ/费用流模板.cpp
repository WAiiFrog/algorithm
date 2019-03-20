#include <bits/stdc++.h>

const int MAXN = 1000000, INF = 1000000000;

using namespace std;

int n, m, s, t, e = 2;
int head[MAXN], pri[MAXN];
long long dis[MAXN];
bool inq[MAXN];

struct node {
    int v, w, c, f, next;
} edge[MAXN];

inline void addedge(int u, int v, int w, int c) {
    edge[e] = (node){ v, w, c, 0, head[u] };
    head[u] = e++;
    edge[e] = (node){ u, -w, 0, 0, head[v] };
    head[v] = e++;
}

inline void init() {
    scanf("%d %d", &n, &m);
    s = 1;
    t = n;
    int u, v, w, c;
    for (int i = 1; i <= m; i++) {
        scanf("%d %d %d %d", &u, &v, &c, &w);
        addedge(u, v, w, c);
    }
}

queue<int> Q;
inline bool spfa() {
    for (int i = s; i <= t; i++) {
        inq[i] = false;
        dis[i] = INF;
        pri[i] = 0;
    }
    Q.push(s);
    dis[s] = 0;
    inq[s] = true;
    while (!Q.empty()) {
        int x = Q.front();
        Q.pop();
        inq[x] = false;
        for (int i = head[x]; i; i = edge[i].next) {
            node E = edge[i];
            if (dis[E.v] > dis[x] + (long long)E.w && E.c > E.f) {
                dis[E.v] = dis[x] + (long long)E.w;
                pri[E.v] = i;
                if (!inq[E.v]) {
                    Q.push(E.v);
                    inq[E.v] = true;
                }
            }
        }
    }
    return pri[t] ? true : false;
}

inline void MCMF() {
    int cost = 0, flow = 0, tmp;
    while (spfa()) {
        int tmp = INF;
        for (int i = pri[t]; i; i = pri[edge[i ^ 1].v]) tmp = min(tmp, edge[i].c - edge[i].f);
        for (int i = pri[t]; i; i = pri[edge[i ^ 1].v]) {
            edge[i].f += tmp;
            edge[i ^ 1].f -= tmp;
            cost += tmp * edge[i].w;
        }
        flow += tmp;
    }
    printf("%d %d", flow, cost);
}

int main() {
#ifdef hi_archer
    freopen("input.txt", "r", stdin);
#endif
    init();
    MCMF();
    return 0;
}

