#include <iostream>
using std::cin, std::cout, std::endl, std::boolalpha;

class Train {
public:
	// Создать паровоз массой m,
	// стоящий в начале координат
	Train(double m)
	{
		this->m = m;
		this->v = 0;
		this->x = 0;
	}

	// Ехать с текущей скоростью в течение времени dt
	void move(double dt) { x += v * dt; }

	// Изменить полный импульс паровоза (p = mv) на dp
	// Изменение может менять знак скорости
	void accelerate(double dp)
	{
		double dv = dp / m;
		v += dv;
	}

	// Получить текущую координату паровоза
	double getX() { return x; }

private:
	double m;
	double v;
	double x;
};

class GasHolder {
public:
	// Создать газгольдер заданного объёма.
	// Температура созданного термостата равна 273 К.
	GasHolder(float v)
	{
		V = v;
		T = 273;
		nu = 0;
	}

	// Уничтожить газгольдер.
	~GasHolder()
	{
		V = 0;
		T = 0;
		nu = 0;
	}

	// Впрыск порции газа массой m и молярной массой M.
	// Считать, что газ принимает текущую температуру газгольдера за пренебрежимо
	// малое время.
	void inject(float m, float M) { nu += m / M; }

	// Подогреть газгольдер на dT градусов.
	// Считать, что нагрев возможен до любых значений температуры.
	void heat(float dT) { T += dT; }

	// Охладить газгольдер на dT градусов.
	// При попытке охладить ниже 0 К температура становится ровно 0 К.
	void cool(float dT)
	{
		if (dT > T) {
			T = 0;
		}
		else {
			T -= dT;
		}
	}

	// Получить текущее давление в газгольдере.
	// Считать, что для газа верно уравнение состояния PV = (m/M)RT.
	// Значение постоянной R принять 8.31 Дж/(моль*К).
	float getPressure() { return nu * R * T / V; }

private:
	float nu;
	int T;
	float V;
	float R = 8.31;
};

class SpacePort {
public:
	// Создать космодром, в котором size штук доков.
	// Доки нумеруются от 0 до size-1.
	// В момент создания все доки свободны.
	SpacePort(unsigned int size)
	{
		port = new int(size);
		this->size = size;
		for (int i = 0; i < size; i++)
			port[i] = 0;
	}

	// Запросить посадку в док с номером dockNumber.
	// Если такого дока нет - вернуть false (запрет посадки).
	// Если док есть, но занят - вернуть false (запрет посадки).
	// Если док есть и свободен - вернуть true (разрешение посадки) и док
	// становится занят.
	bool requestLanding(unsigned int dockNumber)
	{
		if (dockNumber < 0 || dockNumber >= size)
			return false;
		else if (port[dockNumber] == 1)
			return false;
		else {
			port[dockNumber] = 1;
			return true;
		}
	}

	// Запросить взлёт из дока с номером dockNumber.
	// Если такого дока нет - вернуть false (запрет взлёта).
	// Если док есть, но там пусто - вернуть false (запрет взлёта).
	// Если док есть и в нём кто-то стоит - вернуть true (разрешение взлёта) и док
	// становится свободен.
	bool requestTakeoff(unsigned int dockNumber)
	{
		if (dockNumber < 0 || dockNumber >= size)
			return false;
		else if (port[dockNumber] == 0)
			return false;
		else {
			port[dockNumber] = 0;
			return true;
		}
	}

	~SpacePort()
	{
		size = 0;
		delete port;
	}

private:
	unsigned int size;
	int *port;
};

class Animal {
public:
	virtual std::string getType() = 0;
	virtual bool isDangerous() = 0;
};

class ZooKeeper {
public:
	// Создаём смотрителя зоопарка
	ZooKeeper() { number_of_dangerous = 0; }

	// Смотрителя попросили обработать очередного зверя.
	// Если зверь был опасный, смотритель фиксирует у себя этот факт.
	void handleAnimal(Animal *a)
	{
		if ((*a).isDangerous())
			number_of_dangerous++;
	}

	// Возвращает, сколько опасных зверей было обработано на данный момент.
	int getDangerousCount() { return number_of_dangerous; }

private:
	int number_of_dangerous;
};

class Material {
public:
	// Принимает на вход величину деформации.
	// Возвращает величину напряжения, посчитанную с учётом реологии материала.
	virtual float getStress(float strain) = 0;
};

class ElasticMaterial : public Material {
public:
	ElasticMaterial(float elasticModulus)
	{
		this->elasticModulus = elasticModulus;
	}
	float getStress(float strain) { return strain * elasticModulus; }

private:
	float elasticModulus;
};

class PlasticMaterial : public Material {
public:
	PlasticMaterial(float elasticModulus, float strainLimit)
	{
		this->elasticModulus = elasticModulus;
		this->strainLimit = strainLimit;
	}
	float getStress(float strain)
	{
		if (strain > this->strainLimit)
			return strainLimit * elasticModulus;
		return strain * elasticModulus;
	}

protected:
	float elasticModulus, strainLimit;
};
