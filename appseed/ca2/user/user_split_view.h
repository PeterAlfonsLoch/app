#pragma once


namespace user
{


   class CLASS_DECL_ca2 split_view :
      virtual public view,
      virtual public split_layout
   {
   public:


      split_view(sp(base_application) papp);
      virtual ~split_view();


      virtual void install_message_handling(::ca2::message::dispatch * pinterface);
      virtual void _001OnDraw(::draw2d::graphics * pdc);
      virtual bool pre_create_window(CREATESTRUCT& cs);
   #ifdef DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif

      DECL_GEN_SIGNAL(_001OnSize)
      DECL_GEN_SIGNAL(_001OnShowWindow)
   };


} // namespace user



