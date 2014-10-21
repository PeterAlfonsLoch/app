#include "framework.h"


bool ishexdigit(char ch);


bool ishexdigit(char ch)
{
   if(ch >= '0' && ch <= '9')
      return true;
   if(ch >= 'a' && ch <= 'f')
      return true;
   if(ch >= 'A' && ch <= 'F')
      return true;
   return false;
}


namespace html
{


   style::style(sp(::aura::application) papp) :
      element(papp)
   {

      m_edisplay = display_inline;

   }

   style::style(const style & style)
   {
      operator = (style);
   }

   style & style::operator = (const style & style)
   {
      if(this != &style)
      {
         m_etag         = style.m_etag;
         m_strName      = style.m_strName;
         m_strSubClass  = style.m_strSubClass;
         m_propertyset  = style.m_propertyset;
      }
      return *this;
   }

#define n_to_b(nible) ((nible << 4) | (nible))

   COLORREF style::parse_color(const char * psz)
   {
      string str(psz);
      str.trim();
      str += " ";
      if(str.Left(1) == "#" && str.get_length() >= 7 && ishexdigit(str[1]) && ishexdigit(str[2]) && ishexdigit(str[3]) && ishexdigit(str[4])
          && ishexdigit(str[5]) && ishexdigit(str[6]))
      {
         if(str.get_length() >= 9 && ishexdigit(str[7]) && ishexdigit(str[8]) && !ishexdigit(str[9]))
         {
            int32_t a, r, g, b;
            sscanf(str, "#%02x%02x%02x%02x", &a, &r, &g, &b);
            return ARGB(a, r, g, b);
         }
         else if(!ishexdigit(str[7]))
         {
            int32_t r, g, b;
            sscanf(str, "#%02x%02x%02x", &r, &g, &b);
            return ARGB(255, r, g, b);
         }
      }
      else if(str.Left(1) == "#" && str.get_length() >= 4 && ishexdigit(str[1]) && ishexdigit(str[2]) && ishexdigit(str[3]))
      {
         if(str.get_length() >= 5 && ishexdigit(str[4]) && !ishexdigit(str[5]))
         {
            int32_t a, r, g, b;
            sscanf(str, "#%1x%1x%1x%1x", &a, &r, &g, &b);
            return ARGB(n_to_b(a),n_to_b(r),n_to_b(g),n_to_b(b));
         }
         else if(!ishexdigit(str[4]))
         {
            int32_t r, g, b;
            sscanf(str, "#%1x%1x%1x", &r, &g, &b);
            return ARGB(255,n_to_b(r),n_to_b(g),n_to_b(b));
         }
      }
      else if(::str::begins_eat_ci(str, "rgb") || ::str::begins_eat_ci(str, "argb"))
      {
         str.trim();
         if(::str::begins_eat_ci(str, "("))
         {
            str.trim();
            if(::str::ends_eat_ci(str, ")"))
            {
               str.trim();
               var a;
               a.stra().explode(",", str);
               int_array & ia = a.inta();
               if(ia.get_count() == 3)
               {
                  return ARGB(255, ia[0], ia[1], ia[2]);
               }
               else if(ia.get_count() == 4)
               {
                  return ARGB(ia[0], ia[1], ia[2], ia[3]);
               }
            }
         }
      }
      return 0;
   }

   bool style::get_dimension(bool bParent, id idName, const string & strSubClass, data * pdata, elemental * pelemental, float & f)
   {

      f = 0.f;

      e_tag etag = pelemental->m_etag;

      string strClass = pelemental->m_strClass;

      if(m_propertyset.is_new_or_null(idName))
      {

         style * pstyle = pdata->m_stylesheeta.rfind(etag, strClass, strSubClass, idName);

         if(pstyle == NULL)
         {

            if(bParent)
            {

               if(pelemental->m_pparent != NULL && stricmp_dup(idName, "background-color"))
               {

                  if(pelemental->m_pparent->m_style.get_dimension(true, idName, strSubClass, pdata, pelemental->m_pparent, f))
                  {

                     return true;

                  }

               }

            }

            return false;

         }

         return pstyle->get_dimension(bParent, idName, strSubClass, pdata, pelemental, f);

      }

      f = parse_dimension(m_propertyset[idName]);

      return true;

   }


   bool style::get_surround_box(id idName, const string & strSubClass, data * pdata, elemental * pelemental, box & box)
   {
      
      e_tag etag = pelemental->m_etag;
      
      string strClass = pelemental->m_strClass;
      
      style * pstyleCur = NULL;
      style * pstyle = NULL;
      style * pstyleLeft = NULL;
      style * pstyleTop = NULL;
      style * pstyleRight = NULL;
      style * pstyleBottom = NULL;
      index i = 0;
      index iLeft = 0;
      index iTop = 0;
      index iRight = 0;
      index iBottom = 0;

      if(m_propertyset.has_property(idName))
         pstyle = this;
      else
         pstyle = pdata->m_stylesheeta.rfind(etag, strClass, strSubClass, idName);

      if(pstyle != NULL)
         i = pstyle->m_propertyset.find_index(idName);

      if(m_propertyset.has_property(m_pauraapp->m_pcoresystem->m_phtml->concat(idName, __id(html_css_suffix_left))))
         pstyleLeft = this;
      else
         pstyleLeft = pdata->m_stylesheeta.rfind(etag, strClass, strSubClass, m_pauraapp->m_pcoresystem->m_phtml->concat(idName, __id(html_css_suffix_left)));

      if(pstyleLeft != NULL)
         iLeft = pstyleLeft->m_propertyset.find_index(m_pauraapp->m_pcoresystem->m_phtml->concat(idName, __id(html_css_suffix_left)));

      if (m_propertyset.has_property(m_pauraapp->m_pcoresystem->m_phtml->concat(idName, __id(html_css_suffix_top))))
         pstyleTop = this;
      else
         pstyleTop = pdata->m_stylesheeta.rfind(etag, strClass, strSubClass, m_pauraapp->m_pcoresystem->m_phtml->concat(idName, __id(html_css_suffix_top)));

      if(pstyleTop != NULL)
         iTop = pstyleTop->m_propertyset.find_index(m_pauraapp->m_pcoresystem->m_phtml->concat(idName, __id(html_css_suffix_top)));

      if (m_propertyset.has_property(m_pauraapp->m_pcoresystem->m_phtml->concat(idName, __id(html_css_suffix_right))))
         pstyleRight = this;
      else
         pstyleRight = pdata->m_stylesheeta.rfind(etag, strClass, strSubClass, m_pauraapp->m_pcoresystem->m_phtml->concat(idName, __id(html_css_suffix_right)));

      if(pstyleRight != NULL)
         iRight = pstyleRight->m_propertyset.find_index(m_pauraapp->m_pcoresystem->m_phtml->concat(idName, __id(html_css_suffix_right)));

      if (m_propertyset.has_property(m_pauraapp->m_pcoresystem->m_phtml->concat(idName, __id(html_css_suffix_bottom))))
         pstyleBottom = this;
      else
         pstyleBottom = pdata->m_stylesheeta.rfind(etag, strClass, strSubClass, m_pauraapp->m_pcoresystem->m_phtml->concat(idName, __id(html_css_suffix_bottom)));

      if(pstyleBottom != NULL)
         iBottom = pstyleBottom->m_propertyset.find_index(m_pauraapp->m_pcoresystem->m_phtml->concat(idName, __id(html_css_suffix_bottom)));

      float f = 0.f;

      if(pstyle != NULL)
      {

         f = parse_dimension(pstyle->m_propertyset[idName]);

      }

      pstyleCur = pdata->m_stylesheeta.greater(pstyle, pstyleLeft);

      if(pstyleCur != NULL)
      {

         if(pstyleCur == pstyleLeft && if_then(pstyleLeft == pstyle, iLeft > i))
         {

            box.left =  parse_dimension(pstyleLeft->m_propertyset.m_propertya[iLeft].get_value().get_string());

         }
         else
         {

            box.left = f;

         }

      }

      pstyleCur = pdata->m_stylesheeta.greater(pstyle, pstyleTop);

      if(pstyleCur != NULL)
      {

         if(pstyleCur == pstyleTop && if_then(pstyleTop == pstyle, iTop > i))
         {

            box.top =  parse_dimension(pstyleTop->m_propertyset.m_propertya[iTop].get_value().get_string());

         }
         else
         {

            box.top = f;

         }

      }

      pstyleCur = pdata->m_stylesheeta.greater(pstyle, pstyleRight);

      if(pstyleCur != NULL)
      {

         if(pstyleCur == pstyleRight && if_then(pstyleRight == pstyle, iRight > i))
         {

            box.right =  parse_dimension(pstyleRight->m_propertyset.m_propertya[iRight].get_value().get_string());

         }
         else
         {

            box.right = f;

         }

      }

      pstyleCur = pdata->m_stylesheeta.greater(pstyle, pstyleBottom);

      if(pstyleCur != NULL)
      {

         if(pstyleCur == pstyleBottom && if_then(pstyleBottom == pstyle, iBottom > i))
         {

            box.bottom =  parse_dimension(pstyleBottom->m_propertyset.m_propertya[iBottom].get_value().get_string());

         }
         else
         {

            box.bottom = f;

         }

      }

      return true;

   }


   bool style::get_border_box(id idName, const string & strSubClass, data * pdata, elemental * pelemental, border & box)
   {
      
      e_tag etag = pelemental->m_etag;

      string strClass = pelemental->m_strClass;

      style * pstyle          = NULL;
      style * pstyleLeft      = NULL;
      style * pstyleTop       = NULL;
      style * pstyleRight     = NULL;
      style * pstyleBottom    = NULL;
      style * pstyleW         = NULL;
      style * pstyleLeftW     = NULL;
      style * pstyleTopW      = NULL;
      style * pstyleRightW    = NULL;
      style * pstyleBottomW   = NULL;
      index i              = -1;
      index iLeft          = -1;
      index iTop           = -1;
      index iRight         = -1;
      index iBottom        = -1;
      index iW             = -1;
      index iLeftW         = -1;
      index iTopW          = -1;
      index iRightW        = -1;
      index iBottomW       = -1;
      float f              = 0.f;
      float fLeft          = 0.f;
      float fTop           = 0.f;
      float fRight         = 0.f;
      float fBottom        = 0.f;
      float fW             = 0.f;
      float fLeftW         = 0.f;
      float fTopW          = 0.f;
      float fRightW        = 0.f;
      float fBottomW       = 0.f;

      if(m_propertyset.has_property(idName) && parse_border_width(m_propertyset[idName], f))
         pstyle = this;
      else
         pstyle = pdata->m_stylesheeta.rfind_border_width(etag, strClass, strSubClass, idName, f);
      if(pstyle != NULL)
         i = pstyle->m_propertyset.find_index(idName);

      if (m_propertyset.has_property(m_pauraapp->m_pcoresystem->m_phtml->concat(idName, __id(html_css_suffix_width)))
         && parse_border_width(m_propertyset[m_pauraapp->m_pcoresystem->m_phtml->concat(idName, __id(html_css_suffix_width))], fW))
         pstyleW = this;
      else
         pstyleW = pdata->m_stylesheeta.rfind_border_width(etag, strClass, strSubClass, idName, fW);
      if(pstyleW != NULL)
         iW = pstyleW->m_propertyset.find_index(m_pauraapp->m_pcoresystem->m_phtml->concat(idName, __id(html_css_suffix_width)));

      if (m_propertyset.has_property(m_pauraapp->m_pcoresystem->m_phtml->concat(idName, __id(html_css_suffix_left)))
         && parse_border_width(m_propertyset[m_pauraapp->m_pcoresystem->m_phtml->concat(idName, __id(html_css_suffix_left))], fLeft))
         pstyleLeft = this;
      else
         pstyleLeft = pdata->m_stylesheeta.rfind_border_width(etag, strClass, strSubClass, m_pauraapp->m_pcoresystem->m_phtml->concat(idName, __id(html_css_suffix_left)), fLeft);

      if(pstyleLeft != NULL)
         iLeft = pstyleLeft->m_propertyset.find_index(m_pauraapp->m_pcoresystem->m_phtml->concat(idName, __id(html_css_suffix_left)));

      if (m_propertyset.has_property(m_pauraapp->m_pcoresystem->m_phtml->concat(idName, __id(html_css_suffix_left_width))
         && parse_border_width(m_propertyset[m_pauraapp->m_pcoresystem->m_phtml->concat(idName, __id(html_css_suffix_left_width))], fLeftW)))
         pstyleLeftW = this;
      else
         pstyleLeftW = pdata->m_stylesheeta.rfind_border_width(etag, strClass, strSubClass, m_pauraapp->m_pcoresystem->m_phtml->concat(idName, __id(html_css_suffix_left_width)), fLeftW);

      if(pstyleLeftW != NULL)
         iLeftW = pstyleLeftW->m_propertyset.find_index(m_pauraapp->m_pcoresystem->m_phtml->concat(idName, __id(html_css_suffix_left_width)));

      if (m_propertyset.has_property(m_pauraapp->m_pcoresystem->m_phtml->concat(idName, __id(html_css_suffix_top))) 
         && parse_border_width(m_propertyset[m_pauraapp->m_pcoresystem->m_phtml->concat(idName, __id(html_css_suffix_top))], fTop))
         pstyleTop = this;
      else
         pstyleTop = pdata->m_stylesheeta.rfind_border_width(etag, strClass, strSubClass, m_pauraapp->m_pcoresystem->m_phtml->concat(idName, __id(html_css_suffix_top)), fTop);

      if(pstyleTop != NULL)
         iTop = pstyleTop->m_propertyset.find_index(m_pauraapp->m_pcoresystem->m_phtml->concat(idName, __id(html_css_suffix_top)));

      if (m_propertyset.has_property(m_pauraapp->m_pcoresystem->m_phtml->concat(idName, __id(html_css_suffix_top_width))) 
         && parse_border_width(m_propertyset[m_pauraapp->m_pcoresystem->m_phtml->concat(idName, __id(html_css_suffix_top_width))], fTopW))
         pstyleTopW = this;
      else
         pstyleTopW = pdata->m_stylesheeta.rfind_border_width(etag, strClass, strSubClass, m_pauraapp->m_pcoresystem->m_phtml->concat(idName, __id(html_css_suffix_top_width)), fTopW);

      if(pstyleTopW != NULL)
         iTopW = pstyleTopW->m_propertyset.find_index(m_pauraapp->m_pcoresystem->m_phtml->concat(idName, __id(html_css_suffix_top_width)));

      if (m_propertyset.has_property(m_pauraapp->m_pcoresystem->m_phtml->concat(idName, __id(html_css_suffix_right)))
         && parse_border_width(m_propertyset[m_pauraapp->m_pcoresystem->m_phtml->concat(idName, __id(html_css_suffix_right))], fRight))
         pstyleRight = this;
      else
         pstyleRight = pdata->m_stylesheeta.rfind_border_width(etag, strClass, strSubClass, m_pauraapp->m_pcoresystem->m_phtml->concat(idName, __id(html_css_suffix_right)), fRight);

      if(pstyleRight != NULL)
         iRight = pstyleRight->m_propertyset.find_index(m_pauraapp->m_pcoresystem->m_phtml->concat(idName, __id(html_css_suffix_right)));

      if (m_propertyset.has_property(m_pauraapp->m_pcoresystem->m_phtml->concat(idName, __id(html_css_suffix_right_width))) 
         && parse_border_width(m_propertyset[m_pauraapp->m_pcoresystem->m_phtml->concat(idName, __id(html_css_suffix_right_width))], fRightW))
         pstyleRightW = this;
      else
         pstyleRightW = pdata->m_stylesheeta.rfind_border_width(etag, strClass, strSubClass, m_pauraapp->m_pcoresystem->m_phtml->concat(idName, __id(html_css_suffix_right_width)), fRightW);

      if(pstyleRightW != NULL)
         iRightW = pstyleRightW->m_propertyset.find_index(m_pauraapp->m_pcoresystem->m_phtml->concat(idName, __id(html_css_suffix_right_width)));

      if (m_propertyset.has_property(m_pauraapp->m_pcoresystem->m_phtml->concat(idName, __id(html_css_suffix_bottom))) 
         && parse_border_width(m_propertyset[m_pauraapp->m_pcoresystem->m_phtml->concat(idName, __id(html_css_suffix_bottom))], fBottom))
         pstyleBottom = this;
      else
         pstyleBottom = pdata->m_stylesheeta.rfind_border_width(etag, strClass, strSubClass, m_pauraapp->m_pcoresystem->m_phtml->concat(idName, __id(html_css_suffix_bottom)), fBottom);

      if(pstyleBottom != NULL)
         iBottom = pstyleBottom->m_propertyset.find_index(m_pauraapp->m_pcoresystem->m_phtml->concat(idName, __id(html_css_suffix_bottom)));

      if (m_propertyset.has_property(m_pauraapp->m_pcoresystem->m_phtml->concat(idName, __id(html_css_suffix_bottom_width)))
         && parse_border_width(m_propertyset[m_pauraapp->m_pcoresystem->m_phtml->concat(idName, __id(html_css_suffix_bottom_width))], fBottomW))
         pstyleBottomW = this;
      else
         pstyleBottomW = pdata->m_stylesheeta.rfind_border_width(etag, strClass, strSubClass, m_pauraapp->m_pcoresystem->m_phtml->concat(idName, __id(html_css_suffix_bottom_width)), fBottomW);

      if(pstyleBottomW != NULL)
         iBottomW = pstyleBottomW->m_propertyset.find_index(m_pauraapp->m_pcoresystem->m_phtml->concat(idName, __id(html_css_suffix_bottom_width)));

      style *     pstyle1           = NULL;
      index               i1                = -1;
      var               var1              = f;
      pdata->m_stylesheeta.greater(pstyle1, i1, var1, pstyle, i, var1, pstyleW, iW, fW);


      style *     pstyleCur;
      index               iCur;
      var               varCur;

      pstyleCur         = pstyle1;
      iCur              = i1;
      varCur            = var1;
      pdata->m_stylesheeta.greater(pstyleCur, iCur, varCur, pstyleCur, iCur, varCur, pstyleLeft, iLeft, fLeft);
      pdata->m_stylesheeta.greater(pstyleCur, iCur, varCur, pstyleCur, iCur, varCur, pstyleLeftW, iLeftW, fLeftW);
      box.left          = (float) (double) varCur.get_double();

      pstyleCur         = pstyle1;
      iCur              = i1;
      varCur            = var1;
      pdata->m_stylesheeta.greater(pstyleCur, iCur, varCur, pstyleCur, iCur, varCur, pstyleTop, iTop, fTop);
      pdata->m_stylesheeta.greater(pstyleCur, iCur, varCur, pstyleCur, iCur, varCur, pstyleTopW, iTopW, fTopW);
      box.top           = (float) (double) varCur.get_double();

      pstyleCur         = pstyle1;
      iCur              = i1;
      varCur            = var1;
      pdata->m_stylesheeta.greater(pstyleCur, iCur, varCur, pstyleCur, iCur, varCur, pstyleRight, iRight, fRight);
      pdata->m_stylesheeta.greater(pstyleCur, iCur, varCur, pstyleCur, iCur, varCur, pstyleRightW, iRightW, fRightW);
      box.right         = (float) (double) varCur.get_double();

      pstyleCur         = pstyle1;
      iCur              = i1;
      varCur            = var1;
      pdata->m_stylesheeta.greater(pstyleCur, iCur, varCur, pstyleCur, iCur, varCur, pstyleBottom, iBottom, fBottom);
      pdata->m_stylesheeta.greater(pstyleCur, iCur, varCur, pstyleCur, iCur, varCur, pstyleBottomW, iBottomW, fBottomW);
      box.bottom        = (float) (double) varCur.get_double();

      return true;

   }


   bool style::get_border_color(id idName, const string & strSubClass, data * pdata, elemental * pelemental, border & box)
   {
      
      e_tag etag = pelemental->m_etag;

      string strClass= pelemental->m_strClass;
      
      style * pstyle          = NULL;
      style * pstyleLeft      = NULL;
      style * pstyleTop       = NULL;
      style * pstyleRight     = NULL;
      style * pstyleBottom    = NULL;
      style * pstyleW         = NULL;
      style * pstyleLeftW     = NULL;
      style * pstyleTopW      = NULL;
      style * pstyleRightW    = NULL;
      style * pstyleBottomW   = NULL;
      index i              = -1;
      index iLeft          = -1;
      index iTop           = -1;
      index iRight         = -1;
      index iBottom        = -1;
      index iW             = -1;
      index iLeftW         = -1;
      index iTopW          = -1;
      index iRightW        = -1;
      index iBottomW       = -1;
      COLORREF cr              = 0;
      COLORREF crLeft          = 0;
      COLORREF crTop           = 0;
      COLORREF crRight         = 0;
      COLORREF crBottom        = 0;
      COLORREF crW             = 0;
      COLORREF crLeftW         = 0;
      COLORREF crTopW          = 0;
      COLORREF crRightW        = 0;
      COLORREF crBottomW       = 0;

      if(m_propertyset.has_property(idName) && parse_border_color(m_propertyset[idName], cr))
         pstyle = this;
      else
         pstyle = pdata->m_stylesheeta.rfind_border_color(etag, strClass, strSubClass, idName, cr);
      if(pstyle != NULL)
         i = pstyle->m_propertyset.find_index(idName);

      if (m_propertyset.has_property(m_pauraapp->m_pcoresystem->m_phtml->concat(idName, __id(html_css_suffix_color)))
         && parse_border_color(m_propertyset[m_pauraapp->m_pcoresystem->m_phtml->concat(idName, __id(html_css_suffix_color))], crW))
         pstyleW = this;
      else
         pstyleW = pdata->m_stylesheeta.rfind_border_color(etag, strClass, strSubClass, m_pauraapp->m_pcoresystem->m_phtml->concat(idName, __id(html_css_suffix_color)), crW);

      if(pstyleW != NULL)
         iW = pstyleW->m_propertyset.find_index(m_pauraapp->m_pcoresystem->m_phtml->concat(idName, __id(html_css_suffix_color)));

      if (m_propertyset.has_property(m_pauraapp->m_pcoresystem->m_phtml->concat(idName, __id(html_css_suffix_left)))
         && parse_border_color(m_propertyset[m_pauraapp->m_pcoresystem->m_phtml->concat(idName, __id(html_css_suffix_left))], crLeft))
         pstyleLeft = this;
      else
         pstyleLeft = pdata->m_stylesheeta.rfind_border_color(etag, strClass, strSubClass, m_pauraapp->m_pcoresystem->m_phtml->concat(idName, __id(html_css_suffix_left)), crLeft);

      if(pstyleLeft != NULL)
         iLeft = pstyleLeft->m_propertyset.find_index(m_pauraapp->m_pcoresystem->m_phtml->concat(idName, __id(html_css_suffix_left)));

      if (m_propertyset.has_property(m_pauraapp->m_pcoresystem->m_phtml->concat(idName, __id(html_css_suffix_left_color)))
         && parse_border_color(m_propertyset[m_pauraapp->m_pcoresystem->m_phtml->concat(idName, __id(html_css_suffix_left_color))], crLeftW))
         pstyleLeftW = this;
      else
         pstyleLeftW = pdata->m_stylesheeta.rfind_border_color(etag, strClass, strSubClass, m_pauraapp->m_pcoresystem->m_phtml->concat(idName, __id(html_css_suffix_left_color)), crLeftW);

      if(pstyleLeftW != NULL)
         iLeftW = pstyleLeftW->m_propertyset.find_index(m_pauraapp->m_pcoresystem->m_phtml->concat(idName, __id(html_css_suffix_left_color)));

      if (m_propertyset.has_property(m_pauraapp->m_pcoresystem->m_phtml->concat(idName, __id(html_css_suffix_top))) 
         && parse_border_color(m_propertyset[m_pauraapp->m_pcoresystem->m_phtml->concat(idName, __id(html_css_suffix_top))], crTop))
         pstyleTop = this;
      else
         pstyleTop = pdata->m_stylesheeta.rfind_border_color(etag, strClass, strSubClass, m_pauraapp->m_pcoresystem->m_phtml->concat(idName, __id(html_css_suffix_top)), crTop);

      if(pstyleTop != NULL)
         iTop = pstyleTop->m_propertyset.find_index(m_pauraapp->m_pcoresystem->m_phtml->concat(idName, __id(html_css_suffix_top)));

      if (m_propertyset.has_property(m_pauraapp->m_pcoresystem->m_phtml->concat(idName, __id(html_css_suffix_top_color)))
         && parse_border_color(m_propertyset[m_pauraapp->m_pcoresystem->m_phtml->concat(idName, __id(html_css_suffix_top_color))], crTopW))
         pstyleTopW = this;
      else
         pstyleTopW = pdata->m_stylesheeta.rfind_border_color(etag, strClass, strSubClass, m_pauraapp->m_pcoresystem->m_phtml->concat(idName, __id(html_css_suffix_top_color)), crTopW);

      if(pstyleTopW != NULL)
         iTopW = pstyleTopW->m_propertyset.find_index(m_pauraapp->m_pcoresystem->m_phtml->concat(idName, __id(html_css_suffix_top_color)));

      if (m_propertyset.has_property(m_pauraapp->m_pcoresystem->m_phtml->concat(idName, __id(html_css_suffix_right))) 
         && parse_border_color(m_propertyset[m_pauraapp->m_pcoresystem->m_phtml->concat(idName, __id(html_css_suffix_right))], crRight))
         pstyleRight = this;
      else
         pstyleRight = pdata->m_stylesheeta.rfind_border_color(etag, strClass, strSubClass, m_pauraapp->m_pcoresystem->m_phtml->concat(idName, __id(html_css_suffix_right)), crRight);

      if(pstyleRight != NULL)
         iRight = pstyleRight->m_propertyset.find_index(m_pauraapp->m_pcoresystem->m_phtml->concat(idName, __id(html_css_suffix_right)));

      if (m_propertyset.has_property(m_pauraapp->m_pcoresystem->m_phtml->concat(idName, __id(html_css_suffix_right_color))) 
         && parse_border_color(m_propertyset[m_pauraapp->m_pcoresystem->m_phtml->concat(idName, __id(html_css_suffix_right_color))], crRightW))
         pstyleRightW = this;
      else
         pstyleRightW = pdata->m_stylesheeta.rfind_border_color(etag, strClass, strSubClass, m_pauraapp->m_pcoresystem->m_phtml->concat(idName, __id(html_css_suffix_right_color)), crRightW);

      if(pstyleRightW != NULL)
         iRightW = pstyleRightW->m_propertyset.find_index(m_pauraapp->m_pcoresystem->m_phtml->concat(idName, __id(html_css_suffix_right_color)));

      if (m_propertyset.has_property(m_pauraapp->m_pcoresystem->m_phtml->concat(idName, __id(html_css_suffix_bottom))) 
         && parse_border_color(m_propertyset[m_pauraapp->m_pcoresystem->m_phtml->concat(idName, __id(html_css_suffix_bottom))], crBottom))
         pstyleBottom = this;
      else
         pstyleBottom = pdata->m_stylesheeta.rfind_border_color(etag, strClass, strSubClass, m_pauraapp->m_pcoresystem->m_phtml->concat(idName, __id(html_css_suffix_bottom)), crBottom);

      if(pstyleBottom != NULL)
         iBottom = pstyleBottom->m_propertyset.find_index(m_pauraapp->m_pcoresystem->m_phtml->concat(idName, __id(html_css_suffix_bottom)));

      if (m_propertyset.has_property(m_pauraapp->m_pcoresystem->m_phtml->concat(idName, __id(html_css_suffix_bottom_color))) 
         && parse_border_color(m_propertyset[m_pauraapp->m_pcoresystem->m_phtml->concat(idName, __id(html_css_suffix_bottom_color))], crBottomW))
         pstyleBottomW = this;
      else
         pstyleBottomW = pdata->m_stylesheeta.rfind_border_color(etag, strClass, strSubClass, m_pauraapp->m_pcoresystem->m_phtml->concat(idName, __id(html_css_suffix_bottom_color)), crBottomW);

      if(pstyleBottomW != NULL)
         iBottomW = pstyleBottomW->m_propertyset.find_index(m_pauraapp->m_pcoresystem->m_phtml->concat(idName, __id(html_css_suffix_bottom_color)));

      style *     pstyle1           = NULL;
      index               i1                 = -1;
      var               var1                 = (uint32_t) cr;
      pdata->m_stylesheeta.greater(pstyle1, i1, var1, pstyle, i, var1, pstyleW, iW, (uint32_t &) crW);


      style *     pstyleCur;
      index               iCur;
      var               varCur;

      pstyleCur         = pstyle1;
      iCur              = i1;
      varCur            = var1;
      pdata->m_stylesheeta.greater(pstyleCur, iCur, varCur, pstyleCur, iCur, varCur, pstyleLeft, iLeft, (uint32_t &) crLeft);
      pdata->m_stylesheeta.greater(pstyleCur, iCur, varCur, pstyleCur, iCur, varCur, pstyleLeftW, iLeftW, (uint32_t &) crLeftW);
      box.crLeft        = (uint32_t) varCur;

      pstyleCur         = pstyle1;
      iCur              = i1;
      varCur            = var1;
      pdata->m_stylesheeta.greater(pstyleCur, iCur, varCur, pstyleCur, iCur, varCur, pstyleTop, iTop, (uint32_t &) crTop);
      pdata->m_stylesheeta.greater(pstyleCur, iCur, varCur, pstyleCur, iCur, varCur, pstyleTopW, iTopW, (uint32_t &) crTopW);
      box.crTop         = (uint32_t) varCur;

      pstyleCur         = pstyle1;
      iCur              = i1;
      varCur            = var1;
      pdata->m_stylesheeta.greater(pstyleCur, iCur, varCur, pstyleCur, iCur, varCur, pstyleRight, iRight, (uint32_t &) crRight);
      pdata->m_stylesheeta.greater(pstyleCur, iCur, varCur, pstyleCur, iCur, varCur, pstyleRightW, iRightW, (uint32_t &) crRightW);
      box.crRight       = (uint32_t) varCur;

      pstyleCur         = pstyle1;
      iCur              = i1;
      varCur            = var1;
      pdata->m_stylesheeta.greater(pstyleCur, iCur, varCur, pstyleCur, iCur, varCur, pstyleBottom, iBottom, (uint32_t &) crBottom);
      pdata->m_stylesheeta.greater(pstyleCur, iCur, varCur, pstyleCur, iCur, varCur, pstyleBottomW, iBottomW, (uint32_t &) crBottomW);
      box.crBottom      = (uint32_t) varCur;

      return true;

   }


   bool style::get_color(id idName, const string & strSubClass, data * pdata, elemental * pelemental, COLORREF & cr)
   {
      
      e_tag etag = pelemental->m_etag;

      string strClass = pelemental->m_strClass;

      if(m_propertyset.is_new_or_null(idName))
      {

         style * pstyle = pdata->m_stylesheeta.rfind(etag, strClass, strSubClass, idName);

         if(pstyle == NULL)
         {

            if(pelemental->m_pparent != NULL && stricmp_dup(idName, "background-color"))
            {

               if(pelemental->m_pparent->m_style.get_color(idName, strSubClass, pdata, pelemental->m_pparent, cr))
               {
                  return true;
               }
            }
            return false;
         }
         return pstyle->get_color(idName, strSubClass, pdata, pelemental, cr);
      }
      cr = parse_color(m_propertyset[idName]);
      return true;
   }

   bool style::get_text(id idName, const string & strSubClass, data * pdata, elemental * pelemental, string & str)
   {

      e_tag etag = pelemental->m_etag;

      string strClass = pelemental->m_strClass;

      if(m_propertyset.is_new_or_null(idName))
      {

         style * pstyle = pdata->m_stylesheeta.rfind(etag, strClass, strSubClass, idName);
         if(pstyle == NULL)
         {
            if(pelemental->m_pparent != NULL
            && stricmp_dup(idName, "padding") != 0
            && stricmp_dup(idName, "margin") != 0
            && stricmp_dup(idName, "border") != 0)   
            {
               if(pelemental->m_pparent->m_style.get_text(idName, strSubClass, pdata, pelemental->m_pparent, str))
               {
                  return true;
               }
            }
            if(etag == tag_h1)
            {
               if(stricmp_dup("font-family", idName) == 0)
               {
                  str = "Times New Roman";
                  return true;
               }
               else if(stricmp_dup("font-size", idName) == 0)
               {
                  str = "30";
                  return true;
               }
               else if(stricmp_dup("font-weight", idName) == 0)
               {
                  str = "bold";
                  return true;
               }
               else
               {
                  return false;
               }
            }
            else if(etag == tag_h2)
            {
               if(stricmp_dup("font-family", idName) == 0)
               {
                  str = "Times New Roman";
                  return true;
               }
               else if(stricmp_dup("font-size", idName) == 0)
               {
                  str = "23";
                  return true;
               }
               else if(stricmp_dup("font-weight", idName) == 0)
               {
                  str = "bold";
                  return true;
               }
               else
               {
                  return false;
               }
            }
            else if(etag == tag_p)
            {
               if(stricmp_dup("font-family", idName) == 0)
               {
                  str = "Times New Roman";
                  return true;
               }
               else if(stricmp_dup("font-size", idName) == 0)
               {
                  str = "11";
                  return true;
               }
               else if(stricmp_dup("font-weight", idName) == 0)
               {
                  str = "normal";
                  return true;
               }
               else
               {
                  return false;
               }
            }
            else if(etag == tag_h3)
            {
               if(stricmp_dup("font-family", idName) == 0)
               {
                  str = "Times New Roman";
                  return true;
               }
               else if(stricmp_dup("font-size", idName) == 0)
               {
                  str = "18";
                  return true;
               }
               else if(stricmp_dup("font-weight", idName) == 0)
               {
                  str = "bold";
                  return true;
               }
               else
               {
                  return false;
               }
            }
            else if (etag == tag_strong)
            {
               if (stricmp_dup("font-weight", idName) == 0)
               {
                  str = "bold";
                  return true;
               }
               else
               {
                  return false;
               }
            }
            else
            {
               return false;
            }
         }
         return pstyle->get_text(idName, strSubClass, pdata, pelemental, str);
      }
      str = m_propertyset[idName];
      string strEm = str;
      if(string(idName).CompareNoCase("font-size") == 0)
      {
         if(::str::find_awwci("em", str) > 0)
         {
            if(pelemental->m_pparent != NULL)
            {
               string strParent;
               if(pelemental->m_pparent->m_style.get_text(idName, strSubClass, pdata, pelemental->m_pparent, strParent))
               {
                  str = ::str::from((int32_t)((double) atof(str) * atoi(strParent)));
               }
               else
               {
                  str = ::str::from((int32_t)((double) atof(str) * 12));
               }
            }
            else
            {
               str = ::str::from((int32_t)((double) atof(str) * 12));
            }
         }
      }
      return true;
   }

   bool style::get_alpha(const string & strSubClass, data * pdata, elemental * pelemental, double & d)
   {
      
      const char* idName = "opacity";
      
      e_tag etag = pelemental->m_etag;

      string strClass = pelemental->m_strClass;

      if(m_propertyset.is_new_or_null(idName))
      {

         style * pstyle = pdata->m_stylesheeta.rfind(etag, strClass, strSubClass, idName);

         if(pstyle == NULL)
            return false;

         return pstyle->get_alpha(strSubClass, pdata, pelemental, d);

      }

      d = m_propertyset["opacity"];

      return true;

   }


   const char * style::parse(data * pdata, const char * psz)
   {
      UNREFERENCED_PARAMETER(pdata);
      while(*psz != '\0' && *psz != '}')
      {
         const char * pszStart = psz;
         while(*psz != ':' && *psz != '\0' && *psz != '}')
         {
            psz++;
         }
         if(*psz == '\0' || *psz == '}')
            return psz;
         string strKey(pszStart, psz - pszStart);
         strKey.trim();

         char chQuote = '\0';
         psz++;
         pszStart = psz;
         while((chQuote != '\0' || *psz != ';') && *psz != '\0' && *psz != '}')
         {
            psz++;
            if(chQuote != '\0' && chQuote == *psz && *(psz - 1) != '\\')
            {
               chQuote = '\0';
            }
            else if(*psz == '\"' || *psz == '\'')
            {
               chQuote = *psz;
            }
         }
         string strValue(pszStart, psz - pszStart);
         m_propertyset[strKey] = strValue;
         if(*psz == ';')
         {
            psz++;
         }
      }

      return psz;

   }

   bool style::matches(e_tag etag, const string & strClass, const string & strSubClass, id idName)
   {
      if(etag != tag_none && m_etag != tag_none)
         if(m_etag != etag)
            return false;
      if(m_strName.has_char())
         if(m_strName != strClass)
            return false;
      if(m_strSubClass.has_char())
         if(m_strSubClass != strSubClass)
            return false;
      if(!idName.is_empty())
         if(!m_propertyset.has_property(idName))
            return false;
      return true;
   }

   bool style::matches_border_width(e_tag etag, const string & strClass, const string & strSubClass, id idName, float & f)
   {
      if(etag != tag_none && m_etag != tag_none)
         if(m_etag != etag)
            return false;
      if(m_strName.has_char())
         if(m_strName != strClass)
            return false;
      if(m_strSubClass.has_char())
         if(m_strSubClass != strSubClass)
            return false;
      if(idName.is_null())
         return false;
      index i = m_propertyset.find_index(idName);
      if(i < 0)
         return false;
      if(!parse_border_width(m_propertysetm_propertya[i]->get_value().get_string(), f))
         return false;
      return true;
   }

   bool style::matches_border_color(e_tag etag, const string & strClass, const string & strSubClass, id idName, COLORREF & cr)
   {
      if(etag != tag_none && m_etag != tag_none)
         if(m_etag != etag)
            return false;
      if(m_strName.has_char())
         if(m_strName != strClass)
            return false;
      if(m_strSubClass.has_char())
         if(m_strSubClass != strSubClass)
            return false;
      if(idName.is_null())
         return false;
      index i = m_propertyset.find_index(idName);
      if(i < 0)
         return false;
      if(!parse_border_color(m_propertysetm_propertya[i]->get_value().get_string(), cr))
         return false;
      return true;
   }


   float style::parse_dimension(const char * psz)
   {

      string str(psz);

      str.trim();
      if(::str::ends_eat_ci(str, "px"))
      {
         str.trim();
         return (float) strtod(str, NULL);
      }
      else if(::str::ends_eat_ci(str, "pt"))
      {
         str.trim();
         return (float) (strtod(str, NULL) * 96.0 / 72.0);
      }
      else
      {
         return (float) strtod(str, NULL);
      }

   }

   bool style::parse_border_width(const char * psz, float & f)
   {

      if(psz == NULL)
         return false;

      string str(psz);

      str.trim();

      if(str.is_empty())
         return false;

      // todo ::str::find_cssci would find thick between spaces but not concatenated
      if(str.find_ci("thick") >= 0)
      {
         f = 5.0;
         return true;
      }
      else if(str.find_ci("thin") >= 0)
      {
         f = 1.0;
         return true;
      }

      strsize iFindRgb = str.find_ci("rgb");
      strsize iFindSharp = str.find_ci("#");
      strsize iFindColor = -1;
      strsize iFindDigit = str.FindOneOf("0123456789");
      if(iFindRgb >= 0)
      {
         if(iFindSharp >= 0)
         {
            // invalid border specification... two colors?!?!?
            return false;
         }
         iFindColor = iFindRgb + 3;
      }
      else if(iFindSharp >= 0)
         iFindColor = iFindSharp + 1;

      if(iFindDigit >= 0 && iFindColor >= 0 && iFindDigit > iFindColor)
      {
         const char * psz = &str[iFindColor];
         const char * pszStart = psz;
         if(iFindRgb >= 0)
         {
            try
            {
               ::str::consume_spaces(psz, 0);
               ::str::consume(psz, "(");
               ::str::consume_spaces(psz, 0);
               ::str::consume_natural(psz, 255);
               ::str::consume_spaces(psz, 0);
               ::str::consume(psz, ",");
               ::str::consume_spaces(psz, 0);
               ::str::consume_natural(psz, 255);
               ::str::consume_spaces(psz, 0);
               ::str::consume(psz, ",");
               ::str::consume_spaces(psz, 0);
               ::str::consume_natural(psz, 255);
               ::str::consume_spaces(psz, 0);
               ::str::consume(psz, ")");
            }
            catch(...)
            {
               return false;
            }
         }
         else if(iFindSharp >= 0)
         {
            try
            {
               ::str::consume_hex(psz);
            }
            catch(...)
            {
               return false;
            }
         }
         else
         {
            // unexpected condition
            return false;
         }
         iFindColor += psz - pszStart;
         iFindDigit = str.FindOneOf("0123456789", iFindColor);
         if(iFindDigit < 0)
            return false; // no more numeric width
      }

      strsize i = iFindDigit;

      if(i < 0)
         return false;

      while(i < str.get_length() && i < isdigit(str[i]))
      {
         i++;
      }
      if(i >= str.get_length())
      {
         f = (float) strtod(&str[iFindDigit], NULL);
         return true;
      }
      if(str[i] == '.')
      {
         i++;
      }
      if(i >= str.get_length())
      {
         f = (float) strtod(&str[iFindDigit], NULL);
         return true;
      }
      while(i < str.get_length() && i < isdigit(str[i]))
      {
         i++;
      }
      if(i >= str.get_length())
      {
         f = (float) strtod(&str[iFindDigit], NULL);
         return true;
      }
      while(i < str.get_length() && i < isspace(str[i]))
      {
         i++;
      }
      if(i >= str.get_length())
      {
         f = (float) strtod(&str[iFindDigit], NULL);
         return true;
      }
      f = (float) strtod(&str[iFindDigit], NULL);
      str = str.Mid(i);
      if(::str::begins_ci(str, "pt"))
      {
         str.trim();
         if(str.get_length() == 2 || isspace(str[3]))
         {
            f = f * 96.f / 72.f;
         }
      }
      return true;
   }

   bool style::parse_border_color(const char * pszParam, COLORREF & cr)
   {

      if(pszParam == NULL)
         return false;

      string str(pszParam);

      str.trim();

      if(str.is_empty())
         return false;

      // todo ::str::find_cssci would find red between spaces but not concatenated
      if(str.find_ci("magenta") >= 0)
      {
         cr = ARGB(255, 255, 0, 255);
         return true;
      }
      else if(str.find_ci("green") >= 0)
      {
         cr = ARGB(255, 0, 255, 0);
         return true;
      }

      strsize iFindRgb = str.find_ci("rgb");
      strsize iFindSharp = str.find_ci("#");
      strsize iFindColor = -1;
//      strsize iFindDigit = str.FindOneOf("0123456789");
      if(iFindRgb >= 0)
      {
         if(iFindSharp >= 0)
         {
            // invalid border specification... two colors?!?!?
            return false;
         }
         iFindColor = iFindRgb + 3;
      }
      else if(iFindSharp >= 0)
         iFindColor = iFindSharp + 1;

      if(iFindColor < 0)
         return false;

      const char * psz = &str[iFindColor];
      const char * pszStart = psz;
      if(iFindRgb >= 0)
      {
         try
         {
            ::str::consume_spaces(psz, 0);
            ::str::consume(psz, "(");
            ::str::consume_spaces(psz, 0);
            int32_t R = (int32_t) ::str::consume_natural(psz, 255);
            ::str::consume_spaces(psz, 0);
            ::str::consume(psz, ",");
            ::str::consume_spaces(psz, 0);
            int32_t G = (int32_t) ::str::consume_natural(psz, 255);
            ::str::consume_spaces(psz, 0);
            ::str::consume(psz, ",");
            ::str::consume_spaces(psz, 0);
            int32_t B = (int32_t) ::str::consume_natural(psz, 255);
            ::str::consume_spaces(psz, 0);
            ::str::consume(psz, ")");
            cr = ARGB(255, R, G, B);
            return true;
         }
         catch(...)
         {
            return false;
         }
      }
      else if(iFindSharp >= 0)
      {
         try
         {
            ::str::consume_hex(psz);
            cr = parse_color(pszStart - 1);
            return true;
         }
         catch(...)
         {
            return false;
         }
      }
      else
      {
         // unexpected condition
         return false;
      }

      return false;
   }


   void style::initialize(e_tag etag)
   {

      if (m_propertyset.has_property(__id(html_display)))
      {
         
         m_edisplay = m_pauraapp->m_pcoresystem->m_phtml->display_name_to_id(m_propertyset[__id(html_display)], etag);

      }
      else
      {

         m_edisplay = m_pauraapp->m_pcoresystem->m_phtml->tag_to_display(etag);

      }

      

   }




} // namespace html




