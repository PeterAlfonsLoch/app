#pragma once


namespace visual
{


   class CLASS_DECL_ca icon :
      virtual public ::radix::object
   {
   public:
      icon();
      virtual ~icon();
#ifdef WIN32
      icon(HICON hicon) { m_hicon = hicon; }
      HICON m_hicon;
      bool  m_bAutoDelete;
      operator HICON();
#endif

   };


   class CLASS_DECL_ca icon_int_map :
      virtual public ::collection::int_map < icon * >
   {
   public:

   };
   

} // namespace visual

