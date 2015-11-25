#ifndef COMPLEX_H
#define COMPLEX_H

class Complex {
public:
	double re;
	double im;
	Complex();
	Complex(Complex &c);
	Complex(double re, double im);

	Complex operator + (Complex);
	Complex operator * (double);
	Complex operator * (Complex);

	double abs();		//funkcja liczaca modul
	Complex power(int n);		//funkcja liczaca n-ta potege liczby zespolonej
};
#endif
