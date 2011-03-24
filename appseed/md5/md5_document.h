// Alá Telmo Friesen Son God Document
// translucid click-through window
// applications:
//    non-intrusive md5
//    non-intrusive notifications

#pragma once

namespace md5
{

   class CLASS_DECL_CA2_MD5 document :
      public ::userbase::document
   {
   public:

      class thread :
         virtual public simple_thread
      {
      public:

         
         double   m_dProgress;
         string   m_strFile;
         bool     m_bReady;
         string   m_strMd5;


         thread(::ca::application * papp);

         int run();
      };


      string m_strCheckMd5;
      thread m_thread;

      document(::ca::application * papp);
	   virtual ~document();
	   
      DECL_GEN_VSIGNAL(data_on_after_change);

   #ifdef _DEBUG
	   virtual void assert_valid() const;
	   virtual void dump(dump_context& dc) const;
   #endif

	   virtual BOOL on_new_document();
      virtual bool on_open_document(var varFile);

   };

} // namespace md5