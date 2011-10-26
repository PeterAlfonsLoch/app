#pragma once


namespace atesseract
{


   class CLASS_DECL_CA2_TESSERACT application : 
      public ::cube::application
   {
   public:


      application();
      virtual ~application();


   };

   inline application & app_cast(::ca::application * papp)
   {
      return *(dynamic_cast < application * > (papp));
   }


} // namespace atesseract