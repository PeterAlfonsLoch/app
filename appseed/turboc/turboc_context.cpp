#include "framework.h"
//#include "src/turboc.h"


namespace turboc
{


   context::context(::aura::application * papp):
      element(papp),
      m_dib(allocer()),
      m_diba(papp)
   {
      m_diba.set_size(16);
   }

   context::~context()
   {
   }

   bool context::gok()
   {

      return m_dib->area() > 0;

   }

   void context::werase()
   {

      if(!gok())
         return;


      m_dib->Fill(0,0,0,0);


   }

   void context::wrefresh()
   {

   }

   void context::defer_synch()
   {
      if(m_iActivePage == m_iVisualPage)
      {
         m_dib.copy(m_diba[m_iActivePage]);
      }

   }


} // namespace turboc