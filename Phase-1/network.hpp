#ifndef __NETWORK_H__
#define __NETWORK_H__

#include <vector>
#include <string>
#include <iostream>

#include "user.hpp"
#include "comment.hpp"
#include "jeek.hpp"
#include "notification.hpp"

using namespace std;


class Network {
private:
	vector <User*> users;
	User* currentUser;
public:
	Network ();
	void signup (string user, string name, string pass);
	User* findUser (string user);
	void login (string user, string pass);
	void logout ();
	void jeek (string txt, vector <string> tags, vector <string> Mentions);
	void searchByUsername (string user);
	void searchByHashtag (string tag);
	void comment (string jeekID , string txt);
	string createID ();
	void reply (string commentID , string txt);
	int getUserIndex (string ID);
	string removeUserIndexFromID (string ID);
	void rejeek (string jeekID);
	void showJeek (string jeekID);
	void showComment (string commentID);
	void showReply (string replyID);
	void like (string jeekID);
	void dislike (string jeekID);
	void follow (string username);
	void unfollow (string username);
	void sendMentionNotification (Notification* notif, vector <string> MentionedUsers);
	void showNotifications ();
};

class RepeatedUsernameEx {};

class UserNotFoundEx {};

class LengthyTextEx {};

class NotLoggedInEx {};

class IncorrectPasswordEx {};


#endif