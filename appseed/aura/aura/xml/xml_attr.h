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


      node *      m_pnodeParent;


   public:


      attr_array(::aura::application * papp);


   };




} // namespace xml

