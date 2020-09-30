//
// Created by whosdad on 29/09/2020.
//

#ifndef BABEL_USER_HPP
#define BABEL_USER_HPP

class User {
    public:
    User() = default;
    ~User() = default;

    static bool Login();
    static bool Register();
    static bool UserExist();
    static bool Status();
    static bool Friend();

    static bool PutFriend();
    static bool PostFriend();
    static bool DeleteFriend();
    static bool GetFriends();

    static bool IsConnected();
    static bool StartCall();
    static bool EndCall();
};
#endif //BABEL_USER_HPP
