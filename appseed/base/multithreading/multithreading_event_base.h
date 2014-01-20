/**
* \brief	Platform independent waitables (windows version)
*/


#pragma once


/// This class represents waitables which can be put into a event_collection.
class CLASS_DECL_BASE event_base :
   virtual public waitable
{
public:


	/// internal member holding the handle of the waitable
#ifdef WINDOWS
	HANDLE      m_object;
#else
   int_ptr     m_object;
#endif

	/// internal member holding the owner of the waitable
	bool     m_bOwn;

	///  \brief		destructor
	virtual ~event_base();

	///  \brief		constructor with passed handle
	///  \param		item handle of the item (default: INVALID_HANDLE_VALUE)
#ifdef WINDOWS
	explicit event_base( HANDLE   item = INVALID_HANDLE_VALUE);
#else
   explicit event_base( int_ptr  item = -1);
#endif

	///  \brief		resets ownership of the waitable item
	void release_ownership();

   virtual void * get_os_data() const;


#ifdef WINDOWS
	virtual HANDLE item() const;
   operator HANDLE () { return m_object; }
   operator HANDLE () const { return m_object; }
	void set_item( HANDLE item );
#else
	virtual int_ptr item() const;
   operator int_ptr () { return m_object; }
   operator int_ptr () const { return m_object; }
	void set_item( int_ptr item );
#endif

	virtual void init_wait ();
	virtual void exit_wait ();


};


namespace internal { class SocketWaiterThread; }


//#pragma comment(exestr,"$Id: waitable_windows.hpp,v 1.30 2008/02/08 10:41:29 alsdorf\jgo Exp $")
//
// EoF
///////
