#include <iostream>
#include <vector>
using namespace std;

const int BUCKET_SIZE = 102877;
const int MAX_VAL = int(1e9);
const int MAX_SIZE = int(1e5);
vector<int> res;

void add(int start) {
    int curr = start;
    while(curr <= MAX_VAL && res.size() < MAX_SIZE) {
        res.push_back(curr);
        curr += BUCKET_SIZE;
    }
}

int main() {
    for (int i = 0; res.size() < MAX_SIZE; i++) {
        add(i);
    }

    cout << res.size() << "\n";
    for (auto num : res) {
        cout << num << " ";
    }
    cout << "\n";
}
