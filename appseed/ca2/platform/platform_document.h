#pragma once


namespace bergedge
{


   class document;
   class bergedge;


} // namespace bergedge


namespace platform
{


   class view;
   class pane_view;
   class frame;


   class CLASS_DECL_ca2 document :
      public form_document
   {
   public:


      sp(::bergedge::document) m_pbergedgedocument;


      document(::ca::applicationsp papp);
      virtual ~document();


      view *                  get_platform_view();
      pane_view *             get_platform_pane_view();
      frame *                 get_platform_frame();
      bergedge::bergedge *    get_bergedge();
      
      

      virtual bool on_new_document();



   #ifdef DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif


      DECL_GEN_VSIGNAL(data_on_after_change)


   };


} // namespace platform



