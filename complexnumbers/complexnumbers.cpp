#include <iostream>
#include <math.h>
#include <string>

#define LOG(x) std::cout << x << std::endl
#define NL std::cout << std::endl;


struct cpx
{
	cpx();
	cpx(double);
	cpx(double, double);

	double getRe() const;
	double getIm() const;
	void setRe(double);
	void setIm(double);

	friend std::ostream& operator<<(std::ostream&, const cpx&);
	cpx operator+(const cpx&) const;
	cpx operator-(const cpx&) const;
	cpx operator*(const cpx&) const;
	cpx operator/(const cpx&) const;
	cpx pow(int) const;

	std::string trForm;


private:
	double re;
	double im;

	void initTrForm();
	double mod, sin, cos;
};


cpx::cpx()
	: re(0), im(0)
{
	initTrForm();
}

cpx::cpx(double re)
	: re(re), im(0)
{
	initTrForm();
}

cpx::cpx(double re, double im)
	: re(re), im(im)
{
	initTrForm();
}

void cpx::initTrForm()
{
	mod = sqrt((re * re) + (im * im));
	sin = im / mod;
	cos = re / mod;
	if (!mod)
	{
		trForm = "0";
	}
	else
	{
		trForm = std::to_string(mod) + " (" + std::to_string(cos);
		if (sin > 0) trForm += " + "; else trForm += " ";
		trForm += std::to_string(sin) + "i)";
	}
}

double cpx::getRe() const
{
	return this->re;
}

double cpx::getIm() const
{
	return this->im;
}

void cpx::setRe(double value)
{
	this->re = value;
	initTrForm();
}

void cpx::setIm(double value)
{
	this->im = value;
	initTrForm();
}


std::ostream& operator<<(std::ostream& os, const cpx& cp)
{
	if (cp.re)
	{
		os << cp.re;
		if (cp.im > 0) os << " + " << cp.im << "i";
		else if (cp.im < 0) os << " " << cp.im << "i";
	}
	else if (cp.im) os << cp.im << "i";

	return os;
}

cpx cpx::operator+(const cpx& other) const
{
	cpx z(this->re + other.re, this->im + other.im);

	return z;
}

cpx cpx::operator-(const cpx& other) const
{
	cpx z(this->re - other.re, this->im - other.im);

	return z;
}

cpx cpx::operator*(const cpx& other) const
{
	cpx z;
	z.setRe((this->re * other.re) - (this->im * other.im));
	z.setIm((this->re * other.im) + (this->im * other.re));

	return z;
}

cpx cpx::operator/(const cpx& other) const
{
	cpx z;
	double den = (other.re * other.re) + (other.im * other.im);
	if (den > 0)
	{
		z.setRe(((this->re * other.re) + (this->im * other.im)) / den);
		z.setIm(((this->im * other.re) - (this->re * other.im)) / den);
	}
	else LOG("Niepoprawny mianownik");
	
	return z;
}

cpx cpx::pow(int x = 2) const
{
	cpx z(this->re, this->im);
	
	if (!x)
	{
		z.setRe(1);
		z.setIm(0);

		return z;
	}

	if (x < 0)
	{
		LOG("Niepoprawny wykladnik");
		return z;
	}

	if (x == 1) return z;
	else return z * z.pow(x - 1);
}



int main()
{
	cpx z1(5, 12);
	cpx z2(7, -4);

	LOG("z1:");
	LOG(z1);
	LOG(z1.trForm);
	LOG("z2:");
	LOG(z2);
	LOG(z2.trForm);
	NL

	LOG("z1 + z2:");
	LOG(z1 + z2);
	LOG((z1 + z2).trForm);
		NL

	LOG("z1 - z2:");
	LOG(z1 - z2);
	LOG((z1 - z2).trForm);
		NL

	LOG("z1 * z2:");
	LOG(z1 * z2);
	LOG((z1 * z2).trForm);
		NL

	LOG("z1 / z2:");
	LOG(z1 / z2);
	LOG((z1 / z2).trForm);
		NL

	LOG("z1 ^ 2:");
	LOG(z1.pow());
	LOG(z1.pow().trForm);
		NL

	LOG("z1 ^ 5:");
	LOG(z1.pow(5));
	LOG(z1.pow(5).trForm);
	NL
}