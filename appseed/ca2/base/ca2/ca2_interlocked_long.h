#pragma once


namespace ca2
{

   class CLASS_DECL_ca2 interlocked_long
   {
   public:
      
      
      long *       m_plong;

      
      interlocked_long();
      virtual ~interlocked_long();


      void add(long l);
      void subtract(long l);

      bool operator > (long i) const;
      bool operator == (long i) const;

   };

} // namespace ca2
