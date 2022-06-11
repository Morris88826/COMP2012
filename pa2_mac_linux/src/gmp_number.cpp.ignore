#include "gmp_number.h"
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

const string Number::p_str = "13232376895198612407547930718267435757728527029623408872245156039757713029036368719146452186041204237350521785240337048752071462798273003935646236777459223";
const string Number::q_str = "857393771208094202104259627990318636601332086981";
const string Number::g_str = "5421644057436475141609648488325705128047428394380474376834667300766108262613900542681289080713724597310673074119355136085795982097390670890367185141189796";

const Number *Number::P = new Number(Number::p_str, 10);
const Number *Number::Q = new Number(Number::q_str, 10);
const Number *Number::G = new Number(Number::g_str, 10);

const int Number::L = 1024;
const int Number::N = 256;

gmp_randstate_t Number::gmp_rs;

Number::Number(const string &num, int base)
{
    mpz_init_set_str(m_dat, num.c_str(), base);
}

Number::Number(const Number &n)
{
    mpz_init_set_str(m_dat, n.ToString().c_str(), INTBASE_);
}

Number::Number(mpz_t &dat)
{
    mpz_init_set(m_dat, dat);
    mpz_clear(dat);
}

Number::Number(const int &num)
{
    mpz_init_set_si(m_dat, num);
}

Number::~Number()
{
    mpz_clear(m_dat);
}

string Number::ToString() const
{
    stringstream ss;
    ss << setbase(INTBASE_) << m_dat;
    string s;
    ss >> s;
    return s;
}

void Number::Print() const
{
    cout << setbase(INTBASE_) << m_dat;
}

Number Number::Hash(const string &s)
{
    SHA256 sha;
    sha.update(s);
    uint8_t *digest = sha.digest();
    string s_digest = SHA256::toString(digest);
    delete[] digest;
    return Number(s_digest);
}

Number Number::Hash(const Number &n)
{
    SHA256 sha;
    string s = n.ToString();
    stringstream ss;
    ss << setw(64) << setfill('0') << s;
    ss >> s;
    ss.clear();
    uint8_t *n_byte = new uint8_t[32];
    unsigned int temp;
    for (int i = 0; i < 32; i++)
    {
        ss << s.substr(2 * i, 2*i + 2);
        ss >> setbase(INTBASE_) >> temp;
        n_byte[i] = (uint8_t)(temp);
    }
    sha.update(n_byte, 32);

    uint8_t *digest = sha.digest();
    string s_digest = SHA256::toString(digest);
    delete[] digest;
    delete[] n_byte;
    return Number(s_digest);
}

void Number::InitRandom()
{
    gmp_randinit_default(Number::gmp_rs);
    gmp_randseed_ui(Number::gmp_rs, 0);
}

void Number::Delete()
{
    delete Number::P;
    delete Number::Q;
    delete Number::G;
}