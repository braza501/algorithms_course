#include <iostream>
#include <string>
#include <vector>

using std::string;
typedef unsigned long long ull;
ull prime = 1190494771;

struct Data {
    string pattern, text;
};

Data read_input() {
    Data data;
    std::cin >> data.pattern >> data.text;
    return data;
}

void print_occurrences(const std::vector<int> &output) {
    for (size_t i = 0; i < output.size(); ++i)
        std::cout << output[i] << " ";
    std::cout << "\n";
}

ull hash(const string &key, int m) {

    ull h = 0;
    for (int j = 0; j < m; j++)
        h = (256 * h + key[j]) % prime;
    return h;
}

std::vector<int> get_occurrences(const Data &input) {
    const string &pattern = input.pattern, text = input.text;
    std::vector<int> ans;

    int pattern_length = pattern.length();
    int text_length = text.length();

    ull power = 1;
    for (int i = 1; i <= pattern_length - 1; i++)
        power = (256 * power) % prime;
    ull pattern_hash = hash(pattern, pattern_length);

    if (text_length < pattern_length) {
        return ans;
    }

    ull text_hash = hash(text, pattern_length);

    if (pattern_hash == text_hash) {
        ans.push_back(0);
    }

    for (int i = pattern_length; i < text_length; i++) {

        text_hash = (text_hash + prime - power * text[i - pattern_length] % prime) % prime;
        text_hash = (text_hash * 256 + text[i]) % prime;

        if (pattern_hash == text_hash) {
            ans.push_back(i - pattern_length + 1);
        }

    }

    return ans;
}


int main() {
    std::ios_base::sync_with_stdio(false);
    print_occurrences(get_occurrences(read_input()));
    return 0;
}
