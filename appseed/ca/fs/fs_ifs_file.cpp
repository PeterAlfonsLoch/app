#include "framework.h"


ifs_file::ifs_file(::ca::application * papp, var varFile) :
   ca(papp),
   ::sockets::http::batch_file(papp),
   m_httpfile(new ::sockets::http::file(papp)),
   m_memfile(papp),
   m_varFile(varFile)
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
   if((m_nOpenFlags & ::ca::file::mode_read) != 0)
   {
      return m_httpfile->get_length();
   }
   else
   {
      return m_memfile.get_length();
   }
}

file_position ifs_file::seek(file_offset lOff, ::ca::e_seek nFrom)
{
   if((m_nOpenFlags & ::ca::file::mode_read) != 0)
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
   /*if(m_nOpenFlags & ::ca::file::mode_write)
   {
      throw "Cannot open ifs_file for reading and writing simultaneously due the characteristic of possibility of extreme delayed streaming. The way it is implemented would also not work.\n It is build with this premisse.";
      return;
   }*/

   string strUrl;

   strUrl = "http://file.veriwell.net/ifs/get?path=" + System.url().url_encode(m_strPath);

   uint32_t dwAdd = 0;

   if(m_nOpenFlags & hint_unknown_length_supported)
   {
      dwAdd |= hint_unknown_length_supported;
   }

   m_httpfile->open(strUrl, ::ca::file::type_binary | ::ca::file::mode_read | dwAdd);
}
 
void ifs_file::set_file_data()
{
   string strUrl;


   if(m_varFile["xmledit"].ca < ::primitive::memory_file > () != ::null())
   {

      strUrl = "http://file.veriwell.net/ifs/xmledit?path=" + System.url().url_encode(m_varFile["url"]);

      string strResponse;

      Application.http().put(strResponse, strUrl, m_varFile["xmledit"].ca < ::primitive::memory_file >());

      ::ca::property_set set(get_app());

      set.parse_url_query(strResponse);

      string strMd5Here = System.crypt().md5(*m_varFile["xml"].ca < ::primitive::memory_file >()->get_primitive_memory());
      string strMd5There = set["md5"];

      if(strMd5Here == strMd5There)
         return;

      strUrl = "http://file.veriwell.net/ifs/set?path=" + System.url().url_encode(m_varFile["url"]);

      Application.http().put(strUrl, m_varFile["xml"].ca < ::primitive::memory_file >());

      return;
   }


   strUrl = "http://file.veriwell.net/ifs/set?path=" + System.url().url_encode(m_strPath);

   Application.http().put(strUrl, &m_memfile);


}
