#ifndef NUMBER_H
#define NUMBER_H

#include <cstdint>
#include <cstdlib>
#include <string>
#include <iostream>
#include <iomanip>
#include "SHA256.h"

#define INTBASE_ 16

using namespace std;

class Number
{
private:
    int64_t m_dat;

public:
    static Number Add(const Number &n1, const Number &n2)
    {
        return Number(n1.m_dat + n2.m_dat);
    }

    static Number Sub(const Number &n1, const Number &n2)
    {

        return Number(n1.m_dat - n2.m_dat);
    }

    static Number Neg(const Number &n)
    {
        return Number(-n.m_dat);
    }

    static Number Mod(const Number &n, const Number &p)
    {
        if (Number::NSign(p) <= 0)
        {
            throw invalid_argument("Mod P should be > 0 :" + p.ToString(INTBASE_));
        }
        int64_t res = n.m_dat % p.m_dat;
    
        if (res<0) 
        {
            res += p.m_dat;
        }
        return Number(res);
    }

    static Number Mul(const Number &n1, const Number &n2)
    {
        // take care of overflow, use Mul_Mod to be safe
        return Number(n1.m_dat * n2.m_dat);
    }

    static Number Mul_Mod(const Number &n1, const Number &n2, const Number &p)
    {
        return Number::Mod(Number::Mul(n1, n2), p);
    }

    static Number Pow(const Number &base, const Number &exp, const Number &mod)
    {
        if (Number::NSign(exp) < 0)
        {
            throw invalid_argument("Exp should be > 0 : " + exp.ToString(INTBASE_));
        }
        int64_t res = 1;
        int64_t a = base.m_dat;
        int64_t e = exp.m_dat % (mod.m_dat - 1);
        int64_t e_m = 1;

        for (int i = 0; i < 63; i++)
        {
            if (e_m & e)
            {
                res = (res * a) % mod.m_dat;
            }
            e_m = e_m << 1;
            a = (a * a) % mod.m_dat;
        }
        return Number(res);
    }

    static Number Inv(const Number &n, const Number &mod)
    {
        // mod should be a prime number
        return Number::Pow(n, Number::Sub(mod, Number(2)), mod);
    }

    static Number Rand(const Number &lower, const Number &upper)
    {
        // [lower, upper)

        int64_t res = Number::rand_v % (upper.m_dat - lower.m_dat) + lower.m_dat;
        Number::rand_v = (Number::rand_v * Number::rand_v) % (Number::P->m_dat) + 1;
        return Number(res);
    }

    static int NSign(const Number &n)
    {
        if (n.m_dat > 0)
            return 1;
        else if (n.m_dat < 0)
            return -1;
        else
            return 0;
    }

    // hash function: returns a Number of 16 bits
    static Number Hash(const string &s);
    static Number Hash(const Number &n);
    static Number Hash(const Number &n, const string &s);

    static int64_t rand_v; 
    static void InitRandom();

    static void Delete();

    Number(const Number &n);
    Number(const string &num, int base = INTBASE_);
    Number(const int64_t &num);
    ~Number();

    static const string p_str, q_str, g_str;
    static const Number *P;
    static const Number *Q;
    static const Number *G;

    static const int HashHexLen;

    string ToString(int base = INTBASE_) const;
    void Print(int base = INTBASE_) const;
};

#endif