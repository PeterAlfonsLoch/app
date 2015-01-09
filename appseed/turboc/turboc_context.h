#pragma once

namespace turboc
{



   class CLASS_DECL_TURBOC context:
      virtual public ::object
   {
   public:



      ::draw2d::dib_sp           m_dib;
      spa(::draw2d::dib)         m_diba;

      int m_iDriver;
      int m_iActivePage;
      int m_iVisualPage;



      context(::aura::application * papp);
      virtual ~context();

      bool gok();

      void werase();
      void wrefresh();

      void defer_synch();


      ::draw2d::dib & adib() { return *m_diba[m_iActivePage]; }
      ::draw2d::graphics & ag() { return *adib().get_graphics(); }

      spa(::draw2d::dib) & Pixmaps() { return m_diba; }

   };

   CLASS_DECL_TURBOC void set_context(::turboc::context * pcontext);

} // namespace turboc

