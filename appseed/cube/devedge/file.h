#pragma once

namespace devedge
{

   class folder;

   class CLASS_DECL_CA2_CUBE file :
      virtual public ex1::tree_item,
      virtual public ::radix::object
   {
   public:
      file(::ca::application * papp);
      
      // initialize
      folder *    m_pfolder;
      string      m_strPath;
      string      m_strName;

      // load
      document *  m_pdocument;

      void initialize(folder * pfolder, const char * pszPath);

      void open(::user::interaction * puieParent);

      void close();

#undef new
         DECLARE_AND_IMPLEMENT_DEFAULT_ALLOCATION
#define new DEBUG_NEW

   };

} // namespace devedge