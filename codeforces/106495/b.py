n = int(input())

for i in range(n):
    s = input().split(' ')

    for idx, pal in enumerate(s):
        end = ' '
        if idx == len(s)-1:
            end = '\n'
        # print(idx, '|', end, '|')
        num = True
        if not pal.isdecimal():
            print(pal, end=end)
            continue
        
        zer = 0
        for i in range(len(pal)-1, -1, -1):
            if pal[i] != '0':
                break
            zer += 1
        if zer < 4:
            print(pal, end=end)
            continue
        pal = pal.rstrip('0')
        
        if pal == "1":
            print("10^{"+str(zer)+"}", end=end)
            continue

        print(pal[0], end="")            
        if len(pal) >= 2:
            print('.', end ="")            
            print(pal[1:], end ="")
            zer += len(pal)-1
        print("\\cdot10^{" + str(zer) + "}", end=end)