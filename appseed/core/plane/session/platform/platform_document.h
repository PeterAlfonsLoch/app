#pragma once


namespace bergedge
{


   class document;


} // namespace bergedge


namespace platform
{


   class view;
   class pane_view;
   class frame;


   class CLASS_DECL_CORE document :
      public form_document
   {
   public:


      sp(::bergedge::document) m_pbergedgedocument;


      document(sp(base_application) papp);
      virtual ~document();


      sp(view)                  get_platform_view();
      sp(pane_view)             get_platform_pane_view();
      sp(frame)                 get_platform_frame();
      
      

      virtual bool on_new_document();



   #ifdef DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif


      DECL_GEN_VSIGNAL(data_on_after_change);


   };


} // namespace platform



