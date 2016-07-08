#include "Polynomial.h"

PolynomialTerm::PolynomialTerm(AccurateNumber coefficient, int power)
{
    setCoefficient(coefficient);
    setPower(power);
}

AccurateNumber PolynomialTerm::getCoefficient(void)
{
    return coefficient;
}

int PolynomialTerm::getPower(void)
{
    return power;
}

void PolynomialTerm::setCoefficient(AccurateNumber coefficient)
{
    PolynomialTerm::coefficient = coefficient;
}

void PolynomialTerm::setPower(int power)
{
    PolynomialTerm::power = power;
}

Polynomial::Polynomial(vector<PolynomialTerm> terms, AccurateNumber result)
{
    setTerms(terms);
    setResult(result);
}

AccurateNumber Polynomial::valueOfVariable(void)
{
    AccurateNumber testValue, evaluation, increment("1"), one("1");
    unsigned precisionFactor, precisionDestination = 19;
    while (precisionDestination - precisionFactor++)
    {
        while (evaluation.isLessThan(result))
        {
            evaluation -= evaluation; /*
                                       * Evaluation must be set back to zero
                                       * at the start of each iteration of this
                                       * loop.
                                       */
            int index = 0;
            for (;terms.size() - index++;)
                evaluation += (terms[index - 1].getCoefficient() * testValue.power(terms[index - 1].getPower()));
            if (evaluation.isLessThan(result))
                testValue += increment;
        }
        if (increment.isEqualTo(one))
        {
            increment.setIntegerDigits("0");
            increment.setDecimalDigits("1");
        }
        else
            increment.setDecimalDigits("0" + increment.getDecimalDigits());
    }
    return testValue;
}

vector<PolynomialTerm> Polynomial::getTerms(void)
{
    return terms;
}

AccurateNumber Polynomial::getResult(void)
{
    return result;
}

void Polynomial::setTerms(vector<PolynomialTerm> terms)
{
    Polynomial::terms = terms;
}

void Polynomial::setResult(AccurateNumber result)
{
    Polynomial::result = result;
}
