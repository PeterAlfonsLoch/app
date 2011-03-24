#pragma once

#define BACKGROUND_IMAGE_CHANGE_MIN_SECONDS 1
#define BACKGROUND_IMAGE_CHANGE_MAX_SECONDS 10000
#define BACKGROUND_IMAGE_CHANGE_DEFAULT_SECONDS 60

class OptionsSongsImagesDialog :
   public dialog
{
public:
   OptionsSongsImagesDialog(::ca::application * papp);

   //long   m_lChangeType;
   //int      m_iChangeTime;
   gen::property_set m_set;

   BOOL Update(BOOL bSaveAndValidate = TRUE);
   BOOL UpdateDatabase(BOOL bSaveAndValidate = TRUE);



   virtual BOOL DestroyWindow();
//   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

   virtual BOOL OnInitDialog();
};
