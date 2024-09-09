#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

// Função para realizar BFS e encontrar o caminho aumentante
bool bfs(const vector<vector<int>>& capacity, vector<vector<int>>& flow, vector<int>& parent, int source, int sink) {
    int n = capacity.size();
    vector<bool> visited(n, false);
    queue<int> q;

    q.push(source);
    visited[source] = true;
    parent[source] = -1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v = 0; v < n; ++v) {
            if (!visited[v] && capacity[u][v] - flow[u][v] > 0) {
                q.push(v);
                visited[v] = true;
                parent[v] = u;
                if (v == sink) {
                    return true;
                }
            }
        }
    }

    return false;
}


int edmondsKarp(const vector<vector<int>>& capacity, int source, int sink) {
    int n = capacity.size();
    vector<vector<int>> flow(n, vector<int>(n, 0));
    vector<int> parent(n);
    int maxFlow = 0;

    while (bfs(capacity, flow, parent, source, sink)) {
        int pathFlow = INT_MAX;
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            pathFlow = min(pathFlow, capacity[u][v] - flow[u][v]);
        }

        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            flow[u][v] += pathFlow;
            flow[v][u] -= pathFlow;
        }

        maxFlow += pathFlow;
    }

    return maxFlow;
}

int main() {
    // Definindo a rede de fluxo para o problema
    vector<vector<int>> capacity = {
        {0, 10, 5, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 15, 10, 0, 0, 0, 0, 0},  
        {0, 0, 0, 10, 10, 0, 0, 0, 0},  
        {0, 0, 0, 0, 15, 10, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 10, 10, 0, 0}, 
        {0, 0, 0, 0, 0, 0, 10, 5, 0},  
        {0, 0, 0, 0, 0, 0, 0, 10, 10}, 
        {0, 0, 0, 0, 0, 0, 0, 0, 15},  
        {0, 0, 0, 0, 0, 0, 0, 0, 0} 
    };

    int source = 0;  // A é o nó 0
    int sink = 8;    // I é o nó 8

    cout << "Fluxo máximo: " << edmondsKarp(capacity, source, sink);

    return 0;
}
