//#include "framework.h"
//#include "axis/net/net_sockets.h"


ifs_file::ifs_file(::aura::application * papp, var varFile) :
   ::object(papp),
   ::sockets::http_batch_buffer(papp),
   m_httpfile(canew(::sockets::http_buffer(papp))),
   m_memfile(papp),
   m_varFile(varFile)
{

}


ifs_file::~ifs_file()
{

}


memory_size_t ifs_file::read(void *lpBuf, memory_size_t nCount)
{

   return m_httpfile->read(lpBuf, nCount);

}


void ifs_file::write(const void * lpBuf, memory_size_t nCount)
{

   m_memfile.write(lpBuf, nCount);

}


file_size_t ifs_file::get_length() const
{
   if((m_nOpenFlags & ::file::mode_read) != 0)
   {
      return m_httpfile->get_length();
   }
   else
   {
      return m_memfile.get_length();
   }
}

file_position_t ifs_file::seek(file_offset_t lOff, ::file::e_seek nFrom)
{
   if((m_nOpenFlags & ::file::mode_read) != 0)
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
   /*if(m_nOpenFlags & ::file::mode_write)
   {
      throw "Cannot open ifs_file for reading and writing simultaneously due the characteristic of possibility of extreme delayed streaming. The way it is implemented would also not work.\n It is build with this premisse.";
      return;
   }*/

   string strUrl;

   strUrl = "http://file.ca2.cc/ifs/get?path=" + System.url().url_encode(m_strPath);

   uint32_t dwAdd = 0;

   if(m_nOpenFlags & ::file::hint_unknown_length_supported)
   {
      dwAdd |= ::file::hint_unknown_length_supported;
   }

   m_httpfile->open(strUrl, ::file::type_binary | ::file::mode_read | dwAdd);
}

void ifs_file::set_file_data()
{
   string strUrl;


   if(m_varFile["xmledit"].cast < ::file::memory_buffer > () != NULL)
   {

      strUrl = "http://file.ca2.cc/ifs/xmledit?path=" + System.url().url_encode(m_varFile["url"]);

      property_set setRequest;

      setRequest["get_response"] = "";  // touch/create property to get_response

      Application.http().put(strUrl, m_varFile["xmledit"].cast < ::file::memory_buffer >(), setRequest);

      string strResponse(setRequest["get_response"]);

      property_set set(get_app());

      set.parse_url_query(strResponse);

      string strMd5Here;

      {

         MD5_CTX ctx;

         MD5_Init(&ctx);

         MD5_Update(&ctx, m_varFile["xml"].cast < ::file::memory_buffer >()->get_primitive_memory()->get_data(),m_varFile["xml"].cast < ::file::memory_buffer >()->get_primitive_memory()->get_size());

         to_string(strMd5Here, ctx);

      }

      string strMd5There = set["md5"];

      if(strMd5Here == strMd5There)
         return;

      strUrl = "http://file.ca2.cc/ifs/set?path=" + System.url().url_encode(m_varFile["url"]);

      property_set setPut(get_app());

      Application.http().put(strUrl, m_varFile["xml"].cast < ::file::memory_buffer >(), setPut);

      return;

   }

   strUrl = "http://file.ca2.cc/ifs/set?path=" + System.url().url_encode(m_strPath);

   property_set setPut(get_app());

   Application.http().put(strUrl, &m_memfile, setPut);


}
