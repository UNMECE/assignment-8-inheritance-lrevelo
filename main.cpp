#include <iostream>
#include <cmath>

const double epsilon_0 = 8.854e-12;
const double mu_0 = 4 * M_PI * 1e-7;

class Field {
protected:
	double *value;

public:
	Field() {
		value = new double[3]{0, 0, 0};
	}

	Field(double x, double y, double z) {
		value = new double[3]{x ,y, z};
	}

	Field(const Field& other) {
		value = new double[3];
		for (int i = 0; i < 3; ++i)
			value[i] = other.value[i];
	}

	Field& operator=(const Field& other) {
		if (this != &other) {
			for (int i = 0; i < 3; i++) value[i] = other.value[i];
		}
		return *this;
	}

	virtual void printMagnitude() const {
		std::cout << "Field components: (" << value[0] << ", " << value[1] << ", " << value[2] << ")\n";
	}

	double getComponent(int i) const {
		return value[i];
	}

	virtual ~Field() {
		delete[] value;
	}
};

class ElectricField : public Field {
private:
	double calculated_E;

public:
	ElectricField() : Field(), calculated_E(0) {}
	ElectricField(double x, double y, double z) : Field(x, y, z), calculated_E(0) {}
	ElectricField(const ElectricField& other) : Field(other), calculated_E(other.calculated_E) {}
	ElectricField& operator=(const ElectricField& other) {
		if (this != &other) {
			Field::operator=(other);
			calculated_E = other.calculated_E;
		}
		return *this;
	}

	void calculate_electric_field(double Q, double r) {
		if (r != 0) {
			calculated_E = Q / (4 * M_PI * epsilon_0 * r * r);
		} else {
			calculated_E = 0;
		}
	}
	
	void print_calculated_E() const {
		std::cout << "Calculated Electric Field (E) from Gauss' Law: " << calculated_E << " N/C" << std::endl;
	}

	ElectricField operator+(const ElectricField& other) const {
		return ElectricField(value[0] + other.value[0],value[1] + other.value[1],value[2] + other.value[2]);
	}

	friend std::ostream& operator<<(std::ostream& os, const ElectricField& ef) {
		os << "Electric Field: (" << ef.value[0] << ", " << ef.value[1] << ", " << ef.value[2] << ")";
		return os;
	}
};


class MagneticField : public Field {
private:
	double calculated_B;

public:
	MagneticField() : Field(), calculated_B(0) {}
	MagneticField(double x, double y, double z) : Field(x, y, z), calculated_B(0) {}
	MagneticField(const MagneticField& other) : Field(other), calculated_B(other.calculated_B) {}

	MagneticField& operator=(const MagneticField& other) {
		if (this != &other) {
			Field::operator=(other);
			calculated_B = other.calculated_B;
		}
		return *this;
	}

	void calculate_magnetic_field(double I, double r) {
		if (r != 0) {
			calculated_B = I / (2 * M_PI * r * mu_0);
		} else {
			calculated_B = 0;
		}
	}

	void print_calculated_B() const  {
		std::cout << "Calculated Magnetic Field (B) from Ampere's Law: " << calculated_B << " T\n";
	}

	MagneticField operator+(const MagneticField& other) const {
		return MagneticField(value[0] + other.value[0],value[1] + other.value[1],value[2] + other.value[2]);
	}

	friend std::ostream& operator<<(std::ostream& os, const MagneticField& mf) {
		os << "Magnetic Field: (" << mf.value[0] << ", " << mf.value[1] << ", " << mf.value[2] << ")";
		return os;
	}
};

int main() {
	ElectricField E1(1e3, 2e3, 3e3);
	MagneticField B1(0.1, 0.2, 0.3);

	E1.printMagnitude();
	B1.printMagnitude();

	E1.calculate_electric_field(1e-6, 0.05); 
	B1.calculate_magnetic_field(5.0, 0.02);

	E1.print_calculated_E();
	B1.print_calculated_B();

	ElectricField E2(100, 200, 300);
	ElectricField E3 = E1 + E2;

	MagneticField B2(0.01, 0.02, 0.03);
	MagneticField B3 = B1 + B2;

	std::cout << E3 << std::endl;
	std::cout << B3 << std::endl;

	return 0;
}






