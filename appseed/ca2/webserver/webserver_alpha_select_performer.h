#pragma once


namespace webserver
{


   class CLASS_DECL_ca AlphaSelectLinkMaker
   {
   public:
      virtual string code_getLink(const char * classid, const char * code) = 0;
   };


   class CLASS_DECL_ca AlphaSelectPerformerLinkMaker : 
      public dynamic_source::ptr,
      public AlphaSelectLinkMaker
   {
   public:
      string m_strLang;
      string m_strStyle;
      string code_getLink(const char * classid, const char * code);
   };

   class CLASS_DECL_ca AlphaSelectPerformerLinkMaker3 :
      public dynamic_source::ptr,
      public AlphaSelectLinkMaker
   {
   public:
      string m_strLang;
      string m_strStyle;
      string code_getLink(const char * classid, const char * code);
   };

   class CLASS_DECL_ca AlphaSelectPerformer :
      public dynamic_source::ptr
   {
   public:
      AlphaSelectPerformer(const char * topic = NULL);


      AlphaSelectLinkMaker *  m_plinkmaker;
      string                  m_strClassId;
      gen::var_property       m_kptitlea;
      string                  m_strLangStyle;
      int                     m_iTopicType;


      void out(int style);

      stringa code_getArray(int style = 2);

      stringa code_getFullArray(int style = 2);

      void out_xml1();

      void print_td(const char * prefix, const char * pszTitle = NULL);

      int code_getCount(const char * code);

      void code_printCells(const stringa & codea, int style);

      void code_printCell(const char * code, int style, int & index);

      void code_printXml1Tree(const stringa & codea, int style);

      void code_printXml1Element(const char * code, int style, int & index);

      void code_printSpan(const char * code);

      string get_title(const char * code);

      string get_reg_exp(const char * pszCode);

   };


} // namespace webserver


