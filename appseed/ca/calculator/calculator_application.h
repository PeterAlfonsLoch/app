#pragma once


namespace calculator
{


   class CLASS_DECL_ca application :
      virtual public ::ca2::application
   {
   public:
      application(void);
      virtual ~application(void);

      bool initialize();



      calculator & calculator();

      class calculator * m_pcalculator;
         


   };

} // namespace calculator
