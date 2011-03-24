#pragma once

class CLASS_DECL_CA2_CUBE MultiFrameViewSingleDocTemplate :
   virtual public ::userbase::single_document_template  
{
public:
   MultiFrameViewSingleDocTemplate(::ca::application * papp, const char * pszMatter, const type_info* pDocClass,
      const type_info* pFrameClass, const type_info* pViewClass);
   virtual ~MultiFrameViewSingleDocTemplate();

   userbase::frame_window * CreateFrameViewPair(const char * pszMatter, const type_info * pclassFrame, const type_info * pclassView, BOOL bMakeVisible = TRUE);

};

