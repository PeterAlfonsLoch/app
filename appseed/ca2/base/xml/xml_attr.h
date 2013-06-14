#pragma once

namespace xml
{
   
   class node;


   typedef ::ca2::property attr;


   class CLASS_DECL_ca2 attr_array :
      public ::ca2::property_set
   {
   protected:


      
      friend class node;


      sp(node)    m_pnodeParent;


   public:


      attr_array(sp(::ca2::application) papp);


   };




} // namespace xml