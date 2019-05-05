#ifndef __JEEK_H__
#define __JEEK_H__

#include <iostream>
#include <vector>
#include <string>
#include "../server/server.hpp"


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
	void LikeORdislike (string username);
	void dislike (string username);
	void showJeek (string &body,string username);
	void printJeekText (string &body, string username);
	bool includesHashtag (string tag);
	string getID () { return id; }
	void setID (string ID) { id = ID; }
	void updateID (string newPart);
	string createID ();
	
};

#endif