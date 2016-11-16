#pragma once


namespace draw2d_cairo
{


   class CLASS_DECL_DRAW2D_CAIRO brush :
      virtual public ::draw2d::brush
   {
   public:



      brush(::aura::application * papp);
      virtual ~brush();


      virtual void * get_os_data() const;


      virtual void dump(dump_context & dumpcontext) const;


   };


} // namespace draw2d_cairo

