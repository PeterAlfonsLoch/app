#include "framework.h"
#include "src/turboc.h"


namespace turboc
{


   context::context(::aura::application * papp):
      element(papp),
      m_dib(allocer())
   {
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

} // namespace turboc