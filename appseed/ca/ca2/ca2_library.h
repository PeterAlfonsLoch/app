#pragma once


namespace user
{
   

   class view_creator_data;


} // namespace user


namespace ca2
{

   
   typedef class library * (* PFN_GET_NEW_LIBRARY)();


   class CLASS_DECL_ca library :
      virtual public ::ca::library,
      virtual public ::radix::object
   {
   public:



      library *         m_pca2library;
      string            m_strCa2Name;


      library();
      virtual ~library();

      virtual bool open(::ca::application * papp, const char * pszPath, bool bAutoClose = true);
      virtual bool close();


      virtual bool contains_app(const char * pszAppId);


      virtual void get_create_view_id_list(::raw_array < id > & ida);


      virtual void on_create_view(::user::view_creator_data * pcreatordata);


      // impl
      virtual ::ca::application * get_new_app(const char * pszId);
      virtual void get_app_list(stringa & stra);

   private:

      using ::ca::library::open;

   };

   
   template < class APP >
   class single_application_library :
      virtual public library
   {
   public:


      // impl
      virtual ::ca::application * get_new_app(const char * pszAppId)
      {

         if(!contains_app(pszAppId))
            return NULL;

         ::ca::application * papp = new APP();

         if(papp == NULL)
            return NULL;

         try
         {
            papp->construct(pszAppId);
         }
         catch(...)
         {
            try
            {
               delete papp;
            }
            catch(...)
            {
            }
            return NULL;
         }

         return papp;

      }


   };



} // namespace ca2


