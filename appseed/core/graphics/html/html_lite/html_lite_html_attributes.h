//
//HISTORY:
//
//Version 1.0            Gurmeet S. Kochar (GSK)
//Mar 18, 2004         First release version.


#pragma once

class LiteHTMLAttributes;   // forward declaration

/**
 * LiteHTMLElemAttr
 *
 * @version 1.0 (Mar 18, 2004)
 * @author Gurmeet S. Kochar
 */
class CLASS_DECL_CORE LiteHTMLElemAttr
{
public:


   string           m_strName;
   string           m_strValue;


   LiteHTMLElemAttr(const char * lpszAttribName = NULL, const char * lpszAttribValue = NULL)
   {
      Init();
      m_strName = lpszAttribName;
      m_strValue = lpszAttribValue;
   }

   LiteHTMLElemAttr(const LiteHTMLElemAttr &rSource)
   {
      Init();
      m_strName = rSource.m_strName;
      m_strValue = rSource.m_strValue;
   }

   static void Init();

   string getName() const
   {
      return m_strName;
   }

   string getValue() const
   {
      return m_strValue;
   }

   /**
    * Determines if the attribute value is a named color value
    * @return true if attribute value is a named color, otherwise, false
    * @since 1.0
    * @author Gurmeet S. Kochar
    */
   bool isNamedColorValue(::lite_html_reader * preader) const;

   /**
    * Determines if the attribute value is a named system color value
    * @return true if value is a named system color, false otherwise
    * @since 1.0
    * @author Gurmeet S. Kochar
    */
   bool isSysColorValue(::lite_html_reader * preader) const;

   /**
    * Determines if the attribute value is a color value in
    * hexadecimal format
    * @return true if attribute value is a color value, otherwise, false
    * @since 1.0
    * @author Gurmeet S. Kochar
    */
   bool isHexColorValue() const;

   /**
    * Determines if the attribute value contains a color reference
    * @return true, if attribute value is color value, false otherwise.
    * @since 1.0
    * @author Gurmeet S. Kochar
    */
   bool isColorValue(::lite_html_reader * preader) const
      { return (isNamedColorValue(preader) || isHexColorValue()); }

   /**
    * Returns the color value of the attribute
    * @return a COLORREF representing the color
    * @since 1.0
    * @author Gurmeet S. Kochar
    */
   COLORREF getColorValue(::lite_html_reader * preader) const;

   /**
    * Returns the RGB value of the attribute in hexadecimal format
    * @return hexadecimal string representing the color value
    * @since 1.0
    * @author Gurmeet S. Kochar
    */
   string getColorHexValue(::lite_html_reader * preader) const;

   /**
    * Checks to see if the attribute contains a percent value
    * @return true if value is a percent value, otherwise, false
    * @since 1.0
    * @author Gurmeet S. Kochar
    */
   bool isPercentValue() const
      { return (m_strValue.Right(1) == "%" ? true : false); }

   /**
    * Returns a percent value of the attribute
    * @return percentage value
    * @since 1.0
    * @author Gurmeet S. Kochar
    */
   uint16_t getPercentValue(uint16_t max = USHRT_MAX) const
   {
      ASSERT(max > 0);
      if (!isPercentValue())   return (0);
      uint16_t   percentVal = (uint16_t)((int16_t)*this);
      return ((percentVal > max ? max : percentVal));
   }

   /**
    * Parses a length value from the attribute/value
    * and identifies its length unit also
    *
    * @param rUnit - this will receive the type of the length unit
    *
    * @return an integer value of the attribute
    * @since 1.0
    * @author Gurmeet S. Kochar
    */
   enum LengthUnitsEnum { em, ex, px, per, in, cm, mm, pt, pc };
   int16_t getLengthValue(LengthUnitsEnum &rUnit) const
   {
      static const char   _szUnits[][4] =
      {
         /** relative length units */
         "em", "ex", "px", "%",
         /** absolute length units */
         "in", "cm", "mm", "pt", "pc"
      };

      if (m_strValue.is_empty())
         return (0);

      int32_t i;
      for (i = 0; i < sizeof(_szUnits)/sizeof(_szUnits[0]); i++)
      {
         if (m_strValue.Right(::strlen(_szUnits[i])). \
            CompareNoCase(_szUnits[i]) == 0)
         {
            rUnit = (LengthUnitsEnum)i;
            break;
         }
      }
      if (i == sizeof(_szUnits)/sizeof(_szUnits[0]))
         return (0);
      return (*this);
   }

// Operators
public:
   /**
    * Converts attribute value to bool
    * @return true or false
    * @since 1.0
    * @author Gurmeet S. Kochar
    */
   operator bool() const
   {
      if (!m_strValue.CompareNoCase("true"))
         return (true);
      if (!m_strValue.CompareNoCase("false"))
         return (false);
      return (((int16_t)*this ? true : false));
   }

   /**
    * Converts attribute value to BYTE (uchar)
    * @return the left-most character of attribute value
    * @since 1.0
    * @author Gurmeet S. Kochar
    */
   operator BYTE() const
      { return ((BYTE)(m_strValue.get_length() ? m_strValue[0] : 0)); }

   /**
    * Converts attribute value to double
    * @return 0.00 on failure, otherwise, a numeric value
    * @since 1.0
    * @author Gurmeet S. Kochar
    */
   operator double() const
      { return (::strtod(m_strValue, NULL)); }

   /**
    * Converts attribute value to signed int16_t
    * @return 0 on failure, otherwise, an integer value
    * @since 1.0
    * @author Gurmeet S. Kochar
    */
   operator int16_t() const
      { return ((int16_t)::atoi(m_strValue)); }

   /**
    * @return attribute value
    * @since 1.0
    * @author Gurmeet S. Kochar
    */
   operator const char *() const
      { return (m_strValue); }

// Private Operations
private:
   /**
    * Sets the value of an attribute. Takes care of the following:
    *  1. Ignores leading and trailing white-space characters
    *  2. Replaces character entities with appropriate characters.
    *  3. Ignores line feeds (LF).
    *  4. Replaces each carriage-return (CR) or tab with a single space.
    *
    * @param lpszValue - new attribute value
    *
    * @since 1.0
    * @author Gurmeet S. Kochar
    */
   void putValue(::lite_html_reader * m_paxisapp, const char * lpszValue);

// Parsing Helpers
public:
   // parses an attribute/value pair from the given string
   uint_ptr parseFromStr(::lite_html_reader * preader, const char * lpszString);

};


/**
 * LiteHTMLAttributes
 *
 * @version 1.0 (Mar 18, 2004)
 * @author Gurmeet S. Kochar
 */
class LiteHTMLAttributes
{
// Construction/Destruction
public:
   LiteHTMLAttributes()
      : m_parrAttrib(NULL)
   { }

   /**
    * @param bCopy - if true, this LiteHTMLAttributes makes a copy
    * of the encapsulated pointer. if false, this constructor takes
    * ownership of the encapsulated pointer.
    *
    * @since 1.0
    * @author Gurmeet S. Kochar
    */
   LiteHTMLAttributes(LiteHTMLAttributes &rSource, bool bCopy = false)
      : m_parrAttrib(NULL)
   {
      if (!bCopy)
      {
         m_parrAttrib = rSource.m_parrAttrib;
         rSource.m_parrAttrib = NULL;
      }
      else
      {
         const ::count nElemCount = rSource.getCount();
         if (nElemCount)
         {
            if ((m_parrAttrib = new CElemAttrArray) == NULL)
               throw memory_exception(get_thread_app());

            LiteHTMLElemAttr   *pItem = NULL;
            m_parrAttrib->allocate(nElemCount);

            /** DEEP COPY BEGIN */
            for (int32_t iElem = 0; iElem < nElemCount; iElem++)
            {
               if ((pItem = new LiteHTMLElemAttr(rSource[iElem])) == NULL)
               {
                  removeAll();
                  throw memory_exception(get_thread_app());
                  return;
               }

               (*m_parrAttrib)[iElem] = pItem;
               pItem = NULL;
            }
            /** DEEP COPY END */
         }
      }
   }

   virtual ~LiteHTMLAttributes()
      { removeAll(); }

// Initialization
public:
   // parses attribute/value pairs from the given string
   uint_ptr parseFromStr(::lite_html_reader * papp, const char * lpszString, strsize iLen);

// Attributes
public:
   /**
    * Returns the ::count of LiteHTMLElemAttr items in this collection
    * @return number of items
    * @since 1.0
    * @author Gurmeet S. Kochar
    */
   ::count getCount() const
   {
      if (m_parrAttrib != NULL)
         return (m_parrAttrib->get_upper_bound() + 1);
      return (0);
   }

   /**
    * Look up the index of an attribute given its name.
    * If more than one attribute with the same name exist,
    * this will return the index of the first match.
    *
    * @param lpszAttributeName - name of the attribute
    *
    * @return zero-based index of an attribute, or -1 if not found
    * @since 1.0
    * @author Gurmeet S. Kochar
    */
   int32_t getIndexFromName(const char * lpszAttributeName) const
   {
      ASSERT(__is_valid_string(lpszAttributeName));
      LiteHTMLElemAttr   *pItem = NULL;
      for (int32_t iElem = 0; iElem < getCount(); iElem++)
      {
         if ((pItem = (*m_parrAttrib)[iElem]) == NULL)   // just in case
            continue;

         // perform a CASE-INSENSITIVE search
         if (pItem->m_strName.CompareNoCase(lpszAttributeName) == 0)
            return (iElem);
      }
      return (-1);
   }

   /**
    * Returns a LiteHTMLElemAttr object given an attribute's index
    *
    * @return LiteHTMLElemAttr containing the name and value of an attribute
    * @since 1.0
    * @author Gurmeet S. Kochar
    */
   LiteHTMLElemAttr operator[](int32_t nIndex) const
   {
      if (!(nIndex >= 0 && nIndex < getCount()))
      {
         ASSERT(FALSE);
         return (LiteHTMLElemAttr());
      }
      return ( *((*m_parrAttrib)[nIndex]) );
   }

   /**
    * Returns a LiteHTMLElemAttr object given an attribute name
    *
    * @return LiteHTMLElemAttr containing the name and value of an attribute
    * @since 1.0
    * @author Gurmeet S. Kochar
    */
   LiteHTMLElemAttr operator[](const char * lpszIndex) const
   {
      ASSERT(__is_valid_string(lpszIndex));
      return ((*this)[getIndexFromName(lpszIndex)]);
   }

   /**
    * Returns a LiteHTMLElemAttr object given an attribute's index
    *
    * @return LiteHTMLElemAttr containing the name and value of an attribute
    * @since 1.0
    * @author Gurmeet S. Kochar
    */
   LiteHTMLElemAttr getAttribute(int32_t nIndex) const
      { return ((*this)[nIndex]); }

   /**
    * Returns a LiteHTMLElemAttr object given an attribute name
    *
    * @return LiteHTMLElemAttr containing the name and value of an attribute
    * @since 1.0
    * @author Gurmeet S. Kochar
    */
   LiteHTMLElemAttr getAttribute(const char * lpszIndex) const
   {
      ASSERT(__is_valid_string(lpszIndex));
      return ((*this)[getIndexFromName(lpszIndex)]);
   }

   /**
    * Returns the name of an attribute given its index
    *
    * @return name of an attribute
    * @since 1.0
    * @author Gurmeet S. Kochar
    */
   string getName(int32_t nIndex) const
      { return ((*this)[nIndex].m_strName); }

   /**
    * Returns the value of an attribute given its index
    *
    * @return value of an attribute
    * @since 1.0
    * @author Gurmeet S. Kochar
    */
   string getValue(int32_t nIndex) const
      { return ((*this)[nIndex].m_strValue); }

   /**
    * Returns the value of an attribute given its name
    *
    * @return value of an attribute
    * @since 1.0
    * @author Gurmeet S. Kochar
    */
   string getValueFromName(const char * lpszAttributeName) const
      { return ((*this)[lpszAttributeName].m_strValue); }

// Operations
public:
   /**
    * Adds a new LiteHTMLElemAttr item to the collection
    *
    * @param lpszName - attribute name (serves as the key to the item)
    * @param lpszValue - attribute value
    * @param bReplaceOld - If an item with the same name as specified
    *        by lpszName already exists in the collection, this
    *        parameter is used to determine whether to replace the
    *        existing item or add a new one
    *
    * @return pointer to a LiteHTMLElemAttr
    * @since 1.0
    * @author Gurmeet S. Kochar
    */
   LiteHTMLElemAttr* addAttribute(const char * lpszName, const char * lpszValue);

   /**
    * Removes an LiteHTMLElemAttr item from the collection
    *
    * @param lpszName - attribute to remove
    *
    * @return true if successful, false otherwise
    * @since 1.0
    * @author Gurmeet S. Kochar
    */
   bool removeAttribute(int32_t nIndex)
   {
      if (!(nIndex >= 0 && nIndex < getCount()))
         return (false);
      LiteHTMLElemAttr   *pItem = (*m_parrAttrib)[nIndex];
      ASSERT(pItem != NULL);
      SAFE_DELETE_POINTER(pItem);
      return (true);
   }

   /**
    * Removes all LiteHTMLElemAttr items from the collection
    * @return true if successful, false otherwise
    * @since 1.0
    * @author Gurmeet S. Kochar
    */
   bool removeAll()
   {
      LiteHTMLElemAttr   *pItem = NULL;
      for (int32_t iElem = 0; iElem < getCount(); iElem++)
      {
         pItem = (*m_parrAttrib)[iElem];
         ASSERT(pItem != NULL);
         SAFE_DELETE_POINTER(pItem);
      }
      SAFE_DELETE_POINTER(m_parrAttrib);
      return (true);
   }

// Data Members
private:
   typedef primitive_array < LiteHTMLElemAttr * >   CElemAttrArray;
   CElemAttrArray   *m_parrAttrib;   // array of attributes/value pairs
};
