#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cstdio>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

string InverseBWT(string &bwt) {
    string result;
    int size = bwt.length();

    vector<int> a(size);
    vector<int> c(size);
    vector<int> g(size);
    vector<int> t(size);
    int a_count = 0;
    int c_count = 0;
    int g_count = 0;
    int t_count = 0;


    for (int i = 0; i < size; i++) {
        char symbol = bwt[i];
        if(symbol == 'A'){
            a[i] = a_count++;
        }
        else if(symbol == 'C'){
            c[i] = c_count++;
        }
        else if(symbol == 'G'){
            g[i] = g_count++;
        }
        else if(symbol == 'T'){
            t[i] = t_count++;
        }
    }

    int index = 0;
    char s = bwt[0];

    for (int i = 1; i < size; i++) {
        result += s;

        if(s == 'A' ){
            index = a[index] + 1;
        }
        else if(s == 'C' ){
            index = c[index] + 1 + a_count;
        }
        else if(s == 'G' ){
            index = g[index] + 1 + a_count + c_count;
        }
        else if(s == 'T' ){
            index = t[index] + 1 + a_count + c_count + g_count;
        }
        s = bwt[index];
    }

    std::reverse(result.begin(), result.end());
    result += '$';
    return result;
}

int main() {
    string bwt;
    cin >> bwt;
    cout << InverseBWT(bwt) << endl;
    return 0;
}
