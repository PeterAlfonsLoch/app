#pragma once



namespace database
{

   
   class id;

   
   class CLASS_DECL_BASE server :
      public client_array
   {
   public:


      bool                    m_bRemote;



      virtual bool data_server_load       (client * pclient, class id idSection, class id id, class id idIndex, ::file::stream_buffer & obj, update_hint * phint = NULL);

      virtual bool data_server_load       (client * pclient, class id idSection, class id id, class id idIndex, var & var, update_hint * phint = NULL);
      virtual bool data_server_load       (client * pclient, class id idSection, class id id, class id idIndex, ::file::output_stream & ostream, update_hint * phint = NULL);
      virtual bool data_server_load       (client * pclient, class id idSection, class id id, class id idIndex, ::file::serializable & obj, update_hint * phint = NULL);
//      virtual bool data_server_load       (client * pclient, class id idSection, class id id, class id idIndex, ::core::plain_text_output_stream & ostream, update_hint * phint = NULL);
//      virtual bool data_server_load       (client * pclient, class id idSection, class id id, class id idIndex, ::file::serializable & obj, update_hint * phint = NULL);
      
      
      


      virtual bool data_server_save       (client * pclient, class id idSection, class id id, class id idIndex, ::file::stream_buffer & obj, update_hint * phint = NULL);

      virtual bool data_server_save       (client * pclient, class id idSection, class id id, class id idIndex, var & var, update_hint * phint = NULL);
      virtual bool data_server_save       (client * pclient, class id idSection, class id id, class id idIndex, ::file::input_stream & istream, update_hint * phint = NULL);
      virtual bool data_server_save       (client * pclient, class id idSection, class id id, class id idIndex, ::file::serializable & obj, update_hint * phint = NULL);
//      virtual bool data_server_save       (client * pclient, class id idSection, class id id, class id idIndex, ::core::plain_text_input_stream & istream, update_hint * phint = NULL);
//      virtual bool data_server_save       (client * pclient, class id idSection, class id id, class id idIndex, ::file::serializable & obj, update_hint * phint = NULL);





      virtual bool var_load               (client * pclient, class id idSection, class id id, class id idIndex, ::file::output_stream & obj, update_hint * phint = NULL);
      virtual bool var_save               (client * pclient, class id idSection, class id id, class id idIndex, ::file::input_stream & obj, update_hint * phint = NULL);


      virtual bool data_pulse_change      (client * pclient, class id idSection, class id id, class id idIndex, update_hint * puh = NULL);

      virtual bool on_before_data_change  (client * pclient, class id idSection, class id id, class id idIndex, var & varNew, update_hint * puh = NULL);
      virtual bool on_after_data_change   (client * pclient, class id idSection, class id id, class id idIndex, update_hint * puh = NULL);

      virtual var data_load               (client * pclient, class id idSection, class id id, class id idIndex, update_hint * phint = NULL);
      virtual bool data_save              (client * pclient, class id idSection, class id id, class id idIndex, var var, update_hint * phint = NULL);
   };

   
} // namespace database



