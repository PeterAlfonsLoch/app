

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




namespace comparison
{


   template < >
   class equals_type_arg_type < string,const string & >
   {
   public:

      inline static bool CompareElements(const string * pElement1,const string & element2)
      {
         return *pElement1 == element2;
      }

   };

   template < >
   class less < string,const string & >
   {
   public:

      inline bool operator()(const string & element1,const string & element2) const
      {
         return element1 < element2;
      }

   };

   class compare_string_case:
      public compare_type_arg_type < string,const string & >
   {
   public:


      inline static int_ptr CompareElements(const string * pElement1,const string  & element2)
      {

         return pElement1->Compare(element2);

      }


   };


   class compare_string_no_case:
      public compare_type_arg_type < string,const string & >
   {
   public:

      inline static int_ptr CompareElements(const string * pElement1,const string & element2)
      {
         return pElement1->CompareNoCase(element2);
      }

   };

   template < >
   class CLASS_DECL_AURA hash < const string & >
   {
   public:

      inline static UINT HashKey(const string & key)
      {
         uint64_t * puiKey = (uint64_t *)(const char *)key;
         strsize counter = key.get_length();
         uint64_t nHash = 0;
         while(::compare::ge(counter,sizeof(*puiKey)))
         {
            nHash = (nHash << 5) + nHash + *puiKey++;
            counter -= sizeof(*puiKey);
         }
         const char * pszKey = (const char *)puiKey;
         while(counter-- >= 0) nHash = (nHash << 5) + nHash + *pszKey++;
         return (UINT)(nHash & 0xffffffff);
      }

   };

   template < >
   class compare_type_arg_type < id,const id & >
   {
   public:


      inline static int_ptr CompareElements(const id * pElement1,const id & element2)
      {

         int_ptr iCompare = (int_ptr)(pElement1->m_iType - element2.m_iType);
         if(iCompare != 0)
            return iCompare;
         return pElement1->m_psz - element2.m_psz;

      }


   };


   class strid_compare
   {
   public:


      inline static int_ptr CompareElements(const id * pElement1,const id  * pelement2)
      {

         return pElement1->m_psz - pelement2->m_psz;

      }


   };


   class CLASS_DECL_AURA strid_binary
   {
   public:


      inline static int_ptr CompareElements(const id * pElement1,const id * pElement2)
      {

         return pElement1->m_psz - pElement2->m_psz;

      }


   };


} // namespace comparison





