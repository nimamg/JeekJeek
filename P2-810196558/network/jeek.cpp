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

void Jeek::LikeORdislike (string username) {
	for (int i = 0 ; i < likers.size() ; i++)
		if (likers[i] == username) {
			likers.erase(likers.begin() + i);
			likes--;
			return;
		}
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

void Jeek::showJeek (string &body, string username) {
	string detailsPageI = readFile("jeekdetail1.txt");
	string detailsPageII = readFile("jeekdetail2.txt");
	body += text;
	body += "<br>";
	if (hashTags.size() != 0) {
		for (int i = 0 ; i < hashTags.size() ; i++) {
			body+= "#"; 
			body+=hashTags[i];
		}
	}
	body += "<br>";
	if (mentions.size() != 0) {
		for (int i = 0 ; i < mentions.size() ; i++) {
			body+= "@"; 
			body+=mentions[i];	
			body+=",";	
		}
	}
	body += "<br>";
	body+= "Likes: ";
	body+= to_string(likes);
	body += "<span style=\"margin-left:20px;\">";
	body+= "Rejeeks: "; 
	body+= to_string(reJeeks);
	body+= "</span></p>";
	body+= "<form action=\"/like\" method=\"post\"><input name=\"jeekID\" value=\"";
	body += id;
	body += detailsPageI;
	bool liked = false;
	for (int i = 0 ; i < likers.size() ; i++)
		if (likers[i] == username)
			liked = true;
	if (liked)
		body += "./like.png";
	else
		body += "./dislike.png";
	body += detailsPageII;
}

void Jeek::printJeekText (string &body, string username) {
	string homeHTMLCodePartI = readFile("jeekhome1.txt");
	string homeHTMLCodePartII = readFile("jeekhome2.txt");
	string homeHTMLCodePartIII = readFile("jeekhome3.txt");
	body += homeHTMLCodePartI;
	body += "@";
	body += username;
	body += ": ";
	body += text;
	body += homeHTMLCodePartII;
	body += id;
	body += homeHTMLCodePartIII;
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

