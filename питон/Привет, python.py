'''
КУСОК ТЕОРИИ:

Начать работу файла можно с помощью команды python start.py (находимся в папке с файлом, очев)

a = input() - считывает строку
a = int(input()) - число. Аналогично вводится float, double не существует

нихуя списки могут быть такими: a = [3, "masha", "bob", 3.15, [5, 7]]
a.append(9)
a.insert(3, 'misha') - первый аргумент - на какое место встанет элемент в конечном списке
print(a[1:4:2]) - последний параметр - с каким шагом берём элементы из списка
a.remove(value) - убирает первый встречающийся элемент с заданным значением (можно ещё удалять из среза: a[4:].remove('bob')), но выдаёт ошибку, если значения нет
print(a.index('misha')) - выдаёт индексы элементов "misha" (возможно только первый, проверь)
a.sort() - по возрастанию, меняет а
sorted(a) - не меняет a
min(a), max(a)

for i in range(5):
    print(a[i], sep=" ", end='')

словарь:
d = {'misha': 'masha', 2:3} #ключ:значение, перебор по ключам

строки если что можно складывать, то есть склеивать

print(' '.join(a)) - #'1 2 3' из [1, 2, ...]
'''

#now, want, elevator_now, time_for_move, time_for_door, time_to_walk = map(float, input().split())
#time_elevator = (max(elevator_now, now)-min(elevator_now, now))*time_for_move + (max(want, now)-min(want, now))*time_for_move + 4*time_for_door
#time_guy = (max(want, now)-min(want, now))*time_to_walk
#if time_elevator<=time_guy: print('elevator')
#else: print('stairs')
#print("время ног:", time_guy)
#print("время лифт:", time_elevator)
#print(time_guy==time_elevator)

#n = int(input())
#nums = []
#for i in range(n): nums.append(int(input()))
#nums.sort()
#i = 0
#while (i<=len(nums)) and (nums[i]<0): i+=1
#sorted_nums = nums[i:]
#for k in range(i): sorted_nums.append(nums[i-k-1])
#for elem in sorted_nums: print(elem, end=" ")

#def sum_of_dig(n):
#    ans = 0
#    while n>0:
#        ans += n%10
#        n = n//10
#    return ans 

#n = int(input())
#while (n>=10): n = sum_of_dig(n)
#print(n)

def is_broken_x(i, j, all_windows):
    if (h[i][0]<h[j][0] and h[i][1]>h[j][1]) or (h[i][0]>h[j][1] and h[i][1]<h[j][1]):
        return True 
    return False 

def is_broken_y(i, j, all_windows):
    if (h[i][2]<h[j][2] and h[i][3]>h[j][3]) or (h[i][2]>h[j][2] and h[i][3]<h[j][3]):
            return True 
    return False 

n, m = input().split()
n = int(n)
m = int(m)
number_of_windows = int(input())
all_windows = []
is_broken = False
for i in range(number_of_windows): 
    h = list(map(int, input().split()))
    for i in range(4):
        if (h[i]<0) or (i<2 and h[i]>n) or (i>=2 and h[i]>m):
            is_broken = True 
    all_windows.append(h)
if (is_broken):
    print('broken')
    exit()
for i in range(number_of_windows):
    for j in range(i+1, number_of_windows):
        if (is_broken_x(i, j, all_windows) and is_broken_y(i, j, all_windows)):
            print('broken')
            exit()
print('correct')