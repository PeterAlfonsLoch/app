#pragma once


namespace tesseract
{

   
   typedef class library (* PFN_GET_NEW_LIBRARY)();


   class CLASS_DECL_CA2_TESSERACT library :
      virtual public ::ca2::single_application_library < ::tesseract::application >,
      virtual public ::ca2::filehandler::library
   {
   public:

      
      virtual void get_app_list(stringa & stra);

      virtual void get_extension_app(stringa & straApp, const char * pszExtension);
      
      virtual void get_extension_list(stringa & stra);


   };




} // namespace tesseract