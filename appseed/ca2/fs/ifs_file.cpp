#include "StdAfx.h"


ifs_file::ifs_file(::ca::application * papp) :
   ca(papp),
   ::sockets::http::batch_file(papp),
   m_httpfile(new ::sockets::http::file(papp)),
   m_memfile(papp)
{
}

ifs_file::~ifs_file()
{
}

::primitive::memory_size ifs_file::read(void *lpBuf, ::primitive::memory_size nCount)
{
   return m_httpfile->read(lpBuf, nCount);
}

void ifs_file::write(const void * lpBuf, ::primitive::memory_size nCount)
{
   m_memfile.write(lpBuf, nCount);
}


file_size ifs_file::get_length() const
{
   if((m_nOpenFlags & ::ex1::file::mode_read) != 0)
   {
      return m_httpfile->get_length();
   }
   else
   {
      return m_memfile.get_length();
   }
}

file_position ifs_file::seek(file_offset lOff, ::ex1::e_seek nFrom)
{
   if((m_nOpenFlags & ::ex1::file::mode_read) != 0)
   {
      return m_httpfile->seek(lOff, nFrom);
   }
   else
   {
      return m_memfile.seek(lOff, nFrom);
   }
}


void ifs_file::get_file_data()
{
   /*if(m_nOpenFlags & ::ex1::file::mode_write)
   {
      throw "Cannot open ifs_file for reading and writing simultaneously due the characteristic of possibility of extreme delayed streaming. The way it is implemented would also not work.\n It is build with this premisse.";
      return;
   }*/

   string strUrl;

   strUrl = "http://file.veriwell.net/get?path=" + System.url().url_encode(m_strPath);

   DWORD dwAdd = 0;

   if(m_nOpenFlags & hint_unknown_length_supported)
   {
      dwAdd |= hint_unknown_length_supported;
   }

   m_httpfile->open(strUrl, ::ex1::file::type_binary | ::ex1::file::mode_read | dwAdd);
}
 
void ifs_file::set_file_data()
{
   string strUrl;

   strUrl = "http://file.veriwell.net/set?path=" + System.url().url_encode(m_strPath);

   Application.http().put(strUrl, &m_memfile);
}
