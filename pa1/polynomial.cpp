#include "polynomial.h"
#include <iostream>
using namespace std;
//note: you are not allowed to include any additional library, see also FAQ for what you can/cannot do
//write your code below and submit this file only

Polynomial::Polynomial(){
    head = nullptr;
}

Polynomial::Polynomial(const Polynomial& another){

    if(another.head == nullptr){
        head = nullptr;
        return;
    }

    Term* tmp = another.head;
    head = new Term;
    head->coefficient = tmp->coefficient;
    head->exponent = tmp->exponent;
    head->next = nullptr;
    tmp = tmp->next;

    Term* current = head;
    while(tmp != nullptr){
        current->next = new Term; //Allocate new memory for Term node

        current = current->next; //Point to the new node
        current->coefficient = tmp->coefficient; 
        current->exponent = tmp->exponent;
        current->next = nullptr; //By default set the 'next' to null.

        tmp = tmp->next;
    }

}

Polynomial::Polynomial(int array[], int arraySize){
    if(arraySize==0){
        head = nullptr;
        return;
    }

    bool first = true;
    Term* current;
    for(int i=0; i<arraySize; i++){

        if(array[i] !=0 && first){
            first = false;
            head = new Term;
            head->coefficient = array[i];
            head->exponent = (arraySize-i-1);
            head->next = nullptr;
            current = head;
        }else if(array[i]!=0){
            current->next = new Term;
            current = current->next;
            current->coefficient = array[i];
            current->exponent = (arraySize-i-1);
            current->next = nullptr;
        }
    }
}

Polynomial::~Polynomial(){
    if(head==nullptr){
        return;
    }

    Term* current = head;

    while(current != nullptr){
        current = current->next;
        delete head;
        head = current;
    }
    
}

void Polynomial::print() const{

    Term* current = head;
    int i = 0;
    while(current!=nullptr){
        int coeff = current->coefficient;
        int expo = current->exponent;
        if(current==head){
            if(expo==0){
                std::cout << coeff;
            }else if(expo==1){
                if(coeff==1){
                    std::cout << "x";
                }else if(coeff==-1){
                    std::cout << "-x";
                }else if(coeff>0){
                    std::cout << coeff << "*x";
                }else if(coeff<0){
                    std::cout << coeff << "*x";
                }                   
            }
            else{
                if(coeff==1){
                    std::cout << "x^" << expo;
                }else if(coeff==-1){
                    std::cout << "-x^" << expo;
                }else if(coeff>0){
                    std::cout << coeff << "*x^" << expo;
                }else if(coeff<0){
                    std::cout << coeff << "*x^" << expo;
                }   
            }
        }else{
            if(expo==0){
                if(coeff>0){
                    std::cout << " + ";
                    std::cout << coeff;
                }else if(coeff<0){
                    std::cout << " - ";
                    std::cout << -1*coeff;
                }
            }else if(expo==1){
                if(coeff==1){
                    std::cout << " + ";
                    std::cout << "x";
                }else if(coeff==-1){
                    std::cout << " - ";
                    std::cout << "x";
                }else if(coeff>0){
                    std::cout << " + ";
                    std::cout << coeff << "*x";
                }else if(coeff<0){
                    std::cout << " - ";
                    std::cout << -1*coeff << "*x";
                }   
            }else{
                if(coeff==1){
                    std::cout << " + ";
                    std::cout << "x^" << expo;
                }else if(coeff==-1){
                    std::cout << " - ";
                    std::cout << "x^" << expo;
                }else if(coeff>0){
                    std::cout << " + ";
                    std::cout << coeff << "*x^" << expo;
                }else if(coeff<0){
                    std::cout << " - ";
                    std::cout << -1*coeff << "*x^" << expo;
                }   
            }
        }
        i += 1;
        current = current->next;
    }
}

Polynomial Polynomial::add(const Polynomial& another) const{

    Term* cur1 = head;
    Term* cur2 = another.head;

    Polynomial result;
    result.head = new Term;
    Term* cur = result.head;
    cur->coefficient = 0;
    cur->exponent = 0;
    cur->next = nullptr;

    while(true){
        if(cur1==nullptr && cur2==nullptr){
            cur->next = nullptr;
            break;
        }
        else if(cur1 == nullptr){
            cur->next = new Term;
            cur = cur->next;
            cur->coefficient = cur2->coefficient;
            cur->exponent = cur2->exponent; 
            cur2 = cur2->next;
        }else if (cur2 == nullptr){
            cur->next = new Term;
            cur = cur->next;
            cur->coefficient = cur1->coefficient;
            cur->exponent = cur1->exponent; 
            cur1 = cur1->next;  
        }
        
        else if(cur1->exponent == cur2->exponent){
            if(cur1->coefficient + cur2->coefficient != 0){
                cur->next = new Term;
                cur = cur->next;
                cur->coefficient = cur1->coefficient + cur2->coefficient;
                cur->exponent = cur1->exponent; 
            }
            cur1 = cur1->next;
            cur2 = cur2->next;
        }

        else if(cur1->exponent > cur2->exponent){
            cur->next = new Term;
            cur = cur->next;
            cur->coefficient = cur1->coefficient;
            cur->exponent = cur1->exponent;             
            cur1 = cur1->next;
        }else{
            cur->next = new Term; 
            cur = cur->next;
            cur->coefficient = cur2->coefficient;
            cur->exponent = cur2->exponent;
            cur2 = cur2->next;
        }
    }

    Term* tmp = result.head;
    result.head = result.head->next;
    delete tmp;

    return result;
}
Polynomial Polynomial::subtract(const Polynomial& another) const{
    Term* cur1 = head;
    Term* cur2 = another.head;

    Polynomial result;
    result.head = new Term;
    Term* cur = result.head;
    cur->coefficient = 0;
    cur->exponent = 0;
    cur->next = nullptr;

    while(true){
        if(cur1==nullptr && cur2==nullptr){
            cur->next = nullptr;
            break;
        }
        else if(cur1 == nullptr){
            cur->next = new Term;
            cur = cur->next;
            cur->coefficient = -1*cur2->coefficient;
            cur->exponent = cur2->exponent; 
            cur2 = cur2->next;
        }else if (cur2 == nullptr){
            cur->next = new Term;
            cur = cur->next;
            cur->coefficient = cur1->coefficient;
            cur->exponent = cur1->exponent; 
            cur1 = cur1->next;  
        }
        
        else if(cur1->exponent == cur2->exponent){
            if(cur1->coefficient - cur2->coefficient != 0){
                cur->next = new Term;
                cur = cur->next;
                cur->coefficient = cur1->coefficient - cur2->coefficient;
                cur->exponent = cur1->exponent; 
            }
            cur1 = cur1->next;
            cur2 = cur2->next;
        }

        else if(cur1->exponent > cur2->exponent){
            cur->next = new Term;
            cur = cur->next;
            cur->coefficient = cur1->coefficient;
            cur->exponent = cur1->exponent;             
            cur1 = cur1->next;
        }else{
            cur->next = new Term; 
            cur = cur->next;
            cur->coefficient = -1*cur2->coefficient;
            cur->exponent = cur2->exponent;
            cur2 = cur2->next;
        }
    }

    Term* tmp = result.head;
    result.head = result.head->next;
    delete tmp;

    return result;
}
Polynomial Polynomial::multiply(const Polynomial& another) const{
    Polynomial result;
    result.head = new Term;
    result.head->coefficient = -1;
    result.head->exponent = -1;
    result.head->next = nullptr;

    Term* cur = result.head;
    Term* cur2 = another.head;
    while(cur2!=nullptr){
        Term* cur1 = head;

        while(cur1!=nullptr){
            int _coeff = cur1->coefficient*cur2->coefficient;
            int _expo = cur1->exponent + cur2->exponent;
            if(_coeff!=0){
                cur = result.head;
                while (cur!=nullptr)
                {
                    if(cur->exponent == _expo){
                        cur->coefficient += _coeff;
                        break;
                    }else if(cur->next!=nullptr && cur->next->exponent<_expo){
                        Term* tmp = cur->next;
                        cur->next = new Term;
                        cur = cur->next;
                        cur->coefficient = _coeff;
                        cur->exponent = _expo;
                        cur->next = tmp;
                        break;
                    }else if(cur->next==nullptr){
                        cur->next = new Term;
                        cur = cur->next;
                        cur->coefficient = _coeff;
                        cur->exponent = _expo;
                        cur->next = nullptr;
                        break;
                    }
                    cur = cur->next;
                }
                
            }
            cur1 = cur1->next;
        }
        cur2 = cur2->next;
    }

    Term* tmp = result.head;
    result.head = result.head->next;
    delete tmp;

    return result;
}
int Polynomial::evaluate(int valueOfX) const{
    Term* current = head;
    int result = 0;
    while(current!=nullptr){

        int tmp = 1;
        for(int i=0; i<current->exponent; i++){
            tmp = tmp * valueOfX;
        }

        result += current->coefficient*tmp;
        current = current->next;
    }
    return result;
}
int Polynomial::compare(const Polynomial& another) const{
    Term* cur1 = head;
    Term* cur2 = another.head;

    while(true){
        if(cur1==nullptr && cur2==nullptr){
            return 0;
        }

        else if(cur1 == nullptr){
            return -1;
        }else if(cur2 == nullptr){
            return 1;
        }else if(cur1->exponent == cur2->exponent){
            if(cur1->coefficient>cur2->coefficient){
                return 1;
            }else if(cur1->coefficient<cur2->coefficient){
                return -1;
            }else{
                cur1 = cur1->next;
                cur2 = cur2->next;
            }
        }else if(cur1->exponent > cur2->exponent){
            return 1;
        }else{
            return -1;
        }
    }
}