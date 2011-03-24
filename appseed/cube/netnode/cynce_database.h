#pragma once

class CLASS_DECL_CA2_CUBE cynce_database :
   virtual public netnode::database,
   virtual public ptr
{
public:
   cynce_database(::ca::application * papp);
   virtual bool initialize();



};