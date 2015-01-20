#pragma once


namespace tc4
{


   class CLASS_DECL_APP_CORE_TC4 full_view:
      virtual public view
   {
   public:


      full_view(::aura::application * papp);
      virtual ~full_view();


      virtual void assert_valid() const;

      virtual void dump(dump_context & dumpcontext) const;

      virtual void install_message_handling(::message::dispatch * pdispatch);

      virtual void _001OnDraw(::draw2d::graphics * pdc);

      virtual void on_update(::aura::impact * pSender,LPARAM lHint,object* pHint);

      virtual void tc4_render(::draw2d::graphics * pdcFull);

      DECL_GEN_SIGNAL(_001OnCreate);

   };


} // namespace tc4






