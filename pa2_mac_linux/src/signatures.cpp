#include "signatures.h"
#include "number.h"

SigType Signature::GetType() const
{
    string name = typeid(*this).name();

    if (name == "12DSASignature")
        return DSA;
    else if (name == "16SchnorrSignature")
        return Schnorr;
    else
        throw invalid_argument("Signature Type does not exist!");
}

//Todo: Constructors/Destructors
SchnorrSignature::~SchnorrSignature(){
    delete s;
    delete e;
}

DSASignature::~DSASignature(){
    delete r;
    delete s;
}

SchnorrPublicKey::~SchnorrPublicKey(){
    delete y;
}

DSAPublicKey::~DSAPublicKey(){
    delete y;
}

SchnorrSecretKey::~SchnorrSecretKey(){
    delete x;
}

DSASecretKey::~DSASecretKey(){
    delete x;
}


bool SchnorrPublicKey::Verify(const string &message, const Signature &signature) const
{
    //Todo
    const SchnorrSignature& schnorr = static_cast<const SchnorrSignature&>(signature);

    if(Number::NSign(*schnorr.e) <=0 || Number::NSign(*schnorr.s) <=0 || 
        Number::NSign(Number::Sub(*schnorr.e, *Number::Q))>0 || Number::NSign(Number::Sub(*schnorr.s, *Number::Q))>0){
        return false;
    }

    Number r_v = Number::Mul_Mod(Number::Pow(*Number::G, *schnorr.s, *Number::P), Number::Pow(*y, *schnorr.e, *Number::P), *Number::P);
    Number e_v = Number::Mod(Number::Hash(r_v, message), *Number::Q);

    if(Number::NSign(Number::Sub(e_v, *schnorr.e)) == 0){
        return true;
    }else{
        return false;
    }
}


bool DSAPublicKey::Verify(const string &message, const Signature &signature) const
{
    //Todo
    const DSASignature& dsa = static_cast<const DSASignature&>(signature);

    if(Number::NSign(*dsa.r) <=0 || Number::NSign(*dsa.s) <=0 || 
        Number::NSign(Number::Sub(*dsa.r, *Number::Q))>0 || Number::NSign(Number::Sub(*dsa.s, *Number::Q))>0){
        return false;
    }

    Number w = Number::Inv(*dsa.s, *Number::Q);
    Number z = Number::Hash(message);
    Number u1 = Number::Mul_Mod(z, w, *Number::Q);
    Number u2 = Number::Mul_Mod(*dsa.r, w, *Number::Q);
    
    Number result = Number::Mod(Number::Mul_Mod(Number::Pow(*Number::G, u1, *Number::P), Number::Pow(*y, u2, *Number::P), *Number::P), *Number::Q);

    if(Number::NSign(Number::Sub(result, *dsa.r)) == 0){
        return true;
    }else{
        return false;
    }
}



const Signature *SchnorrSecretKey::Sign(const string &message) const
{
    //Todo
    while(true){
        Number k = Number::Rand(1, *Number::Q);
        Number r = Number::Pow(*Number::G, k, *Number::P);
        Number e = Number::Mod(Number::Hash(r, message), *Number::Q);
        Number s = Number::Mod(Number::Sub(k, Number::Mul_Mod(*this->x, e, *Number::Q)), *Number::Q);
        if(Number::NSign(e)!=0 && Number::NSign(s)!=0){
            const Signature * signature = new SchnorrSignature(new Number(s), new Number(e));
            return signature;
        }
    }
}



const Signature *DSASecretKey::Sign(const string &message) const
{
    while (true)
    {
        Number k = Number::Rand(1, *Number::Q);
        Number r = Number::Mod(Number::Pow(*Number::G, k, *Number::P), *Number::Q);
        Number z = Number::Hash(message);
        Number zxr = Number::Mod(Number::Add(z, Number::Mul_Mod(*(this->x), r, *Number::Q)), *Number::Q);
        Number ki = Number::Inv(k, *Number::Q);
        Number s = Number::Mul_Mod(ki, zxr, *Number::Q);

        if (Number::NSign(r) > 0 && Number::NSign(s) > 0)
            return new DSASignature(new Number(r), new Number(s));
    }
}

SigPair::SigPair(const PublicKey *publicKey, const SecretKey *secretKey)
    : publicKey(publicKey), secretKey(secretKey)
{
}

SigPair::~SigPair()
{
    cout << "Destruct SigPair..."<<endl;
    delete publicKey;
    delete secretKey;
}

const SigPair *GenerateKey(SigType sigType, const string &info)
{
    if (sigType == DSA )
    {
        Number x = Number::Rand(Number(1), *Number::Q);
        Number y = Number::Pow(*Number::G, x, *Number::P);
        const Number *newX = new Number(x);
        const Number *newY = new Number(y);

        DSASecretKey *sk = new DSASecretKey(newX);
        DSAPublicKey *pk = new DSAPublicKey(newY);

        SigPair *sigPair = new SigPair(pk, sk);

        return sigPair;
    }
    else if (sigType == Schnorr )
    {
        //Todo
        Number x = Number::Rand(Number(1), *Number::Q);
        Number y = Number::Pow(*Number::G, x, *Number::P);

        SchnorrSecretKey *sk = new SchnorrSecretKey(new Number(x));
        SchnorrPublicKey *pk = new SchnorrPublicKey(new Number(y));

        SigPair* sigPair = new SigPair(pk, sk);
        return sigPair;
    }
        return nullptr;
}

vector<SigType> SigTypes()
{
    vector<SigType> s;
    s.push_back(DSA);
    s.push_back(Schnorr);
    return s;
}
