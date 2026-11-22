#include <stdio.h>
#include <stdlib.h>

// 간선 정보를 담는 구조체
typedef struct {
    int u, v, w;
} Edge;

// Disjoint-Set(Union-Find)을 위한 배열
int parent[100001];

// qsort를 위한 간선 가중치 오름차순 비교 함수
int compare(const void* a, const void* b) {
    Edge* edgeA = (Edge*)a;
    Edge* edgeB = (Edge*)b;
    if (edgeA->w != edgeB->w) {
        return edgeA->w - edgeB->w;
    }
    // 가중치가 같을 경우 문제 조건에 맞춰 u나 v 기준으로 정렬할 수도 있으나,
    // 일반적인 MST에서는 가중치 오름차순이 핵심입니다.
    if (edgeA->u != edgeB->u) {
        return edgeA->u - edgeB->u;
    }
    return edgeA->v - edgeB->v;
}

// Find 연산 (경로 압축 포함)
int findParent(int i) {
    if (parent[i] == i)
        return i;
    return parent[i] = findParent(parent[i]);
}

// Union 연산
void unionSets(int i, int j) {
    int rootI = findParent(i);
    int rootJ = findParent(j);
    if (rootI != rootJ) {
        parent[rootI] = rootJ;
    }
}

int main() {
    int n, m;
    if (scanf("%d %d", &n, &m) != 2) return 0;

    // 간선 배열 동적 할당
    Edge* edges = (Edge*)malloc(sizeof(Edge) * m);
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);
    }

    // 1. 간선들을 가중치 기준으로 오름차순 정렬
    qsort(edges, m, sizeof(Edge), compare);

    // Union-Find 부모 배열 초기화 (0번 정점부터 n번 정점까지)
    for (int i = 0; i <= n; i++) {
        parent[i] = i;
    }

    // MST에 포함된 간선들을 저장할 배열
    Edge* mstEdges = (Edge*)malloc(sizeof(Edge) * n);
    int mstEdgeCount = 0;
    int totalWeight = 0;

    // 2. 가중치가 낮은 간선부터 보면서 사이클을 만들지 않으면 선택
    for (int i = 0; i < m; i++) {
        // 정점 개수가 n개이면 MST의 간선은 n-1개(정점이 0부터 시작하므로 최대 n개 선택 가능할 수 있음)
        // 안전하게 모든 간선을 순회하며 체크합니다.
        int rootU = findParent(edges[i].u);
        int rootV = findParent(edges[i].v);

        // 부모가 다르다면 사이클이 생기지 않으므로 선택
        if (rootU != rootV) {
            unionSets(rootU, rootV);
            mstEdges[mstEdgeCount++] = edges[i];
            totalWeight += edges[i].w;
        }
    }

    // 3. 출력 형식에 맞춰 가중치 오름차순으로 선택된 간선 출력
    // 이미 정렬된 edges 배열을 순서대로 순회하며 선택했기 때문에 mstEdges도 자동 정렬되어 있습니다.
    for (int i = 0; i < mstEdgeCount; i++) {
        printf("%d %d %d\n", mstEdges[i].u, mstEdges[i].v, mstEdges[i].w);
    }

    // 총 가중치 출력
    printf("%d\n", totalWeight);

    // 메모리 해제
    free(edges);
    free(mstEdges);

    return 0;
}
