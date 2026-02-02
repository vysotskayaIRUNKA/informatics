import matplotlib.pyplot as plt
import numpy as np
import math

def line(x1, y1, x2, y2):
    k = (y2-y1)/(x2-x1)
    b = (y1-x1*k)
    return (k, b)

n_slow = [1000, 5000, 10000, 50000]
log_n_slow = [math.log2(x) for x in n_slow]

t_bubble = [3174576, 73373640, 301105102, 5842885709]
t_bubble_0 = [0.002, 0.03, 0.1, 5.7]
t_bubble_1 = [0.001, 0.01, 0.1, 2.1]
t_bubble_2 = [0.002, 0.04, 0.2, 5.3]
t_bubble_3 = [0.002, 0.038, 0.16, 5.4]
log_t_bubble = [math.log2(x) for x in t_bubble]
(k_bubble, b_bubble) = line(log_n_slow[0], log_t_bubble[0], log_n_slow[1], log_t_bubble[1])
t_bubble_worst = [2366953, 48850092, 193268949, 5759220441]
t_bubble_best = [1720, 8135, 11621, 112718]
#plt.plot(log_n_slow, [x*k_bubble + b_bubble for x in log_n_slow], color = 'lightgray', label = 'прямые')
#plt.plot(n_slow, t_bubble_0, color = 'pink', marker = 's', label = 'Оптимизация -О0')
#plt.plot(n_slow, t_bubble_1, color = 'purple', marker = '^', label = 'Оптимизация -О1')
#plt.plot(n_slow, t_bubble, color = 'blue', label = 'Сортировка пузырьком')
#plt.scatter(n_slow, t_bubble, color = 'blue', marker = 'o', label = 'Средний вариант')
#plt.plot(n_slow, t_bubble_worst, color='blue')
#plt.scatter(n_slow, t_bubble_worst, color='blue', marker='s', label = 'Худший вариант')
#plt.plot(n_slow, t_bubble_best, color='blue')
#plt.scatter(n_slow, t_bubble_best, color='blue', marker='^', label = 'Лучший вариант')
#plt.plot(n_slow, t_bubble_3, color = 'cyan', marker = 'o', label = 'Оптимизация -O3')
#plt.title('Пузырек с различными оптимизациями')

t_selection = [816791, 12727304, 50057079, 1276449635]
t_selection_worst = [882116, 14462147, 55843147,1922801682]
t_selection_best = [779670, 13034084, 51718385, 1325644587]
#log_t_selection = [math.log2(x) for x in t_selection]
#(k_selection, b_selection) = line(log_n_slow[0], log_t_selection[0], log_n_slow[2], log_t_selection[2])
#plt.plot(log_n_slow, [x*k_selection + b_selection for x in log_n_slow], color = 'lightgray')
#plt.plot(n_slow, t_selection, color = 'green', label = 'Сортировка выбором')
#plt.scatter(n_slow, t_selection, color='green', marker='o', label = 'Средний вариант')
#plt.plot(n_slow, t_selection_worst, color='green')
#plt.scatter(n_slow, t_selection_worst, color='green', marker='s', label = 'Худший вариант')
#plt.plot(n_slow, t_selection_best, color='green')
#plt.scatter(n_slow, t_selection_best, color='green', marker='^', label='Лучший вариант')

t_insert = [1225633, 20035765, 80266498, 2394659862]
t_insert_worst = [2099686, 43671091, 171248175, 4448830129]
t_insert_best = [2670, 11847, 16411, 79986]
#log_t_insert = [math.log2(x) for x in t_insert]
#(k_insert, b_insert) = line(log_n_slow[0], log_t_insert[0], log_n_slow[2], log_t_insert[2])
#plt.plot(log_n_slow, [x*k_insert + b_insert for x in log_n_slow], color = 'lightgray')
#plt.plot(n_slow, t_insert, color = 'orange', label = 'Сортировка вставкой')
#plt.scatter(n_slow, t_insert, color='orange', marker='o', label = 'Средний вариант')
#plt.plot(n_slow, t_insert_worst, color='orange')
#plt.scatter(n_slow, t_insert_worst, color='orange', marker='s', label = 'Худший вариант')
#plt.plot(n_slow, t_insert_best, color='orange')
#plt.scatter(n_slow, t_insert_best, color='orange', marker='^', label='Лучший вариант')

n_quick = [1000, 5000, 10000, 50000, 100000]

t_quick = [89866, 511131, 797050, 4134121, 8303861]
t_quick_worst = [213541, 1225320, 2081127, 14462841, 29958403]
t_quick_best = [17488, 118758, 205944, 1321660, 2740839]
log_t_quick = [0.000089866/(1000*math.log2(1000)), 0.000511131/(5000*math.log2(5000)), 0.00079705/(10000*math.log2(10000)), 0.004134121/(50000*math.log2(50000))]#,0.008303861/(100000*math.log2(100000))] 
#plt.plot(n_quick, t_quick, color = 'mediumaquamarine', marker = 's', label = 'Быстрая сортировка')
#plt.plot(n_quick, log_t_quick, color = 'blue', marker = 'o', label = 'Быстрая сортировка')
#plt.title('Линеаризованные быстрые сортировки')
#plt.plot(1, 0.00001)
plt.plot(n_quick, t_quick, color = 'blue', label = 'Быстрая сортировка')
plt.scatter(n_quick, t_quick, color='blue', marker='o', label = 'Средний вариант')
plt.plot(n_quick, t_quick_worst, color='blue')
plt.scatter(n_quick, t_quick_worst, color='blue', marker='s', label = 'Худший вариант')
plt.plot(n_quick, t_quick_best, color='blue')
plt.scatter(n_quick, t_quick_best, color='blue', marker='^', label='Лучший вариант')
 
t_comb = [141346, 752554, 1129403, 6418572, 14333314]
t_comb_worst = [67322, 395348, 657424, 3908172, 8337243]
t_comb_best = [57491, 320054, 545224, 3137433, 6682800]
log_t_comb = [0.000141346/(1000*math.log2(1000)), 0.000752554/(5000*math.log2(5000)), 0.001129403/(10000*math.log2(10000)), 0.006418572/(50000*math.log2(50000)),0.014333314/(100000*math.log2(100000))] 
#plt.plot(n_quick, t_comb, color = 'cyan', marker = '.', label = 'Сортировка расческой')
plt.plot(n_quick, t_comb, color = 'green', label = 'Сортировка расческой')

plt.plot(n_quick, t_comb_worst, color='green')
plt.scatter(n_quick, t_comb_worst, color='green', marker='o', label = 'Средний вариант')
plt.scatter(n_quick, t_comb, color='green', marker='s', label = 'Худший вариант')
plt.scatter(n_quick, t_comb_best, color='green', marker='^', label='Лучший вариант')
plt.plot(n_quick, t_comb_best, color='green')


t_merge = [1384781, 6935226, 13715786, 69800884, 140378229]
t_merge_worst = [1227840, 4153112, 8293260, 41844907, 83402310]
t_merge_best = [1018000, 3434313, 6721929, 33852989, 68301653]
log_t_merge = [0.001384781/(1000*math.log2(1000)), 0.006935226/(5000*math.log2(5000)), 0.013715786/(10000*math.log2(10000)), 0.069800884/(50000*math.log2(50000)),0.140378229/(100000*math.log2(100000))] 
#plt.plot(n_quick, t_merge, color = 'gold', marker = '.', label = 'Сортировка слиянием')
plt.plot(n_quick, t_merge, color = 'orange', label = 'Сортировка расческой')
plt.scatter(n_quick, t_merge, color='orange', marker='o', label = 'Средний вариант')
plt.plot(n_quick, t_merge_worst, color='orange')
plt.scatter(n_quick, t_merge_worst, color='orange', marker='s', label = 'Худший вариант')
plt.plot(n_quick, t_merge_best, color='orange')
plt.scatter(n_quick, t_merge_best, color='orange', marker='^', label='Лучший вариант')




plt.title('Быстрые сортировки: лучший, средний и худший варианты')
plt.legend(loc='upper left')
plt.xlabel('Размер массива')
plt.ylabel('Время сортировки, нсек')
#plt.xlabel('N')
#plt.ylabel('t/NlogN')
plt.show()


