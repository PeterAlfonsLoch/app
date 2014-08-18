#pragma once


namespace user
{


   class CLASS_DECL_AXIS printer :
      virtual public ::object
   {
   public:


      string      m_strName;


      printer(sp(::axis::application) papp);
      virtual ~printer();

      virtual bool open(const char * pszDeviceName);
      virtual ::draw2d::graphics * create_graphics();
      virtual bool is_opened();
      virtual bool close();



   };


} // namespace user


