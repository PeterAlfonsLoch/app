#pragma once

namespace kar
{

	class CLASS_DECL_CA2_CUBE page_category :
      virtual public body_page
	{
   public:
		var m_perpertop;		
		var m_ppt_year;		
		var m_ppt_month;		
		var m_ppt_week;	
		music::in2_list_category *             m_plist;	
		AlphaSelectPerformer *                 m_pasp;	
		AlphaSelectPerformerLinkMaker3 *       m_plm;	
		ui_nav * m_pnavYear;
		ui_nav * m_pnavMonth;
		ui_nav * m_pnavWeek;
		var m_title1;
		var m_pagetitle1;
		
		
		
		page_category();
	
	   void print_head();
	   void print_body();

   };

} // namespace kar
