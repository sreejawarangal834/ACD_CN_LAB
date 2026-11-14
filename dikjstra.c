#include <stdio.h>

#define MAX 100
#define INF 99999

void printPath(int parent[], int v)
{
    if (v == -1)
        return;

    printPath(parent, parent[v]);
    printf("%d ", v);
}

int main()
{
    int n, i, j, src, count;
    int cost[MAX][MAX];
    int dist[MAX], visited[MAX], parent[MAX];
    int u, min;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter adjacency matrix (0 if no edge):\n");

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            scanf("%d", &cost[i][j]);
        }
    }

    printf("Enter source vertex (0 to %d): ", n - 1);
    scanf("%d", &src);

    // Initialize arrays
    for (i = 0; i < n; i++)
    {
        dist[i] = INF;
        visited[i] = 0;
        parent[i] = -1;
    }

    dist[src] = 0;

    // Dijkstra's algorithm
    for (count = 0; count < n - 1; count++)
    {
        u = -1;
        min = INF;

        // Find the unvisited vertex with minimum distance
        for (i = 0; i < n; i++)
        {
            if (!visited[i] && dist[i] < min)
            {
                min = dist[i];
                u = i;
            }
        }

        if (u == -1)
            break;

        visited[u] = 1;

        // Update distances of adjacent vertices
        for (j = 0; j < n; j++)
        {
            if (!visited[j] && cost[u][j] != 0 &&
                dist[u] != INF &&
                dist[u] + cost[u][j] < dist[j])
            {
                dist[j] = dist[u] + cost[u][j];
                parent[j] = u;
            }
        }
    }

    // Print shortest distances and paths
    printf("\nShortest distances from source %d:\n", src);

    for (i = 0; i < n; i++)
    {
        printf("To %d: ", i);

        if (dist[i] == INF)
        {
            printf("Unreachable\n");
        }
        else
        {
            printf("%d\tPath: ", dist[i]);
            printPath(parent, i);
            printf("\n");
        }
    }

    return 0;
}