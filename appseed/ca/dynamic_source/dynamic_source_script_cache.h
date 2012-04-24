#pragma once


namespace dynamic_source
{

   class script;

   class script_cache :
      virtual public ::radix::object
   {
   public:


      critical_section     m_cs;
      map_string_to_ptr    m_map;


      script_cache(::ca::application * papp);
      ~script_cache(void);

      script_manager * m_pmanager;
      script_instance * create_instance(const char * lpcszName);

      void set_all_out_of_date();

      void cache(script * pscript);

      script * get(const char * lpcszName);
      script * register_script(const char * lpcszName, script * pscript);


   };


} // namespace dynamic_source


