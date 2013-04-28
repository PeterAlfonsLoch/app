#pragma once


namespace calculator
{


   class calculator;


   class CLASS_DECL_ca2 calculator :
      virtual public ::ca::section
   {
   public:


      calculator(::ca::application * papp);
      virtual ~calculator();


      bool initialize();


   };


} // namespace calculator


