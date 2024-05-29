# Attacking Hash Collisions
String Matching
https://leetcode.com/problems/number-of-subarrays-that-match-a-pattern-ii/

- [ ] find collision on non-prime modulus (2^64)
  - should just work with birthday attack
- [x] find collision on modulo (1e9 + 7)
  - birthday attack
- [ ] randomized base (probably just do 1e6 random numbers length 40+ works for mod 1e9 + 7)
- [ ] multi-hashing
- [ ] unordered_map hash function (uses deterministic primes)
  - benchmark number of collisions
  - bucket count vs element count?

- string hashing to find number of matches
  - modulo 1e9, modulo 998
  - create a testset where all values are different
    - only need a single wrong collision

- hashmap
  - in general: hash function for int: identity function
  - c++: set prime modulus, dependent on compiler
  - python: 5x + 1
    - numbers wrap at 2^31 - 1 for 32-bit, 2^61 - 1 for 64-bit
