#include "framework.h"


namespace file
{


   plain_text_input_stream::plain_text_input_stream()
   {
   }

   plain_text_input_stream::plain_text_input_stream(reader * preader) :
      input_stream(preader)
   {

   }

   plain_text_input_stream::plain_text_input_stream(const input_stream & istream) :
      input_stream(istream)
   {

   }

   plain_text_input_stream::~plain_text_input_stream()
   {

   }

   void plain_text_input_stream::read (bool & b)
   {
      m_spreader->read(&b, sizeof(b));
      
   }

   void plain_text_input_stream::read (char & ch)
   {
      m_spreader->read(&ch, sizeof(ch));
      
   }

   void plain_text_input_stream::read (uchar & uch)
   {
      m_spreader->read(&uch, sizeof(uch));
      
   }

   void plain_text_input_stream::read (wchar_t & wch)
   {
      m_spreader->read(&wch, sizeof(wch));
      
   }

   void plain_text_input_stream::read (int16_t & sh)
   {
      m_spreader->read(&sh, sizeof(sh));
      
   }

   void plain_text_input_stream::read (uint16_t & ui)
   {
      m_spreader->read(&ui, sizeof(ui));
      
   }

   void plain_text_input_stream::read (int32_t & i)
   {
      uint64_t uiRead = m_spreader->read(&i, sizeof(i));
      if(uiRead != sizeof(i))
         throw "failed to read int32_t";
      
   }

   void plain_text_input_stream::read (uint32_t & ui)
   {
      uint64_t uiRead = m_spreader->read(&ui, sizeof(ui));
      if(uiRead != sizeof(ui))
         throw "failed to read uint32_t";
      
   }

   void plain_text_input_stream::read (int64_t & i)
   {
      m_spreader->read(&i, sizeof(i));
      
   }

   void plain_text_input_stream::read (uint64_t & ui)
   {
      m_spreader->read(&ui, sizeof(ui));
      
   }

   void plain_text_input_stream::read (float & f)
   {
      m_spreader->read(&f, sizeof(f));
      
   }

   void plain_text_input_stream::read (double & d)
   {
      m_spreader->read(&d, sizeof(d));
      
   }

   void plain_text_input_stream::read (LPRECT lprect)
   {
      m_spreader->read(&lprect->left,     sizeof(lprect->left));
      m_spreader->read(&lprect->top,      sizeof(lprect->top));
      m_spreader->read(&lprect->right,    sizeof(lprect->right));
      m_spreader->read(&lprect->bottom,   sizeof(lprect->bottom));
      
   }

   void plain_text_input_stream::read (SIZE & size)
   {
      m_spreader->read(&size.cx,     sizeof(size.cx));
      m_spreader->read(&size.cy,      sizeof(size.cy));
      
   }

   void plain_text_input_stream::read (sp(type) info)
   {
      {
         int32_t iLen;
         m_spreader->read(&iLen, sizeof(iLen));
         char * psz = (char *) malloc(iLen + 1);
         m_spreader->read(psz, iLen);
         psz[iLen] = '\0';
         info->m_id = psz;
         free((void *) psz);
      }
      {
         int32_t iLen;
         m_spreader->read(&iLen, sizeof(iLen));
         char * psz = (char *) malloc(iLen + 1);
         m_spreader->read(psz, iLen);
         psz[iLen] = '\0';
         info->m_idFriendly = psz;
         free((void *) psz);
      }
      
   }


   void plain_text_input_stream::read (serializable & serializable)
   {
      serializable.read(*this);
      
   }


   string plain_text_input_stream::get_location() const
   {
      return "<unknown plain_text_input_stream location>";
   }

   input_stream & plain_text_input_stream::operator = (const input_stream & istream)
   {
      
      return input_stream::operator = (istream);
      
   }








} // namespace ca2

