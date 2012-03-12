#pragma once


namespace webserver
{


   class CLASS_DECL_ca AlphaSelectLinkMaker
   {
   public:
      virtual string code_getLink(const int64_array & iaClassId, const char * code) = 0;
   };


   class CLASS_DECL_ca AlphaSelectPerformerLinkMaker : 
      public dynamic_source::ptr,
      public AlphaSelectLinkMaker
   {
   public:
      string m_strLang;
      string m_strSchema;
      string code_getLink(const int64_array & iaClassId, const char * code);
   };

   class CLASS_DECL_ca AlphaSelectPerformerLinkMaker3 :
      public dynamic_source::ptr,
      public AlphaSelectLinkMaker
   {
   public:
      string m_strLang;
      string m_strSchema;
      string code_getLink(const int64_array & iaClassId, const char * code);
   };

   class CLASS_DECL_ca AlphaSelectPerformer :
      public dynamic_source::ptr
   {
   public:


      AlphaSelectLinkMaker *  m_plinkmaker;
      int64_array             m_iaClassId;
      gen::var_property       m_kptitlea;
      string                  m_strLangStyle;
      int                     m_iTopicType;


      AlphaSelectPerformer();
      AlphaSelectPerformer(int64_t topic);

      void construct();

      void out(index style);

      stringa code_getArray();

      stringa code_calcArray();

      stringa code_getFullArray();

      void out_xml1();

      void print_td(const char * prefix, const char * pszTitle = NULL);

      int code_getCount(const char * pszCode);

      void code_printCells(const stringa & codea, index style);

      void code_printCell(const char * code, index style, index & index);

      void code_printXml1Tree(const stringa & codea, index style);

      void code_printXml1Element(const char * code, index style, index & index);

      void code_printSpan(const char * code);

      string get_title(const char * code);

      string get_reg_exp(const char * pszCode);

   };


} // namespace webserver


