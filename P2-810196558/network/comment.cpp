#include "comment.hpp"

Comment::Comment (string txt) {
	text = txt;
}

void Comment::printText () {
	cout << text << endl;
}

void Comment::show () {
	cout << text << endl;
	if (replies.size() != 0) {
		cout << "Replies: " << endl;
		for (int i = 0 ; i < replies.size() ; i++)
			replies[i]->printText();
		cout << endl;
	}
}

void Comment::setID (string ID) {
	id = ID;
}

void Comment::reply (Reply* newReply, string ID) {
	if (isItRepliedToYou(ID)) {
		string replyID = createID ();
		newReply->setID(replyID);
		replies.push_back (newReply);
	}
	else {
		int replyIndex = getReplyIndex (ID);
		ID = removeReplyIndexFromID (ID);
		replies[replyIndex]->reply (newReply, ID);
	}
}

bool Comment::isItRepliedToYou (string ID) {
	if (ID.find("-"))
		return false;
	return true;
}

string Comment::createID () {
	string ID = id + "-" + to_string(replies.size() + 1);
	return ID;
}

int Comment::getReplyIndex (string ID) {
	if (ID.find("-"))
		ID = ID.substr(0,ID.find("-"));
	for (int i = 0 ; i < ID.size() ; i++)
		if (!isdigit(ID[i]))
			throw InvalidID();
	int replyIndex = stoi (ID) - 1;
	if (replyIndex > replies.size() || replyIndex < 0)
		throw InvalidID();
	return replyIndex;
}

string Comment::removeReplyIndexFromID (string ID) {
	if (ID.find("-"))
		return ID.substr(ID.find("-") - 1);
	return ID;
}

void Comment::showReply (string replyID) {
	int index = getReplyIndex(replyID);
	if (isItRepliedToYou(replyID)) {
		replies[index]->show();
	}
	else {
		replyID = removeReplyIndexFromID(replyID);
		replies[index]->showReply(replyID);
	}
}



Reply::Reply (string txt) : Comment(txt) {}

void Reply::printText () {
	cout << text << endl;
}

void Reply::showReply (string replyID) {
	int replyIndex = getReplyIndex (replyID);
	if (isItRepliedToYou(replyID))
		replies[replyIndex]->show();
	else {
		replyID = removeReplyIndexFromID (replyID);
		replies[replyIndex]->showReply(replyID);
	}
}

void Reply::show () {
	cout << text << endl;
	if (replies.size() != 0) {
		cout << "Replies: " << endl;
		for (int i = 0 ; i < replies.size() ; i++)
			replies[i]->printText();
		cout << endl;
	}
}

void Reply::setID (string ID) {
	id = ID;
}