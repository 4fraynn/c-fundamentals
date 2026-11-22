#include <stdio.h>
#include <stdlib.h>

#define MAXN 101

int adj[MAXN][MAXN]; // 버스 노선 저장   
int visited[MAXN]; // 방문 여부 확인   
int N, M; // 방문 여부 확인

void dfs(int node) {
    visited[node] = 1;
    for (int i = 1; i <= N; i++) {
        if (adj[node][i] && !visited[i]) {
            dfs(i);
        }
    }
}

int main() {
    scanf("%d %d", &N, &M);

    // 도달 가능한 지역 수
    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        adj[u][v] = 1;
    }

    int start;
    scanf("%d", &start);

    dfs(start);

    int count = 0;
    for (int i = 1; i <= N; i++) {
        if (visited[i]) count++; // 방문 가능한 지역 수 증가
    }

    printf("%d\n", count);

    return 0;
}



