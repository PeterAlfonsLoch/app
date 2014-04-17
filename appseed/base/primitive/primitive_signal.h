#pragma once


namespace message
{

   class dispatch;

} // namespace message

class signal;
class request_signal;


class CLASS_DECL_BASE signal_details :
   public object
{
public:


   index                m_iIndex;
   property_set *  m_pset;
   index                m_iParam;
   bool                 m_bRet;
   class signal *             m_psignal;



   signal_details(sp(base_application) papp = NULL);
   signal_details(class signal * psignal);
   virtual ~signal_details();


   bool emit(); // returns m_bRet

   bool all_previous(); // returns bRet

   bool previous(); // returns bRet


   property_set & operator()();

};


class CLASS_DECL_BASE signalizable :
   virtual public ::object
{
public:


   comparable_eq_array < class signal *, class signal * > m_signalptra;


   signalizable();
   virtual ~signalizable();


   virtual void on_request_signal(request_signal * pobj);

   void register_signal(class signal * psignal);
   void unregister_signal(class signal * psignal);
   void unregister_target(signalizable* psignalizable);
   void filter_target(signalizable* psignalizable);


   virtual void install_message_handling(::message::dispatch * pdispatch);

};

class CLASS_DECL_BASE base_signalizable_array :
   virtual protected comparable_array < signalizable * >
{
public:

   inline index add(signalizable * psignalizable)
   {
      install_handlers(psignalizable);
      return ::comparable_array < signalizable * >::add(psignalizable);
   }
   inline index remove(signalizable * psignalizable)
   {
      return ::comparable_array < signalizable * >::remove(psignalizable);
   }

   inline signalizable * element_at(index i) { return ::comparable_array < signalizable * >::element_at(i); }
   inline ::count get_size() { return ::comparable_array < signalizable * >::get_size(); }
   inline ::count get_count() { return ::comparable_array < signalizable * >::get_count(); }
   inline ::count size() { return ::comparable_array < signalizable * >::size(); }
   inline ::count count() { return ::comparable_array < signalizable * >::count(); }

   virtual void install_handlers(signalizable *) {}

};


template < class SIGNALIZABLE >
class signalizable_array :
   virtual public base_signalizable_array
{
public:

   inline index add(SIGNALIZABLE * psignalizable)
   {
      return base_signalizable_array::add(psignalizable);
   }

   inline index remove(SIGNALIZABLE * psignalizable)
   {
      return base_signalizable_array::remove(psignalizable);
   }

   SIGNALIZABLE * element_at(index i) { return dynamic_cast < SIGNALIZABLE * > (base_signalizable_array::element_at(i)); }

};

class CLASS_DECL_BASE signal :
   virtual public root
{
protected:


   class signal_delegate :
      virtual public element
   {
   public:
      virtual ~signal_delegate()
      {
      };
      virtual void emit(signal_details * pobject) = 0;
      virtual signalizable * get_signalizable() { return NULL;}
   };
   template < class T >
   class signal_delegate_instance : public signal_delegate
   {
   public:
      signal_delegate_instance(T * psignalizable)
      {
#if defined(DEBUG) && defined(WINDOWS)
         // The object that is connected to a signal should be signalizable
         // (derived from signalizable);
         signalizable * psignalizableTest = psignalizable;
         DBG_UNREFERENCED_LOCAL_VARIABLE(psignalizableTest);
#endif
         m_psignalizable = psignalizable;
      };
      T * m_psignalizable; // should be derived from
      void (T::*m_pfn)(signal_details *);
      virtual void emit(signal_details * pobject);
      bool operator == (const signal_delegate_instance & deleg) const;
      virtual signalizable * get_signalizable() { return m_psignalizable;}
   };
   friend class signalizable;
public:
   signal();
   virtual ~signal();

   bool has_handler();
   void emit(signal_details * pobject = NULL);
   void emit_previous(signal_details * pobject);
   void emit_all_previous(signal_details * pobject);
   template < class T >
   void connect(T * psignalizable, void (T::*pfn)(signal_details *))
   {
      signal_delegate_instance < T > * pdelegate = canew(signal_delegate_instance < T >(psignalizable));
      pdelegate->m_pfn = pfn;
      m_delegatea.add(pdelegate);
      psignalizable->register_signal(this);
   }
   template < class T >
   bool is_connected(T * psignalizable, void (T::*pfn)(signal_details *))
   {
      for(int32_t i = 0; i < m_delegatea.get_size(); i++)
      {
         signal_delegate_instance < T > * pdelegate = m_delegatea.typed_ptr_at < signal_delegate_instance < T > > (i);
         if(pdelegate != NULL && pdelegate->m_psignalizable == psignalizable && pdelegate->m_pfn == pfn)
            return true;
      }
      return false;
   }

protected:
   spa(signal_delegate) m_delegatea;
   void disconnect(signalizable * psignalizable);
   void leave_only(signalizable * psignalizable);
};


template < class T >
void connect(class signal & sig, T * p, void (T::*pfn)(signal_details *))
{

   sig.connect(p, pfn);

}


template < class T >
void signal::signal_delegate_instance<T>::emit(signal_details * pobject)
{

   (m_psignalizable->*m_pfn)(pobject);

}


template < class T >
bool signal::signal_delegate_instance<T>::operator == (const signal_delegate_instance<T> & deleg) const
{

   return m_psignalizable == deleg.m_psignalizable && m_pfn == deleg.m_pfn;

}


class CLASS_DECL_BASE signalid
{
public:


   virtual ~signalid();
   virtual bool is_equal(signalid * pid) = 0;
   virtual bool matches(signalid * pid) = 0;
   virtual signalid * copy() = 0;


};

class CLASS_DECL_BASE signalid_array :
   virtual public array < signalid *, signalid * >
{
public:


   virtual ~signalid_array();
   signalid * get(signalid * pid);


};


class CLASS_DECL_BASE dispatch
{
public:


   class CLASS_DECL_BASE handler_item_base
   {
   public:

      virtual signalizable* get_signalizable() = 0;

   };


   template < class T >
   class handler_item : public handler_item_base
   {
   public:
      T *                     m_psignalizable;
      // Pointer to signal object directly associate with the
      // prototype.
      // This is a cached value and not the
      // storage holder of the object.
      virtual signalizable* get_signalizable() { return dynamic_cast < signalizable* > (m_psignalizable); }
   };


   class CLASS_DECL_BASE handler_item_array :
      public array < handler_item_base *, handler_item_base *>
   {
   public:
      bool HasSignalizable(signalizable* psignalizable);
   };


   class CLASS_DECL_BASE signal_item :
      virtual public ::object
   {
   public:


      signalid *           m_pid;
      class ::signal *     m_psignal;

      handler_item_array   m_handlera;


      signal_item();
      virtual ~signal_item();

   };


   class CLASS_DECL_BASE signal_item_ptr_array :
      public array < signal_item * , signal_item * >
   {
   public:

      bool emit(signal_details * pobj);

   };


   class CLASS_DECL_BASE signal_item_array :
      public spa(signal_item)
   {
   public:

      void GetSignalsById(signal_item_ptr_array & signalptra, signalid * pid);
      signal_item * GetSignalById(signalid * pid);

   };


   void RemoveMessageHandler(signalizable* psignalizable);
   // Prototype_bool_WPARAM_LPARAM;

   template < class T >
   bool AddMessageHandler(
      signalid * pid,
      T * psignalizable,
      void (T::*pfn)(signal_details *),
      bool bAddUnique = true)
   {
      signal_item * psignal = m_signala.GetSignalById(pid);
      // If not found a existing Signal, create one
      if(psignal == NULL)
      {
         psignal                    = new signal_item;
         psignal->m_pid             = pid->copy();
         psignal->m_psignal         = new class ::signal();
         psignal->m_psignal->connect(psignalizable, pfn);
         handler_item <T> * pitem   = new handler_item<T>;
         pitem->m_psignalizable     = psignalizable;
         psignal->m_handlera.add(pitem);
         m_signala.add(psignal);
      }
      else
      {
         if(bAddUnique && psignal->m_psignal->is_connected(psignalizable, pfn))
            return true;
         // If a matching Signal is found, connect to
         // this signal.
         psignal->m_psignal->connect(psignalizable, pfn);
         handler_item <T> * pitem = new handler_item<T>;
         pitem->m_psignalizable = psignalizable;
         psignal->m_handlera.add(pitem);
      }
      m_iHandling++;
      return true;
   }

   int32_t                  m_iHandling;
   signal_item_array          m_signala;


   dispatch();
   virtual ~dispatch();

};


inline void dispatch::signal_item_array::GetSignalsById(dispatch::signal_item_ptr_array & signalptra, signalid * pid)
{
   for(int32_t i = 0; i < this->get_size(); i++)
   {
      signal_item & signal = *this->element_at(i);
      if(signal.m_pid->matches(pid))
      {
         signalptra.add(&signal);
      }
   }
}

inline dispatch::signal_item * dispatch::signal_item_array::GetSignalById(signalid * pid)
{
   for(int32_t i = 0; i < this->get_size(); i++)
   {
      signal_item & signal = *this->element_at(i);
      if(signal.m_pid->matches(pid))
      {
         return &signal;
      }
   }
   return NULL;
}


#define DECL_GEN_SIGNAL(function) void function(signal_details * pobj)
#define DECL_GEN_VSIGNAL(function) virtual void function(signal_details * pobj)
#define BEG_GEN_SIGNAL(cl, function, signal_impl_class) void cl::function(signal_details * pobj) \
{ SCAST_PTR(signal_impl_class, pobj, psignal);
#define END_GEN_SIGNAL() }



