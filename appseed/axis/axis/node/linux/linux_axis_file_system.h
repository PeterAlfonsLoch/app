#pragma once


namespace linux
{


   namespace axis
   {


      class CLASS_DECL_AXIS file_system :
         virtual public ::linux::file_system,
         virtual public ::file::axis::system
      {
      public:


         file_system(::aura::application *  papp);


      };


   } // namespace axis


} // namespace ca2










































