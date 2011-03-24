#include "StdAfx.h"

namespace html
{

   font * document::get_font(elemental * pelemental)
   {
      impl::text * ptext = dynamic_cast < impl::text * > (pelemental->m_pimpl);
      if(ptext != NULL)
      {  
         if(ptext->m_iFont >= 0)
         {
            return &m_fonta[ptext->m_iFont];
         }
         ptext->m_iFont = create_font(pelemental);
         if(ptext->m_iFont >= 0)
         {
            return &m_fonta[ptext->m_iFont];
         }
      }
      return NULL;
   }
   int document::create_font(elemental * pelemental)
   {
      string strTag = pelemental->m_propertyset[PropertyTag]->GetValue().m_str;
      font * pfont = new font;
      if(strTag == "h1")
      {
         pfont->m_strFamily = "Times New Roman";
         pfont->m_strSize = "30";
         pfont->m_strWeight = "bold";
      }
      else if(strTag == "h2")
      {
         pfont->m_strFamily = "Times New Roman";
         pfont->m_strSize = "23";
         pfont->m_strWeight = "bold";
      }
      if(pfont->create())
      {
         m_fonta.Add(pfont);
         pfont->m_iIndex = m_fonta.GetUpperBound();
         return pfont->m_iIndex;
      }
      else
      {
         delete pfont;
         return -1;
      }
   }

   void document::load(const char * psz)
   {
      m_node.Load(psz);
      m_elemental.m_pnode = NULL;
      delete m_elemental.m_pimpl;
      for(int i = 0; i < m_elemental.m_elementalptra.GetSize(); i++)
      {
         delete m_elemental.m_elementalptra[i];
      }
      m_elemental.m_elementalptra.RemoveAll();
      m_elemental.m_pimpl = NULL;
      m_elemental.load(this, &m_node);
   }

   void document::implement(CDC * pdc)
   {
      m_pdc = pdc;
      m_elemental.implement(this);
   }

   void document::_001OnDraw(CDC * pdc)
   {
      m_pdc = pdc;
      m_elemental._001OnDraw(this);
   }

} // namespace html