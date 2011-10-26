#pragma once


namespace whiteboard
{

   class CLASS_DECL_CA2_TESSERACT sites
   {
   public:
      site * get_at(int iIndex);
      site * get(e_site esite);
      void add(const site & site);
      int get_count();
   protected:
      base_array < site > m_sitea;
   };

} // namespace whiteboard