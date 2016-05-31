#pragma once



namespace ace
{

   inline id system::id(const class var & var)
   {
      return ::id((const char *)(class var &) var);
   }

   inline id system::id(const property & prop)
   {
      return ::id((const string &)(property &)prop);
   }


   inline id system::id(const std_type_info & info)
   {
#ifdef WINDOWS
      return get_id_space()(info.name());
#else
      return get_id_space()(info.name());
#endif
   }

   inline id system::id(const char * psz)
   {
      return get_id_space()(psz);
   }

   inline id system::id(const string & str)
   {
      return get_id_space()(str);
   }

   inline id system::id(int64_t i)
   {
      return get_id_space()(i);
   }

   inline id_space & system::id()
   {
      return get_id_space();
   }


} //namespace ace



inline id::id(const char * psz)
{
   
   m_all ={};

   if(psz != NULL)
   {

      operator = (::ace::system::id(psz));

   }

}


#if defined(_LP64) || defined(_AMD64_)
inline id & id::operator = (int32_t i)
{
   m_etype     = type_integer;
   m_i         = i;
   return *this;
}
#endif

inline id & id::operator = (int_ptr i)
{
   m_etype     = type_integer;
   m_i         = i;
   return *this;
}




