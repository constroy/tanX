#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>

#define MAX_NUM_CLTS 8

int num;
int sock;
int buf[2];
sockaddr_in si_srv,si_oth;
unsigned buf_size=sizeof buf,len=sizeof si_oth;
sockaddr_in clts[MAX_NUM_CLTS];

void fail(const char s[])
{
    puts(s);
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
	for (int i=0;i<num;++i)
	{
		if (recvfrom(sock,buf,buf_size,0,(sockaddr *)&si_oth,&len)==-1)
        {
            fail("recvfrom");
        }
        if (buf[0]==0)
        {
			clts[i]=si_oth;
			printf("Clients connected %d/%d\n",i,num);
		}
	}
	puts("Starting the game...");

	for (int i=0;i<num;++i)
	{
		buf[0]=i+1;
		buf[1]=num;
		sendto(sock,buf,buf_size,0,(sockaddr *)(clts+i),len);
	}

	for (;;)
	{
		if (recvfrom(sock,buf,buf_size,0,(sockaddr *)&si_oth,&len)==buf_size)
		{
			for (int i=0;i<num;++i)
				sendto(sock,buf,buf_size,0,(sockaddr *)(clts+i),len);
		}
	}
	return 0;
}
