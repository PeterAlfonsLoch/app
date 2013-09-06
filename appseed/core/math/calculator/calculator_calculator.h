#pragma once


namespace calculator
{


   class calculator;


   class CLASS_DECL_ca2 calculator :
      virtual public ::departament
   {
   public:


      calculator(application * papp);
      virtual ~calculator();


      bool initialize();


   };


} // namespace calculator


