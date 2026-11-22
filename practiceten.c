#include <stdio.h>
#include <stdlib.h>

#define INF 2000000000000LL // s의 범위를 고려해 충분히 큰 값 설정

// 트리 노드 구조체 정의
typedef struct {
    int k;             
    int *children;     
    long long score;   
    int level;         
    long long leaf_cnt;
    int best_child;    
} Node;

Node tree[200005];

// 1단계: DFS를 통해 각 노드의 레벨을 계산합니다.
void compute_levels(int u, int current_level) {
    tree[u].level = current_level;
    for (int i = 0; i < tree[u].k; i++) {
        compute_levels(tree[u].children[i], current_level + 1);
    }
}

// 2단계: DFS(후위 순회)를 통해 Minimax 값과 최적 리프 노드 수를 계산합니다.
void compute_minimax(int u) {
    // 리프 노드인 경우 기본값 세팅
    if (tree[u].k == 0) {
        tree[u].leaf_cnt = 1;
        tree[u].best_child = -1;
        return;
    }

    // 자식 노드들을 먼저 계산 (Bottom-up)
    for (int i = 0; i < tree[u].k; i++) {
        compute_minimax(tree[u].children[i]);
    }

    int is_max_node = (tree[u].level % 2 == 0);
    long long opt_val = is_max_node ? -INF : INF;
    long long total_leaves = 0;
    int best_c = -1;

    // 1. 최적의 Minimax 값 찾기
    for (int i = 0; i < tree[u].k; i++) {
        int v = tree[u].children[i];
        if (is_max_node) {
            if (tree[v].score > opt_val) opt_val = tree[v].score;
        } else {
            if (tree[v].score < opt_val) opt_val = tree[v].score;
        }
    }
    tree[u].score = opt_val;

    // 2. 최적값을 가지는 자식들의 리프 개수 합산 및 대표 자식 선정
    for (int i = 0; i < tree[u].k; i++) {
        int v = tree[u].children[i];
        if (tree[v].score == opt_val) {
            total_leaves += tree[v].leaf_cnt;
            // 번호가 가장 작은 자식을 대표 자식으로 선택
            if (best_c == -1 || v < best_c) {
                best_c = v;
            }
        }
    }
    tree[u].leaf_cnt = total_leaves;
    tree[u].best_child = best_c;
}

int main() {
    int n, q;
    if (scanf("%d %d", &n, &q) != 2) return 0;

    // 트리 입력 받기
    for (int i = 1; i <= n; i++) {
        int k;
        scanf("%d", &k);
        tree[i].k = k;
        if (k > 0) {
            tree[i].children = (int *)malloc(sizeof(int) * k);
            for (int j = 0; j < k; j++) {
                scanf("%d", &tree[i].children[j]);
            }
        } else {
            long long s;
            scanf("%lld", &s);
            tree[i].score = s;
            tree[i].children = NULL;
        }
    }

    compute_levels(1, 0);
    compute_minimax(1);

    printf("%lld\n", tree[1].score);

    int path_len = 0;
    int curr = 1;
    while (curr != -1) {
        path_len++;
        curr = tree[curr].best_child;
    }
    printf("%d", path_len);
    
    curr = 1;
    while (curr != -1) {
        printf(" %d", curr);
        curr = tree[curr].best_child;
    }
    printf("\n");
    printf("%lld\n", tree[1].leaf_cnt);

    for (int i = 0; i < q; i++) {
        int u;
        scanf("%d", &u);
        printf("%lld %lld\n", tree[u].score, tree[u].leaf_cnt);
    }
    for (int i = 1; i <= n; i++) {
        if (tree[i].children != NULL) {
            free(tree[i].children);
        }
    }

    return 0;
}