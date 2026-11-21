#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

typedef struct AdjNode {
    int dest;
    int weight;
    struct AdjNode *next;
} AdjNode;

typedef struct {
    int num_vertices;
    AdjNode **head;
} AdjGraph;

typedef struct {
    int vertex;
    int dist;
} HeapItem;

typedef struct {
    int size;
    int capacity;
    int *pos; // Position of vertex in heap array for decrease-key
    HeapItem *array;
} MinHeap;

AdjGraph* graph_create(int v) {
    AdjGraph *g = malloc(sizeof(AdjGraph));
    g->num_vertices = v;
    g->head = calloc((size_t)v, sizeof(AdjNode*));
    return g;
}

void graph_add_edge(AdjGraph *g, int src, int dest, int weight) {
    AdjNode *node = malloc(sizeof(AdjNode));
    node->dest = dest;
    node->weight = weight;
    node->next = g->head[src];
    g->head[src] = node;
}

MinHeap* heap_create(int capacity) {
    MinHeap *h = malloc(sizeof(MinHeap));
    h->pos = malloc(sizeof(int) * (size_t)capacity);
    h->size = 0;
    h->capacity = capacity;
    h->array = malloc(sizeof(HeapItem) * (size_t)capacity);
    return h;
}

void heap_swap(MinHeap *h, int a, int b) {
    h->pos[h->array[a].vertex] = b;
    h->pos[h->array[b].vertex] = a;
    HeapItem tmp = h->array[a];
    h->array[a] = h->array[b];
    h->array[b] = tmp;
}

void heapify_down(MinHeap *h, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < h->size && h->array[left].dist < h->array[smallest].dist)
        smallest = left;
    if (right < h->size && h->array[right].dist < h->array[smallest].dist)
        smallest = right;

    if (smallest != idx) {
        heap_swap(h, smallest, idx);
        heapify_down(h, smallest);
    }
}

HeapItem heap_pop_min(MinHeap *h) {
    HeapItem root = h->array[0];
    HeapItem last = h->array[h->size - 1];
    h->array[0] = last;
    h->pos[root.vertex] = h->size - 1;
    h->pos[last.vertex] = 0;
    h->size--;
    heapify_down(h, 0);
    return root;
}

void heap_decrease_key(MinHeap *h, int v, int dist) {
    int i = h->pos[v];
    h->array[i].dist = dist;
    while (i > 0 && h->array[i].dist < h->array[(i - 1) / 2].dist) {
        heap_swap(h, i, (i - 1) / 2);
        i = (i - 1) / 2;
    }
}

void dijkstra(AdjGraph *g, int src) {
    int V = g->num_vertices;
    int *dist = malloc(sizeof(int) * (size_t)V);
    MinHeap *h = heap_create(V);

    for (int v = 0; v < V; v++) {
        dist[v] = INT_MAX;
        h->array[v] = (HeapItem){.vertex = v, .dist = dist[v]};
        h->pos[v] = v;
    }

    dist[src] = 0;
    h->size = V;
    heap_decrease_key(h, src, 0);

    while (h->size > 0) {
        HeapItem min_node = heap_pop_min(h);
        int u = min_node.vertex;
        if (dist[u] == INT_MAX) break;

        AdjNode *crawl = g->head[u];
        while (crawl) {
            int v = crawl->dest;
            if (h->pos[v] < h->size && dist[u] + crawl->weight < dist[v]) {
                dist[v] = dist[u] + crawl->weight;
                heap_decrease_key(h, v, dist[v]);
            }
            crawl = crawl->next;
        }
    }

    printf("Shortest distances from vertex %d:\n", src);
    for (int i = 0; i < V; i++) {
        printf("  Vertex %d -> %d\n", i, dist[i]);
    }

    free(dist);
    free(h->pos);
    free(h->array);
    free(h);
}

void graph_free(AdjGraph *g) {
    for (int i = 0; i < g->num_vertices; i++) {
        AdjNode *curr = g->head[i];
        while (curr) {
            AdjNode *next = curr->next;
            free(curr);
            curr = next;
        }
    }
    free(g->head);
    free(g);
}

int main(void) {
    AdjGraph *g = graph_create(5);
    graph_add_edge(g, 0, 1, 10);
    graph_add_edge(g, 0, 4, 5);
    graph_add_edge(g, 1, 2, 1);
    graph_add_edge(g, 4, 1, 3);
    graph_add_edge(g, 4, 2, 9);
    graph_add_edge(g, 4, 3, 2);
    graph_add_edge(g, 2, 3, 4);
    graph_add_edge(g, 3, 2, 6);

    printf("--- Dijkstra Shortest Path with Min-Heap ---\n");
    dijkstra(g, 0);

    graph_free(g);
    return 0;
}
