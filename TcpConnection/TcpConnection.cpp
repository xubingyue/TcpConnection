
#include "TcpConnection.h"
#include "impl/TcpConnectionImpl.h"

TcpConnection::TcpConnection()
    :_heartbeat("PING")
{

}

TcpConnection::TcpConnection(const std::string &heartbeat)
    :_heartbeat(heartbeat)
{

}

TcpConnection::~TcpConnection(void)
{
    if (_mTcpConnectionImpl)
    {
        delete _mTcpConnectionImpl;
        _mTcpConnectionImpl = nullptr;
    }
}

TcpConnection::Pointer TcpConnection::create()
{
    return create("PING");
}

TcpConnection::Pointer TcpConnection::create(const std::string &heartbeat)
{
    auto pTcpConnection = new TcpConnection(heartbeat);
    if (pTcpConnection && pTcpConnection->init())
    {
        return TcpConnection::Pointer(pTcpConnection);
    }
    return nullptr;
}

bool TcpConnection::init()
{
    _mTcpConnectionImpl = new TcpConnectionImpl(_heartbeat);
    if (_mTcpConnectionImpl)
    {
        _mTcpConnectionImpl->ConnectedCallback = [&](const boost::asio::ip::tcp::endpoint& ep)
        {
            if (this->ConnectedCallback)
                this->ConnectedCallback(ep.address().to_string(), ep.port());
        };
        _mTcpConnectionImpl->DisconnectedCallback = [&](const boost::asio::ip::tcp::endpoint& ep)
        {
            if (this->DisconnectedCallback)
                this->DisconnectedCallback(ep.address().to_string(), ep.port());
        };

        _mTcpConnectionImpl->MessageCallback = [&](const std::string& msg)
        {
            if (this->MessageCallback)
                this->MessageCallback(msg);
        };
        _mTcpConnectionImpl->ExceptionCallback = [&](const boost::system::error_code& errCode)
        {
            if (this->ExceptionCallback)
                this->ExceptionCallback(errCode.value(), errCode.message());
        };
        return true;
    }

    return false;
}

void TcpConnection::update()
{
    _mTcpConnectionImpl->update();
}

void TcpConnection::write(const std::string &msg)
{
    _mTcpConnectionImpl->write(msg);
}

void TcpConnection::connect(const std::string &ip, unsigned short port)
{
    _mTcpConnectionImpl->connect(ip, port);
}

void TcpConnection::connect(const std::string &url, const std::string &protocol)
{
    _mTcpConnectionImpl->connect(url, protocol);
}

void TcpConnection::disconnect()
{
    _mTcpConnectionImpl->disconnect();
}

bool TcpConnection::isConnected()
{
    return _mTcpConnectionImpl->isConnected();
}

std::string TcpConnection::getDelimiter()
{
    return _mTcpConnectionImpl->getDelimiter();
}

void TcpConnection::setDelimiter(const std::string &delimiter)
{
    _mTcpConnectionImpl->setDelimiter(delimiter);
}

void TcpConnection::setHeartBeatTimeOut(size_t timeOut)
{
    _mTcpConnectionImpl->setHeartBeatTimeOut(timeOut);
}

void TcpConnection::setreconnectTimeOut(size_t timeOut)
{
    _mTcpConnectionImpl->setreconnectTimeOut(timeOut);
}

