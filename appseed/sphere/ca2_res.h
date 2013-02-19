#ifndef __AFXRES_H__
#define __AFXRES_H__

#ifdef RC_INVOKED
#ifndef _INC_WINDOWS
#define _INC_WINDOWS
   #include "winres.h"           // extract from windows header
#endif
#endif

#ifdef RC_INVOKED
	#if defined(_VC80_UPGRADE) && (_VC80_UPGRADE >= 0x0700) && (_VC80_UPGRADE < 0x0800) && defined(IDR_MANIFEST)
		// Handle project upgrade from VC7/VC7.1 for projects with manifest
		#define IDR_MANIFEST	1024
	#endif
#endif	// RC_INVOKED

#ifdef APSTUDIO_INVOKED
#define APSTUDIO_HIDDEN_SYMBOLS
#endif

/////////////////////////////////////////////////////////////////////////////
// ca2 API resource types (see Technical note TN024 for implementation details)

#ifndef RC_INVOKED
#define RT_DLGINIT  MAKEINTRESOURCE(240)
#define RT_TOOLBAR  MAKEINTRESOURCE(241)
#endif

/////////////////////////////////////////////////////////////////////////////

#ifdef APSTUDIO_INVOKED
#undef APSTUDIO_HIDDEN_SYMBOLS
#endif



/////////////////////////////////////////////////////////////////////////////
// Manifest Resource ID of manifest containing Localized DLL information
#define ID_MFCLOC_MANIFEST             1000

/////////////////////////////////////////////////////////////////////////////
// Standard ::ca::window components

// Mode indicators in status bar - these are routed like commands
#define ID_INDICATOR_EXT                0xE700  // extended selection indicator
#define ID_INDICATOR_CAPS               0xE701  // cap lock indicator
#define ID_INDICATOR_NUM                0xE702  // num lock indicator
#define ID_INDICATOR_SCRL               0xE703  // scroll lock indicator
#define ID_INDICATOR_OVR                0xE704  // overtype mode indicator
#define ID_INDICATOR_REC                0xE705  // record mode indicator
#define ID_INDICATOR_KANA               0xE706  // kana lock indicator

#define ID_SEPARATOR                    0   // special separator value

#ifndef RC_INVOKED  // code only

// parts of Main Frame
#define "pane_first"              0xE900  // first pane (256 max)
#define __IDW_PANE_LAST               0xE9ff
#define __IDW_HSCROLL_FIRST           0xEA00  // first Horz scrollbar (16 max)
#define __IDW_VSCROLL_FIRST           0xEA10  // first Vert scrollbar (16 max)

#define __IDW_SIZE_BOX                0xEA20  // size box for splitters
#define "pane_save"               0xEA21  // to shift "pane_first"
#endif //!RC_INVOKED

#ifndef APSTUDIO_INVOKED

// common style for form views
#define __WS_DEFAULT_VIEW             (WS_CHILD | WS_VISIBLE | WS_BORDER)

#endif //!APSTUDIO_INVOKED

/////////////////////////////////////////////////////////////////////////////
// Standard cast configurable strings

// for application title (defaults to EXE name or name in constructor)
#define __IDS_APP_TITLE               0xE000
// idle message bar line
#define __IDS_IDLEMESSAGE             0xE001
// message bar line when in shift-F1 help mode
#define __IDS_HELPMODEMESSAGE         0xE002
// document title when editing OLE embedding
#define __IDS_APP_TITLE_EMBEDDING     0xE003
// company name
#define __IDS_COMPANY_NAME            0xE004
// object name when server is inplace
#define __IDS_OBJ_TITLE_INPLACE       0xE005

/////////////////////////////////////////////////////////////////////////////
// Standard Commands

// File commands
#define ID_FILE_NEW                     0xE100
#define ID_FILE_OPEN                    0xE101
#define ID_FILE_CLOSE                   0xE102
#define ID_FILE_SAVE                    0xE103
#define ID_FILE_SAVE_AS                 0xE104
#define ID_FILE_PAGE_SETUP              0xE105
#define ID_FILE_PRINT_SETUP             0xE106
#define ID_FILE_PRINT                   0xE107
#define ID_FILE_PRINT_DIRECT            0xE108
#define ID_FILE_PRINT_PREVIEW           0xE109
#define ID_FILE_UPDATE                  0xE10A
#define ID_FILE_SAVE_COPY_AS            0xE10B
#define ID_FILE_SEND_MAIL               0xE10C
#define ID_FILE_NEW_FRAME               0xE10D

#define ID_FILE_MRU_FIRST               0xE110
#define ID_FILE_MRU_FILE1               0xE110          // range - 16 max
#define ID_FILE_MRU_FILE2               0xE111
#define ID_FILE_MRU_FILE3               0xE112
#define ID_FILE_MRU_FILE4               0xE113
#define ID_FILE_MRU_FILE5               0xE114
#define ID_FILE_MRU_FILE6               0xE115
#define ID_FILE_MRU_FILE7               0xE116
#define ID_FILE_MRU_FILE8               0xE117
#define ID_FILE_MRU_FILE9               0xE118
#define ID_FILE_MRU_FILE10              0xE119
#define ID_FILE_MRU_FILE11              0xE11A
#define ID_FILE_MRU_FILE12              0xE11B
#define ID_FILE_MRU_FILE13              0xE11C
#define ID_FILE_MRU_FILE14              0xE11D
#define ID_FILE_MRU_FILE15              0xE11E
#define ID_FILE_MRU_FILE16              0xE11F
#define ID_FILE_MRU_LAST                0xE11F

// Edit commands
#define ID_EDIT_CLEAR                   0xE120
#define ID_EDIT_CLEAR_ALL               0xE121
#define ID_EDIT_COPY                    0xE122
#define ID_EDIT_CUT                     0xE123
#define ID_EDIT_FIND                    0xE124
#define ID_EDIT_PASTE                   0xE125
#define ID_EDIT_PASTE_LINK              0xE126
#define ID_EDIT_PASTE_SPECIAL           0xE127
#define ID_EDIT_REPEAT                  0xE128
#define ID_EDIT_REPLACE                 0xE129
#define ID_EDIT_SELECT_ALL              0xE12A
#define ID_EDIT_UNDO                    0xE12B
#define ID_EDIT_REDO                    0xE12C

// Window commands
#define ID_WINDOW_NEW                   0xE130
#define ID_WINDOW_ARRANGE               0xE131
#define ID_WINDOW_CASCADE               0xE132
#define ID_WINDOW_TILE_HORZ             0xE133
#define ID_WINDOW_TILE_VERT             0xE134
#define ID_WINDOW_SPLIT                 0xE135
#ifndef RC_INVOKED      // code only
#define __IDM_WINDOW_FIRST            0xE130
#define __IDM_WINDOW_LAST             0xE13F
#define __IDM_FIRST_MDICHILD          0xFF00  // ::ca::window list starts here
#endif //!RC_INVOKED

// Help and App commands
#define ID_APP_ABOUT                    0xE140
#define ID_APP_EXIT                     0xE141
#define ID_HELP_INDEX                   0xE142
#define ID_HELP_FINDER                  0xE143
#define ID_HELP_USING                   0xE144
#define ID_CONTEXT_HELP                 0xE145      // shift-F1
// special commands for processing help
#define ID_HELP                         0xE146      // first attempt for F1
#define ID_DEFAULT_HELP                 0xE147      // last attempt

// Misc
#define ID_NEXT_PANE                    0xE150
#define ID_PREV_PANE                    0xE151

// Format
#define ID_FORMAT_FONT                  0xE160

// OLE commands
#define ID_OLE_INSERT_NEW               0xE200
#define ID_OLE_EDIT_LINKS               0xE201
#define ID_OLE_EDIT_CONVERT             0xE202
#define ID_OLE_EDIT_CHANGE_ICON         0xE203
#define ID_OLE_EDIT_PROPERTIES          0xE204
#define ID_OLE_VERB_FIRST               0xE210     // range - 16 max
#ifndef RC_INVOKED      // code only
#define ID_OLE_VERB_LAST                0xE21F
#endif //!RC_INVOKED

// for print preview dialog bar
#define __ID_PREVIEW_CLOSE            0xE300
#define __ID_PREVIEW_NUMPAGE          0xE301      // One/Two Page button
#define __ID_PREVIEW_NEXT             0xE302
#define __ID_PREVIEW_PREV             0xE303
#define __ID_PREVIEW_PRINT            0xE304
#define __ID_PREVIEW_ZOOMIN           0xE305
#define __ID_PREVIEW_ZOOMOUT          0xE306

// ::view commands (same number used as IDW used for control bar)
#define ID_VIEW_TOOLBAR                 0xE800
#define ID_VIEW_STATUS_BAR              0xE801
#define ID_VIEW_REBAR                   0xE804
#define ID_VIEW_AUTOARRANGE         0xE805
   // E810 -> E81F must be kept in order for RANGE macros
#define ID_VIEW_SMALLICON               0xE810
#define ID_VIEW_LARGEICON               0xE811
#define ID_VIEW_LIST                   0xE812
#define ID_VIEW_DETAILS                 0xE813
#define ID_VIEW_LINEUP                  0xE814
#define ID_VIEW_BYNAME                  0xE815
#define __ID_VIEW_MINIMUM              ID_VIEW_SMALLICON
#define __ID_VIEW_MAXIMUM              ID_VIEW_BYNAME
   // E800 -> E8FF reserved for other control bar commands

// RecordForm commands
#define ID_RECORD_FIRST                 0xE900
#define ID_RECORD_LAST                  0xE901
#define ID_RECORD_NEXT                  0xE902
#define ID_RECORD_PREV                  0xE903

/////////////////////////////////////////////////////////////////////////////
// Standard control IDs

#ifdef IDC_STATIC
#undef IDC_STATIC
#endif
#define IDC_STATIC              (-1)     // all static controls

/////////////////////////////////////////////////////////////////////////////
// Standard string error/warnings

#ifndef RC_INVOKED      // code only
#define __IDS_SCFIRST                 0xEF00
#endif //!RC_INVOKED

/*

commenttest

#define __IDS_SCSIZE                  0xEF00
#define __IDS_SCMOVE                  0xEF01
#define __IDS_SCMINIMIZE              0xEF02
#define __IDS_SCMAXIMIZE              0xEF03
#define __IDS_SCNEXTWINDOW            0xEF04
#define __IDS_SCPREVWINDOW            0xEF05
#define __IDS_SCCLOSE                 0xEF06
#define __IDS_SCRESTORE               0xEF12
#define __IDS_SCTASKLIST              0xEF13

#define __IDS_MDICHILD                0xEF1F

#define __IDS_DESKACCESSORY           0xEFDA

// General strings
#define __IDS_OPENFILE                0xF000
#define __IDS_SAVEFILE                0xF001
#define __IDS_ALLFILTER               0xF002
#define __IDS_UNTITLED                0xF003
#define __IDS_SAVEFILECOPY            0xF004
#define __IDS_PREVIEW_CLOSE           0xF005
#define __IDS_UNNAMED_FILE            0xF006
#define __IDS_HIDE                    0xF011

// ca2 API Standard Exception Error messages
#define __IDP_NO_ERROR_AVAILABLE      0xF020
#define __IDS_NOT_SUPPORTED_EXCEPTION 0xF021
#define __IDS_RESOURCE_EXCEPTION      0xF022
#define __IDS_MEMORY_EXCEPTION        0xF023
#define __IDS_USER_EXCEPTION          0xF024
#define __IDS_INVALID_ARG_EXCEPTION   0xF025

// Printing and print preview strings
#define __IDS_PRINTONPORT             0xF040
#define __IDS_ONEPAGE                 0xF041
#define __IDS_TWOPAGE                 0xF042
#define __IDS_PRINTPAGENUM            0xF043
#define __IDS_PREVIEWPAGEDESC         0xF044
#define __IDS_PRINTDEFAULTEXT         0xF045
#define __IDS_PRINTDEFAULT            0xF046
#define __IDS_PRINTFILTER             0xF047
#define __IDS_PRINTCAPTION            0xF048
#define __IDS_PRINTTOFILE             0xF049


// OLE strings
#define __IDS_OBJECT_MENUITEM         0xF080
#define __IDS_EDIT_VERB               0xF081
#define __IDS_ACTIVATE_VERB           0xF082
#define __IDS_CHANGE_LINK             0xF083
#define __IDS_AUTO                    0xF084
#define __IDS_MANUAL                  0xF085
#define __IDS_FROZEN                  0xF086
#define __IDS_ALL_FILES               0xF087
// dynamically changing menu items
#define __IDS_SAVE_MENU               0xF088
#define __IDS_UPDATE_MENU             0xF089
#define __IDS_SAVE_AS_MENU            0xF08A
#define __IDS_SAVE_COPY_AS_MENU       0xF08B
#define __IDS_EXIT_MENU               0xF08C
#define __IDS_UPDATING_ITEMS          0xF08D
// COlePasteSpecialDialog defines
#define __IDS_METAFILE_FORMAT         0xF08E
#define __IDS_DIB_FORMAT              0xF08F
#define __IDS_BITMAP_FORMAT           0xF090
#define __IDS_LINKSOURCE_FORMAT       0xF091
#define __IDS_EMBED_FORMAT            0xF092
// other OLE utility strings
#define __IDS_PASTELINKEDTYPE         0xF094
#define __IDS_UNKNOWNTYPE             0xF095
#define __IDS_RTF_FORMAT              0xF096
#define __IDS_TEXT_FORMAT             0xF097
// OLE datatype format error strings
#define __IDS_INVALID_CURRENCY        0xF098
#define __IDS_INVALID_DATETIME        0xF099
#define __IDS_INVALID_DATETIMESPAN    0xF09A

// General error / prompt strings
#define __IDP_INVALID_FILENAME        0xF100
#define __IDP_FAILED_TO_OPEN_DOC      0xF101
#define __IDP_FAILED_TO_SAVE_DOC      0xF102
#define __IDP_ASK_TO_SAVE             0xF103
#define __IDP_FAILED_TO_CREATE_DOC    0xF104
#define __IDP_FILE_TOO_LARGE          0xF105
#define __IDP_FAILED_TO_START_PRINT   0xF106
#define __IDP_FAILED_TO_LAUNCH_HELP   0xF107
#define __IDP_INTERNAL_FAILURE        0xF108      // general failure
#define __IDP_COMMAND_FAILURE         0xF109      // command failure
#define __IDP_FAILED_MEMORY_ALLOC     0xF10A
#define __IDP_UNREG_DONE              0xF10B
#define __IDP_UNREG_FAILURE           0xF10C
#define __IDP_DLL_LOAD_FAILED         0xF10D
#define __IDP_DLL_BAD_VERSION         0xF10E

// DDV parse errors
#define __IDP_PARSE_INT               0xF110
#define __IDP_PARSE_REAL              0xF111
#define __IDP_PARSE_INT_RANGE         0xF112
#define __IDP_PARSE_REAL_RANGE        0xF113
#define __IDP_PARSE_STRING_SIZE       0xF114
#define __IDP_PARSE_RADIO_BUTTON      0xF115
#define __IDP_PARSE_BYTE              0xF116
#define __IDP_PARSE_UINT              0xF117
#define __IDP_PARSE_DATETIME          0xF118
#define __IDP_PARSE_CURRENCY          0xF119
#define __IDP_PARSE_GUID              0xF11A
#define __IDP_PARSE_TIME              0xF11B
#define __IDP_PARSE_DATE              0xF11C

// ex1::filesp/CArchive error strings for ::user::profile failure
#define __IDP_FAILED_INVALID_FORMAT   0xF120
#define __IDP_FAILED_INVALID_PATH     0xF121
#define __IDP_FAILED_DISK_FULL        0xF122
#define __IDP_FAILED_ACCESS_READ      0xF123
#define __IDP_FAILED_ACCESS_WRITE     0xF124
#define __IDP_FAILED_IO_ERROR_READ    0xF125
#define __IDP_FAILED_IO_ERROR_WRITE   0xF126

// Script errors / prompt strings
#define __IDP_SCRIPT_ERROR            0xF130
#define __IDP_SCRIPT_DISPATCH_EXCEPTION 0xF131

// OLE errors / prompt strings
#define __IDP_STATIC_OBJECT           0xF180
#define __IDP_FAILED_TO_CONNECT       0xF181
#define __IDP_SERVER_BUSY             0xF182
#define __IDP_BAD_VERB                0xF183
#define __IDS_NOT_DOCOBJECT           0xF184
#define __IDP_FAILED_TO_NOTIFY        0xF185
#define __IDP_FAILED_TO_LAUNCH        0xF186
#define __IDP_ASK_TO_UPDATE           0xF187
#define __IDP_FAILED_TO_UPDATE        0xF188
#define __IDP_FAILED_TO_REGISTER      0xF189
#define __IDP_FAILED_TO_AUTO_REGISTER 0xF18A
#define __IDP_FAILED_TO_CONVERT       0xF18B
#define __IDP_GET_NOT_SUPPORTED       0xF18C
#define __IDP_SET_NOT_SUPPORTED       0xF18D
#define __IDP_ASK_TO_DISCARD          0xF18E
#define __IDP_FAILED_TO_CREATE        0xF18F

// MAPI errors / prompt strings
#define __IDP_FAILED_MAPI_LOAD        0xF190
#define __IDP_INVALID_MAPI_DLL        0xF191
#define __IDP_FAILED_MAPI_SEND        0xF192

#define __IDP_FILE_NONE               0xF1A0
#define __IDP_FILE_GENERIC            0xF1A1
#define __IDP_FILE_NOT_FOUND          0xF1A2
#define __IDP_FILE_BAD_PATH           0xF1A3
#define __IDP_FILE_TOO_MANY_OPEN      0xF1A4
#define __IDP_FILE_ACCESS_DENIED      0xF1A5
#define __IDP_FILE_INVALID_FILE       0xF1A6
#define __IDP_FILE_REMOVE_CURRENT     0xF1A7
#define __IDP_FILE_DIR_FULL           0xF1A8
#define __IDP_FILE_BAD_SEEK           0xF1A9
#define __IDP_FILE_HARD_IO            0xF1AA
#define __IDP_FILE_SHARING            0xF1AB
#define __IDP_FILE_LOCKING            0xF1AC
#define __IDP_FILE_DISKFULL           0xF1AD
#define __IDP_FILE_EOF                0xF1AE

#define __IDP_ARCH_NONE               0xF1B0
#define __IDP_ARCH_GENERIC            0xF1B1
#define __IDP_ARCH_READONLY           0xF1B2
#define __IDP_ARCH_ENDOFFILE          0xF1B3
#define __IDP_ARCH_WRITEONLY          0xF1B4
#define __IDP_ARCH_BADINDEX           0xF1B5
#define __IDP_ARCH_BADCLASS           0xF1B6
#define __IDP_ARCH_BADSCHEMA          0xF1B7

#define __IDS_OCC_SCALEUNITS_PIXELS   0xF1C0

// 0xf200-0xf20f reserved

// font names and point sizes
#define __IDS_STATUS_FONT             0xF230
#define __IDS_TOOLTIP_FONT            0xF231
#define __IDS_UNICODE_FONT            0xF232
#define __IDS_MINI_FONT               0xF233

// ODBC Database errors / prompt strings
#ifndef RC_INVOKED      // code only
#define __IDP_SQL_FIRST                       0xF280
#endif //!RC_INVOKED
#define __IDP_SQL_CONNECT_FAIL                0xF281
#define __IDP_SQL_RECORDSET_FORWARD_ONLY      0xF282
#define __IDP_SQL_EMPTY_COLUMN_LIST           0xF283
#define __IDP_SQL_FIELD_SCHEMA_MISMATCH       0xF284
#define __IDP_SQL_ILLEGAL_MODE                0xF285
#define __IDP_SQL_MULTIPLE_ROWS_AFFECTED      0xF286
#define __IDP_SQL_NO_CURRENT_RECORD           0xF287
#define __IDP_SQL_NO_ROWS_AFFECTED            0xF288
#define __IDP_SQL_RECORDSET_READONLY          0xF289
#define __IDP_SQL_SQL_NO_TOTAL                0xF28A
#define __IDP_SQL_ODBC_LOAD_FAILED            0xF28B
#define __IDP_SQL_DYNASET_NOT_SUPPORTED       0xF28C
#define __IDP_SQL_SNAPSHOT_NOT_SUPPORTED      0xF28D
#define __IDP_SQL_API_CONFORMANCE             0xF28E
#define __IDP_SQL_SQL_CONFORMANCE             0xF28F
#define __IDP_SQL_NO_DATA_FOUND               0xF290
#define __IDP_SQL_ROW_UPDATE_NOT_SUPPORTED    0xF291
#define __IDP_SQL_ODBC_V2_REQUIRED            0xF292
#define __IDP_SQL_NO_POSITIONED_UPDATES       0xF293
#define __IDP_SQL_LOCK_MODE_NOT_SUPPORTED     0xF294
#define __IDP_SQL_DATA_TRUNCATED              0xF295
#define __IDP_SQL_ROW_FETCH                   0xF296
#define __IDP_SQL_INCORRECT_ODBC              0xF297
#define __IDP_SQL_UPDATE_DELETE_FAILED        0xF298
#define __IDP_SQL_DYNAMIC_CURSOR_NOT_SUPPORTED    0xF299
#define __IDP_SQL_FIELD_NOT_FOUND             0xF29A
#define __IDP_SQL_BOOKMARKS_NOT_SUPPORTED     0xF29B
#define __IDP_SQL_BOOKMARKS_NOT_ENABLED       0xF29C

// ODBC Database strings
#define __IDS_DELETED                   0xF29D

// DAO Database errors / prompt strings
#ifndef RC_INVOKED      // code only
#define __IDP_DAO_FIRST                       0xF2B0
#endif //!RC_INVOKED
#define __IDP_DAO_ENGINE_INITIALIZATION       0xF2B0
#define __IDP_DAO_DFX_BIND                    0xF2B1
#define __IDP_DAO_OBJECT_NOT_OPEN             0xF2B2

// ICDAORecordset::GetRows Errors
//  These are not placed in DAO Errors collection
//  and must be handled directly by ca2 API.
#define __IDP_DAO_ROWTOOSHORT                 0xF2B3
#define __IDP_DAO_BADBINDINFO                 0xF2B4
#define __IDP_DAO_COLUMNUNAVAILABLE           0xF2B5

/////////////////////////////////////////////////////////////////////////////
// Strings for ISAPI support

#define __IDS_HTTP_TITLE              0xF2D1
#define __IDS_HTTP_NO_TEXT            0xF2D2
#define __IDS_HTTP_BAD_REQUEST        0xF2D3
#define __IDS_HTTP_AUTH_REQUIRED      0xF2D4
#define __IDS_HTTP_FORBIDDEN          0xF2D5
#define __IDS_HTTP_NOT_FOUND          0xF2D6
#define __IDS_HTTP_SERVER_ERROR       0xF2D7
#define __IDS_HTTP_NOT_IMPLEMENTED    0xF2D8

/////////////////////////////////////////////////////////////////////////////
// Strings for Accessibility support for CCheckListBox
#define __IDS_CHECKLISTBOX_UNCHECK	0xF2E1
#define __IDS_CHECKLISTBOX_CHECK		0xF2E2
#define __IDS_CHECKLISTBOX_MIXED		0xF2E3

/////////////////////////////////////////////////////////////////////////////
// AFX implementation - control IDs (__IDC)

// Parts of dialogs
#define __IDC_LISTBOX                 100
#define __IDC_CHANGE                  101
#define __IDC_BROWSER             102

// for print dialog
#define __IDC_PRINT_DOCNAME           201
#define __IDC_PRINT_PRINTERNAME       202
#define __IDC_PRINT_PORTNAME          203
#define __IDC_PRINT_PAGENUM           204

// property Sheet control id's (determined with Spy++)
#define ID_APPLY_NOW                    0x3021
#define ID_WIZBACK                      0x3023
#define ID_WIZNEXT                      0x3024
#define ID_WIZFINISH                    0x3025
#define __IDC_TAB_CONTROL             0x3020

/////////////////////////////////////////////////////////////////////////////
// IDRs for standard components

#ifndef RC_INVOKED  // code only
// These are really COMMDLG dialogs, so there usually isn't a resource
// for them, but these IDs are used as help IDs.
#define __IDD_FILEOPEN                28676
#define __IDD_FILESAVE                28677
#define __IDD_FONT                    28678
#define __IDD_COLOR                   28679
#define __IDD_PRINT                   28680
#define __IDD_PRINTSETUP              28681
#define __IDD_FIND                    28682
#define __IDD_REPLACE                 28683
#endif //!RC_INVOKED

// Standard dialogs cast should leave alone (0x7801->)
#define __IDD_NEWTYPEDLG              30721
#define __IDD_PRINTDLG                30722
#define __IDD_PREVIEW_TOOLBAR         30723

// Dialogs defined for OLE2UI library
#define __IDD_INSERTOBJECT            30724
#define __IDD_CHANGEICON              30725
#define __IDD_CONVERT                 30726
#define __IDD_PASTESPECIAL            30727
#define __IDD_EDITLINKS               30728
#define __IDD_FILEBROWSE              30729
#define __IDD_BUSY                    30730

#define __IDD_OBJECTPROPERTIES        30732
#define __IDD_CHANGESOURCE            30733

//WinForms
#define __IDD_EMPTYDIALOG				30734

// Standard cursors (0x7901->)
   // __IDC = Cursor resources
#define __IDC_CONTEXTHELP             30977       // context sensitive help
#define __IDC_MAGNIFY                 30978       // print preview zoom
#define __IDC_SMALLARROWS             30979       // splitter
#define __IDC_HSPLITBAR               30980       // splitter
#define __IDC_VSPLITBAR               30981       // splitter
#define __IDC_NODROPCRSR              30982       // No Drop Cursor
#define __IDC_TRACKNWSE               30983       // tracker
#define __IDC_TRACKNESW               30984       // tracker
#define __IDC_TRACKNS                 30985       // tracker
#define __IDC_TRACKWE                 30986       // tracker
#define __IDC_TRACK4WAY               30987       // tracker
#define __IDC_MOVE4WAY                30988       // resize bar (server only)

// Wheel mouse cursors
// NOTE: values must be in this order!  See CScrollView::OnTimer()
#define __IDC_MOUSE_PAN_NW            30998       // pan east
#define __IDC_MOUSE_PAN_N             30999       // pan northeast
#define __IDC_MOUSE_PAN_NE            31000       // pan north
#define __IDC_MOUSE_PAN_W             31001       // pan northwest
#define __IDC_MOUSE_PAN_HV            31002       // pan both axis
#define __IDC_MOUSE_PAN_E             31003       // pan west
#define __IDC_MOUSE_PAN_SW            31004       // pan south-west
#define __IDC_MOUSE_PAN_S             31005       // pan south
#define __IDC_MOUSE_PAN_SE            31006       // pan south-east
#define __IDC_MOUSE_PAN_HORZ          31007       // pan X-axis
#define __IDC_MOUSE_PAN_VERT          31008       // pan Y-axis

// Wheel mouse bitmaps
#define __IDC_MOUSE_ORG_HORZ          31009       // anchor for horz only
#define __IDC_MOUSE_ORG_VERT          31010       // anchor for vert only
#define __IDC_MOUSE_ORG_HV            31011       // anchor for horz/vert
#define __IDC_MOUSE_MASK              31012

// Mini frame ::ca::window bitmap ID
#define __IDB_MINIFRAME_MENU          30994

// CheckListBox checks bitmap ID
#define __IDB_CHECKLISTBOX_95         30996

// AFX standard accelerator resources
#define __IDR_PREVIEW_ACCEL           30997

// AFX standard ICON IDs (for ca2 API V1 apps) (0x7A01->)
#define __IDI_STD_MDIFRAME            31233
#define __IDI_STD_FRAME               31234

/////////////////////////////////////////////////////////////////////////////
// AFX OLE control implementation - control IDs (__IDC)

// font property page
#define __IDC_FONTPROP                1000
#define __IDC_FONTNAMES               1001
#define __IDC_FONTSTYLES              1002
#define __IDC_FONTSIZES               1003
#define __IDC_STRIKEOUT               1004
#define __IDC_UNDERLINE               1005
#define __IDC_SAMPLEBOX               1006

// color property page
#define __IDC_COLOR_BLACK             1100
#define __IDC_COLOR_WHITE             1101
#define __IDC_COLOR_RED               1102
#define __IDC_COLOR_GREEN             1103
#define __IDC_COLOR_BLUE              1104
#define __IDC_COLOR_YELLOW            1105
#define __IDC_COLOR_MAGENTA           1106
#define __IDC_COLOR_CYAN              1107
#define __IDC_COLOR_GRAY              1108
#define __IDC_COLOR_LIGHTGRAY         1109
#define __IDC_COLOR_DARKRED           1110
#define __IDC_COLOR_DARKGREEN         1111
#define __IDC_COLOR_DARKBLUE          1112
#define __IDC_COLOR_LIGHTBROWN        1113
#define __IDC_COLOR_DARKMAGENTA       1114
#define __IDC_COLOR_DARKCYAN          1115
#define __IDC_COLORPROP               1116
#define __IDC_SYSTEMCOLORS            1117

// Picture porperty page
#define __IDC_PROPNAME                1201
#define __IDC_PICTURE                 1202
#define __IDC_BROWSE                  1203
#define __IDC_CLEAR                   1204

/////////////////////////////////////////////////////////////////////////////
// IDRs for OLE control standard components

// Standard propery page dialogs cast should leave alone (0x7E01->)
#define __IDD_PROPPAGE_COLOR         32257
#define __IDD_PROPPAGE_FONT          32258
#define __IDD_PROPPAGE_PICTURE       32259

#define __IDB_TRUETYPE               32384

/////////////////////////////////////////////////////////////////////////////
// Standard OLE control strings

// OLE control page strings
#define __IDS_PROPPAGE_UNKNOWN        0xFE01
#define __IDS_COLOR_DESKTOP           0xFE04
#define __IDS_COLOR_APPWORKSPACE      0xFE05
#define __IDS_COLOR_WNDBACKGND        0xFE06
#define __IDS_COLOR_WNDTEXT           0xFE07
#define __IDS_COLOR_MENUBAR           0xFE08
#define __IDS_COLOR_MENUTEXT          0xFE09
#define __IDS_COLOR_ACTIVEBAR         0xFE0A
#define __IDS_COLOR_INACTIVEBAR       0xFE0B
#define __IDS_COLOR_ACTIVETEXT        0xFE0C
#define __IDS_COLOR_INACTIVETEXT      0xFE0D
#define __IDS_COLOR_ACTIVEBORDER      0xFE0E
#define __IDS_COLOR_INACTIVEBORDER    0xFE0F
#define __IDS_COLOR_WNDFRAME          0xFE10
#define __IDS_COLOR_SCROLLBARS        0xFE11
#define __IDS_COLOR_BTNFACE           0xFE12
#define __IDS_COLOR_BTNSHADOW         0xFE13
#define __IDS_COLOR_BTNTEXT           0xFE14
#define __IDS_COLOR_BTNHIGHLIGHT      0xFE15
#define __IDS_COLOR_DISABLEDTEXT      0xFE16
#define __IDS_COLOR_HIGHLIGHT         0xFE17
#define __IDS_COLOR_HIGHLIGHTTEXT     0xFE18
#define __IDS_REGULAR                 0xFE19
#define __IDS_BOLD                    0xFE1A
#define __IDS_ITALIC                  0xFE1B
#define __IDS_BOLDITALIC              0xFE1C
#define __IDS_SAMPLETEXT              0xFE1D
#define __IDS_DISPLAYSTRING_FONT      0xFE1E
#define __IDS_DISPLAYSTRING_COLOR     0xFE1F
#define __IDS_DISPLAYSTRING_PICTURE   0xFE20
#define __IDS_PICTUREFILTER           0xFE21
#define __IDS_PICTYPE_UNKNOWN         0xFE22
#define __IDS_PICTYPE_NONE            0xFE23
#define __IDS_PICTYPE_BITMAP          0xFE24
#define __IDS_PICTYPE_METAFILE        0xFE25
#define __IDS_PICTYPE_ICON            0xFE26
#define __IDS_COLOR_PPG               0xFE28
#define __IDS_COLOR_PPG_CAPTION       0xFE29
#define __IDS_FONT_PPG                0xFE2A
#define __IDS_FONT_PPG_CAPTION        0xFE2B
#define __IDS_PICTURE_PPG             0xFE2C
#define __IDS_PICTURE_PPG_CAPTION     0xFE2D
#define __IDS_PICTUREBROWSETITLE      0xFE30
#define __IDS_BORDERSTYLE_0           0xFE31
#define __IDS_BORDERSTYLE_1           0xFE32

// OLE control verb names
#define __IDS_VERB_EDIT               0xFE40
#define __IDS_VERB_PROPERTIES         0xFE41

// OLE control internal error messages
#define __IDP_PICTURECANTOPEN         0xFE83
#define __IDP_PICTURECANTLOAD         0xFE84
#define __IDP_PICTURETOOLARGE         0xFE85
#define __IDP_PICTUREREADFAILED       0xFE86

// Standard OLE control error strings

#define __IDP_E_ILLEGALFUNCTIONCALL       0xFEA0
#define __IDP_E_OVERFLOW                  0xFEA1
#define __IDP_E_OUTOFMEMORY               0xFEA2
#define __IDP_E_DIVISIONBYZERO            0xFEA3
#define __IDP_E_OUTOFSTRINGSPACE          0xFEA4
#define __IDP_E_OUTOFSTACKSPACE           0xFEA5
#define __IDP_E_BADFILENAMEORNUMBER       0xFEA6
#define __IDP_E_FILENOTFOUND              0xFEA7
#define __IDP_E_BADFILEMODE               0xFEA8
#define __IDP_E_FILEALREADYOPEN           0xFEA9
#define __IDP_E_DEVICEIOERROR             0xFEAA
#define __IDP_E_FILEALREADYEXISTS         0xFEAB
#define __IDP_E_BADRECORDLENGTH           0xFEAC
#define __IDP_E_DISKFULL                  0xFEAD
#define __IDP_E_BADRECORDNUMBER           0xFEAE
#define __IDP_E_BADFILENAME               0xFEAF
#define __IDP_E_TOOMANYFILES              0xFEB0
#define __IDP_E_DEVICEUNAVAILABLE         0xFEB1
#define __IDP_E_PERMISSIONDENIED          0xFEB2
#define __IDP_E_DISKNOTREADY              0xFEB3
#define __IDP_E_PATHFILEACCESSERROR       0xFEB4
#define __IDP_E_PATHNOTFOUND              0xFEB5
#define __IDP_E_INVALIDPATTERNSTRING      0xFEB6
#define __IDP_E_INVALIDUSEOFNULL          0xFEB7
#define __IDP_E_INVALIDFILEFORMAT         0xFEB8
#define __IDP_E_INVALIDPROPERTYVALUE      0xFEB9
#define __IDP_E_INVALIDPROPERTYARRAYINDEX 0xFEBA
#define __IDP_E_SETNOTSUPPORTEDATRUNTIME  0xFEBB
#define __IDP_E_SETNOTSUPPORTED           0xFEBC
#define __IDP_E_NEEDPROPERTYARRAYINDEX    0xFEBD
#define __IDP_E_SETNOTPERMITTED           0xFEBE
#define __IDP_E_GETNOTSUPPORTEDATRUNTIME  0xFEBF
#define __IDP_E_GETNOTSUPPORTED           0xFEC0
#define __IDP_E_PROPERTYNOTFOUND          0xFEC1
#define __IDP_E_INVALIDCLIPBOARDFORMAT    0xFEC2
#define __IDP_E_INVALIDPICTURE            0xFEC3
#define __IDP_E_PRINTERERROR              0xFEC4
#define __IDP_E_CANTSAVEFILETOTEMP        0xFEC5
#define __IDP_E_SEARCHTEXTNOTFOUND        0xFEC6
#define __IDP_E_REPLACEMENTSTOOLONG       0xFEC7

*/


#endif //__AFXRES_H__

