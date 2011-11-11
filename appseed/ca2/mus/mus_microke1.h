#pragma once

namespace mus
{

   class CLASS_DECL_ca microke1  :
      virtual public ::radix::object
   {
   public:


      microke1(::ca::application * papp);
      virtual ~microke1();


      bool ExtractFile(const char * lpcszPath, primitive::memory & storage);
      bool ExtractFile(primitive::memory & storageSrc, primitive::memory & storage);
      bool IsMicroke1File(const char * lpcsz);
      bool IsMicroke1File(primitive::memory & storage);

   };

} // namespace microke1