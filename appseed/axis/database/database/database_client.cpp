//#include "framework.h"


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
      return data_set(id, i, phint);
   }


   bool client::data_set(
      class id id,
      
      var & var,
      update_hint * puh)
   {
      if(m_pdataserver != NULL)
      {
         return m_pdataserver->data_server_save(this, id, var, puh);
      }
      return false;
   }

   bool client::data_set(class id id, int32_t i, update_hint * puh)
   {
      if(m_pdataserver != NULL)
      {
         var var(i);
         return m_pdataserver->data_server_save(this, id, var, puh);
      }
      return false;
   }

   bool client::data_set(class id id, int64_t i, update_hint * puh)
   {
      if(m_pdataserver != NULL)
      {
         var var(i);
         return m_pdataserver->data_server_save(this, id, var, puh);
      }
      return false;
   }



   bool client::data_set(class id id, const char * lpsz, update_hint * puh)
   {
      if(m_pdataserver != NULL)
      {
         var var;
         var = lpsz;
         return m_pdataserver->data_server_save(this, id, var, puh);
      }
      return false;
   }

   bool client::data_set(class id id, const char16_t * lpsz, update_hint * puh)
   {
      if(m_pdataserver != NULL)
      {
         var var;
         var = lpsz;
         return m_pdataserver->data_server_save(this, id, var, puh);
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
         if(!data_set(item.m_id, lpsz, puh))
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
         if(!data_set(item.m_id,var,puh))
         {
            bOk = false;
         }

      }
      return bOk;
   }

   bool client::data_set(class id id, ::file::stream_buffer & readable, update_hint * puh)
   {
      if(m_pdataserver != NULL)
      {
         return m_pdataserver->data_server_save(this, id, readable, puh);
      }
      return false;
   }

   bool client::data_set(class id id, ::file::serializable & obj, update_hint * puh)
   {
      if(m_pdataserver != NULL)
      {
         if(!m_pdataserver->data_server_save(this, id, obj, puh))
            return false;
         return true;
      }
      return false;
   }

   bool client::data_set(class id id, ::file::istream & istream, update_hint * puh)
   {
      if(m_pdataserver != NULL)
      {
         return m_pdataserver->data_server_save(this, id, istream, puh);
      }
      return false;
   }


   bool client::data_get(class id id, bool & b)
   {
      int32_t i;
      if(!data_get(id, i))
         return false;
      b = i != 0;
      return true;
   }


   bool client::data_get(class id id, var & var)
   {
      if(m_pdataserver != NULL)
      {
         return m_pdataserver->data_server_load(this, id, var);
      }
      return false;
   }

   bool client::data_get(class id id, int32_t & i)
   {
      if(m_pdataserver != NULL)
      {
         var var;
         if(!m_pdataserver->data_server_load(this, id, var))
            return false;
         i = var;
         return true;
      }
      return false;
   }

   bool client::data_get(class id id, int64_t & i)
   {
      if(m_pdataserver != NULL)
      {
         var var;
         if(!m_pdataserver->data_server_load(this, id, var))
            return false;
         i = var;
         return true;
      }
      return false;
   }

   bool client::data_get(class id id, string & str)
   {
      if(m_pdataserver != NULL)
      {
         var var;
         if(!m_pdataserver->data_server_load(this, id, var))
            return false;
         if(var.get_type() != var::type_string)
            return false;
         str = var.m_str;
         return true;
      }
      return false;
   }

   bool client::data_get(class id id, ::file::stream_buffer & writable)
   {
      if(m_pdataserver != NULL)
      {
         if(!m_pdataserver->data_server_load(this, id, writable))
            return false;
         return true;
      }
      return false;
   }

   bool client::data_get(class id id, ::file::serializable & obj)
   {
      if(m_pdataserver != NULL)
      {
         if(!m_pdataserver->data_server_load(this, id, obj))
            return false;
         return true;
      }
      return false;
   }

   bool client::data_get(class id id, ::file::ostream & ostream)
   {
      if(m_pdataserver != NULL)
      {
         if(!m_pdataserver->data_server_load(this, id, ostream))
            return false;
         return true;
      }
      return false;
   }

   
   bool client::data_pulse_change(class id id, update_hint * puh)
   {
      if(m_pdataserver != NULL)
      {
         if(!m_pdataserver->data_pulse_change(this, id, puh))
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

   string client::calc_data_key(::database::id & id)
   {
      string str;
      str = get_data_id().m_id;
      str += ".";
      str += id.m_id;
      return str;
   }


   id client::get_data_id()
   {

      return m_dataid;

   }

   string client::calc_data_id()
   {

      return "";

   }


   void client::defer_update_data_id()
   {

      if(m_dataid.m_id.is_empty())
      {

         m_dataid = calc_data_id();

      }

   }


} // namespace database



namespace file
{

   data_trigger_ostream::data_trigger_ostream(data_trigger_ostream && d):
      byte_stream_memory_buffer((byte_stream_memory_buffer &&)d)
   {
      m_pclient = d.m_pclient;
      m_id = d.m_id;
      d.m_pclient = NULL;
   }

   data_trigger_ostream::data_trigger_ostream(::database::client * pclient,class ::database::id id) :
      ::object(pclient->get_app()),
      byte_stream_memory_buffer(pclient->get_app())
   {

      m_id = id;
      m_pclient = pclient;

   }
   
   data_trigger_ostream::~data_trigger_ostream()
   {
   
      if(m_pclient != NULL)
      {
         seek_to_begin();
         m_pclient->data_set(m_id,(::file::istream &)*this);

      }
   
   }

   data_trigger_istream::data_trigger_istream(data_trigger_istream && d):
      byte_stream_memory_buffer((byte_stream_memory_buffer &&) d)
   {
   }

   data_trigger_istream::data_trigger_istream(::database::client * pclient,class ::database::id id) :
      ::object(pclient->get_app()),
      byte_stream_memory_buffer(pclient->get_app())
   {
      
      pclient->data_get(id,(::file::ostream &)*this);
      seek_to_begin();
   }

   data_trigger_istream::~data_trigger_istream()
   {

   }


} // namespace file


