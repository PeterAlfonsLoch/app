#pragma once


namespace xml
{

   
   class var_exchange :
      public exportable,
      public importable,
      virtual public ::object
   {
   public:
   

      var * m_pvar;


      var_exchange(sp(::base::application) papp);
      virtual ~var_exchange();


      void xml_export(class output_tree &);
      void xml_import(class input_tree &);


   };

   
} // namespace xml




