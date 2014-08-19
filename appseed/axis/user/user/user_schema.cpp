#include "framework.h"


namespace user
{


   schema::schema()
   {

      m_puserschema = NULL;

   }

   schema::~schema()
   {

   }


   bool schema::get_color(COLORREF & cr, e_color ecolor)
   {

      if(m_puserschema != NULL && m_puserschema != this)
      {

         if(m_puserschema->get_color(cr,ecolor))
            return true;

      }

      if(get_parent_user_schema() != NULL)
      {

         if(get_parent_user_schema()->get_color(cr,ecolor))
            return true;

      }

      if(m_paxisapp != NULL && m_paxisapp->m_paxissession != NULL && m_paxisapp->m_paxissession != m_puserschema && m_paxisapp->m_paxissession->m_puserschema != m_puserschema)
      {

         if(m_paxisapp->m_paxissession->get_color(cr,ecolor))
            return true;

      }

      return false;

   }

   bool schema::get_font(::draw2d::font_sp & spfont)
   {

      if(m_puserschema != NULL && m_puserschema != this)
      {

         if(m_puserschema->get_font(spfont))
            return true;

      }

      if(get_parent_user_schema() != NULL)
      {

         if(get_parent_user_schema()->get_font(spfont))
            return true;

      }

      if(m_paxisapp != NULL && m_paxisapp->m_paxissession != NULL && m_paxisapp->m_paxissession != m_puserschema && m_paxisapp->m_paxissession->m_puserschema != m_puserschema)
      {

         if(m_paxisapp->m_paxissession->get_font(spfont))
            return true;

      }

      return false;

   }

   bool schema::get_translucency(ETranslucency & etranslucency)
   {

      if(m_puserschema != NULL && m_puserschema != this)
      {

         if(m_puserschema->get_translucency(etranslucency))
            return true;

      }

      if(get_parent_user_schema() != NULL)
      {

         if(get_parent_user_schema()->get_translucency(etranslucency))
            return true;

      }

      if(m_paxisapp != NULL && m_paxisapp->m_paxissession != NULL && m_paxisapp->m_paxissession != m_puserschema && m_paxisapp->m_paxissession->m_puserschema != m_puserschema)
      {

         if(m_paxisapp->m_paxissession->get_translucency(etranslucency))
            return true;

      }

      return false;

   }

   COLORREF schema::_001GetColor(e_color ecolor,COLORREF crDefault)
   {

      COLORREF cr;

      if(get_color(cr,ecolor))
         return cr;

      return crDefault;

   }

   COLORREF schema::_001GetColor(e_color ecolor)
   {

      COLORREF cr;

      if(get_color(cr, ecolor))
         return cr;

      if(ecolor == color_text)
      {

         return ARGB(255,0,0,0);

      }
      else if(ecolor == color_text_selected)
      {

         return ARGB(255,255,255,255);

      }
      else if(ecolor == color_text_highlight)
      {

         return ARGB(255,55,105,255);

      }
      else if(ecolor == color_text_selected_highlight)
      {

         return ARGB(255,102,153,255);

      }
      else if(ecolor == color_background)
      {

         if(_001IsTranslucent())
         {

            return ARGB(184,255,255,255);

         }
         else
         {

            return ARGB(255,255,255,255);

         }

      }
      else if(ecolor == color_background_selected)
      {

         if(_001IsTranslucent())
         {

            return ARGB(184,0,0,127);

         }
         else
         {

            return ARGB(255,0,0,127);

         }

      }
      else if(ecolor == color_background_selected)
      {

         if(_001IsTranslucent())
         {

            return ARGB(184,0,0,127);

         }
         else
         {

            return ARGB(255,0,0,127);

         }

      }
      else if(ecolor == color_border_normal)
      {

         return ARGB(255,84,84,77);

      }




      throw invalid_argument_exception(::get_thread_app());

   }


   ETranslucency schema::_001GetTranslucency(ETranslucency etranslucencyDefault)
   {

      ETranslucency etranslucency;

      if(get_translucency(etranslucency))
         return etranslucency;

      return etranslucencyDefault;


   }



   bool schema::_001IsTranslucent()
   {

      ETranslucency etranslucency = _001GetTranslucency();

      return etranslucency == TranslucencyPresent || etranslucency == TranslucencyTotal;

   }


   bool schema::_001IsBackgroundBypass()
   {

      return _001GetTranslucency() == TranslucencyTotal;

   }


   bool schema::_001HasTranslucency()
   {

      ETranslucency etranslucency = _001GetTranslucency();

      return etranslucency == TranslucencyPresent || etranslucency == TranslucencyTotal;

   }


   bool schema::_001IsTransparent()
   {

      return _001GetTranslucency() == TranslucencyTotal;

   }


   ::user::schema * schema::get_user_schema()
   {

      if(m_puserschema != NULL)
      {

         return m_puserschema;

      }

      return get_parent_user_schema();

   }


   ::user::schema * schema::get_parent_user_schema()
   {

      return NULL;

   }


   bool schema::select_layered_frame()
   {


      
      m_puserschema = System.m_pschemaLayeredFrame;

      return true;

   }



   bool schema::select_text_color(::draw2d::graphics * pgraphics,e_color ecolor)
   {

      COLORREF crText;

      if(!get_color(crText,ecolor))
         return false;

      return pgraphics->set_text_color(crText);

   }

   
   bool schema::select_font(::draw2d::graphics * pgraphics)
   {

      ::draw2d::font_sp spfont;

      if(!get_font(spfont))
         return false;

      if(spfont.is_null())
         return false;

      return pgraphics->set_font(spfont);

   }




} // namespace user





