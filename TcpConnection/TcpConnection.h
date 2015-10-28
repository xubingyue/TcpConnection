
#ifndef FoundationKit_TcpConnection_H
#define FoundationKit_TcpConnection_H

#pragma once

#include <string>
#include <memory>
#include <functional>

class TcpConnectionImpl;

class TcpConnection
{
public:

    typedef std::shared_ptr<TcpConnection>    Pointer;

    static Pointer create();
    static Pointer create(const std::string &heartbeat);


    virtual ~TcpConnection(void);

    /**
    * @brief Call this function to process network messages.
    */
    void update();

    /**
    * @brief Send message to server
    * @param[in] msg Want to send a message.
    */
    void write(const std::string &msg);

    /**
    * @brief Connect to server
    * @param[in] ip Server ip address like "192.168.10.26".
    * @param[in] port Server listening port for example 8080.
    */
    void connect(const std::string &ip, unsigned short port);

    /**
    * @brief Connect to server
    * @param[in] url Server url like "www.google.com".
    * @param[in] protocol Connection protocol like "http".
    */
    void connect(const std::string &url, const std::string &protocol);

    /**
    * @brief Close network connection, you can call connect function
    *        to reconnect.
    */
    void disconnect();

    /**
    * @brief Check whether the network connection.
    */
    bool isConnected();

    /**
    * @brief Get message end marker.
    * @return  The message end marker string.
    */
    std::string getDelimiter();

    /**
    * @brief Set message end marker.
    * @param[in] delimiter The message end marker string.
    */
    void setDelimiter(const std::string &delimiter);

    /**
    * @brief Set heart beat time out.
    * @param[out] timeOut Time value (second).
    */
    void setHeartBeatTimeOut(size_t timeOut);

    /**
    * @brief Set reconnect time out.
    * @param[in] timeOut Time value (second).
    */
    void setreconnectTimeOut(size_t timeOut);


public:
    std::function<void(const std::string& strAddress, unsigned short port)> ConnectedCallback;
    std::function<void(const std::string& strAddress, unsigned short port)> DisconnectedCallback;
    std::function<void(const std::string&)>				        	        MessageCallback;
    std::function<void(int errorCode, const std::string& strErrorMsg)>      ExceptionCallback;

protected:
    TcpConnection();
   /**
    * @brief Create a TcpClient with heartbeat string.
    * @param[in] heartbeat Heartbeat string.
    */
    explicit TcpConnection(const std::string &heartbeat);

    bool init();

private:
    TcpConnectionImpl *_mTcpConnectionImpl;
    std::string        _heartbeat;

};
#endif // FoundationKit_TcpConnection_H