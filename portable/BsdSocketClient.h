// portable/BsdSocketClient.h
// Created by Robin Rowe on 11/27/2015
// Copyright (c) 2015 Robin.Rowe@CinePaint.org
// License open source MIT

#ifndef BsdSocketClient_h
#define BsdSocketClient_h

#include "BsdSocket.h"

namespace portable 
{
	
class BsdSocketClient
:	public BsdSocket
{	std::thread worker;
	const unsigned bufsize;
	static void Main(BsdSocketClient* self)
    {   self->Run();
    }
protected:
	void Run() override;
public:
	BsdSocketClient(unsigned bufsize)
	:	bufsize(bufsize)
	{}
	void Close()
	{	Stop();
		if(socketfd)
		{	closesocket(socketfd);
			socketfd=0;
	}	}
	bool Open(const char* serverName,int serverPort);
	void Start() override
	{	worker=std::thread(Main,this);
		worker.detach();
		puts("Started socket thread");
	}
};

}

#endif

