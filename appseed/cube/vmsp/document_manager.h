#pragma once

namespace vmsp
{

   class document_manager : 
      public ::radix::object
   {
   public:

      
      ::userbase::single_document_template *   m_pdoctemplateAudioSpectrum;

      
      document_manager(::ca::application * papp);
      virtual ~document_manager();


      bool UpdateRegistry();
      bool CreateTemplates();

   };

} // namespace vmsp
