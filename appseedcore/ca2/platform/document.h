#pragma once

namespace bergedge
{
   class document;
   class bergedge;
} // namespace bergedge

namespace platform
{

   class view;
   class frame;

   class CLASS_DECL_ca document :
      public form_document
   {
   public:


      bergedge::document * m_pbergedgedocument;


      document(::ca::application * papp);
      virtual ~document();

      view *                  get_platform_view();
      frame *                 get_platform_frame();
      bergedge::bergedge *    get_bergedge();
      
      

      virtual BOOL on_new_document();
      


      DECL_GEN_VSIGNAL(data_on_after_change)


   #ifdef _DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif


   };


} // namespace platform