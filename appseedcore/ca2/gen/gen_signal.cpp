#include "StdAfx.h"
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

   void signal::signal_delegate::emit(signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }

   signal::signal(void)
   {
   }

   signal::~signal(void)
   {
      for(int i = 0; i < m_delegateptra.get_size(); i++)
      {
         m_delegateptra[i]->get_signalizable()->unregister_signal(this);
         delete m_delegateptra[i];
      }
      m_delegateptra.set_size(0);
   }


   void signal::emit(signal_object * pobj)
   {
      if(pobj == NULL)
      {
         for(int i = m_delegateptra.get_size() - 1; i >= 0 ; i++)
         {
            m_delegateptra[i]->emit(NULL);
         }
      }
      else
      {
         for(pobj->m_iIndex = m_delegateptra.get_size() - 1; pobj->m_iIndex >= 0 ; pobj->m_iIndex = min(pobj->m_iIndex - 1, m_delegateptra.get_size() - 1))
         {
            m_delegateptra[pobj->m_iIndex]->emit(pobj);
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
      m_delegateptra[pobj->m_iIndex]->emit(pobj);
   }

   bool signal::has_handler()
   {
      return m_delegateptra.get_size() > 0;
   }

   void signal::disconnect(signalizable * psignalizable)
   {
      for(int i = 0; i < m_delegateptra.get_size();)
      {
         if(m_delegateptra[i]->get_signalizable() == psignalizable)
         {
            delete m_delegateptra[i];
            m_delegateptra.remove_at(i);
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
      for(int i = 0; i < get_size(); i++)
      {
         if(element_at(i)->is_equal(pid))
         {
            return element_at(i);
         }
      }
      add(pid->copy());
      return element_at(get_upper_bound());
   }

   signalid_array::~signalid_array()
   {
      for(int i = 0; i < get_size(); i++)
      {
         delete element_at(i);
      }
   }


   void signalizable::on_request_signal(request_signal * prequestsignal)
   {
      request(prequestsignal->m_varFile, prequestsignal->m_varQuery);
   }

} // namespace gen 