#pragma once


namespace base
{


   class CLASS_DECL_AXIS copydesk :
      virtual public ::object
   {
   public:


      copydesk(sp(::base::application) papp);
      virtual ~copydesk();


      virtual bool initialize();
      virtual bool finalize();

      virtual void set_filea(stringa & stra);

      virtual int32_t get_file_count();
      virtual void get_filea(stringa & stra);

      virtual void set_plain_text(const char * psz);
      virtual string get_plain_text();


      virtual bool desk_to_dib(::draw2d::dib * pdib);
      // todo
      //bool dib_to_desk(::draw2d::dib * pdib);

   };


   typedef smart_pointer < copydesk > copydesk_sp;


} // namespace base



