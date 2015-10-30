
/****************************************************************************
 Copyright (c) 2013 libo

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/


#ifndef FoundationKit_TcpConnectionImpl_H
#define FoundationKit_TcpConnectionImpl_H

#ifdef WIN32
    #include <sdkddkver.h>
#endif

#include <string>
#include <iostream>
#include <deque>
#include <boost/asio.hpp>
#include <boost/function.hpp>


class TcpConnectionImpl
{
public:
    TcpConnectionImpl();

    /**
     * @brief Create a TcpClient with heartbeat string.
     * @param[in] heartbeat Heartbeat string.
     */
    explicit TcpConnectionImpl(const std::string &heartbeat);
    virtual ~TcpConnectionImpl(void);
    
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
     * @brief Connect to server
     * @param[in] endpoint .
     */
	void connect(boost::asio::ip::tcp::endpoint& endpoint);

    /**
     * @brief Close network connection, you can call connect function
     *        to reconnect.
     */
	void disconnect();

    /**
     * @brief Check whether the network connection.
     */
	bool isConnected(){ return m_isConnected; };
	
    /**
     * @brief Get message end marker.
     * @return  The message end marker string. 
     */
	std::string getDelimiter(){ return m_delimiter; };

    /**
     * @brief Set message end marker.
     * @param[in] delimiter The message end marker string. 
     */
	void setDelimiter(const std::string &delimiter){ m_delimiter = delimiter; };

    /**
     * @brief Set heart beat time out.
     * @param[out] timeOut Time value (second).
     */
    void setHeartBeatTimeOut(size_t timeOut){m_heartBeatTimeOut = timeOut; };

    /**
     * @brief Set reconnect time out.
     * @param[in] timeOut Time value (second).
     */
    void setreconnectTimeOut(size_t timeOut){m_reconnectTimeOut = timeOut; };
public:

    /**
     * @brief Callback when the network connected, Disconnected and have message.
     */
	boost::function<void(const boost::asio::ip::tcp::endpoint&)>	ConnectedCallback;
    boost::function<void(const boost::asio::ip::tcp::endpoint&)>	DisconnectedCallback;
    boost::function<void(const std::string&)>				   	    MessageCallback;
    boost::function<void(const boost::system::error_code&)>         ExceptionCallback;

protected:
	void read();
	void close();

	// callbacks
	void handle_connect(const boost::system::error_code& error);
	void handle_read(const boost::system::error_code& error);
	void handle_write(const boost::system::error_code& error);

	void do_write(const std::string &msg);
	void do_close();
	void do_reconnect(const boost::system::error_code& error);
	void do_heartbeat(const boost::system::error_code& error);

    void restartHeartbeatTimer();
    void restartReconnectTimer();


    

protected:
	bool                            m_isConnected;
	bool                            m_isClosing;

	boost::asio::ip::tcp::endpoint  m_endPoint;

	boost::asio::io_service         m_ioServer;
	boost::asio::ip::tcp::socket    m_socket;

	boost::asio::streambuf          m_buffer;

	//! to be written to server
	std::deque<std::string>         m_messages;

	boost::asio::deadline_timer     m_heartBeatTimer;
	boost::asio::deadline_timer     m_reconnectTimer;

	std::string                     m_delimiter;
	std::string                     m_heartBeat;

    size_t                          m_heartBeatTimeOut;
    size_t                          m_reconnectTimeOut;
};
#endif // FoundationKit_TcpConnectionImpl_H



