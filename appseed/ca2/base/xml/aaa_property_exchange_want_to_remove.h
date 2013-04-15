#pragma once

namespace xml
{

   class CLASS_DECL_ca2 property_set_exchange :
      virtual public exportable,
      virtual public importable,
      virtual public ::radix::object
   {
   public:


      gen::property_set * m_ppropertyset;


      property_set_exchange(::ca::application * papp);
      virtual ~property_set_exchange();


      void xml_export(class output_tree &);
      void xml_import(class input_tree &);


   };


} // namespace xml
