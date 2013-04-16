/*! 
@file epAsyncTcpSocket.h
@author Woong Gyu La a.k.a Chris. <juhgiyo@gmail.com>
		<http://github.com/juhgiyo/epserverengine>
@date February 13, 2012
@brief Asynchronous TCP Socket Interface
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

An Interface for Asynchronous TCP Socket.

*/
#ifndef __EP_ASYNC_TCP_SOCKET_H__
#define __EP_ASYNC_TCP_SOCKET_H__

#include "epServerEngine.h"
#include "epBaseTcpSocket.h"

namespace epse
{

	/*! 
	@class AsyncTcpSocket epAsyncTcpSocket.h
	@brief A class for Asynchronous TCP Socket.
	*/
	class EP_SERVER_ENGINE AsyncTcpSocket:public BaseTcpSocket
	{
	public:
		/*!
		Default Constructor

		Initializes the Socket
		@param[in] callBackObj the callback object
		@param[in] isAsynchronousReceive the flag for Asynchronous Receive
		@param[in] waitTimeMilliSec wait time for Socket Thread to terminate
		@param[in] maximumProcessorCount the maximum number of processor
		@param[in] lockPolicyType The lock policy
		*/
		AsyncTcpSocket(ServerCallbackInterface *callBackObj,bool isAsynchronousReceive=true,unsigned int waitTimeMilliSec=WAITTIME_INIFINITE,unsigned int maximumProcessorCount=PROCESSOR_LIMIT_INFINITE,epl::LockPolicy lockPolicyType=epl::EP_LOCK_POLICY);

		/*!
		Default Destructor

		Destroy the Socket
		*/
		virtual ~AsyncTcpSocket();

		/*!
		Kill the connection
		*/
		virtual void KillConnection();
		
		/*!
		Set the Maximum Processor Count for the Socket.
		@param[in] maxProcessorCount The Maximum Processor Count to set.
		@remark 0 means there is no limit
		*/
		virtual void SetMaximumProcessorCount(unsigned int maxProcessorCount);

		/*!
		Get the Maximum Processor Count of the Socket
		@return The Maximum Processor Count
		@remark 0 means there is no limit
		*/
		virtual unsigned int GetMaximumProcessorCount() const;

		/*!
		Get the asynchronous receive flag for the Socket.
		@return The flag whether to receive asynchronously.
		*/
		virtual bool GetIsAsynchronousReceive() const;

		/*!
		Set the asynchronous receive flag for the Socket.
		@param[in] isASynchronousReceive The flag whether to receive asynchronously.
		*/
		virtual void SetIsAsynchronousReceive(bool isASynchronousReceive);

		/*!
		Set the wait time for the thread termination
		@param[in] milliSec the time for waiting in millisecond
		*/
		virtual void SetWaitTime(unsigned int milliSec);

	private:	
		friend class AsyncTcpServer;
	
		/*!
		Actually Kill the connection
		*/
		virtual void killConnection();

		/*!
		thread loop function
		*/
		virtual void execute();

		
	private:
		/*!
		Default Copy Constructor

		Initializes the Socket
		@param[in] b the second object
		@remark Copy Constructor prohibited
		*/
		AsyncTcpSocket(const AsyncTcpSocket& b):BaseTcpSocket(b)
		{}

		/*!
		Assignment operator overloading
		@param[in] b the second object
		@return the new copied object
		@remark Copy Operator prohibited
		*/
		AsyncTcpSocket & operator=(const AsyncTcpSocket&b){return *this;}
	
	
	private:

		/// processor thread list
		ServerObjectList m_processorList;

		/// Maximum Processor Count
		unsigned int m_maxProcessorCount;

		/// Flag for Asynchronous Receive
		bool m_isAsynchronousReceive;

	};

}

#endif //__EP_ASYNC_TCP_SOCKET_H__