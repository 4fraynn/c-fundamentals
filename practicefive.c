#include <stdio.h>

#define MAX 100
#define INF 1000000000

int n;
int graph[MAX][MAX];

int visited[MAX];
int parent[MAX];
int key[MAX];

int mst_adj[MAX][MAX];  // MST 저장

void prim() {
    for (int i = 0; i < n; i++) {
        key[i] = INF;
        visited[i] = 0;
        parent[i] = -1;
    }

    key[0] = 0;  // 시작 노드

    for (int count = 0; count < n - 1; count++) {
        int u = -1, min = INF;

        for (int i = 0; i < n; i++) {
            if (!visited[i] && key[i] < min) {
                min = key[i];
                u = i;
            }
        }

        visited[u] = 1;

        for (int v = 0; v < n; v++) {
            if (graph[u][v] && !visited[v] && graph[u][v] < key[v]) {
                key[v] = graph[u][v];
                parent[v] = u;
            }
        }
    }

    // MST adjacency matrix 생성
    for (int i = 1; i < n; i++) {
        int u = parent[i];
        int v = i;
        mst_adj[u][v] = mst_adj[v][u] = 1;
    }
}

void dfs(int u, int visited2[], int path[], int *idx) {
    visited2[u] = 1;
    path[(*idx)++] = u;

    for (int v = 0; v < n; v++) {
        if (mst_adj[u][v] && !visited2[v]) {
            dfs(v, visited2, path, idx);
        }
    }
}

int main() {
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    prim();

    // MST 출력
    printf("MST: ");
    for (int i = 1; i < n; i++) {
        printf("(%d, %d) ", parent[i], i);
    }
    printf("\n");

    int visited2[MAX] = {0};
    int path[MAX];
    int idx = 0;

    dfs(0, visited2, path, &idx);

    // 시작점으로 돌아오기
    path[idx++] = 0;

    printf("방문 경로: ");
    for (int i = 0; i < idx; i++) {
        printf("%d ", path[i]);
    }

    return 0;
}
