#pragma once


namespace gen
{

   class signal;
   class request_signal;

   class CLASS_DECL_ca signal_object :
      public ::radix::object
   {
      friend class signal;


   protected:


      int                  m_iIndex;
      gen::property_set *  m_pset;


   public:


      int                  m_iParam;
      bool                 m_bRet;
      signal *             m_psignal;



      signal_object(::ca::application * papp = NULL);
      signal_object(signal * psignal);
      virtual ~signal_object();


      bool emit(); // returns m_bRet

      bool all_previous(); // returns bRet

      bool previous(); // returns bRet


      gen::property_set & operator()();

   };


   class CLASS_DECL_ca signalizable :
      virtual public ::radix::object
   {
   public:


      comparable_eq_array < signal *, signal * > m_signalptra;


      signalizable();
      virtual ~signalizable();


      virtual void on_request_signal(request_signal * pobj);

      void register_signal(signal * psignal);
      void unregister_signal(signal * psignal);
      void unregister_target(gen::signalizable * psignalizable);
      void filter_target(gen::signalizable * psignalizable);

   };


   class CLASS_DECL_ca signal
   {
   protected:
      class signal_delegate
      {
      public:
         virtual ~signal_delegate()
         {
         };
         virtual void emit(signal_object * pobject) = 0;
         virtual signalizable * get_signalizable() { return NULL;}
      };
      template < class T >
      class signal_delegate_instance : public signal_delegate
      {
      public:
         signal_delegate_instance(T * psignalizable)
         {
#ifdef _DEBUG
            // The object that is connected to a signal should be signalizable
            // (derived from signalizable);
            signalizable * psignalizableTest = psignalizable;
            DBG_UNREFERENCED_LOCAL_VARIABLE(psignalizableTest);
#endif
            m_psignalizable = psignalizable;
         };
         T * m_psignalizable; // should be derived from
         void (T::*m_pfn)(signal_object *);
         virtual void emit(signal_object * pobject);
         bool operator == (const signal_delegate_instance & deleg) const;
         virtual signalizable * get_signalizable() { return m_psignalizable;}
      };
      friend class signalizable;
   public:
      signal(void);
      virtual ~signal(void);

      bool has_handler();
      void emit(signal_object * pobject = NULL);
      void emit_previous(signal_object * pobject);
      void emit_all_previous(signal_object * pobject);
      template < class T >
      void connect(T * psignalizable, void (T::*pfn)(signal_object *))
      {
         signal_delegate_instance < T > * pdelegate = new signal_delegate_instance < T >(psignalizable);
         pdelegate->m_pfn = pfn;
         m_delegatea.add_unique(pdelegate);
         psignalizable->register_signal(this);
      }
      template < class T >
      bool is_connected(T * psignalizable, void (T::*pfn)(signal_object *))
      {
         for(int i = 0; i < m_delegatea.get_size(); i++)
         {
            signal_delegate_instance < T > * pdelegate = m_delegatea.typed_ptr_at < signal_delegate_instance < T > > (i);
            if(pdelegate != NULL && pdelegate->m_psignalizable == psignalizable && pdelegate->m_pfn == pfn)
               return true;
         }
         return false;
      }

   protected:
      array_del_ptr < signal_delegate > m_delegatea;
      void disconnect(signalizable * psignalizable);
      void leave_only(signalizable * psignalizable);
   };

   template < class T>
   void connect(signal & sig, T * p, void (T::*pfn)(signal_object *))
   {
      sig.connect(p, pfn);
   }

   template < class T >
   void signal::signal_delegate_instance<T>::emit(signal_object * pobject)
   {
      (m_psignalizable->*m_pfn)(pobject);
   }

   template < class T >
   bool signal::signal_delegate_instance<T>::operator == (const signal_delegate_instance<T> & deleg) const
   {
      return m_psignalizable == deleg.m_psignalizable
         && m_pfn == deleg.m_pfn;
   }

   class CLASS_DECL_ca signalid
   {
   public:
      virtual ~signalid();
      virtual bool is_equal(signalid * pid) = 0;
      virtual bool matches(signalid * pid) = 0;
      virtual signalid * copy() = 0;
   };

   class CLASS_DECL_ca signalid_array :
      virtual public base_array < signalid *, signalid * >
   {
   public:
      virtual ~signalid_array();
      signalid * get(signalid * pid);
   };

   class CLASS_DECL_ca dispatch
   {
      protected:
      public:

         class CLASS_DECL_ca handler_item_base
         {
         public:
            virtual gen::signalizable * get_signalizable() = 0;
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
            virtual gen::signalizable * get_signalizable() { return dynamic_cast < gen::signalizable * > (m_psignalizable); }
         };

         class CLASS_DECL_ca handler_item_array :
            public base_array < handler_item_base *, handler_item_base *>
         {
         public:
            bool HasSignalizable(gen::signalizable * psignalizable);
         };

         class CLASS_DECL_ca signal :
            virtual public ::radix::object
         {
         public:
            signalid *        m_pid;
            gen::signal *     m_psignal;

            handler_item_array  m_handlera;

            signal();
            virtual ~signal();

         };

         class CLASS_DECL_ca signal_ptr_array :
            public base_array < signal * , signal * >
         {
         public:
            bool emit(signal_object * pobj);
         };

         class CLASS_DECL_ca signal_array :
            public array_ptr_alloc < signal , signal & >
         {
         public:
            void GetSignalsById(signal_ptr_array & signalptra, signalid * pid);
            signal * GetSignalById(signalid * pid);
         };


         void RemoveMessageHandler(gen::signalizable * psignalizable);
         // Prototype_bool_WPARAM_LPARAM;

         template < class T >
         bool AddMessageHandler(
            signalid * pid,
            T * psignalizable,
            void (T::*pfn)(gen::signal_object *),
            bool bAddUnique = true)
         {
            signal * psignal = m_signala.GetSignalById(pid);
            // If not found a existing Signal, create one
            if(psignal == NULL)
            {
               psignal                    = new signal;
               psignal->m_pid             = pid->copy();
               psignal->m_psignal         = new gen::signal();
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

      public:
         int                  m_iHandling;
         signal_array          m_signala;


         dispatch();
         virtual ~dispatch();

      };


inline void dispatch::signal_array::
GetSignalsById(dispatch::signal_ptr_array & signalptra, signalid * pid)
{
   for(int i = 0; i < this->get_size(); i++)
   {
      signal & signal = this->element_at(i);
      if(signal.m_pid->matches(pid))
      {
         signalptra.add(&signal);
      }
   }
}

inline dispatch::signal * dispatch::signal_array::GetSignalById(signalid * pid)
{
   for(int i = 0; i < this->get_size(); i++)
   {
      signal & signal = this->element_at(i);
      if(signal.m_pid->matches(pid))
      {
         return &signal;
      }
   }
   return NULL;
}


} // namespace gen


#define DECL_GEN_SIGNAL(function) void function(gen::signal_object * pobj);
#define DECL_GEN_VSIGNAL(function) virtual void function(gen::signal_object * pobj);
#define BEG_GEN_SIGNAL(cl, function, signal_impl_class) void cl::function(gen::signal_object * pobj) \
{ SCAST_PTR(signal_impl_class, pobj, psignal);
#define END_GEN_SIGNAL() }


#include "gen_request_signal.h"
