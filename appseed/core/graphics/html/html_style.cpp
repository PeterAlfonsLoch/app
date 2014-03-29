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


   style::style()
   {
   }

   style::style(const style & style)
   {
      operator = (style);
   }

   style & style::operator = (const style & style)
   {
      if(this != &style)
      {
         m_strTag       = style.m_strTag;
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

   bool style::get_dimension(bool bParent, const char * pszName, const char * pszSubClass, data * pdata, elemental * pelemental, float & f)
   {

      f = 0.f;

      string strTag;
      if(pelemental->m_propertyset.is_new_or_null("PropertyTag"))
      {
         strTag = pelemental->m_pparent->m_propertyset["PropertyTag"];
      }
      else
      {
         strTag = pelemental->m_propertyset["PropertyTag"];
      }
      string strClass;
      if(pelemental->m_pparent != NULL && pelemental->m_pparent->get_tag()->get_attr_value("class").has_char())
      {
         strClass = pelemental->m_pparent->get_tag()->get_attr_value("class");
      }
      else
      {
         strClass = pelemental->get_tag()->get_attr_value("class");
      }
      if(pelemental->m_propertyset.is_new_or_null("PropertyTag"))
      {
         strTag = pelemental->m_pparent->m_propertyset["PropertyTag"];
      }
      else
      {
         strTag = pelemental->m_propertyset["PropertyTag"];
      }
      if(m_propertyset.is_new_or_null(pszName))
      {
         style * pstyle = pdata->m_stylesheeta.rfind(strTag, strClass, pszSubClass, pszName);
         if(pstyle == NULL)
         {
            if(bParent)
            {
               if(pelemental->m_pparent != NULL && stricmp_dup(pszName, "background-color"))
               {
                  if(pelemental->m_pparent->m_style.get_dimension(true, pszName, pszSubClass, pdata, pelemental->m_pparent, f))
                  {
                     return true;
                  }
               }
            }
            return false;
         }
         return pstyle->get_dimension(bParent, pszName, pszSubClass, pdata, pelemental, f);
      }
      f = parse_dimension(m_propertyset[pszName]);
      return true;
   }

   bool style::get_surround_box(const char * pszName, const char * pszSubClass, data * pdata, elemental * pelemental, box & box)
   {
      string strTag;
      string strClass;
      if (pelemental->m_propertyset.is_new_or_null("PropertyTag"))
      {
         strTag = pelemental->m_pparent->m_propertyset["PropertyTag"];
         if (pelemental->m_pparent != NULL && pelemental->m_pparent->get_tag()->get_attr_value("class").has_char())
         {
            strClass = pelemental->m_pparent->get_tag()->get_attr_value("class");
         }
      }
      else
      {
         strTag = pelemental->m_propertyset["PropertyTag"];
         if (pelemental->get_tag() != NULL)
         {
            strClass = pelemental->get_tag()->get_attr_value("class");
         }
      }
      
      if(pelemental->m_propertyset.is_new_or_null("PropertyTag"))
      {
         strTag = pelemental->m_pparent->m_propertyset["PropertyTag"];
      }
      else
      {
         strTag = pelemental->m_propertyset["PropertyTag"];
      }
      style * pstyleCur = NULL;
      style * pstyle = NULL;
      style * pstyleLeft = NULL;
      style * pstyleTop = NULL;
      style * pstyleRight = NULL;
      style * pstyleBottom = NULL;
      index i;
      index iLeft;
      index iTop;
      index iRight;
      index iBottom;
      string strName(pszName);

      if(m_propertyset.has_property(strName))
         pstyle = this;
      else
         pstyle = pdata->m_stylesheeta.rfind(strTag, strClass, pszSubClass, pszName);
      if(pstyle != NULL)
         i = pstyle->m_propertyset.find_index(strName);

      if(m_propertyset.has_property(strName + "-left"))
         pstyleLeft = this;
      else
         pstyleLeft = pdata->m_stylesheeta.rfind(strTag, strClass, pszSubClass, strName + "-left");
      if(pstyleLeft != NULL)
         iLeft = pstyleLeft->m_propertyset.find_index(strName + "-left");

      if(m_propertyset.has_property(strName + "-top"))
         pstyleTop = this;
      else
         pstyleTop = pdata->m_stylesheeta.rfind(strTag, strClass, pszSubClass, strName + "-top");
      if(pstyleTop != NULL)
         iTop = pstyleTop->m_propertyset.find_index(strName + "-top");

      if(m_propertyset.has_property(strName + "-right"))
         pstyleRight = this;
      else
         pstyleRight = pdata->m_stylesheeta.rfind(strTag, strClass, pszSubClass, strName + "-right");
      if(pstyleRight != NULL)
         iRight = pstyleRight->m_propertyset.find_index(strName + "-right");

      if(m_propertyset.has_property(strName + "-bottom"))
         pstyleBottom = this;
      else
         pstyleBottom = pdata->m_stylesheeta.rfind(strTag, strClass, pszSubClass, strName + "-bottom");
      if(pstyleBottom != NULL)
         iBottom = pstyleBottom->m_propertyset.find_index(strName + "-bottom");

      float f = 0.f;
      if(pstyle != NULL)
      {
         f = parse_dimension(pstyle->m_propertyset[strName]);
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


   bool style::get_border_box(const char * pszName, const char * pszSubClass, data * pdata, elemental * pelemental, border & box)
   {
      string strTag;
      if(pelemental->m_propertyset.is_new_or_null("PropertyTag"))
      {
         strTag = pelemental->m_pparent->m_propertyset["PropertyTag"];
      }
      else
      {
         strTag = pelemental->m_propertyset["PropertyTag"];
      }
      string strClass;
      if(pelemental->m_pparent != NULL && pelemental->m_pparent->get_tag()->get_attr_value("class").has_char())
      {
         strClass = pelemental->m_pparent->get_tag()->get_attr_value("class");
      }
      else if(pelemental->get_tag() != NULL)
      {
         strClass = pelemental->get_tag()->get_attr_value("class");
      }
      if(pelemental->m_propertyset.is_new_or_null("PropertyTag"))
      {
         strTag = pelemental->m_pparent->m_propertyset["PropertyTag"];
      }
      else
      {
         strTag = pelemental->m_propertyset["PropertyTag"];
      }

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
      string strName(pszName);

      if(m_propertyset.has_property(strName) && parse_border_width(m_propertyset[strName], f))
         pstyle = this;
      else
         pstyle = pdata->m_stylesheeta.rfind_border_width(strTag, strClass, pszSubClass, pszName, f);
      if(pstyle != NULL)
         i = pstyle->m_propertyset.find_index(strName);

      if(m_propertyset.has_property(strName + "-width") && parse_border_width(m_propertyset[strName + "-width"], fW))
         pstyleW = this;
      else
         pstyleW = pdata->m_stylesheeta.rfind_border_width(strTag, strClass, pszSubClass, pszName, fW);
      if(pstyleW != NULL)
         iW = pstyleW->m_propertyset.find_index(strName + "-width");

      if(m_propertyset.has_property(strName + "-left") && parse_border_width(m_propertyset[strName + "-left"], fLeft))
         pstyleLeft = this;
      else
         pstyleLeft = pdata->m_stylesheeta.rfind_border_width(strTag, strClass, pszSubClass, strName + "-left", fLeft);
      if(pstyleLeft != NULL)
         iLeft = pstyleLeft->m_propertyset.find_index(strName + "-left");

      if(m_propertyset.has_property(strName + "-left-width") && parse_border_width(m_propertyset[strName + "-left-width"], fLeftW))
         pstyleLeftW = this;
      else
         pstyleLeftW = pdata->m_stylesheeta.rfind_border_width(strTag, strClass, pszSubClass, strName + "-left-width", fLeftW);
      if(pstyleLeftW != NULL)
         iLeftW = pstyleLeftW->m_propertyset.find_index(strName + "-left-width");

      if(m_propertyset.has_property(strName + "-top") && parse_border_width(m_propertyset[strName + "-top"], fTop))
         pstyleTop = this;
      else
         pstyleTop = pdata->m_stylesheeta.rfind_border_width(strTag, strClass, pszSubClass, strName + "-top", fTop);
      if(pstyleTop != NULL)
         iTop = pstyleTop->m_propertyset.find_index(strName + "-top");

      if(m_propertyset.has_property(strName + "-top-width") && parse_border_width(m_propertyset[strName + "-top-width"], fTopW))
         pstyleTopW = this;
      else
         pstyleTopW = pdata->m_stylesheeta.rfind_border_width(strTag, strClass, pszSubClass, strName + "-top-width", fTopW);
      if(pstyleTopW != NULL)
         iTopW = pstyleTopW->m_propertyset.find_index(strName + "-top-width");

      if(m_propertyset.has_property(strName + "-right") && parse_border_width(m_propertyset[strName + "-right"], fRight))
         pstyleRight = this;
      else
         pstyleRight = pdata->m_stylesheeta.rfind_border_width(strTag, strClass, pszSubClass, strName + "-right", fRight);
      if(pstyleRight != NULL)
         iRight = pstyleRight->m_propertyset.find_index(strName + "-right");

      if(m_propertyset.has_property(strName + "-right-width") && parse_border_width(m_propertyset[strName + "-right-width"], fRightW))
         pstyleRightW = this;
      else
         pstyleRightW = pdata->m_stylesheeta.rfind_border_width(strTag, strClass, pszSubClass, strName + "-right-width", fRightW);
      if(pstyleRightW != NULL)
         iRightW = pstyleRightW->m_propertyset.find_index(strName + "-right-width");

      if(m_propertyset.has_property(strName + "-bottom") && parse_border_width(m_propertyset[strName + "-bottom"], fBottom))
         pstyleBottom = this;
      else
         pstyleBottom = pdata->m_stylesheeta.rfind_border_width(strTag, strClass, pszSubClass, strName + "-bottom", fBottom);
      if(pstyleBottom != NULL)
         iBottom = pstyleBottom->m_propertyset.find_index(strName + "-bottom");

      if(m_propertyset.has_property(strName + "-bottom-width") && parse_border_width(m_propertyset[strName + "-bottom-width"], fBottomW))
         pstyleBottomW = this;
      else
         pstyleBottomW = pdata->m_stylesheeta.rfind_border_width(strTag, strClass, pszSubClass, strName + "-bottom-width", fBottomW);
      if(pstyleBottomW != NULL)
         iBottomW = pstyleBottomW->m_propertyset.find_index(strName + "-bottom-width");

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


   bool style::get_border_color(const char * pszName, const char * pszSubClass, data * pdata, elemental * pelemental, border & box)
   {
      string strTag;
      if(pelemental->m_propertyset.is_new_or_null("PropertyTag"))
      {
         strTag = pelemental->m_pparent->m_propertyset["PropertyTag"];
      }
      else
      {
         strTag = pelemental->m_propertyset["PropertyTag"];
      }
      string strClass;
      if(pelemental->m_pparent != NULL && pelemental->m_pparent->get_tag()->get_attr_value("class").has_char())
      {
         strClass = pelemental->m_pparent->get_tag()->get_attr_value("class");
      }
      else if(pelemental->get_tag() != NULL)
      {
         strClass = pelemental->get_tag()->get_attr_value("class");
      }
      if(pelemental->m_propertyset.is_new_or_null("PropertyTag"))
      {
         strTag = pelemental->m_pparent->m_propertyset["PropertyTag"];
      }
      else
      {
         strTag = pelemental->m_propertyset["PropertyTag"];
      }
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
      string strName(pszName);

      if(m_propertyset.has_property(strName) && parse_border_color(m_propertyset[strName], cr))
         pstyle = this;
      else
         pstyle = pdata->m_stylesheeta.rfind_border_color(strTag, strClass, pszSubClass, pszName, cr);
      if(pstyle != NULL)
         i = pstyle->m_propertyset.find_index(strName);

      if(m_propertyset.has_property(strName + "-color") && parse_border_color(m_propertyset[strName + "-color"], crW))
         pstyleW = this;
      else
         pstyleW = pdata->m_stylesheeta.rfind_border_color(strTag, strClass, pszSubClass, pszName, crW);
      if(pstyleW != NULL)
         iW = pstyleW->m_propertyset.find_index(strName + "-color");

      if(m_propertyset.has_property(strName + "-left") && parse_border_color(m_propertyset[strName + "-left"], crLeft))
         pstyleLeft = this;
      else
         pstyleLeft = pdata->m_stylesheeta.rfind_border_color(strTag, strClass, pszSubClass, strName + "-left", crLeft);
      if(pstyleLeft != NULL)
         iLeft = pstyleLeft->m_propertyset.find_index(strName + "-left");

      if(m_propertyset.has_property(strName + "-left-color") && parse_border_color(m_propertyset[strName + "-left-color"], crLeftW))
         pstyleLeftW = this;
      else
         pstyleLeftW = pdata->m_stylesheeta.rfind_border_color(strTag, strClass, pszSubClass, strName + "-left-color", crLeftW);
      if(pstyleLeftW != NULL)
         iLeftW = pstyleLeftW->m_propertyset.find_index(strName + "-left-color");

      if(m_propertyset.has_property(strName + "-top") && parse_border_color(m_propertyset[strName + "top"], crTop))
         pstyleTop = this;
      else
         pstyleTop = pdata->m_stylesheeta.rfind_border_color(strTag, strClass, pszSubClass, strName + "-top", crTop);
      if(pstyleTop != NULL)
         iTop = pstyleTop->m_propertyset.find_index(strName + "-top");

      if(m_propertyset.has_property(strName + "-top-color") && parse_border_color(m_propertyset[strName + "-top-color"], crTopW))
         pstyleTopW = this;
      else
         pstyleTopW = pdata->m_stylesheeta.rfind_border_color(strTag, strClass, pszSubClass, strName + "-top-color", crTopW);
      if(pstyleTopW != NULL)
         iTopW = pstyleTopW->m_propertyset.find_index(strName + "-top-color");

      if(m_propertyset.has_property(strName + "-right") && parse_border_color(m_propertyset[strName + "-right"], crRight))
         pstyleRight = this;
      else
         pstyleRight = pdata->m_stylesheeta.rfind_border_color(strTag, strClass, pszSubClass, strName + "-right", crRight);
      if(pstyleRight != NULL)
         iRight = pstyleRight->m_propertyset.find_index(strName + "-right");

      if(m_propertyset.has_property(strName + "-right-color") && parse_border_color(m_propertyset[strName + "-right-color"], crRightW))
         pstyleRightW = this;
      else
         pstyleRightW = pdata->m_stylesheeta.rfind_border_color(strTag, strClass, pszSubClass, strName + "-right-color", crRightW);
      if(pstyleRightW != NULL)
         iRightW = pstyleRightW->m_propertyset.find_index(strName + "-right-color");

      if(m_propertyset.has_property(strName + "-bottom") && parse_border_color(m_propertyset[strName + "-bottom"], crBottom))
         pstyleBottom = this;
      else
         pstyleBottom = pdata->m_stylesheeta.rfind_border_color(strTag, strClass, pszSubClass, strName + "-bottom", crBottom);
      if(pstyleBottom != NULL)
         iBottom = pstyleBottom->m_propertyset.find_index(strName + "-bottom");

      if(m_propertyset.has_property(strName + "-bottom-color") && parse_border_color(m_propertyset[strName + "-bottom-color"], crBottomW))
         pstyleBottomW = this;
      else
         pstyleBottomW = pdata->m_stylesheeta.rfind_border_color(strTag, strClass, pszSubClass, strName + "-bottom-color", crBottomW);
      if(pstyleBottomW != NULL)
         iBottomW = pstyleBottomW->m_propertyset.find_index(strName + "-bottom-color");

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


   bool style::get_color(const char * pszName, const char * pszSubClass, data * pdata, elemental * pelemental, COLORREF & cr)
   {
      string strTag;
      if(pelemental->m_propertyset.is_new_or_null("PropertyTag"))
      {
         strTag = pelemental->m_pparent->m_propertyset["PropertyTag"];
      }
      else
      {
         strTag = pelemental->m_propertyset["PropertyTag"];
      }
      string strClass;
      if(pelemental->m_pparent != NULL && pelemental->m_pparent->get_tag()->get_attr_value("class").has_char())
      {
         strClass = pelemental->m_pparent->get_tag()->get_attr_value("class");
      }
      else if(pelemental->get_tag() != NULL)
      {
         strClass = pelemental->get_tag()->get_attr_value("class");
      }
      if(pelemental->m_propertyset.is_new_or_null("PropertyTag"))
      {
         strTag = pelemental->m_pparent->m_propertyset["PropertyTag"];
      }
      else
      {
         strTag = pelemental->m_propertyset["PropertyTag"];
      }
      if(m_propertyset.is_new_or_null(pszName))
      {
         style * pstyle = pdata->m_stylesheeta.rfind(strTag, strClass, pszSubClass, pszName);
         if(pstyle == NULL)
         {
            if(pelemental->m_pparent != NULL && stricmp_dup(pszName, "background-color"))
            {
               if(pelemental->m_pparent->m_style.get_color(pszName, pszSubClass, pdata, pelemental->m_pparent, cr))
               {
                  return true;
               }
            }
            return false;
         }
         return pstyle->get_color(pszName, pszSubClass, pdata, pelemental, cr);
      }
      cr = parse_color(m_propertyset[pszName]);
      return true;
   }

   bool style::get_text(const char * pszName, const char * pszSubClass, data * pdata, elemental * pelemental, string & str)
   {
      string strTag;
      string strClass;
      if(pelemental->m_propertyset.is_new_or_null("PropertyTag"))
      {
         strTag = pelemental->m_pparent->m_propertyset["PropertyTag"];
         strClass = pelemental->m_pparent->get_tag()->get_attr_value("class");
      }
      else
      {
         strTag = pelemental->m_propertyset["PropertyTag"];
         strClass = pelemental->get_tag()->get_attr_value("class");
      }

      if(m_propertyset.is_new_or_null(pszName))
      {
         style * pstyle = pdata->m_stylesheeta.rfind(strTag, strClass, pszSubClass, pszName);
         if(pstyle == NULL)
         {
            if(pelemental->m_pparent != NULL
            && stricmp_dup(pszName, "padding") != 0
            && stricmp_dup(pszName, "margin") != 0
            && stricmp_dup(pszName, "border") != 0)   
            {
               if(pelemental->m_pparent->m_style.get_text(pszName, pszSubClass, pdata, pelemental->m_pparent, str))
               {
                  return true;
               }
            }
            if(strTag == "h1")
            {
               if(stricmp_dup("font-family", pszName) == 0)
               {
                  str = "Times New Roman";
                  return true;
               }
               else if(stricmp_dup("font-size", pszName) == 0)
               {
                  str = "30";
                  return true;
               }
               else if(stricmp_dup("font-weight", pszName) == 0)
               {
                  str = "bold";
                  return true;
               }
               else
               {
                  return false;
               }
            }
            else if(strTag == "h2")
            {
               if(stricmp_dup("font-family", pszName) == 0)
               {
                  str = "Times New Roman";
                  return true;
               }
               else if(stricmp_dup("font-size", pszName) == 0)
               {
                  str = "23";
                  return true;
               }
               else if(stricmp_dup("font-weight", pszName) == 0)
               {
                  str = "bold";
                  return true;
               }
               else
               {
                  return false;
               }
            }
            else if(strTag == "p")
            {
               if(stricmp_dup("font-family", pszName) == 0)
               {
                  str = "Times New Roman";
                  return true;
               }
               else if(stricmp_dup("font-size", pszName) == 0)
               {
                  str = "11";
                  return true;
               }
               else if(stricmp_dup("font-weight", pszName) == 0)
               {
                  str = "normal";
                  return true;
               }
               else
               {
                  return false;
               }
            }
            else if(strTag == "h3")
            {
               if(stricmp_dup("font-family", pszName) == 0)
               {
                  str = "Times New Roman";
                  return true;
               }
               else if(stricmp_dup("font-size", pszName) == 0)
               {
                  str = "18";
                  return true;
               }
               else if(stricmp_dup("font-weight", pszName) == 0)
               {
                  str = "bold";
                  return true;
               }
               else
               {
                  return false;
               }
            }
            else if (strTag == "strong")
            {
               if (stricmp_dup("font-weight", pszName) == 0)
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
         return pstyle->get_text(pszName, pszSubClass, pdata, pelemental, str);
      }
      str = m_propertyset[pszName];
      string strEm = str;
      if(string(pszName).CompareNoCase("font-size") == 0)
      {
         if(::str::find_awwci("em", str) > 0)
         {
            if(pelemental->m_pparent != NULL)
            {
               string strParent;
               if(pelemental->m_pparent->m_style.get_text(pszName, pszSubClass, pdata, pelemental->m_pparent, strParent))
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

   bool style::get_alpha(const char * pszSubClass, data * pdata, elemental * pelemental, double & d)
   {
      const char* pszName = "opacity";
      string strTag;
      if(pelemental->m_propertyset.is_new_or_null("PropertyTag"))
      {
         strTag = pelemental->m_pparent->m_propertyset["PropertyTag"];
      }
      else
      {
         strTag = pelemental->m_propertyset["PropertyTag"];
      }
      string strClass;
      if(pelemental->m_pparent->get_tag()->get_attr_value("class").has_char())
      {
         strClass = pelemental->m_pparent->get_tag()->get_attr_value("class");
      }
      else if(pelemental->get_tag() != NULL)
      {
         strClass = pelemental->get_tag()->get_attr_value("class");
      }
      if(m_propertyset.is_new_or_null(pszName))
      {
         style * pstyle = pdata->m_stylesheeta.rfind(strTag, strClass, pszSubClass, pszName);
         if(pstyle == NULL)
            return false;
         return pstyle->get_alpha(pszSubClass, pdata, pelemental, d);
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

   bool style::matches(const char * pszTag, const char * pszClass, const char * pszSubClass, const char * pszName)
   {
      if(pszTag != NULL && m_strTag.has_char())
         if(m_strTag != pszTag)
            return false;
      if(pszClass != NULL && m_strName.has_char())
         if(m_strName != pszClass)
            return false;
      if(pszSubClass != NULL && m_strSubClass.has_char())
         if(m_strSubClass != pszSubClass)
            return false;
      if(pszName != NULL)
         if(!m_propertyset.has_property(pszName))
            return false;
      return true;
   }

   bool style::matches_border_width(const char * pszTag, const char * pszClass, const char * pszSubClass, const char * pszName, float & f)
   {
      if(pszTag != NULL && m_strTag.has_char())
         if(m_strTag != pszTag)
            return false;
      if(pszClass != NULL && m_strName.has_char())
         if(m_strName != pszClass)
            return false;
      if(pszSubClass != NULL && m_strSubClass.has_char())
         if(m_strSubClass != pszSubClass)
            return false;
      if(pszName == NULL)
         return false;
      index i = m_propertyset.find_index(pszName);
      if(i < 0)
         return false;
      if(!parse_border_width(m_propertyset.m_propertya[i].get_value().get_string(), f))
         return false;
      return true;
   }

   bool style::matches_border_color(const char * pszTag, const char * pszClass, const char * pszSubClass, const char * pszName, COLORREF & cr)
   {
      if(pszTag != NULL && m_strTag.has_char())
         if(m_strTag != pszTag)
            return false;
      if(pszClass != NULL && m_strName.has_char())
         if(m_strName != pszClass)
            return false;
      if(pszSubClass != NULL && m_strSubClass.has_char())
         if(m_strSubClass != pszSubClass)
            return false;
      if(pszName == NULL)
         return false;
      index i = m_propertyset.find_index(pszName);
      if(i < 0)
         return false;
      if(!parse_border_color(m_propertyset.m_propertya[i].get_value().get_string(), cr))
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

} // namespace html
