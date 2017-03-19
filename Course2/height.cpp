#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>

class TreeHeight {
    int n;
    std::vector<std::vector<int>> parent;
    int root;

public:
    void read() {
        std::cin >> n;
        parent.resize(n);
        for (int i = 0; i < n; i++) {
            int k;
            std::cin >> k;
            if (k == -1) { root = i; }
            else {
                parent[k].push_back(i);
            }
        }
    }

    int compute_height() {
        return height(root);
    }

    int height(int index) {

        std::queue<int> queue;

        queue.push(root);
        int height = 0;

        while (true) {
            int levelSize = queue.size();
            if (levelSize == 0)
                return height;

            height++;


            while (levelSize > 0) {
                int k = queue.front();
                queue.pop();
                for (auto &&x: parent[k])
                    queue.push(x);
                levelSize--;
            }
        }
    }
};

int main() {
    std::ios_base::sync_with_stdio(0);
    TreeHeight tree;
    tree.read();
    std::cout << tree.compute_height() << std::endl;
}
