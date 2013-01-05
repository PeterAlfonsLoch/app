/**
* \brief	Platform independent waitables
* \author	Thomas Hoefer
*/
// from sector8J on 2011-08-09
#pragma once




//namespace multithreading
//{

	/// constant representing infinite time
	//const boost::posix_time::time_duration InfiniteTime = boost::posix_time::time_duration(boost::date_time::pos_infin);
// use INFINITE

	/// constant representing zero time
	//const boost::posix_time::time_duration ZeroTime = boost::posix_time::time_duration();
// use 0

/// This class represents results of waiting actions.
class CLASS_DECL_ca wait_result
{
	/// Internal member holding the result of the last waiting action
	int32_t                        m_iWaitResult;

public:
	static const int32_t Abandon0	= -10;		/// waiting abandoned because thread stopped
	// place additional failure codes here
	static const int32_t Failure	= -3;		/// waiting failure
	static const int32_t BadThread	= -2;		/// thread not found?
	static const int32_t Timeout	= -1;		/// timeout occured
	static const int32_t Event0		=  0;		/// signaled

public:
//#if defined(WIN32) || defined(WIN64)
	///  \brief		constructor with result value and object count passed (Windows only)
	///  \param		value waiting result value as passed by Windows API function
	///  \param		objectCount number of items in event_collection
	explicit wait_result(uint32_t long value, count objectCount=1 );
//#endif
	///  \brief		constructor with result value passed
	///  \param		value waiting result value as passed by Windows API function
	explicit wait_result(int32_t value )
		: m_iWaitResult(value)
	{}

	///  \brief		default constructor
	wait_result()
		: m_iWaitResult(Failure)
	{}

	///  \brief		checks if last result == Abandon0
	///  \return	true if last result == Abandon0
	bool abandoned() const
	{ return m_iWaitResult <= Abandon0; }

	///  \brief		returns index of abandoned thread
	///  \return	abandoned thread index
	size_t abandoned_index() const
	{
		if ( !abandoned() )
			throw range_error(::ca::get_thread_app(), "abandoned index out of range");
		return -(m_iWaitResult + Abandon0);
	}

	///  \brief		checks if last result == Failure
	///  \return	true if last result == Failure
	bool failed() const
	{ return m_iWaitResult == Failure; }

	///  \brief		checks if last result == BadThread
	///  \return	true if last result == BadThread
	bool bad_thread() const
	{ return m_iWaitResult == BadThread; }

	///  \brief		checks if last result == Timeout
	///  \return	true if last result == Timeout
	bool timeout() const
	{ return m_iWaitResult == Timeout; }

	///  \brief		checks if last result == Event0
	///  \return	true if last result == Event0
	bool signaled() const
	{ return m_iWaitResult >= Event0; }

	///  \brief		returns index of signaled thread
	///  \return	signaled thread index
	size_t signaled_index() const
	{
		if ( !signaled() )
			throw range_error(::ca::get_thread_app(), "signaled index out of range");
		return m_iWaitResult - Event0;
	}

};

