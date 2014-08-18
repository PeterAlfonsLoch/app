#pragma once


namespace axis
{


   class CLASS_DECL_AXIS session:
      virtual public ::axis::application,
      virtual public ::axis::session_interface
   {
   public:

      



      ::core::platform *                                       m_pcoreplatform;
      string_map < sp(::axis::application) >                   m_mapApplication;

      bool                                                     m_bDrawCursor;


      application_ptra                                         m_appptra;








      session(sp(::axis::application) papp);
      virtual ~session();


      application_ptra & appptra();

      virtual bool is_session();


      void construct(sp(::axis::application) papp, int iPhase);

      virtual bool process_initialize();

      virtual bool initialize1();

      virtual bool initialize2();

      virtual bool initialize_instance();

      virtual bool initialize();

      virtual bool finalize();

      virtual int32_t exit_instance();




      
      virtual COLORREF get_default_color(uint64_t ui);


      

      




      virtual void  get_cursor_pos(LPPOINT lppoint);

      







   };


} // namespace axis








inline ::axis::session & sess(::axis::application * papp);




























