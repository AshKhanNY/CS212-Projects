#include <cassert>   // Provides assert()
#include <cmath>	 // Provides pow(x,y)
#include <climits> 	 // Provides UINT_MAX
using namespace std;
#include "poly0.h"

/* Privates:
 * double coef[CAPACITY];
 * unsigned int current_degree;
 */

namespace main_savitch_3
{
    // CONSTANTS
	const unsigned int polynomial::CAPACITY;
	const unsigned int polynomial::MAX_EX;

    // CONSTRUCTOR
    polynomial::polynomial(double c, unsigned int exponent) {
        assert(exponent <= MAX_EX);
        current_degree = 0;
        clear();
        coef[exponent] = c;
        if (coef[exponent] != 0 && (exponent > current_degree)) current_degree = exponent;
    }

    // MODIFICATION MEMBER FUNCTIONS
    void polynomial::add_to_coef(double amount, unsigned int exponent){
    	assert(exponent <= MAX_EX);
    	coef[exponent] = coef[exponent] + amount;
    	if (coef[exponent] != 0 && (exponent > current_degree)) current_degree = exponent;
    	else if (coef[current_degree] == 0){
    		for (unsigned int i = current_degree - 1; i >= 0; --i){
    			current_degree = i;
    			if (coef[i] != 0) break;
    		}
    	}
    }
    void polynomial::assign_coef(double coefficient, unsigned int exponent){
    	assert(exponent <= MAX_EX);
    	coef[exponent] = coefficient;
    	if (coef[exponent] != 0 && (exponent > current_degree)) current_degree = exponent;
		else if (coef[current_degree] == 0){
			for (unsigned int i = current_degree - 1; i >= 0; --i){
				current_degree = i;
				if (coef[i] != 0) break;
			}
		}
    }
    void polynomial::clear(){
    	for (unsigned int i = 0; i < CAPACITY; ++i) coef[i] = 0;
    	current_degree = 0;
    }

    // CONSTANT MEMBER FUNCTIONS
    double polynomial::coefficient(unsigned int exponent) const{
    	if (exponent > MAX_EX) return 0;
    	else return coef[exponent];
    }
    polynomial polynomial::derivative() const{
    	polynomial d;
    	if (current_degree == 0) return d;
    	else {
    		for (unsigned int i = 0; i < current_degree; ++i) d.coef[i] = (i+1)*(coef[i+1]);
    		d.current_degree = current_degree - 1;
    		return d;
    	}
    }
    double polynomial::eval(double x) const{
    	double sum = 0;
    	for (unsigned int i = 0; i <= current_degree; ++i) sum += pow(x,i)*(coef[i]);
    	return sum;
    }
    unsigned int polynomial::next_term(unsigned int e) const{
    	for (unsigned int i = e+1; i <= current_degree; ++i) if (coef[i] != 0) return i;
    	return 0;
    }
    unsigned int polynomial::previous_term(unsigned int e) const{
    	for (unsigned int i = current_degree; i > 0; --i) if (coef[i] != 0 && i < e) return i;
    	if (coef[0] != 0) return 0;
    	return UINT_MAX;
    }
    // NON-MEMBER BINARY OPERATORS
    polynomial operator +(const polynomial& p1, const polynomial& p2){
    	polynomial d;
    	for (unsigned int i = 0; i < d.CAPACITY; ++i) d.add_to_coef(p1.coefficient(i) + p2.coefficient(i) ,i);
    	return d;
    }
    polynomial operator -(const polynomial& p1, const polynomial& p2){
    	polynomial d;
		for (unsigned int i = 0; i < d.CAPACITY; ++i) d.add_to_coef(p1.coefficient(i) - p2.coefficient(i) ,i);
		return d;
    }
    polynomial operator *(const polynomial& p1, const polynomial& p2){
    	polynomial d;
		for (unsigned int i = 0; i <= p1.degree(); ++i){
		for (unsigned int k = 0; k <= p2.degree(); ++k) d.add_to_coef(p1.coefficient(i)*p2.coefficient(k), i+k); }
		return d;
    }

    // NON-MEMBER OUTPUT FUNCTIONS
    std::ostream& operator << (std::ostream& out, const polynomial& p){
    	for (unsigned int i = p.degree(); i > 0; --i){
    		if (i == p.degree()){
    			out << p.coefficient(i) << "x";
				if (i > 1) out << "^" << i;
    		} else if (p.coefficient(i) != 0){
    			out << abs(p.coefficient(i)) << "x";
    			if (i > 1) out << "^" << i;
    		}
    		if (p.coefficient(i-1) > 0) out << " + ";
    		else if (p.coefficient(i-1) < 0) out << " - ";
    	}
    	if (p.coefficient(0) != 0) out << p.coefficient(0);
    	return out;
    }

    /*
    void make_gif(
        const polynomial& p,
        const char filename[ ],
        double low_x,
        double high_x,
        double low_y,
        double high_y
        );*/
}
