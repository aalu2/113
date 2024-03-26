#include <iostream>
#include <vector>
#include <cmath> // Include cmath header for std::abs function

class Term {
public:
    int coefficient;
    int exponent;

    Term(int coef, int exp) : coefficient(coef), exponent(exp) {}
};

class Polynomial {
private:
    std::vector<Term> terms;

public:
    Polynomial() {}

    void addTerm(int coef, int exp) {
        Term term(coef, exp);
        terms.push_back(term);
    }

    void display() {
        for (size_t i = 0; i < terms.size(); ++i) {
            if (terms[i].coefficient > 0 && i != 0) {
                std::cout << " + ";
            }
            if (terms[i].coefficient < 0) {
                std::cout << " - ";
            }
            std::cout << std::abs(terms[i].coefficient) << "x^" << terms[i].exponent;
        }
        std::cout << "\n";
    }

    Polynomial operator+(const Polynomial &other) const {
        Polynomial result;
        for (const auto &term : terms) {
            result.terms.push_back(term);
        }
        for (const auto &term : other.terms) {
            result.terms.push_back(term);
        }
        // Combine like terms in the result
        Polynomial finalResult;
        for (const auto &term : result.terms) {
            bool found = false;
            for (auto &finalTerm : finalResult.terms) {
                if (term.exponent == finalTerm.exponent) {
                    finalTerm.coefficient += term.coefficient;
                    found = true;
                    break;
                }
            }
            if (!found) {
                finalResult.terms.push_back(term);
            }
        }
        return finalResult;
    }

    Polynomial operator-(const Polynomial &other) const {
        Polynomial result;
        for (const auto &term : terms) {
            result.terms.push_back(term);
        }
        for (const auto &term : other.terms) {
            result.terms.push_back(Term(-term.coefficient, term.exponent));
        }
        // Combine like terms in the result
        Polynomial finalResult;
        for (const auto &term : result.terms) {
            bool found = false;
            for (auto &finalTerm : finalResult.terms) {
                if (term.exponent == finalTerm.exponent) {
                    finalTerm.coefficient += term.coefficient;
                    found = true;
                    break;
                }
            }
            if (!found) {
                finalResult.terms.push_back(term);
            }
        }
        return finalResult;
    }

    Polynomial operator*(const Polynomial &other) const {
        Polynomial result;
        for (const auto &term1 : terms) {
            for (const auto &term2 : other.terms) {
                result.terms.push_back(Term(term1.coefficient * term2.coefficient, term1.exponent + term2.exponent));
            }
        }
        // Combine like terms in the result
        Polynomial finalResult;
        for (const auto &term : result.terms) {
            bool found = false;
            for (auto &finalTerm : finalResult.terms) {
                if (term.exponent == finalTerm.exponent) {
                    finalTerm.coefficient += term.coefficient;
                    found = true;
                    break;
                }
            }
            if (!found) {
                finalResult.terms.push_back(term);
            }
        }
        return finalResult;
    }

    // Destructor
    ~Polynomial() {}
};

int main() {
    Polynomial poly1, poly2;

    poly1.addTerm(3, 2);
    poly1.addTerm(2, 1);

    poly2.addTerm(4, 3);
    poly2.addTerm(1, 1);

    std::cout << "Polynomial 1: ";
    poly1.display();  // Output: 3x^2 + 2x^1
    std::cout << "Polynomial 2: ";
    poly2.display();  // Output: 4x^3 + 1x^1

    Polynomial sum = poly1 + poly2;
    Polynomial difference = poly1 - poly2;
    Polynomial product = poly1 * poly2;

    std::cout << "Sum: ";
    sum.display();  // Output: 4x^3 + 3x^2 + 2x^1
    std::cout << "Difference: ";
    difference.display();  // Output: 3x^2 + 2x^1 - 4x^3
    std::cout << "Product: ";
    product.display();  // Output: 12x^5 + 3x^3 + 8x^4 + 2x^2

    return 0;
}
