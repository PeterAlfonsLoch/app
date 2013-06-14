#pragma once


namespace calculator
{


   class calculator;


   class CLASS_DECL_ca2 calculator :
      virtual public ::ca2::section
   {
   public:


      calculator(::ca2::application * papp);
      virtual ~calculator();


      bool initialize();


   };


} // namespace calculator


