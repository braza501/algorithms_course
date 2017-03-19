#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;


int distance(vector<vector<int> > &adj, int s, int t) {
    vector<int> distances(adj.size());
    vector<bool> marked(adj.size());
    std::queue<int> queue;

    for (int i = 0; i < adj.size(); i++)
        distances[i] = -1;

    distances[s] = 0;
    marked[s] = true;
    queue.push(s);

    while (!queue.empty()) {
        int v = queue.front();
        queue.pop();
        for (int w : adj[v]) {
            if (!marked[w]) {
                distances[w] = distances[v] + 1;
                marked[w] = true;
                queue.push(w);
            }
        }
    }
    return distances[t];
}


int main() {
    int n, m;
    std::cin >> n >> m;
    vector<vector<int> > adj(n, vector<int>());
    for (int i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        adj[x - 1].push_back(y - 1);
        adj[y - 1].push_back(x - 1);
    }
    int s, t;
    std::cin >> s >> t;
    s--, t--;
    std::cout << distance(adj, s, t);
}
