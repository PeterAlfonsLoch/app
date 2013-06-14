#pragma once


namespace user
{


   class CLASS_DECL_ca2 printer :
      virtual public ::ca2::object
   {
   public:

      string      m_strName;


      printer(sp(::ca2::application) papp);
      virtual ~printer();

      virtual bool open(const char * pszDeviceName);
      virtual ::ca2::graphics * create_graphics();
      virtual bool is_opened();
      virtual bool close();



   };


} // namespace user


