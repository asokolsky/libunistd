// portable/BsdPacketServer.cpp
// Created by Robin Rowe on 2016/06/24
// License MIT Open Source

#include "BsdPacketServer.h"
#include "Logger.h"

namespace portable 
{
	
bool BsdPacketServer::Start(int serverPort,unsigned maxStreams)
{	const bool isReceive=false;
	if(!Open(serverPort,maxStreams,isReceive))
	{	return false;
	}
	const bool isBlocking=true;
	isVerbose = false;//true; //bug - should pass in as param
	BsdSocketServer::Start();
	return true;
}

void BsdPacketServer::LogSocketError(const BsdSocket& bsdSocket)
{	std::string msg;
	bsdSocket.GetPeerName(msg);
	msg+=" SendTo error: ";
	msg+=bsdSocket.errorMsg;
	LogMsg(msg);
}

bool BsdPacketServer::Login(SOCKET* slot,SOCKET fd) 
{	if(!slot)
	{	puts("No slot");
		return false;
	}
	for(unsigned i=0;i<pool.socketfd.size();i++)
	{	if(IsInvalid(pool.socketfd[i]))
		{	if(!SendHeaderPacket(fd))
			{	return false;
			}
			pool.socketfd[i]=fd;
			std::string msg;
			BsdSocket bsdSocket(fd);
			bsdSocket.GetPeerName(msg);
			msg+=" Connected";
			LogMsg(msg);
			return true;
	}	}
	LogMsg("Can't subscribe");
	return false;
}

}
