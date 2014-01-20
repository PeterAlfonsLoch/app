#pragma once


namespace core
{
   

   namespace match
   {


      class CLASS_DECL_CORE item :
         virtual public element
      {
      public:
         item() {}
         virtual ~item() {}
         virtual bool matches(const var & var) const = 0;
      };


      class CLASS_DECL_CORE _and :
         virtual public item
      {
      public:


         item *   m_pitem1;
         item *   m_pitem2;


         virtual bool matches(const var & var) const;

      };


      class CLASS_DECL_CORE string :
         virtual public item
      {
      public:


         ::string      m_str;


         string(const char * psz = NULL);


         virtual bool matches(const var & var) const;


      };


      class CLASS_DECL_CORE ci_string :
         virtual public string
      {
      public:


         ci_string(const char * psz = NULL);


         virtual bool matches(const var & var) const;


      };


      class CLASS_DECL_CORE prefix :
         virtual public string
      {
      public:


         prefix(const char * psz = NULL);


         virtual bool matches(const var & var) const;


      };


      class CLASS_DECL_CORE ci_prefix :
         virtual public string
      {
      public:


         ci_prefix(const char * psz = NULL);


         virtual bool matches(const var & var) const;


      };


      class CLASS_DECL_CORE suffix :
         virtual public string
      {
      public:


         suffix(const char * psz = NULL);


         virtual bool matches(const var & var) const;


      };


      class CLASS_DECL_CORE ci_suffix :
         virtual public string
      {
      public:


         ci_suffix(const char * psz = NULL);


         virtual bool matches(const var & var) const;

      };


      class CLASS_DECL_CORE any :
         virtual public spa(item),
         virtual public item
      {
      public:


         virtual bool matches(const var & var) const;


      };


   } // namespace match


} // namespace core

