#define POLYNOMIAL_H
#include "AccurateNumber.h"
#include <vector>

class PolynomialTerm {
private:
    AccurateNumber coefficient;
    int power;
public:
    PolynomialTerm(AccurateNumber, int);
    AccurateNumber getCoefficient(void);
    int getPower(void);
    void setCoefficient(AccurateNumber);
    void setPower(int);
};

class Polynomial {
private:
    vector<PolynomialTerm> terms;
    AccurateNumber result;
public:
    Polynomial(vector<PolynomialTerm>, AccurateNumber);
    AccurateNumber valueOfVariable(void);
    vector<PolynomialTerm> getTerms(void);
    AccurateNumber getResult(void);
    void setTerms(vector<PolynomialTerm>);
    void setResult(AccurateNumber);
};

#endif
