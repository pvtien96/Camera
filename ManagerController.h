// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#pragma comment(lib, "ws2_32.lib")

#include <winsock2.h>
#include <ws2tcpip.h>

#define _WINSOCKAPI_
#include <windows.h>
#include <string>
#include "BaseMessage.h"
#include "constant.h"
#include "ByteBuffer.h"

/**
*
*/	
class ManagerController
{
public:
	ManagerController();
	~ManagerController();

	void DestroyThis();

	static ManagerController *getInstance();

	void initSocket(int portSend, int portReceive, std::string ipSend);
	MSG_RETURN initUdpSendSocket(int portSend, std::string ipSend);
	MSG_RETURN initUdpReceiveSocket(int portReceive);

	void doReceivedUdpData(SOCKET socket);
	void doSendUdpData(SOCKET socket);
	void parseMessage(std::string *buffer);
	int sendMessage(BaseMessage *message);

private:
	static ManagerController *instance;

	DWORD dwInitSocketThreadId;
	HANDLE hInitSocketThread;

	// Udp
	struct sockaddr_in si_drivingUDP;
	int si_drivingUDP_len;
	SOCKET sendUdpSocket, listenUdpSocket;
	DWORD dwSendUdpThreadId;
	DWORD dwReceivedUdpThreadId;
	HANDLE hReceivedUdpThread;
	HANDLE hSendUdpThread;

	HANDLE mManagerMutex;
	ByteBuffer *sendManagerBuffer;

	DWORD dwSendManagerThreadId;
	HANDLE hSendManagerThread;

	DWORD dwReceiveSimulationThreadId;
	HANDLE hReceiveSimulationThread;

	bool managerConnected;
};
