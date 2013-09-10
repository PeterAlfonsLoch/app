#pragma once


enum e_application_signal
{
   application_signal_initialize1, // cgcl // first initialization
   application_signal_initialize2, // cst  // second initialization
   application_signal_initialize3, // third initialization and so on...
   application_signal_initialize, // last initialization
   application_signal_start,
   application_signal_process_initialize,
   application_signal_finalize,
   application_signal_exit_instance,
   application_signal_init_application,
   application_signal_none,
};


class CLASS_DECL_c application_signal_details :
   public signal_details
{
public:


   e_application_signal             m_esignal;
   int32_t                          m_iRet;
   bool                             m_bOk;


   application_signal_details(sp(base_application) papp, class ::signal * psignal, e_application_signal esignal);


};



class CLASS_DECL_c base_application :
   virtual public base_thread
{
public:


   class signal *                                  m_psignal;
   base_system *                                   m_pbasesystem;
   string                                          m_strAppName;
   sp(::command_thread)                            m_pcommandthread;
   allocatorsp                                     m_allocer;
   ::plane::application *                          m_pplaneapp; // can be used only from core and upper




   base_application();
   virtual ~base_application();


   virtual sp(base_element) alloc(sp(type) info);
   virtual sp(base_element) alloc(const id & idType);


   int32_t simple_message_box(const char * pszMessage, UINT fuStyle);


   virtual bool load_string(string & str, id id);

   virtual bool is_system();

//   virtual string matter_as_string(const char * pszMatter, const char * pszMatter2 = NULL);
//   virtual string dir_matter(const char * pszMatter, const char * pszMatter2 = NULL);
   virtual bool is_inside_time_dir(const char * pszPath);
   virtual bool file_is_read_only(const char * pszPath);
   virtual string file_as_string(var varFile);
   virtual string dir_path(const char * psz1, const char * psz2, const char * psz3 = NULL);
   virtual string dir_name(const char * psz);
   virtual bool dir_mk(const char * psz);
   virtual string file_title(const char * psz);
   virtual string file_name(const char * psz);

   ::file::binary_buffer_sp file_get_file(var varFile, uint32_t uiFlags);


   // Wall-eeeeee aliases
   sp(::command_thread) command_central();
   sp(::command_thread) command_thread();
   sp(::command_thread) guideline();
   sp(::command_thread) command();
   sp(::command_thread) directrix();
   sp(::command_thread) axiom();
   sp(::command_thread) creation();

   //virtual void on_allocation_error(const sp(type) info);
   //virtual sp(base_element) on_alloc(const sp(type) info);

   virtual bool verb();



};


inline allocatorsp base_element::allocer()
{
   return m_pbaseapp->m_allocer;
}



inline sp(::command_thread) object::command_thread()
{

   return m_pbaseapp->command_thread();

}
