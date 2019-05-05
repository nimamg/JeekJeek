#ifndef __NOTIFICATION_H__
#define __NOTIFICATION_H__

#include <iostream>
#include <string>

using namespace std;

class Notification {
protected:
	string text;
	string user;
	string ID;
public:
	void print ();
};

class likeDislikeNotif : public Notification {
public:
	likeDislikeNotif (string username , string jeekID, bool like);
};

class jeekNotif : public Notification {
public:
	jeekNotif (string username , string jeekID);
};

class commentNotif : public Notification {
public:
	commentNotif (string username , string jeekID);
};

class mentionNotif : public Notification {
public:
	mentionNotif (string username , string jeekID);
};

class rejeekNotif : public Notification {
public:
	rejeekNotif (string username , string jeekID);
};

class replyNotif : public Notification {
public:
	replyNotif (string username , string commentID);
};

#endif