#pragma once




class factory_item_base;



namespace ca
{


   class ca;
   class ptra;


} // namespace ca


namespace cube8
{


   class system;


} // namespace cube8


namespace bergedge
{


   class bergedge;


} // namespace bergedge


#define CaSys(pca) (*pca->m_papp->m_psystem)
#define Sys(papp) (*papp->m_psystem)
#define System (Sys(this->get_app()))
#define Mathematics(papp) (Sys(papp).math())
#define Math (Mathematics(this->get_app()))


#define Berg(papp) (*papp->m_pbergedge)
#define Bergedge (Berg(this->get_app()))


namespace gen
{

   template < class ca_derived >
   inline __int64 add_ref(ca_derived * pca)
   {
      if(pca == NULL)
         return -1;
      return pca->add_ref();
   }

   template < class ca_derived >
   inline __int64 release(ca_derived * & pca)
   {
      if(pca == NULL)
         return -1;
      __int64 count = pca->release();
      pca = NULL;
      return count;
   }

   template < class ca_derived >
   inline __int64 ref_count(ca_derived * pca)
   {
      if(pca == NULL)
         return -1;
      return pca->get_ref_count();
   }

} // namespace gen

class fixed_alloc_no_sync;

namespace ca
{


   class bergedge;
   class system;


   class CLASS_DECL__ ca
   {
   public:


      static const char g_szCarlosGustavoCecynLundgren[];
      static const char g_szCamiloSasukeTsumanuma[];
      static const char g_szCarlosgustavocecynlundgren[];
      static const char g_szCamilosasuketsumanuma[];
      static const char g_szKaarurosu[];
      static const char g_szKamiiro[];
      static const char g_szZack[];
      static const char g_szCa[];


      enum flag
      {
         flag_auto_clean = 1,
         flag_discard_to_factory = 2,
         flag_ready_for_delete = 4,
         flag_auto_delete = 8,
         flag_heap_alloc = 16,
         flag_locked = 32,
      };

      unsigned long           m_ulFlags;
      ::ca::application *     m_papp;
      ::bergedge::bergedge *  m_pbergedge;
      ::cube8::system *       m_psystem;
      __int64                 m_countReference;
      ::ca::ptra *            m_pptraListener;
      ::ca::ptra *            m_pptraListened;
      factory_item_base *     m_pfactoryitembase;
      void *                  m_pthis;


      ca();
      ca(const ca & o);
      ca(::ca::application * papp);
      virtual ~ca();

      virtual void delete_this();


      virtual ::ca::ca * clone();


      static void system(const char * pszProjectName);



      virtual ::ca::application * get_app() const;
      virtual void set_app(::ca::application * papp);

      inline bool is_set_ca_flag(::ca::ca::flag eflag)
      {
         return (m_ulFlags & ((unsigned long) eflag)) == (unsigned long) eflag;
      }

      inline void clear_ca_flag(::ca::ca::flag eflag)
      {
         m_ulFlags &= ~eflag;
      }

      inline void set_ca_flag(::ca::ca::flag eflag)
      {
         m_ulFlags |= eflag;
      }


      ca & operator = (const ca & o);

      virtual void on_delete(::ca::ca * pca);

      inline __int64 get_ref_count()
      {
         return m_countReference;
      }

      inline __int64 add_ref()
      {
         return m_countReference++;
      }

      inline __int64 release()
      {
         if(m_countReference > 0)
         {
            if(m_countReference == 1)
            {
               m_countReference = 0;
               delete_this();
               return 0;
            }
            else
            {
               m_countReference--;
               return m_countReference;
            }
         }
         else
         {
            return 0;
         }

      }


      ptra & listenerptra();
      ptra & listenedptra();

      virtual ptra * new_ptra() = 0;


   };

} // namespace ca



