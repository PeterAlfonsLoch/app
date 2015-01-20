#pragma once


namespace turboc
{


   class CLASS_DECL_TURBOC lite_view:
      virtual public view
   {
   public:


      lite_view(::aura::application * papp);
      virtual ~lite_view();

      virtual void assert_valid() const;

      virtual void dump(dump_context & dumpcontext) const;

      virtual void install_message_handling(::message::dispatch * pdispatch);

      virtual void _001OnDraw(::draw2d::graphics * pdc);

      virtual void on_update(::aura::impact * pSender,LPARAM lHint,object* pHint);

      virtual void turboc_render(::draw2d::graphics * pdcFull);

      DECL_GEN_SIGNAL(_001OnCreate);

      virtual int64_t add_ref();

      virtual int64_t dec_ref();

   };


} // namespace turboc












