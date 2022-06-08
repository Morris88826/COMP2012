#include "user.h"
#include "admin.h"

#include <stdexcept>
using namespace std;

User::User(const string &username, Admin *admin) : m_username(username), admin(admin)
{
    string info = m_username;
    for (auto sigType : SigTypes())
        m_sigPairs[sigType] = GenerateKey(sigType, info);
    for (const auto &kv : m_sigPairs)
    {
        publicKeys[kv.first] = kv.second->publicKey;
    }
    bool res = admin->RegisterUser(this);

    if (!res)
        throw invalid_argument("Username " + m_username + " already exists. ");
}

User::~User()
{
    cout << "Destruct User " << m_username << "..." << endl;
    for (auto &kv : m_sigPairs)
    {
        delete kv.second;
    }
    for (auto sig : m_signatures)
    {
        delete sig;
    }
}

void User::SendMessage(const string &message, const string &dstUsername, SigType sigType)
{
    const Signature *sig = m_sigPairs[sigType]->secretKey->Sign(message);
    m_signatures.push_back(sig);

    admin->Send(m_username, dstUsername, message, *sig);
}

void User::ReceiveMessage(const string &message, const string &srcUsername,
                          const Signature &sig) const
{
    const PublicKey *srcPublicKey = admin->GetPublicKey(srcUsername, sig);
    cout << this->m_username << ": Receive Message from " << srcUsername << endl;
    cout << "message=" << message << endl;
    cout << "signature: ";
    sig.Print();
    if (srcPublicKey != nullptr)
    {
        bool verifyResult = srcPublicKey->Verify(message, sig);
        string res = verifyResult ? "passed" : "failed";
        cout << "Verification " << res << endl;
    }
    else
    {
        cout << "Error: public key is invalid!";
    }
}

void User::MaliciousSendMessage(const string &message, const string &dstUsername, SigType sigType)
{
    const Signature *sig = m_sigPairs[sigType]->secretKey->Sign(message);
    Signature *new_sig;
    if (sigType == DSA)
    {
        const DSASignature *dsa_sig = reinterpret_cast<const DSASignature *>(sig);
        new_sig = new DSASignature(new Number(Number::Add(*dsa_sig->r, 1)),
                                   new Number(*dsa_sig->s));
        delete sig;
    }
    else if (sigType == Schnorr)
    {
        const SchnorrSignature *schnorr_sig = reinterpret_cast<const SchnorrSignature *>(sig);
        new_sig = new SchnorrSignature(new Number(Number::Add(*schnorr_sig->s, 1)),
                                   new Number(*schnorr_sig->e));
        delete sig;
    }
    m_signatures.push_back(new_sig);

    admin->Send(m_username, dstUsername, message, *new_sig);
}