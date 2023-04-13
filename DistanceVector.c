#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODES 10
#define INFINITY 99999

int graph[MAX_NODES][MAX_NODES];
int next_hop[MAX_NODES][MAX_NODES];

void initialize(int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                graph[i][j] = 0;
            } else {
                graph[i][j] = INFINITY;
            }
            next_hop[i][j] = j;
        }
    }
}

void update_table(int node, int n) {
    for (int i = 0; i < n; i++) {
        if (i == node) {
            continue;
        }
        for (int j = 0; j < n; j++) {
            if (j == node || j == i) {
                continue;
            }
            if (graph[i][node] + graph[node][j] < graph[i][j]) {
                graph[i][j] = graph[i][node] + graph[node][j];
                next_hop[i][j] = next_hop[i][node];
            }
        }
    }
}

void print_table(int n) {
    printf("\nDistance Vector Table:\n");
    for (int i = 0; i < n; i++) {
        printf("Node %d:\n", i);
        for (int j = 0; j < n; j++) {
            printf("    -> Node %d: Distance=%d, Next Hop=%d\n", j, graph[i][j], next_hop[i][j]);
        }
    }
}

int main() {
    int n;
    printf("Enter the number of nodes in the network: ");
    scanf("%d", &n);

    initialize(n);

    printf("Enter the network topology:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int d;
            printf("Distance from node %d to node %d (Enter -1 if no connection): ", i, j);
            scanf("%d", &d);
            if (d != -1) {
                graph[i][j] = d;
            }
        }
    }

    int iterations = 0;
    int changed = 1;
    while (changed && iterations < n) {
        changed = 0;
        for (int i = 0; i < n; i++) {
            int min_dist = INFINITY;
            for (int j = 0; j < n; j++) {
                if (graph[i][j] < min_dist) {
                    min_dist = graph[i][j];
                }
            }
            if (min_dist == INFINITY) {
                continue;
            }
            if (min_dist != graph[i][i]) {
                graph[i][i] = min_dist;
                next_hop[i][i] = i;
                update_table(i, n);
                changed = 1;
            }
        }
        iterations++;
    }

    print_table(n);

    return 0;
}
