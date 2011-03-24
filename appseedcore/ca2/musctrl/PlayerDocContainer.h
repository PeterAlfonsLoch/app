#pragma once

class ::userbase::document;

namespace musctrl
{

class CLASS_DECL_ca PlayerDocContainer :
   virtual public ::radix::object
{
public:
   PlayerDocContainer();
   virtual ~PlayerDocContainer();

//   virtual ::userbase::document * GetPlayerDoc() = 0;
   virtual ::userbase::document * GetXfplayerDoc();


};

} //namespace musctrl
