#include "user.hpp"

User::User (string user, string name, string pass) {
	userName = user;
	displayName = name;
	password = pass;
}

bool User::login (string pass) {
	if (pass == password)
		return true;
	return false;
}

void User::jeek (Jeek* newJeek) {
	string newIdPart = createID();
	newJeek->updateID (newIdPart);
	jeeks.push_back (newJeek);
}


void User::showJeek (string jeekID,string& body,string username) {
	int jeekIndex = getJeekIndex(jeekID);
	cout << displayName << endl;
	jeeks[jeekIndex]->showJeek(body,username);
}

void User::printJeeks (string jeekID, string& body) {
	if (jeekID == "") {
		for (int i = jeeks.size() - 1 ; i >= 0 ; i--) {
			jeeks[i]->printJeekText(body, userName);
		}
	}
	else {
		jeekID = jeekID.substr(jeekID.find('-') + 1);
		int index = atoi (jeekID.c_str()) - 1;
		jeeks[index]->printJeekText(body, userName);
	}
}

bool User::isPasswordCorrect (string pass) {
	if (pass == password)
		return true;
	return false;
}

void User::printByHashtag (string tag, string &body) {
	for (int i = 0 ; i < jeeks.size() ; i++) {
		if (jeeks[i]->includesHashtag(tag)) {
			printJeeks(jeeks[i]->getID(), body);
		}
	}

}

string User::createID () {
	return to_string(jeeks.size() + 1);
}

int User::getJeekIndex (string ID) {
	if (ID.find("-"))
		ID.substr(0,ID.find("-"));
	for (int i = 0 ; i < ID.size() ; i++)
		if (!isdigit(ID[i]))
			throw InvalidID();
	int jeekIndex = stoi (ID) - 1;
	if (jeekIndex > jeeks.size() || jeekIndex < 0)
		throw InvalidID();
	return jeekIndex;
}

string User::removeJeekIndexFromID (string ID) {
	return ID.substr(ID.find("-") + 1);
}

void User::rejeek (Jeek* Rejeeked) {
	Rejeeked->updateID(createID());
	jeeks.push_back(Rejeeked);
}

Jeek* User::rejeek (string ID) {
	for (int i = 0 ; i < ID.size() ; i++)
		if (!isdigit(ID[i]))
			throw InvalidID();
	int index = stoi(ID) - 1;
	jeeks[index]->rejeek();
	return jeeks[index];
}

void User::likeORdislike (string jeekID, string user) {
	int jeekIndex = getJeekIndex(jeekID);
	jeeks[jeekIndex]->LikeORdislike(user);
}

void User::dislike (string jeekID, string user) {
	int jeekIndex = getJeekIndex(jeekID);
	jeeks[jeekIndex]->dislike(user);
}

void User::follow (string username) {
	following.push_back(username);
}

void User::follow (User* follower) {
	User* newFollower = follower;
	followers.push_back(newFollower);
}

void User::unfollow (string username) {
	for (int i = 0 ; i < following.size() ; i++)
		if (following[i] == username) {
			following.erase(following.begin() + i);
			return;
		}
		throw NotFollowingEx();
}

void User::unfollow (User* follower) {
	for (int i = 0 ; i < followers.size() ; i++)
		if (followers[i]->getUsername() == follower->getUsername()) {
			followers.erase(followers.begin() + i);
			return;
		}
}

