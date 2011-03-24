#pragma once


namespace ca
{

   class CLASS_DECL_ca interlocked_long
   {
   public:
      
      
      PLONG       m_plong;

      
      interlocked_long();
      virtual ~interlocked_long();


      void add(long l);
      void subtract(long l);

      bool operator > (int i) const;
      bool operator == (int i) const;

   };

} // namespace ca