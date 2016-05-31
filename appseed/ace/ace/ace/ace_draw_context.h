#pragma once


namespace draw2d
{

   class graphics;


} // namespace draw2d


namespace core
{

   template < class TYPE >
   class simple_chain :
      virtual public object
   {
   public:


      TYPE * m_pnext;


      simple_chain()
      {
         simple_chain < TYPE > ::m_pnext = NULL;
      }

      void chain(TYPE * p)
      {
         if (simple_chain < TYPE > ::m_pnext == NULL)
         {
            simple_chain < TYPE > ::m_pnext = p;
         }
         else
         {
            simple_chain < TYPE > ::m_pnext->simple_chain < TYPE > ::chain(p);
         }
      }
      void unchain(TYPE * p)
      {
         if (simple_chain < TYPE > ::m_pnext == p)
         {
            simple_chain < TYPE > ::m_pnext = simple_chain < TYPE > ::m_pnext->simple_chain < TYPE > ::m_pnext;
         }
         else
         {
            simple_chain < TYPE > ::m_pnext->simple_chain < TYPE > ::unchain(p);
         }
      }

      TYPE * get_last()
      {
         TYPE * plast = simple_chain < TYPE > ::m_pnext;
         if (plast == NULL)
            return NULL;
         while (plast->simple_chain < TYPE > ::m_pnext != NULL)
         {
            plast = plast->simple_chain < TYPE > ::m_pnext;
         }
         return plast;
      }
   };


} // namespace template




namespace ace
{

   class CLASS_DECL_AURA draw_context :
      public ::core::simple_chain < draw_context >
   {
   public:


      ::draw2d::graphics *    m_pgraphics;
      rect                    m_rectClient;
      rect                    m_rectWindow;
      bool                    m_bListItemHover;
      bool                    m_bListSubItemHover;
      bool                    m_bListItemSelected;
      bool                    m_bFocus;
      draw_context *          m_pdrawcontextNext;


      draw_context();




   };





} // namespace ace
