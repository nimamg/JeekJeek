#include "../server/server.hpp"
#include <string> 
#include <cstdlib>

using namespace std;

class LoginHandler : public RequestHandler {
public:
	LoginHandler(Network* net, int& id) : sid(id) {network = net;}
	Response* callback (Request* req) {
		string username = req->getBodyParam("username");
	    string password = req->getBodyParam("password");
	    if (network->login(username,password,sid)) {
	    	Response *res = Response::redirect("/home");
	    	res->setSessionId (to_string(sid));
	    	sid++;
	    	return res;
	    }
	    else {
	    	Response *res = Response::redirect("/wrongpass");
	    	return res;
	    }
	}
	private: 
		Network* network;
		int& sid;
};

class SignupHandler : public RequestHandler {
public:
	SignupHandler (Network* net) {network = net;}
	Response* callback (Request* req) {
		string username = req->getBodyParam("username");
		string pass = req->getBodyParam("password");
		string name = req->getBodyParam("displayname");
		if(network->signup(username, name, pass)) {
			Response* res = Response::redirect("/login");
			return res;
		}
		else {
			Response *res = Response::redirect("/wrongusername");
			return res;
		}
	}
private:
	Network* network;
};

class SearchHandler : public RequestHandler {
public:
	SearchHandler (Network* net) {network = net;}
	Response* callback (Request* req) {
		string id = req->getSessionId();
		sid = atoi(id.c_str());
		string body = network->search(req->getBodyParam("search"), sid);
		Response* res = new Response;
		res->setHeader("Content-Type", "text/html");
		res->setBody(body);
		return res;
	}
private:
	Network *network;
	int sid;
};

class HomeHandler : public RequestHandler {
public:
	HomeHandler (Network* net) {network = net;}
	Response* callback (Request* req) {
		int sid = atoi(req->getSessionId().c_str());
		Response* res = new Response;
		res->setHeader("Content-Type", "text/html");
		string body = network->createHomePage(sid);
		res->setBody(body);
		return res;
	}

private:
	Network* network;
};

class LogoutHandler : public RequestHandler {
public:
	LogoutHandler (Network* net) {network = net;}
	Response* callback (Request* req) {
		network->logout();
		Response* res = Response::redirect("/login");
		return res;
	}
private:
	Network* network;
};

class DetailsHandler : public RequestHandler {
public:
	DetailsHandler(Network* net) {network = net;}
		Response* callback (Request* req) {
			Response* res = new Response;
			res->setHeader("Content-Type", "text/html");
			string id = req->getBodyParam("jeekID");
			string body = network->showJeek(id, req->getSessionId());
			res->setBody(body);
			return res;
		}
private:
	Network* network;
};

class LikeHandler : public RequestHandler {
public:
	LikeHandler(Network* net) {network = net;}
	Response* callback (Request* req) {
		int sid = atoi(req->getSessionId().c_str());
		string jeekID = req->getBodyParam("jeekID");
		network->likeORdislike(jeekID, sid);
		Response* res = new Response;
		res->setHeader("Content-Type", "text/html");
		string body = network->showJeek(jeekID, req->getSessionId());
		res->setBody(body);
		return res;
	}
private:
	Network* network;
};

class RejeekHandler : public RequestHandler {
public:
	RejeekHandler(Network* net) {network = net;}
	Response* callback (Request* req) {
		string id = req->getBodyParam("jeekID");
		int sid = atoi(req->getSessionId().c_str());
		network->rejeek(id, sid);
		Response* res = new Response;
		res->setHeader("Content-Type", "text/html");
		string body = network->createHomePage(sid);
		res->setBody(body);
		return res;
	}
private:
	Network* network;
};