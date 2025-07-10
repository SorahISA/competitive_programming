from math import gcd

# Define the divfloor function
def divfloor(a, b):
    if b == 0:
        print(f"Error: Division by zero with a={a}, b={b}")
        return 0
    if (a >= 0) == (b > 0):
        return a // b
    return a // b - (a % b != 0)

# Define the divceil function
def divceil(a, b):
    if b == 0:
        print(f"Error: Division by zero with a={a}, b={b}")
        return 0
    if (a >= 0) != (b > 0):
        return a // b
    return a // b + (a % b != 0)

# Extended GCD function
def exgcd(a, b):
    if b == 0:
        return a, 1, 0
    gcd_val, x1, y1 = exgcd(b, a % b)
    x = y1
    y = x1 - (a // b) * y1
    return gcd_val, x, y

# Main solve function
def solve():
    N, M, A, B, K = map(int, input().split())
    
    if A < B:
        A, B = B, A
        N, M = M, N
    
    d = gcd(A, B)
    if K % d != 0:
        print(N + M)
        return
    
    A //= d
    B //= d
    K //= d
    
    gcd_val, x, y = exgcd(A, B)
    
    if x < 0:
        x += B
        y -= A
    
    x *= K
    y *= K
    
    shift = x // B
    x -= shift * B
    y += shift * A
    
    if y < 0:
        print(N + M)
        return
    
    max_use = 0
    
    def check(l, flag=False):
        nonlocal max_use
        lb = max(0, divceil(l * y - M, A))
        ub = min(l * divfloor(y, A), divfloor(N - l * x, B))
        
        if flag and lb <= ub:
            max_use = max(max_use, l * x + lb * B + l * y - lb * A)
        return (l * x + lb * B + l * y - lb * A) if lb <= ub else 0
    
    lo, hi = 0, N + M
    while lo < hi:
        mi = (lo + hi + 1) // 2
        if check(mi):
            lo = mi
        else:
            hi = mi - 1
    
    check(lo, True)
    
    if y % A != 0:
        res = (lo * y - M) % A
        mul = divceil(res, y % A)
        if lo > mul:
            check(lo - mul, True)
    
    print(N + M - max_use)

# Main function to handle multiple test cases
if __name__ == "__main__":
    t = int(input())
    for _ in range(t):
        solve()
