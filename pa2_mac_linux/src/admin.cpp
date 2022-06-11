#include "admin.h"
#include "user.h"

Admin::Admin()
{
    cout << "P=";
    Number::P->Print();
    cout << "\nQ=";
    Number::Q->Print();
    cout << "\nG=";
    Number::G->Print();
    cout << endl;

}

Admin::~Admin()
{
    cout<<"Destruct Admin..."<<endl;
}

bool Admin::RegisterUser(const User *user)
{
    const string &username = user->m_username;
    if (UserExist(username))
        return false;

    user_name2address[username] = user;
    user_name2publickey[username] = user->publicKeys;

    return true;
}

void Admin::PrintAllUsers()const
{
    cout<<"\nUser information:\n";
    for (const auto& kv: user_name2publickey)
    {
        cout<<"Username: "<<kv.first<<endl;
        for(const auto&kv2: kv.second)
        {
            kv2.second->Print();
        } 
    }
    cout << endl;
}

bool Admin::UserExist(const string &username) const
{
    return user_name2address.find(username) != user_name2address.end();
}

bool Admin::Send(const string &srcUsername, const string &dstUsername,
                 const string &message, const Signature &signature)
{
    if (!(UserExist(srcUsername) && UserExist(dstUsername)))
        return false;
    const User *dstUser = user_name2address[dstUsername];
    dstUser->ReceiveMessage(message, srcUsername, signature);
    return true;
}

const PublicKey *Admin::GetPublicKey(const string &username, const Signature &signature)
{

    if (!(UserExist(username)))
    {
        cout << "In Admin::GetPublicKey(), " << username << " does not exist!";
        return nullptr;
    }

    SigType sigType = signature.GetType();

    const PublicKey *pk = user_name2publickey[username][sigType];

    return pk;
}