

inline property & object::oprop(const char * psz)
{

   return oprop_set()[psz];

}


inline property & object::oprop(const char * psz) const
{

   return const_cast < object * > (this)->oprop_set()[psz];

}


inline property_set & object::oprop_set()
{

   if(m_psetObject == NULL)
   {

      m_psetObject = new property_set(get_app());

   }

   return *m_psetObject;

}




inline ::aura::allocatorsp & object::allocer()
{

   return m_pauraapp->m_allocer;

}



inline sp(::command_thread) object::command_thread()
{

   return m_pauraapp->command_thread();

}





