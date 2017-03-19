#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>

using std::vector;
using std::pair;

void dfs(int v, vector<bool> &marked, const vector<vector<int>> &adj, std::stack<int> &order) {
    marked[v] = true;

    for (int w : adj[v]) {
        if (!marked[w]) {
            dfs(w, marked, adj, order);
        }
    }
    order.push(v);
}

std::stack<int> toposort(vector<vector<int> > adj) {
    vector<bool> marked(adj.size());
    std::stack<int> order;
    for (int i = 0; i < adj.size(); i++) {
        if (!marked[i]) {
            dfs(i, marked, adj, order);
        }
    }
    return order;
}

int main() {
    size_t n, m;
    std::cin >> n >> m;
    vector<vector<int> > adj(n, vector<int>());
    for (size_t i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        adj[x - 1].push_back(y - 1);
    }
    std::stack<int> order = toposort(adj);
    while(!order.empty()){
        std::cout << order.top() + 1 << " ";
        order.pop();
    }
//    for (size_t i = 0; i < order.size(); i++) {
//        std::cout << order[i] + 1 << " ";
//    }
}
