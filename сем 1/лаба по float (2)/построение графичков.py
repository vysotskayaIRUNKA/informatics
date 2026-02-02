import matplotlib.pyplot as plt
import numpy as np
import math

#функция, её производная и первообразная
#x = 0.001
#list_x = []
#while (x<=1):
#    list_x.append(x)
#    x+=0.001
#plt.scatter(list_x, [i**3 for i in list_x], label = 'График функции')
#plt.scatter(list_x, [3 * i**2 for i in list_x], label = 'Производная функции')
#plt.scatter(list_x, [i**4 / 4 for i in list_x], label = 'Первообразная функции')
#plt.title('Функция x^3, её производная и первообразная')

#f = open('площадь float — копия.csv')
#r = f.readlines()
#n = [int(x.split(';')[0]) for x in r[1:]]
#s = [float(x.split(';')[1]) for x in r[1:]]
#plt.scatter(n, s, label = 'используем float')
#print(s)
#plt.title('Площадь под графиком x^3 в зависимости от количества прямоугольников разбиения')

f1 = open('площадь double.csv')
r1 = f1.readlines()
n1 = [int(x.split(';')[0]) for x in r1[1:]]
s1 = [float(x.split(';')[1]) for x in r1[1:]]
plt.scatter(n1, s1, label = 'используем double')

plt.legend(loc='upper left')
plt.xlabel('Количество прямоугольников n')
plt.ylabel('Площадь под графиком')


plt.show()
    
