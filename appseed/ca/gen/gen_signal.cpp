#include "framework.h"
#include "signal.h"

namespace gen
{

   signal_object::signal_object(::ca::application * papp) :
      ca(papp)
   {
      m_iParam    = 0;
      m_psignal   = NULL;
      m_bRet      = false;
      m_iIndex    = 0;
      m_pset      = NULL;
   }


   signal_object::signal_object(signal * psignal)
   {
      m_iParam    = 0;
      m_psignal   = psignal;
      m_bRet      = false;
      m_iIndex    = 0;
      m_pset      = NULL;
   }

   signal_object::~signal_object()
   {
      if(m_pset != NULL)
      {
         delete m_pset;
      }
   }


   gen::property_set & signal_object::operator()()
   {
      if(m_pset == NULL)
      {
         m_pset = new gen::property_set(get_app());
      }
      return *m_pset;
   }

   bool signal_object::all_previous() // returns bRet;
   {
      m_psignal->emit_all_previous(this);
      return m_bRet;
   }

   bool signal_object::previous() // returns bRet;
   {
      m_psignal->emit_previous(this);
      return m_bRet;
   }

   bool signal_object::emit()
   {
      m_psignal->emit(this);
      return m_bRet;
   }

   signalizable::signalizable()
   {
   }

   signalizable::~signalizable()
   {
      for(int i = 0; i < m_signalptra.get_size(); i++)
      {
         m_signalptra[i]->disconnect(this);
      }
   }


   void signalizable::register_signal(signal * psignal)
   {
      m_signalptra.add_unique(psignal);
   }

   void signalizable::unregister_signal(signal * psignal)
   {
      for(int i = 0; i < m_signalptra.get_size();)
      {
         if(m_signalptra[i] == psignal)
         {
            m_signalptra.remove_at(i);
         }
         else
         {
            i++;
         }
      }
   }

   void signalizable::unregister_target(gen::signalizable * psignalizable)
   {
      for(int i = 0; i < m_signalptra.get_size();)
      {
         m_signalptra[i]->disconnect(psignalizable);
         if(m_signalptra[i]->m_delegatea.get_count() <= 0)
         {
            m_signalptra.remove_at(i);
         }
         else
         {
            i++;
         }
      }
   }

   void signalizable::filter_target(gen::signalizable * psignalizable)
   {
      for(int i = 0; i < m_signalptra.get_size();)
      {
         m_signalptra[i]->leave_only(psignalizable);
         if(m_signalptra[i]->m_delegatea.get_count() <= 0)
         {
            m_signalptra.remove_at(i);
         }
         else
         {
            i++;
         }
      }
   }

   void signal::signal_delegate::emit(signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }

   signal::signal()
   {
   }

   signal::~signal()
   {
      for(int i = 0; i < m_delegatea.get_size(); i++)
      {
         try
         {
            m_delegatea[i].get_signalizable()->unregister_signal(this);
         }
         catch(...)
         {
         }
      }
   }


   void signal::emit(signal_object * pobj)
   {
      if(pobj == NULL)
      {
         for(index i = m_delegatea.get_size() - 1; i >= 0 ; i++)
         {
            m_delegatea[i].emit(NULL);
         }
      }
      else
      {
         for(pobj->m_iIndex = m_delegatea.get_upper_bound(); pobj->m_iIndex >= 0 ; pobj->m_iIndex = min(pobj->m_iIndex - 1, m_delegatea.get_upper_bound()))
         {
            signal_delegate * pdelegate = m_delegatea.ptr_at(pobj->m_iIndex);
            pdelegate->emit(pobj);
            if(pobj->m_bRet)
               return;
         }
      }
   }

   void signal::emit_previous(signal_object * pobj)
   {
      if(pobj->m_iIndex <= 0)
         return;
      pobj->m_iIndex--;
      signal_delegate * pdelegate = m_delegatea.ptr_at(pobj->m_iIndex);
      pdelegate->emit(pobj);
   }

   void signal::emit_all_previous(signal_object * pobj)
   {
      while(pobj->m_iIndex > 0)
      {
         emit_previous(pobj);
         if(pobj->m_bRet)
            return;
      }
   }

   bool signal::has_handler()
   {
      return m_delegatea.get_size() > 0;
   }

   void signal::disconnect(signalizable * psignalizable)
   {
      for(int i = 0; i < m_delegatea.get_size();)
      {
         if(m_delegatea[i].get_signalizable() == psignalizable)
         {
            m_delegatea.remove_at(i);
         }
         else
         {
            i++;
         }
      }
   }

   void signal::leave_only(signalizable * psignalizable)
   {
      for(int i = 0; i < m_delegatea.get_size();)
      {
         if(m_delegatea[i].get_signalizable() != psignalizable)
         {
            m_delegatea[i].get_signalizable()->unregister_signal(this);
            m_delegatea.remove_at(i);
         }
         else
         {
            i++;
         }
      }
   }


   signalid::~signalid()
   {
   }

   signalid * signalid_array::get(signalid * pid)
   {
      for(int i = 0; i < this->get_size(); i++)
      {
         if(this->element_at(i)->is_equal(pid))
         {
            return this->element_at(i);
         }
      }
      add(pid->copy());
      return this->element_at(get_upper_bound());
   }

   signalid_array::~signalid_array()
   {
      for(int i = 0; i < this->get_size(); i++)
      {
         delete this->element_at(i);
      }
   }


   void signalizable::on_request_signal(request_signal * prequestsignal)
   {
      request(prequestsignal->m_varFile, prequestsignal->m_varQuery);
   }


      dispatch::signal::signal()
      {
      }

      dispatch::signal::~signal()
      {
         delete m_psignal;
      }

      dispatch::dispatch()
      {
      }

      dispatch::~dispatch()
      {
      }


} // namespace gen
