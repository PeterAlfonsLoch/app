#pragma once

#include "CDDeviceItem.h"

class CLASS_DECL_CA2_CUBE CCDBrowseDoc : public ::userbase::document
{
public:


   CCDDeviceItemArray      m_cddeviceitema;
   
   
   CCDBrowseDoc(::ca::application * papp); 
   virtual ~CCDBrowseDoc();


   virtual BOOL on_new_document();

   void CacheCDList();
   

#ifdef _DEBUG
   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;
#endif

};
