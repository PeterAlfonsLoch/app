#pragma once


namespace html
{


   class CLASS_DECL_ca application :
      virtual public ::ca5::application
   {
   public:


      
      class html_ex * m_phtmlex;

      application();
      virtual ~application();

      virtual bool initialize();

      html_ex & html_ex();


   };

} // namespace html