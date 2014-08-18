#include "framework.h"
#include "signal.h"


signal_details::signal_details(sp(::axis::application) papp) :
   element(papp)
{
   m_iParam    = 0;
   m_psignal   = NULL;
   m_bRet      = false;
   m_iIndex    = 0;
   m_pset      = NULL;
}


signal_details::signal_details(class signal * psignal)
{
   m_iParam    = 0;
   m_psignal   = psignal;
   m_bRet      = false;
   m_iIndex    = 0;
   m_pset      = NULL;
}

signal_details::~signal_details()
{
   if(m_pset != NULL)
   {
      delete m_pset;
   }
}


property_set & signal_details::operator()()
{
   if(m_pset == NULL)
   {
      m_pset = new property_set(get_app());
   }
   return *m_pset;
}

bool signal_details::all_previous() // returns bRet;
{
   m_psignal->emit_all_previous(this);
   return m_bRet;
}

bool signal_details::previous() // returns bRet;
{
   m_psignal->emit_previous(this);
   return m_bRet;
}

bool signal_details::emit()
{
   m_psignal->emit(this);
   return m_bRet;
}

signalizable::signalizable()
{
}

signalizable::~signalizable()
{
   for(int32_t i = 0; i < m_signalptra.get_size(); i++)
   {
      m_signalptra[i]->disconnect(this);
   }
}

void signalizable::install_message_handling(::message::dispatch * pdispatch)
{

   UNREFERENCED_PARAMETER(pdispatch);

}


void signalizable::register_signal(class signal * psignal)
{
   m_signalptra.add_unique(psignal);
}

void signalizable::unregister_signal(class signal * psignal)
{
   for(int32_t i = 0; i < m_signalptra.get_size();)
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

void signalizable::unregister_target(signalizable* psignalizable)
{
   for(int32_t i = 0; i < m_signalptra.get_size();)
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

void signalizable::filter_target(signalizable* psignalizable)
{
   for(int32_t i = 0; i < m_signalptra.get_size(); i++)
   {
      m_signalptra[i]->leave_only(psignalizable);
   }
   for (int32_t i = 0; i < m_signalptra.get_size();)
   {
      if (m_signalptra[i]->m_delegatea.get_count() <= 0)
      {
         m_signalptra.remove_at(i);
      }
      else
      {
         i++;
      }
   }
}

void signal::signal_delegate::emit(signal_details * pobj)
{
   UNREFERENCED_PARAMETER(pobj);
}

signal::signal()
{
}

signal::~signal()
{
   for(int32_t i = 0; i < m_delegatea.get_size(); i++)
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


void signal::emit(signal_details * pobj)
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
      for(pobj->m_iIndex = m_delegatea.get_upper_bound(); pobj->m_iIndex >= 0 ; pobj->m_iIndex = MIN(pobj->m_iIndex - 1, m_delegatea.get_upper_bound()))
      {
         signal_delegate * pdelegate = m_delegatea.element_at(pobj->m_iIndex);
         pdelegate->emit(pobj);
         if(pobj->m_bRet)
            return;
      }
   }
}

void signal::emit_previous(signal_details * pobj)
{
   if(pobj->m_iIndex <= 0)
      return;
   pobj->m_iIndex--;
   signal_delegate * pdelegate = m_delegatea.element_at(pobj->m_iIndex);
   pdelegate->emit(pobj);
}

void signal::emit_all_previous(signal_details * pobj)
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
   for(int32_t i = 0; i < m_delegatea.get_size();)
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
   for(int32_t i = 0; i < m_delegatea.get_size();)
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
   for(int32_t i = 0; i < this->get_size(); i++)
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
   for(int32_t i = 0; i < this->get_size(); i++)
   {
      delete this->element_at(i);
   }
}


void signalizable::on_request_signal(request_signal * prequestsignal)
{
   request_file_query(prequestsignal->m_varFile, prequestsignal->m_varQuery);
}


dispatch::signal_item::signal_item()
{
}

dispatch::signal_item::~signal_item()
{
   delete m_psignal;
}

dispatch::dispatch()
{
}

dispatch::~dispatch()
{
}


