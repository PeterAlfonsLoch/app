#pragma once

namespace metrowin
{
   
   class CLASS_DECL_AXIS printer :
      virtual public ::user::printer
   {
   public:


      class CLASS_DECL_AXIS document_properties :
         virtual public ::object
      {
      public:


         DEVMODE *      m_pdevmode;
         HDC            m_hdc;


         document_properties(::axis::application * papp);
         virtual ~document_properties();


         virtual bool initialize(::metrowin::printer * pprinter, DEVMODE * pdevmode = NULL);
         virtual bool close();
         virtual ::draw2d::graphics * create_graphics();

      };


      HANDLE                  m_hPrinter;
      document_properties     m_documentproperties;


      printer(::axis::application * papp);
      virtual ~printer();


      virtual bool open(const char * pszDeviceName);
      virtual ::draw2d::graphics * create_graphics();
      virtual bool is_opened();
      virtual bool close();



   };



} // namespace user


