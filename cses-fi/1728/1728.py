from decimal import Decimal, getcontext, ROUND_HALF_EVEN

def main():
    getcontext().prec = 50
    getcontext().rounding = ROUND_HALF_EVEN
    
    n = int(input())
    r = list(map(int, input().split()))

    # Initialize as a Decimal string
    resp = Decimal('0') 
    
    for i in range(n):
        for j in range(i + 1, n):
            cnt = 0
            for x in range(1, r[i] + 1):
                for y in range(1, r[j] + 1):
                    if x > y:
                        cnt += 1
            
            # Explicitly cast integers to Decimal before dividing
            resp += Decimal(cnt) / (Decimal(r[i]) * Decimal(r[j]))

    print(f"{resp:.6f}")

main()