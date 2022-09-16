#pragma once
#include "Network.h"
#include <SFML/Network.hpp>

class TcpSender final: public Sender
{
public:
	TcpSender(sf::TcpSocket* tcpSocket);
	virtual ~TcpSender() = default;
	
	void Send(Packet & packet) override;
private:
	sf::TcpSocket* m_tcpSocket;
};

