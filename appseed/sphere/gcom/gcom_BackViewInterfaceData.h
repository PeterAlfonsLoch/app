#pragma once

namespace gcom
{

   namespace backview
   {

      class CLASS_DECL_ca2 InterfaceData  
      {
      public:
         flags < EInterfaceData >   m_einterfacedataflags;
         HENHMETAFILE               m_henhmetafile;
         EImagePlacement            m_eimageplacemnt;
         string                    m_wstrNextImagePath;
         string                    m_wstrCurrentImagePath;
         rect                      m_rect;
      public:
         void signalize(EInterfaceData edata);
         bool is_signalized(EInterfaceData edata);

      public:
         InterfaceData();
         virtual ~InterfaceData();

      };
   } // namespace backview

} // namespace gcom

