#include "jeek.hpp"

Jeek::Jeek (string txt, vector <string> tags, vector <string> Mentions, string ID) {
	text = txt;
	for (int i = 0 ; i < tags.size() ; i++)
		hashTags.push_back(tags[i]);
	for (int i = 0 ; i < Mentions.size() ; i++)
		mentions.push_back(Mentions[i]);
	likes = 0;
	reJeeks = 0;
	id = ID;
}

Jeek::Jeek (Jeek* jeek) {
	text = "Rejeeked: " + jeek->text;
	for (int i = 0 ; i < jeek->hashTags.size() ; i++)
		hashTags.push_back(jeek->hashTags[i]);
	for (int i = 0 ; i < jeek->mentions.size() ; i++)
		mentions.push_back(jeek->mentions[i]);
	likes = 0 ;
	reJeeks = 0;
	id = "";
}

void Jeek::Like (string username) {
	for (int i = 0 ; i < likers.size() ; i++)
		if (likers[i] == username)
			return ;
	likers.push_back(username);
	likes++;
}

void Jeek::rejeek () {
	reJeeks++;
}

void Jeek::dislike (string username) {
	for (int i = 0 ; i < likers.size() ; i++)
		if (likers[i] == username) {
			likes--;
			likers.erase(likers.begin() + i);
		}
}

void Jeek::showJeek () {
	cout << text << endl;
	if (hashTags.size() != 0) {
		for (int i = 0 ; i < hashTags.size() ; i++)
			cout << "#" << hashTags[i] << endl;
	}
	if (mentions.size() != 0) {
		for (int i = 0 ; i < mentions.size() ; i++) 
			cout << "@" << mentions[i] << endl;
	}
	cout << "Likes: " << likes << endl;
	cout << "Rejeeks: " << reJeeks << endl;
	if (comments.size() != 0) {
		cout << "Comments: " << endl;
		for (int i = 0 ; i < comments.size() ; i++)
			comments[i]->printText();
	}
}

void Jeek::printJeekText () {
	cout << text << endl;
}

bool Jeek::includesHashtag (string tag) {
	for (int i = 0 ; i < hashTags.size() ; i++) {
		if (hashTags[i] == tag)
			return true;
	}
	return false;
}

void Jeek::updateID (string newPart) {
	id  = id + "-" + newPart;
}

string Jeek::createID () {
	return (id + "-" + to_string(comments.size() + 1));
}

void Jeek::comment (Comment* newComment) {
	string commentID = createID ();
	newComment->setID (commentID);
	comments.push_back(newComment);
}

void Jeek::reply (Reply* newReply , string ID) {
	int commentIndex = getCommentIndex (ID);
	if (commentIndex > comments.size() || !isdigit(ID[0]))
		throw InvalidID();
	ID = removeCommentIndexFromID(ID);
	comments[commentIndex]->reply(newReply, ID);
}

int Jeek::getCommentIndex (string ID) {
	if (ID.find("-"))
		ID = ID.substr(0,ID.find("-"));
	for (int i = 0 ; i < ID.size() ; i++)
		if (!isdigit(ID[i]))
			throw InvalidID();
	int commentIndex = stoi (ID) - 1;
	if (commentIndex > comments.size() || commentIndex < 0)
		throw InvalidID();
	return commentIndex;
}

string Jeek::removeCommentIndexFromID (string ID) {
	if (ID.find("-") != -1) {
		return ID.substr(ID.find("-") + 1);
	}
	return "R" + ID;
}

void Jeek::showComment (string commentID) {
	int commentIndex = getCommentIndex (commentID);
	comments[commentIndex]->show();
}

void Jeek::showReply (string replyID) {
	int commentIndex = getCommentIndex(replyID);
	replyID = removeCommentIndexFromID (replyID);
	comments[commentIndex]->showReply (replyID);
}