#pragma once


namespace visual
{


   class CLASS_DECL_AXIS icon :
      virtual public ::object
   {
   public:


      void *   m_picon;
      bool  m_bAutoDelete;


      icon();
      icon(void * picon);
#ifdef WINDOWS
      icon(HICON hicon);
#endif
      virtual ~icon();


      operator void *();
#ifdef WINDOWS
      operator HICON();
#endif


   };


   class CLASS_DECL_AXIS icon_int_map :
      virtual public int_map < icon * >
   {
   public:

   };


} // namespace visual

