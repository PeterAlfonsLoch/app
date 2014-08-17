#pragma once


class CLASS_DECL_AXIS event_base :
   virtual public waitable
{
public:


   int_ptr        m_object;
	bool           m_bOwn;

	virtual ~event_base();

   explicit event_base(int_ptr item = -1);

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


