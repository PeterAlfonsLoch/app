#pragma once


namespace core
{


   namespace international
   {


      class locale_schema;


   } // namespace international


} // namespace core



namespace user
{


   class str_context;


   class CLASS_DECL_AXIS str_schema :
      public strid_map < string >
   {
   public:


      id m_idSchema;


      str_schema() { InitHashTable(4 * 1024); };


   };

   class CLASS_DECL_AXIS str_locale :
      public strid_map < str_schema >
   {
   public:


      id       m_idLang;

      inline str_schema * get_schema(const ::id & idSchema)
      {
         strid_map < str_schema > ::pair * ppair = PLookup(idSchema);
         if (ppair == NULL)
            return NULL;
         return &ppair->second;
      }


      str_locale() { InitHashTable(256); };


   };


   class CLASS_DECL_AXIS str :
      public strid_map < str_locale >
   {
   public:


      sp(str_schema)                      m_pschemaEn;
      sp(str_schema)                      m_pschemaStd;



      str(sp(::axis::application) papp);


      inline str_locale * get_locale(const ::id & idLocale)
      {
         strid_map < str_locale > ::pair * ppair = PLookup(idLocale);
         if (ppair == NULL)
            return NULL;
         return &ppair->second;
      }


      bool initialize();


      void set(const ::id & id, const ::id & idLocale, const ::id & idSchema, const char * psz);
      string get(str_context * pcontext, const ::id & id);
      string get(str_context * pcontext, const ::id & id, const ::id & idLocale, const ::id & idSchema);
      void get(stringa & stra, str_context * pcontext, const ::id & id);
      void _get(stringa & stra, str_context * pcontext, const ::id & id);

      bool load(const char * pszBaseDir);
      bool load_uistr_file(const ::id & idLocale, const ::id & idSchema, const char * pszFile);

      string body(const char * psz);

      bool matches(str_context * pcontext, const ::id & id, const char * psz);
      bool begins(str_context * pcontext, const char * psz, const ::id & id);
      bool begins_eat(str_context * pcontext, string & str, const ::id & id);


   };



   class CLASS_DECL_AXIS str_context :
      virtual public ::object
   {
   public:



      sp(::str::international::locale_schema)    m_plocaleschema;


      sp(str)                                   m_pstr;

      str_locale *                              m_plocale;

      str_schema *                              m_pschema;
      str_schema *                              m_pschemaLocale;
      str_schema *                              m_pschemaSchemaEn;
      str_schema *                              m_pschemaSchemaStd;



      comparable_array < str_schema * >         m_schemaptra;



      str_context(sp(::axis::application) papp);
      virtual ~str_context();


      inline void defer_ok(str * pstr)
      {
         if (pstr != m_pstr)
         {
            m_pstr = pstr;
            prepare();
         }
      }

      void prepare();

      inline ::str::international::locale_schema & localeschema()
      {
         return *m_plocaleschema;
      }


      inline bool matches(const ::id & id, const char * psz)
      {

         return m_pstr->matches(this, id, psz);

      }


      inline bool begins(const ::id & id, const char * psz)
      {

         return m_pstr->begins(this, id, psz);

      }


      inline bool begins_eat(string & str, const ::id & id)
      {

         return m_pstr->begins_eat(this, str, id);

      }


      inline void get(stringa & stra, const ::id & id)
      {

         return m_pstr->get(stra, this, id);


      }


      inline string get(const ::id & id)
      {
         if (m_pstr == NULL)
            return id;
         return m_pstr->get(this, id);

      }


   };




} // namespace user




