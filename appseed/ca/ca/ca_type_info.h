#pragma once


class factory_item_base;


namespace ca
{


   class CLASS_DECL_ca type_info :
      virtual public ca
   {
   public:


      ::ca::smart_pointer < mutex >       m_spmutex;
      id                                  m_id;
      ph(factory_item_base)               m_pfactoryitem;


      type_info();
      type_info(const type_info * pinfo);
      type_info(const type_info & info);
      type_info(const std_type_info * pinfo);
      type_info(const std_type_info & info);
      type_info(const char * pszRawName);
      type_info(const id & id);
      virtual ~type_info();


      type_info & operator = (const ::ca::type_info * pinfo);
      type_info & operator = (::ca::type_info info);
      type_info & operator = (const char * psz);
      type_info & operator = (const std_type_info & info);
      type_info & operator = (const id & id);


      bool operator == (const std_type_info & info) const;
      bool operator == (::ca::type_info info) const;
      bool operator == (const char * pszRawName) const;

      bool operator != (const std_type_info & info) const;
      bool operator != (::ca::type_info info) const;
      bool operator != (const char * pszRawName) const;

      virtual void name(const char * pszRawName);
      virtual const char * name() const;

      virtual ptra * new_ptra();

      operator bool() const
      {
         return !m_id.is_empty();
      }


   };


} // namespace ca


CLASS_DECL_ca bool operator == (const std_type_info & info1, ::ca::type_info info2);
CLASS_DECL_ca bool operator != (const std_type_info & info1, ::ca::type_info info2);


