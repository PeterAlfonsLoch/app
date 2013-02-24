#pragma once


inline var::var()
{
   m_etype = type_new;
   m_pca2 = NULL;
}


inline var::var(const ::ca::null & null)
{
   m_etype = type_null;
   m_pca2 = NULL;
}


inline var::var(e_type etype)
{
   m_etype = etype;
   m_pca2 = NULL;
}


inline count var::get_count() const
{
   switch(m_etype)
   {
   case type_bool:
      return 1;
   case type_inta:
      return m_pia->get_count();
   case type_stra:
      return m_pstra->get_count();
   case type_vara:
      return m_pvara->get_count();
   case type_propset:
      return m_pset->get_count();
   default:
      return 1;
   }
}


inline count var::array_get_count() const
{
   if(m_etype == type_new
   || m_etype == type_null
   || m_etype == type_empty
   || m_etype == type_empty_argument)
   {
      return -1; // indicates that this var is not an base_array
   }
   else if(is_array())
      return this->get_count();
   else
      return 1; // this var is an scalar or object that can be retrieved through "array_" methods
}



inline index var::array_get_upper_bound() const
{
   if(m_etype == type_new
   || m_etype == type_null
   || m_etype == type_empty
   || m_etype == type_empty_argument)
   {
      return -1; // indicates that this var is not an base_array
   }
   else if(is_array())
      return this->get_count() - 1;
   else
      return 0; // this var is an scalar or object that can be retrieved through "array_" methods
}


inline bool var::is_array() const
{
   if(m_etype == type_new
   || m_etype == type_null
   || m_etype == type_empty)
   {
      return false;
   }
   else if(m_etype == type_string
   || m_etype == type_int32
   || m_etype == type_pint32
   || m_etype == type_uint32
   || m_etype == type_bool
   || m_etype == type_double)
   {
      return false;
   }
   else if(m_etype == type_stra
      || m_etype == type_inta
      || m_etype == type_vara
      || m_etype == type_propset)
   {
      return true;
   }
   else if(m_etype == type_prop)
   {
      return prop().get_value().is_array();
   }
   else if(m_etype == type_ca2)
   {
      return false;
   }
   else
   {
      return false;
   }
}



inline bool CLASS_DECL_ca operator == (const string & str, const var & var)
{
   return str == var.get_string();
}



inline id & id::operator = (const var & var)
{

   if(var.is_null())
   {
      m_chType = IDTYPE_TYPE_NULL;
      return *this;
   }
   if(var.is_integer())
   {
      return operator = (var.intptr());
   }
   else
   {
      return operator = (var.get_string());
   }
   
}

inline id & id::operator = (const ca::property & prop)
{

   return operator = (prop.m_var);

}



inline id::id(const var & var)
{

   m_i = 0;
   m_chType = IDTYPE_TYPE_NULL;

   *this = var.get_id();

}
