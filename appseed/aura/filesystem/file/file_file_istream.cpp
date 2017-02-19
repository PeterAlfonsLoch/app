//#include "framework.h"



namespace file
{


   file_istream::file_istream()
   {


   }

   
   file_istream::file_istream(const char * lpszFileName,uint32_t nOpenFlags,::aura::application * papp)
   {

      open(lpszFileName,nOpenFlags,papp);

   }


   file_istream::file_istream(file * preader)
   {

      m_spfile = preader;

   }

   file_istream::file_istream(const file_istream & istream)
   {

      m_spfile = istream.m_spfile;

   }

   file_istream::~file_istream()
   {

      close();



   }


} // namespace file









