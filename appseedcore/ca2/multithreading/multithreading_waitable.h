/**
* \brief	Platform independent waitables
* \author	Thomas Hoefer
*/
// from sector8J on 2011-08-09
#pragma once




/// This class represents an item which can be waited for. Items can be threads, events, sockets,
/// files, semaphores and so on.
class CLASS_DECL_ca waitable :
   virtual public ::radix::object
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


///  \brief		pauses waitable for specified time
///  \param		duration sleeping time of waitable
CLASS_DECL_ca void sleep(const duration & duration);


// forward declaration
class event_base;


/// This class represents a virtual interface for a callback method for WaitableItems in a
/// event_collection.


class CLASS_DECL_ca waitable_callback
{
public:
	virtual ~waitable_callback();

	/// called on signalization of a event_base
	/// \param signaling event_base
	virtual void callback(const event_base& waitItem) = 0;
};



// generic
namespace gen
{


   // platform abstraction layer
   namespace pal
   {

      
      typedef ::waitable WaitableItem;


   } // namespace pal - platform abstraction layer


} // namespace gen - generic

