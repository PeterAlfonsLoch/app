#pragma once


namespace ios
{


   class CLASS_DECL_AURA copydesk :
      virtual public ::core::copydesk,
      virtual public ::window_sp
   {
   public:


      copydesk(::aura::application * papp);
      virtual ~copydesk();


      virtual bool initialize();
      virtual bool finalize();

      virtual void set_filea(stringa & stra);

      virtual int32_t get_file_count();
      virtual void get_filea(stringa & stra);

      virtual void set_plain_text(const char * psz);
      virtual string get_plain_text();


      virtual bool desk_to_dib(::draw2d::graphics * pgraphics);
      // todo
      //bool dib_to_desk(::draw2d::graphics * pgraphics);

   };


} // namespace ios



