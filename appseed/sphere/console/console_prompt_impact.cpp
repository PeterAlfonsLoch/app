#include "framework.h"



namespace console
{



   prompt_impact::prompt_impact(::aura::application * papp) :
      element(papp)
   {

      m_dwCaretPeriod   = 500;

      m_iNewCh          = 0;
         
   }


   prompt_impact::~prompt_impact()
   {
      
      m_sizeChar.cx = 32;
      m_sizeChar.cy = 32;
      m_iCursor = 0;

   }
      
   
   void prompt_impact::install_message_handling(::message::dispatch * pdispatch)
   {

      ::aura::impact::install_message_handling(pdispatch);

      IGUI_WIN_MSG_LINK(WM_CREATE,pdispatch,this,&prompt_impact::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_KEYDOWN,pdispatch,this,&prompt_impact::_001OnKeyDown);
      IGUI_WIN_MSG_LINK(WM_KEYUP,pdispatch,this,&prompt_impact::_001OnKeyUp);

   }

   
   void prompt_impact::_001OnCreate(::signal_details * pobj)
   {

      SCAST_PTR(::message::create,pcreate,pobj);

      if(pcreate->previous())
         return;


      m_dwCaretPeriod = ::get_tick_count();


   }

   void prompt_impact::_001OnKeyDown(::signal_details * pobj)
   {
      
      SCAST_PTR(::message::key,pkey,pobj);

      m_dwLastCaret = ::get_tick_count();

      string str = Session.user()->keyboard().process_key(pkey->m_ekey);

      if(str.has_char())
      {

         if(m_iNewCh == 0x80000000)
         {
            
            m_iNewCh = str[0];

         }
         else
         {

            m_strCommand += str;

         }

      }

   }

   
   void prompt_impact::_001OnKeyUp(::signal_details * pobj)
   {

      UNREFERENCED_PARAMETER(pobj);

   }


   int prompt_impact::getch()
   {

      m_dwCaretPeriod = ::get_tick_count();

      m_iNewCh = 0x80000000;

      while(m_iNewCh == 0x80000000)
      {
         Sleep(84);
      }

      return m_iNewCh;
   }

   int prompt_impact::ungetch(int c)
   {

      return 0;
       
   }


   void prompt_impact::_001OnDraw(::draw2d::graphics * pgraphics)
   {

      DWORD dwAlpha = 184;

      bool bCaretOn = ((::get_tick_count() - m_dwLastCaret) % m_dwCaretPeriod) < (m_dwCaretPeriod / 2);

      ::rect rectClient;

      GetClientRect(rectClient);

      pgraphics->FillSolidRect(rectClient,ARGB(dwAlpha,255,255,255));

      for(int i = 0; i < m_strCommand.length(); i++)
      {

         pgraphics->TextOut(m_sizeChar.cx *i, 0,m_strCommand.Mid(i,1));

      }

      ::rect rectCaret;

      rectCaret.left = m_sizeChar.cx * m_iCursor;
      rectCaret.right = rectCaret.left + m_sizeChar.cx;
      rectCaret.left = m_sizeChar.cy-3;
      rectCaret.bottom = m_sizeChar.cy;

       

      pgraphics->FillSolidRect(rectCaret,ARGB(dwAlpha,0,0,0));

   }
   

   bool prompt_impact::keyboard_focus_is_focusable()
   {

      return true;

   }


} // namespace console








































