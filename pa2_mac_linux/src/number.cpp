#include "number.h"
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

const string Number::p_str = "669320e7";
const string Number::q_str = "48b9";
const string Number::g_str = "414245a8";

const Number *Number::P = new Number(Number::p_str, 16);
const Number *Number::Q = new Number(Number::q_str, 16);
const Number *Number::G = new Number(Number::g_str, 16);

const int Number::HashHexLen = 4;

int64_t Number::rand_v = 2022;

Number::Number(const string &num, int base)
{
    stringstream ss;
    ss << setbase(base) << num;
    ss >> m_dat;
}

Number::Number(const Number &n)
{
    m_dat = n.m_dat;
}

Number::Number(const int64_t &num)
{
    m_dat = num;
}

Number::~Number()
{
}

string Number::ToString(int base) const
{
    stringstream ss;
    ss << setbase(base) << m_dat;
    string s;
    ss >> s;
    return s;
}

void Number::Print(int base) const
{
    cout << setbase(base) << m_dat;
}

Number Number::Hash(const string &s)
{
    SHA256 sha;
    sha.update(s);
    uint8_t *digest = sha.digest();
    string s_digest = SHA256::toString(digest).substr(0, Number::HashHexLen);
    delete[] digest;
    return Number(s_digest, 16);
}

Number Number::Hash(const Number &n)
{
    SHA256 sha;
    int64_t dt = n.m_dat;
    uint8_t *n_byte = new uint8_t[32];
    uint64_t mask = 255;
    for (int i = 31; i >= 0; i--)
    {
        n_byte[i] = (uint8_t)dt & mask;
        dt = dt >> 8;
    }
    sha.update(n_byte, 32);

    uint8_t *digest = sha.digest();
    string s_digest = SHA256::toString(digest).substr(0, Number::HashHexLen);
    delete[] digest;
    delete[] n_byte;
    return Number(s_digest, 16);
}

Number Number::Hash(const Number &n, const string &s)
{
    SHA256 sha;
    int sl = s.length();
    int64_t dt = n.m_dat;
    uint8_t *n_byte = new uint8_t[32 + sl + 1];
    uint64_t mask = 255;
    for (int i = 31; i >= 0; i--)
    {
        n_byte[i] = (uint8_t)dt & mask;
        dt = dt >> 8;
    }
    sha.update(n_byte, 32);
    for (int i = 0; i < sl; i++)
        n_byte[32 + i] = s[i];
    n_byte[32 + sl] = '\0';

    sha.update(n_byte, 32 + sl);

    uint8_t *digest = sha.digest();
    string s_digest = SHA256::toString(digest).substr(0, Number::HashHexLen);
    delete[] digest;
    delete[] n_byte;
    return Number(s_digest, 16);
}

void Number::InitRandom()
{
    Number::rand_v = 2022;
}

void Number::Delete()
{
    delete Number::P;
    delete Number::Q;
    delete Number::G;
}