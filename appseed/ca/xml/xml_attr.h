#pragma once

namespace xml
{
   
   class node;


   typedef ::gen::property attr;


   class CLASS_DECL_ca attr_array :
      public gen::property_set
   {
   protected:


      
      friend class node;


      node *   m_pnodeParent;


   public:


      attr_array(::ca::application * papp);


   };




} // namespace xml