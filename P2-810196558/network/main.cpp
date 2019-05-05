#include "../server/server.hpp"
#include "network.hpp"
#include "handlers.hpp"
#include <map>
using namespace std;

void makeSomeTestUserAndJeeks (Network* network, int& SID);

int main (int argc, char** argv) {
	int SID = 1;
	Network* network = new Network();
	makeSomeTestUserAndJeeks(network, SID);
	try {
		Server server (argc > 1 ? atoi(argv[1]) : 5000);
		server.get("/login" , new ShowPage("login.html"));
		server.get("/signup", new ShowPage("signup.html"));
		server.post("/logout", new LogoutHandler(network));
		server.get("/", new ShowPage("signup.html"));
		server.post("/login" , new LoginHandler(network, SID));
		server.post("/signup", new SignupHandler(network));
		server.post("/search", new SearchHandler(network));
		server.post("/details", new DetailsHandler(network));
		server.get("/home", new HomeHandler(network));
		server.get("/wrongpass", new ShowPage("wrongpass.html"));
		server.get("/wrongusername", new ShowPage("wronguser.html"));
		server.post("/like", new LikeHandler(network));
		server.post("/rejeek", new RejeekHandler(network));
		server.get("/dislike.png", new ShowImage("./dislike.png"));
		server.get("/like.png", new ShowImage("./like.png"));
		server.run();
	}
	catch (Server::Exception e) {
    cerr << e.getMessage() << endl;
  }
}

void makeSomeTestUserAndJeeks (Network* network, int& SID) {
	network->signup("nima","nima","pass");
	network->login("nima","pass",SID);
	vector<string>tags;
	tags.push_back("firstJeek");
	tags.push_back("JeekJeek");
	vector <string> mentions;
	network->jeek("Hey this is the first jeek." , tags, mentions);

	vector <string> tags2;
	tags2.push_back("awesome");
	tags2.push_back("html");
	tags2.push_back("css");
	vector <string> mentions2;
	mentions2.push_back("ali");
	network->jeek("Awesome project, I'm beginning to like HTML and CSS stuff", tags2, mentions2);
	network->logout();

	network->signup("30bill","ali","ay");
	network->login("30bill","ay",SID);
	vector <string> tags3;
	tags3.push_back("CSGO");
	tags3.push_back("nerdDogg");
	vector<string> mentions3;
	mentions3.push_back("alik");
	mentions3.push_back("nima");
	network->jeek("CS:GO Is the best. I'm the most khafan human ever!!", tags3, mentions3);
	network->logout();

	network->signup("par&", "Parand", "pmg");
	network->login("par&","pmg",SID);
	vector<string> tags4;
	tags4.push_back("colors");
	tags4.push_back("painting");
	vector<string>mentions4;
	mentions4.push_back("nima");
	network->jeek("Painting is the best hobby ever!! I love it.", tags4, mentions4);
	network->logout();

}