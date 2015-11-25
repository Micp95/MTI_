#include"Complex.h"
#include<math.h>

Complex Complex::operator + (Complex c) {
	Complex result(this->re + c.re, this->im + c.im);
	return result;
}

Complex::Complex() {
	this->re = 0;
	this->im = 0;
}

Complex::Complex(double re, double im) {
	this->re = re;
	this->im = im;
}

Complex::Complex(Complex &c) {
	this->re = c.re;
	this->im = c.im;
}

Complex Complex::operator * (double i) {

	Complex result(this->re * i, this->im * i);
	return result;
}

double Complex::abs() {
	return (sqrt((re * re) + (im * im)));
}

Complex Complex::operator * (Complex c) {
	Complex result;
	result.re = ((this->re * c.re) - (this->im * c.im));
	result.im = ((this->re * c.im) + (this->im * c.re));
	
	return result;
}

Complex Complex::power(int n) {
	double abs = this->abs();
	double absN = pow(abs, n);

	//Complex result(absN * (cos(n*re) + sin(n*im)));

	Complex result(absN * cos(n * re), absN * sin(n*re));

	return result;
}

