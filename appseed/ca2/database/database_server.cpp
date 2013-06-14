#include "framework.h"


namespace database
{


   bool server::data_server_load(client * pclient, class id idSection, class id id, class id idIndex, ::ca2::writable & writable, update_hint * puh)
   {
      return var_load(pclient, idSection, id, idIndex, writable, puh);
   }

   bool server::data_server_load(client * pclient, class id idSection, class id id, class id idIndex, var & var   , update_hint * puh)
   {
      ::ca2::byte_stream_memory_file memfile(get_app());
      if(!data_server_load(pclient, idSection, id, idIndex, memfile, puh))
         return false;
      try
      {
         memfile.seek_to_begin();
         memfile >> var;
      }
      catch(...)
      {
         return false;
      }
      return true;
   }

   bool server::data_server_load(client * pclient, class id idSection, class id id, class id idIndex, ::ca2::byte_output_stream & ostream, update_hint * puh)
   {
      return data_server_load(pclient, idSection, id, idIndex, (::ca2::writable &) ostream, puh);
   }

   bool server::data_server_load(client * pclient, class id idSection, class id id, class id idIndex, ::ca2::plain_text_output_stream & ostream, update_hint * puh)
   {
      return data_server_load(pclient, idSection, id, idIndex, (::ca2::writable &) ostream, puh);
   }

   bool server::data_server_load(client * pclient, class id idSection, class id id, class id idIndex, ::ca2::byte_serializable & obj, update_hint * puh)
   {
      ::ca2::byte_stream_memory_file memfile(get_app());
      if(!data_server_load(pclient, idSection, id, idIndex, memfile, puh))
         return false;
      try
      {
         memfile.seek_to_begin();
         obj.read(memfile);
      }
      catch(...)
      {
         return false;
      }
      return memfile.get_position() == memfile.get_length();
   }

   bool server::data_server_load(client * pclient, class id idSection, class id id, class id idIndex, ::ca2::plain_text_serializable & obj, update_hint * puh)
   {
      _template_std_stringstream strstream;
      if(!data_server_load(pclient, idSection, id, idIndex, strstream, puh))
         return false;
      try
      {
         strstream.m_dwPos = 0;
         obj.read(strstream);
      }
      catch(const char * psz)
      {
         TRACE("database::server::data_server_load : %s", psz);
         return false;
      }
      catch(...)
      {
         return false;
      }
      return true;
   }

   bool server::data_server_save(client * pclient, class id idSection, class id id, class id idIndex, ::ca2::readable & readable, update_hint * puh)
   {
      return var_save(pclient, idSection, id, idIndex, readable, puh);
   }

   bool server::data_server_save(client * pclient, class id idSection, class id id, class id idIndex, var & var   , update_hint * puh)
   {
      ::ca2::byte_stream_memory_file memfile(get_app());
      memfile << var;
      memfile.seek_to_begin();
      if(!data_server_save(pclient, idSection, id, idIndex, memfile, puh))
         return false;
      return true;
   }

   bool server::data_server_save(client * pclient, class id idSection, class id id, class id idIndex, ::ca2::byte_input_stream & istream, update_hint * puh)
   {
      return data_server_save(pclient, idSection, id, idIndex, (::ca2::readable &) istream, puh);
   }

   bool server::data_server_save(client * pclient, class id idSection, class id id, class id idIndex, ::ca2::plain_text_input_stream & istream, update_hint * puh)
   {
      return data_server_save(pclient, idSection, id, idIndex, (::ca2::readable &) istream, puh);
   }

   bool server::data_server_save(client * pclient, class id idSection, class id id, class id idIndex, ::ca2::byte_serializable & obj, update_hint * puh)
   {
      ::ca2::byte_stream_memory_file memfile(get_app());
      obj.write(memfile);
      memfile.seek_to_begin();
      if(!data_server_save(pclient, idSection, id, idIndex, memfile, puh))
         return false;
      return true;
   }

   bool server::data_server_save(client * pclient, class id idSection, class id id, class id idIndex, ::ca2::plain_text_serializable & obj, update_hint * puh)
   {
      _template_std_stringstream strstream;
      obj.write(strstream);
      strstream.m_dwPos = 0;
      if(!data_server_save(pclient, idSection, id, idIndex, strstream, puh))
         return false;
      return true;
   }

   bool server::data_pulse_change(client * pclient, class id idSection, class id key, class id idIndex, update_hint * puh)
   {
      return on_after_data_change(pclient, idSection, key, idIndex, puh);
   }


   bool server::on_before_data_change(client * pclient, class id idSection, class id key, class id idIndex, var & var, update_hint * puh)
   {
      ::database::change_event signal(var);
      signal.m_pserver = this;
      signal.m_key.m_pclient = pclient;
      signal.m_key.m_idSection = idSection;
      signal.m_key.m_idKey = key;
      signal.m_key.m_idIndex = idIndex;
      signal.m_puh = puh;
      for(int32_t i = 0; i < client_array::get_count(); i++)
      {
         client_array::element_at(i)->data_on_before_change(&signal);
         if(!signal.m_bOk)
            return false;

      }
      return true;
   }

   bool server::on_after_data_change(client * pclient, class id idSection, class id key, class id idIndex, update_hint * puh)
   {
      ::database::change_event signal;
      signal.m_pserver       = this;
      signal.m_key.m_pclient     = pclient;
      signal.m_key.m_idSection   = idSection;
      signal.m_key.m_idKey       = key;
      signal.m_key.m_idIndex     = idIndex;
      signal.m_puh = puh;
      for(int32_t i = 0; i < client_array::get_count(); i++)
      {
         client_array::element_at(i)->data_on_after_change(&signal);
      }
      return true;
   }

   var server::data_load(client * pclient, class id idSection, class id id, class id idIndex, update_hint * phint)
   {
      var var;
      if(data_server_load(pclient, idSection, id, idIndex, var, phint))
         return var;
      return ::var(::var::type_new);
   }

   bool server::data_save(client * pclient, class id idSection, class id id, class id idIndex, var var, update_hint * phint)
   {
      return data_server_save(pclient, idSection, id, idIndex, var, phint);
   }

   bool server::var_load(client * pclient, class id idSection, class id id, class id idIndex, ::ca2::writable & writable, update_hint * puh)
   {
      var var;
      if(!data_server_load(pclient, idSection, id, idIndex, var, puh))
         return false;
      ::ca2::byte_output_stream ostream(&writable);
      var.write(ostream);
      return true;
   }

   bool server::var_save(client * pclient, class id idSection, class id id, class id idIndex, ::ca2::readable & readable, update_hint * puh)
   {
      var var;
      ::ca2::byte_input_stream istream(&readable);
      var.read(istream);
      if(!data_server_save(pclient, idSection, id, idIndex, var, puh))
         return false;
      return true;
   }


} // namespace database
