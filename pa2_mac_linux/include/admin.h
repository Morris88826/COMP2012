#ifndef ADMIN_H
#define ADMIN_H

#include <map>
#include "signatures.h"


using namespace std;

class User;

class Admin
{
public:
    map<const string, const User *> user_name2address;
    map<const string, map<SigType, const PublicKey *> > user_name2publickey;
    
    Admin();
    ~Admin();

    bool RegisterUser(const User *user);

    bool UserExist(const string &username) const;

    bool Send(const string &srcUsername, const string &dstUsername,
              const string &message, const Signature &signature);

    const PublicKey *GetPublicKey(const string &username, const Signature&signature);

    void PrintAllUsers()const;
};

#endif