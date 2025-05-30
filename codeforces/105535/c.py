from typing import List

POTMAX: int = 32
pot2: List[int] = [1 << i for i in range(POTMAX + 2)]


def mod_pow(a, b, mod):
    res = 1
    a %= mod
    while b > 0:
        if b & 1:
            res = (res * a) % mod
        a = (a * a) % mod
        b >>= 1
    return res


def solve(a):
    b = 0
    for k in range(1, POTMAX):
        a_pow_b_mod = mod_pow(a, b % pot2[k], pot2[k + 1])
        b = ((a % pot2[k + 1]) ^ a_pow_b_mod) % pot2[k + 1]

    if mod_pow(a, b, pot2[POTMAX]) == (a ^ b):
        return 1, b
    else:
        return (0,)


def main() -> None:
    t = int(input())
    for _ in range(t):
        a = int(input())
        res = solve(a)
        print(*res)


if __name__ == "__main__":
    main()
