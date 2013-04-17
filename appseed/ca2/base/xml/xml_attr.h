#pragma once

namespace xml
{
   
   class node;


   typedef ::ca::property attr;


   class CLASS_DECL_ca2 attr_array :
      public ::ca::property_set
   {
   protected:


      
      friend class node;


      sp(node)    m_pnodeParent;


   public:


      attr_array(sp(::ca::application) papp);


   };




} // namespace xml