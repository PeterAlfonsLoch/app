#pragma once


namespace html
{


   class attribute :
      virtual public element
   {
   public:


      id          m_idName;
      string      m_strValue;


      void set_name(id idName);
      id get_name() const;

      void set_value(const char * pszValue);
      string get_value() const;


   };


   class attribute_array : public spa(attribute)
   {
   public:


      attribute * get(id idName);
      const attribute * get(id idName) const;
      string get_value(id idName) const;


   };



} // namespace html


