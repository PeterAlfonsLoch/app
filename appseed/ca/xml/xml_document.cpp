#include "StdAfx.h"

namespace xml
{

   document::document(::ca::application * papp) :
      ca(papp),
      node(papp),
      m_parseinfo(papp)
   {
      m_pnodeParent  = NULL;
      m_pdoc         = this;
      m_etype        = node_document;
      m_parseinfo    = *System.m_pparseinfoDefault;
      entitiesHash.set_at("lt", "<");
      entitiesHash.set_at("gt", ">");
      entitiesHash.set_at("quot", "\"");
      entitiesHash.set_at("apos", "'");
      entitiesHash.set_at("amp", "&");
   }

   document::~document()
   {
   }


   document & document::operator = (document & document)
   {
      if(this == &document)
         return *this;
      *get_root() = *document.get_root();
      return *this;
   }

   char * document::load_location(const char * psz)
   {
      m_strLocation = psz;
      string str;
      str = Application.file().as_string(psz);
      return load(str);
   }

   // <?xml version='1.0'?>
   // <TAG attr1="value1" attr2='value2' attr3=value3 >
   // </TAG>
   // or
   // <TAG />
   //        ^- return pointer
   //========================================================
   // Name   : Load
   // Desc   : load xml plain text for xml document
   // Param  : pszXml - plain xml text
   //          pparseinfo = parser information
   // Return : advanced string pointer  (error return NULL)
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   char * document::load(const char * psz)
   {

      m_nodea.remove_all();

      m_strData = psz;
      const char * pszXml = m_strData;
      class node * pnodeRoot = new class node(get_app());
      pnodeRoot->m_pnodeParent = (node *)this;
      pnodeRoot->m_etype = node_element;
      pnodeRoot->m_pdoc = this;
      char * end;

      if( (end = pnodeRoot->load( pszXml, &m_parseinfo )) == NULL )
      {
         delete pnodeRoot;
         return NULL;
      }

      m_nodea.add(pnodeRoot);

      // Load Other Node after </Tag>(pparseinfo, comment, CDATA etc)
      char * ret;
      bool bRet = false;
      ret = pnodeRoot->LoadOtherNodes(&bRet, end, &m_parseinfo );
      if( ret != NULL )
         end = ret;

      return end;
   }

   node * document::get_root()
   {
      index i = 0;
      for( ; i < m_nodea.get_size(); i++)
      {
         xml::node & node = m_nodea[i];
         e_node e_type = node.m_etype;
         if(e_type == node_element || e_type == node_text)
            return &m_nodea[i];
      }
      // Not found: create one.
      class node * pnodeRoot = new class node(get_app());
      pnodeRoot->m_pnodeParent = (node *)this;
      pnodeRoot->m_etype = node_element;
      pnodeRoot->m_pdoc = this;
      m_nodea.add(pnodeRoot);
      return pnodeRoot;
   }
   string document::consume_entity_ref(const char * & pszXml, string & strName, bool useExtEnt, bool & bExt)
   {
      gen::str::consume(pszXml, "&");
      strName.Empty();
      while(*pszXml != ';')
      {
         strName += *pszXml;
         pszXml = gen::str::utf8_inc(pszXml);
      }
      pszXml++;
      string ent = entitiesHash[strName];
      string extEnt;
      if (useExtEnt)
      {
         extEnt = extEntitiesHash[strName];
      }
      if(ent.is_empty() && extEnt.is_empty())
      {
          throw "Undefined Entity Reference";
      }
      if(ent.has_char())
      {
         bExt = false;
         return ent;
      }
      if(extEnt.has_char())
      {
         bExt = true;
         return Application.file().as_string(System.dir().path(System.dir_name(m_strLocation), extEnt));
      }
      return "";
   }

   char * document::patch_entity_ref(const char * & pszXml, bool useExtEnt, ...)
   {
      // pszXml must be a valid portion of and point to an entity ref in:
      // m_strData of this document
      const char * pszOldData = m_strData;
      int iPos = pszXml - pszOldData;
      ASSERT(iPos < m_strData.get_length() && iPos >= 0);
      string strName;
      bool bExt = false;
      string strValue = consume_entity_ref(pszXml, strName, useExtEnt, bExt);
      m_strData = m_strData.Left(iPos) + strValue + m_strData.Mid(iPos + strName.get_length() + 2);
      int iOffset = ((const char *)m_strData) - pszOldData;
      va_list ptr;
      va_start(ptr, useExtEnt);
      INT_PTR p;
      while((p = va_arg(ptr, INT_PTR)) != NULL)
      {
         const char ** ppch = (const char **) p;
         if(*ppch <= (pszOldData + iPos))
         {
            *ppch += iOffset;
         }
         else if(*ppch >= (pszOldData + iPos + strName.get_length() + 2))
         {
            *ppch += iOffset + strValue.get_length() - strName.get_length() - 2;
         }
         else
         {
            throw "pointer to be offset cannot lie inside the entity ref";
         }
      }
      va_end(ptr);
      return (char *) &((const char *)m_strData)[iPos + (bExt ? 0 : strValue.get_length())];
   }

} // namespace xml
