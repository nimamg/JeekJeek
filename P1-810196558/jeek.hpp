#ifndef __JEEK_H__
#define __JEEK_H__

#include <iostream>
#include <vector>
#include <string>

#include "comment.hpp"

using namespace std;

class Jeek {
private:
	string id;
	string text;
	vector <string> hashTags;
	vector <string> mentions;
	vector <Comment*> comments;
	vector <string> likers;
	int likes;
	int reJeeks;
public:
	Jeek (string txt, vector <string> tags, vector <string> Mentions, string ID);
	Jeek (Jeek* jeek);
	void rejeek();
	void Like (string username);
	void dislike (string username);
	void showJeek ();
	void printJeekText ();
	bool includesHashtag (string tag);
	string getID () { return id; }
	void setID (string ID) { id = ID; }
	void updateID (string newPart);
	string createID ();
	void comment (Comment* newComment) ;
	void reply (Reply* newReply , string ID);
	int getCommentIndex (string ID);
	string removeCommentIndexFromID (string ID);
	void showComment (string commentID);
	void showReply (string replyID);
	
};

#endif