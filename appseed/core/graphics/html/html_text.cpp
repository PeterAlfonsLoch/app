#include "framework.h"


namespace html
{


   namespace impl
   {


      text::text(sp(base_application) papp) :
         element(papp),
         user::scroll_view(papp),
         ::data::data_listener(papp),
         ::colorertake5::base_editor(papp),
         user::edit_plain_text(papp)
      {

         m_bLink                                         = false;

         m_bSendEnterKey                                 = true;

         m_bOnAfterChangeText                            = false;

      }

      void text::delete_implementation()
      {
         m_bLink = false;
      }

      void text::implement_phase1(data * pdata, ::html::elemental * pelemental)
      {

         ::data::lock lock(pdata);

         ::html::impl::elemental::implement_phase1(pdata, pelemental);
         string strTag;
         if(pelemental->m_propertyset.is_new_or_null("PropertyTag"))
         {
            strTag = pelemental->m_pparent->m_propertyset["PropertyTag"];
         }
         else
         {
            strTag = pelemental->m_propertyset["PropertyTag"];
         }
         if(strTag == "a")
         {
            m_bLink = true;
            if(m_strLink.is_empty())
            {
               if(!pelemental->m_pparent->m_propertyset.is_new_or_null("href"))
               {
                  m_strLink = pelemental->m_pparent->m_propertyset["href"];
               }
               else if(!pelemental->m_propertyset.is_new_or_null("href"))
               {
                  m_strLink = pelemental->m_propertyset["href"];
               }
            }
         }
         if(!IsWindow() && pdata->m_bEdit)
         {
            create(pdata->m_pform, 1004);
         }

         if(pelemental->m_elementalptra.get_size() > 0
         || pelemental->m_propertyset["PropertyBody"].is_empty())
            return;

         ::draw2d::graphics * pdc = pdata->m_pdc;
         if(pdc == NULL)
            return;
         font * pfont = pdata->get_font(m_pelemental);
         if(pfont != NULL)
         {
            pdc->SelectObject(pfont->m_font);
         }
         string str = m_pelemental->m_propertyset["PropertyBody"];

         if(IsWindow() && pdata->m_bEdit)
         {
            _001SetText(str, ::action::source::add(::action::source_data, ::action::source_load));
         }


         ::size size = pdc->GetTextExtent(str);


         m_cxMax = (float) size.cx;


         strsize iLastSpace = 0;
         uchar uch;
         int32_t iSpace = 0;
         string strLine;
         for(int32_t i = 0; i < str.get_length();)
         {
            iSpace = 0;
            uch = (uchar) str[i];
            while(i < str.get_length())
            {
               uch = (uchar) str[i];
               if(!isspace(uch))
                  break;
               iSpace++;
               if(iSpace == 1)
               {
                  if(strLine.get_length() > 0)
                  {
                     strLine += " ";
                     iLastSpace = strLine.get_length();
                  }
               }
               i++;
            }
            if(strLine.get_length() > 0)
            {
               m_straWordSpace.add(strLine);
               strLine.Empty();
            }
            while(i < str.get_length())
            {
               uch = (uchar) str[i];
               if(isspace(uch))
                  break;
               strLine += str[i];
               i++;
            }
            if(strLine.get_length() > 0)
            {
               m_straWordSpace.add(strLine);
               strLine.Empty();
            }
         }
         m_cxMin = 0;
         for(int32_t i = 0; i < m_straWordSpace.get_size(); i++)
         {
            uch = (uchar) m_straWordSpace[i][0];
            if(!isspace(uch))
            {
               size = pdc->GetTextExtent(m_straWordSpace[i]);
               if(size.cx > m_cxMin)
                  m_cxMin = (float) size.cx;
            }
         }
      }


      void text::layout_phase3(data * pdata)
      {

         string strTag;
         bool bParent = false;
         if(m_pelemental->m_propertyset.is_new_or_null("PropertyTag"))
         {
            strTag = m_pelemental->m_pparent->m_propertyset["PropertyTag"];
            bParent = true;
         }
         else
         {
            strTag = m_pelemental->m_propertyset["PropertyTag"];
         }
         ::html::impl::elemental::layout_phase3(pdata);
         if(strTag.CompareNoCase("br") == 0)
         {
//            int32_t iIndex = -1;

            ::draw2d::graphics * pdc = pdata->m_pdc;
            if(pdc == NULL)
               return;
            if(pdata->m_layoutstate.m_cy <= 0)
            {
               pdc->SelectObject(pdata->get_font(m_pelemental)->m_font);
               m_box.set_cx(0);
               class ::size size = pdc->GetTextExtent(unitext("MAÚqg"));
               m_box.set_cy((float) size.cy);
               pdata->m_layoutstate.m_cy = (float) size.cy;
            }
            pdata->m_layoutstate.m_bLastBlockX = true;
            pdata->m_layoutstate.m_bLastBlockY = true;
            return;
         }
/*         if(m_pelemental->m_pbase->get_type() != ::html::base::type_value)
         {
            text::layout_phase1(pdata);
            return;
         }*/

         if(m_pelemental->m_elementalptra.get_size() > 0
         || m_pelemental->m_propertyset["PropertyBody"].is_empty())
         {
            if ((bParent && m_pelemental->m_pparent->m_style.m_propertyset["display"] != "table-cell")
               || (!bParent && m_pelemental->m_style.m_propertyset["display"] != "table-cell"))
            {
               m_box.set_cx(0);
            }
            m_box.set_cy(pdata->m_layoutstate.m_cy);
            pdata->m_layoutstate.m_cx = get_cx();
            if (strTag == "body")
            {
               m_box.set_x(m_margin.left + m_border.left + m_padding.left);
               m_box.set_y(pdata->m_layoutstate.m_cy + m_margin.top + m_border.top + m_padding.top);
               pdata->m_layoutstate.m_x = get_x();
               pdata->m_layoutstate.m_y = get_y();
            }
         }
         else
         {
//            int32_t iIndex = -1;

            ::draw2d::graphics * pdc = pdata->m_pdc;
            if(pdc == NULL)
               return;
            pdc->SelectObject(pdata->get_font(m_pelemental)->m_font);
            string str = m_pelemental->m_propertyset["PropertyBody"];
            m_straLines.remove_all();
            m_sizea.remove_all();
            ::size sizeText;
            int32_t iSpace;
            string strLine;
            uchar uch;
            strsize iLastSpace = 0;
            point pointBound(get_x(), get_y());
            pointBound.x += m_margin.left + m_border.left + m_padding.left;
            float x = pointBound.x;
            size sizeContent = size(get_bound_size());
            sizeContent.cx = max(0, sizeContent.cx - m_padding.left - m_padding.right - m_border.left - m_border.right - m_margin.left - m_margin.right);
            sizeContent.cy = max(0, sizeContent.cy - m_padding.top - m_padding.bottom - m_border.top - m_border.bottom - m_margin.top - m_margin.bottom);
            for(int32_t i = 0; i < str.get_length();)
            {
               iSpace = 0;
               uch = (uchar) str[i];
               while(i < str.get_length())
               {
                  uch = (uchar) str[i];
                  if(!isspace(uch))
                     break;
                  iSpace++;
                  if(iSpace == 1)
                  {
                     if(strLine.get_length() > 0
                     || pdata->m_layoutstate.m_bHasChar)
                     {
                        strLine += " ";
                        iLastSpace = strLine.get_length();
                     }
                  }
                  i++;
               }
               while(i < str.get_length())
               {
                  uch = (uchar) str[i];
                  if(isspace(uch))
                     break;
                  strLine += str[i];
                  i++;
               }
               sizeText = pdc->GetTextExtent(strLine);
               if((x + sizeText.cx) > pointBound.x + sizeContent.cx)
               {
                  if(x > pointBound.x && iLastSpace == 0)
                  {
                     m_straLines.add("");
                     sizeText.cx = 0;
                  }
                  else if(iLastSpace > 0)
                  {
                     sizeText = pdc->GetTextExtent(strLine.Left(iLastSpace));
                     m_straLines.add(strLine.Left(iLastSpace));
                     strLine = strLine.Mid(iLastSpace);
                  }
                  else
                  {
                     m_straLines.add(strLine);
                     strLine.Empty();
                  }
                  m_sizea.add(size(sizeText));
                  iLastSpace = 0;
                  x = pointBound.x;
               }
            }
            if(strLine.get_length() > 0)
            {
               sizeText = pdc->GetTextExtent(strLine);
               m_straLines.add(strLine);
               m_sizea.add(size(sizeText));
            }
            if(pdata->m_bEdit && m_straLines.get_size() == 0)
            {
               m_straLines.add("");
               m_sizea.add(size(0.f, 0.f));
            }
            if((bParent && m_pelemental->m_pparent->m_style.m_propertyset["display"] != "table-cell")
            || (!bParent && m_pelemental->m_style.m_propertyset["display"] != "table-cell"))
            {
               float cx = 0.f;
               if(m_straLines.get_size() > 1)
               {
                  cx = m_sizea.last_element().cx;
               }
               else if(m_straLines.get_size() > 0)
               {
                  cx = m_sizea[0].cx;
               }
               m_box.set_cx(cx);
            }

            float cy = 0.f;
            int32_t i;
            for(i = 0; i < m_sizea.get_size(); i++)
            {
               cy += m_sizea[i].cy;
            }

            if(m_pelemental->m_pparent == NULL)
            {

               m_box.set_cy(cy);

            }
            else
            {

               m_box.set_cy(cy + m_pelemental->m_pparent->m_pimpl->m_padding.top
                            + m_pelemental->m_pparent->m_pimpl->m_padding.bottom
                            + m_pelemental->m_pparent->m_pimpl->m_border.top
                            + m_pelemental->m_pparent->m_pimpl->m_border.bottom
                            + m_pelemental->m_pparent->m_pimpl->m_margin.top
                            + m_pelemental->m_pparent->m_pimpl->m_margin.top);

            }

            if(m_straLines.get_size() > 0)
            {
/*               if(get_y() == pdata->m_layoutstate.m_y)
               {
                  if(pdata->m_layoutstate.m_cy > m_size.cy)
                  {
                     m_pt.y += pdata->m_layoutstate.m_cy - m_size.cy;
                     m_size.cy = pdata->m_layoutstate.m_cy;
                  }
               }*/
               pdata->m_layoutstate.m_cy   = get_cy();
               pdata->m_layoutstate.m_cx   = get_cx();
            }

            //m_size.cx = min(m_size.cx, m_pelemental->m_pparent->m_pimpl->get_cx());
            /*if(m_pelemental->m_pparent->m_pimpl->get_cx() == 0)
            {
               m_size.cy = sizeText.cy;
            }
            else
            {
               m_size.cy = sizeText.cy * ((sizeText.cx / m_pelemental->m_pparent->m_pimpl->get_cx()) + 1);
            }*/
         }
      }

      void text::_001OnDraw(data * pdata)
      {
      COLORREF crBkSel = RGB(120, 240, 150);
      COLORREF crSel = RGB(10, 30, 20);
         string strTag;
         if(m_pelemental->m_propertyset.is_new_or_null("PropertyTag"))
         {
            strTag = m_pelemental->m_pparent->m_propertyset["PropertyTag"];
         }
         else
         {
            strTag = m_pelemental->m_propertyset["PropertyTag"];
         }
         if(strTag == "body")
         {
            rect rect;
            m_box.get(rect);
            COLORREF cr;
            double d;
            if(m_pelemental->m_style.get_alpha(NULL, pdata, m_pelemental, d))
            {
               if(m_bHover && m_pelemental->m_style.get_color("background-color", "hover", pdata, m_pelemental, cr))
               {
                  Sys(pdata->get_app()).visual().imaging().color_blend(
                     pdata->m_pdc,
                     &rect,
                     cr,
                     max(0, min(255, (BYTE)(d * 255))));
               }
               else if(has_link() && m_pelemental->m_style.get_color("background-color", "link", pdata, m_pelemental, cr))
               {
                  Sys(pdata->get_app()).visual().imaging().color_blend(
                     pdata->m_pdc,
                     &rect,
                     cr,
                     max(0, min(255, (BYTE)(d * 255))));
               }
               else if(m_pelemental->m_style.get_color("background-color", NULL, pdata, m_pelemental, cr))
               {
                  Sys(pdata->get_app()).visual().imaging().color_blend(
                     pdata->m_pdc,
                     &rect,
                     cr,
                     max(0, min(255, (BYTE)(d * 255))));
               }
            }
            else
            {
               if(m_bHover && m_pelemental->m_style.get_color("background-color", "hover", pdata, m_pelemental, cr))
               {
                  pdata->m_pdc->FillSolidRect(rect, cr);
               }
               else if(has_link() && m_pelemental->m_style.get_color("background-color", "link", pdata, m_pelemental, cr))
               {
                  pdata->m_pdc->FillSolidRect(rect, cr);
               }
               else if(m_pelemental->m_style.get_color("background-color", NULL, pdata, m_pelemental, cr))
               {
                  pdata->m_pdc->FillSolidRect(rect, cr);
               }
            }
         }
         if(m_pelemental->m_elementalptra.get_size() > 0
         || m_pelemental->m_propertyset["PropertyBody"].is_empty())
            return;
         ::draw2d::graphics * pdc = pdata->m_pdc;
         ::html::impl::elemental::_001OnDraw(pdata);


         COLORREF cr;
         bool bOpaque;
         COLORREF crBkColor;
         if(m_bHover && m_pelemental->m_style.get_color("background-color", "hover", pdata, m_pelemental, cr))
         {
            bOpaque = true;
            //pdc->SetBkMode(OPAQUE);
            //pdc->SetBkColor(cr);
            crBkColor = cr;
         }
         else if(has_link() && m_pelemental->m_style.get_color("background-color", "link", pdata, m_pelemental, cr))
         {
            bOpaque = true;
            //pdc->SetBkMode(OPAQUE);
            //pdc->SetBkColor(cr);
            crBkColor = cr;
         }
         else if(m_pelemental->m_style.get_color("background-color", NULL, pdata, m_pelemental, cr))
         {
            bOpaque = true;
            //pdc->SetBkMode(OPAQUE);
            //pdc->SetBkColor(cr);
            crBkColor = cr;
         }
         else
         {
            bOpaque = false;
            //pdc->SetBkMode(TRANSPARENT);
         }

         ::draw2d::brush_sp brushText(allocer());

         if(m_bHover && m_pelemental->m_style.get_color("color", "hover", pdata, m_pelemental, cr))
         {
            brushText->create_solid(cr);
         }
         else if(has_link() && m_pelemental->m_style.get_color("color", "link", pdata, m_pelemental, cr))
         {
            brushText->create_solid(cr);
         }
         else if(has_link())
         {
            brushText->create_solid(ARGB(255, 127, 127, 255));
         }
         else if(m_pelemental->m_style.get_color("color", "", pdata, m_pelemental, cr))
         {
            brushText->create_solid(cr);
         }
         else
         {
            brushText->create_solid(ARGB(255, 0, 0, 0));
         }

         strsize iSelStart;
         strsize iSelEnd;
         ::size size3;
         visual::graphics_extension(pdata->m_pbaseapp).GetTextExtent(pdc, unitext("gGYIﾍ"), size3);
         int32_t maxcy = size3.cy;

         _001GetViewSel(iSelStart, iSelEnd);
         strsize iCursor = iSelEnd;
         sort::sort(iSelStart, iSelEnd);

         ::html::font * pfont = pdata->get_font(m_pelemental);

         if(pfont != NULL)
         {

            pdc->SelectObject(pfont->m_font);

         }

         float x = get_x();

         float y = get_y();

         if(m_pelemental->m_pparent != NULL)
         {

            x += m_pelemental->m_pparent->m_pimpl->m_border.left + m_pelemental->m_pparent->m_pimpl->m_padding.left + m_pelemental->m_pparent->m_pimpl->m_margin.left;

            y += m_pelemental->m_pparent->m_pimpl->m_border.top + m_pelemental->m_pparent->m_pimpl->m_padding.top + m_pelemental->m_pparent->m_pimpl->m_margin.top;

         }

         float cy = 0;
         string str1;
         string str2;
         string str3;
         string strExtent1;
         string strExtent2;
         string strExtent3;
         strsize lim = 0;

         ::draw2d::brush_sp brushBackground(allocer());

         if(!pdata->m_bEdit)
         {
//            brushText->create_solid(cr);
            pdc->SelectObject(brushText);
         }


        for(int32_t i = 0; i < m_straLines.get_size(); i++)
        {
         string strLine = m_straLines[i];
         float left = i == 0 ? x : m_bound.left;
         float top = y + cy;
         if(pdata->m_bEdit)
         {
            float y = top;
            stringa stra;
            strsize i1 = iSelStart - lim;
            strsize i2 = iSelEnd - lim;
            strsize i3 = iCursor - lim;
            strsize iStart = max(0, i1);
            strsize iEnd = min(i2, strLine.get_length());
            str1 = strLine.Mid(0, iStart);
            str2 = strLine.Mid(iStart, iEnd - iStart);
            str3 = strLine.Mid(iEnd);
            strExtent1 = str1;
            strExtent2 = str2;
            strExtent3 = str3;
            strExtent1.replace("\t", "   ");
            strExtent2.replace("\t", "   ");
            strExtent3.replace("\t", "   ");
            //pdc->SetBkMode(TRANSPARENT);
            brushText->create_solid(cr);
            pdc->SelectObject(brushText);
            //pdc->SetBkColor(crBkSel);
            pdc->TextOut(left, y, strExtent1);
            ::size size1 = pdc->GetTextExtent(strExtent1);

            brushBackground->create_solid(crBkSel);
            //pdc->SetBkMode(OPAQUE);
            pdc->SelectObject(brushBackground);
            ::size size2 = pdc->GetTextExtent(strExtent2);
            pdc->FillSolidRect((int32_t ) ( left + size1.cx), (int32_t) y, size2.cx, size2.cy, crBkSel);

            //pdc->set_text_color(crSel);
            brushText->create_solid(crSel);
            pdc->SelectObject(brushText);
            pdc->TextOut(left + size1.cx, y, strExtent2);

//            pdc->set_text_color(cr);
            brushText->create_solid(cr);
            pdc->SelectObject(brushText);
            //pdc->SetBkColor(RGB(120, 240, 180));
  //          pdc->SetBkMode(TRANSPARENT);
            pdc->TextOut(left + size1.cx + size2.cx, y, strExtent3);

            maxcy = max(size1.cy, size2.cy);
            maxcy = max(maxcy, size3.cy);
            if(m_bFocus && m_bCaretOn && i3 == str1.get_length())
            {
               pdc->MoveTo(left + size1.cx, y);
               pdc->LineTo(left + size1.cx, y + maxcy);
            }
            if(m_bFocus && m_bCaretOn && i3 == (str1.get_length() + str2.get_length()))
            {
               pdc->MoveTo(left + size1.cx + size2.cx, y);
               pdc->LineTo(left + size1.cx + size2.cx, y + maxcy);
            }

         }
         else
         {
            pdc->TextOut(left, top, strLine);
         }


         cy += m_sizea[i].cy;
         lim += strLine.get_length();
        }
        //pdc->FillSolidRect(0, 0, 100, 100, RGB(0, 255, 0));

      }

      float text::get_first_line_height()
      {
         if(m_sizea.get_size() > 0)
         {
            return m_sizea[0].cy;
         }
         else
         {
            return m_box.get_cy();
         }
      }

      float text::get_last_line_height()
      {
         if(m_sizea.get_size() > 0)
         {
            return m_sizea[m_sizea.get_upper_bound()].cy;
         }
         else if(m_pelemental->m_pbase->get_type() == base::type_tag)
         {
            if(m_pelemental->m_elementalptra.get_size() > 0)
            {
               return m_pelemental->m_elementalptra
                  [m_pelemental->m_elementalptra.get_upper_bound()]->m_pimpl->get_last_line_height();
            }
            else
            {
               return m_box.get_cy();
            }
         }
         else
         {
            return m_box.get_cy();
         }
      }

      bool text::get_color(COLORREF & cr)
      {
         if(has_link())
            cr =  ARGB(255, 127, 127, 255);
         else
            cr = ARGB(255, 0, 0, 0);
         return true;
      }

      bool text::has_link()
      {
         if(m_bLink)
         {
            return true;
         }
         else
         {
            return ::html::impl::elemental::has_link();
         }
      }
      string text::link()
      {
         if(m_bLink)
         {
            return m_strLink;
         }
         else
         {
            return ::html::impl::elemental::link();
         }
      }

      int32_t text::hit_test(data * pdoc, ::point pt)
      {
         UNREFERENCED_PARAMETER(pdoc);
         float x = get_x();
//         int32_t y = get_y();
        float cy = 0.f;
        float x1;
        float x2;
//        bool bTag = is_tag();
  //      bool bValue = is_value();
        for(int32_t i = 0; i < m_straLines.get_size(); i++)
        {
           x1 = i == 0 ? x : m_bound.left;
           x2 = x1 + m_sizea[i].cx;
            if(pt.x > x1 && pt.x < x2)
               if(pt.y > m_box.top + cy  && pt.y < m_box.top + cy + m_sizea[i].cy)
                  return 1;
         cy += m_sizea[i].cy;
        }
        return 0;

      }

      void text::OnLButtonDown(signal_details * pobj)
      {
         SCAST_PTR(::html::signal, phtml, pobj);
         if(m_pelemental->m_pdata->m_bEdit)
         {
            if(m_pelemental->m_elementalptra.get_size() == 1)
               m_pelemental->m_elementalptra.first_element()->m_pimpl->OnLButtonDown(pobj);
            else
               _002OnLButtonDown(phtml->m_psignal);
         }
         else
         {
            ::html::impl::elemental::OnLButtonDown(pobj);
         }
      }

      void text::OnLButtonUp(signal_details * pobj)
      {
         SCAST_PTR(::html::signal, phtml, pobj);
         if(m_pelemental->m_pdata->m_bEdit)
         {
            if(m_pelemental->m_elementalptra.get_size() == 1)
               m_pelemental->m_elementalptra.first_element()->m_pimpl->OnLButtonUp(pobj);
            else
               _002OnLButtonUp(phtml->m_psignal);
         }
         else
         {
            ::html::impl::elemental::OnLButtonUp(pobj);
         }
      }

      void text::OnMouseMove(signal_details * pobj)
      {
         SCAST_PTR(::html::signal, phtml, pobj);
         if(!m_bHoverEvaluated)
         {
            bool bHasHover = true;
            if(bHasHover && !has_link())
               bHasHover = false;
            if(bHasHover)
            {
               string strTag;
               if(m_pelemental->m_propertyset.is_new_or_null("PropertyTag"))
               {
                  strTag = m_pelemental->m_pparent->m_propertyset["PropertyTag"];
               }
               else
               {
                  strTag = m_pelemental->m_propertyset["PropertyTag"];
               }
               string strClass;
               if (m_pelemental->m_pparent->get_tag() != NULL && m_pelemental->m_pparent->get_tag()->get_attr_value("class").has_char())
               {
                  strClass = m_pelemental->m_pparent->get_tag()->get_attr_value("class");
               }
               else if (m_pelemental->get_tag() != NULL)
               {
                  strClass = m_pelemental->get_tag()->get_attr_value("class");
               }
               style * pstyle = phtml->m_pdata->m_stylesheeta.rfind(strTag, strClass, "hover", NULL);
               if(pstyle == NULL)
               {
                  bHasHover = false;
               }
            }
            m_bHasHover = bHasHover;
            m_bHoverEvaluated = true;
         }
         SCAST_PTR(::message::mouse, pmouse, phtml->m_psignal);
         ::point pt = pmouse->m_pt;
         phtml->m_pui->ScreenToClient(&pt);
         bool bHover = hit_test(phtml->m_pdata, pt) != 0;
         if(bHover != m_bHover)
         {
            m_bHover = bHover;
            phtml->m_pui->_001RedrawWindow();
         }
         phtml->m_bRet = m_bHover;
         if(m_bHover)
         {
            pmouse->m_ecursor = ::visual::cursor_hand;
         }
         if(m_pelemental->m_pdata->m_bEdit)
         {
            _002OnMouseMove(phtml->m_psignal);
         }
      }

      strsize text::char_hit_test(::draw2d::graphics * pdc, int32_t px, int32_t py)
      {
         string strTag;
         if(m_pelemental->m_propertyset.is_new_or_null("PropertyTag"))
         {
            strTag = m_pelemental->m_pparent->m_propertyset["PropertyTag"];
         }
         else
         {
            strTag = m_pelemental->m_propertyset["PropertyTag"];
         }
         rect rect;
         m_box.get(rect);

         pdc->SelectObject(m_pelemental->m_pdata->get_font(m_pelemental)->m_font);
         float x = get_x();
         float y = get_y();
         float cy = 0;
         if(py < y)
            return 0;
         strsize iFind = 0;
         strsize iLen = 0;
         for(int32_t i = 0; i < m_straLines.get_size(); i++)
         {
            string str = m_straLines[i];
            const char * lpszStart = str;
            const char * lpszEnd = lpszStart;
            float cur_x = i == 0 ? x : m_bound.left;
//            int32_t cur_y = y + cy;
            if(py >= (y + cy) && py < (y + m_sizea[i].cy))
            {
               class ::size size(0, 0);
               strsize iChar = 0;
               while(true)
               {
                  if(px < cur_x + size.cx)
                     return iLen + iChar;
                  size = pdc->GetTextExtent(string(lpszStart, lpszEnd - lpszStart));
                  if(*lpszEnd == '\0')
                     break;
                  lpszEnd = ::str::utf8_inc(lpszEnd);
                  iChar++;
               }
               iFind = iChar;
            }
            else
            {
               iLen += str.get_length();
            }
            cy += m_sizea[i].cy;
         }
         return iFind + iLen;
      }

      void text::_001OnGetText()
      {
      }

      void text::_001OnDraw(::draw2d::graphics * pgraphics)
      {
         UNREFERENCED_PARAMETER(pgraphics);
      }

      void text::_001OnAfterChangeText(::action::context actioncontext)
      {

         if(m_bOnAfterChangeText)
            return;

         keeper < bool > keep(&m_bOnAfterChangeText, true, false, true);

         string strText;

         _001GetText(strText);

         m_pelemental->_001SetText(strText, actioncontext);

         m_pelemental->m_pdata->m_pform->layout();

      }



   } // namespace impl


} // namespace html


