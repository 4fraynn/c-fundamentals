#include <stdio.h>
#include <stdlib.h>

#define MAXN 100000
#define MAXM 300000
#define INF 4000000000000000000LL

typedef long long ll;

typedef struct Edge {
    int to;
    int weight;
    int next;
} Edge;

typedef struct Node {
    int v;
    int used;
    ll dist;
} Node;

Edge edges[MAXM + 5];
int head[MAXN + 5];
int edgeCount = 0;

ll distArr[MAXN + 5][2];

Node heap[(MAXM * 4) + 10];
int heapSize = 0;

void addEdge(int u, int v, int w) {
    edges[edgeCount].to = v;
    edges[edgeCount].weight = w;
    edges[edgeCount].next = head[u];
    head[u] = edgeCount++;
}

void swap(Node *a, Node *b) {
    Node temp = *a;
    *a = *b;
    *b = temp;
}

void push(Node x) {
    heap[++heapSize] = x;

    int i = heapSize;
    while (i > 1 && heap[i].dist < heap[i / 2].dist) {
        swap(&heap[i], &heap[i / 2]);
        i /= 2;
    }
}

Node pop() {
    Node ret = heap[1];
    heap[1] = heap[heapSize--];

    int i = 1;
    while (1) {
        int left = i * 2;
        int right = i * 2 + 1;
        int smallest = i;

        if (left <= heapSize && heap[left].dist < heap[smallest].dist)
            smallest = left;
        if (right <= heapSize && heap[right].dist < heap[smallest].dist)
            smallest = right;

        if (smallest == i) break;

        swap(&heap[i], &heap[smallest]);
        i = smallest;
    }

    return ret;
}

int main() {
    int N, M, S;
    scanf("%d %d %d", &N, &M, &S);

    for (int i = 1; i <= N; i++) {
        head[i] = -1;
        distArr[i][0] = INF;
        distArr[i][1] = INF;
    }

    for (int i = 0; i < M; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        addEdge(u, v, w);
    }

    distArr[S][0] = 0;
    distArr[S][1] = 0;

    push((Node){S, 0, 0});
    push((Node){S, 1, 0});

    while (heapSize > 0) {
        Node cur = pop();

        int u = cur.v;
        int used = cur.used;
        ll nowDist = cur.dist;

        if (nowDist != distArr[u][used]) continue;

        for (int e = head[u]; e != -1; e = edges[e].next) {
            int v = edges[e].to;
            int w = edges[e].weight;

            // 1. 무료 통행권을 사용하지 않고 일반 이동
            if (distArr[v][used] > nowDist + w) {
                distArr[v][used] = nowDist + w;
                push((Node){v, used, distArr[v][used]});
            }

            // 2. 아직 무료 통행권을 사용하지 않았다면 이번 간선을 무료로 이동
            if (used == 0 && distArr[v][1] > nowDist) {
                distArr[v][1] = nowDist;
                push((Node){v, 1, distArr[v][1]});
            }
        }
    }

    for (int i = 1; i <= N; i++) {
        ll ans = distArr[i][0] < distArr[i][1] ? distArr[i][0] : distArr[i][1];

        if (ans == INF)
            printf("-1\n");
        else
            printf("%lld\n", ans);
    }

    return 0;
}