#pragma once


namespace visual
{


   class CLASS_DECL_ca icon :
      virtual public ::ca::object
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


   class CLASS_DECL_ca icon_int_map :
      virtual public ::collection::int_map < icon * >
   {
   public:

   };


} // namespace visual

