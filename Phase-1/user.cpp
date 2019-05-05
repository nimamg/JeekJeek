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
	sendJeekNotificationToFollowers(newJeek->getID());
}

void User::sendJeekNotificationToFollowers (string jeekID) {
	Notification* newNotification = new jeekNotif (userName , jeekID);
	for (int i = 0 ; i < followers.size() ; i++)
		followers[i]->getNotification(newNotification);
}

void User::showJeek (string jeekID) {
	int jeekIndex = getJeekIndex(jeekID);
	cout << displayName << endl;
	jeeks[jeekIndex]->showJeek();
}

void User::printJeeks (string jeekID) {
	if (jeekID == "") {
		for (int i = 0 ; i < jeeks.size() ; i++) {
			cout << jeeks[i]->getID() << " " << displayName << endl;
			jeeks[i]->printJeekText();
		}
	}
	else {
		jeekID = jeekID.substr(jeekID.find('-') + 1);
		int index = atoi (jeekID.c_str()) - 1;
		cout << jeeks[index]->getID() << " " << displayName << endl;
		jeeks[index]->printJeekText();
	}
}

bool User::isPasswordCorrect (string pass) {
	if (pass == password)
		return true;
	return false;
}

void User::printByHashtag (string tag) {
	for (int i = 0 ; i < jeeks.size() ; i++) {
		if (jeeks[i]->includesHashtag(tag)) {
			printJeeks(jeeks[i]->getID());
		}
	}

}

string User::createID () {
	return to_string(jeeks.size() + 1);
}

void User::comment (Comment* newComment , string jeekID) {
	int jeekIndex = getJeekIndex(jeekID);
	for (int i = 0 ; i < jeekID.size();i++)
		if (!isdigit(jeekID[i])) {
			throw InvalidID();
		}
	if (jeekIndex > jeeks.size())
		throw InvalidID();
	jeeks[jeekIndex]->comment(newComment);
}

int User::getJeekIndex (string ID) {
	if (ID.find("-"))
		ID = ID.substr(0,ID.find("-"));
	for (int i = 0 ; i < ID.size() ; i++)
		if (!isdigit(ID[i]))
			throw InvalidID();
	int jeekIndex = stoi (ID) - 1;
	if (jeekIndex > jeeks.size() || jeekIndex < 0)
		throw InvalidID();
	return jeekIndex;
}

void User::reply (Reply* newReply, string commentID) {
	int jeekIndex = getJeekIndex (commentID);
	if (jeekIndex > jeeks.size() || !isdigit(commentID[0]))
		throw InvalidID();
	commentID = removeJeekIndexFromID(commentID);
	jeeks[jeekIndex]->reply(newReply, commentID);
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

void User::showComment (string commentID) {
	int jeekIndex = getJeekIndex(commentID);
	commentID = removeJeekIndexFromID (commentID);
	cout << displayName << endl;
	jeeks[jeekIndex]->showComment (commentID);
}

void User::showReply (string replyID) {
	int jeekIndex = getJeekIndex(replyID);
	replyID = removeJeekIndexFromID (replyID);
	cout << displayName << endl;
	jeeks[jeekIndex]->showReply (replyID);
}

void User::like (string jeekID, string user) {
	int jeekIndex = getJeekIndex(jeekID);
	jeeks[jeekIndex]->Like(user);
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

void User::getNotification (Notification* newNotif) {
	Notification* notif = newNotif;
	notifs.push_back(notif);
}

Notification* User::getMentionNotification () {
	Notification* newNotif = new mentionNotif (userName, jeeks[jeeks.size()-1]->getID());
	return newNotif;
}

void User::showNotifications () {
	for (int i = 0 ; i < notifs.size() ; i++)
		notifs[i]->print();
}