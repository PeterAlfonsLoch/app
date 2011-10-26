#pragma once


namespace tesseract
{

   
   namespace simpledbcfg
   {

      class CLASS_DECL_CA2_TESSERACT area
      {
      public:
         area(::ca::application * papp);
         ::critical_section m_cs;
         ::ca::graphics_sp m_dcSource;
         ::ca::dib_sp m_dib1;
         ::ca::dib_sp m_dib2;
      };

   } // namespace simpledbcfg



} // namespace tesseract


