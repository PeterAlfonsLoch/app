/**
* \brief	Platform independent waitables
*/
#pragma once


class mutex;
class event;


/////////////////////////////////////////////////////////////////////////////
// Basic synchronization object

/** templatization of sync_object inspired my class
    Mutex from C++ Sockets Library \file Mutex.h
 **   \date  2004-10-30
 **   \author grymse@alhem.net
**/
/** waitable renamed to waitable
Thank you Thomas Hoefer!!

/// This class represents an item which can be waited for. Items can be threads, events, sockets,
/// files, semaphores and so on.
class CLASS_DECL_AXIS waitable :
   virtual public ::object
{
public:
	///  \brief		destructor
	virtual ~waitable();

	///  \brief		abstract function to initialize a waiting action without a timeout
	virtual void wait();

	///  \brief		abstract function to initialize a waiting action with a timeout
	///  \param		duration time period to wait for item
	///  \return	waiting action result as wait_result
	virtual wait_result wait(const duration & duration ) = 0;
};
*/

class CLASS_DECL_AXIS waitable :
   virtual public request_interface
{
public:


   mutex          *  m_pmutex;


   waitable();
   waitable(const waitable & objectSrc);
   virtual ~waitable();


   virtual void * get_os_data() const;


   virtual void lock();
   virtual bool lock(const duration & durationTimeout);
   virtual bool unlock();
   virtual bool unlock(LONG lCount, LPLONG lpPrevCount = NULL);


	///  \brief		abstract function to initialize a waiting action without a timeout
	virtual void wait();

	///  \brief		*no more as of 2012-05-12* abstract function to initialize a waiting action with a timeout
	///  \param		duration time period to wait for item
	///  \return	waiting action result as wait_result
	virtual wait_result wait(const duration & duration);


	virtual bool is_locked() const;


};



///  \brief		pauses waitable for specified time
///  \param		duration sleeping time of waitable
CLASS_DECL_AXIS void sleep(const duration & duration);


// forward declaration
class event_base;


/// This class represents a virtual interface for a callback method for WaitableItems in a
/// event_collection.


class CLASS_DECL_AXIS waitable_callback
{
public:
	virtual ~waitable_callback();

	/// called on signalization of a event_base
	/// \param signaling event_base
	virtual void callback(const event_base& waitItem) = 0;
};



namespace base
{


   // platform abstraction layer
   namespace pal
   {


      typedef ::waitable WaitableItem;


   } // namespace pal - platform abstraction layer


} // namespace base




