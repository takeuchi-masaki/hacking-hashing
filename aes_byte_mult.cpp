#include <iostream>
#include <iomanip>
#include <bitset>

/*
 * Multiplying bytes in GF(2^8)
*/
const int MAX_BIT = 8;

/*
    base irreducible polynomial
    Rijndael Finite Field
    x^8 + x^4 + x^3 + x + 1 = 0
    -> x^8 = x^4 + x^3 + x + 1
    bits:      7654 3210
            0b 0001 1011
    hex:    0x    1    B
*/
const uint8_t base_polynomial = 0x1B;

uint8_t mult(uint8_t A, uint8_t B) {
    uint8_t res = 0;

    uint8_t b_copy = B;
    uint8_t prev = A, next = A;
    for (int shift = 0; shift < MAX_BIT; shift++) {
        if (shift > 0) {
            next <<= 1;
            /*
                XOR base polynomial when x^8 would be created:
                  (prev & (1 << (MAX_BIT - 1))) gets the top bit
                  when top bit is 1, shifting creates x^8
                  in if-statement since not shifting for lowest bit
            */
            if (prev & (1 << (MAX_BIT - 1))) {
                next ^= base_polynomial;
            }
        }
        if (b_copy & 1) {
            res ^= next;
        }
        b_copy >>= 1;
        prev = next;
    }
    return res;
}

void checkPair(uint8_t A, uint8_t B) {
    uint8_t ans = mult(A, B);
    std::cout << std::setfill('0');
    std::cout
        << "decimal: "
        << std::dec << std::setw(3) << int(ans) << '\n'
        << "binary:  0b"
        << std::bitset<MAX_BIT>(ans) << '\n'
        << "hex:     0x"
        << std::hex << std::uppercase << std::setw(2) << int(ans) << "\n";
}

int main() {
    uint8_t A = 0xB7;
    uint8_t B = 0xA5;
    checkPair(A, B);
}
