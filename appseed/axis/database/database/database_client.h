#pragma once


namespace database
{


   class client;


} // namespace database


namespace file
{


   class CLASS_DECL_AXIS data_trigger_output_stream :
      virtual public byte_stream_memory_buffer
   {
   public:

      ::database::client * m_pclient;
      class ::database::id m_id;

      data_trigger_output_stream(data_trigger_output_stream && d):
         element(d),
         byte_stream_memory_buffer(d)
      {
         m_pclient = d.m_pclient;
         m_id = d.m_id;
         d.m_pclient = NULL;
      }
      data_trigger_output_stream(::database::client * pclient,class ::database::id);
      virtual ~data_trigger_output_stream();


   };


   class CLASS_DECL_AXIS data_trigger_input_stream :
      virtual public byte_stream_memory_buffer
   {
   public:

      //::database::client * m_pclient;
      //class ::database::id m_id;

      data_trigger_input_stream(data_trigger_input_stream && d):
         element(d),
         byte_stream_memory_buffer(d)
      {
      }
      data_trigger_input_stream(::database::client * pclient,class ::database::id);
      virtual ~data_trigger_input_stream();

   };


} // namespace file


namespace database
{


   class client_array;




   class CLASS_DECL_AXIS client :
      virtual public ::object
   {
   public:


      friend class client_array;
      friend class server;


      server *  m_pdataserver;
      id        m_dataid;



      client();
      virtual ~client();


      virtual bool set_data_server(server * pserver);


      void initialize_data_client(server * pserver);

      DECL_GEN_VSIGNAL(data_on_before_change);
      DECL_GEN_VSIGNAL(data_on_after_change);

      //virtual bool data_set(class id, bool b, update_hint * phint = NULL);
      //virtual bool data_set(class id, const char * lpsz, update_hint * puh = NULL);
      //virtual bool data_set(class id, int32_t i, update_hint * puh = NULL);
      //virtual bool data_set(class id, int64_t i, update_hint * puh = NULL);

      //virtual bool data_get(class id, bool & b);
      //virtual bool data_get(class id, string & str);
      //virtual bool data_get(class id, int32_t & i);
      //virtual bool data_get(class id, int64_t & i);

      virtual bool data_set(class id, bool b, update_hint * phint = NULL);
      virtual bool data_set(class id, var & var, update_hint * puh = NULL);
      virtual bool data_set(class id, int32_t i, update_hint * puh = NULL);
      virtual bool data_set(class id, int64_t i, update_hint * puh = NULL);
      virtual bool data_set(class id, const char * lpsz, update_hint * puh = NULL);
      virtual bool data_set(class id, const wchar_t * lpsz, update_hint * puh = NULL);
      virtual bool data_set(class id, ::file::stream_buffer & obj, update_hint * puh = NULL);
      virtual bool data_set(class id, ::file::serializable & obj, update_hint * puh = NULL);
      virtual bool data_set(class id, ::file::input_stream & obj, update_hint * puh = NULL);
//      virtual bool data_set(class id, ::file::serializable & obj, update_hint * puh = NULL);
      //virtual bool data_set(class id, ::core::plain_text_input_stream & obj, update_hint * puh = NULL);
      virtual bool data_set(selection & selection, const char * lpsz, update_hint * puh = NULL);
      virtual bool data_set(selection & selection, var & var, update_hint * puh = NULL);

      //virtual bool data_set(class id dataid, class id,  const char * lpsz, update_hint * puh = NULL);

      inline ::file::data_trigger_output_stream data_set(class id id) { return ::file::data_trigger_output_stream(this,id);  }

      virtual bool data_get(class id,  bool & b);
      virtual bool data_get(class id, var & var);
      virtual bool data_get(class id, int32_t & i);
      virtual bool data_get(class id, int64_t & i);
      virtual bool data_get(class id, string & str);
      virtual bool data_get(class id, ::file::stream_buffer & obj);
      virtual bool data_get(class id, ::file::serializable & obj);
      virtual bool data_get(class id, ::file::output_stream & obj);
//      virtual bool data_get(class id, ::file::serializable & obj);
      //virtual bool data_get(class id, ::core::plain_text_output_stream & obj);
//      virtual bool data_get(class id dataid, class id, string & str);


      inline ::file::data_trigger_input_stream data_get(class id id) { return ::file::data_trigger_input_stream(this,id); }

      virtual bool data_pulse_change(class id, update_hint * puh);



      virtual string calc_key(::database::id & idSection, ::database::id & id);

      virtual id get_data_id(class id id);
      virtual id calc_data_id();
      virtual bool update_data_id();



   };

   class CLASS_DECL_AXIS client_array :
      public ptr_array < client >
   {
   public:


      client_array();
      virtual ~client_array();


      virtual void add_client(client * pclient);
      virtual void RemoveClient(client * pclient);
      client * ClientAt(index iClient);
      ::count GetClientCount();


   };


} // namespace database


