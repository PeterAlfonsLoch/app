//#include "framework.h"


namespace file
{


   plain_text_istream::plain_text_istream()
   {
   }

   plain_text_istream::plain_text_istream(stream_buffer * preader) :
      istream(preader)
   {

   }

   plain_text_istream::plain_text_istream(const istream & is) :
      istream(is)
   {

   }

   plain_text_istream::~plain_text_istream()
   {

   }

   void plain_text_istream::read (bool & b)
   {
      m_spbuffer->read(&b, sizeof(b));

   }

   void plain_text_istream::read (char & ch)
   {
      m_spbuffer->read(&ch, sizeof(ch));

   }

   void plain_text_istream::read (uchar & uch)
   {
      m_spbuffer->read(&uch, sizeof(uch));

   }

   void plain_text_istream::read (wchar_t & wch)
   {
      m_spbuffer->read(&wch, sizeof(wch));

   }

   void plain_text_istream::read (int16_t & sh)
   {
      m_spbuffer->read(&sh, sizeof(sh));

   }

   void plain_text_istream::read (uint16_t & ui)
   {
      m_spbuffer->read(&ui, sizeof(ui));

   }

   void plain_text_istream::read (int32_t & i)
   {
      uint64_t uiRead = m_spbuffer->read(&i, sizeof(i));
      if(uiRead != sizeof(i))
         throw "failed to read int32_t";

   }

   void plain_text_istream::read (uint32_t & ui)
   {
      uint64_t uiRead = m_spbuffer->read(&ui, sizeof(ui));
      if(uiRead != sizeof(ui))
         throw "failed to read uint32_t";

   }

   void plain_text_istream::read (int64_t & i)
   {
      m_spbuffer->read(&i, sizeof(i));

   }

   void plain_text_istream::read (uint64_t & ui)
   {
      m_spbuffer->read(&ui, sizeof(ui));

   }

   void plain_text_istream::read (float & f)
   {
      m_spbuffer->read(&f, sizeof(f));

   }

   void plain_text_istream::read (double & d)
   {
      m_spbuffer->read(&d, sizeof(d));

   }

   void plain_text_istream::read (LPRECT lprect)
   {
      m_spbuffer->read(&lprect->left,     sizeof(lprect->left));
      m_spbuffer->read(&lprect->top,      sizeof(lprect->top));
      m_spbuffer->read(&lprect->right,    sizeof(lprect->right));
      m_spbuffer->read(&lprect->bottom,   sizeof(lprect->bottom));

   }

   void plain_text_istream::read (SIZE & size)
   {
      m_spbuffer->read(&size.cx,     sizeof(size.cx));
      m_spbuffer->read(&size.cy,      sizeof(size.cy));

   }

   void plain_text_istream::read (sp(type) info)
   {
      {
         int32_t iLen;
         m_spbuffer->read(&iLen, sizeof(iLen));
         char * psz = (char *) malloc(iLen + 1);
         m_spbuffer->read(psz, iLen);
         psz[iLen] = '\0';
         info->m_id = psz;
         free((void *) psz);
      }
      {
         int32_t iLen;
         m_spbuffer->read(&iLen, sizeof(iLen));
         char * psz = (char *) malloc(iLen + 1);
         m_spbuffer->read(psz, iLen);
         psz[iLen] = '\0';
         info->m_idFriendly = psz;
         free((void *) psz);
      }

   }


   void plain_text_istream::read (serializable & serializable)
   {
      serializable.read(*this);

   }


   string plain_text_istream::get_location() const
   {
      return "<unknown plain_text_istream location>";
   }

   istream & plain_text_istream::operator = (const istream & istream)
   {

      return istream::operator = (istream);

   }








} // namespace core

