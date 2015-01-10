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
      m_rgbset.set_size(256);


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

#define forall(a) for(decltype(a)::BASE_TYPE & item : a)

   void context::resize(int x,int y)
   {

      if(x <= 0 || y <= 0)
         return;

      m_dib->create(x,y);

      m_dib->Fill(0,0,0,0);

      forall(m_diba)
      {
         
         item.alloc(allocer());
         
         item->create(x,y);
         
         item->Fill(0,0,0,0);

      }

   }


} // namespace turboc