#include "StdAfx.h"

namespace database
{

   bool server::data_server_load(class id idSection, class id id, class id idIndex, var & var   , update_hint * puh)
   {
      return data_server_load(idSection, id, idIndex, (ex1::serializable &) var, puh);
   }

   bool server::data_server_load(class id idSection, class id id, class id idIndex, ex1::serializable & obj, update_hint * puh)
   {
      UNREFERENCED_PARAMETER(idSection);
      UNREFERENCED_PARAMETER(id);
      UNREFERENCED_PARAMETER(idIndex);
      UNREFERENCED_PARAMETER(obj);
      UNREFERENCED_PARAMETER(puh);
      return false;
   }

   bool server::data_server_save(class id idSection, class id id, class id idIndex, var & var   , update_hint * puh)
   {
      return data_server_save(idSection, id, idIndex, (ex1::serializable &) var, puh);
   }

   bool server::data_server_save(class id idSection, class id id, class id idIndex, ex1::serializable & obj, update_hint * puh)
   {
      UNREFERENCED_PARAMETER(puh);
      UNREFERENCED_PARAMETER(obj);
      return false;
   }

   bool server::data_pulse_change(class id idSection, class id key, class id idIndex, update_hint * puh)
   {
      return on_after_data_change(idSection, key, idIndex, puh);
   }


   bool server::on_before_data_change(class id idSection, class id key, class id idIndex, var & var, update_hint * puh)
   {
      ::database::change_event signal(var);
      signal.m_pserver = this;
      signal.m_key.m_idSection = idSection;
      signal.m_key.m_idKey = key;
      signal.m_key.m_idIndex = idIndex;
      signal.m_puh = puh;
      for(int i = 0; i < client_array::get_count(); i++)
      {
         client_array::element_at(i)->data_on_before_change(&signal);
         if(!signal.m_bOk)
            return false;

      }
      return true;
   }

   bool server::on_after_data_change(class id idSection, class id key, class id idIndex, update_hint * puh)
   {
      ::database::change_event signal;
      signal.m_pserver       = this;
      signal.m_key.m_idSection   = idSection;
      signal.m_key.m_idKey       = key;
      signal.m_key.m_idIndex     = idIndex;
      signal.m_puh = puh;
      for(int i = 0; i < client_array::get_count(); i++)
      {
         client_array::element_at(i)->data_on_after_change(&signal);
      }
      return true;
   }

   var server::data_load(class id idSection, class id id, class id idIndex, update_hint * phint)
   {
      var var;
      if(data_server_load(idSection, id, idIndex, var, phint))
         return var;
      return gen::e_fail;
   }

   bool server::data_save(class id idSection, class id id, class id idIndex, var var, update_hint * phint)
   {
      return data_server_save(idSection, id, idIndex, var, phint);
   }

} // namespace database