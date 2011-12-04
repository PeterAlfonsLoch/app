#pragma once


namespace calculator
{


   class CLASS_DECL_ca2 application :
      virtual public ::ca8::application
   {
   public:
      application(void);
      virtual ~application(void);

      bool initialize();



      calculator & calculator();

      class calculator * m_pcalculator;
         


   };

} // namespace calculator
