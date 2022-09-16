#pragma once
#include <vector>
#include <SFML/Network.hpp>

struct Packet
{
	size_t size;
	void* data;
};

const size_t MAX_PACKET_SIZE = 512;

class Sender
{
public:
	Sender() = default;
	virtual ~Sender() = default;
	
	virtual void Send(Packet& packet) = 0;
};

class ServerEventHandler
{
public:
	ServerEventHandler() = default;
	virtual ~ServerEventHandler() = default;

	virtual void HandleNewConnection(Sender& newClient) = 0;
	virtual void ClientHasBeenDisconected() = 0;
};

class Server final
{
public:
	Server(unsigned short port, ServerEventHandler* handler);
	~Server();
	
	void Listen();
	void StopListen();
	
	std::vector<std::string> ipAddreses();
private:	
	unsigned short m_port;
	bool m_allowedToListen;
	bool m_threadIsAlive;
	
	ServerEventHandler* m_handler;
	sf::TcpListener m_tcpListener;
	std::vector<sf::TcpSocket*> m_clients;
	sf::SocketSelector m_selector;
	
	void _Listen();
	void _HandleNewConnection();
	void _HandleConnections();
	void _HandleDisConnection(size_t clientIndex);
	void _Broadcast(char* message, size_t messageSize);	
};

class ClientEventHandler
{
public:
	ClientEventHandler() = default;
	virtual ~ClientEventHandler() = default;
	
	virtual void PacketReceiver(Packet& packet) = 0;
	virtual void OnError(const std::string& message) = 0;
};



class Client final: public Sender
{
public:
	Client(ClientEventHandler* clientEventHandler);
	~Client();
	
	bool Connect(const std::string& ipAddres, unsigned short port);
	void DisConnect();

	void Send(Packet& packet) override;
	
	void Listen();
	void StopListen();

private:
	bool m_allowedToListen;
	bool m_threadIsAlive;

	ClientEventHandler* m_clientEventHandler;
	sf::TcpSocket m_tcpSocket;

	void _Listen();
};