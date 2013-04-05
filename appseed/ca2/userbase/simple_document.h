#pragma once


class CLASS_DECL_ca2 simple_document :
   virtual public ::userbase::document
{
public:


   ::ca::property_set       m_set;


   simple_document(::ca::applicationsp papp);
   virtual ~simple_document();

};

