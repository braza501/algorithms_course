#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <deque>

using std::string;
using std::vector;
using std::cin;

struct Query {
    string type, s;
    size_t ind;
};

class QueryProcessor {
    int bucket_count;

    std::vector<std::deque<string>> set;
    vector<string> elems;

    size_t hash_func(const string &s) const {
        static const size_t multiplier = 263;
        static const size_t prime = 1000000007;
        unsigned long long hash = 0;
        for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
            hash = (hash * multiplier + s[i]) % prime;
        return hash % bucket_count;
    }

public:
    explicit QueryProcessor(int bucket_count) : bucket_count(bucket_count), set(bucket_count) {}

    Query readQuery() const {
        Query query;
        cin >> query.type;
        if (query.type != "check")
            cin >> query.s;
        else
            cin >> query.ind;
        return query;
    }

    void writeSearchResult(bool was_found) const {
        std::cout << (was_found ? "yes\n" : "no\n");
    }

    void processQuery(const Query &query) {

        if (query.type == "check") {
            auto x = set[query.ind];
            if (x.empty()) {
                std::cout << "" << "\n";;
            } else {
                for (auto &&var: x)
                    std::cout << var << " ";
                std::cout << "\n";
            }
        } else {

            if (query.type == "find") {
                long long hash = hash_func(query.s);
                auto &x = set[hash];
                bool flag = false;
                for (auto &&var: x) {
                    if (query.s == var) {
                        flag = true;
                        break;
                    }
                }
                writeSearchResult(flag);
            } else if (query.type == "add") {
                long long hash = hash_func(query.s);
                auto &x = set[hash];
                bool flag = false;
                for (auto &&var: x) {
                    if (query.s == var) {
                        flag = true;
                        break;
                    }
                }
                if (!flag) {
                    x.push_front(query.s);
                }
            } else if (query.type == "del") {
                long long hash = hash_func(query.s);
                auto &x = set[hash];
                for (auto i = x.begin(); i != x.end(); ++i) {
                    if (query.s == (*i)) {
                        x.erase(i);
                        break;
                    }
                }
            }
        }
    }

    void processQueries() {
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i)
            processQuery(readQuery());
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    int bucket_count;
    cin >> bucket_count;
    QueryProcessor proc(bucket_count);
    proc.processQueries();
    return 0;
}
