# Hashing in Competitive Programming

## Introduction

During Competitive Programming contests, participants compete for
the maximum number of problems solved and earliest time solved.

One of the most popular Competitive Programming websites,
Codeforces features a "hacking" system where after you have
submitted a solution that passes the tests provided by the
problem-setter, you have the option to try to find a counter-test
for a submission by another participant.

Although hashing is a very powerful tool for competitive
programming, it's necessary to take precautions like introducing runtime
randomness into a program to make it non-deterministic and thus
more robust against hacking in a contest.

I researched the two most popular applications of hashing in
Competitive Programming in C++: Hashtables and Polynomial String Hashing.

## Defining Robustness

Due to the nature of hashing, for non-trivial cases there are always
more possible states than hash values. Therefore, with an unlimited number of
attempts all hashing solutions will eventually have collisions.

The Codeforces platform gives a participant +100 points for a
successful hacking attempt against another competitor and -50 points for
unsuccessful tries. In addition, the hacking period is typically around 12
hours after the end of a contest. These parameters give us more reasonable
bounds for the number of attempts and the computing power of an adversary.

A robust hashing solution would be one that cannot be hacked in 1~2 attempts
using an average computer within 12 hours with high probability.

## Pseudo-random Generators (PRNG)

### rand() : BAD

The C-standard library function rand is legacy code that is not
suitable for most applications today. The function returns a
library-dependent value between 0 and RAND_MAX but the C-standard
only guarantees that RAND_MAX is at least 32767 or $2^{15} - 1$.

### Mersenne Twister : DECENT

32-bit and 64-bit versions of the Mersenne Twister random-number
generator are included in the C++ standard library as mt19937.

The GCC compiler also includes SIMD-oriented fast Mersenne Twister
(sfmt19937) which is around 3x faster than mt19937.

Several cons prevent

### Xorshift : GOOD

New shift-register PRNGS such as xorshift and splitmix64 only
utilize a handful of operations such as add, xor, and shift which
are very fast on modern hardware. This results in up to 4-5x faster
performance in comparison to the Mersenne Twister PRNG.

Although this PRNG is not included in the C++ standard library, the
code is very short, fewer than 10 lines depending on the
implementation.



## Seeding PRNGs

### Fixed seed : BAD

### time(null) : BAD
Like rand, time is part of the C standard library.
"The value returned generally represents the number of seconds since
00:00 hours, Jan 1, 1970 UTC (i.e., the current _unix timestamp_)"
The return value is a 32-bit value that increments every second.
Similar to the fixed seed,

### std::chrono::steady_clock,  : GOOD
```c++
chrono::steady_clock::now().time_since_epoch().count()
```
This returns a

## Hashtables
### How it works
- chaining
- load factor
- primes

### Hacking


### Robust solution


## Polynomial String Hashing
### Rabin-Karp Rolling Hash

## Hacking

### Birthday Attack
A simple and very effective solution is the Birthday attack.

## Robust solution


## References
- It is high time we let go of the Mersenne Twister - Sebastian Vigna (preprint)
  - http://arxiv.org/abs/1910.06437
- https://en.wikipedia.org/wiki/Xorshift
- https://cplusplus.com/reference/ctime/time/
- Blowing up unordered_map, and how to stop getting hacked on it
	- https://codeforces.com/blog/entry/62393
- https://cplusplus.com/reference/unordered_map/unordered_map/
- On the mathematics behind rolling hashes and anti-hash tests
	- https://codeforces.com/blog/entry/60442
- https://github.com/gcc-mirror/gcc/blob/master/libstdc%2B%2B-v3/src/shared/hashtable-aux.cc
- https://www.vincent-lunot.com/post/playing-with-pseudo-random-number-generators-part-3/
