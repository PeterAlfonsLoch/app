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
#define System (Sys(this->m_papp))
#define Mathematics(papp) (Sys(papp).math())
#define Math (Mathematics(this->m_papp))

#define Cub(papp) (*Sys(papp).m_pcube)
#define Cube (Cub(this->m_papp))

#define Sess(papp) (*papp->m_psession)
#define Session (Sess(this->m_papp))

#define Berg(papp) (*Sess(papp).m_pbergedge)
#define Bergedge (Berg(this->m_papp))


class fixed_alloc_no_sync;

namespace ca
{


   class bergedge;
   class system;

   
   class CLASS_DECL_ca ca :
      virtual public ::ca::c
   {
   public:


      enum flag
      {
         flag_auto_clean = 1 << 0,
         flag_discard_to_factory = 1 << 1,
         flag_ready_for_delete = 1 << 2,
         flag_auto_delete = 1 << 3,
         //flag_heap_alloc = 1 << 4,
         flag_locked = 1 << 5,
      };

      uint32_t                m_ulFlags;
      sp(::ca::application)     m_papp;
      //::ca::ptra *            m_pptraListener;
      //::ca::ptra *            m_pptraListened;
      factory_item_base *     m_pfactoryitembase;
      void *                  m_pthis;


      ca();
      ca(const ca & o);
      ca(sp(::ca::application) papp);
      virtual ~ca();

      virtual void delete_this();


      virtual sp(::ca::ca) clone();


      static void system(const char * pszProjectName);

      inline allocer allocer();

      virtual sp(::ca::application) get_app() const;
      virtual void set_app(sp(::ca::application) papp);

      inline bool is_set_ca_flag(::ca::ca::flag eflag)
      {
         return (m_ulFlags & ((uint32_t) eflag)) == (uint32_t) eflag;
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

      virtual void on_delete(sp(::ca::ca) pca);



      //ptra & listenerptra();
      //ptra & listenedptra();

      //virtual ptra * new_ptra();

      virtual ::bergedge::bergedge * get_bergedge();
      virtual ::cube::cube * get_cube();

   };


   class CLASS_DECL_ca allocator :
      virtual public ::ca::ca
   {
   public:

      
   };


   class CLASS_DECL_ca allocer :
      public sp(allocator)
   {
   public:


      allocer(sp(application) papp);


   };



} // namespace ca



