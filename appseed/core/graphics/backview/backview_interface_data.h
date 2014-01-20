#pragma once


namespace backview
{


   class CLASS_DECL_CORE InterfaceData
   {
   public:


      flags < EInterfaceData >      m_einterfacedataflags;
      HENHMETAFILE                  m_henhmetafile;
      EImagePlacement               m_eimageplacement;
      string                        m_strNextImagePath;
      string                        m_strCurrentImagePath;
      rect                          m_rect;


      InterfaceData();
      virtual ~InterfaceData();


      void signalize(EInterfaceData edata);
      bool is_signalized(EInterfaceData edata);

   };


} // namespace backview
