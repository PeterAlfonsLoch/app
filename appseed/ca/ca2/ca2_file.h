#pragma once


typedef struct MD5state_st MD5_CTX;


namespace ca4
{


   class CLASS_DECL_ca file :
      public ::gen::object
   {
   public:

      class CLASS_DECL_ca path :
         public ::gen::object
      {
      public:
         bool rename(const char * pszNew, const char * psz, ::ca::application * papp);
         file * m_pfile;
      };


      path m_path;

      file();


      string md5(const char * psz);
      string nessie(const char * psz);

      string nessie(gen::file * pfile);

      path & path36();
   
      void dtf(const char * pszFile, const char * pszDir, ::ca::application * papp);
      void dtf(const char * pszFile, stringa & stra, stringa & straRelative, ::ca::application * papp);
      void ftd(const char * pszDir, const char * pszFile, ::ca::application * papp);

      void is_valid_fileset(const char * pszFile, ::ca::application * papp);

      // 'n' (natural) terminated ascii number, example: 245765487n
      static void write_n_number(gen::file * pfile, ::crypto::md5::context * pctx, int64_t iNumber);
      static void read_n_number(gen::file * pfile, ::crypto::md5::context * pctx, int64_t & iNumber);

      static void write_gen_string(gen::file * pfile, ::crypto::md5::context * pctx, string & str);
      static void read_gen_string(gen::file * pfile, ::crypto::md5::context * pctx, string & str);


   };


} // namespace ca4


