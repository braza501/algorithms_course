#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using std::vector;
using std::cin;
using std::cout;

class Thread {
public :
    long long number = -1;
    long long when_free = -1;

    Thread(int number_, int when_free_) : number(number_), when_free(when_free_) {}

    bool operator<(const Thread &b)const {
        if (when_free < b.when_free) {
            return false;
        }
        if (when_free > b.when_free) {
            return true;
        }

        return number > b.number;
    }
};

class JobQueue {
private:
    int num_workers_;
    vector<long long> jobs_;
    std::priority_queue<Thread> priority_queue;
    vector<long long> assigned_workers_;
    vector<long long> start_times_;

    void WriteResponse() const {
        for (int i = 0; i < jobs_.size(); ++i) {
            cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
        }
    }

    void ReadData() {
        int m;
        cin >> num_workers_ >> m;
        for (int i = 0; i < num_workers_; i++) {
            priority_queue.push(Thread(i, 0));
        }
        jobs_.resize(m);
        for (int i = 0; i < m; ++i)
            cin >> jobs_[i];
    }

    void AssignJobs() {

        assigned_workers_.resize(jobs_.size());
        start_times_.resize(jobs_.size());
        for (int i = 0; i < jobs_.size(); ++i) {
            int duration = jobs_[i];
            Thread thread = priority_queue.top();
            priority_queue.pop();

            assigned_workers_[i] = thread.number;
            start_times_[i] = thread.when_free;
            thread.when_free += duration;
            priority_queue.push(thread);
        }
    }

public:
    void Solve() {
        ReadData();
        AssignJobs();
        WriteResponse();
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    JobQueue job_queue;
    job_queue.Solve();
    return 0;
}
