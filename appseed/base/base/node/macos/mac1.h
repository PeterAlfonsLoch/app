#pragma once


namespace mac
{
   
   
   class thread;
   
   class MAC
   {
      int32_t function();
   };
   
   
   
} // namespace mac



// Placed on frame for EXCEPTION linkage, or ::exception::base cleanup
struct CLASS_DECL_mac __exception_link
{
   __exception_link* m_pLinkPrev;    // previous top, next in handler chain
   ::exception::base * m_pException;   // current exception (NULL in try block)
   
   __exception_link();       // for initialization and linking
   ~__exception_link()       // for cleanup and unlinking
   {
      //__try_cleanup();
   };
};

// Exception global state - never access directly
struct CLASS_DECL_mac __EXCEPTION_CONTEXT
{

   __exception_link* m_pLinkTop;

};

void CLASS_DECL_mac __abort();



CLASS_DECL_mac LRESULT CALLBACK __window_procedure(oswindow hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam);


CLASS_DECL_mac MESSAGE * __get_current_message();


CLASS_DECL_mac void __mac_term();


CLASS_DECL_mac void __delete_object(HGDIOBJ* pObject);

void CLASS_DECL_mac __global_free(HGLOBAL hGlobal);
