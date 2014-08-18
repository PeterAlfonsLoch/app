#pragma once


#ifdef WINDOWSEX


/// This class represents events for file changes
class CLASS_DECL_AXIS file_change_event :
   virtual public waitable,
   virtual public event_base
{
public:

	/// enum describing the possible filters
	enum filter
	{
		change_file_name = FILE_NOTIFY_CHANGE_FILE_NAME,
		change_dir_name = FILE_NOTIFY_CHANGE_DIR_NAME,
		change_attributes = FILE_NOTIFY_CHANGE_ATTRIBUTES,
		change_size = FILE_NOTIFY_CHANGE_SIZE,
		change_last_write = FILE_NOTIFY_CHANGE_LAST_WRITE,
		change_security = FILE_NOTIFY_CHANGE_SECURITY
	};

	///  \brief		constructor with passed path to file
	///  \param		path the file to watch
	///  \param		watchsubtree if true, the function monitors the directory tree
	///				rooted at the specified directory, if it is false,
	///				it monitors only the specified directory
	///  \param		filter filter conditions that satisfy a change notification wait
	///				can take values described by enum filter
	file_change_event (sp(::base::application) papp, const char * path, bool watchsubtree, uint32_t filter);

	///  \brief		destructor
	~file_change_event();


   virtual bool lock(const duration & durationTimeout = duration::infinite());

   using waitable::unlock;
   virtual bool unlock();


	///  \brief		waits for an file notification forever
	virtual void wait ();

	///  \brief		waits for an file notification for a specified time
	///  \param		duration time period to wait for an file notification
	///  \return	waiting action result as wait_result
	virtual wait_result wait (const duration& duration);

	///  \brief		requests that the operating system signal a change
	///				notification handle the next time it detects an appropriate
	///				change
	bool next ();

	///  \brief		stops change notification handle monitoring
	void close ();

};



#endif


