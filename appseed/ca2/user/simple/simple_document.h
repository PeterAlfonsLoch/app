#pragma once


class CLASS_DECL_ca2 simple_document :
   virtual public ::user::document
{
public:


   ::ca2::property_set       m_set;


   simple_document(sp(::ca2::application) papp);
   virtual ~simple_document();

};

