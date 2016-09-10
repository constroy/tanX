#ifndef _CLIENT_HXX
#define _CLIENT_HXX

#include <arpa/inet.h>

class Client {
public:
	Client(const char ip_addr[]);
	void Connect(int &id, int &num);
	bool Send(int id, int cmd);
	bool Receive(int &id, int &cmd);
private:
	int sock;
	int buf[2];
	unsigned len;
	sockaddr_in si_srv;
};

#endif
