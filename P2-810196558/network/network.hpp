#ifndef __NETWORK_H__
#define __NETWORK_H__

#include <vector>
#include <string>
#include <cstdlib>
#include <iostream>
#include <map> 

#include "user.hpp"
#include "jeek.hpp"
#include "../server/server.hpp"

using namespace std;


class Network {
private:
	vector <User*> users;
	User* currentUser;
	map <int, string> SID;
public:
	Network ();
	bool signup (string user, string name, string pass);
	User* findUser (string user);
	bool login (string user, string pass, int sid);
	void logout ();
	void jeek (string txt, vector <string> tags, vector <string> Mentions);
	string search (string parameter, int sid);
	void searchByUsername (string user, string &body);
	void searchByHashtag (string tag, string &body);
	string createID ();
	int getUserIndex (string ID);
	string removeUserIndexFromID (string ID);
	void rejeek (string jeekID, int sid);
	string showJeek (string jeekID, string sid);
	void likeORdislike (string jeekID, int sid);
	void dislike (string jeekID);
	void follow (string username);
	void unfollow (string username);
	string createHomePage (int sid);
};

class RepeatedUsernameEx {};

class UserNotFoundEx {};

class LengthyTextEx {};

class NotLoggedInEx {};

class IncorrectPasswordEx {};


#endif