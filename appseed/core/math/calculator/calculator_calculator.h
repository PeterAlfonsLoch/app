#pragma once


namespace calculator
{


   class calculator;


   class CLASS_DECL_ca2 calculator :
      virtual public ::base_departament
   {
   public:


      calculator(base_application * papp);
      virtual ~calculator();


      bool initialize();


   };


} // namespace calculator


