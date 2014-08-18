#pragma once



namespace install
{


   class CLASS_DECL_AXIS trace :
      virtual public object,
      virtual public progress_listener
   {
   public:



      mutex                m_mutex;
      stringa              m_stra;
      HANDLE               m_hfile;
      string               m_strLastStatus;
      string               m_strLastGlsStatus;
      int32_t              m_iLastStatus;
      int32_t              m_iLastGlsStatus;
      
      
      trace(sp(::axis::application) papp);
      virtual ~trace();

      
      bool initialize();

      void finalize();

      void ensure_trace_file();

      virtual void on_trace(string & str, string & str2);

      virtual void rich_trace(const char * psz);

      virtual void trace_add(const char * psz);

      virtual void trace_progress(double dRate);

      virtual void on_progress(double dRate);

      virtual bool isspace_dup(char ch);


   };


} // namespace trace




