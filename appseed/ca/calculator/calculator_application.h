#pragma once


namespace calculator
{


   class calculator;


   class CLASS_DECL_ca application :
      virtual public ::ca2::application
   {
   public:


      class ::calculator::calculator  * m_pcalculator;


      application(void);
      virtual ~application(void);


      bool initialize();


      class ::calculator::calculator & calculator();


   };


} // namespace calculator


