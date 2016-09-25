#include "client.hxx"

#include <sys/socket.h>

#include <cstring>

Client::Client(const char ip[]) {
	sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	len = sizeof si_srv;
	memset(&si_srv, 0, len);
	si_srv.sin_family = AF_INET;
	si_srv.sin_port = htons(6666);
	inet_aton(ip, &si_srv.sin_addr);
}
void Client::Connect(int &id, int &num) {
	buf[0] = 0;
	buf[1] = 0;
	sendto(sock, buf, sizeof(buf), 0, (sockaddr *)&si_srv, len);
	recvfrom(sock, buf, sizeof(buf), 0, (sockaddr *)&si_srv, &len);
	id = buf[0];
	num = buf[1];
}
bool Client::Send(int id, int cmd) {
	buf[0] = id;
	buf[1] = cmd;
	return sendto(sock, buf, sizeof(buf), 0, (sockaddr *)&si_srv,
				  len) == sizeof(buf);
}
bool Client::Receive(int &id, int &cmd) {
	int t = recvfrom(sock, buf, sizeof(buf), MSG_DONTWAIT, (sockaddr *)&si_srv,
					 &len);
	if (t == sizeof buf) {
		id = buf[0];
		cmd = buf[1];
		return true;
	} else {
		return false;
	}
}
