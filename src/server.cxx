#include <cstdio>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <map>
#include <SDL/SDL.h>
#include "timer.hxx"

const int time_slot=40;

using std::map;
using std::pair;
using std::make_pair;

typedef pair<unsigned,int> Addr;

int id,num;
int sock;
int buf[2];
sockaddr_in si_srv,si_oth;
unsigned len=sizeof si_oth;
map<Addr,sockaddr_in> clts;

void fail(const char s[])
{
    perror(s);
    exit(-1);
}
int main(int argc,char *argv[])
{
	if (argc!=2)
	{
		fail("usage: lnX number_of_players");
	}
	num=atoi(argv[1]);
	if ((sock=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP))==-1)
    {
        fail("socket");
    }
    memset(&si_srv,0,len);
    si_srv.sin_family=AF_INET;
    si_srv.sin_port=htons(6666);
    si_srv.sin_addr.s_addr=htonl(INADDR_ANY);

    if (bind(sock,(sockaddr *)&si_srv,len)==-1)
    {
		fail("bind");
	}

	puts("Waiting for clients...");
	while ((int)clts.size()<num)
	{
		if (recvfrom(sock,buf,sizeof buf,0,(sockaddr *)&si_oth,&len)==-1)
        {
            fail("recvfrom");
        }
        if (buf[0]==0)
        {
			Addr addr=make_pair(inet_addr(inet_ntoa(si_oth.sin_addr)),si_oth.sin_port);
			clts[addr]=si_oth;
			printf("Clients connected %lu/%d\n",clts.size(),num);
		}
	}
	puts("Starting the game...");

	for (const auto &i:clts)
	{
		buf[0]=++id;
		buf[1]=clts.size();
		sendto(sock,buf,sizeof buf,0,(sockaddr *)&i.second,len);
	}

	Timer timer;
	for (;;)
	{
		timer.Start();
		int t=recvfrom(sock,buf,sizeof buf,MSG_DONTWAIT,(sockaddr *)(sockaddr *)&si_oth,&len);
		if (t==sizeof buf)
		{
			for (const auto &i:clts)
				sendto(sock,buf,sizeof buf,0,(sockaddr *)&i.second,len);
		}
		if (timer.GetTicks()<time_slot) SDL_Delay(time_slot-timer.GetTicks());
	}
	return 0;
}
