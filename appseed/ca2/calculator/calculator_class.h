#pragma once

namespace calculator
{

   class CLASS_DECL_ca calculator :
      virtual public ::radix::object
   {
   public:
      calculator(::ax::application * papp);
      virtual ~calculator();
   };



} // namespace calculator