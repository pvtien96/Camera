// Fill out your copyright notice in the Description page of Project Settings.

#include "ManagerController.h"

#include <iostream>
#include <exception>
#include <vector>

#include "BaseMessage.h"
#include "ByteBuffer.h"
#include "MessageFactory.h"
#include "BaseHandler.h"
#include "HandleFactory.h"
#include "QDebug"

//DEFINE_LOG_CATEGORY_STATIC(LogInfo, Log, All);

ManagerController *ManagerController::instance = nullptr;

DWORD WINAPI ioReceivedUdpData(LPVOID lpParam);
DWORD WINAPI ioSendUdpData(LPVOID lpParam);

DWORD WINAPI ioReceivedUdpData(LPVOID lpParam)
{
	SOCKET* receivedsocket = (SOCKET*)lpParam;
	ManagerController::getInstance()->doReceivedUdpData(*receivedsocket);
	return 0;
}

DWORD WINAPI ioSendUdpData(LPVOID lpParam)
{
	SOCKET* sendsocket = (SOCKET*)lpParam;
	ManagerController::getInstance()->doSendUdpData(*sendsocket);
	return 0;
}

ManagerController::ManagerController()
{
	sendManagerBuffer = new ByteBuffer();
	mManagerMutex = CreateMutex(nullptr, 0, nullptr);

	managerConnected = false;

	dwInitSocketThreadId = 0;
	hInitSocketThread = 0;
	si_drivingUDP_len = 0;
	sendUdpSocket = 0;
	listenUdpSocket = 0;
	dwSendUdpThreadId = 0;
	dwReceivedUdpThreadId = 0;
	hReceivedUdpThread = 0;
	hSendUdpThread = 0;
	dwSendManagerThreadId = 0;
	hSendManagerThread = 0;
	dwReceiveSimulationThreadId = 0;
	hReceiveSimulationThread = 0;
}

ManagerController::~ManagerController()
{
	// Terminate device threads
	TerminateThread(hSendUdpThread, 0);
	TerminateThread(hInitSocketThread, 0);
	TerminateThread(hReceivedUdpThread, 0);

	CloseHandle(hSendUdpThread);
	CloseHandle(hInitSocketThread);
	CloseHandle(hReceivedUdpThread);

	// Close device socket
	closesocket(sendUdpSocket);
	closesocket(listenUdpSocket);

	// WSA cleanup
	WSACleanup();

}

void ManagerController::DestroyThis()
{
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}

ManagerController * ManagerController::getInstance()
{
	if (instance == nullptr)
		instance = new ManagerController();
	return instance;
}

void ManagerController::initSocket(int portSend, int portReceive, std::string ipSend)
{
	int iResult;
	WSADATA wsaData;
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0)
	{
	}
	initUdpSendSocket(portSend, ipSend);
	initUdpReceiveSocket(portReceive);
}

MSG_RETURN ManagerController::initUdpSendSocket(int portSend, std::string ipSend)
{
	si_drivingUDP_len = sizeof(si_drivingUDP);
	sendUdpSocket = INVALID_SOCKET;
	sendUdpSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sendUdpSocket == INVALID_SOCKET)
	{
	}

	memset((char *)&si_drivingUDP, 0, sizeof(si_drivingUDP));
	si_drivingUDP.sin_family = AF_INET;
	si_drivingUDP.sin_port = htons((u_short)portSend);
	si_drivingUDP.sin_addr.S_un.S_addr = inet_addr(ipSend.c_str());

	/************************************************************************/
	/* Create thread for sending to driver                                  */
	/************************************************************************/
	hSendUdpThread = CreateThread(NULL, 0, ioSendUdpData, &sendUdpSocket, 0, &dwSendManagerThreadId);
	if (hSendUdpThread == NULL)
	{
		return MSG_RETURN::FAIL;
	}
	managerConnected = true;

	return MSG_RETURN::SUCCESS;
}

MSG_RETURN ManagerController::initUdpReceiveSocket(int portReceive)
{
	/************************************************************************/
	/* Init socket for received				                                */
	/************************************************************************/
	struct sockaddr_in receiveAddress;
	listenUdpSocket = INVALID_SOCKET;
	listenUdpSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (listenUdpSocket == INVALID_SOCKET)
	{
		return MSG_RETURN::FAIL;
	}

	receiveAddress.sin_family = AF_INET;
	receiveAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	receiveAddress.sin_port = htons((u_short)portReceive);
	if (::bind(listenUdpSocket, (struct sockaddr *)&receiveAddress, sizeof(receiveAddress)) != 0)
	{
		return MSG_RETURN::FAIL;
	}

	/************************************************************************/
	/* Create thread for receiving                                          */
	/************************************************************************/
	hReceivedUdpThread = CreateThread(nullptr, 0, ioReceivedUdpData, &listenUdpSocket, 0, &dwReceivedUdpThreadId);
	if (hReceivedUdpThread == nullptr)
	{
		return MSG_RETURN::FAIL;
	}
	return MSG_RETURN::SUCCESS;
}

void ManagerController::doReceivedUdpData(SOCKET socket)
{
	char recvbuf[DEFAULT_BUFLEN];
	int recvbuflen = DEFAULT_BUFLEN;
	std::string *buffer = new std::string();

	while (true)
	{
		memset(recvbuf, 0, DEFAULT_BUFLEN);
		recvbuflen = recv(socket, recvbuf, DEFAULT_BUFLEN, 0);
		if (recvbuflen > 0)
		{
			buffer->append(recvbuf, recvbuflen);
			this->parseMessage(buffer);
		}
		else if (recvbuflen == 0) // Terminate receive thread
		{
			/*closesocket(socket);
			TerminateThread(hReceivedUdpThread, 0);
			CloseHandle(hReceivedUdpThread);
			break;*/
		}
		else // Socket error
		{
			/*closesocket(socket);
			TerminateThread(hReceivedUdpThread, 0);
			CloseHandle(hReceivedUdpThread);
			break;*/
		}
		Sleep(50);
	}

	buffer->clear();
	delete buffer;
}

void ManagerController::doSendUdpData(SOCKET socket)
{
	DWORD wait_result;
	int send_len;
	unsigned int bufferlen;
	while (true)
	{
		wait_result = WaitForSingleObject(mManagerMutex, INFINITE);
		switch (wait_result)
		{
		case WAIT_OBJECT_0:
			bufferlen = sendManagerBuffer->Length();
			if (bufferlen <= 0)
				break;
			else
			{
				send_len = sendto(socket, sendManagerBuffer->Data(), bufferlen, 0, (struct sockaddr *)&si_drivingUDP, si_drivingUDP_len);
				if (send_len != SOCKET_ERROR)
					sendManagerBuffer->Shift(send_len);
				else
				{
					//UE_LOG(LogTemp, Warning, TEXT("Send upd message from manager error: %d"), WSAGetLastError());
				}
			}
			break;
		case WAIT_ABANDONED:
			break;
		default:
			break;
		}
		ReleaseMutex(mManagerMutex);
		Sleep(10);
	}
}

void ManagerController::parseMessage(std::string *buffer)
{
	const char *data = buffer->c_str();
	int length = buffer->length();
	ByteBuffer byteBuffer(data, length);

	while (true)
	{
		if (byteBuffer.Length() < 3)
			break;

		uint16 messlen = 0;
		uint16 networkmesslen = 0;
		byteBuffer.PeekUInt16(networkmesslen);
		messlen = ntohs(networkmesslen);
		if (messlen <= 0)
		{
			buffer->clear();
			return;
		}

		if (byteBuffer.Length() < messlen)
			break;

		char *messdata = new char[messlen];
		byteBuffer.ReadBytes(messdata, messlen);

		uint8 messtype = 0;
		memcpy_s((char*)&messtype, 1, messdata + 2, 1);
		BaseMessage *message = MessageFactory::getInstance()->createMessage(messtype);
		if (message == NULL)
		{
			buffer->clear();
			delete[] messdata;
			messdata = NULL;
			return;
		}
		message->setLeng(messlen);
		message->setType(messtype);
		if (message->parseFromData(messdata + 3, messlen - 3) == MSG_RETURN::FAIL)
		{
			buffer->clear();
			delete[] messdata;
			messdata = NULL;
			return;
		}

		BaseHandler *handler = HandleFactory::getInstance()->createHandler(messtype);
		if (handler != NULL)
		{
			handler->setMessage(message);
            handler->handle();
		}

		delete[] messdata;
		messdata = NULL;
	}

	int pos = length - byteBuffer.Length();
	if (pos > 0)
		buffer->erase(buffer->begin(), buffer->begin() + pos);
}

int ManagerController::sendMessage(BaseMessage *message)
{
	if (!managerConnected)
		return MSG_RETURN::FAIL;

	uint16 mesLen = message->getLeng();
	uint8_t mesType = message->getType();
	char *mesData = new char[mesLen];
	memset(mesData, 0, mesLen);

	uint16_t nlength = htons(message->getLeng());
    memcpy_s(mesData, mesLen, (char *)&nlength, 2);
    memcpy_s(mesData + 2, mesLen - 2, (char *)&mesType, 1);
    message->serialToData(mesData + 3, mesLen - 3);

	DWORD waitResult;
	int ret = MSG_RETURN::SUCCESS;

	waitResult = WaitForSingleObject(mManagerMutex, INFINITE);
	switch (waitResult)
	{
	case WAIT_OBJECT_0:
		sendManagerBuffer->WriteBytes(mesData, mesLen);
		ret = mesLen;
		break;
	case WAIT_ABANDONED:
		ret = MSG_RETURN::FAIL;
		break;
	default:
		ret = MSG_RETURN::FAIL;
		break;
	}
	ReleaseMutex(mManagerMutex);
	delete[] mesData;

	return ret;
}
