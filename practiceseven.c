#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 2005
#define MAX_NODES (2 * MAX_N)

typedef struct {
    long long weight;
    int minIndex;
    int id;
    int left;
    int right;
    int parent;
} Node;

Node nodes[MAX_NODES];
int node_count = 0;

int heap[MAX_NODES];
int heap_size = 0;

char b_str[250000]; 
int code_stack[MAX_NODES];

int compare_nodes(int u, int v) {
    if (nodes[u].weight != nodes[v].weight) {
        return nodes[u].weight < nodes[v].weight ? 1 : 0;
    }
    if (nodes[u].minIndex != nodes[v].minIndex) {
        return nodes[u].minIndex < nodes[v].minIndex ? 1 : 0;
    }
    return nodes[u].id < nodes[v].id ? 1 : 0;
}

void heap_push(int node_idx) {
    int i = ++heap_size;
    while (i > 1 && compare_nodes(node_idx, heap[i / 2])) {
        heap[i] = heap[i / 2];
        i /= 2;
    }
    heap[i] = node_idx;
}

int heap_pop() {
    int res = heap[1];
    int last = heap[heap_size--];
    int i = 1, child = 2;
    while (child <= heap_size) {
        if (child < heap_size && compare_nodes(heap[child + 1], heap[child])) {
            child++;
        }
        if (compare_nodes(last, heap[child])) break;
        heap[i] = heap[child];
        i = child;
        child *= 2;
    }
    heap[i] = last;
    return res;
}

int get_height(int root) {
    if (root == 0) return -1;
    if (nodes[root].left == 0 && nodes[root].right == 0) return 0;
    int lh = get_height(nodes[root].left);
    int rh = get_height(nodes[root].right);
    return (lh > rh ? lh : rh) + 1;
}

void print_preorder(int root, int *is_first) {
    if (root == 0) return;
    
    if (*is_first) *is_first = 0;
    else printf(" ");

    if (nodes[root].left == 0 && nodes[root].right == 0) {
        printf("%d", nodes[root].minIndex);
    } else {
        printf("#");
        print_preorder(nodes[root].left, is_first);
        print_preorder(nodes[root].right, is_first);
    }
}

void print_huffman_code(int x) {
    int top = 0;
    int curr = x;
    while (nodes[curr].parent != 0) {
        int p = nodes[curr].parent;
        if (nodes[p].left == curr) code_stack[top++] = 0;
        else code_stack[top++] = 1;
        curr = p;
    }
    for (int i = top - 1; i >= 0; i--) {
        printf("%d", code_stack[i]);
    }
    printf("\n");
}

int get_code_length(int x) {
    int len = 0;
    int curr = x;
    while (nodes[curr].parent != 0) {
        len++;
        curr = nodes[curr].parent;
    }
    return len;
}

int main() {
    // 백준 등 채점 서버에서 C언어 표준 입출력 속도를 높이기 위한 설정입니다.
    setvbuf(stdout, NULL, _IOFBF, 4096);

    int n, q;
    if (scanf("%d %d", &n, &q) != 2) return 0;

    for (int i = 1; i <= n; i++) {
        scanf("%lld", &nodes[i].weight);
        nodes[i].minIndex = i;
        nodes[i].id = i;
        nodes[i].left = 0;
        nodes[i].right = 0;
        nodes[i].parent = 0;
        heap_push(i);
    }
    node_count = n;

    for (int step = 1; step < n; step++) {
        int left_child = heap_pop();
        int right_child = heap_pop();

        int new_id = n + step;
        node_count++;

        nodes[new_id].weight = nodes[left_child].weight + nodes[right_child].weight;
        nodes[new_id].minIndex = (nodes[left_child].minIndex < nodes[right_child].minIndex) ? 
                                  nodes[left_child].minIndex : nodes[right_child].minIndex;
        nodes[new_id].id = new_id;
        nodes[new_id].left = left_child;
        nodes[new_id].right = right_child;
        nodes[new_id].parent = 0;

        nodes[left_child].parent = new_id;
        nodes[right_child].parent = new_id;

        heap_push(new_id);
    }

    int root = heap[1];
    int height = get_height(root);

    long long total_bits = 0;
    for (int i = 1; i <= n; i++) {
        total_bits += nodes[i].weight * get_code_length(i);
    }

    // 첫째 줄 출력
    printf("%d %lld\n", height, total_bits);

    // 둘째 줄 출력 (공백 형식 엄격히 제한)
    int is_first = 1;
    print_preorder(root, &is_first);
    printf("\n");

    // 질의 처리
    for (int i = 0; i < q; i++) {
        int q_type;
        if (scanf("%d", &q_type) != 1) break;

        if (q_type == 1) {
            int x;
            scanf("%d", &x);
            print_huffman_code(x);
        } 
        else if (q_type == 2) {
            int k;
            scanf("%d", &k);
            long long query_bits = 0;
            for (int j = 0; j < k; j++) {
                int log_idx;
                scanf("%d", &log_idx);
                query_bits += get_code_length(log_idx);
            }
            printf("%lld\n", query_bits);
        } 
        else if (q_type == 3) {
            scanf("%s", b_str);
            int curr = root;
            int len = strlen(b_str);
            int first_out = 1;
            
            for (int j = 0; j < len; j++) {
                if (b_str[j] == '0') curr = nodes[curr].left;
                else curr = nodes[curr].right;

                if (nodes[curr].left == 0 && nodes[curr].right == 0) {
                    if (first_out) first_out = 0;
                    else printf(" ");
                    
                    printf("%d", nodes[curr].minIndex);
                    curr = root;
                }
            }
            printf("\n");
        }
    }

    return 0;
}