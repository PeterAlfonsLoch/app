/**
* \brief	Platform independent waitables
*/
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
class CLASS_DECL_AXIS wait_result
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
	///  \brief		constructor with result value and object ::count passed (Windows only)
	///  \param		value waiting result value as passed by Windows API function
	///  \param		objectCount number of items in event_collection
	explicit wait_result(uint32_t value, ::count objectCount = 1);
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
	inline bool abandoned() const;

	///  \brief		returns index of abandoned thread
	///  \return	abandoned thread index
	inline size_t abandoned_index() const;

	///  \brief		checks if last result == Failure
	///  \return	true if last result == Failure
	inline bool failed() const;

	///  \brief		checks if last result == BadThread
	///  \return	true if last result == BadThread
	inline bool bad_thread() const;

	///  \brief		checks if last result == Timeout
	///  \return	true if last result == Timeout
	inline bool timeout() const;

	///  \brief		checks if last result == Event0
	///  \return	true if last result == Event0
	inline bool signaled() const;

   inline bool succeeded() const;

	///  \brief		returns index of signaled thread
	///  \return	signaled thread index
	inline size_t signaled_index() const;

};

