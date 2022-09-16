#include "Network.h"
#include <string>
#include <thread>

#include <Windows.h>

Client::Client(ClientEventHandler* clientEventHandler) :
	m_clientEventHandler(clientEventHandler) {}

Client::~Client()
{
	StopListen();
}

bool Client::Connect(const std::string & ipAddres, unsigned short port)
{
	sf::Socket::Status status = m_tcpSocket.connect(ipAddres, port);
	if (status != sf::Socket::Done)
	{
		return false;
	}
	return true;
}

void Client::DisConnect()
{
	m_tcpSocket.disconnect();
}

void Client::Send(Packet& packet)
{
	m_tcpSocket.send(packet.data,packet.size);
}

void Client::Listen()
{
	m_allowedToListen = true;
	m_threadIsAlive = true;
	std::thread Listener(&Client::_Listen, this);
	Listener.detach();
}

void Client::StopListen()
{
	m_allowedToListen = false;
	while (m_threadIsAlive)
	{
		Sleep(100);
	}
}

void Client::_Listen()
{
	while (m_allowedToListen&&m_threadIsAlive)
	{
		char buf[MAX_PACKET_SIZE];
		size_t receivedSize;
		
		if (m_tcpSocket.receive(buf, MAX_PACKET_SIZE, receivedSize) != sf::Socket::Done)
		{
			m_clientEventHandler->OnError("something Bad");
			break;
		}
		Packet receivedPacket;
		receivedPacket.size = receivedSize;
		receivedPacket.data = buf;
		m_clientEventHandler->PacketReceiver(receivedPacket);
	}
	m_threadIsAlive = false;
}
