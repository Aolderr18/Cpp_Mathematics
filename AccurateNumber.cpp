#include "AccurateNumber.h"
#include <sstream>
#include <cmath>

AccurateNumber::AccurateNumber(void)
{
    /*
     * A default constructor is essential for 
     * implementations of AccurateNumber.
     */
    setNonNegative(true); // By default, a number should be nonnegative.
}

AccurateNumber::AccurateNumber(string integerDigits)
{
    setNonNegative(true); 
    setIntegerDigits(integerDigits);
}

AccurateNumber::AccurateNumber(string integerDigits, string decimalDigits)
{
    setNonNegative(true); 
    setIntegerDigits(integerDigits);
    setDecimalDigits(decimalDigits);
}

AccurateNumber::AccurateNumber(bool nonNegative, string integerDigits, string decimalDigits)
{
    setNonNegative(nonNegative);
    setIntegerDigits(integerDigits);
    setDecimalDigits(decimalDigits);
}

string AccurateNumber::userVisibleRepresentation(void)
{
    trimZeros();
    if (nonNegative)
    {
        if (decimalDigits.length())
            return integerDigits + "." + decimalDigits;
        if (integerDigits.length())
            return integerDigits;
        return "0";
    }
    if (decimalDigits.length())
        return "-" + integerDigits + "." + decimalDigits;
    return "-" + integerDigits;
}

AccurateNumber AccurateNumber::sum(AccurateNumber other)
{
    AccurateNumber duplicate(nonNegative, integerDigits, decimalDigits);
    if (nonNegative xor other.isNonNegative())
    {
        if (hasGreaterAbsoluteValueThan(other))
        {
            other.setNonNegative(nonNegative);
            return difference(other);
            /*
             * If a negative number is being added to a positive number with a 
             * greater absolute value, it is roughly equivalent to subtracting 
             * the additive inverse of that number.
             */
        }
        duplicate.setNonNegative(other.isNonNegative());
        return other.difference(duplicate);
    }
    stringstream operand1, operand2;
    unsigned differenceInLength = 0;
    /*
     * Both operand strings must have the same length for the algorithm to work.
     */
    if (integerDigits.length() > other.getIntegerDigits().length())
    {
        differenceInLength = integerDigits.length() - other.getIntegerDigits().length();
        while (differenceInLength)
        {
            operand2 << "0";
            differenceInLength--;
        }
    }
    else
    {
        differenceInLength = other.getIntegerDigits().length() - integerDigits.length();
        while (differenceInLength)
        {
            operand1 << "0";
            differenceInLength--;
        }
    }
    operand1 << integerDigits << decimalDigits;
    operand2 << other.getIntegerDigits() << other.getDecimalDigits();
    unsigned digitsAfterDecimal = 0;
    if (decimalDigits.length() > other.getDecimalDigits().length())
    {
        digitsAfterDecimal = decimalDigits.length();
        differenceInLength = decimalDigits.length() - other.getDecimalDigits().length();
        while (differenceInLength)
        {
            operand2 << "0";
            differenceInLength--;
        }
    }
    else
    {
        digitsAfterDecimal = other.getDecimalDigits().length();
        differenceInLength = other.getDecimalDigits().length() - decimalDigits.length();
        while (differenceInLength)
        {
            operand1 << "0";
            differenceInLength--;
        }
    }
    unsigned index, carry = 0;
    stringstream sumDigits;
    for (index = operand1.str().length() - 1; index + 1; index--)
    {
        unsigned placeSum = carry + operand1.str().at(index) + operand2.str().at(index) - 96;
        carry = (placeSum - placeSum % 10) / 10;
        placeSum %= 10;
        sumDigits << placeSum;
    }
    sumDigits << carry;
    stringstream sumIntegerDigits, sumDecimalDigits;
    for (index = sumDigits.str().length() - 1; index + 1; index--)
    {
        if (index < digitsAfterDecimal)
        {
            sumDecimalDigits << sumDigits.str().at(index);
            continue;
        }
        sumIntegerDigits << sumDigits.str().at(index);
    }
    duplicate.setIntegerDigits(sumIntegerDigits.str());
    duplicate.setDecimalDigits(sumDecimalDigits.str());
    duplicate.trimZeros();
    return duplicate;
}

AccurateNumber AccurateNumber::difference(AccurateNumber other)
{
    AccurateNumber duplicate(nonNegative, integerDigits, decimalDigits);
    if (nonNegative xor other.isNonNegative())
    {
        other.setNonNegative(nonNegative);
        return sum(other);
    }
    if (hasLowerAbsoluteValueThan(other))
    {
        other.setNonNegative(not other.isNonNegative());
        setNonNegative(not nonNegative);
        return other.difference(duplicate);
    }
    stringstream operand1, operand2;
    unsigned differenceInLength = 0;
    unsigned totalLength = 0;
    if (integerDigits.length() > other.getIntegerDigits().length())
    {
        totalLength += integerDigits.length();
        differenceInLength = integerDigits.length() - other.getIntegerDigits().length();
        while (differenceInLength)
        {
            operand2 << "0";
            differenceInLength--;
        }
    }
    else
    {
        totalLength += other.getIntegerDigits().length();
        differenceInLength = other.getIntegerDigits().length() - integerDigits.length();
        while (differenceInLength)
        {
            operand1 << "0";
            differenceInLength--;
        }
    }
    operand1 << integerDigits << decimalDigits;
    operand2 << other.getIntegerDigits() << other.getDecimalDigits();
    unsigned digitsAfterDecimal = 0;
    if (decimalDigits.length() > other.getDecimalDigits().length())
    {
        totalLength += decimalDigits.length();
        digitsAfterDecimal = decimalDigits.length();
        differenceInLength = decimalDigits.length() - other.getDecimalDigits().length();
        while (differenceInLength)
        {
            operand2 << "0";
            differenceInLength--;
        }
    }
    else
    {
        totalLength += other.getDecimalDigits().length();
        digitsAfterDecimal = other.getDecimalDigits().length();
        differenceInLength = other.getDecimalDigits().length() - decimalDigits.length();
        while (differenceInLength)
        {
            operand1 << "0";
            differenceInLength--;
        }
    }
    unsigned operand1Digits[totalLength];
    unsigned operand2Digits[totalLength];
    int index;
    for (index = 0; totalLength - index; index++)
    {
        operand1Digits[index] = operand1.str().at(index) - 48;
        operand2Digits[index] = operand2.str().at(index) - 48;
    }
    stringstream differenceDigits;
    for (index = totalLength - 1; index + 1; index--)
    {
        int borrowIndex = index;
        unsigned placeDifference;
        if (operand1Digits[index] >= operand2Digits[index])
            placeDifference = operand1Digits[index] - operand2Digits[index];
        else
        {
            placeDifference = 10 + operand1Digits[index] - operand2Digits[index];
            try
            {
                do
                {
                    --borrowIndex;
                    operand1Digits[borrowIndex] += 10;
                    operand1Digits[borrowIndex] %= 11;
                }
                while (!(operand1Digits[borrowIndex]));
            }
            catch (std::exception outOfBounds)
            {
                
            }
        }
        differenceDigits << placeDifference;
    }
    stringstream differenceIntegerDigits, differenceDecimalDigits;
    for (index = differenceDigits.str().length() - 1; index + 1; index--)
    {
        if (index < digitsAfterDecimal)
        {
            differenceDecimalDigits << differenceDigits.str().at(index);
            continue;
        }
        differenceIntegerDigits << differenceDigits.str().at(index);
    }
    duplicate.setIntegerDigits(differenceIntegerDigits.str());
    duplicate.setDecimalDigits(differenceDecimalDigits.str());
    duplicate.trimZeros();
    return duplicate;
}

AccurateNumber AccurateNumber::product(AccurateNumber other)
{
    AccurateNumber product;
    AccurateNumber Zero(true, "0", "0");
    if (isEqualTo(Zero) or other.isEqualTo(Zero))
    {
        product.setIntegerDigits("0");
        product.setDecimalDigits("0");
        product.setNonNegative(true);
        return product;/*
                        * Zero multiplied by any number returns zero.
                        */
    }
    if (nonNegative xor other.isNonNegative())
        product.setNonNegative(false);/*
                                       * A negative multiplied by a positive
                                       * returns a negative.
                                       */
    else
        product.setNonNegative(true);/*
                                      * A negative multiplied by a negative or
                                      * a positive multiplied by a positive returns
                                      * a positive.
                                      */
    stringstream operand1, operand2;
    unsigned differenceInLength = 0;
    if (integerDigits.length() > other.getIntegerDigits().length())
    {
        differenceInLength = integerDigits.length() - other.getIntegerDigits().length();
        while (differenceInLength)
        {
            operand2 << "0";
            differenceInLength--;
        }
    }
    else
    {
        differenceInLength = other.getIntegerDigits().length() - integerDigits.length();
        while (differenceInLength)
        {
            operand1 << "0";
            differenceInLength--;
        }
    }
    operand1 << integerDigits << decimalDigits;
    operand2 << other.getIntegerDigits() << other.getDecimalDigits();
    unsigned digitsAfterDecimal = decimalDigits.length() + other.getDecimalDigits().length();
    if (decimalDigits.length() > other.getDecimalDigits().length())
    {
        differenceInLength = decimalDigits.length() - other.getDecimalDigits().length();
        while (differenceInLength)
        {
            operand2 << "0";
            digitsAfterDecimal++;
            differenceInLength--;
        }
    }
    else
    {
        differenceInLength = other.getDecimalDigits().length() - decimalDigits.length();
        while (differenceInLength)
        {
            operand1 << "0";
            digitsAfterDecimal++;
            differenceInLength--;
        }
    }
    string productRows[operand2.str().length()];
    int indexA = 0, indexB = 0;
    unsigned carry = 0;
    for (indexB = operand2.str().length() - 1; indexB + 1; indexB--)
    {
        stringstream productRow;
        unsigned rowShift = operand2.str().length() - 1 - indexB;
        while (--rowShift + 1)
            productRow << "0";
        for (indexA = operand1.str().length() - 1; indexA + 1; indexA--)
        {
            unsigned placeProduct = carry + (operand1.str().at(indexA) - 48) * (operand2.str().at(indexB) - 48);
            carry = (placeProduct - placeProduct % 10) / 10;
            placeProduct %= 10;
            productRow << placeProduct;
        }
        productRow << carry;
        carry = 0;
        stringstream reversedProductRow; // Each product row must be reversed
        for (int h = productRow.str().length() - 1; h + 1; h--)
            reversedProductRow << productRow.str().at(h);
        productRows[operand2.str().length() - indexB - 1] = reversedProductRow.str();
    }
    unsigned index;
    for (index = 0; operand2.str().length() - index; index++)
    {
        AccurateNumber rowSum(productRows[index], "");
        product = product.sum(rowSum);
    }
    stringstream productIntegerDigits, productDecimalDigits;
    string productDigits = product.getIntegerDigits();
    for (index = 0; productDigits.length() - index; index++)
    {
        if (index + 1 > productDigits.length() - digitsAfterDecimal)
        {
            productDecimalDigits << productDigits.at(index);
            continue;
        }
        productIntegerDigits << productDigits.at(index);
    }
    AccurateNumber Product(product.isNonNegative(), productIntegerDigits.str(), productDecimalDigits.str());
    Product.trimZeros();
    return Product;
}

AccurateNumber AccurateNumber::quotient(AccurateNumber other)
{
    AccurateNumber Quotient, Divisor(other.getIntegerDigits(), other.getDecimalDigits());
    string dividendDigits = integerDigits + decimalDigits;
    string divisorDigits = Divisor.getIntegerDigits() + Divisor.getDecimalDigits();
    stringstream quotientDigits;
    unsigned digitsBeforeDecimal = integerDigits.length() - other.getIntegerDigits().length();
    if (dividendDigits.at(0) >= divisorDigits.at(0))
        ++digitsBeforeDecimal;
    unsigned placeIndex = 0;
    AccurateNumber temporaryDividend(dividendDigits.substr(placeIndex++, 1));
    unsigned precisionFactor = 0, precisionDestination = 129;
    while (precisionDestination - precisionFactor++)
    {
        while (Divisor > temporaryDividend)
        {
            if (placeIndex < dividendDigits.length())
                temporaryDividend.setIntegerDigits(temporaryDividend.getIntegerDigits() + dividendDigits.substr(placeIndex++, 1));
            else
            {
                if (temporaryDividend == Divisor - Divisor)
                    break;
                temporaryDividend.setIntegerDigits(temporaryDividend.getIntegerDigits() + "0");
            }
            if (Divisor > temporaryDividend)
                quotientDigits << "0";
        }
        AccurateNumber temporaryFactor("1"), increment("1"), temporaryProduct = Divisor * temporaryFactor;
        while (temporaryProduct <= temporaryDividend)
        {
            temporaryFactor += increment;
            temporaryProduct = Divisor * temporaryFactor;
        }
        temporaryFactor -= increment;
        quotientDigits << temporaryFactor.userVisibleRepresentation();
        temporaryProduct = Divisor * temporaryFactor;
        temporaryDividend -= temporaryProduct;
    }
    placeIndex -= placeIndex;
    stringstream quotientIntegerDigits, quotientDecimalDigits;
    while (quotientDigits.str().length() - placeIndex++)
    {
        if (placeIndex - 1 < digitsBeforeDecimal)
        {
            quotientIntegerDigits << quotientDigits.str().substr(placeIndex - 1, 1);
            continue;
        }
        quotientDecimalDigits << quotientDigits.str().substr(placeIndex - 1, 1);
    }
    Quotient.setIntegerDigits(quotientIntegerDigits.str());
    Quotient.setDecimalDigits(quotientDecimalDigits.str());
    if (nonNegative xor other.isNonNegative())
        Quotient.setNonNegative(false);
    return Quotient;
}

AccurateNumber AccurateNumber::modulus(AccurateNumber other)
{
    AccurateNumber Quotient = quotient(other);
    AccurateNumber Modulus, temporary;
    temporary.setDecimalDigits(Quotient.getDecimalDigits());
    bool negative;
    if (not other.isNonNegative())
        negative = true;
    if (nonNegative xor other.isNonNegative())
    {
        other.setNonNegative(true);
        Modulus = other - (other * temporary);
    }
    else
    {
        other.setNonNegative(true);
        Modulus = other * temporary;
    }
    Modulus.setNonNegative(not negative);
    return Modulus;
}

AccurateNumber AccurateNumber::power(int x)
{
    AccurateNumber one("1"), duplicate(nonNegative, integerDigits, decimalDigits);
    if (x < 0)
        return one.quotient(power(-x));
    if (x == 0)
        return one; // Any number raised to the zero power is 1.
    if (x == 1)
        return duplicate; // Any number raised to the first power is itself.
    AccurateNumber Power("1");
    unsigned times = 0;
    while (x - ++times + 1)
        Power = Power.product(duplicate);
    return Power;
}

AccurateNumber AccurateNumber::root(int x)
{
    AccurateNumber one("1", ""), duplicate(nonNegative, integerDigits, decimalDigits);
    if (x < 0)
        return one.quotient(power(-x));
    if (x == 0)
        return one;
    if (x == 1)
        return duplicate;
    AccurateNumber Root("1", ""), increment("1", "");
    unsigned precisionDestination = 129, precisionFactor = 0;
    while (precisionDestination - precisionFactor)
    {
        bool decrementNecessary = true;
        AccurateNumber temp = Root.power(x);
        while (isGreaterThanOrEqualTo(temp))
        {
            if (Root.getDecimalDigits().length() > 1)
                if (Root.getDecimalDigits().substr(Root.getDecimalDigits().length() - 2, 2) == "99")
                {
                    decrementNecessary = false;
		    Root.setDecimalDigits(Root.getDecimalDigits() + "0");
		    break;
                }
            Root = Root.sum(increment);
            temp = Root.power(x);
        }
        if (decrementNecessary)
            Root = Root.difference(increment);
        decrementNecessary = true;
        if (precisionFactor == 0)
        {
            increment.setIntegerDigits("0");
            increment.setDecimalDigits("1");
        }
        else
            increment.setDecimalDigits("0" + increment.getDecimalDigits());
        precisionFactor++;
    }
    Root.trimZeros();
    return Root;
}

AccurateNumber AccurateNumber::operator+(AccurateNumber other) throw(std::exception)
{
    return sum(other);
}

AccurateNumber AccurateNumber::operator-(AccurateNumber other) throw(std::exception)
{
    return difference(other);
}

AccurateNumber AccurateNumber::operator*(AccurateNumber other) throw(std::exception)
{
    return product(other);
}

AccurateNumber AccurateNumber::operator/(AccurateNumber other) throw(std::exception)
{
    return quotient(other);
}

AccurateNumber AccurateNumber::operator%(AccurateNumber other) throw(std::exception)
{
    return modulus(other);
}

void AccurateNumber::operator+=(AccurateNumber other) throw(std::exception)
{
    AccurateNumber sum = this->sum(other);
    setIntegerDigits(sum.getIntegerDigits());
    setDecimalDigits(sum.getDecimalDigits());
    setNonNegative(sum.isNonNegative());
}

void AccurateNumber::operator-=(AccurateNumber other) throw(std::exception)
{
    AccurateNumber difference = this->difference(other);
    setIntegerDigits(difference.getIntegerDigits());
    setDecimalDigits(difference.getDecimalDigits());
    setNonNegative(difference.isNonNegative());
}

void AccurateNumber::operator*=(AccurateNumber other) throw(std::exception)
{
    AccurateNumber product = this->product(other);
    setIntegerDigits(product.getIntegerDigits());
    setDecimalDigits(product.getDecimalDigits());
    setNonNegative(product.isNonNegative());
}

void AccurateNumber::operator/=(AccurateNumber other) throw(std::exception)
{
    AccurateNumber quotient = this->quotient(other);
    setIntegerDigits(quotient.getIntegerDigits());
    setDecimalDigits(quotient.getDecimalDigits());
    setNonNegative(quotient.isNonNegative());
}

void AccurateNumber::operator%=(AccurateNumber other) throw(std::exception)
{
    AccurateNumber modulus = this->modulus(other);
    setIntegerDigits(modulus.getIntegerDigits());
    setDecimalDigits(modulus.getDecimalDigits());
    setNonNegative(modulus.isNonNegative());
}

bool AccurateNumber::operator<(AccurateNumber other) throw(std::exception)
{
    return isLessThan(other);
}

bool AccurateNumber::operator==(AccurateNumber other) throw(std::exception)
{
    return isEqualTo(other);
}

bool AccurateNumber::operator>(AccurateNumber other) throw(std::exception)
{
    return isGreaterThan(other);
}

bool AccurateNumber::operator<=(AccurateNumber other) throw(std::exception)
{
    return isLessThanOrEqualTo(other);
}

bool AccurateNumber::operator>=(AccurateNumber other) throw(std::exception)
{
    return isGreaterThanOrEqualTo(other);
}

void AccurateNumber::trimZeros()
{
    if (integerDigits.length())
        try
        {
            while (integerDigits.at(0) == '0')
                setIntegerDigits(integerDigits.substr(1, integerDigits.length() - 1));
            /*
             * The integer digits should be repeatedly updated until they no longer
             * start with a "0". 
             */
        }
        catch (std::exception outOfBounds)
        {
            /*
             * Deleting all unnecessary zeros may make the string representing
             * the integer digits empty.
             */
        }
    if (decimalDigits.length())
        try
        {
            while (decimalDigits.at(decimalDigits.length() - 1) == '0')
                setDecimalDigits(decimalDigits.substr(0, decimalDigits.length() - 1));
            /*
             * The decimal digits should be repeatedly updated until they no longer
             * end with a "0".
             */
        }
        catch (std::exception outOfBounds)
        {
            /*
             * Deleting all unnecessary zeros may make the string representing
             * the decimal digits empty.
             */
        }
}

void AccurateNumber::round(int place)
{
    if (place < 0)
        try
        {
            setDecimalDigits(decimalDigits.substr(0, -1 * place));
        }
        catch (std::exception outOfBounds)
        {
            /*
             * The desired place to round to may round beyond the available
             * digits.
             */
        }
    else
    {
        setIntegerDigits(integerDigits.substr(0, integerDigits.length() - place));
        while (--place + 1)
            setIntegerDigits(integerDigits + "0");
	setDecimalDigits("");
    }
}

bool AccurateNumber::hasGreaterAbsoluteValueThan(AccurateNumber other)
{
    stringstream comparativeA, comparativeB;
    unsigned differenceInLength, totalLength;
    // Both comparatives must be of the same length.
    if (integerDigits.length() > other.getIntegerDigits().length())
    {
        totalLength = integerDigits.length();
        differenceInLength = integerDigits.length() - other.getIntegerDigits().length();
    }
    else
    {
        totalLength = other.getIntegerDigits().length();
        differenceInLength = other.getIntegerDigits().length() - integerDigits.length();
    }
    while (--differenceInLength + 1)
        if (integerDigits.length() > other.getIntegerDigits().length())
            comparativeB << "0";
        else
            comparativeA << "0";
    comparativeA << integerDigits;
    comparativeB << other.getIntegerDigits();
    unsigned comparisonIndex = 0;
    while (totalLength - comparisonIndex)
    {
        if (comparativeA.str().at(comparisonIndex) < comparativeB.str().at(comparisonIndex))
            return false;
        /*
         * If any digit starting from the beginning indices of each number is less
         * than the one it is being compared to, the number will always be less than
         * the one it is being compared to.
         */
        else if (comparativeA.str().at(comparisonIndex) > comparativeB.str().at(comparisonIndex))
            return true;
        /*
         * If any digit starting from the beginning indices of each number is greater
         * than the one it is being compared to, the number will always be greater than
         * the one it is being compared to.
         */
        comparisonIndex++;
    }
    /*
     * If the integer digits of both numbers are equal, their decimal digits
     * must be compared.
     */
    if (other.getDecimalDigits().length() + decimalDigits.length())
    {
        comparativeA.str("");
        comparativeB.str("");
        differenceInLength = 1 + std::abs(integerDigits.length() - other.getIntegerDigits().length());
        comparativeA << decimalDigits;
        comparativeB << other.getDecimalDigits();
        while (--differenceInLength + 1)
            if (decimalDigits.length() > other.getDecimalDigits().length())
                comparativeB << "0";
            else if (decimalDigits.length() < other.getDecimalDigits().length())
                comparativeA << "0";
        AccurateNumber newComparativeA(comparativeA.str(), ""), newComparativeB(comparativeB.str(), "");
        return newComparativeA.hasGreaterAbsoluteValueThan(newComparativeB);
    }
    return false;
}

bool AccurateNumber::hasLowerAbsoluteValueThan(AccurateNumber other)
{
    stringstream comparativeA, comparativeB;
    unsigned differenceInLength, totalLength;
    if (integerDigits.length() > other.getIntegerDigits().length())
    {
        totalLength = integerDigits.length();
        differenceInLength = integerDigits.length() - other.getIntegerDigits().length();
    }
    else
    {
        totalLength = other.getIntegerDigits().length();
        differenceInLength = other.getIntegerDigits().length() - integerDigits.length();
    }
    while (--differenceInLength + 1)
        if (integerDigits.length() > other.getIntegerDigits().length())
            comparativeB << "0";
        else
            comparativeA << "0";
    comparativeA << integerDigits;
    comparativeB << other.getIntegerDigits();
    unsigned comparisonIndex = 0;
    while (totalLength - comparisonIndex)
    {
        if (comparativeA.str().at(comparisonIndex) > comparativeB.str().at(comparisonIndex))
            return false;
        else if (comparativeA.str().at(comparisonIndex) < comparativeB.str().at(comparisonIndex))
            return true;
        comparisonIndex++;
    }
    if (other.getDecimalDigits().length() + decimalDigits.length())
    {
        comparativeA.str("");
        comparativeB.str("");
        differenceInLength = 1 + std::abs(integerDigits.length() - other.getIntegerDigits().length());
        comparativeA << decimalDigits;
        comparativeB << other.getDecimalDigits();
        while (--differenceInLength + 1)
            if (decimalDigits.length() > other.getDecimalDigits().length())
                comparativeB << "0";
            else if (decimalDigits.length() < other.getDecimalDigits().length())
                comparativeA << "0";
        AccurateNumber newComparativeA(comparativeA.str(), ""), newComparativeB(comparativeB.str(), "");
        return newComparativeA.hasLowerAbsoluteValueThan(newComparativeB);
    }
    return false;
}

bool AccurateNumber::hasEqualAbsoluteValueTo(AccurateNumber other)
{
    stringstream comparativeA, comparativeB;
    unsigned differenceInLength, totalLength;
    if (integerDigits.length() > other.getIntegerDigits().length())
    {
        totalLength = integerDigits.length();
        differenceInLength = integerDigits.length() - other.getIntegerDigits().length();
    }
    else
    {
        totalLength = other.getIntegerDigits().length();
        differenceInLength = other.getIntegerDigits().length() - integerDigits.length();
    }
    while (--differenceInLength + 1)
        if (integerDigits.length() > other.getIntegerDigits().length())
            comparativeB << "0";
        else
            comparativeA << "0";
    comparativeA << integerDigits;
    comparativeB << other.getIntegerDigits();
    unsigned comparisonIndex = 0;
    while (totalLength - comparisonIndex)
    {
        if (not(comparativeA.str().at(comparisonIndex) == comparativeB.str().at(comparisonIndex)))
            return false;
        /*
         * If any digits of any two numbers at the same digits place are not equal,
         * the numbers must not have equal absolute value.
         */
        comparisonIndex++;
    }
    if (other.getDecimalDigits().length() + decimalDigits.length())
    {
        comparativeA.str("");
        comparativeB.str("");
        differenceInLength = 1 + std::abs(integerDigits.length() - other.getIntegerDigits().length());
        comparativeA << decimalDigits;
        comparativeB << other.getDecimalDigits();
        while (--differenceInLength + 1)
            if (decimalDigits.length() > other.getDecimalDigits().length())
                comparativeB << "0";
            else if (decimalDigits.length() < other.getDecimalDigits().length())
                comparativeA << "0";
        AccurateNumber newComparativeA(comparativeA.str(), ""), newComparativeB(comparativeB.str(), "");
        return newComparativeA.hasEqualAbsoluteValueTo(newComparativeB);
    }
    return true;
}

bool AccurateNumber::isGreaterThan(AccurateNumber other)
{
    if (hasGreaterAbsoluteValueThan(other))
        return nonNegative;
    else
        return nonNegative and (not other.isNonNegative()) and (not hasEqualAbsoluteValueTo(other));
    /*
     * If a positive number has a greater absolute value than another number, it 
     * must be greater than it. On the other hand, if a negative number has a 
     * greater absolute value than another number, is must be less than it.
     */
}

bool AccurateNumber::isLessThan(AccurateNumber other)
{
    if (hasLowerAbsoluteValueThan(other))
        return nonNegative;
    else
        return (not nonNegative) and other.isNonNegative() and (not hasEqualAbsoluteValueTo(other));
    /*
     * If a positive number has a lower absolute value than another number, it 
     * must be less than it. On the other hand, if a negative number has a lower
     * absolute value than another number, is must be greater than it.
     */
}

bool AccurateNumber::isEqualTo(AccurateNumber other)
{
    return not(nonNegative xor other.isNonNegative()) and hasEqualAbsoluteValueTo(other);
    /*
     * If two numbers have the same absolute value, they must be either both 
     * negative or nonnegative to be equal.
     */
}

bool AccurateNumber::isGreaterThanOrEqualTo(AccurateNumber other)
{
    return isEqualTo(other) or isGreaterThan(other);
}

bool AccurateNumber::isLessThanOrEqualTo(AccurateNumber other)
{
    return isEqualTo(other) or isLessThan(other);
}

bool AccurateNumber::isNonNegative(void)
{
    return nonNegative;
}

string AccurateNumber::getIntegerDigits(void)
{
    return integerDigits;
}

string AccurateNumber::getDecimalDigits(void)
{
    return decimalDigits;
}

void AccurateNumber::setNonNegative(bool nonNegative)
{
    AccurateNumber::nonNegative = nonNegative;
}

void AccurateNumber::setIntegerDigits(string integerDigits)
{
    AccurateNumber::integerDigits = integerDigits;
}

void AccurateNumber::setDecimalDigits(string decimalDigits)
{
    AccurateNumber::decimalDigits = decimalDigits;
}
