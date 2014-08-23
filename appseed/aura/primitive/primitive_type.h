#pragma once


class factory_item_base;


class CLASS_DECL_AURA type :
   virtual public element
{
public:


   sp(mutex)                           m_spmutex;
   id                                  m_id;
   id                                  m_idFriendly;
   sp(factory_item_base)               m_pfactoryitem;


   type();
   type(const type & info);
   type(const std_type_info & info);
   type(const string & strName, const string & strFriendlyName);
   type(const id & id, const class id & idFriendly);
   virtual ~type();


   type & operator = (const type & info);
   type & operator = (const std_type_info & info);


   bool operator == (const type & info) const;
   bool operator == (const std_type_info & info) const;
   bool operator == (const string & strName) const;
   bool operator == (const id & id) const;


   bool operator != (const type & info) const;
   bool operator != (const std_type_info & info) const;
   bool operator != (const string & strName) const;
   bool operator != (const id & id) const;

   virtual const char * name() const;
   virtual const char * friendly_name() const;

   virtual ptra * new_ptra();

   operator bool() const
   {
      return !m_id.is_empty();
   }


};


CLASS_DECL_AURA bool operator == (const std_type_info & info1, const sp(type) info2);
CLASS_DECL_AURA bool operator != (const std_type_info & info1, const sp(type) info2);


template<>
inline UINT HashKey(sp(type) key)
{
   // default identity hash - works for most primitive values
   return HashKey(key->name());
}


