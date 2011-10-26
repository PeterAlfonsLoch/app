#pragma once


namespace musctrl
{

   class single_document_template;

   class CLASS_DECL_ca MusicalPlayerCentral :
      virtual public ::radix::object
   {
   public:
      
      
      ::ca::type_info               m_typeinfoDocument;
      ::ca::type_info               m_typeinfoFrameWnd;
      ::ca::type_info               m_typeinfoView;
      ::ca::type_info               m_typeinfoIPFrame;

      string                        m_strMatter;
      single_document_template *    m_pdoctemplate;


      MusicalPlayerCentral(::ca::application * papp);
      virtual ~MusicalPlayerCentral();

   
      static MusicalPlayerCentral & AppGetMusicalPlayerCentral(::ca::application * papp);
      single_document_template * get_document_template();
      single_document_template * CreateDocTemplate();

   };

} // namespace musctrl
