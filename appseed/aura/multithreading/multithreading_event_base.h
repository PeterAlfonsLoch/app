#pragma once


class CLASS_DECL_AURA event_base :
   public sync_object
{
public:


   int_ptr        m_object;
	bool           m_bOwn;


   event_base(int_ptr item = -1, const char * pszName = NULL);
   virtual ~event_base();


	void release_ownership();

   virtual void * get_os_data() const;


	virtual int_ptr item() const;
   operator int_ptr () { return m_object; }
   operator int_ptr () const { return m_object; }
	void set_item( int_ptr item );

	virtual void init_wait ();
	virtual void exit_wait ();


};


namespace internal { class SocketWaiterThread; }


