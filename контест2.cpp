class Car {
protected:
	bool allowesBoarding;
	bool allowesLoading;
	unsigned int numberOfSeats;
	unsigned int numberOfContainers;

public:
	Car(bool allowesBoarding, bool allowesLoading, unsigned int numberOfSeats,
	    unsigned int numberOfContainers)
	{
		this->allowesBoarding = allowesBoarding;
		this->allowesLoading = allowesLoading;
		this->numberOfSeats = numberOfSeats;
		this->numberOfContainers = numberOfContainers;
	}
	~Car() {}

	bool isBoardingAllowed() const { return allowesBoarding; }

	bool isLoadingAllowed() const { return allowesLoading; }

	unsigned int getNumberOfSeats() const { return numberOfSeats; }

	unsigned int getNumberOfContainers() const { return numberOfContainers; }
};

class ConvoyManager {
public:
	// Зарегистрировать новую машину в колонне
	void registerCar(const Car &c)
	{
		if (c.isBoardingAllowed()) {
			this->total_seats += c.getNumberOfSeats();
		}
		if (c.isLoadingAllowed()) {
			this->total_containers += c.getNumberOfContainers();
		}
	}

	// Сообщить, сколько всего пассажиров может принять колонна
	unsigned int getTotalSeats() const { return this->total_seats; }

	// Сообщить, сколько всего грузовых контейнеров может взять колонна
	unsigned int getTotalContainers() const { return this->total_containers; }

private:
	unsigned int total_seats = 0;
	unsigned int total_containers = 0;
};
