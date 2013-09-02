#pragma once


namespace ca2
{


   class CLASS_DECL_ca2 simple_tree_item_data :
      public tree_item_data
   {
   public:


      index                      m_iImage;
      index                      m_iImageSelected;
      string                     m_str;


      simple_tree_item_data();
      virtual ~simple_tree_item_data();

      virtual string get_text(sp(::ca2::tree) ptree);
      virtual index get_image(sp(::ca2::tree) ptree);

      /*#undef new
      void * operator new(size_t i, const char * lpszFileName, int32_t iLine);
      void * operator new(size_t i);
      #define new DEBUG_NEW
      void operator delete(void *);
      void operator delete(void *, const char * lpszFileName, int32_t iLine);*/


   };


} // namespace ca2


