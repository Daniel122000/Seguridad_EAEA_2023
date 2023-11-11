#include "fnafselbdFDF.hpp"
using namespace std;
int cnreiuabisvdbf::gdfgibyasd(std::string X) {
	if ((vasnbdikkhu = socket(AF_INET, SOCK_STREAM, 0)) < 0) {cout << "\n Socket creation error \n";
    return -1;}
	plaoaujbsdvcwd.sin_family = AF_INET;
	plaoaujbsdvcwd.sin_port = htons(FASDFDSA);  
	plaoaujbsdvcwd.sin_addr.s_addr = inet_addr(X.c_str());
	bind(vasnbdikkhu, (struct sockaddr *)&plaoaujbsdvcwd, sizeof(plaoaujbsdvcwd));
	return 0;
	}
int cnreiuabisvdbf::dasd(char* deedd) {if (inet_pton(AF_INET, deedd, &plaoaujbsdvcwd.sin_addr) <= 0) {
	  cout << "\nADDRFAIL\n";
	  return -1;}	return 0;}

	  cnreiuabisvdbf::cnreiuabisvdbf() {}
	  cnreiuabisvdbf::cnreiuabisvdbf(std::string X) 
	  {gdfgibyasd(X);}

	  char* cnreiuabisvdbf::FARFANNNNN() {return plpldadad;}

	int cnreiuabisvdbf::plolop(std::string Y) {
		struct sockaddr_in RAkfoadR;
		RAkfoadR.sin_family = AF_INET;
		//RAkfoadR.sin_addr.s_addr = inet_addr(Y.c_str());
		RAkfoadR.sin_port = htons(FASDFDSA);
		if (inet_pton(AF_INET, Y.c_str(), &RAkfoadR.sin_addr) <= 0) {
	  		cout << "\nADDRFAIL\n";
	  		return -1;}
		if ((connect(vasnbdikkhu, (struct sockaddr *)&RAkfoadR, sizeof(RAkfoadR))) < 0) 
		{cout << "\nConnection Failed \n";return -1;}return 0;}
		
		void cnreiuabisvdbf::rereradada() {read(vasnbdikkhu, plpldadad, 500);}
		void cnreiuabisvdbf::CSMDASDEFR(const char* numberXD) {send(vasnbdikkhu, numberXD, strlen(numberXD), 0);}
		void cnreiuabisvdbf::ECCFNALJKA() {close(vasnbdikkhu);}