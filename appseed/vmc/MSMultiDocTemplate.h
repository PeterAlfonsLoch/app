#pragma once

class CMSMultiDocTemplate : public BaseMultipleDocumentTemplate  
{
public:
   CMSMultiDocTemplate(::ca::application * papp, UINT nIDResource, const type_info * pDocClass,
   const type_info * pFrameClass, const type_info * pViewClass);
};

