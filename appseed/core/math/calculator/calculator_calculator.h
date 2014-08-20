#pragma once


namespace calculator
{


   class calculator;


   class CLASS_DECL_CORE calculator :
      virtual public ::base::departament
   {
   public:


      calculator(sp(::axis::application) papp);
      virtual ~calculator();


      bool initialize();


   };


} // namespace calculator


