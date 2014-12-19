#pragma once


namespace aura
{


   class CLASS_DECL_AURA printer :
      virtual public ::object
   {
   public:


      string      m_strName;


      printer(::aura::application * papp);
      virtual ~printer();

      virtual bool open(const char * pszDeviceName);
      virtual ::draw2d::graphics * create_graphics();
      virtual bool is_opened();
      virtual bool close();



   };


} // namespace aura























