//#include "framework.h"
//#include "signal.h"


signal_details::signal_details(::aura::application * papp) :
   object(papp)
{
   m_iParam    = 0;
   m_psignal   = NULL;
   m_bRet      = false;
   m_iIndex    = 0;
   m_pset      = NULL;
}


signal_details::signal_details(class signal * psignal) :
   object(psignal->get_app())
{
   m_iParam    = 0;
   m_psignal   = psignal;
   m_bRet      = false;
   m_iIndex    = 0;
   m_pset      = NULL;
}

signal_details::signal_details(::aura::application * papp,class signal * psignal):
   object(papp)
{

   if(m_pauraapp == NULL && psignal != NULL)
   {

      m_pauraapp = psignal->m_pauraapp;

   }

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

   signalizable_disconnect_all();

}


void signalizable::signalizable_disconnect_all()
{

   for(int32_t i = 0; i < m_signalptra.get_size(); i++)
   {

      m_signalptra[i]->disconnect(this);

   }

   m_signalptra.remove_all();

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

      if(m_signalptra[i]->m_delegateptra.get_count() <= 0)
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

      if (m_signalptra[i]->m_delegateptra.get_count() <= 0)
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

   for (index i = 0; i < m_delegateptra.get_count(); i++)
   {

      m_delegateptra[i]->get_signalizable()->unregister_signal(this);

   }

   m_delegateptra.remove_all();

}


void signal::emit(signal_details * pobj)
{
   if(pobj == NULL)
   {
      for(index i = m_delegateptra.get_size() - 1; i >= 0 ; i++)
      {
         m_delegateptra[i]->emit(NULL);
      }
   }
   else
   {
      for(pobj->m_iIndex = m_delegateptra.get_upper_bound(); pobj->m_iIndex >= 0 ; pobj->m_iIndex = MIN(pobj->m_iIndex - 1, m_delegateptra.get_upper_bound()))
      {
         signal_delegate * pdelegate = m_delegateptra.element_at(pobj->m_iIndex);
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
   signal_delegate * pdelegate = m_delegateptra.element_at(pobj->m_iIndex);
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

   return m_delegateptra.get_size() > 0;

}


void signal::disconnect(signalizable * psignalizable)
{

   for(int32_t i = 0; i < m_delegateptra.get_size();)
   {

      if(m_delegateptra[i]->get_signalizable() == psignalizable)
      {

         try
         {

            m_delegateptra.remove_at(i);

         }
         catch(...)
         {

         }

      }
      else
      {

         i++;

      }

   }

}


void signal::leave_only(signalizable * psignalizable)
{

   for(int32_t i = 0; i < m_delegateptra.get_size();)
   {

      if(m_delegateptra[i]->get_signalizable() != psignalizable)
      {

         m_delegateptra[i]->get_signalizable()->unregister_signal(this);

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

signalid_array::signalid_array()
{

}

signalid_array::~signalid_array()
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



void signalizable::on_request_signal(request_signal * prequestsignal)
{
   request_file_query(prequestsignal->m_varFile, prequestsignal->m_varQuery);
}


dispatch::handler_item_base::~handler_item_base()
{


}


dispatch::handler_item_array::~handler_item_array()
{
}

bool dispatch::handler_item_array::HasSignalizable(signalizable* psignalizable)
{
   for (int32_t i = 0; i < this->get_size(); i++)
   {
      if (this->element_at(i)->get_signalizable() == psignalizable)
         return true;
   }
   return false;
}


dispatch::signal_item::signal_item()
{
   m_psignal      = NULL;
   m_pid          = NULL;
}

dispatch::signal_item::~signal_item()
{
   ::aura::del(m_psignal);
}

dispatch::dispatch()
{
}

dispatch::~dispatch()
{

   string strId = typeid(*this).name();

}


