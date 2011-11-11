#pragma once


class CLASS_DECL_ca simple_document :
   virtual public ::userbase::document
{
public:


   gen::property_set       m_set;


   simple_document(::ca::application * papp);
   virtual ~simple_document();

};

