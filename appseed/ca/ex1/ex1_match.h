#pragma once


namespace ex1
{

   namespace match
   {


      class CLASS_DECL_ca item
      {
      public:
         virtual bool matches(const var & var) const = 0;
      };


      class CLASS_DECL_ca _and :
         virtual public item
      {
      public:


         item *   m_pitem1;
         item *   m_pitem2;


         virtual bool matches(const var & var) const;

      };


      class CLASS_DECL_ca string :
         virtual public item
      {
      public:


         ::string      m_str;


         string(const char * psz = NULL);


         virtual bool matches(const var & var) const;


      };


      class CLASS_DECL_ca ci_string :
         virtual public string
      {
      public:


         ci_string(const char * psz = NULL);


         virtual bool matches(const var & var) const;


      };


      class CLASS_DECL_ca prefix :
         virtual public string
      {
      public:


         prefix(const char * psz = NULL);


         virtual bool matches(const var & var) const;


      };


      class CLASS_DECL_ca ci_prefix :
         virtual public string
      {
      public:


         ci_prefix(const char * psz = NULL);


         virtual bool matches(const var & var) const;


      };


      class CLASS_DECL_ca suffix :
         virtual public string
      {
      public:


         suffix(const char * psz = NULL);


         virtual bool matches(const var & var) const;


      };


      class CLASS_DECL_ca ci_suffix :
         virtual public string
      {
      public:


         ci_suffix(const char * psz = NULL);


         virtual bool matches(const var & var) const;

      };


      class CLASS_DECL_ca any :
         virtual public array_del_ptr < item >,
         virtual public item
      {
      public:


         virtual bool matches(const var & var) const;


      };


   } // namespace match


} // namespace ex1

