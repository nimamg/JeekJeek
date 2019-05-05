#ifndef __USER_H__
#define __USER_H__

#include <iostream>
#include <vector>
#include <string>

#include "jeek.hpp"
#include "comment.hpp"
#include "notification.hpp"

using namespace std;

class User {
private:
	string userName;
	string displayName;
	string password;
	vector <Jeek*> jeeks;
	vector <Notification*> notifs;
	vector <User*> followers;
	vector <string> following;
public:
	User (string user, string name, string passb);
	bool login(string pass);
	void jeek (Jeek* newJeek);
	void showJeek (string jeekID);
	void printJeeks (string jeekID = "");
	bool isPasswordCorrect (string pass);
	void printByHashtag (string tag);
	string getUsername () { return userName; }
	string createID ();
	void comment (Comment* newComment , string jeekID);
	void reply (Reply* newReply, string commentID);
	int getJeekIndex (string ID);
	string removeJeekIndexFromID (string ID);
	void rejeek (Jeek* Rejeeked);
	Jeek* rejeek (string ID);
	void showComment (string commentID);
	void showReply (string replyID);
	void like (string jeekID, string user);
	void dislike (string jeekID, string user);
	void follow (string username);
	void follow (User* follower);
	void unfollow (string username);
	void unfollow (User* follower);
	void getNotification (Notification * newNotif);
	void sendJeekNotificationToFollowers (string jeekID);
	Notification* getMentionNotification ();
	void showNotifications ();
	bool isIdValid (string ID);
};

class NotFollowingEx {};

#endif
