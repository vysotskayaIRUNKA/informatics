'''
КУСОК ТЕОРИИ:

'''

#N = int(input())
#Fib = [max(0, i-7) for i in range(N)]
#for i in range(9, N): Fib[i] = Fib[i-1]+Fib[i-2]+Fib[i-3]+Fib[i-4]+Fib[i-5]+Fib[i-6]+Fib[i-7]+Fib[i-8]+Fib[i-9]
#print(Fib[-1])

#l = list(map(int, input().split()))
#s = [i for i in l if l.count(i)==1]
#print(max(s))

#l = list(input().split())
#d = {i: l.count(i) for i in set(l)}
#sorted_dict = dict(sorted((dict(sorted(d.items(), key=lambda item: item[0]))).items(), key=lambda item: item[1], reverse=True))
#for i in sorted_dict: print(sorted_dict[i], i)

#path = input()
#with open(path, 'r') as f: print(sorted(f.read().split(), key=lambda item: len(item))[-1])

import os

paths = list(input().split())
l = []
for i in paths:
    if os.path.isfile(i):
        with open(i, 'r') as f: 
            words = f.read().split()
            for j in words:
                if l.count(j)==0: l.append(j)
print(*sorted(l))