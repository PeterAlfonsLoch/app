#pragma once


class CLASS_DECL_CORE simple_document :
   virtual public ::user::document
{
public:


   property_set       m_set;


   simple_document(sp(::aura::application) papp);
   virtual ~simple_document();

};

