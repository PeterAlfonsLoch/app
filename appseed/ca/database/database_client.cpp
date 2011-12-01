#include "StdAfx.h"

namespace database
{

   client::client()
   {
      m_pdataserver = NULL;
   }


   void client::initialize(::ca::application * papp)
   {
      set_server(dynamic_cast < database::application * > (papp)->get_data_server());
   }


   void client::initialize(server * pserver)
   {
      set_server(pserver);
   }

   bool client::set_server(server * pserver)
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

   void client::data_on_before_change(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }

   void client::data_on_after_change(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }

   bool client::data_set(class id id, bool b, update_hint * phint)
   {
      return data_set(id, ::radix::system::idEmpty, b, phint);
   }

   bool client::data_set(class id id, const char * lpcsz, update_hint * phint)
   {
      return data_set(id, ::radix::system::idEmpty, lpcsz, phint);
   }

   bool client::data_get(class id id, bool & b)
   {
      return data_get(id, ::radix::system::idEmpty, b);
   }

   bool client::data_get(class id id, string & str)
   {
      return data_get(id, ::radix::system::idEmpty, str);
   }

   bool client::data_set(class id id, class id idIndex, bool b, update_hint * phint)
   {
      UNREFERENCED_PARAMETER(phint);
      int i;
      if(b)
      {
         i = 1;
      }
      else
      {
         i = 0;
      }
      return data_set(id, idIndex, i);
   }


   bool client::data_set(
      class id id,
      class id idIndex,
      var & var,
      update_hint * puh)
   {
      if(m_pdataserver != NULL)
      {
         return m_pdataserver->data_server_save(m_dataid, id, idIndex, var, puh);
      }
      return false;
   }

   bool client::data_set(class id id, class id idIndex, int i, update_hint * puh)
   {
      if(m_pdataserver != NULL)
      {
         var var;
         var.set_type(var::type_integer);
         var.m_i = i;
         return m_pdataserver->data_server_save(m_dataid, id, idIndex, var, puh);
      }
      return false;
   }

   bool client::data_set(class id id, class id idIndex, __int64 i, update_hint * puh)
   {
      if(m_pdataserver != NULL)
      {
         var var;
         var.set_type(var::type_integer);
         var.m_i64 = i;
         return m_pdataserver->data_server_save(m_dataid, id, idIndex, var, puh);
      }
      return false;
   }


   bool client::data_set(class id id, int i, update_hint * puh)
   {
      return data_set(id, ::radix::system::idEmpty, i, puh);
   }

   bool client::data_set(class id id, int64_t i, update_hint * puh)
   {
      return data_set(id, ::radix::system::idEmpty, i, puh);
   }

   bool client::data_get(class id id, int & i)
   {
      return data_get(id, ::radix::system::idEmpty, i);
   }

   bool client::data_get(class id id, int64_t & i)
   {
      return data_get(id, ::radix::system::idEmpty, i);
   }

   bool client::data_set(class id id, class id idIndex, const char * lpsz, update_hint * puh)
   {
      return data_set(m_dataid, id, idIndex, lpsz, puh);
   }

   bool client::data_set(class id dataid, class id id, class id idIndex, const char * lpsz, update_hint * puh)
   {
      if(m_pdataserver != NULL)
      {
         var var;
         var = lpsz;
         return m_pdataserver->data_server_save(dataid, id, idIndex, var, puh);
      }
      return false;
   }

   bool client::data_set(class id id, class id idIndex, const wchar_t * lpsz, update_hint * puh)
   {
      if(m_pdataserver != NULL)
      {
         var var;
         var = lpsz;
         return m_pdataserver->data_server_save(m_dataid, id, idIndex, var, puh);
      }
      return false;
   }


   bool client::data_set(selection & selection, const char * lpsz, update_hint * puh)
   {
      int iCount = selection.get_item_count();
      bool bOk = true;
      for(int iItem = 0; iItem < iCount; iItem++)
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
      int iCount = selection.get_item_count();
      bool bOk = true;
      for(int iItem = 0; iItem < iCount; iItem++)
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

   bool client::data_set(class id id, class id idIndex, ex1::readable & readable, update_hint * puh)
   {
      if(m_pdataserver != NULL)
      {
         return m_pdataserver->data_server_save(m_dataid, id, idIndex, readable, puh);
      }
      return false;
   }

   bool client::data_set(class id id, class id idIndex, ex1::byte_serializable & obj, update_hint * puh)
   {
      if(m_pdataserver != NULL)
      {
         if(!m_pdataserver->data_server_save(m_dataid, id, idIndex, obj, puh))
            return false;
         return true;
      }
      return false;
   }

   bool client::data_set(class id id, class id idIndex, ex1::byte_input_stream & istream, update_hint * puh)
   {
      if(m_pdataserver != NULL)
      {
         return m_pdataserver->data_server_save(m_dataid, id, idIndex, istream, puh);
      }
      return false;
   }

   bool client::data_set(class id id, class id idIndex, ex1::plain_text_serializable & obj, update_hint * puh)
   {
      if(m_pdataserver != NULL)
      {
         if(!m_pdataserver->data_server_save(m_dataid, id, idIndex, obj, puh))
            return false;
         return true;
      }
      return false;
   }

   bool client::data_set(class id id, class id idIndex, ex1::plain_text_input_stream & istream, update_hint * puh)
   {
      if(m_pdataserver != NULL)
      {
         return m_pdataserver->data_server_save(m_dataid, id, idIndex, istream, puh);
      }
      return false;
   }

   bool client::data_get(class id id, class id idIndex, bool & b)
   {
      int i;
      if(!data_get(id, idIndex, i))
         return false;
      b = i != 0;
      return true;
   }


   bool client::data_get(class id id, class id idIndex, var & var)
   {
      if(m_pdataserver != NULL)
      {
         return m_pdataserver->data_server_load(m_dataid, id, idIndex, var);
      }
      return false;
   }

   bool client::data_get(class id id, class id idIndex, int & i)
   {
      if(m_pdataserver != NULL)
      {
         var var;
         if(!m_pdataserver->data_server_load(m_dataid, id, idIndex, var))
            return false;
         if(var.get_type() != var::type_integer)
            return false;
         i = var.m_i;
         return true;
      }
      return false;
   }

   bool client::data_get(class id id, class id idIndex, __int64 & i)
   {
      if(m_pdataserver != NULL)
      {
         var var;
         if(!m_pdataserver->data_server_load(m_dataid, id, idIndex, var))
            return false;
         if(var.get_type() != var::type_integer)
            return false;
         i = var.m_i;
         return true;
      }
      return false;
   }

   bool client::data_get(class id id, class id idIndex, string & str)
   {
      return data_get(m_dataid, id, idIndex, str);
   }

   bool client::data_get(class id dataid, class id id, class id idIndex, string & str)
   {
      if(m_pdataserver != NULL)
      {
         var var;
         if(!m_pdataserver->data_server_load(dataid, id, idIndex, var))
            return false;
         if(var.get_type() != var::type_string)
            return false;
         str = var.m_str;
         return true;
      }
      return false;
   }

   bool client::data_get(class id id, class id idIndex, ex1::writable & writable)
   {
      if(m_pdataserver != NULL)
      {
         if(!m_pdataserver->data_server_load(m_dataid, id, idIndex, writable))
            return false;
         return true;
      }
      return false;
   }

   bool client::data_get(class id id, class id idIndex, ex1::byte_serializable & obj)
   {
      if(m_pdataserver != NULL)
      {
         if(!m_pdataserver->data_server_load(m_dataid, id, idIndex, obj))
            return false;
         return true;
      }
      return false;
   }

   bool client::data_get(class id id, class id idIndex, ex1::byte_output_stream & ostream)
   {
      if(m_pdataserver != NULL)
      {
         if(!m_pdataserver->data_server_load(m_dataid, id, idIndex, ostream))
            return false;
         return true;
      }
      return false;
   }

   bool client::data_get(class id id, class id idIndex, ex1::plain_text_serializable & obj)
   {
      if(m_pdataserver != NULL)
      {
         if(!m_pdataserver->data_server_load(m_dataid, id, idIndex, obj))
            return false;
         return true;
      }
      return false;
   }

   bool client::data_get(class id id, class id idIndex, ex1::plain_text_output_stream & ostream)
   {
      if(m_pdataserver != NULL)
      {
         if(!m_pdataserver->data_server_load(m_dataid, id, idIndex, ostream))
            return false;
         return true;
      }
      return false;
   }

   bool client::data_pulse_change(class id id, class id idIndex, update_hint * puh)
   {
      if(m_pdataserver != NULL)
      {
         if(!m_pdataserver->data_pulse_change(m_dataid, id, idIndex, puh))
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
      for(int i = 0; i < this->get_count(); i++)
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

   int client_array::GetClientCount()
   {
      return this->get_size();
   }

   client * client_array::ClientAt(int iClient)
   {
      return this->element_at(iClient);
   }

   void client_array::RemoveClient(client *pclient)
   {
      remove(pclient);
   }

} // namespace database
