#ifndef NUMBER_H
#define NUMBER_H

#include <cstdint>
#include <gmp.h>
#include <string>
#include "SHA256.h"

#define INTBASE_ 16

using namespace std;

class Number
{
public:
    mpz_t m_dat;

public:
    static Number Add(const Number &n1, const Number &n2)
    {
        mpz_t res;
        mpz_init(res);
        mpz_add(res, n1.m_dat, n2.m_dat);
        return Number(res);
    }

    static Number Sub(const Number &n1, const Number &n2)
    {
        mpz_t res;
        mpz_init(res);
        mpz_sub(res, n1.m_dat, n2.m_dat);
        return Number(res);
    }

    static Number Neg(const Number &n)
    {
        mpz_t res;
        mpz_init(res);
        mpz_neg(res, n.m_dat);
        return Number(res);
    }

    static Number Mod(const Number &n, const Number &p)
    {
        mpz_t res;
        mpz_init(res);
        mpz_mod(res, n.m_dat, p.m_dat);
        return Number(res);
    }

    static Number Mul(const Number &n1, const Number &n2)
    {
        mpz_t res;
        mpz_init(res);
        mpz_mul(res, n1.m_dat, n2.m_dat);
        return Number(res);
    }

    static Number Pow(const Number &base, const Number &exp, const Number & mod)
    {
        mpz_t res;
        mpz_init(res);
        mpz_powm(res, base.m_dat, exp.m_dat, mod.m_dat);
        return Number(res);
    }

    static Number Inv(const Number &n, const Number & mod)
    {
        mpz_t res;
        mpz_init(res);
        mpz_invert(res, n.m_dat, mod.m_dat);
        return Number(res);
    }

    static Number Rand(const Number &lower, const Number & upper)
    {
        // [lower, upper)
        mpz_t r;
        mpz_init(r);
        mpz_sub(r, upper.m_dat, lower.m_dat);
        mpz_urandomm(r, Number::gmp_rs, r);
        mpz_add(r, r, lower.m_dat);
        return Number(r);
    }

    static int NSign(const Number& n)
    {
        return mpz_sgn(n.m_dat);
    }

    static Number Hash(const string& s);
    static Number Hash(const Number& n);

    static void InitRandom();

    Number(const Number &n);
    Number(const string &num, int base=INTBASE_);
    Number(const int &num);
    Number(mpz_t& dat);
    ~Number();

    static const string p_str, q_str, g_str;
    static const Number *P;
    static const Number *Q;
    static const Number *G;

    static void Delete();

    static const int L, N;
    
    static gmp_randstate_t gmp_rs;

    string ToString() const;
    void Print() const;
};



#endif