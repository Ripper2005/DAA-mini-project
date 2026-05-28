/* ============================================================
 * Mini Project: Bellman-Ford Shortest Path Algorithm
 * Algorithm   : Bellman-Ford with Negative Cycle Detection
 * Author      : Harsha Vardhana M G  |  USN: R24EK016
 * Date        : 29-05-2026
 * Description : Computes single-source shortest paths in a
 *               weighted directed graph; detects negative cycles.
 * ============================================================ */

/* --- Include necessary header files --- */
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/* --- Constants used for validation and safe relaxation --- */
#define MAX_VERTICES 1000
#define INF (INT_MAX / 2)

/* --- Edge representation for a weighted directed graph --- */
struct Edge {
    int src;
    int dest;
    int weight;
};

/* ============================================================
 * Module / Function 1: readGraph
 * Purpose : Reads number of vertices, edges, and edge list.
 * Input   : Addresses of V, E, and edge-list pointer.
 * Output  : Returns 1 for valid input and 0 for invalid input.
 * ============================================================ */
int readGraph(int *V, int *E, struct Edge **edges) {
    int i;

    /* Read and validate the number of vertices and edges. */
    printf("Enter number of vertices: ");
    if (scanf("%d", V) != 1 || *V < 1 || *V > MAX_VERTICES) {
        printf("Invalid number of vertices. Valid range is 1 to %d.\n", MAX_VERTICES);
        return 0;
    }

    printf("Enter number of edges: ");
    if (scanf("%d", E) != 1 || *E < 0) {
        printf("Invalid number of edges. Edge count cannot be negative.\n");
        return 0;
    }

    /* Allocate memory for the edge list when at least one edge exists. */
    *edges = NULL;
    if (*E > 0) {
        *edges = (struct Edge *)malloc((size_t)(*E) * sizeof(struct Edge));
        if (*edges == NULL) {
            printf("Memory allocation failed for edge list.\n");
            return 0;
        }
    }

    /* Read every directed weighted edge and validate vertex numbers. */
    printf("Enter each edge as: source destination weight\n");
    for (i = 0; i < *E; i++) {
        printf("Edge %d: ", i + 1);
        if (scanf("%d %d %d", &(*edges)[i].src, &(*edges)[i].dest,
                  &(*edges)[i].weight) != 3) {
            printf("Invalid edge input.\n");
            free(*edges);
            *edges = NULL;
            return 0;
        }

        /* Ensure both endpoints lie inside the valid vertex range. */
        if ((*edges)[i].src < 0 || (*edges)[i].src >= *V ||
            (*edges)[i].dest < 0 || (*edges)[i].dest >= *V) {
            printf("Invalid edge endpoint. Vertices must be between 0 and %d.\n", *V - 1);
            free(*edges);
            *edges = NULL;
            return 0;
        }
    }

    return 1;
}

/* ============================================================
 * Module / Function 2: initializeSingleSource
 * Purpose : Initializes distance and predecessor arrays.
 * Input   : Number of vertices, source vertex, dist[], and pred[].
 * Output  : Updates dist[] and pred[] in place.
 * ============================================================ */
void initializeSingleSource(int V, int source, int dist[], int pred[]) {
    int i;

    /* Mark every vertex as unreachable before relaxation begins. */
    for (i = 0; i < V; i++) {
        dist[i] = INF;
        pred[i] = -1;
    }

    /* Distance from the source to itself is always zero. */
    dist[source] = 0;
}

/* ============================================================
 * Module / Function 3: bellmanFord
 * Purpose : Performs edge relaxation and negative cycle detection.
 * Input   : Vertex count, edge count, edge list, source, dist[], pred[].
 * Output  : Returns 1 if shortest paths exist; 0 if a negative cycle exists.
 * ============================================================ */
int bellmanFord(int V, int E, struct Edge edges[], int source, int dist[], int pred[]) {
    int i, j;

    /* Prepare all vertices before the relaxation passes. */
    initializeSingleSource(V, source, dist, pred);

    /* Relax all edges at most V - 1 times. */
    for (i = 1; i <= V - 1; i++) {
        int relaxed = 0;

        /* Scan every edge and improve the destination if possible. */
        for (j = 0; j < E; j++) {
            int u = edges[j].src;
            int v = edges[j].dest;
            int w = edges[j].weight;

            /* Relax only edges whose source is already reachable. */
            if (dist[u] != INF && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pred[v] = u;
                relaxed = 1;
            }
        }

        /* Early termination avoids unnecessary passes after convergence. */
        if (!relaxed) {
            break;
        }
    }

    /* One more scan detects a reachable negative-weight cycle. */
    for (j = 0; j < E; j++) {
        int u = edges[j].src;
        int v = edges[j].dest;
        int w = edges[j].weight;

        if (dist[u] != INF && dist[u] + w < dist[v]) {
            return 0;
        }
    }

    return 1;
}

/* ============================================================
 * Module / Function 4: printDistances
 * Purpose : Prints shortest distance from source to all vertices.
 * Input   : Number of vertices and distance array.
 * Output  : Displays a formatted distance table.
 * ============================================================ */
void printDistances(int V, int dist[]) {
    int i;

    /* Display INF for vertices that cannot be reached from source. */
    printf("\nVertex\tDistance from Source\n");
    printf("------\t--------------------\n");
    for (i = 0; i < V; i++) {
        if (dist[i] == INF) {
            printf("%d\tINF\n", i);
        } else {
            printf("%d\t%d\n", i, dist[i]);
        }
    }
}

/* ============================================================
 * Module / Function 5: printPath
 * Purpose : Iteratively reconstructs and prints a shortest path.
 * Input   : Source, destination, predecessor array, and distance array.
 * Output  : Prints the path or Unreachable.
 * ============================================================ */
void printPath(int source, int destination, int pred[], int dist[]) {
    int path[MAX_VERTICES];
    int count = 0;
    int current = destination;
    int i;

    /* Stop immediately when the destination is not reachable. */
    if (dist[destination] == INF) {
        printf("Unreachable");
        return;
    }

    /* Follow predecessors backward from destination to source. */
    while (current != -1 && count < MAX_VERTICES) {
        path[count++] = current;
        if (current == source) {
            break;
        }
        current = pred[current];
    }

    /* Detect malformed predecessor chains before printing. */
    if (count == 0 || path[count - 1] != source) {
        printf("Unreachable");
        return;
    }

    /* Print the reversed predecessor chain in source-to-destination order. */
    for (i = count - 1; i >= 0; i--) {
        printf("%d", path[i]);
        if (i > 0) {
            printf(" -> ");
        }
    }
}

/* ============================================================
 * Module / Function 6: main
 * Purpose : Controls input, algorithm execution, and output.
 * Input   : User-provided graph and source vertex.
 * Output  : Shortest distances, paths, or negative cycle message.
 * ============================================================ */
int main(void) {
    int V, E, source, i;
    int *dist = NULL;
    int *pred = NULL;
    struct Edge *edges = NULL;

    /* Read the graph and stop if validation fails. */
    if (!readGraph(&V, &E, &edges)) {
        return 1;
    }

    /* Read and validate the source vertex after the graph is known. */
    printf("Enter source vertex: ");
    if (scanf("%d", &source) != 1 || source < 0 || source >= V) {
        printf("Invalid source vertex. Valid range is 0 to %d.\n", V - 1);
        free(edges);
        return 1;
    }

    /* Allocate arrays used for distances and path reconstruction. */
    dist = (int *)malloc((size_t)V * sizeof(int));
    pred = (int *)malloc((size_t)V * sizeof(int));
    if (dist == NULL || pred == NULL) {
        printf("Memory allocation failed for auxiliary arrays.\n");
        free(edges);
        free(dist);
        free(pred);
        return 1;
    }

    /* Execute Bellman-Ford and handle a reachable negative cycle. */
    if (!bellmanFord(V, E, edges, source, dist, pred)) {
        printf("\nNegative weight cycle detected. Shortest paths are undefined.\n");
        free(edges);
        free(dist);
        free(pred);
        return 0;
    }

    /* Print shortest distance table followed by each reconstructed path. */
    printDistances(V, dist);
    printf("\nShortest paths from source %d:\n", source);
    for (i = 0; i < V; i++) {
        printf("Path to %d: ", i);
        printPath(source, i, pred, dist);
        printf("\n");
    }

    /* Release dynamically allocated memory before program termination. */
    free(edges);
    free(dist);
    free(pred);

    return 0;
}
