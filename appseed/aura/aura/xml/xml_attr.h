#pragma once


namespace xml
{

   
   class node;


   typedef property attr;


   class CLASS_DECL_AURA attr_array :
      public property_set
   {
   protected:


      
      friend class node;


      sp(node)    m_pnodeParent;


   public:


      attr_array(sp(::aura::application) papp);


   };




} // namespace xml

