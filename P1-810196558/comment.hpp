#ifndef __COMMENT_H__
#define __COMMENT_H__

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Reply;

class Comment {
protected:
	string id;
	string text;
	vector <Reply*> replies;
	string username;
public:
	Comment (string txt, string user);
	void reply(Reply* newReply, string ID);
	void printText();
	void show();
	bool isItHere (string id);
	void showReply(string replyID);
	void setID (string ID);
	bool isItRepliedToYou (string ID);
	string createID ();
	int getReplyIndex (string ID);
	string removeReplyIndexFromID (string ID);
};

class Reply : public Comment {
public:
	Reply (string txt, string user);
	void setID (string ID);
	void printText ();
	void showReply (string replyID);
	void show();
};

class InvalidID {};

#endif