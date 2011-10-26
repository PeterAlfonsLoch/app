#pragma once


namespace dynamic_source
{


   class CLASS_DECL_ca ptr : 
      virtual public script_composite
   {
   public:
      ptr();
      virtual ~ptr();
      bool m_bUnkeep;
   };


   template < class TYPE >
   class CLASS_DECL_ca ptr_array : 
      virtual public ptr,
      virtual public base_array < TYPE * >
   {
   public:
   };



} // namespace dynamic_source


