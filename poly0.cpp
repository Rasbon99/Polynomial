/*
 * poly0.cpp
 *
 *  Created on: 5 nov 2019
 *      Author: lollo
 */
#include "poly0.h"
#include <iostream>
#include <cassert>
#include <math.h>
#include <climits>

namespace lorenzom
{
	// CONSTRUCTOR
	polynomial::polynomial(double c,unsigned int exponent)
	{
		assert(exponent<MAX_EX);
		coef[exponent]=c;
		current_degree=exponent;
	}

	// MODIFICATION MEMBER FUNCTIONS
	void polynomial::add_to_coef(double amount,unsigned int exponent)
	{
		assert(exponent<MAX_EX);
		if(exponent>current_degree) {current_degree=exponent;}
		coef[exponent]+=amount;
	}

	void polynomial::assign_coef(double coefficient,unsigned int exponent)
	{
		assert(exponent<MAX_EX);
		if(exponent>current_degree) {current_degree=exponent;}
		coef[exponent]=coefficient;
	}

	void polynomial::clear()
	{
		for(unsigned int i=0;i<=current_degree;i++)
		{
			coef[i]=0;
		}
	}

	// CONSTANT MEMBER FUNCTIONS
	double polynomial::coefficient(unsigned int exponent) const
	{
		if(exponent>MAX_EX){return 0;}
		return coef[exponent];
	}

	polynomial polynomial::derivative() const
	{
		polynomial p;
		for (unsigned int i=1;i<current_degree;i++)
		{
			p.coef[i-1]=coef[i]*(double)i;
		}

		return p;
	}

	double polynomial::eval(double x) const

	{
		double sum;

		for(unsigned int i=0;i<current_degree;i++)
		{
			sum+=coef[i]*pow(x,i);
		}

		return sum;
	}

	unsigned int polynomial::next_term(int unsigned e) const
	{
		unsigned int n=e++;
		if(n==0 || coef[n]==NULL){return 0;}
		else {return n;}
	}

	unsigned int polynomial::previous_term(int unsigned e) const
	{
		unsigned int n=e--;

		if(n==0 || coef[n]==NULL) {return UINT_MAX;}
		else {return n;}
	}

	// NON-MEMBER BINARY OPERATORS
	polynomial operator + (const polynomial& p1, const polynomial& p2)
	{
		polynomial p;
		unsigned int MAX_current_degree;
		if(p1.degree()>p2.degree()) {MAX_current_degree=p1.degree();}
		else {MAX_current_degree=p2.degree();}
		for(unsigned int i=0;i<MAX_current_degree;i++)
		{
			p.assign_coef(p1.coefficient(i)+p2.coefficient(i), i);
		}

		return p;
	}

	polynomial operator - (const polynomial& p1, const polynomial& p2)
	{
		polynomial p;
		unsigned int MAX_current_degree;
		if(p1.degree()>p2.degree()) {MAX_current_degree=p1.degree();}
		else {MAX_current_degree=p2.degree();}

		for(unsigned int i=0;i<MAX_current_degree;i++)
		{
			p.assign_coef(p1.coefficient(i)-p2.coefficient(i), i);
		}

		return p;
	}

	polynomial operator * (const polynomial& p1, const polynomial& p2)
	{
		polynomial p;
		p.assign_coef(0, p1.degree()+p2.degree());
		p.clear();
		assert(p1.degree()+p2.degree()<polynomial::MAX_EX);


		for(unsigned int i1=0;i1<p1.degree;i1++)
			for(unsigned int i2=0;i2<p2.degree;i1++)
				p.add_to_coef((p1.coefficient(i1)*p2.coefficient(i2)), i1+i2);

		return p;

	}

	std::ostream& operator << (std::ostream& out, const polynomial& p)
	{
		for(unsigned int i=0;i<p.degree();i++)
		{
			out<< p.coefficient(i)<<"x^"<<i;
		}

		return out;

	}

}







