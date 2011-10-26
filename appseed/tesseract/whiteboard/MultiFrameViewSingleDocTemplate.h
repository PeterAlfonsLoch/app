#pragma once


class CLASS_DECL_CA2_TESSERACT MultiFrameViewSingleDocTemplate :
   virtual public ::userbase::single_document_template  
{
public:
   
   
   MultiFrameViewSingleDocTemplate(::ca::application * papp, const char * pszMatter, ::ca::type_info & pDocClass, ::ca::type_info & pFrameClass, ::ca::type_info & pViewClass);
   virtual ~MultiFrameViewSingleDocTemplate();


   userbase::frame_window * CreateFrameViewPair(const char * pszMatter, ::ca::type_info & pclassFrame, ::ca::type_info & pclassView, BOOL bMakeVisible = TRUE);


};

