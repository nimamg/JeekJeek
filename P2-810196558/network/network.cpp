#include "network.hpp"


Network::Network () {}

bool Network::signup (string user, string name, string pass) {
	try {
		if (findUser(user) != NULL)
			throw RepeatedUsernameEx();
		User* newUser = new User (user, name, pass);
		users.push_back(newUser);
		cout << "Successfuly Signed up! Welcome to Jeek Jeek " << name << '.' << endl;
		return true;
	}
	catch (RepeatedUsernameEx) {
		cout << "This username is already used by someone else, Please choose another one." << endl;
		return false;
	}
}

User* Network::findUser (string user) {
	for (int i = 0 ; i < users.size() ; i++)
		if (user == users[i]->getUsername())
			return users[i];
	return NULL;
}

bool Network::login (string user, string pass, int sid) {
	try {
		User* requestedUser = findUser(user);
		if (requestedUser == NULL) {
			throw UserNotFoundEx();
		}
		if (requestedUser->isPasswordCorrect(pass)) {
			currentUser = requestedUser;
			cout << user << pass << endl;
			cout << "Login Successful" << endl;
			SID[sid] = currentUser->getUsername();
			return true;
		}
		else {
			throw IncorrectPasswordEx() ;
		}
	}
	catch (IncorrectPasswordEx) {
		cout << "Incorrect password, please try again." << endl;
		return false;
	}
	catch (UserNotFoundEx) {
		cout << "The entered username doesn't exist, please try again." << endl;
		return false;
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
		cout << "Jeek successfully published!" << endl;
	}
	catch (LengthyTextEx) {
		cout << "The text of the Jeek can't have more than 140 characters!" << endl;
	}
	catch (NotLoggedInEx) {
		cout << "You should be logged in too Jeek! Please log in and try again" << endl;
	}
}
string Network::search (string parameter, int sid) {
	string homePagePartI = readFile("home1.txt");
	string homePagePartII = readFile("home2.txt");
	string body = homePagePartI;
	body += findUser(SID[sid])->getName();
	body += homePagePartII;
	if (parameter[0] == '#') {
		parameter = parameter.substr(1);
		searchByHashtag(parameter, body);
	}
	else if (parameter[0] == '@') {
		parameter = parameter.substr(1);
		searchByUsername(parameter, body);
	}
	body += "</div> </div> </body> </html>";
	return body;

}

string Network::createHomePage (int sid) {
	string homePagePartI = readFile("home1.txt");
	string homePagePartII = readFile("home2.txt");
	currentUser = findUser(SID[sid]);
	string body = homePagePartI;
	body += currentUser->getName();
	body += homePagePartII;
	currentUser->printJeeks("",body);
	body += "</div> </div> </body> </html>";
	return body;
}

void Network::searchByUsername (string user, string& body) {
	try {
		User* requestedUser = findUser(user);
		if (requestedUser == NULL) {
			throw UserNotFoundEx();
		}
		requestedUser->printJeeks("", body);
	}
	catch (UserNotFoundEx) {
		cout << "This user doesn't exist." << endl;
	}
}

void Network::searchByHashtag (string tag, string& body) {
	for (int i = 0 ; i < users.size() ; i++) {
		users[i]->printByHashtag(tag, body);
	}
}

string Network::createID () {
	for (int i = 0 ; i < users.size() ; i++)
		if (users[i]->getUsername() == currentUser->getUsername())
			return to_string(i+1);
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



void Network::rejeek (string jeekID, int sid) {
	try {
		int userIndex = getUserIndex(jeekID);
		jeekID = removeUserIndexFromID (jeekID);
		Jeek* Rejeeked = new Jeek (users[userIndex]->rejeek(jeekID));
		Rejeeked->setID(createID());
		findUser(SID[sid])->rejeek(Rejeeked);
	}
	catch (NotLoggedInEx) {
		cout << "You must be logged in to rejeek!" << endl;
	}
	catch (InvalidID) {
		cout << "Invalid jeek ID!" << endl;
	}
}

string Network::showJeek (string jeekID, string sid) {
	try {
		string detailPageI = readFile("details1.txt");
		string detailPageII = readFile("details.txt");
		string body = detailPageI;
		int Sid = atoi(sid.c_str());
		body+=findUser(SID[Sid])->getName();
		body+=detailPageII;
		int userIndex = getUserIndex (jeekID);
		jeekID = removeUserIndexFromID(jeekID);
		body+= users[userIndex]->getUsername();
		body += "<br>";
		users[userIndex]->showJeek (jeekID,body,findUser(SID[Sid])->getUsername());
		return body;
	}
	catch (InvalidID) {
		cout << "Invalid ID! No such Jeek exists." << endl;
	}
}


void Network::likeORdislike (string jeekID,int sid) {
	try {
		int userIndex = getUserIndex(jeekID);
		string fullID = jeekID;
		jeekID = removeUserIndexFromID (jeekID);
		users[userIndex]->likeORdislike (jeekID, findUser(SID[sid])->getUsername());
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
	}
	catch (InvalidID) {
		cout << "Invalid ID! No such Jeek exists." << endl;
	}
}