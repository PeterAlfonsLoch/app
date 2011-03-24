#pragma once

namespace netnode
{

   class CLASS_DECL_CA2_CUBE simage_accepta
   {
   public:
      var m_root;
      gen::property_set m_propsetAccept;
      
      simage_accepta(var root);
   };

   typedef base_array < simage_accepta * > simage_accepta_ptr_array;




} // namespace netnode