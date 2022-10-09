n, sum = [int(x) for x in input().split(' ')]

bidder = []

for i in range(n):
    name, val = input().split(' ')
    val = int(val)
    bidder.append((name, val))

bidder.sort(key = lambda x: x[1], reverse = 1)
# print(bidder)

succ_bidder = []

for (name, val) in bidder:
    # print(type(name), type(val))
    if (sum >= val):
        sum -= val
        succ_bidder.append(name)

if (sum == 0):
    print(len(succ_bidder))
    [print(name) for name in succ_bidder]

else:
    print(0)

# (print(len(succ_bidder)), [print(name) for name in succ_bidder]) if sum == 0 else print(0)