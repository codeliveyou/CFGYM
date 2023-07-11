import math

def power(a, b, mod):
    ans = 1
    while b > 0:
        if b & 1 == 1:
            ans = ans * a % mod
        b >>= 1
        a = a * a % mod
    return ans

s = input().split(' ')

b=int(s[0])
n=int(s[1])
Q=int(s[2])

a=[]

for _ in range(0,n):
    t=input().split(' ')
    a.append((int(t[0]), int(t[1])))

def cmp(x):
    return x[0]

a.sort(key = cmp)

P = 0
B = 233

if a[0][0]<=B:
    P=(b**a[0][0]) - a[0][1]

for i in range(1,n):
    if(a[i][0] - a[i-1][0] <= B):
        P=math.gcd(P, a[i-1][1] * (b**(a[i][0]-a[i-1][0])) - a[i][1])

for _ in range (0, Q):
    q = int(input())
    print(power(b, q, P))
