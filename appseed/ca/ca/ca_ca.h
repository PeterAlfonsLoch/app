#pragma once




class factory_item_base;


#define SCAST_PTR(TYPE, ptarget, psource) TYPE * ptarget = dynamic_cast < TYPE * > (psource);
#define SCAST_REF(TYPE, rtarget, psource) TYPE & rtarget = *(dynamic_cast < TYPE * > (psource));



namespace ca
{


   class ca;
   class ptra;


} // namespace ca


namespace plane
{


   class session;
   class system;
   class cube;


} // namespace plane


namespace bergedge
{


   class bergedge;


} // namespace bergedge


namespace cube
{


   class cube;


} // namespace cube


#define CaSys(pca) (*pca->m_papp->m_psystem)
#define Sys(papp) (*papp->m_psystem)
#define System (Sys(this->get_app()))
#define Mathematics(papp) (Sys(papp).math())
#define Math (Mathematics(this->get_app()))

#define Cub(papp) (*Sys(papp).m_pcube)
#define Cube (Cub(this->get_app()))

#define Sess(papp) (*papp->m_psession)
#define Session (Sess(this->get_app()))

#define Berg(papp) (*Sess(papp).m_pbergedge)
#define Bergedge (Berg(this->get_app()))

namespace gen
{

   template < class ca_derived >
   inline int64_t add_ref(ca_derived * pca)
   {
      if(pca == NULL)
         return -1;
      return pca->add_ref();
   }

   template < class ca_derived >
   inline int64_t release(ca_derived * & pca)
   {
      if(pca == NULL)
         return -1;
      int64_t count = pca->release();
      pca = NULL;
      return count;
   }

   template < class ca_derived >
   inline int64_t ref_count(ca_derived * pca)
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

   template < class TYPE >
   bool is_null(TYPE * p)
   {
      return (((int32_t) p) < sizeof(TYPE));
   }

   template <class t>
   inline void delptr(t *& p)
   {
      if(p != NULL)
      {
         delete p;
         p = NULL;
      }
   }


   class CLASS_DECL_ca ca
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
         //flag_heap_alloc = 16,
         flag_locked = 32,
      };

      uint32_t long           m_ulFlags;
      ::ca::application *     m_papp;
      int64_t                 m_countReference;
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
         return (m_ulFlags & ((uint32_t long) eflag)) == (uint32_t long) eflag;
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

      inline int64_t get_ref_count()
      {
         return m_countReference;
      }

      inline int64_t add_ref()
      {
         return m_countReference++;
      }

      inline int64_t release()
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

      virtual ptra * new_ptra();

      virtual ::bergedge::bergedge * get_bergedge();
      virtual ::cube::cube * get_cube();

   };


} // namespace ca



