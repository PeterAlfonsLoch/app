#pragma once



namespace database
{


   class id;


   class CLASS_DECL_AXIS server :
      public client_array
   {
   public:


      bool                    m_bRemote;


      server(::aura::application * papp);
      virtual ~server();



      virtual bool data_server_load       (client * pclient, class id id, ::file::stream_buffer & obj, update_hint * phint = NULL);

      virtual bool data_server_load       (client * pclient, class id id, var & var, update_hint * phint = NULL);
      virtual bool data_server_load       (client * pclient, class id id, ::file::ostream & ostream, update_hint * phint = NULL);
      virtual bool data_server_load       (client * pclient, class id id, ::file::serializable & obj, update_hint * phint = NULL);
//      virtual bool data_server_load       (client * pclient, class id id, ::core::plain_text_ostream & ostream, update_hint * phint = NULL);
//      virtual bool data_server_load       (client * pclient, class id id, ::file::serializable & obj, update_hint * phint = NULL);





      virtual bool data_server_save       (client * pclient, class id id, ::file::stream_buffer & obj, update_hint * phint = NULL);

      virtual bool data_server_save       (client * pclient, class id id, var & var, update_hint * phint = NULL);
      virtual bool data_server_save       (client * pclient, class id id, ::file::istream & istream, update_hint * phint = NULL);
      virtual bool data_server_save       (client * pclient, class id id, ::file::serializable & obj, update_hint * phint = NULL);
//      virtual bool data_server_save       (client * pclient, class id id, ::core::plain_text_istream & istream, update_hint * phint = NULL);
//      virtual bool data_server_save       (client * pclient, class id id, ::file::serializable & obj, update_hint * phint = NULL);





      virtual bool var_load               (client * pclient, class id id, ::file::ostream & obj, update_hint * phint = NULL);
      virtual bool var_save               (client * pclient, class id id, ::file::istream & obj, update_hint * phint = NULL);


      virtual bool data_pulse_change      (client * pclient, class id id, update_hint * puh = NULL);

      virtual bool on_before_data_change  (client * pclient, class id id, var & varNew, update_hint * puh = NULL);
      virtual bool on_after_data_change   (client * pclient, class id id, update_hint * puh = NULL);

      virtual var data_load               (client * pclient, class id id, update_hint * phint = NULL);
      virtual bool data_save              (client * pclient, class id id, var var, update_hint * phint = NULL);
   };


} // namespace database



