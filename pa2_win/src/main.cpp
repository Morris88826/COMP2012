#include "admin.h"
#include "user.h"
#include "number.h"
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    Number::InitRandom();
    Admin * admin = new Admin();
    vector<string> names;
    names.push_back("Alice");
    names.push_back("Bob");

    map<const string, User *> users; 
    for(auto name: names)
    {
        User * user = new User(name, admin);
        users[name] = user;
    }

    admin->PrintAllUsers();

    cout << "===> Alice send message to Bob using DSA\n";
    users["Alice"]->SendMessage("hello", "Bob", DSA);
    cout << "\n===> Bob send message to Alice using Schnorr\n";
    users["Bob"]->SendMessage("hi", "Alice", Schnorr);



    cout << "\n===> Alice send malicious message to Bob using DSA\n";
    users["Alice"]->MaliciousSendMessage("hello", "Bob", DSA);

    cout << "\n===> Bob send malicious message to Alice using Schnorr\n";
    users["Bob"]->MaliciousSendMessage("hi", "Alice", Schnorr);

    cout <<endl<<"Destruction==="<<endl;
    delete admin;

    for(const auto&kv: users)
    {
        delete kv.second;
    }

    Number::Delete();
    return 0;
}