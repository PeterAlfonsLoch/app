#include "framework.h"


namespace database
{


   client::client()
   {
      m_pdataserver = NULL;
   }


   void client::initialize_data_client(server * pserver)
   {
      set_data_server(pserver);
   }

   bool client::set_data_server(server * pserver)
   {
      if(pserver != NULL)
      {
         pserver->add_client(this);
      }
      m_pdataserver = pserver;
      return true;
   }


   client::~client()
   {
      if(m_pdataserver != NULL)
      {
         try
         {
            m_pdataserver->RemoveClient(this);
         }
         catch(...)
         {
         }
      }
   }

   void client::data_on_before_change(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }

   void client::data_on_after_change(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }

   bool client::data_set(class id id, bool b, update_hint * phint)
   {
      return data_set(id, ::axis::system::idEmpty, b, phint);
   }

   bool client::data_set(class id id, const char * lpcsz, update_hint * phint)
   {
      return data_set(id, ::axis::system::idEmpty, lpcsz, phint);
   }

   bool client::data_get(class id id, bool & b)
   {
      return data_get(id, ::axis::system::idEmpty, b);
   }

   bool client::data_get(class id id, string & str)
   {
      return data_get(id, ::axis::system::idEmpty, str);
   }

   bool client::data_set(class id id, class id idIndex, bool b, update_hint * phint)
   {
      UNREFERENCED_PARAMETER(phint);
      int32_t i;
      if(b)
      {
         i = 1;
      }
      else
      {
         i = 0;
      }
      return data_set(id, idIndex, i, phint);
   }


   bool client::data_set(
      class id id,
      class id idIndex,
      var & var,
      update_hint * puh)
   {
      if(m_pdataserver != NULL)
      {
         return m_pdataserver->data_server_save(this, get_data_id(), id, idIndex, var, puh);
      }
      return false;
   }

   bool client::data_set(class id id, class id idIndex, int32_t i, update_hint * puh)
   {
      if(m_pdataserver != NULL)
      {
         var var(i);
         return m_pdataserver->data_server_save(this, get_data_id(), id, idIndex, var, puh);
      }
      return false;
   }

   bool client::data_set(class id id, class id idIndex, int64_t i, update_hint * puh)
   {
      if(m_pdataserver != NULL)
      {
         var var(i);
         return m_pdataserver->data_server_save(this, get_data_id(), id, idIndex, var, puh);
      }
      return false;
   }


   bool client::data_set(class id id, int32_t i, update_hint * puh)
   {
      return data_set(id, ::axis::system::idEmpty, i, puh);
   }

   bool client::data_set(class id id, int64_t i, update_hint * puh)
   {
      return data_set(id, ::axis::system::idEmpty, i, puh);
   }

   bool client::data_get(class id id, int32_t & i)
   {
      return data_get(id, ::axis::system::idEmpty, i);
   }

   bool client::data_get(class id id, int64_t & i)
   {
      return data_get(id, ::axis::system::idEmpty, i);
   }

   bool client::data_set(class id id, class id idIndex, const char * lpsz, update_hint * puh)
   {
      return data_set(get_data_id(), id, idIndex, lpsz, puh);
   }

   bool client::data_set(class id dataid, class id id, class id idIndex, const char * lpsz, update_hint * puh)
   {
      if(m_pdataserver != NULL)
      {
         var var;
         var = lpsz;
         return m_pdataserver->data_server_save(this, dataid, id, idIndex, var, puh);
      }
      return false;
   }

   bool client::data_set(class id id, class id idIndex, const wchar_t * lpsz, update_hint * puh)
   {
      if(m_pdataserver != NULL)
      {
         var var;
         var = lpsz;
         return m_pdataserver->data_server_save(this, get_data_id(), id, idIndex, var, puh);
      }
      return false;
   }


   bool client::data_set(selection & selection, const char * lpsz, update_hint * puh)
   {
      ::count iCount = selection.get_item_count();
      bool bOk = true;
      for(index iItem = 0; iItem < iCount; iItem++)
      {
         selection_item & item = selection.get_item(iItem);
         if(!data_set(
            item.m_id,
            item.m_idIndex,
            lpsz,
            puh))
         {
            bOk = false;
         }

      }
      return bOk;
   }

   bool client::data_set(selection & selection, var & var, update_hint * puh)
   {
      ::count iCount = selection.get_item_count();
      bool bOk = true;
      for(index iItem = 0; iItem < iCount; iItem++)
      {
         selection_item & item = selection.get_item(iItem);
         if(!data_set(
            item.m_id,
            item.m_idIndex,
            var,
            puh))
         {
            bOk = false;
         }

      }
      return bOk;
   }

   bool client::data_set(class id id, class id idIndex, ::file::stream_buffer & readable, update_hint * puh)
   {
      if(m_pdataserver != NULL)
      {
         return m_pdataserver->data_server_save(this, get_data_id(), id, idIndex, readable, puh);
      }
      return false;
   }

   bool client::data_set(class id id, class id idIndex, ::file::serializable & obj, update_hint * puh)
   {
      if(m_pdataserver != NULL)
      {
         if(!m_pdataserver->data_server_save(this, get_data_id(), id, idIndex, obj, puh))
            return false;
         return true;
      }
      return false;
   }

   bool client::data_set(class id id, class id idIndex, ::file::input_stream & istream, update_hint * puh)
   {
      if(m_pdataserver != NULL)
      {
         return m_pdataserver->data_server_save(this, get_data_id(), id, idIndex, istream, puh);
      }
      return false;
   }


   bool client::data_get(class id id, class id idIndex, bool & b)
   {
      int32_t i;
      if(!data_get(id, idIndex, i))
         return false;
      b = i != 0;
      return true;
   }


   bool client::data_get(class id id, class id idIndex, var & var)
   {
      if(m_pdataserver != NULL)
      {
         return m_pdataserver->data_server_load(this, get_data_id(), id, idIndex, var);
      }
      return false;
   }

   bool client::data_get(class id id, class id idIndex, int32_t & i)
   {
      if(m_pdataserver != NULL)
      {
         var var;
         if(!m_pdataserver->data_server_load(this, get_data_id(), id, idIndex, var))
            return false;
         i = var;
         return true;
      }
      return false;
   }

   bool client::data_get(class id id, class id idIndex, int64_t & i)
   {
      if(m_pdataserver != NULL)
      {
         var var;
         if(!m_pdataserver->data_server_load(this, get_data_id(), id, idIndex, var))
            return false;
         i = var;
         return true;
      }
      return false;
   }

   bool client::data_get(class id id, class id idIndex, string & str)
   {
      return data_get(get_data_id(), id, idIndex, str);
   }

   bool client::data_get(class id dataid, class id id, class id idIndex, string & str)
   {
      if(m_pdataserver != NULL)
      {
         var var;
         if(!m_pdataserver->data_server_load(this, dataid, id, idIndex, var))
            return false;
         if(var.get_type() != var::type_string)
            return false;
         str = var.m_str;
         return true;
      }
      return false;
   }

   bool client::data_get(class id id, class id idIndex, ::file::stream_buffer & writable)
   {
      if(m_pdataserver != NULL)
      {
         if(!m_pdataserver->data_server_load(this, get_data_id(), id, idIndex, writable))
            return false;
         return true;
      }
      return false;
   }

   bool client::data_get(class id id, class id idIndex, ::file::serializable & obj)
   {
      if(m_pdataserver != NULL)
      {
         if(!m_pdataserver->data_server_load(this, get_data_id(), id, idIndex, obj))
            return false;
         return true;
      }
      return false;
   }

   bool client::data_get(class id id, class id idIndex, ::file::output_stream & ostream)
   {
      if(m_pdataserver != NULL)
      {
         if(!m_pdataserver->data_server_load(this, get_data_id(), id, idIndex, ostream))
            return false;
         return true;
      }
      return false;
   }

   
   bool client::data_pulse_change(class id id, class id idIndex, update_hint * puh)
   {
      if(m_pdataserver != NULL)
      {
         if(!m_pdataserver->data_pulse_change(this, get_data_id(), id, idIndex, puh))
            return false;
         return true;
      }
      return false;
   }


   client_array::client_array()
   {

   }

   client_array::~client_array()
   {
      for(int32_t i = 0; i < this->get_count(); i++)
      {
         this->element_at(i)->m_pdataserver = NULL;
      }
   }

   void client_array::add_client(client *pclient)
   {
      if(pclient != dynamic_cast < client * > (this))
      {
         add_unique(pclient);
      }
   }

   ::count client_array::GetClientCount()
   {
      return this->get_size();
   }

   client * client_array::ClientAt(index iClient)
   {
      return this->element_at(iClient);
   }

   void client_array::RemoveClient(client *pclient)
   {
      remove(pclient);
   }

   string client::calc_key(::database::id & idSection, ::database::id & id, ::database::id & idIndex)
   {
      string str;
      str = idSection.get_id().str();
      str += ".";
      str += id.get_id().str();
      str += ".";
      str += idIndex.get_id().str();
      return str;
   }


   id client::get_data_id()
   {

      return m_dataid;

   }

   id client::calc_data_id()
   {

      return "";

   }


   bool client::update_data_id()
   {
      
      m_dataid = calc_data_id();

      return true;

   }


} // namespace database


