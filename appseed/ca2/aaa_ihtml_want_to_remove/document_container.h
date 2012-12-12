#pragma once

namespace ihtml
{

class CLASS_DECL_CA2_IHTML document_container :
   virtual public bergedge_object
{
public:

   document_container();   
   virtual ~document_container();

   virtual bool open_document(const char * pszPath) = 0;
   

   document * m_pdocument;
   ca27::http_cookies *  m_pcookies;

};


} // namespace ihtml