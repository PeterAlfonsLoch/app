#pragma once




class CLASS_DECL_c simple_memory
{
public:

   
   char *      m_psz;
   int         m_iAlloc;
   int         m_iSize;

   int         m_iPos;


   simple_memory();
   simple_memory(const char * psz);
   ~simple_memory();


   void allocate(int iSize);


   void write(void * p, int iCount);


   int read(void * p, int iCount) const;


   void from_string(const vsstring & str);

   vsstring str();

   void to_string(vsstring & str);

   inline void * get_data() { return m_psz; }

   inline const void * get_data() const { return m_psz; }

   inline ::count get_size() const { return m_iSize; } 

};



