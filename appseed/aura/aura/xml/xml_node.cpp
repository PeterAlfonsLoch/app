#include "framework.h"


namespace xml
{

   static const CHAR chXMLTagOpen      = '<';
   static const CHAR chXMLTagClose   = '>';
   static const CHAR chXMLTagPre   = '/';
   static const CHAR chXMLEscape = '\\';   // for m_strValue field escape

   static const CHAR szXMLPIOpen[] = "<?";
   static const CHAR szXMLPIClose[] = "?>";
   static const CHAR szXMLDOCTYPEOpen[] = "<!DOCTYPE";
//   static const CHAR szXMLDOCTYPEClose[] = ">";
   static const CHAR szXMLCommentOpen[] = "<!--";
   static const CHAR szXMLCommentClose[] = "-->";
   static const CHAR szXMLCDATAOpen[] = "<![CDATA[";
   static const CHAR szXMLCDATAClose[] = "]]>";

   node::node(::aura::application * papp) :
      element(papp),
      m_nodea(papp),
      m_attra(papp)
   {

      m_attra.m_pnodeParent   = this;
      m_pnodeParent           = NULL;
      m_pdoc                  = NULL;
      m_etype                 = node_document;

   }

   node::node(::xml::node * pnodeParent) :
      element(pnodeParent->get_app()),
      m_nodea(pnodeParent->get_app()),
      m_attra(pnodeParent->get_app())
   {

      m_attra.m_pnodeParent   = this;
      m_pnodeParent           = pnodeParent;
      m_pdoc                  = pnodeParent->m_pdoc;
      m_etype                 = node_element;

   }

   node::node(const node & node) :
      element(node.get_app()),
      m_nodea(node.get_app()),
      m_attra(node.get_app())
   {
      operator = (node);
   }

   node::~node()
   {
      close();
   }


   node & node::operator = (const node & node)
   {

      if(&node == this)
         return *this;

      m_strName   = node.m_strName;
      m_strValue  = node.m_strValue;
      m_nodea     = node.m_nodea;
      m_attra     = node.m_attra;

      return *this;

   }


   attr_array & node::attrs()
   {
      return m_attra;
   }

   var node::attr(const char * lpcszName)
   {
      return m_attra[lpcszName];
   }

   bool node::get_attr(const char * lpcszName, string & strValue)
   {
      if(!m_attra.has_property(lpcszName))
         return false;
      strValue = m_attra[lpcszName];
      return true;
   }

   bool node::get_attr(const char * lpcszName, int32_t & iValue)
   {
      if(!m_attra.has_property(lpcszName))
         return false;
      iValue = m_attra[lpcszName];
      return true;
   }

   bool node::get_attr(const char * lpcszName, bool & bValue)
   {
      if(!m_attra.has_property(lpcszName))
         return false;
      bValue = m_attra[lpcszName];
      return true;
   }

   bool node::contains(attr_array & attra)
   {
      return m_attra.str_contains(attra);
   }

   attr * node::add_attr(const char * pszName, const var & var)
   {

      ::xml::attr * pattr = (::xml::attr *) m_attra.add(pszName, var);

      if(m_pdoc != NULL)
      {

         if(m_pdoc->m_pedit != NULL)
         {

            m_pdoc->m_pedit->add_attr(this, pattr);

         }

      }

      return pattr;

   }

   attr * node::set_attr(const char * lpcszName, const var & var)
   {

      ::xml::attr * pattr = &(m_attra[lpcszName] = var);

      if(m_pdoc != NULL)
      {

         if(m_pdoc->m_pedit != NULL)
         {

            m_pdoc->m_pedit->set_attr(this, pattr);

         }

      }

      return pattr;


   }

   index node::find(const char * lpcszName, attr_array & attra, index iStart)
   {
      for(index i = iStart; i < m_nodea.get_count(); i++)
      {
         if(m_nodea[i]->m_strName == lpcszName && m_nodea[i]->m_attra.str_contains(attra))
            return i;
      }
      return -1;
   }

   node * node::get_child_with_attr(const char * lpcszName, const char * pszAttr, var value, index iStart)
   {
      for(index i = iStart; i < m_nodea.get_count(); i++)
      {
         if(m_nodea[i]->m_strName == lpcszName && m_nodea[i]->attr(pszAttr) == value)
            return m_nodea.element_at(i);
      }
      return NULL;
   }


   index node::find(const char * lpcszName, index iStart)
   {
      for(index i = iStart; i < m_nodea.get_count(); i++)
      {
         if(m_nodea[i]->m_strName == lpcszName)
            return i;
      }
      return -1;
   }
   /*
   bool node::Contains(attr_array & attributea)
   {
      return GetAttributeArray().Contains(attributea);
   }
   */
   /*
   node & node::FindNode(const char * lpcszName,int32_t iPos)
   {
      return GetChildNodeArray().find(lpcszName, iPos);
   }
   */
      index node::find(node * pnode)
      {
         return m_nodea.find_first(pnode);
      }

      node * node::get_next_sibling()
      {
         if(m_pnodeParent == NULL)
            return NULL;
         index i = m_pnodeParent->find(this);
         if(i < 0)
            throw "strange: this is not child of this->parent";
         i++;
         if(i >= m_pnodeParent->get_children_count())
            return NULL;
         return m_pnodeParent->child_at(i);
      }

      node * node::first_child()
      {
         if(m_nodea.get_count() <= 0)
            return NULL;
         return child_at(0);
      }



   char * node::LoadDocType( const char * pszXml, parse_info * pparseinfo)
   {
      if(pparseinfo == NULL)
         pparseinfo = System.xml().m_pparseinfoDefault;
      if(pszXml[0] != '<' || pszXml[1] != '!')
         return (char *) pszXml;

      ::str::consume(pszXml, "<!DOCTYPE");
      ::str::consume_spaces(pszXml);
      ::str::consume_nc_name(pszXml);

      ::str::consume_spaces(pszXml, 0);
      if(::str::begins_consume(pszXml, "SYSTEM"))
      {
         ::str::consume_spaces(pszXml);
         ::str::consume_quoted_value(pszXml);
      }
      else if(::str::begins_consume(pszXml, "PUBLIC"))
      {
         ::str::consume_spaces(pszXml);
         ::str::consume_quoted_value(pszXml);
         ::str::consume_spaces(pszXml);
         ::str::consume_quoted_value(pszXml);
      }

      ::str::consume_spaces(pszXml, 0);

      //markup decl
      if(*pszXml == '[')
      {
         ::str::consume(pszXml, "[");

         while(*pszXml != ']')
         {
            if(::str::begins_consume(pszXml, "<!ENTITY"))
            {
               ::str::consume_spaces(pszXml);
               string entity_name = ::str::consume_nc_name(pszXml);
               ::str::consume_spaces(pszXml);
               string entity_value;
               string ext_entity_value;
               if(::str::begins_consume(pszXml, "SYSTEM"))
               {
                  ::str::consume_spaces(pszXml);
                  ext_entity_value = ::str::consume_quoted_value(pszXml);
               }
               else if (::str::begins_consume(pszXml, "PUBLIC"))
               {
                  ::str::consume_spaces(pszXml);
                  ::str::consume_quoted_value(pszXml);
                  ::str::consume_spaces(pszXml);
                  ext_entity_value = ::str::consume_quoted_value(pszXml);
               }
               else
               {
                  entity_value = ::str::consume_quoted_value(pszXml);
               }
               if(entity_value.has_char())
               {
                  m_pdoc->entitiesHash.set_at(entity_name, entity_value);
               }
               if(ext_entity_value.has_char())
               {
                  m_pdoc->extEntitiesHash.set_at(entity_name, ext_entity_value);
               }
            }
            else if(::str::xml_is_comment(pszXml))
            {
               ::str::xml_consume_comment(pszXml);
            }
            pszXml++;
         }
         ::str::consume(pszXml, "]");
         ::str::consume_spaces(pszXml, 0);
      }


      ::str::consume(pszXml, ">");


      return (char *) pszXml;
   }


   // attr1="value1" attr2='value2' attr3=value3 />
   //                                            ^- return pointer
   //========================================================
   // Name   : LoadAttributes
   // Desc   : loading attr plain xml text
   // Param  : pszAttrs - xml of attributes
   //          pparseinfo = parser information
   // Return : advanced string pointer. (error return NULL)
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   char * node::LoadAttributes( const char * pszAttrs , parse_info * pparseinfo)
   {
      if(pparseinfo == NULL)
         pparseinfo = System.xml().m_pparseinfoDefault;

      char * xml = (char *)pszAttrs;

      while( xml && *xml )
      {
         if( (xml = _tcsskip( xml )) )
         {
            // close tag
            if( *xml == chXMLTagClose || *xml == chXMLTagPre )
               // wel-formed tag
               return xml;

            // XML Attr Name
            CHAR* pEnd = strpbrk( xml, " =" );
            if( pEnd == NULL )
            {
               // error
               if( pparseinfo->m_bErrorOccur == false )
               {
                  pparseinfo->m_bErrorOccur = true;
                  pparseinfo->m_pszErrorPointer = xml;
                  pparseinfo->m_eparseerror = parse_error_attr_no_value;
                  pparseinfo->m_strError.Format( "<%s> attr has error ", m_strName.c_str() );
               }
               return NULL;
            }


            string strName;
              // XML Attr Name
            _SetString( xml, pEnd, &strName );


            // add new attr
            ::xml::attr * pattr = m_attra.add(strName);
            xml = pEnd;

            // XML Attr Value
            if( (xml = _tcsskip( xml )) )
            {
               //if( xml = strchr( xml, '=' ) )
               if( *xml == '=' )
               {
                  if( ((xml = _tcsskip( ++xml )) ))
                  {
                     // if " or '
                     // or none quote
                     int32_t quote = *xml;
                     if( quote == '"' || quote == '\'' )
                        //pEnd = _tcsechr( ++xml, quote, chXMLEscape );
                        pEnd = _tcsechr( ++xml, quote, 0 );
                     else
                     {
                        //attr= m_strValue>
                        // none quote mode
                        //pEnd = _tcsechr( xml, ' ', '\\' );
                        //pEnd = _tcsepbrk( xml, " >", chXMLEscape );
                        pEnd = _tcsepbrk( xml, " >", 0 );
                     }

                     bool trim = pparseinfo->m_bTrimValue;
                     CHAR escape = pparseinfo->m_chEscapeValue;
                     //_SetString( xml, pEnd, &attr->m_strValue, trim, chXMLEscape );
                     string strValue;
                     _SetString( xml, pEnd, &strValue, trim, escape );
                     pattr->set_string(strValue);
                     xml = pEnd;
                     // ATTRVALUE
                     if( pparseinfo->m_bEntityValue && pparseinfo->m_pentities )
                        pattr->set_string(pparseinfo->m_pentities->ref_to_entity(pattr->get_string()));
                     if( quote == '"' || quote == '\'' )
                     {
                        if(*xml == '\0')
                        {
                           return xml;
                           break;
                           // resilliency
                        }
                        else
                        {
                           xml++;
                        }
                     }
                  }
               }
            }
         }
      }

      // not wel-formed tag
      return NULL;
   }


   // <?xml version="1.0"?>
   //                      ^- return pointer
   //========================================================
   // Name   : LoadProcessingInstrunction
   // Desc   : loading processing instruction
   // Param  : pszXml - PI string
   //          pparseinfo - parser information
   // Return : advanced string pointer. (error return NULL)
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2004-06-14
   //========================================================
   char * node::LoadProcessingInstruction( const char * pszXml, parse_info * pparseinfo)
   {
      if(pparseinfo == NULL)
         pparseinfo = System.xml().m_pparseinfoDefault;

      // find the end of pparseinfo
      char * end = _tcsenistr( pszXml, szXMLPIClose, sizeof(szXMLPIClose)-1, pparseinfo ? pparseinfo->m_chEscapeValue : 0 );
      if(end == NULL)
         return NULL;

      while(*end != '\0' && isspace(*end))
         end++;

      if(*end == '\0')
         return NULL;

      // process pparseinfo
      if( m_pdoc )
      {
         char * xml = (char *)pszXml;

         node * pnode = new node(this);
         pnode->m_pnodeParent = this;
         pnode->m_pdoc = m_pdoc;
         pnode->m_etype = node_pi;

         xml += sizeof(szXMLPIOpen)-1;
         CHAR* pTagEnd = strpbrk( xml, " ?>" );
         _SetString( xml, pTagEnd, &pnode->m_strName );
         xml = pTagEnd;

         pnode->LoadAttributes( xml, end, pparseinfo );

         m_pdoc->m_nodea.add( pnode );
      }

      end += sizeof(szXMLPIClose)-1;
      return end;
   }

   // attr1="value1" attr2='value2' attr3=value3 />
   //                                            ^- return pointer
   //========================================================
   // Name   : LoadAttributes
   // Desc   : loading attr plain xml text
   // Param  : pszAttrs - xml of attributes
   //          pszEnd - last string
   //          pparseinfo = parser information
   // Return : advanced string pointer. (error return NULL)
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2004-06-14
   //========================================================
   char * node::LoadAttributes( const char * pszAttrs, const char * pszEnd, parse_info * pparseinfo)
   {
      if(pparseinfo == NULL)
         pparseinfo = System.xml().m_pparseinfoDefault;

      char * xml = (char *)pszAttrs;

      while( xml && *xml )
      {
         if( (xml = _tcsskip( xml )) )
         {
            // close tag
            if( xml >= pszEnd )
               // wel-formed tag
               return xml;

            // XML Attr Name
            CHAR* pEnd = strpbrk( xml, " =" );
            if( pEnd == NULL )
            {
               // error
               if( pparseinfo->m_bErrorOccur == false )
               {
                  pparseinfo->m_bErrorOccur = true;
                  pparseinfo->m_pszErrorPointer = xml;
                  pparseinfo->m_eparseerror = parse_error_attr_no_value;
                  pparseinfo->m_strError.Format( "<%s> attr has error ", m_strName.c_str() );
               }
               return NULL;
            }

            string strName;
            // XML Attr Name
            _SetString( xml, pEnd, &strName );

            // add new attr
            ::xml::attr * pattr = m_attra.add(strName);
            xml = pEnd;

            // XML Attr Value
            if( (xml = _tcsskip( xml )) )
            {
               //if( xml = strchr( xml, '=' ) )
               if( *xml == '=' )
               {
                  if( (xml = _tcsskip( ++xml )) )
                  {
                     // if " or '
                     // or none quote
                     int32_t quote = *xml;
                     if( quote == '"' || quote == '\'' )
                        pEnd = _tcsechr( ++xml, quote, chXMLEscape );
                     else
                     {
                        //attr= m_strValue>
                        // none quote mode
                        //pEnd = _tcsechr( xml, ' ', '\\' );
                        pEnd = _tcsepbrk( xml, " >", chXMLEscape );
                     }

                     bool trim = pparseinfo->m_bTrimValue;
                     CHAR escape = pparseinfo->m_chEscapeValue;
                     //_SetString( xml, pEnd, &attr->m_strValue, trim, chXMLEscape );
                     string strValue;
                     _SetString( xml, pEnd, &strValue, trim, escape );
                     pattr->set_string(strValue);
                     xml = pEnd;
                     // ATTRVALUE
                     if( pparseinfo->m_bEntityValue && pparseinfo->m_pentities )
                        pattr->set_string(pparseinfo->m_pentities->ref_to_entity(pattr->get_string()));
                     if( quote == '"' || quote == '\'' )
                        xml++;
                  }
               }
            }
         }
      }

      // not wel-formed tag
      return NULL;
   }

   // <!-- comment -->
   //                 ^- return pointer
   //========================================================
   // Name   : LoadComment
   // Desc   : loading comment
   // Param  : pszXml - comment string
   //          pparseinfo - parser information
   // Return : advanced string pointer. (error return NULL)
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2004-06-14
   //========================================================
   char * node::LoadComment( const char * pszXml, parse_info * pparseinfo)
   {
      if(pparseinfo == NULL)
         pparseinfo = System.xml().m_pparseinfoDefault;

      // find the end of comment
      char * end = _tcsenistr( pszXml, szXMLCommentClose, sizeof(szXMLCommentClose)-1, pparseinfo ? pparseinfo->m_chEscapeValue : 0 );
      if( end == NULL )
         return NULL;

      // process comment
      node * par = m_pnodeParent;
      if( m_pnodeParent == NULL && m_pdoc )
         par = (node *)&m_pdoc;
      if( par )
      {
         char * xml = (char *)pszXml;
         xml += sizeof(szXMLCommentOpen)-1;

         node * pnode = new node(this);
         pnode->m_pnodeParent = par;
         pnode->m_pdoc = m_pdoc;
         pnode->m_etype = node_comment;
         pnode->m_strName = "#COMMENT";
         _SetString( xml, end, &pnode->m_strValue, FALSE );

         par->m_nodea.add( pnode );
      }

      end += sizeof(szXMLCommentClose)-1;
      return end;
   }

   // <![CDATA[ cdata ]]>
   //                    ^- return pointer
   //========================================================
   // Name   : LoadCDATA
   // Desc   : loading CDATA
   // Param  : pszXml - CDATA string
   //          pparseinfo - parser information
   // Return : advanced string pointer. (error return NULL)
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2004-06-14
   //========================================================
   char * node::LoadCDATA( const char * pszXml, parse_info * pparseinfo)
   {
      if(pparseinfo == NULL)
         pparseinfo = System.xml().m_pparseinfoDefault;

      // find the end of CDATA
      char * end = _tcsenistr( pszXml, szXMLCDATAClose, sizeof(szXMLCDATAClose)-1, pparseinfo ? pparseinfo->m_chEscapeValue : 0 );
      if( end == NULL )
         return NULL;

      // process CDATA
      node * pnodeParent = m_pnodeParent;
      if( m_pnodeParent == NULL && m_pdoc )
         pnodeParent = (node *)&m_pdoc;
      if( pnodeParent )
      {
         char * xml = (char *)pszXml;
         xml += sizeof(szXMLCDATAOpen)-1;

         node * pnode = new node(this);
         pnode->m_pnodeParent = this;
         pnode->m_pdoc = m_pdoc;
         pnode->m_etype = node_cdata;
         pnode->m_strName = "#CDATA";
         _SetString( xml, end, &pnode->m_strValue, FALSE );

         pnodeParent->m_nodea.add( pnode );
      }

      end += sizeof(szXMLCDATAClose)-1;
      return end;
   }



   //========================================================
   // Name   : LoadOtherNodes
   // Desc   : internal function for loading PI/CDATA/Comment
   // Param  : node - current xml node
   //          pbRet - error occur
   //          pszXml - CDATA string
   //          pparseinfo - parser information
   // Return : advanced string pointer. (error return NULL)
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2004-06-14
   //========================================================
   char * node::LoadOtherNodes(bool* pbRet, const char * pszXml, parse_info * pparseinfo)
   {
      if(pparseinfo == NULL)
         pparseinfo = System.xml().m_pparseinfoDefault;

      char * xml = (char *)pszXml;
      bool do_other_type = true;
      *pbRet = false;

      while( xml && do_other_type )
      {
         do_other_type = false;

         xml = _tcsskip( xml );
         char * prev = xml;
         // is PI( Processing Instruction ) Node?
         if(strnicmp_dup( xml, szXMLPIOpen, sizeof(szXMLPIOpen)-1 ) == 0 )
         {
            // processing instrunction parse
            // return pointer is next node of pparseinfo
            xml = LoadProcessingInstruction( xml, pparseinfo );
            //if( xml == NULL )
            //   return NULL;
            // restart xml parse
         }

         if( xml != prev )
            do_other_type = true;
         xml = _tcsskip( xml );
         prev = xml;

         if(m_pnodeParent != NULL && m_pnodeParent->m_etype == node_document)
         {
            // is DOCTYPE
            if(::str::begins(xml, szXMLDOCTYPEOpen))
            {
               // processing instrunction parse
               // return pointer is next node of pparseinfo
               xml = LoadDocType( xml, pparseinfo );
               //if( xml == NULL )
               //   return NULL;
               // restart xml parse
            }

            if( xml != prev )
               do_other_type = true;
            xml = _tcsskip( xml );
            prev = xml;
         }

         // is comment Node?
         if(strnicmp_dup( xml, szXMLCommentOpen, sizeof(szXMLCommentOpen)-1 ) == 0 )
         {
            // processing comment parse
            // return pointer is next node of comment
            xml = LoadComment( xml, pparseinfo );
            // comment node is terminal node
            if(m_pnodeParent != NULL && m_pnodeParent->m_etype != node_document
               && xml != prev )
            {
               *pbRet = true;
               xml = _tcsskip( xml );
               return xml;
            }
            // restart xml parse when this node is root m_pdoc node
         }

         if( xml != prev )
            do_other_type = true;

         xml = _tcsskip( xml );
         prev = xml;
         // is CDATA Node?
         if(strnicmp_dup( xml, szXMLCDATAOpen, sizeof(szXMLCDATAOpen)-1 ) == 0 )
         {
            // processing CDATA parse
            // return pointer is next node of CDATA
            xml = LoadCDATA( xml, pparseinfo );
            // CDATA node is terminal node
            if(m_pnodeParent && m_pnodeParent->m_etype != node_document
               && xml != prev )
            {
               *pbRet = true;
               return xml;
            }
            // restart xml parse when this node is root m_pdoc node
         }

         if( xml != prev )
            do_other_type = true;
      }

      return xml;
   }

   // <TAG attr1="value1" attr2='value2' attr3=value3 >
   // </TAG>
   // or
   // <TAG />
   //        ^- return pointer
   //========================================================
   // Name   : Load
   // Desc   : load xml plain text
   // Param  : pszXml - plain xml text
   //          pparseinfo = parser information
   // Return : advanced string pointer  (error return NULL)
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   char * node::load( const char * pszXml, parse_info * pparseinfo)
   {
      if(pparseinfo == NULL)
         pparseinfo = System.xml().m_pparseinfoDefault;

      // close it
      close();

      char * xml = (char *)pszXml;

      xml = strchr( xml, chXMLTagOpen );
      if( xml == NULL )
         return NULL;

      // close Tag
      if( *(xml+1) == chXMLTagPre ) // </close
         return xml;

      // Load Other Node before <Tag>(pparseinfo, comment, CDATA etc)
      bool bRet = false;
      char * ret = NULL;
      ret = LoadOtherNodes(&bRet, xml, pparseinfo );
      if( ret != NULL )
         xml = ret;
      if( bRet )
         return xml;

      // XML Node Tag Name open
      xml++;
      CHAR* pTagEnd = strpbrk( xml, " />\t\r\n" );
      _SetString( xml, pTagEnd, &m_strName );
      xml = pTagEnd;
      // Generate XML Attributte List
      if( (xml = LoadAttributes( xml, pparseinfo )) )
      {
         // alone tag <TAG ... />
         if(  *xml == chXMLTagPre )
         {
            xml++;
            if( *xml == chXMLTagClose )
               // wel-formed tag
               return ++xml;
            else
            {
               // error: <TAG ... / >
               if( pparseinfo->m_bErrorOccur == false )
               {
                  pparseinfo->m_bErrorOccur = true;
                  pparseinfo->m_pszErrorPointer = xml;
                  pparseinfo->m_eparseerror = parse_error_alone_not_closed;
                  pparseinfo->m_strError = "Element must be closed.";
               }
               // not wel-formed tag
               return NULL;
            }
         }
         else if(*xml)
         // open/close tag <TAG ..> ... </TAG>
         //                        ^- current pointer
         {
            // if text m_strValue is not exist, then assign m_strValue
            //if( this->m_strValue.is_empty() || this->m_strValue == "" )
            if(::str::trimmed_is_empty(m_strValue))
            {
               // Text Value
               CHAR* pEnd = _tcsechr( ++xml, chXMLTagOpen, chXMLEscape );
               if( pEnd == NULL )
               {
                  if( pparseinfo->m_bErrorOccur == false )
                  {
                     pparseinfo->m_bErrorOccur = true;
                     pparseinfo->m_pszErrorPointer = xml;
                     pparseinfo->m_eparseerror = parse_error_not_closed;
                     pparseinfo->m_strError.Format("%s must be closed with </%s>", m_strName.c_str() );
                  }
                  // error cos not exist CloseTag </TAG>
                  return NULL;
               }

               bool trim = pparseinfo->m_bTrimValue;
               CHAR escape = pparseinfo->m_chEscapeValue;
               //_SetString( xml, pEnd, &m_strValue, trim, chXMLEscape );
               pEnd = xml;
               while(*pEnd != '<' && *pEnd != '\0')
               {
                  if(pEnd[0] == '&' && pEnd[1] != '#')
                  {
                     pEnd = m_pdoc->patch_entity_ref((const char * &) pEnd, true, &xml, NULL);
                  }
                  else
                  {
                     pEnd = (char *) ::str::utf8_inc(pEnd);
                  }
               }
               _SetString( xml, pEnd, &m_strValue, trim, escape );
               xml = pEnd;

               // TEXTVALUE reference
               if( pparseinfo->m_bEntityValue && pparseinfo->m_pentities )
                  m_strValue = pparseinfo->m_pentities->ref_to_entity(m_strValue);
            }

            // generate child nodes
            while( xml && *xml )
            {
               node * pnode = new node(this);
               pnode->m_pnodeParent = this;
               pnode->m_pdoc = m_pdoc;
               pnode->m_etype = m_etype;

               xml = pnode->load( xml,pparseinfo );
               if(pnode->m_strName.has_char())
               {
                  m_nodea.add(pnode);
//                  ::release(pnode);
               }
               else
               {
                  delete pnode;
                  pnode = NULL;
               }

               // open/close tag <TAG ..> ... </TAG>
               //                             ^- current pointer
               // CloseTag case
               if( xml && *xml && *(xml+1) && *xml == chXMLTagOpen && *(xml+1) == chXMLTagPre )
               {
                  // </close>
                  xml+=2; // C

                  if( (xml = _tcsskip( xml )) )
                  {
                     string closename;
                     CHAR* pEnd = strpbrk( xml, " >" );
                     if( pEnd == NULL )
                     {
                        if( pparseinfo->m_bErrorOccur == false )
                        {
                           pparseinfo->m_bErrorOccur = true;
                           pparseinfo->m_pszErrorPointer = xml;
                           pparseinfo->m_eparseerror = parse_error_not_closed;
                           pparseinfo->m_strError.Format("it must be closed with </%s>", m_strName.c_str() );
                        }
                        // error
                        return NULL;
                     }
                     _SetString( xml, pEnd, &closename );
                     if( closename == this->m_strName )
                     {
                        // wel-formed open/close
                        xml = pEnd+1;
                        // return '>' or ' ' after pointer
                        return xml;
                     }
                     else
                     {
                        xml = pEnd+1;
                        // 2004.6.15 - example <B> alone tag
                        // now it can parse with attr 'force_arse'
                        if( pparseinfo->m_bForceParse == false )
                        {
                           // not welformed open/close
                           if( pparseinfo->m_bErrorOccur == false )
                           {
                              pparseinfo->m_bErrorOccur = true;
                              pparseinfo->m_pszErrorPointer = xml;
                              pparseinfo->m_eparseerror = parse_error_not_nested;
                              pparseinfo->m_strError.Format("'<%s> ... </%s>' is not wel-formed.", m_strName.c_str(), closename.c_str() );
                           }
                           return NULL;
                        }
                     }
                  }
               }
               else if(xml && *xml)  // Alone child Tag Loaded
                     // else ﾇﾘｾﾟﾇﾏｴﾂﾁ・ｸｻｾﾆｾﾟﾇﾏｴﾂﾁ・ﾀﾇｽﾉｰ｣ｴﾙ.
               {

                  //if( xml && this->m_strValue.is_empty() && *xml !=chXMLTagOpen )
                  if( xml && ::str::trimmed_is_empty(m_strValue) && *xml !=chXMLTagOpen )
                  {
                     // Text Value
                     CHAR* pEnd = _tcsechr( xml, chXMLTagOpen, chXMLEscape );
                     if( pEnd == NULL )
                     {
                        // error cos not exist CloseTag </TAG>
                        if( pparseinfo->m_bErrorOccur == false )
                        {
                           pparseinfo->m_bErrorOccur = true;
                           pparseinfo->m_pszErrorPointer = xml;
                           pparseinfo->m_eparseerror = parse_error_not_closed;
                           pparseinfo->m_strError.Format("it must be closed with </%s>", m_strName.c_str() );
                        }
                        return NULL;
                     }

                     bool trim = pparseinfo->m_bTrimValue;
                     CHAR escape = pparseinfo->m_chEscapeValue;
                     //_SetString( xml, pEnd, &m_strValue, trim, chXMLEscape );
               pEnd = xml;
               while(*pEnd != '<' && *pEnd != '\0')
               {
                  if(pEnd[0] == '&' && pEnd[1] != '#')
                  {
                     pEnd = m_pdoc->patch_entity_ref((const char * &) pEnd, true, &xml, NULL);
                  }
                  else
                  {
                     pEnd = (char *) ::str::utf8_inc(pEnd);
                  }
               }
               _SetString( xml, pEnd, &m_strValue, trim, escape );
               xml = pEnd;
                     //TEXTVALUE
                     if( pparseinfo->m_bEntityValue && pparseinfo->m_pentities )
                        m_strValue = pparseinfo->m_pentities->ref_to_entity(m_strValue);
                  }
               }
            }
         }
      }

      return xml;
   }



   //========================================================
   // Name   : get_xml
   // Desc   : convert plain xml text from parsed xml attirbute
   // Param  :
   // Return : converted plain string
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================

   //========================================================
   // Name   : get_xml
   // Desc   : convert plain xml text from parsed xml node
   // Param  :
   // Return : converted plain string
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   string node::get_xml( disp_option * opt /*= &optDefault*/ )
   {
      string ostring;

      if(opt == NULL)
      {
         opt = System.xml().m_poptionDefault;
      }

      // tab
      if( opt && opt->newline )
      {
         if( opt && opt->newline )
            ostring += "\r\n";
         for( int32_t i = 0 ; i < opt->tab_base ; i++)
            ostring += '\t';
      }

      if( m_etype == node_document )
      {
         for( int32_t i = 0 ; i < m_nodea.get_size(); i++ )
            ostring += m_nodea[i]->get_xml( opt );
         return ostring;
      }
      else
      if( m_etype == node_pi )
      {
         // <?TAG
         ostring += szXMLPIOpen + m_strName;
         // <?TAG Attr1="Val1"
         if(m_attra.has_properties())
            ostring += ' ';
         for( int32_t i = 0 ; i < m_attra.m_propertya.get_size(); i++ )
         {
            ostring += m_attra.m_propertya[i]->get_xml(opt);
         }
         //?>
         ostring += szXMLPIClose;
         return ostring;
      }
      else
      if( m_etype == node_comment )
      {
         // <--comment
         ostring += szXMLCommentOpen + m_strValue;
         //-->
         ostring += szXMLCommentClose;
         return ostring;
      }
      else
      if( m_etype == node_cdata )
      {
         // <--comment
         ostring += szXMLCDATAOpen + m_strValue;
         //-->
         ostring += szXMLCDATAClose;
         return ostring;
      }

      // <TAG
      ostring += '<' + m_strName;

      // <TAG Attr1="Val1"
      if(m_attra.has_properties())
         ostring += ' ';
      for( int32_t i = 0 ; i < m_attra.m_propertya.get_count(); i++ )
      {
         ostring += m_attra.m_propertya[i]->get_xml(opt);
      }

      if( m_nodea.is_empty() && m_strValue.is_empty() )
      {
         // <TAG Attr1="Val1"/> alone tag
         ostring += "/>";
      }
      else
      {
         // <TAG Attr1="Val1"> and get child
         ostring += ">";
         if( opt && opt->newline && !m_nodea.is_empty() )
         {
            opt->tab_base++;
         }

         for( int32_t i = 0 ; i < m_nodea.get_size(); i++ )
            ostring += m_nodea[i]->get_xml( opt );

         string strTrimmedValue = m_strValue;

         strTrimmedValue.trim();
         // Text Value
         if( strTrimmedValue != "" )
         {
            if( opt && opt->newline && !m_nodea.is_empty() )
            {
               if( opt && opt->newline )
                  ostring += "\r\n";
               for( int32_t i = 0 ; i < opt->tab_base ; i++)
                  ostring += '\t';
            }
            ostring += (opt->reference_value&&opt->m_pentities?opt->m_pentities->entity_to_ref(m_strValue):m_strValue);
         }

         // </TAG> CloseTag
         if( opt && opt->newline && !m_nodea.is_empty() )
         {
            ostring += "\r\n";
            for( int32_t i = 0 ; i < opt->tab_base-1 ; i++)
               ostring += '\t';
         }
         ostring += "</" + m_strName + '>';

         if( opt && opt->newline )
         {
            if( !m_nodea.is_empty() )
               opt->tab_base--;
         }
      }

      return ostring;
   }

   //========================================================
   // ﾇﾔｼ・: get_text
   // ｼｳ  ｸ・: ｳ・・ﾇﾏｳｪｸｦ ﾅﾘｽｺﾆｮ ｹｮﾀﾚｿｭｷﾎ ｹﾝﾈｯ
   // ﾀﾎ  ﾀﾚ :
   // ｸｮﾅﾏｰｪ : ｺｯﾈｯｵﾈ ｹｮﾀﾚｿｭ
   //--------------------------------------------------------
   // ﾀﾛｼｺﾀﾚ   ﾀﾛｼｺﾀﾏ                 ﾀﾛｼｺﾀﾌﾀｯ
   // ﾁｶｰ貉ﾎ   2004-06-15
   //========================================================
   string node::get_text( disp_option * opt /*= &optDefault*/ )
   {
      string ostring;

      if( m_etype == node_document )
      {
         for( int32_t i = 0 ; i < m_nodea.get_size(); i++ )
            ostring += m_nodea[i]->get_text( opt );
      }
      else
      if( m_etype == node_pi )
      {
         // no text
      }
      else
      if( m_etype == node_comment )
      {
         // no text
      }
      else
      if( m_etype == node_cdata )
      {
         ostring += m_strValue;
      }
      else
      if( m_etype == node_element )
      {
         if( m_nodea.is_empty() && m_strValue.is_empty() )
         {
            // no text
         }
         else
         {
            // m_nodea text
            for( int32_t i = 0 ; i < m_nodea.get_size(); i++ )
               ostring += m_nodea[i]->get_text();

            // Text Value
            ostring += (opt->reference_value&&opt->m_pentities?opt->m_pentities->entity_to_ref(m_strValue):m_strValue);
         }
      }

      return ostring;
   }

   //========================================================
   // Name   : get_attr
   // Desc   : get attr with attr m_strName
   // Param  :
   // Return :
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   attr * node::find_attr( const char * attrname )
   {
      return m_attra.find(attrname);
      /*for( int32_t i = 0 ; i < m_attra.m_propertya.get_size(); i++ )
      {
         ::xml::attr * attr = &m_attra.m_propertya[i];
         if(attr != NULL)
         {
            if(attr->name() == attrname)
               return attr;
         }
      }
      return NULL;*/
   }

   //========================================================
   // Name   : GetAttrs
   // Desc   : find attributes with attr m_strName, return its list
   // Param  :
   // Return :
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   /*attr_array node::attrs( const char * pszName )
   {

      attr_array attra(get_app());

      for( int32_t i = 0 ; i < m_attra.m_propertya.get_count(); i++ )
      {
         ::xml::attr * attr = &m_attra.m_propertya[i];
         if(attr != NULL)
         {
            if(attr->name() == pszName)
               attra.m_propertya.add(*attr);
         }
      }

      return attra;

   }*/

   //========================================================
   // Name   : get_attr_value
   // Desc   : get attr with attr m_strName, return its m_strValue
   // Param  :
   // Return :
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   /*bool node::get_attr_value( const char * attrname, string & strValue )
   {
      attr * attr = get_attr( attrname );
      if(attr == NULL)
         return false;
      strValue = attr->m_strValue;
      return true;
   }*/

   node::array & node::children()
   {
      return m_nodea;
   }

   //========================================================
   // Name   : GetChilds
   // Desc   : find m_nodea with m_strName and return m_nodea list
   // Param  :
   // Return :
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   node::array node::children( const char * pszName )
   {
      node::array nodea(get_app());
      for( int32_t i = 0 ; i < m_nodea.get_size(); i++ )
      {
         node * node = m_nodea[i];
         if( node )
         {
            if( node->m_strName == pszName )
               nodea.add( node );
         }
      }
      return nodea;
   }

   //========================================================
   // Name   : get_child
   // Desc   : get child node with index
   // Param  :
   // Return : NULL return if no child.
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   node * node::child_at(index i )
   {
      if( i >= 0 && i < m_nodea.get_size() )
         return m_nodea[i];
      return NULL;
   }

   //========================================================
   // Name   : GetChildCount
   // Desc   : get child node count
   // Param  :
   // Return : 0 return if no child
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-12-26
   //========================================================
   ::count node::get_children_count(const char * pszName )
   {
      if(pszName == NULL || *pszName == '\0')
      {
         return get_children_count();
      }
      else
      {
         ::count count = 0;
         for(int32_t i = 0; i < m_nodea.get_count(); i++)
         {
            if(m_nodea[i]->m_strName == pszName)
               count++;
         }
         return count;
      }
   }
   ::count node::get_children_count()
   {
      return m_nodea.get_count();
   }

   ::count node::get_children_count(const char * pszName, index iDepth)
   {
      if(iDepth == 0)
         return 0;
      ::count count = 0;
      for(index i = 0; i < m_nodea.get_count(); i++)
      {
         if(pszName == NULL || *pszName == '\0')
         {
            count++;
         }
         else
         {
            if(m_nodea[i]->m_strName == pszName)
               count++;
         }
         if(iDepth < 0)
            count += m_nodea[i]->get_children_count(pszName, -1);
         else
            count += m_nodea[i]->get_children_count(pszName, iDepth - 1);
      }
      return count;
   }

   //========================================================
   // Name   : get_child
   // Desc   : find child with m_strName and return child
   // Param  :
   // Return : NULL return if no child.
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   node * node::get_child(const char * pszName)
   {
      index iStart = 0;
      return get_child(pszName, iStart);
   }

   node *        node::get_node_from_attr_path(const char * path, const char * pszName, const char * pszAttr)
   {
      stringa stra;
      stra.explode("/", path);
      ::xml::node  * pnode = this;
      if(stra.get_size() <= 0 || (stra.get_size() == 1 && stra[0].get_length() == 0))
         return this;
      for(int32_t i = 0; i < stra.get_size(); i++)
      {
         pnode = pnode->get_child_with_attr(pszName, pszAttr, stra[i]);
         if(pnode == NULL)
            return NULL;
      }
      return pnode;
   }

   string                  node::get_child_simple_attr_path(node * pnode, const char * pszAttr)
   {
      string str;
      while(pnode != NULL && pnode != this)
      {
         str = pnode->attr(pszAttr).get_string() + ::str::has_char(str, "/");
         pnode = pnode->m_pnodeParent;
      }
      if(pnode == NULL)
         return "";
      else if(pnode != this)
         return "";
      return str;

   }


   node * node::get_node_from_simple_path(const char * path)
   {
      stringa stra;
      stra.explode("/", path);
      ::xml::node  * pnode = this;
      if(stra.get_size() <= 0 || (stra.get_size() == 1 && stra[0].get_length() == 0))
         return this;
      for(int32_t i = 0; i < stra.get_size(); i++)
      {
         pnode = pnode->get_child(stra[i]);
         if(pnode == NULL)
            return NULL;
      }
      return pnode;
   }

   node * node::get_node_from_indexed_path(const index_array & iaPath)
   {

      node * pnode = this;

      if(pnode == NULL)
         return NULL;

      for(index iLevel = 0; iLevel < iaPath.get_count(); iLevel++)
      {

         index iIndex = iaPath[iLevel];

         if(iIndex < 0)
            return NULL;

         if(iIndex >= pnode->get_children_count())
            return NULL;

         pnode = pnode->child_at(iIndex);

         if(pnode == NULL)
            return NULL;

      }

      return pnode;
   }

   string node::get_child_simple_path(const node * pnode) const
   {
      string str;
      while(pnode != NULL && pnode != this)
      {
         str = pnode->m_strName + ::str::has_char(str, "/");
         pnode = pnode->m_pnodeParent;
      }
      if(pnode == NULL)
         return "";
      else if(pnode != this)
         return "";
      return str;
   }

   void node::get_child_indexed_path(index_array & iaPath, const node * pnode) const
   {

      iaPath.remove_all();
      while(pnode != NULL && pnode != this)
      {
         iaPath.insert_at(0, pnode->get_index());
         pnode = pnode->m_pnodeParent;
      }

   }

   index_array node::get_child_indexed_path(const node * pnode) const
   {

      index_array iaPath;
      get_child_indexed_path(iaPath, pnode);
      return iaPath;

   }

   node * node::get_child(const char * pszName, index & iStartPosition)
   {
      for(index i = iStartPosition; i < m_nodea.get_size(); i++ )
      {
         if(m_nodea[i]->m_strName.compare(pszName) == 0)
            return m_nodea[i];
      }
      return NULL;
   }


   //========================================================
   // Name   : GetChildValue
   // Desc   : find child with m_strName and return child's m_strValue
   // Param  :
   // Return : NULL return if no child.
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   string   node::get_child_value( const char * pszName )
   {
      node * node = get_child( pszName );
      return (node != NULL)? (const char *)node->m_strValue : NULL;
   }

   string   node::get_child_text( const char * pszName, disp_option * opt /*= &optDefault*/ )
   {
      node * node = get_child( pszName );
      return (node != NULL)? node->get_text(opt) : "";
   }

   attr * node::GetChildAttr( const char * pszName, const char * attrname )
   {
      node * node = get_child(pszName);
      return node ? node->find_attr(attrname) : NULL;
   }

   string node::GetChildAttrValue( const char * pszName, const char * attrname )
   {
      ::xml::attr * attr = GetChildAttr( pszName, attrname );
      return attr ? attr->get_string() : string("");
   }

   //========================================================
   // Name   : find
   // Desc   : find node with tag pszName from it's all m_nodea
   // Param  :
   // Return : NULL return if no found node.
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   node * node::rfind( const char * pszName, int32_t iDepth)
   {
      index i = 0;
      for( ; i < m_nodea.get_size(); i++)
      {
         if(m_nodea[i]->m_strName == pszName )
            return m_nodea[i];
      }
      if(iDepth == 0)
         return NULL;
      if(iDepth > 0)
      {
         iDepth--;
      }
      i = 0;
      for( ; i < m_nodea.get_size(); i++)
      {
         node * lpnodeChild = m_nodea[i];
         lpnodeChild = lpnodeChild->rfind(pszName, iDepth);
         if(lpnodeChild != NULL)
            return lpnodeChild;
      }
      return NULL;
   }


   //========================================================
   // Name   : add_child
   // Desc   : add node
   // Param  :
   // Return :
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   node * node::add_child( const char * pszName /*= NULL*/, const char * pszValue /*= NULL*/ )
   {
      node * pnode = new node(this);
      pnode->m_strName = pszName;
      pnode->m_strValue = pszValue;
      return add_child(pnode);
   }

   //========================================================
   // Name   : add_child
   // Desc   : add node
   // Param  :
   // Return :
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   node * node::add_child( node * node )
   {
      node->m_pnodeParent = this;
      node->m_pdoc = m_pdoc;
      m_nodea.add( node );
      return node;
   }

   //========================================================
   // Name   : remove_child
   // Desc   : detach node and delete object
   // Param  :
   // Return :
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   bool node::remove_child( node * pnode )
   {
      if(m_nodea.remove(pnode) > 0)
      {
         delete pnode;
         return true;
      }
      return false;
   }

   //========================================================
   // Name   : get_attr
   // Desc   : get attr with index in attr list
   // Param  :
   // Return :
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   attr * node::attr_at( index i )
   {
      return m_attra.m_propertya[i];
   }


   //========================================================
   // Name   : add_attr
   // Desc   : add attr
   // Param  :
   // Return :
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   attr * node::add_attr(const ::xml::attr & attr)
   {

      m_attra[attr.name()].set_string(attr.get_value());

      return find_attr(attr.name());

   }

   //========================================================
   // Name   : remove_attr
   // Desc   : detach attr and delete object
   // Param  :
   // Return :
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   bool node::remove_attr(::xml::attr * pattr )
   {
      if(m_attra.remove_by_name(pattr->name()) > 0)
      {
         delete pattr;
         return true;
      }
      return false;
   }


   //========================================================
   // Name   : add_attr
   // Desc   : add attr
   // Param  :
   // Return :
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
 // /*   attr * node::add_attr( const char * pszName /*= NULL*/, /*const char * pszValue /*= NULL*/ /*)
  /* {

      ::xml::attr * pattr = (::xml::attr *) m_attra.add(pszName, pszValue);

      if(m_pdoc != NULL)
      {

         if(m_pdoc->m_pedit != NULL)
         {

            m_pdoc->m_pedit->add_attr(this, pattr);

         }

      }

      return pattr;

   }*/

   //========================================================
   // Name   : detach_child
   // Desc   : no delete object, just detach in list
   // Param  :
   // Return :
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   node * node::detach_child( node * node )
   {
      index find = m_nodea.find_first(node);
      if(find >= 0)
      {
         m_nodea.remove_at(find);
         return node;
      }
      return NULL;
   }

   //========================================================
   // Name   : detach_attr
   // Desc   : no delete object, just detach in list
   // Param  :
   // Return :
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
/*   attr  node::detach_attr(::xml::attr * attr )
   {
      attr = m_attra.m_propertymap[attr]find_first((property *) attr);
      if(find >= 0)
      {
         a
         m_attra.m_propertya.remove_at(find);
         return attr;
      }
      return NULL;
   }*/

   //========================================================
   // Name   : CopyNode
   // Desc   : copy current level node with own attributes
   // Param  :
   // Return :
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   void node::CopyNode( node * node )
   {

      close();

      m_pdoc         = node->m_pdoc;
      m_pnodeParent  = node->m_pnodeParent;
      m_strName      = node->m_strName;
      m_strValue     = node->m_strValue;
      m_etype        = node->m_etype;
      m_attra        = node->m_attra;

   }

   //========================================================
   // Name   : _CopyBranch
   // Desc   : recursive internal copy branch
   // Param  :
   // Return :
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   void node::_CopyBranch( node * pnode )
   {

      CopyNode(pnode);

      for( int32_t i = 0 ; i < pnode->m_nodea.get_size(); i++)
      {
         class node * pnodeChild = pnode->m_nodea.element_at(i);
         if(pnodeChild)
         {
            class node * pnodeNewChild = new class node(get_app());
            pnodeNewChild->CopyNode(pnodeChild);
            add_child(pnodeNewChild);
            pnodeNewChild->_CopyBranch(pnodeChild);
         }
      }

   }

   //========================================================
   // Name   : AppendChildBranch
   // Desc   : add child branch ( deep-copy )
   // Param  :
   // Return :
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   node *   node::AppendChildBranch(node * pnode)
   {
      class node * pnodeNewChild = new class node(get_app());
      pnodeNewChild->CopyBranch(pnode);
      return add_child( pnodeNewChild );
   }

   //========================================================
   // Name   : CopyBranch
   // Desc   : copy branch ( deep-copy )
   // Param  :
   // Return :
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   void node::CopyBranch( node * branch )
   {
      close();

      _CopyBranch( branch );
   }


   node *                  node::get_child_at(const char * pszName, index iIndex, index iDepth)
   {
      if(iDepth == 0)
         return 0;

      if(iIndex < 0)
         return NULL;

      for(int32_t i = 0; i < m_nodea.get_size(); i++)
      {
         if(m_nodea[i].m_strName == pszName)
         {
            if(iIndex <= 0)
               return m_nodea.element_at(i);
            iIndex--;
         }
         if(iDepth > 0)
            m_nodea[i].get_child_at(pszName, iIndex, iDepth - 1);
         else if(iDepth < 0)
            m_nodea[i].get_child_at(pszName, iIndex, -1);
      }
      return NULL;

   }

   // iDepth
   // -1 recursive
   // 0 nothing
   // 1 children
   // 2 children and children of children
   ::count node::get_child_attr_value(stringa & stra, const char * pszName, const char * pszAttrName, index iDepth)
   {

      if(iDepth == 0)
         return 0;

      string strValue;
      ::count count = 0;
      for(int32_t i = 0; i < m_nodea.get_size(); i++)
      {
         if(m_nodea[i].m_strName == pszName)
         {
            if(m_nodea[i].get_attr(pszAttrName, strValue))
            {
               count++;
               stra.add(strValue);
            }
         }
         if(iDepth > 0)
            count += m_nodea[i].get_child_attr_value(stra, pszName, pszAttrName, iDepth - 1);
         else if(iDepth < 0)
            count += m_nodea[i].get_child_attr_value(stra, pszName, pszAttrName, -1);
      }
      return count;
   }

   // iDepth
   // -1 recursive
   // 0 nothing
   // 1 children
   // 2 children and children of children
   ::count node::remove_child_with_attr(const char * pszName, const char * pszAttrName, index iIndex, ::count iCount, index iDepth)
   {

      ::count nRemoveCount = 0;

      if(iDepth == 0)
         return 0;

      string strValue;
      ::count count = 0;
      for(index i = 0; i < m_nodea.get_size(); )
      {
         if(m_nodea[i].m_strName == pszName)
         {
            if(m_nodea[i].get_attr(pszAttrName, strValue))
            {
               if(iIndex <= 0)
               {
                  if(iCount <= 0)
                  {
                     return count;
                  }
                  else
                  {
                     iCount--;
                     count++;
                     m_nodea.remove_at(i);
                     continue;
                  }
               }
               else
               {
                  iIndex--;
               }
            }
         }
         if(iDepth > 0)
            nRemoveCount = m_nodea[i].remove_child_with_attr(pszName, pszAttrName, iIndex, iCount, iDepth - 1);
         else if(iDepth < 0)
            nRemoveCount = m_nodea[i].remove_child_with_attr(pszName, pszAttrName, iIndex, iCount, -1);
         if(nRemoveCount > 0)
         {
            count    += nRemoveCount;
            iCount   -= nRemoveCount;
            iIndex   = 0;
            if(iCount <= 0)
            {
               return count;
            }
         }
         i++;
      }
      return count;
   }

   node * node::GetChildByAttr(const char * pszName, const char * pszAttrName, const char * pszAttrValue)
   {
      string strValue;
      for(int32_t i = 0; i < m_nodea.get_size(); i++)
      {
         if(m_nodea[i].m_strName == pszName)
         {
            if(m_nodea[i].get_attr(pszAttrName, strValue)
               && stricmp_dup(strValue, pszAttrValue) == 0)
            {
               return m_nodea(i);
            }
         }
      }
      return NULL;
   }

   node * node::GetChildByAnyAttr(const char * pszName, stringa & straAttrName, stringa & straAttrValue)
   {
      string strValue;
      for(int32_t i = 0; i < m_nodea.get_size(); i++)
      {
         if(m_nodea[i].m_strName == pszName)
         {
            for(int32_t j = 0; j < straAttrName.get_size(); j++)
            {
               if(m_nodea[i].get_attr(straAttrName[j], strValue) && stricmp_dup(strValue, straAttrValue[j]) == 0)
               {
                  return m_nodea(i);
               }
            }
         }
      }
      return NULL;
   }

   node * node::GetChildByAllAttr(const char * pszName, stringa & straAttrName, stringa & straAttrValue)
   {
      string strValue;
      for(int32_t i = 0; i < m_nodea.get_size(); i++)
      {
         if(m_nodea[i].m_strName == pszName)
         {
            bool bAll = true;
            for(int32_t j = 0; j < straAttrName.get_size(); j++)
            {
               if(!m_nodea[i].get_attr(straAttrName[j], strValue) || stricmp_dup(strValue, straAttrValue[j]) != 0)
               {
                  bAll = false;
                  break;
               }
            }
            if(bAll)
            {
               return m_nodea(i);
            }
         }
      }
      return NULL;
   }

   void node::close()
   {
      m_nodea.remove_all();
      m_attra.clear();
   }

   bool node::from_row_column_v2(const string2a & str2a)
   {
      m_strName = "row_column_v2";
      if(str2a.get_size() <= 0)
      {
         m_strValue.Empty();
         add_attr("column_count", 0);
         m_nodea.remove_all();
      }
      else
      {
         ::count iColCount = str2a.get_count();
         add_attr("column_count", iColCount);
         ::count iRowCount;

         for(index iCol = 0; iCol < iColCount; iCol++)
         {
            sp(::xml::node) pcol = add_child("ca");
            iRowCount = str2a[iCol].get_count();
            pcol->add_attr("row_count", iRowCount);
            for(int32_t iRow = 0; iRow < iRowCount; iRow++)
            {
//               sp(::xml::node) prow = add_child("r");
               if(iRow < str2a[iCol].get_count())
               {
                  pcol->m_strValue = str2a[iCol].element_at(iRow);
               }
            }
         }
      }
      return true;
   }


   bool node::to_row_column_v2(string2a & str2a)
   {
      // "this is not a row column v2 xml node";
      if(m_strName != "row_column_v2")
         return false;
      ::count iColCount = attr("column_count");
      if(m_nodea.get_count() == 0 ||  iColCount <= 0)
      {
         str2a.remove_all();
         return true;
      }
      str2a.set_size(iColCount);
      ::count iRowCount = 0;
      sp(::xml::node) pheader = m_nodea.element_at(0);
      for(::index iCol = 0; iCol < iColCount; iCol++)
      {
         sp(::xml::node) pcol = pheader->m_nodea.element_at(iCol);
         str2a[iCol].set_size(pcol->attr("row_count"));
      }
      for(::index iRow = 0; iRow < iRowCount; iRow++)
      {
//         sp(::xml::node) prow = m_nodea.element_at(0);
         for(int32_t iCol = 0; iCol < str2a[iCol].get_count(); iCol++)
         {
//            sp(::xml::node) pcol = prow->add_child("ca");
            if(iRow < str2a[iCol].get_count())
            {
               //pcol->m_strValue =
               iRowCount = str2a[iCol].get_count();
            }
         }
      }

      return true;

   }

   void node::write(::file::output_stream & ostream)
   {

      string str = get_xml();
      ostream << str;

   }

   void node::read(::file::input_stream & istream)
   {

      close();

      string str;
      istream >> str;
      load(str);

   }

   void node::set_name(const string & strName)
   {

      m_strName = strName;

      if(m_pdoc != NULL)
      {

         if(m_pdoc->m_pedit != NULL)
         {

            m_pdoc->m_pedit->set_name(this);

         }

      }

   }

   void node::set_value(const string & strValue)
   {

      m_strValue = strValue;

      if(m_pdoc != NULL)
      {

         if(m_pdoc->m_pedit != NULL)
         {

            m_pdoc->m_pedit->set_value(this);

         }

      }

   }

   string node::get_simple_path() const
   {

      return get_document()->get_child_simple_path(this);

   }

   index_array node::get_indexed_path() const
   {

      return get_document()->get_child_indexed_path(this);

   }

   void node::get_indexed_path(index_array & iaPath) const
   {

      return get_document()->get_child_indexed_path(iaPath, this);

   }

   index node::get_index() const
   {

      if(m_pnodeParent == NULL)
         return -1;


      for(index iIndex = 0; iIndex < m_pnodeParent->m_nodea.get_count(); iIndex++)
      {

         if(m_pnodeParent->m_nodea.element_at(iIndex) == this)
            return iIndex;

      }

      return -1;

   }


} // namespace xml
