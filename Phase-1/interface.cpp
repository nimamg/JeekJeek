#include "interface.hpp"

void Interface::getCommand () {
	string command;
	cin >> command;
	try {
		if (command == "signup") 
			signup();
		else if (command == "login") 
			login();
		else if (command == "logout") 
			logout();
		else if (command == "jeek") 
			jeek();
		else if (command == "search") 
			search();
		else if (command == "comment") 
			comment();
		else if (command == "reply") 
			reply();
		else if (command == "rejeek") 
			rejeek();
		else if (command == "showJeek") 
			showJeek();
		else if (command == "showComment") 
			showComment();
		else if (command == "showReply")
			showReply();
		else if (command == "like") 
			like();
		else if (command == "dislike") 
			dislike();
		else if (command == "follow") 
			follow();
		else if (command == "unfollow") 
			unfollow();
		else if (command == "notifications") 
			showNotifications();
		else
			throw InvalidCommandEx();

	}
	catch (InvalidCommandEx) {
		cout << "Command not available." << endl;
		cin.sync();
	}
}

void Interface::signup () {
	string user, pass, name;
	cin >> user >> name >> pass;
	network.signup (user, name, pass);
}

void Interface::login () {
	string user, pass;
	cin >> user >> pass;
	network.login (user , pass);
}

void Interface::logout () {
	network.logout ();
	cout << "Logout successful.	" << endl;
}

void Interface::jeek () {
	string command;
	string text;
	vector <string> tags;
	vector <string> mentions;
	cin >> command;
	while (command != "publish" && command != "abort") {
		if (command == "text") {
			getline (cin, text);
			text = text.substr(1);
		}
		else if (command == "tag") {
			string tag;
			getline(cin, tag);
			while (tag[0] == WHITESPACE) {
				tag = tag.substr(1);
			}
			if (tag.find(WHITESPACE) != -1) {
				cout << "Hashtags can't contain white spaces." << endl;
			}
			else
				tags.push_back(tag);
		}
		else if (command == "mention") {
			string username;
			cin >> username; 
			mentions.push_back(username);
		}
		else {
			cout << "Invalid command." << endl;
			cin.sync();
		}
		cin >> command;
	}
	if (command == "publish") {
		network.jeek(text, tags, mentions);
	}
	else if (command == "abort")
		return;
}

void Interface::search () {
	string searchedItem;
	cin >> searchedItem;
	if (searchedItem[0] == '@') {
		searchedItem = searchedItem.substr(1);
		network.searchByUsername (searchedItem);
	}
	else if (searchedItem[0] == '#') {
		searchedItem = searchedItem.substr(1);
		network.searchByHashtag (searchedItem);
	}
	else {
		cout << "Invalid input." << endl;
	}
}

void Interface::comment () {
	string jeekID;
	cin >> jeekID;
	string commentText;
	getline (cin, commentText);
	while (commentText[0] == WHITESPACE) {
		commentText = commentText.substr(1);
	}
	network.comment(jeekID, commentText);
}

void Interface::reply () {
	string ID;
	cin >> ID;
	string replyText;
	getline(cin, replyText);
	while (replyText[0] == WHITESPACE)
		replyText = replyText.substr(1);
	network.reply (ID, replyText);
}

void Interface::rejeek () {
	string jeekID;
	cin >> jeekID;
	network.rejeek(jeekID);
}

void Interface::showJeek () {
	string jeekID;
	cin >> jeekID;
	network.showJeek(jeekID);
}

void Interface::showComment () {
	string commentID;
	cin >> commentID;
	network.showComment(commentID);
}

void Interface::showReply () {
	string replyID;
	cin >> replyID;
	network.showReply(replyID);
}

void Interface::like () {
	string jeekID;
	cin >> jeekID;
	network.like(jeekID);
}

void Interface::dislike () {
	string jeekID;
	cin >> jeekID;
	network.dislike(jeekID);
}

void Interface::follow () {
	string username;
	cin >> username;
	network.follow(username);
}

void Interface::unfollow () {
	string username;
	cin >> username;
	network.unfollow(username);
}

void Interface::showNotifications () {
	network.showNotifications();
}