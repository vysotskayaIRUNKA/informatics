#l = list(map(int, input().split()))
#n = int(input())
#l.sort(reverse=True)
#for i in range(n): print(l[n-i-1])


#def if_int(s):
#    is_int = True
#    for j in s:
#        if not(j>='0' and j<='9'):
#            is_int = False 
#    return is_int
#l = input().split()
#s = 0
#for i in l:
#    if (if_int(i[1:]) and ((i[0]>='0' and i[0]<='9') or i[0]=='-')):
#        s += int(i)
#print(s)


#def need_power(s):
#    index_point = s.find('.')
#    if (index_point==-1): return 0
#    else: return len(s)-index_point-1
#n = input()
#power = need_power(n)
#if power==0: print(int(n)-1)
#else:
#    n = float(n)
#    ans = round(n- 1*10**(-1*power), power)
#    print(f"{ans:.{power}f}")


#s = input()
#ones = "1"
#while True:
#    if (s.find(ones)!=-1):
#        ones+='1'
#    else: break 
#print(len(ones)-1)


#import os
#path = input()
#word = input()
#counter = 0
#if os.path.isfile(path):
#    with open(path, 'r') as f:
#        list_of_words = f.read().split()
#        for w in list_of_words:
#            if w.lower()==word.lower(): counter+=1 #lower -- игнор регистра
#print(counter)


class GasStation:
    def __init__(self, capacity):
        self.capacity = capacity
        self.filled = 0 
    def fill(self, n):
        if n>(self.capacity-self.filled): raise Exception("Вливаемый объём больше доступного")
        else: self.filled+=n 
    def tank(self, n):
        if n>self.filled: raise Exception("Выливаемый объём больше доступного")
        else: self.filled-=n 
    def get_limit(self): return self.filled

'''
N = int(input())
dull_list = []
for i in range(N): dull_list.append(input().split())
l = []
for i in dull_list:
    for k in i:
        l.append(k)
list_of_similar = {}
for i in l:
    if i.lower() not in list_of_similar:
        list_of_similar[i.lower()]= [i]
    else: 
        if i not in list_of_similar[i.lower()]: list_of_similar[i.lower()].append(i)
sorted_dict = dict(sorted((dict(sorted(list_of_similar.items(), key=lambda item: item[0]))).items(), key=lambda item: len(item[1]), reverse=True))

nearly_ans = [i for i in sorted_dict if len(sorted_dict[i])>2]
for i in nearly_ans:
    print(i)
'''


class time_machine:
    def __init__(self, time, *rest):
        self.time==time
        if rest!=[]:
            if rest[0]=='SET':
                if rest[1]=="status": self.status = rest[2]
                elif rest[1]=="pressure": self.pressure = rest[2]
                elif rest[1]=="speed": self.speed = rest[2]
            else:
                if rest[1]=="status": self.status = None
                elif rest[1]=="pressure": self.pressure = None
                elif rest[1]=="speed": self.speed = None 
    def iteration(self, prev_machine, time, *rest):
        self.time = time 
        self.status = prev_machine.status
        self.pressure = prev_machine.pressure
        self.speed = prev_machine.speed
        if rest[0]=='SET':
                if rest[1]=="status": self.status = rest[2]
                elif rest[1]=="pressure": self.pressure = rest[2]
                elif rest[1]=="speed": self.speed = rest[2]
        else:
            if rest[1]=="status": self.status = None
            elif rest[1]=="pressure": self.pressure = None
            elif rest[1]=="speed": self.speed = None 



