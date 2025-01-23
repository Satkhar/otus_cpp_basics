#include <iostream>
#include <limits>
#include <inttypes.h>
#include <vector>
#include <numeric>
#include <cmath>

//------------------------------------------------------------

// базовый класс. содежрит методы, переопределяемые в каждом наследнике
class IStatistics {
public:
	virtual ~IStatistics() {}

	virtual void update(double next) = 0;
	virtual double eval() const = 0;
	virtual const char * name() const = 0;
};

//------------------------------------------------------------

// класс для минимума.
class Min : public IStatistics {
public:
	// Min() : m_min{std::numeric_limits<double>::min()} {
	Min() : m_min{std::numeric_limits<double>::max()} {
	}

	void update(double next) override {
		if (next < m_min) {
			m_min = next;
		}
	}

	double eval() const override {
		return m_min;
	}

	const char * name() const override {
		return "min";
	}

private:
	double m_min;
};

//------------------------------------------------------------

// класс для максимума.
class Max : public IStatistics {
public:
	Max() : m_max{-std::numeric_limits<double>::max()} {		// инициализация минимально возможным значением. почему не нулём?
	}

	void update(double next) override {
		if (next > m_max) {
			m_max = next;
		}
	}

	double eval() const override {
		return m_max;
	}

	const char * name() const override {
		return "max";
	}

private:
	double m_max;
};

//------------------------------------------------------------

// класс для среднего.
class Mean : public IStatistics {
public:
	Mean() : m_mean{0.}, m_count{(uint64_t)0}, m_summ{0.} {
	}

	void update(double next) override {
		{
			m_count++;
			m_summ += next;
			m_mean = m_summ/m_count;
		}
	}

	double eval() const override {
		return m_mean;
	}

	const char * name() const override {
		return "mean";
	}

private:
	double m_mean;
	uint64_t m_count;	// счетчик для среднего (берем максимальную размерность)
	double m_summ;
};

//------------------------------------------------------------

// класс для среднеквадратичного.
class StdDev : public IStatistics {
public:
	StdDev() : m_mean{0.}, m_count{(uint64_t)0}, m_summ{0.}, m_dispersion{0.}
	 {}

	void update(double next) override {
		{
			// среднее
			m_count++;
			m_summ += next;
			m_mean = m_summ/m_count;

			// дисперсия
			// diff = (next-mean) 			// значение - среднее
			// squaredDiff += diff*diff		// разницу в квадрат и суммируем
			// dispersion = squaredDiff/(count - 1)	// делим на количество чисел - 1
			// не понятно как можно это посчитать без хранения всего массива чисел, нужна помощь

			// m_squaredDiff += (next - m_mean)*(next - m_mean);
			// m_dispersion = m_squaredDiff/(m_count - 1);

			m_data.push_back(next);	// сохраняем введеные числа

			// каждый раз должна вычисляться т.к. меняется среднее

			// объявляем итератор
			std::vector<double>::iterator it;
			
			std::vector<double> m_squaredDiff;

			//проходим по всему массиву введенных чисел
			// for(it = m_data.begin(); it != m_data.end(); it++)
			for(int i = 0; i < m_data.size(); i++)
			{
				m_diff = (m_data[i] - m_mean)*(m_data[i] - m_mean);
				m_squaredDiff.push_back(m_diff);	// вычисляем квадрат отклонения и добавляем в вектор 
			}
			double temp = std::accumulate(m_squaredDiff.begin(), m_squaredDiff.end(), 0);
			m_dispersion = temp/(double)((double)m_count-1.0); 
			
			m_stdDev = sqrt(m_dispersion);
		}
	}

	double eval() const override {
		return m_dispersion;
	}

	const char * name() const override {
		return "stdDev";
	}

private:
	double m_mean;
	uint64_t m_count;	// счетчик для среднего (берем максимальную размерность)
	double m_summ;
	double m_diff;
	double m_dispersion;
	std::vector<double> m_data;
	double m_stdDev;
};

//------------------------------------------------------------
// 0 1 2 3 4 5 6 7 8 9 10
// 2 4 4 4 5 5 7 9
//------------------------------------------------------------

int main() {

	const size_t statistics_count = 4;
	IStatistics *statistics[statistics_count];

	statistics[0] = new Min{};
	statistics[1] = new Max{};
	statistics[2] = new Mean{};
	statistics[3] = new StdDev{};

	double val = 0.0;
	while (std::cin >> val) {
		for (size_t i = 0; i < statistics_count; ++i) {
			statistics[i]->update(val);
		}
	}

	// Handle invalid input data
	if (!std::cin.eof() && !std::cin.good()) {
		std::cerr << "Invalid input data\n";
		return 1;
	}

	// Print results if any
	for (size_t i = 0; i < statistics_count; ++i) {
		std::cout << statistics[i]->name() << " = " << statistics[i]->eval() << std::endl;
	}

	// Clear memory - delete all objects created by new
	for (size_t i = 0; i < statistics_count; ++i) {
		delete statistics[i];
	}

	return 0;
}