/*! 
@file epAsyncTcpClient.h
@author Woong Gyu La a.k.a Chris. <juhgiyo@gmail.com>
		<http://github.com/juhgiyo/epserverengine>
@date February 13, 2012
@brief Asynchronous TCP Client Interface
@version 1.0

@section LICENSE

Copyright (C) 2012  Woong Gyu La <juhgiyo@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

@section DESCRIPTION

An Interface for Asynchronous TCP Client.

*/
#ifndef __EP_ASYNC_TCP_CLIENT_H__
#define __EP_ASYNC_TCP_CLIENT_H__

#include "epServerEngine.h"
#include "epPacket.h"
#include "epBaseServerObject.h"
#include "epServerConf.h"
#include "epClientInterfaces.h"
#include "epServerObjectList.h"
#include "epClientPacketProcessor.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif //WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>



// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")



using namespace std;


namespace epse{

	/*! 
	@class BaseClient epBaseClient.h
	@brief A class for Base Client.
	*/
	class EP_SERVER_ENGINE AsyncTcpClient:public BaseServerObject, public ClientInterface{
	public:
		/*!
		Default Constructor

		Initializes the Client
		@param[in] hostName the hostname string
		@param[in] port the port string
		@param[in] syncPolicy Synchronous Policy
		@param[in] maximumParserCount the maximum number of parser
		@param[in] waitTimeMilliSec wait time for Client Thread to terminate
		@param[in] lockPolicyType The lock policy
		*/
		AsyncTcpClient(ClientCallbackInterface *callBackObj,const TCHAR * hostName=_T(DEFAULT_HOSTNAME), const TCHAR * port=_T(DEFAULT_PORT),bool isAsynchronousReceive=true,unsigned int waitTimeMilliSec=WAITTIME_INIFINITE,unsigned int maximumProcessorCount=PROCESSOR_LIMIT_INFINITE,epl::LockPolicy lockPolicyType=epl::EP_LOCK_POLICY);

		/*!
		Default Copy Constructor

		Initializes the BaseClient
		@param[in] b the second object
		*/
		AsyncTcpClient(const AsyncTcpClient& b);
		/*!
		Default Destructor

		Destroy the Client
		*/
		virtual ~AsyncTcpClient();

		/*!
		Assignment operator overloading
		@param[in] b the second object
		@return the new copied object
		*/
		AsyncTcpClient & operator=(const AsyncTcpClient&b);
	

		/*!
		Set the hostname for the server.
		@remark Cannot be changed while connected to server
		@param[in] hostName The hostname to set.
		*/
		void SetHostName(const TCHAR * hostName);

		/*!
		Set the port for the server.
		@remark Cannot be changed while connected to server
		@param[in] port The port to set.
		*/
		void SetPort(const TCHAR * port);

		/*!
		Get the hostname of server
		@return the hostname in string
		*/
		epl::EpTString GetHostName() const;

		/*!
		Get the port number of server
		@return the port number in string
		*/
		epl::EpTString GetPort() const;

		/*!
		Set the Maximum Processor Count for the server.
		@param[in] maxProcessorCount The Maximum Processor Count to set.
		@remark 0 means there is no limit
		*/
		void SetMaximumProcessorCount(unsigned int maxProcessorCount);

		/*!
		Get the Maximum Parser Parser of server
		@return The Maximum Connection Count
		@remark 0 means there is no limit
		*/
		unsigned int GetMaximumProcessorCount() const;


		/*!
		Set the wait time for the thread termination
		@param[in] milliSec the time for waiting in millisecond
		*/
		virtual void SetWaitTime(unsigned int milliSec);

		/*!
		Connect to the server
		@param[in] hostName the hostname string
		@param[in] port the port string
		@remark if argument is NULL then previously setting value is used
		*/
		bool Connect(const TCHAR * hostName=NULL, const TCHAR * port=NULL);

		/*!
		Disconnect from the server
		*/
		void Disconnect();

		/*!
		Check if the connection is established
		@return true if the connection is established otherwise false
		*/
		bool IsConnected() const;

		/*!
		Send the packet to the server
		@param[in] packet the packet to be sent
		@param[in] waitTimeInMilliSec wait time for sending the packet in millisecond
		@return sent byte size
		@remark return -1 if error occurred
		*/
		virtual int Send(const Packet &packet, unsigned int waitTimeInMilliSec=WAITTIME_INIFINITE);

		/*!
		Set the Callback Object for the server.
		@param[in] callBackObj The Callback Object to set.
		*/
		virtual void SetCallbackObject(ClientCallbackInterface *callBackObj);

		/*!
		Get the Callback Object of server
		@return the current Callback Object
		*/
		virtual ClientCallbackInterface *GetCallbackObject();

	
		/*!
		Get the asynchronous receive flag for the Socket.
		@return The flag whether to receive asynchronously.
		@remark for Asynchronous Socket Use Only!
		*/
		virtual bool GetIsAsynchronousReceive() const;
		

		/*!
		Set the asynchronous receive flag for the Socket.
		@param[in] isASynchronousReceive The flag whether to receive asynchronously.
		@remark for Asynchronous Socket Use Only!
		*/
		virtual void SetIsAsynchronousReceive(bool isASynchronousReceive);

	private:

		/*!
		Reset Client
		*/
		void resetClient();
		/*!
		Actually set the hostname for the server.
		@remark Cannot be changed while connected to server
		@param[in] hostName The hostname to set.
		*/
		void setHostName(const TCHAR * hostName);
		
		/*!
		Actually set the port for the server.
		@remark Cannot be changed while connected to server
		@param[in] port The port to set.
		*/
		void setPort(const TCHAR *port);

		/*!
		Receive the packet from the server
		@param[out] packet the packet received
		@return received byte size
		*/
		int receive(Packet &packet);

		/*!
		Actually processing the client thread
		*/
		virtual void execute();


		/*!
		Clean up the client initialization.
		*/
		void cleanUpClient();

		/*!
		Actually Disconnect from the server
		*/
		void disconnect();


	private:
		/// port
		epl::EpString m_port;
		/// hostname
		epl::EpString m_hostName;
		/// connection socket
		SOCKET m_connectSocket;
		/// internal variable
		struct addrinfo *m_result;
	
		/// send lock
		epl::BaseLock *m_sendLock;
		/// general lock
		epl::BaseLock *m_generalLock;

		/// Lock Policy
		epl::LockPolicy m_lockPolicy;

		/// Temp Packet;
		Packet m_recvSizePacket;

		/// Parser list
		ServerObjectList m_processorList;

		/// Maximum Processor Count
		unsigned int m_maxProcessorCount;

		/// Callback Object
		ClientCallbackInterface *m_callBackObj;

		/// Flag for Asynchronous Receive
		bool m_isAsynchronousReceive;

	};
}


#endif //__EP_ASYNC_TCP_CLIENT_H__