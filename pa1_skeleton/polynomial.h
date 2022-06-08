#ifndef __POLYNOMIAL_H__
#define __POLYNOMIAL_H__

class Polynomial
{
    private:
        struct Term
        {
            int coefficient;
            int exponent;
            Term* next;
        } * head;

    public:
        Polynomial(); 
        Polynomial(const Polynomial& another); 
        Polynomial(int array[], int arraySize);
        ~Polynomial();
        void print() const;
        Polynomial add(const Polynomial& another) const;
        Polynomial subtract(const Polynomial& another) const;
        Polynomial multiply(const Polynomial& another) const;
        int evaluate(int valueOfX) const;
        int compare(const Polynomial& another) const; 
 
        explicit Polynomial(int n)
        {
            switch(n)
            {
                case 1:
                {
                    Term* term1 = new Term;
                    term1->coefficient = 4;
                    term1->exponent = 3;
                    Term* term2 = new Term;
                    term2->coefficient = 1;
                    term2->exponent = 2;
                    Term* term3 = new Term;
                    term3->coefficient = 5;
                    term3->exponent = 0;
                    head = term1;
                    term1->next = term2;
                    term2->next = term3;
                    term3->next = nullptr;
                    break;
                }
                case 2:
                {
                    Term* term1 = new Term;
                    term1->coefficient = 4;
                    term1->exponent = 3;
                    Term* term2 = new Term;
                    term2->coefficient = 2;
                    term2->exponent = 2;
                    Term* term3 = new Term;
                    term3->coefficient = 5;
                    term3->exponent = 0;
                    head = term1;
                    term1->next = term2;
                    term2->next = term3;
                    term3->next = nullptr;
                    break;
                }
                case 3:
                {
                    Term* term1 = new Term;
                    term1->coefficient = -7;
                    term1->exponent = 3;
                    Term* term2 = new Term;
                    term2->coefficient = 2;
                    term2->exponent = 2;
                    Term* term3 = new Term;
                    term3->coefficient = 5;
                    term3->exponent = 0;
                    head = term1;
                    term1->next = term2;
                    term2->next = term3;
                    term3->next = nullptr;
                    break;
                }
                case 4:
                {
                    Term* term1 = new Term;
                    term1->coefficient = 5;
                    term1->exponent = 3;
                    Term* term2 = new Term;
                    term2->coefficient = -2;
                    term2->exponent = 2;
                    Term* term3 = new Term;
                    term3->coefficient = -5;
                    term3->exponent = 0;
                    head = term1;
                    term1->next = term2;
                    term2->next = term3;
                    term3->next = nullptr;
                    break;
                }
                case 5:
                {
                    Term* term1 = new Term;
                    term1->coefficient = 5;
                    term1->exponent = 6;
                    Term* term2 = new Term;
                    term2->coefficient = -2;
                    term2->exponent = 1;
                    head = term1;
                    term1->next = term2;
                    term2->next = nullptr;
                    break;
                }
                case 6:
                {
                    Term* term1 = new Term;
                    term1->coefficient = 5;
                    term1->exponent = 6;
                    Term* term2 = new Term;
                    term2->coefficient = 1;
                    term2->exponent = 1;
                    head = term1;
                    term1->next = term2;
                    term2->next = nullptr;
                    break;
                }
                case 7:
                {
                    Term* term1 = new Term;
                    term1->coefficient = 5678;
                    term1->exponent = 999;
                    Term* term2 = new Term;
                    term2->coefficient = -1;
                    term2->exponent = 1;
                    head = term1;
                    term1->next = term2;
                    term2->next = nullptr;
                    break;
                }
                case 8:
                {
                    Term* term1 = new Term;
                    term1->coefficient = -45;
                    term1->exponent = 0;
                    head = term1;
                    term1->next = nullptr;
                    break;
                }
                case 9:
                {
                    Term* term1 = new Term;
                    term1->coefficient = 90;
                    term1->exponent = 0;
                    head = term1;
                    term1->next = nullptr;
                    break;
                }
                case 10:
                {
                    Term* term1 = new Term;
                    term1->coefficient = 45;
                    term1->exponent = 1;
                    head = term1;
                    term1->next = nullptr;
                    break;
                }
                case 11:
                {
                    Term* term1 = new Term;
                    term1->coefficient = -90;
                    term1->exponent = 1;
                    head = term1;
                    term1->next = nullptr;
                    break;
                }
                case 12:
                {
                    Term* term1 = new Term;
                    term1->coefficient = 45;
                    term1->exponent = 2;
                    head = term1;
                    term1->next = nullptr;
                    break;
                }
                case 13:
                {
                    Term* term1 = new Term;
                    term1->coefficient = -90;
                    term1->exponent = 2;
                    head = term1;
                    term1->next = nullptr;
                    break;
                }
                case 14:
                {
                    Term* term1 = new Term;
                    term1->coefficient = -1;
                    term1->exponent = 1;
                    head = term1;
                    term1->next = nullptr;
                    break;
                }
                case 15:
                {
                    Term* term1 = new Term;
                    term1->coefficient = 1;
                    term1->exponent = 1;
                    head = term1;
                    term1->next = nullptr;
                    break;
                }
                default: //won't happen in any test case
                    break;
            }
        };
};

#endif // __POLYNOMIAL_H__