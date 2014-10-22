#pragma once


namespace user
{


   class interaction_spa;


   class CLASS_DECL_AXIS oswindow_array :
      public comparable_array < oswindow, oswindow >
   {
   public:
      void SortByZOrder();
      void SortSiblingsByZOrder();
      void top_windows_by_z_order();
   };

   class CLASS_DECL_AXIS interaction_ptra:
      virtual public ptr_array < ::user::interaction >
   {
   public:

      interaction_ptra();
      interaction_ptra(const interaction_ptra & array);
      interaction_ptra(const ptr_array < ::user::interaction > & array);
      interaction_ptra(const interaction_spa & array);
      interaction_ptra(interaction_ptra && array);


      interaction_ptra & operator = (const interaction_ptra & array);
      interaction_ptra & operator = (const ptr_array < ::user::interaction > & array);
      interaction_ptra & operator = (interaction_ptra && array);

      ::user::oswindow_array get_hwnda();

      using ptr_array < ::user::interaction >::find_first;
      ::user::interaction * find_first_typed(sp(type) info);
      ::user::interaction * find_first(oswindow oswindow);


   };


   class CLASS_DECL_AXIS interaction_spa :
      virtual public spa(::user::interaction)
   {
   public:


      interaction_spa();
      interaction_spa(sp(::aura::application) papp);
      interaction_spa(const ptr_array < ::user::interaction > & a);
      interaction_spa(const ::user::interaction_spa & a)
      {

         copy(a);

      }

#ifdef MOVE_SEMANTICS

      interaction_spa(const ::user::interaction_spa && a)
      {

         copy(a);

      }

#endif


      using spa(::user::interaction)::find_first;
      sp(::user::interaction) find_first_typed(sp(type) info);
      sp(::user::interaction) find_first(oswindow oswindow);

      ::user::oswindow_array get_hwnda();
      void send_message(UINT uiMessage, WPARAM wparam = 0, LPARAM lparam = 0);
      void send_message_to_descendants(UINT uiMessage, WPARAM wparam = 0, LPARAM lparam = 0, bool bRecursive = true);

      interaction_spa & operator = (const interaction_spa & a);

      };


   class CLASS_DECL_AXIS oswindow_tree :
      virtual public element
   {
   public:

      class CLASS_DECL_AXIS Array :
         public spa(oswindow_tree)
      {
      public:

         bool remove(oswindow oswindow);
         int_ptr find(oswindow oswindow);
         void EnumDescendants();
         Array & operator = (oswindow_array & oswindowa);

         };

      oswindow       m_oswindow;
      uint32_t       m_dwUser;
      oswindow       m_pvoidUser;
      Array          m_oswindowtreea;


      oswindow_tree();
      oswindow_tree(oswindow interaction_impl);
      oswindow_tree(const oswindow_tree & tree);

      void EnumDescendants();

      oswindow_tree & operator = (const oswindow_tree & tree);

      static index compare_oswindow(const oswindow_tree * ptree1, const oswindow_tree * ptree2);


   };


   class CLASS_DECL_AXIS window_util
   {
   public:
      static void ContraintPosToParent(oswindow oswindow);
      //static void EnumChildren(::window_sp pwnd, interaction_spa & wndpa);
      static void EnumChildren(oswindow oswindow, oswindow_array & oswindowa);
      /*static void ExcludeChild(interaction_spa & wndpa);*/
      /*static void SortByZOrder(interaction_spa & wndpa);*/
      static void SortByZOrder(oswindow_array & oswindowa);
      static HRGN GetAClipRgn(oswindow oswindow, POINT ptOffset, bool bExludeChilren);
      static void ExcludeChildren(oswindow oswindow, HRGN hrgn, POINT ptOffset);
      window_util();
      virtual ~window_util();
      /*static void SendMessageToDescendants(oswindow oswindow, UINT message,
      WPARAM wParam, LPARAM lParam, bool bDeep, bool bOnlyPerm);*/
      static void SendMessageToDescendants(oswindow oswindow, UINT message,
         WPARAM wParam, LPARAM lParam, bool bDeep);
      static bool IsAscendant(oswindow oswindowAscendant, oswindow oswindowDescendant);

      static int32_t GetZOrder(oswindow oswindow);
      static void GetZOrder(oswindow oswindow, int_array & ia);

      //      static HRGN GetAClipRgn(oswindow oswindow, POINT ptOffset, bool bExludeChilren);
      //      static void ExcludeChildren(oswindow oswindow, HRGN hrgn, POINT ptOffset);

      //static void SortByZOrder(comparable_array < ::window_sp, ::window_sp > & wndpa);
      //static void SortByZOrder(comparable_array < oswindow, oswindow > & oswindowa);
      //static void EnumChildren(oswindow oswindow, comparable_array < oswindow, oswindow > & oswindowa);

   };




} // namespace user



