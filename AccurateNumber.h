/*
 * The AccurateNumber class was designed to create instances of numbers with large 
 * amounts of digits, hence greater accuracy. Its functions include addition, 
 * subtraction, multiplication division, powers, and roots. It also includes the 
 * ability to round to a desired digit place and get rid of unnecessary zeros at 
 * the beginning and end of each number. It primarily serves for solving for variables
 * in equations with decimal digit precision exceeding 100 places.
 */

#ifndef ACCURATENUMBER_H
#define ACCURATENUMBER_H
#include <iostream>

using namespace std;

class AccurateNumber {
    private:
        bool nonNegative; // Whether an AccurateNumber is nonnegative or negative
        string integerDigits;
        string decimalDigits;
    public:
        AccurateNumber(void);
        AccurateNumber(string);
        AccurateNumber(string, string);
        AccurateNumber(bool, string, string);
        string userVisibleRepresentation(void);
        AccurateNumber sum(AccurateNumber); // Adding another AccurateNumber
        AccurateNumber difference(AccurateNumber); // Subtracting another AccurateNumber
        AccurateNumber product(AccurateNumber); // Multiplying by another AccurateNumber
        AccurateNumber quotient(AccurateNumber); // Dividing by another AccurateNumber
        AccurateNumber modulus(AccurateNumber); /*
                                      * This finds the remainder of the object
                                      * divided by another AccurateNumber.
                                      */
        AccurateNumber power(int); // Raising the AccurateNumber to an integer power
        AccurateNumber root(int); // Computing the integer square root of a AccurateNumber 
        /*
         * Defining an operator for addition
         */
        AccurateNumber operator+(AccurateNumber) throw(std::exception);
        AccurateNumber operator-(AccurateNumber) throw(std::exception);
        AccurateNumber operator*(AccurateNumber) throw(std::exception);
        AccurateNumber operator/(AccurateNumber) throw(std::exception);
        AccurateNumber operator%(AccurateNumber) throw(std::exception);
        void operator+=(AccurateNumber) throw(std::exception);
        void operator-=(AccurateNumber) throw(std::exception);
        void operator*=(AccurateNumber) throw(std::exception);
        void operator/=(AccurateNumber) throw(std::exception);
        void operator%=(AccurateNumber) throw(std::exception);
        void trimZeros(void); /*
                           * This function deletes all unnecessary zeros at the
                           * beginning and end of a number. For example, 7.1300 
                           * becomes 7.13, 05.19 becomes 5.19, 08.34000 becomes 
                           * 8.34.
                           */
        void round(int); // Rounds the AccurateNumber to a desired digit place
        bool hasGreaterAbsoluteValueThan(AccurateNumber);
        bool hasLowerAbsoluteValueThan(AccurateNumber);
        bool hasEqualAbsoluteValueTo(AccurateNumber);
        bool isGreaterThan(AccurateNumber);
        bool isLessThan(AccurateNumber);
        bool isEqualTo(AccurateNumber);
        bool isGreaterThanOrEqualTo(AccurateNumber);
        bool isLessThanOrEqualTo(AccurateNumber);
        
        // Accessors
        bool isNonNegative(void);
        string getIntegerDigits(void);
        string getDecimalDigits(void);
        
        // Mutators
        void setNonNegative(bool);
        void setIntegerDigits(string);
        void setDecimalDigits(string);
};

#endif
