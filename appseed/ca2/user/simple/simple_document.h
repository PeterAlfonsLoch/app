#pragma once


class CLASS_DECL_ca2 simple_document :
   virtual public ::user::document
{
public:


   property_set       m_set;


   simple_document(sp(::application) papp);
   virtual ~simple_document();

};

