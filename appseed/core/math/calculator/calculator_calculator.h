#pragma once


namespace calculator
{


   class calculator;


   class CLASS_DECL_CORE calculator :
      virtual public ::base::departament
   {
   public:


      calculator(::base::application * papp);
      virtual ~calculator();


      bool initialize();


   };


} // namespace calculator


