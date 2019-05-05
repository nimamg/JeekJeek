#ifndef __USER_H__
#define __USER_H__

#include <iostream>
#include <vector>
#include <string>

#include "jeek.hpp"
#include "comment.hpp"

using namespace std;

class User {
private:
	string userName;
	string displayName;
	string password;
	vector <Jeek*> jeeks;
	vector <User*> followers;
	vector <string> following;
public:
	User (string user, string name, string pass);
	bool login(string pass);
	void jeek (Jeek* newJeek);
	void showJeek (string jeekID, string& body,string username);
	void printJeeks (string jeekID, string& body);
	bool isPasswordCorrect (string pass);
	void printByHashtag (string tag, string& body);
	string getUsername () { return userName; }
	string createID ();
	string getName () {return displayName;}
	int getJeekIndex (string ID);
	string removeJeekIndexFromID (string ID);
	void rejeek (Jeek* Rejeeked);
	Jeek* rejeek (string ID);
	void likeORdislike (string jeekID, string user);
	void dislike (string jeekID, string user);
	void follow (string username);
	void follow (User* follower);
	void unfollow (string username);
	void unfollow (User* follower);

};

class NotFollowingEx {};

#endif
