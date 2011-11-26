#pragma once


namespace html
{


   class value : public base
   {
   public:


      int      m_iIndex;
      string            m_strValue;


      value(class tag * pparent);
      virtual ~value();


      virtual type get_type() const;

      void set_value(const char * pszValue);
      string get_value() const;

   };


} // namespace html


