def f(x):
    return (2 * x**6 + 6 * x**5 + 5 * x**4 - x**2) / 12

# def g(x):
    # ret = 0;
    # for i in range(1, x+1):
        # ret += i ** 5;
    # return ret

# for i in range(1, 100):
    # print(f(i) - g(i))

p, q = list(map(int, input().split()))

lo, hi, mi = 1, 10000, 0
while (lo < hi):
    mi = (lo + hi) // 2
    if (q * mi ** 5 >= p):
        hi = mi
    else:
        lo = mi + 1

lost, now_lost = 0, 0;
for d in range(1, lo+1):
    now_lost += p;
    lost = max(lost, now_lost)
    now_lost -= q * d ** 5
    lost = max(lost, now_lost)

goal = int(1e99)
lo, hi, mi = 1, int(1e21), 0
while (lo < hi):
    mi = (lo + hi) // 2
    if (q * f(mi) - p * mi >= goal):
        hi = mi
    else:
        lo = mi + 1

days = lo

print(lost)
print(days)
