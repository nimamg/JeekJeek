#ifndef __INTERFACE_H__
#define __INTERFACE_H__

#include <string>
#include <iostream>
#include <vector>

#include "network.hpp"

#define WHITESPACE ' '

using namespace std;

class Interface {
private:
	Network network;
public:
	Interface () {}
	void getCommand ();
	void signup ();
	void login();
	void logout ();
	void jeek ();
	void search ();
	void comment ();
	void reply ();
	void rejeek ();
	void showJeek ();
	void showComment ();
	void showReply ();
	void like ();
	void dislike ();
	void follow ();
	void unfollow ();
	void showNotifications ();
};

class InvalidCommandEx {};

#endif