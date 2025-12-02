
def f(t, s ,k):
    return s*k + t*(20*k-4*s)-80*t*t

def aux(s, k):
    ver = int((5*k-s)/40)
    ans = -1000000
    for i in range(-2, 3):
        ans = max(ans ,f(ver+i, s, k))
    return ans

def solve():
    v = [int(x) for x in input().split(" ")]
    s = v[0]
    k = v[1]
    ans = s*k
    if s%10 == 0:
        print(ans)
        return
    if s%10 == 5:
        s += 5
        k -= 1
        ans = max(ans, s*k)
        print(ans)
        return
    if s%2 == 1:
        s += s%10
        k -= 1
    
    for i in range(6):
        ans = max(ans, aux(s,k))
        s += s%10
        k -= 1
        if k == 0:
            break
    print(ans)

ta = int(input())#

while(ta != 0):
    solve()
    ta -= 1
    