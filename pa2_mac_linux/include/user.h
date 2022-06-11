#ifndef USER_H
#define USER_H

#include <map>

#include "signatures.h"
#include "admin.h"

using namespace std;

class User
{
public:
    User(const string &username, Admin *admin);
    ~User();

    void SendMessage(const string &message,
                     const string &dstUsername, SigType sigType = DSA);
    void ReceiveMessage(const string &message,
                        const string &srcUsername, const Signature &sig) const;
    
    void MaliciousSendMessage(const string&message, 
                    const string & dstUsername, SigType sigType = DSA);
    

    string m_username;
    Admin *admin;

    map<SigType, const PublicKey *> publicKeys;

private:
    map<SigType, const SigPair *> m_sigPairs;
    vector<const Signature *> m_signatures;
};

#endif