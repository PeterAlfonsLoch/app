#pragma once


namespace ace
{


   class CLASS_DECL_ACE printer :
      virtual public ::object
   {
   public:


      string      m_strName;


      printer(::ace::application * papp);
      virtual ~printer();

      virtual bool open(const char * pszDeviceName);
      virtual ::draw2d::graphics * create_graphics();
      virtual bool is_opened();
      virtual bool close();



   };


} // namespace ace























