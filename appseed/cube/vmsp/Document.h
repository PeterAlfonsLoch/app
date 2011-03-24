#pragma once

namespace vmsp
{

   class DocumentInterface;
   class DocumentDataExchange
   {
   protected:
      DocumentInterface *      m_pdocument;
   public:
      DocumentDataExchange(DocumentInterface * pdoc);
      DocumentInterface * get_document();
   };

class CLASS_DECL_CA2_CUBE DocumentInterface  
{
public:
   DocumentInterface();
   virtual ~DocumentInterface();

   virtual void DocumentDX(DocumentDataExchange * pdx);

};

} // namespace vmsp

