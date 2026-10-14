#n = int(input())
#dictionary = {}
#for i in range(n):
#    help = list(map(int, input().split()))
#    dictionary[help[0]] = help[1]
#sorted_dict = (dict(sorted(dictionary.items(), key=lambda item: item[1], reverse=True)))
#for i in sorted_dict: print(i)


'''
def is_int(s):
    for i in s[1:]:
        if not(i>='0' and i<='9'): return False
    if s[0]=='-' or (s[0]>='0' and s[0]<='9'): return True
    return False

eq = input()
if eq.count(' ')!=2: 
    print("Bad input")
else:
    eq_list = eq.split()
    if not(is_int(eq_list[0])) or not(is_int(eq_list[2])): print("Bad input")
    else:
        if eq_list[1]=='+': print(int(eq_list[0])+int(eq_list[2]))
        elif eq_list[1]=='-': print(int(eq_list[0])-int(eq_list[2]))
        elif eq_list[1]=='*': print(int(eq_list[0])*int(eq_list[2]))
        elif eq_list[1]=='^': print(int(eq_list[0])**int(eq_list[2]))
        else: print("Bad input")
'''

#def is_in(point, range):
#    if point>=range[0] and point<=range[1]: return True 
#    return False
#
#x = list(map(float, input().split()))
#y = list(map(float, input().split()))
#z = list(map(float, input().split()))
#n = int(input())
#counter = 0
#for i in range(n):
#    coords = list(map(float, input().split()))
#    if is_in(coords[0], x) and is_in(coords[1], y) and is_in(coords[2], z): counter+=1
#print(counter)

#import numpy as np
#n = int(input())
#t = np.array([])
#p = np.array([])
#for i in range(n):
#    data = list(map(float, input().split()))
#    t = np.append(t, data[0])
#    if data[0]>=-70 and data[0]<=80: p = np.append(p, data[1])
#average_t = round(sum(t)/len(t), 4)
#average_p = round(sum(p)/len(p), 4)
#print(f"{average_t:.{4}f}", f"{average_p:.{4}f}")


'''
def rot13(symbol):
    return chr(ord('a') + (ord(symbol)-ord('a')+13)%26)

import os
path = input()
if os.path.isfile(path):
    with open(path, 'r') as f:
        mui_hi_hi = f.read()
        ans = ''
        for i in mui_hi_hi:
            if (i>='a' and i<='z'): ans += rot13(i)
            elif (i>='A' and i<='Z'): ans += rot13(i.lower()).upper()
            else: ans+=i
        print(ans)
else: print("Can not read file")
'''


class Cursor:
    def __init__(self, x, y):
        self.x = x
        self.y = y 
        self.clicks = []
    def move(self, n, m):
        self.x+=n 
        self.y+=m 
    def click(self):
        self.clicks.append([self.x, self.y])
    def get_click_count(self, min_x, max_x, min_y, max_y):
        counter = 0
        for i in self.clicks:
            if (i[0]>=min_x and i[0]<=max_x) and (i[1]>=min_y and i[1]<=max_y): counter+=1
        return counter


class Point:
    def __init__(self, gugugaga):
        self.x = gugugaga[0]
        self.y = gugugaga[1]
        self.brightness = gugugaga[2]
    def rasstoyanie(self):
        return (self.x**2+self.y**2)**0.5
    def __repr__(self):
        return "%d %d %d" % (self.x, self.y, self.brightness)
    def __eq__(self, other):
        return self.x==other.x and self.y==other.y



list_of_points = []
n = int(input())
for i in range(n): list_of_points.append(Point(list(map(int, input().split()))))
filtered_list = []
for i in list_of_points:
    if i.brightness>=10 or i.rasstoyanie()<=100 or (list_of_points.count(i)>=2 and filtered_list.count(i)==0):
        filtered_list.append(i)
filtered_list = sorted(filtered_list, key=lambda e: e.rasstoyanie())
filtered_list = sorted(filtered_list, key=lambda e: list_of_points.count(e), reverse=True)
filtered_list = sorted(filtered_list, key=lambda e: e.brightness, reverse=True)
for i in filtered_list: print(i) 
