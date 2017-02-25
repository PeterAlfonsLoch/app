#include "framework.h"


#include "aura/filestream.h"


#include "aura/primitive/str/str_base64.h"



namespace str
{


   void base64::encode(::file::ostream & ostream, ::file::istream & istream)
   {
      int32_t i, hiteof = FALSE;
      byte igroup[3], ogroup[4];
      int32_t n;
      char ch;

      while (!hiteof)
      {
         igroup[0] = igroup[1] = igroup[2] = 0;
         for (n = 0; n<3; n++)
         {
            if (istream.read(&ch, 1) == 0)
            {
               hiteof = TRUE;
               break;
            }
            igroup[n] = (uchar)ch;
         }
         if (n> 0)
         {
            ogroup[0] = etable[igroup[0] >> 2];
            ogroup[1] = etable[((igroup[0] & 3) << 4) | (igroup[1] >> 4)];
            ogroup[2] = etable[((igroup[1] & 0xF) << 2) | (igroup[2] >> 6)];
            ogroup[3] = etable[igroup[2] & 0x3F];
            if (n<3)
            {
               ogroup[3] = '=';
               if (n<2)
               {
                  ogroup[2] = '=';
               }
            }
            for (i = 0; i<4; i++)
            {
               ostream.write(&ogroup[i], 1);
            }
         }
      }
   }


   void base64::decode(::file::ostream & ostream, ::file::istream & istream)
   {
      int32_t i;
      byte a[4], b[4], o[3];
      uchar uch;

      while (TRUE)
      {
         for (i = 0; i<4; i++)
         {
            if (istream.read(&uch, 1) == 0)
            {
               if (i > 0)
               {
                  throw io_exception(get_app(), "Input file incomplete.\n");
                  //ASSERT(FALSE);
               }
               return;
            }
            if (dtable[uch] & 0x80)
            {
               string str;
               str.Format("Illegal character '%ca' in input spfile->\n", uch);
               throw io_exception(get_app(), str);
               i--;
               continue;
            }
            a[i] = (uchar)uch;
            b[i] = (uchar)dtable[uch];
         }
         o[0] = (b[0] << 2) | (b[1] >> 4);
         o[1] = (b[1] << 4) | (b[2] >> 2);
         o[2] = (b[2] << 6) | b[3];
         i = a[2] == '=' ? 1 : (a[3] == '=' ? 2 : 3);
         ostream.write(o, i);
         if (i<3)
            break;
      }
   }

   string base64::encode(const char * psz)
   {

      memory storage;

      strsize iLen = strlen(psz);

      storage.allocate(iLen);

      memcpy(storage.get_data(), psz, iLen);

      return encode(storage);

   }

   string base64::encode(byte * p, ::count ca)
   {

      memory storage;

      storage.allocate(ca);

      memcpy(storage.get_data(), p, ca);

      return encode(storage);

   }

   string base64::encode(primitive::memory_base & storageBinary)
   {

      string strRet;

      ::memory_file buf(get_app(), &storageBinary);

      ::file::byte_istream istream(&buf);

      ::file::string_file file(&strRet);

      ::file::plain_text_ostream ostream(&file);

      encode(ostream, istream);

      return strRet;

   }

   string base64::decode(const char * pszBase64)
   {

      memory storage;

      decode(storage, pszBase64);

      string str;

      memcpy(
         str.GetBufferSetLength(storage.get_size()),
         storage.get_data(),
         storage.get_size());

      str.ReleaseBuffer();

      return str;

   }

   void base64::decode(::primitive::memory_base & storageBinary, const char * pszBase64)
   {

      string str(pszBase64);

      ::file::string_file buf(str);

      ::file::plain_text_istream istream(&buf);

      ::memory_file bufOut(get_app(), &storageBinary);

      ::file::byte_ostream ostream(&bufOut);

      decode(ostream, istream);

   }

   string base64::serialize(::file::serializable & serializable)
   {

      memory storageBinary;

      ::memory_file buf(get_app(), &storageBinary);

      ::file::byte_stream stream(&buf);

      serializable.write(stream);

      buf.seek_to_begin();

      string strRet;

      ::file::string_file file(&strRet);

      ::file::plain_text_ostream ostream(&file);

      encode(ostream, stream);

      return strRet;

   }


   void base64::unserialize(::file::serializable & serializable, const char * pszBase64)
   {

      string str(pszBase64);

      ::file::string_file bufIn(str);

      ::file::plain_text_istream istream(&bufIn);

      memory storageBinary;

      ::memory_file buf(get_app(), &storageBinary);

      ::file::byte_stream stream(&buf);

      decode(stream, istream);

      buf.seek_to_begin();

      serializable.read(stream);

   }



} // namespace str



