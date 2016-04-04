#pragma once


namespace draw2d_gl2d
{


   class CLASS_DECL_DRAW2D_GL2D font : 
      virtual public ::draw2d::font
   {
   public:

      
      //plusplus::Font *   m_pfont;


      font(::aura::application * papp);
      font(const font & font);
      virtual ~font();


      //virtual void * get_os_data() const;


      virtual void construct(const ::draw2d::font & fontParam);

      
      virtual void dump(dump_context & dumpcontext) const;





   };


} // namespace draw2d_gl2d



