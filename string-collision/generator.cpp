#include <chrono>
#include <random>
typedef long long ll;
using namespace std;

/*
    create random test
*/
int main() {
    const int n = int(1e5);
    mt19937_64 rng(chrono::high_resolution_clock::now().time_since_epoch().count());
    uniform_int_distribution<> uid('a', 'z');

    string str;
    for (int i = 0; i < n; i++) {
        str.push_back(uid(rng));
    }
}
