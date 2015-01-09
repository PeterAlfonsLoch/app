#pragma once

namespace turboc
{



   class CLASS_DECL_TURBOC context:
      virtual public ::object
   {
   public:



      ::draw2d::dib_sp           m_dib;

      context(::aura::application * papp);
      virtual ~context();

      bool gok();

      void werase();
      void wrefresh();

   };

   CLASS_DECL_TURBOC void set_context(::turboc::context * pcontext);

} // namespace turboc

