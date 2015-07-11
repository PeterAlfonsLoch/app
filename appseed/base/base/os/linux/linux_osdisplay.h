#pragma once


#ifdef __cplusplus


class osdisplay_dataptra;
class osdisplay_data;
class mutex;


CLASS_DECL_AURA int32_t osdisplay_find(Display * pdisplay);
CLASS_DECL_AURA osdisplay_data * osdisplay_get(Display * pdisplay);
CLASS_DECL_AURA bool osdisplay_remove(Display * pdisplay);


class CLASS_DECL_AURA xdisplay
{
public:


   osdisplay_data *  m_pdata;
   bool              m_bLocked;
   bool              m_bOwn;


   xdisplay();
   xdisplay(Display * pdisplay, bool bInitialLock = true);
   ~ xdisplay();

   bool open(char * display_name, bool bInitialLock = true);

   void lock();
   void unlock();


   bool close();

   inline operator Display *();


   Window default_root_window();

   int default_screen();

};




class CLASS_DECL_AURA osdisplay_data
{
public:


   mutex *                 m_pmutex;
   Display *               m_pdisplay;
   Atom                    m_atomLongType;
   Atom                    m_atomLongStyle;
   Atom                    m_atomLongStyleEx;
   int64_t                 m_countReference;


   static osdisplay_dataptra * s_pdataptra;
   static mutex * s_pmutex;

   osdisplay_data();
   ~osdisplay_data();

   Display * display()
   {
      return this == NULL ? NULL : m_pdisplay;
   }

   Display * display() const
   {
      return this == NULL ? NULL : m_pdisplay;
   }

   Atom atom_long_type()
   {
      return this == NULL ? 0 : m_atomLongType;
   }

   Atom atom_long_style()
   {
      return this == NULL ? 0 : m_atomLongStyle;
   }

   Atom atom_long_style_ex()
   {
      return this == NULL ? 0 : m_atomLongStyleEx;
   }

   bool is_null() const
   {
      return this == NULL;
   }

   Atom get_window_long_atom(int32_t nIndex);


   inline int64_t get_ref_count()
   {

      return m_countReference;

   }


   inline int64_t add_ref()
   {

#ifdef WINDOWS

      return InterlockedIncrement64(&m_countReference);

#else

      return __sync_add_and_fetch(&m_countReference,1);

#endif

   }


   inline int64_t dec_ref()
   {

#ifdef WINDOWS

      return InterlockedDecrement64(&m_countReference);

#else

      return  __sync_sub_and_fetch(&m_countReference,1);

#endif

   }


   inline int64_t release()
   {

      int64_t i = dec_ref();

      if(i == 0)
      {

         osdisplay_remove(m_pdisplay);

      }

      return i;

   }

};




typedef osdisplay_data * osdisplay;


inline xdisplay::operator Display *()
{

   return m_pdata->m_pdisplay;

}


#endif




