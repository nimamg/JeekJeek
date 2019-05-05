#include "notification.hpp"

void Notification::print () {
	cout << user << " " << text << " " << ID << endl;
}

likeDislikeNotif::likeDislikeNotif (string username , string jeekID, bool like) {
	user = username;
	ID = jeekID;
	if (like)
		text = "liked";
	else
		text = "disliked";
}

jeekNotif::jeekNotif (string username , string jeekID) {
	user = username;
	ID = jeekID;
	text = "jeeked";
}

commentNotif::commentNotif (string username , string jeekID) {
	user = username;
	ID = jeekID;
	text = "commented on";
}

mentionNotif::mentionNotif (string username , string jeekID) {
	user = username;
	ID = jeekID;
	text = "mentioned you in";
}

rejeekNotif::rejeekNotif (string username , string jeekID) {
	user = username;
	ID = jeekID;
	text = "rejeeked";
}

replyNotif::replyNotif (string username , string commentID) {
	user = username;
	ID = commentID;
	text = "replied";
}