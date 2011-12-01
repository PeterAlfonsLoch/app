/**
* \brief	Platform independent waitables (windows version)
* \author	Thomas Hoefer
*/


#pragma once


/// This class represents waitables which can be put into a event_collection.
class CLASS_DECL_ca event_base : 
   virtual public waitable
{
public:


	/// internal member holding the handle of the waitable
	HANDLE   m_object;

	/// internal member holding the owner of the waitable
	bool     m_bOwn;

	///  \brief		destructor
	virtual ~event_base();

	///  \brief		constructor with passed handle
	///  \param		item handle of the item (default: INVALID_HANDLE_VALUE)
	explicit event_base( HANDLE item=INVALID_HANDLE_VALUE);

	///  \brief		handle setter
	///  \param     item handle to set
	void set_item( HANDLE item );

	///  \brief		resets ownership of the waitable item
	void release_ownership();

	///  \brief		handle getter
	///  \return    item handle
	virtual HANDLE item() const;

   virtual void * get_os_data() const;

   operator HANDLE ()
   {
      return m_object;
   }

   operator HANDLE () const
   {
      return m_object;
   }

	virtual void init_wait ();
	virtual void exit_wait ();
};


namespace internal { class SocketWaiterThread; }


//#pragma comment(exestr,"$Id: waitable_windows.hpp,v 1.30 2008/02/08 10:41:29 alsdorf\jgo Exp $")
//
// EoF
///////
