#pragma once


namespace ca
{

   class ca;

} // namespace ca

namespace icube
{

   class system;

}

#define System (*m_papp->m_psystem)



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
         flag_heap_alloc = 16
      };

      unsigned long           m_ulFlags;
      ::ca::application *     m_papp;
      __int64                 m_countReference;

      ca();
      ca(const ca & o);
      ca(::ca::application * papp);
      virtual ~ca();

      virtual void delete_this();


      virtual ::ca::ca * clone();


      static void system(const char * pszProjectName);


      virtual ::ca::application * get_app() const;
      virtual void set_app(::ca::application * papp);

      inline bool is_set(::ca::ca::flag eflag)
      {
         return (m_ulFlags & ((unsigned long) eflag)) == (unsigned long) eflag;
      }

      inline void clear(::ca::ca::flag eflag)
      {
         m_ulFlags &= ~eflag;
      }

      inline void set(::ca::ca::flag eflag)
      {
         m_ulFlags |= eflag;
      }

      
      ca & operator = (const ca & o);

      template < class ca_derived > friend inline __int64 gen::add_ref(ca_derived * pca);
      template < class ca_derived > friend inline __int64 gen::release(ca_derived * & pca);
      template < class ca_derived > friend inline __int64 gen::ref_count(ca_derived * pca);

      virtual void on_delete(::ca::ca * pca);


   protected:

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


   };

} // namespace ca



