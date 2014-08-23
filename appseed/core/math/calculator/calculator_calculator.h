#pragma once


namespace calculator
{


   class calculator;


   class CLASS_DECL_CORE calculator :
      virtual public ::aura::departament
   {
   public:


      calculator(sp(::aura::application) papp);
      virtual ~calculator();


      bool initialize();


   };


} // namespace calculator


