#include "framework.h"


namespace simple_ui
{

   
   class CLASS_DECL_BASE message_box :
      virtual public ::simple_ui::interaction
   {
   public:

   
      stringa        m_stra;
      sp(tap)        m_ptapOk;
      sp(tap)        m_ptapYes;
      sp(tap)        m_ptapNo;
      sp(tap)        m_ptapCancel;
      int32_t        m_iResult;
      uint32_t       m_uiFlags;
      

      message_box(sp(::base::application) papp);
      virtual ~message_box();


      int32_t show(const char * pszMessage, uint32_t uiFlags);

      DRAWDD();

      virtual void layout();

      bool on_action(const char * pszId);
      

   };


} // namespace simple_ui



CLASS_DECL_BASE int32_t simple_ui_message_box(oswindow window, const char * lpText,const char * lpCaption, uint32_t uiFlags);






