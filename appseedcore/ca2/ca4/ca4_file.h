#pragma once

namespace ca4
{

   class CLASS_DECL_ca file :
      public ::radix::object
   {
   public:
      file();
      class CLASS_DECL_ca path :
         public ::radix::object
      {
      public:
         bool rename(const char * pszNew, const char * psz);
         file * m_pfile;
      };
      string md5(const char * psz);
      string nessie(const char * psz);

      path & path36();
   
         void dtf(const char * pszFile, const char * pszDir);
         void dtf(const char * pszFile, stringa & stra, stringa & straRelative);
         void ftd(const char * pszDir, const char * pszFile);

         void is_valid_fileset(const char * pszFile);

         // 'n' (natural) terminated ascii number, example: 245765487n
         static void write_n_number(ex1::file * pfile, MD5_CTX * pctx, int iNumber);
         static void read_n_number(ex1::file * pfile, MD5_CTX * pctx, int & iNumber);

         static void write_ex1_string(ex1::file * pfile, MD5_CTX * pctx, string & str);
         static void read_ex1_string(ex1::file * pfile, MD5_CTX * pctx, string & str);


   protected:
      path m_path;

   };

} // namespace ca4