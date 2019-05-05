#include "network.hpp"

Network::Network () {}

void Network::signup (string user, string name, string pass) {
	try {
		if (findUser(user) != NULL)
			throw RepeatedUsernameEx();
		User* newUser = new User (user, name, pass);
		users.push_back(newUser);
		cout << "Successfuly Signed up! Welcome to Jeek Jeek " << name << '.' << endl;
	}
	catch (RepeatedUsernameEx) {
		cout << "This username is already used by someone else, Please choose another one." << endl;
	}
}

User* Network::findUser (string user) {
	for (int i = 0 ; i < users.size() ; i++)
		if (user == users[i]->getUsername())
			return users[i];
	return NULL;
}

void Network::login (string user, string pass) {
	try {
		User* requestedUser = findUser(user);
		if (requestedUser == NULL) {
			throw UserNotFoundEx();
		}
		if (requestedUser->isPasswordCorrect(pass)) {
			currentUser = requestedUser;
			cout << "Login Successful" << endl;
			return;
		}
		else {
			throw IncorrectPasswordEx() ;
		}
	}
	catch (IncorrectPasswordEx) {
		cout << "Incorrect password, please try again." << endl;
	}
	catch (UserNotFoundEx) {
		cout << "The entered username doesn't exist, please try again." << endl;
	}
}

void Network::logout () {
	currentUser = NULL;
}

void Network::jeek (string txt, vector <string> tags, vector <string> Mentions) {
	try {
		if (currentUser == NULL)
			throw NotLoggedInEx();
		if (txt.size() > 140)
			throw LengthyTextEx();
		string id = createID ();
		class Jeek* newJeek = new class Jeek (txt , tags, Mentions, id);
		currentUser->jeek(newJeek);
		sendMentionNotification(currentUser->getMentionNotification(), Mentions);
		cout << "Jeek successfully published! A notification will be sent to all of your followers." << endl;
	}
	catch (LengthyTextEx) {
		cout << "The text of the Jeek can't have more than 140 characters!" << endl;
	}
	catch (NotLoggedInEx) {
		cout << "You should be logged in too Jeek! Please log in and try again" << endl;
	}
}

void Network::searchByUsername (string user) {
	try {
		User* requestedUser = findUser(user);
		if (requestedUser == NULL) {
			throw UserNotFoundEx();
		}
		requestedUser->printJeeks();
	}
	catch (UserNotFoundEx) {
		cout << "This user doesn't exist." << endl;
	}
}

void Network::searchByHashtag (string tag) {
	for (int i = 0 ; i < users.size() ; i++) {
		users[i]->printByHashtag(tag);
	}
}

string Network::createID () {
	for (int i = 0 ; i < users.size() ; i++)
		if (users[i]->getUsername() == currentUser->getUsername())
			return to_string(i+1);
}

void Network::comment (string jeekID , string txt) {
	try {
		if (currentUser == NULL)
			throw NotLoggedInEx();
		int userIndex = getUserIndex(jeekID);
		Comment* newComment = new Comment (txt, currentUser->getUsername());
		string fullID = jeekID;
		jeekID = removeUserIndexFromID(jeekID);
		users[userIndex]->comment (newComment, jeekID);
		Notification* newNotification = new commentNotif (currentUser->getUsername() , fullID);
		users[userIndex]->getNotification (newNotification);
	}
	catch (NotLoggedInEx) {
		cout << "You should be logged in too Jeek! Please log in and try again" << endl;
	}
	catch (InvalidID) {
		cout << "Invalid ID! No such Jeek exists." << endl;
	}
}

int Network::getUserIndex (string ID) {
	string userIndexString = ID.substr(0,ID.find("-"));
		for (int i = 0 ; i < userIndexString.size() ; i++)
			if (!isdigit(userIndexString[i]))
				throw InvalidID();
		int userIndex = stoi(userIndexString) - 1;
		if (userIndex >= users.size() || userIndex < 0)
			throw InvalidID();
		return userIndex;
}

string Network::removeUserIndexFromID (string ID) {
	if (ID.find("-") == -1)
		throw InvalidID();
	return ID.substr(ID.find("-") + 1);
}

void Network::reply (string commentID , string txt) {
	try {
		if (currentUser == NULL)
			throw NotLoggedInEx();
		int userIndex = getUserIndex(commentID);
		Reply* newReply = new Reply (txt, currentUser->getUsername());
		string fullID = commentID;
		commentID = removeUserIndexFromID(commentID);
		users[userIndex]->reply (newReply, commentID);
		Notification* newNotification = new replyNotif (currentUser->getUsername(), fullID);
		users[userIndex]->getNotification(newNotification);
	}
	catch (InvalidID) {
		cout << "Invalid ID! No such comment exists." << endl;
	}
}

void Network::rejeek (string jeekID) {
	try {
		if (currentUser == NULL)
			throw NotLoggedInEx();
		int userIndex = getUserIndex(jeekID);
		string fullID = jeekID;
		jeekID = removeUserIndexFromID (jeekID);
		Jeek* Rejeeked = new Jeek (users[userIndex]->rejeek(jeekID));
		Rejeeked->setID(createID());
		currentUser->rejeek(Rejeeked);
		Notification* newNotification = new rejeekNotif (currentUser->getUsername(), fullID);
		users[userIndex]-> getNotification(newNotification);
	}
	catch (NotLoggedInEx) {
		cout << "You must be logged in to rejeek!" << endl;
	}
	catch (InvalidID) {
		cout << "Invalid jeek ID!" << endl;
	}
}

void Network::showJeek (string jeekID) {
	try {
		int userIndex = getUserIndex (jeekID);
		jeekID = removeUserIndexFromID(jeekID);
		users[userIndex]->showJeek (jeekID);
	}
	catch (InvalidID) {
		cout << "Invalid ID! No such Jeek exists." << endl;
	}
}

void Network::showComment (string commentID) {
	try {
		int userIndex = getUserIndex(commentID);
		commentID = removeUserIndexFromID(commentID);
		users[userIndex]->showComment(commentID);
	}
	catch (InvalidID) {
		cout << "Invalid ID! No such Comment exists." << endl;
	}
}

void Network::showReply (string replyID) {
	try {
		int userIndex = getUserIndex(replyID);
		replyID = removeUserIndexFromID(replyID);
		users[userIndex]->showReply(replyID);
	}
	catch (InvalidID) {
		cout << "Invalid ID! No such Reply exists." << endl;
	}
}

void Network::like (string jeekID) {
	try {
		int userIndex = getUserIndex(jeekID);
		string fullID = jeekID;
		jeekID = removeUserIndexFromID (jeekID);
		users[userIndex]->like (jeekID, currentUser->getUsername());
		Notification* newNotification = new likeDislikeNotif (currentUser->getUsername(), fullID , true);
		users[userIndex]->getNotification(newNotification);
		}
	catch (InvalidID) {
		cout << "Invalid ID! No such Jeek exists." << endl;
	}
}

void Network::dislike (string jeekID) {
	try {
		int userIndex = getUserIndex(jeekID);
		string fullID = jeekID;
		jeekID = removeUserIndexFromID (jeekID);
		users[userIndex]->dislike (jeekID, currentUser->getUsername());
		Notification* newNotification = new likeDislikeNotif (currentUser->getUsername(), fullID , false);
		users[userIndex]->getNotification(newNotification);
	}
	catch (InvalidID) {
		cout << "Invalid ID! No such Jeek exists." << endl;
	}
}

void Network::follow (string username) {
	try {
		for (int i = 0 ; i < users.size() ; i++)
			if (users[i]->getUsername() == username) {
				currentUser->follow(username);
				users[i]->follow(currentUser);
				return;
			}
		throw UserNotFoundEx();
	}
	catch (UserNotFoundEx) {
		cout << "The entered username doesn't exist! Please try again." << endl;
	}	
}

void Network::unfollow (string username) {
	try {
		for (int i = 0 ; i < users.size() ; i++)
			if (users[i]->getUsername() == username) {
				currentUser->unfollow(username);
				users[i]->unfollow(currentUser);
				return;
			}
		throw UserNotFoundEx();
	}
	catch (UserNotFoundEx) {
		cout << "This username doesn't exist" << endl;
	}
}

void Network::sendMentionNotification (Notification* notif, vector <string> MentionedUsers) {
	for (int i = 0 ; i < MentionedUsers.size() ; i++)
		for (int j = 0 ; j < users.size() ; j++)
			if (MentionedUsers[i] == users[j]->getUsername()) {
				users[j]->getNotification(notif);
				break;
			}
}

void Network::showNotifications() {
	currentUser->showNotifications();
}