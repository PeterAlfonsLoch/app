#pragma once


namespace windows
{


   class CLASS_DECL_AXIS copydesk : 
      virtual public ::user::copydesk
   {
   public:


      HWND m_hwnd;
      
      copydesk(::aura::application * papp);
      virtual ~copydesk();

      
      virtual bool initialize();
      virtual bool finalize();

      virtual void set_filea(stringa & stra);

      virtual int32_t get_file_count();
      virtual void get_filea(::file::patha & stra);

      virtual void set_plain_text(const char * psz);
      virtual string get_plain_text();

      virtual bool desk_to_dib(::draw2d::dib * pdib);
      virtual bool dib_to_desk(::draw2d::dib * pdib);

   };


} // namespace windows



