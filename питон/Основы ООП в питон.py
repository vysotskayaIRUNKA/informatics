'''
КУСОК ТЕОРИИ ДАЙ БОГ

x, y, *rest = 1, 2, 3, 4, 5, 6 -- типа нужна функция с пременным числом переменных
*rest = [3, 4, 5, 6] -- типа это будет список, может стоять вообще где угодно, похуй+похуй
для функций есть ещё тема с **arg -- захватывает все именованные переменные. Пример: def nop(*rest, **kwargs) -- *rest возьмёт просто переменные, **kwargs -- именованные (видимо * и ** мешать всё-таки не надо)


если на кой-то хуй нам нужен один элемент из кортежа: b, = (1, ) -- запятая обязательно, справа не уверена

чтобы вывести список без форматирования как у списков: print(*array)

кстати забавная хуйня:
int('101') -- 101
int('101', 10) -- 101
int('101', 2) -- 5

именованные аргументы: matrix_has_value(matrix=[[1, 2, 3], [4, 5, 6]], value=7) аналогично с matrix_has_value(value=7, matrix=[[1, 2, 3], [4, 5, 6]])

pass работает как continue, видимо
'''

class MoneyBox:
    def __init__(self):
        self.number_of_coins = 0
        self.value_of_coins = 0 
    def add_coin(self, value):
        self.number_of_coins+=1
        self.value_of_coins+=value 
    def get_coins_number(self):
        return self.number_of_coins 
    def get_coins_value(self):
        return self.value_of_coins 


class Car:
    def __init__(self, capacity, speed, number):
        self.capacity = int(capacity)
        self.speed = int(speed)
        self.number = number
    def __eq__(self, other):
        if isinstance(other, Car):
            return self.number == other.number
        else: return False
    def __hash__(self):
        return hash(self.number)
    def __str__(self):
        return "<Car capacity: %d speed: %d number: %s>" % (self.capacity, self.speed, self.number)

class RaceCar(Car):
    def __init__(self, speed):
        super().__init__(0, speed, "None")

class Truck(Car):
    pass 
class Bus(Car):
    pass

class Garage:
    def __init__(self):
        self.all_cars = []
        self.all_trucks = []
        self.all_buses = []
    def park(self, v):
        self.all_cars.append(v)
        if isinstance(v, Truck): self.all_trucks.append(v)
        elif isinstance(v, Bus): self.all_buses.append(v)
    def count(self, t):
        if t== Truck: return len(self.all_trucks)
        elif t==Bus: return len(self.all_buses)
        return len(self.all_cars)
    def get_fastest_of_type(self, t):
        if t==Truck: return max(self.all_trucks, key=lambda x: x.speed)
        elif t==Bus: return max(self.all_buses, key=lambda x: x.speed)
        return max(self.all_cars, key=lambda x: x.speed)
