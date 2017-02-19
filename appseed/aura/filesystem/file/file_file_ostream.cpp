//#include "framework.h"



namespace file
{


   file_ostream::file_ostream()
   {

   }


   file_ostream::file_ostream(const char * lpszFileName,uint32_t nOpenFlags,::aura::application * papp)
   {

      open(lpszFileName,nOpenFlags,papp);

   }


   file_ostream::file_ostream(file * preader)
   {

      m_spfile = preader;

   }

   file_ostream::file_ostream(const file_ostream & istream)
   {

      m_spfile = istream.m_spfile;

   }

   file_ostream::~file_ostream()
   {


   }


} // namespace file









