#include "StdAfx.h"

namespace mus
{

microke1::microke1(::ca::application * papp)
{

}

microke1::~microke1()
{

}

bool microke1::IsMicroke1File(primitive::memory &storage)
{
   LPDWORD lpdw = (LPDWORD) storage.GetAllocation();
   return *lpdw == 0x30D60A87;

}

bool microke1::IsMicroke1File(const char * lpcsz)
{
   DWORD dw;
   ex1::filesp spfile(&System);
   if(!spfile->open(lpcsz, ::ex1::file::mode_read | ::ex1::file::type_binary))
      return false;
   spfile->read(&dw, 4);
   return dw == 0x30D60A87;

}

bool microke1::ExtractFile(const char * lpcszPath, primitive::memory & storage)
{
   ex1::filesp spfile(&System);
   if(spfile->open(lpcszPath, ::ex1::file::mode_read | ::ex1::file::type_binary))
      return false;
   int iLen = spfile->get_length();
   zip::memory_file memfile(get_app());
   memfile.allocate(iLen);
   spfile->read(memfile.GetAllocation(), iLen);
   
   unzFile pf = zip::api::unzipOpen(&memfile);

   if(pf != NULL)
   {
      if(unzOpenCurrentFilePassword(pf, "bqN,Sepc;MqD,PAmnC!") == UNZ_OK)
      {
         gen::memory_file target(get_app());
         target.FullLoad(&storage);
         BYTE buf[1024];
         int iRead;
         while((iRead = unzReadCurrentFile(pf, buf, sizeof(buf))) > 0)
         {
            target.write(buf, iRead);
         }  
         return true;
      }
      else
      {
         return false;
      }

   }
   else
   {
      return false;
   }
}

bool microke1::ExtractFile(primitive::memory & storageSrc, primitive::memory & storage)
{
   zip::memory_file memfile(get_app());
   memfile.FullLoad(&storageSrc);
   
   unzFile pf = zip::api::unzipOpen(&memfile);

   if(pf != NULL)
   {
      if(unzOpenCurrentFilePassword(pf, "bqN,Sepc;MqD,PAmnC!") == UNZ_OK)
      {
         gen::memory_file target(get_app());
         target.Attach(&storage);
         BYTE buf[1024];
         int iRead;
         while((iRead = unzReadCurrentFile(pf, buf, sizeof(buf))) > 0)
         {
            target.write(buf, iRead);
         }  
         target.Detach();
         return true;
      }
      else
      {
         return false;
      }

   }
   else
   {
      return false;
   }
}


} // namespace mus