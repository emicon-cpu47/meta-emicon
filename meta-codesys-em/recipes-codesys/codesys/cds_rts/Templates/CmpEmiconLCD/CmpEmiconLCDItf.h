 /**
 * <interfacename>CmpEmiconLCD</interfacename>
 * <description></description>
 *
 * <copyright></copyright>
 */


	
	
#ifndef _CMPEMICONLCDITF_H_
#define _CMPEMICONLCDITF_H_

#include "CmpStd.h"

 

 




/** EXTERN LIB SECTION BEGIN **/
/*  Comments are ignored for m4 compiler so restructured text can be used.  */

#ifdef __cplusplus
extern "C" {
#endif

/**
 *
 * * Выводит на LCD экран с заданным номером.
 * 
 */
typedef struct tagdisplay_screen_struct
{
	RTS_IEC_USINT n;					/* VAR_INPUT */	/* номер экрана */
	RTS_IEC_INT display_screen;			/* VAR_OUTPUT */	
} display_screen_struct;

void CDECL CDECL_EXT display_screen(display_screen_struct *p);
typedef void (CDECL CDECL_EXT* PFDISPLAY_SCREEN_IEC) (display_screen_struct *p);
#if defined(CMPEMICONLCD_NOTIMPLEMENTED) || defined(DISPLAY_SCREEN_NOTIMPLEMENTED)
	#define USE_display_screen
	#define EXT_display_screen
	#define GET_display_screen(fl)  ERR_NOTIMPLEMENTED
	#define CAL_display_screen(p0) 
	#define CHK_display_screen  FALSE
	#define EXP_display_screen  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_display_screen
	#define EXT_display_screen
	#define GET_display_screen(fl)  CAL_CMGETAPI( "display_screen" ) 
	#define CAL_display_screen  display_screen
	#define CHK_display_screen  TRUE
	#define EXP_display_screen  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"display_screen", (RTS_UINTPTR)display_screen, 1, 0x46B0648F, 0x03050D02) 
#elif defined(MIXED_LINK) && !defined(CMPEMICONLCD_EXTERNAL)
	#define USE_display_screen
	#define EXT_display_screen
	#define GET_display_screen(fl)  CAL_CMGETAPI( "display_screen" ) 
	#define CAL_display_screen  display_screen
	#define CHK_display_screen  TRUE
	#define EXP_display_screen  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"display_screen", (RTS_UINTPTR)display_screen, 1, 0x46B0648F, 0x03050D02) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpEmiconLCDdisplay_screen
	#define EXT_CmpEmiconLCDdisplay_screen
	#define GET_CmpEmiconLCDdisplay_screen  ERR_OK
	#define CAL_CmpEmiconLCDdisplay_screen  display_screen
	#define CHK_CmpEmiconLCDdisplay_screen  TRUE
	#define EXP_CmpEmiconLCDdisplay_screen  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"display_screen", (RTS_UINTPTR)display_screen, 1, 0x46B0648F, 0x03050D02) 
#elif defined(CPLUSPLUS)
	#define USE_display_screen
	#define EXT_display_screen
	#define GET_display_screen(fl)  CAL_CMGETAPI( "display_screen" ) 
	#define CAL_display_screen  display_screen
	#define CHK_display_screen  TRUE
	#define EXP_display_screen  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"display_screen", (RTS_UINTPTR)display_screen, 1, 0x46B0648F, 0x03050D02) 
#else /* DYNAMIC_LINK */
	#define USE_display_screen  PFDISPLAY_SCREEN_IEC pfdisplay_screen;
	#define EXT_display_screen  extern PFDISPLAY_SCREEN_IEC pfdisplay_screen;
	#define GET_display_screen(fl)  s_pfCMGetAPI2( "display_screen", (RTS_VOID_FCTPTR *)&pfdisplay_screen, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x46B0648F, 0x03050D02)
	#define CAL_display_screen  pfdisplay_screen
	#define CHK_display_screen  (pfdisplay_screen != NULL)
	#define EXP_display_screen   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"display_screen", (RTS_UINTPTR)display_screen, 1, 0x46B0648F, 0x03050D02) 
#endif


/**
 *
 * * Возвращает номер отображаемого экрана на LCD.
 * 
 */
typedef struct tagget_current_screen_struct
{
	RTS_IEC_USINT get_current_screen;	/* VAR_OUTPUT */	
} get_current_screen_struct;

void CDECL CDECL_EXT get_current_screen(get_current_screen_struct *p);
typedef void (CDECL CDECL_EXT* PFGET_CURRENT_SCREEN_IEC) (get_current_screen_struct *p);
#if defined(CMPEMICONLCD_NOTIMPLEMENTED) || defined(GET_CURRENT_SCREEN_NOTIMPLEMENTED)
	#define USE_get_current_screen
	#define EXT_get_current_screen
	#define GET_get_current_screen(fl)  ERR_NOTIMPLEMENTED
	#define CAL_get_current_screen(p0) 
	#define CHK_get_current_screen  FALSE
	#define EXP_get_current_screen  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_get_current_screen
	#define EXT_get_current_screen
	#define GET_get_current_screen(fl)  CAL_CMGETAPI( "get_current_screen" ) 
	#define CAL_get_current_screen  get_current_screen
	#define CHK_get_current_screen  TRUE
	#define EXP_get_current_screen  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"get_current_screen", (RTS_UINTPTR)get_current_screen, 1, 0xB05F91C6, 0x03050D02) 
#elif defined(MIXED_LINK) && !defined(CMPEMICONLCD_EXTERNAL)
	#define USE_get_current_screen
	#define EXT_get_current_screen
	#define GET_get_current_screen(fl)  CAL_CMGETAPI( "get_current_screen" ) 
	#define CAL_get_current_screen  get_current_screen
	#define CHK_get_current_screen  TRUE
	#define EXP_get_current_screen  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"get_current_screen", (RTS_UINTPTR)get_current_screen, 1, 0xB05F91C6, 0x03050D02) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpEmiconLCDget_current_screen
	#define EXT_CmpEmiconLCDget_current_screen
	#define GET_CmpEmiconLCDget_current_screen  ERR_OK
	#define CAL_CmpEmiconLCDget_current_screen  get_current_screen
	#define CHK_CmpEmiconLCDget_current_screen  TRUE
	#define EXP_CmpEmiconLCDget_current_screen  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"get_current_screen", (RTS_UINTPTR)get_current_screen, 1, 0xB05F91C6, 0x03050D02) 
#elif defined(CPLUSPLUS)
	#define USE_get_current_screen
	#define EXT_get_current_screen
	#define GET_get_current_screen(fl)  CAL_CMGETAPI( "get_current_screen" ) 
	#define CAL_get_current_screen  get_current_screen
	#define CHK_get_current_screen  TRUE
	#define EXP_get_current_screen  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"get_current_screen", (RTS_UINTPTR)get_current_screen, 1, 0xB05F91C6, 0x03050D02) 
#else /* DYNAMIC_LINK */
	#define USE_get_current_screen  PFGET_CURRENT_SCREEN_IEC pfget_current_screen;
	#define EXT_get_current_screen  extern PFGET_CURRENT_SCREEN_IEC pfget_current_screen;
	#define GET_get_current_screen(fl)  s_pfCMGetAPI2( "get_current_screen", (RTS_VOID_FCTPTR *)&pfget_current_screen, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xB05F91C6, 0x03050D02)
	#define CAL_get_current_screen  pfget_current_screen
	#define CHK_get_current_screen  (pfget_current_screen != NULL)
	#define EXP_get_current_screen   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"get_current_screen", (RTS_UINTPTR)get_current_screen, 1, 0xB05F91C6, 0x03050D02) 
#endif


/**
 *
 * * Возвращает номер экрана по умолчанию.
 * 
 */
typedef struct tagget_default_screen_struct
{
	RTS_IEC_USINT get_default_screen;	/* VAR_OUTPUT */	
} get_default_screen_struct;

void CDECL CDECL_EXT get_default_screen(get_default_screen_struct *p);
typedef void (CDECL CDECL_EXT* PFGET_DEFAULT_SCREEN_IEC) (get_default_screen_struct *p);
#if defined(CMPEMICONLCD_NOTIMPLEMENTED) || defined(GET_DEFAULT_SCREEN_NOTIMPLEMENTED)
	#define USE_get_default_screen
	#define EXT_get_default_screen
	#define GET_get_default_screen(fl)  ERR_NOTIMPLEMENTED
	#define CAL_get_default_screen(p0) 
	#define CHK_get_default_screen  FALSE
	#define EXP_get_default_screen  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_get_default_screen
	#define EXT_get_default_screen
	#define GET_get_default_screen(fl)  CAL_CMGETAPI( "get_default_screen" ) 
	#define CAL_get_default_screen  get_default_screen
	#define CHK_get_default_screen  TRUE
	#define EXP_get_default_screen  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"get_default_screen", (RTS_UINTPTR)get_default_screen, 1, 0xBC400E09, 0x03050D02) 
#elif defined(MIXED_LINK) && !defined(CMPEMICONLCD_EXTERNAL)
	#define USE_get_default_screen
	#define EXT_get_default_screen
	#define GET_get_default_screen(fl)  CAL_CMGETAPI( "get_default_screen" ) 
	#define CAL_get_default_screen  get_default_screen
	#define CHK_get_default_screen  TRUE
	#define EXP_get_default_screen  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"get_default_screen", (RTS_UINTPTR)get_default_screen, 1, 0xBC400E09, 0x03050D02) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpEmiconLCDget_default_screen
	#define EXT_CmpEmiconLCDget_default_screen
	#define GET_CmpEmiconLCDget_default_screen  ERR_OK
	#define CAL_CmpEmiconLCDget_default_screen  get_default_screen
	#define CHK_CmpEmiconLCDget_default_screen  TRUE
	#define EXP_CmpEmiconLCDget_default_screen  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"get_default_screen", (RTS_UINTPTR)get_default_screen, 1, 0xBC400E09, 0x03050D02) 
#elif defined(CPLUSPLUS)
	#define USE_get_default_screen
	#define EXT_get_default_screen
	#define GET_get_default_screen(fl)  CAL_CMGETAPI( "get_default_screen" ) 
	#define CAL_get_default_screen  get_default_screen
	#define CHK_get_default_screen  TRUE
	#define EXP_get_default_screen  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"get_default_screen", (RTS_UINTPTR)get_default_screen, 1, 0xBC400E09, 0x03050D02) 
#else /* DYNAMIC_LINK */
	#define USE_get_default_screen  PFGET_DEFAULT_SCREEN_IEC pfget_default_screen;
	#define EXT_get_default_screen  extern PFGET_DEFAULT_SCREEN_IEC pfget_default_screen;
	#define GET_get_default_screen(fl)  s_pfCMGetAPI2( "get_default_screen", (RTS_VOID_FCTPTR *)&pfget_default_screen, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xBC400E09, 0x03050D02)
	#define CAL_get_default_screen  pfget_default_screen
	#define CHK_get_default_screen  (pfget_default_screen != NULL)
	#define EXP_get_default_screen   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"get_default_screen", (RTS_UINTPTR)get_default_screen, 1, 0xBC400E09, 0x03050D02) 
#endif


/**
 * <description>lcd_puts</description>
 */
typedef struct taglcd_puts_struct
{
	RTS_IEC_USINT usiScreen;			/* VAR_INPUT */	/* номер экрана 0-9 */
	RTS_IEC_USINT iLine;				/* VAR_INPUT */	/* Строка 0-1 */
	RTS_IEC_USINT iPos;					/* VAR_INPUT */	/* Столбец 0-249 */
	RTS_IEC_STRING stData[252];			/* VAR_INPUT */	/* Текст 1-250 сиволов */
	RTS_IEC_INT lcd_puts;				/* VAR_OUTPUT */	
} lcd_puts_struct;

void CDECL CDECL_EXT lcd_puts(lcd_puts_struct *p);
typedef void (CDECL CDECL_EXT* PFLCD_PUTS_IEC) (lcd_puts_struct *p);
#if defined(CMPEMICONLCD_NOTIMPLEMENTED) || defined(LCD_PUTS_NOTIMPLEMENTED)
	#define USE_lcd_puts
	#define EXT_lcd_puts
	#define GET_lcd_puts(fl)  ERR_NOTIMPLEMENTED
	#define CAL_lcd_puts(p0) 
	#define CHK_lcd_puts  FALSE
	#define EXP_lcd_puts  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_lcd_puts
	#define EXT_lcd_puts
	#define GET_lcd_puts(fl)  CAL_CMGETAPI( "lcd_puts" ) 
	#define CAL_lcd_puts  lcd_puts
	#define CHK_lcd_puts  TRUE
	#define EXP_lcd_puts  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"lcd_puts", (RTS_UINTPTR)lcd_puts, 1, 0xA74BD7B7, 0x03050D02) 
#elif defined(MIXED_LINK) && !defined(CMPEMICONLCD_EXTERNAL)
	#define USE_lcd_puts
	#define EXT_lcd_puts
	#define GET_lcd_puts(fl)  CAL_CMGETAPI( "lcd_puts" ) 
	#define CAL_lcd_puts  lcd_puts
	#define CHK_lcd_puts  TRUE
	#define EXP_lcd_puts  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"lcd_puts", (RTS_UINTPTR)lcd_puts, 1, 0xA74BD7B7, 0x03050D02) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpEmiconLCDlcd_puts
	#define EXT_CmpEmiconLCDlcd_puts
	#define GET_CmpEmiconLCDlcd_puts  ERR_OK
	#define CAL_CmpEmiconLCDlcd_puts  lcd_puts
	#define CHK_CmpEmiconLCDlcd_puts  TRUE
	#define EXP_CmpEmiconLCDlcd_puts  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"lcd_puts", (RTS_UINTPTR)lcd_puts, 1, 0xA74BD7B7, 0x03050D02) 
#elif defined(CPLUSPLUS)
	#define USE_lcd_puts
	#define EXT_lcd_puts
	#define GET_lcd_puts(fl)  CAL_CMGETAPI( "lcd_puts" ) 
	#define CAL_lcd_puts  lcd_puts
	#define CHK_lcd_puts  TRUE
	#define EXP_lcd_puts  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"lcd_puts", (RTS_UINTPTR)lcd_puts, 1, 0xA74BD7B7, 0x03050D02) 
#else /* DYNAMIC_LINK */
	#define USE_lcd_puts  PFLCD_PUTS_IEC pflcd_puts;
	#define EXT_lcd_puts  extern PFLCD_PUTS_IEC pflcd_puts;
	#define GET_lcd_puts(fl)  s_pfCMGetAPI2( "lcd_puts", (RTS_VOID_FCTPTR *)&pflcd_puts, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xA74BD7B7, 0x03050D02)
	#define CAL_lcd_puts  pflcd_puts
	#define CHK_lcd_puts  (pflcd_puts != NULL)
	#define EXP_lcd_puts   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"lcd_puts", (RTS_UINTPTR)lcd_puts, 1, 0xA74BD7B7, 0x03050D02) 
#endif


/**
 * <description>menu_item_create</description>
 */
typedef struct tagmenu_item_create_struct
{
	RTS_IEC_USINT screen;				/* VAR_INPUT */	/* номер экрана меню 0-9 */
	RTS_IEC_STRING st_line1[252];		/* VAR_INPUT */	/* Текст 1-250 сиволов */
	RTS_IEC_STRING st_line2[252];		/* VAR_INPUT */	/* Текст 1-250 сиволов */
	RTS_IEC_BYTE *p_menu_function;		/* VAR_INPUT */	/* указатель на функцию */
	RTS_IEC_UDINT menu_item_create;		/* VAR_OUTPUT */	
} menu_item_create_struct;

void CDECL CDECL_EXT menu_item_create(menu_item_create_struct *p);
typedef void (CDECL CDECL_EXT* PFMENU_ITEM_CREATE_IEC) (menu_item_create_struct *p);
#if defined(CMPEMICONLCD_NOTIMPLEMENTED) || defined(MENU_ITEM_CREATE_NOTIMPLEMENTED)
	#define USE_menu_item_create
	#define EXT_menu_item_create
	#define GET_menu_item_create(fl)  ERR_NOTIMPLEMENTED
	#define CAL_menu_item_create(p0) 
	#define CHK_menu_item_create  FALSE
	#define EXP_menu_item_create  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_menu_item_create
	#define EXT_menu_item_create
	#define GET_menu_item_create(fl)  CAL_CMGETAPI( "menu_item_create" ) 
	#define CAL_menu_item_create  menu_item_create
	#define CHK_menu_item_create  TRUE
	#define EXP_menu_item_create  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"menu_item_create", (RTS_UINTPTR)menu_item_create, 1, 0x4B583CD3, 0x03050D02) 
#elif defined(MIXED_LINK) && !defined(CMPEMICONLCD_EXTERNAL)
	#define USE_menu_item_create
	#define EXT_menu_item_create
	#define GET_menu_item_create(fl)  CAL_CMGETAPI( "menu_item_create" ) 
	#define CAL_menu_item_create  menu_item_create
	#define CHK_menu_item_create  TRUE
	#define EXP_menu_item_create  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"menu_item_create", (RTS_UINTPTR)menu_item_create, 1, 0x4B583CD3, 0x03050D02) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpEmiconLCDmenu_item_create
	#define EXT_CmpEmiconLCDmenu_item_create
	#define GET_CmpEmiconLCDmenu_item_create  ERR_OK
	#define CAL_CmpEmiconLCDmenu_item_create  menu_item_create
	#define CHK_CmpEmiconLCDmenu_item_create  TRUE
	#define EXP_CmpEmiconLCDmenu_item_create  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"menu_item_create", (RTS_UINTPTR)menu_item_create, 1, 0x4B583CD3, 0x03050D02) 
#elif defined(CPLUSPLUS)
	#define USE_menu_item_create
	#define EXT_menu_item_create
	#define GET_menu_item_create(fl)  CAL_CMGETAPI( "menu_item_create" ) 
	#define CAL_menu_item_create  menu_item_create
	#define CHK_menu_item_create  TRUE
	#define EXP_menu_item_create  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"menu_item_create", (RTS_UINTPTR)menu_item_create, 1, 0x4B583CD3, 0x03050D02) 
#else /* DYNAMIC_LINK */
	#define USE_menu_item_create  PFMENU_ITEM_CREATE_IEC pfmenu_item_create;
	#define EXT_menu_item_create  extern PFMENU_ITEM_CREATE_IEC pfmenu_item_create;
	#define GET_menu_item_create(fl)  s_pfCMGetAPI2( "menu_item_create", (RTS_VOID_FCTPTR *)&pfmenu_item_create, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x4B583CD3, 0x03050D02)
	#define CAL_menu_item_create  pfmenu_item_create
	#define CHK_menu_item_create  (pfmenu_item_create != NULL)
	#define EXP_menu_item_create   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"menu_item_create", (RTS_UINTPTR)menu_item_create, 1, 0x4B583CD3, 0x03050D02) 
#endif


/**
 *
 * * Устанавливает эран по умолчанию.
 * 
 */
typedef struct tagset_default_screen_struct
{
	RTS_IEC_USINT n;					/* VAR_INPUT */	/* номер экрана */
	RTS_IEC_USINT set_default_screen;	/* VAR_OUTPUT */	
} set_default_screen_struct;

void CDECL CDECL_EXT set_default_screen(set_default_screen_struct *p);
typedef void (CDECL CDECL_EXT* PFSET_DEFAULT_SCREEN_IEC) (set_default_screen_struct *p);
#if defined(CMPEMICONLCD_NOTIMPLEMENTED) || defined(SET_DEFAULT_SCREEN_NOTIMPLEMENTED)
	#define USE_set_default_screen
	#define EXT_set_default_screen
	#define GET_set_default_screen(fl)  ERR_NOTIMPLEMENTED
	#define CAL_set_default_screen(p0) 
	#define CHK_set_default_screen  FALSE
	#define EXP_set_default_screen  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_set_default_screen
	#define EXT_set_default_screen
	#define GET_set_default_screen(fl)  CAL_CMGETAPI( "set_default_screen" ) 
	#define CAL_set_default_screen  set_default_screen
	#define CHK_set_default_screen  TRUE
	#define EXP_set_default_screen  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"set_default_screen", (RTS_UINTPTR)set_default_screen, 1, 0x99CC3DB4, 0x03050D02) 
#elif defined(MIXED_LINK) && !defined(CMPEMICONLCD_EXTERNAL)
	#define USE_set_default_screen
	#define EXT_set_default_screen
	#define GET_set_default_screen(fl)  CAL_CMGETAPI( "set_default_screen" ) 
	#define CAL_set_default_screen  set_default_screen
	#define CHK_set_default_screen  TRUE
	#define EXP_set_default_screen  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"set_default_screen", (RTS_UINTPTR)set_default_screen, 1, 0x99CC3DB4, 0x03050D02) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpEmiconLCDset_default_screen
	#define EXT_CmpEmiconLCDset_default_screen
	#define GET_CmpEmiconLCDset_default_screen  ERR_OK
	#define CAL_CmpEmiconLCDset_default_screen  set_default_screen
	#define CHK_CmpEmiconLCDset_default_screen  TRUE
	#define EXP_CmpEmiconLCDset_default_screen  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"set_default_screen", (RTS_UINTPTR)set_default_screen, 1, 0x99CC3DB4, 0x03050D02) 
#elif defined(CPLUSPLUS)
	#define USE_set_default_screen
	#define EXT_set_default_screen
	#define GET_set_default_screen(fl)  CAL_CMGETAPI( "set_default_screen" ) 
	#define CAL_set_default_screen  set_default_screen
	#define CHK_set_default_screen  TRUE
	#define EXP_set_default_screen  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"set_default_screen", (RTS_UINTPTR)set_default_screen, 1, 0x99CC3DB4, 0x03050D02) 
#else /* DYNAMIC_LINK */
	#define USE_set_default_screen  PFSET_DEFAULT_SCREEN_IEC pfset_default_screen;
	#define EXT_set_default_screen  extern PFSET_DEFAULT_SCREEN_IEC pfset_default_screen;
	#define GET_set_default_screen(fl)  s_pfCMGetAPI2( "set_default_screen", (RTS_VOID_FCTPTR *)&pfset_default_screen, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x99CC3DB4, 0x03050D02)
	#define CAL_set_default_screen  pfset_default_screen
	#define CHK_set_default_screen  (pfset_default_screen != NULL)
	#define EXP_set_default_screen   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"set_default_screen", (RTS_UINTPTR)set_default_screen, 1, 0x99CC3DB4, 0x03050D02) 
#endif


/**
 *
 * * Установка видимости экрана.
 * 
 */
typedef struct tagset_visibility_struct
{
	RTS_IEC_USINT n;					/* VAR_INPUT */	/* номер экрана */
	RTS_IEC_BOOL visibility;			/* VAR_INPUT */	
	RTS_IEC_INT set_visibility;			/* VAR_OUTPUT */	
} set_visibility_struct;

void CDECL CDECL_EXT set_visibility(set_visibility_struct *p);
typedef void (CDECL CDECL_EXT* PFSET_VISIBILITY_IEC) (set_visibility_struct *p);
#if defined(CMPEMICONLCD_NOTIMPLEMENTED) || defined(SET_VISIBILITY_NOTIMPLEMENTED)
	#define USE_set_visibility
	#define EXT_set_visibility
	#define GET_set_visibility(fl)  ERR_NOTIMPLEMENTED
	#define CAL_set_visibility(p0) 
	#define CHK_set_visibility  FALSE
	#define EXP_set_visibility  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_set_visibility
	#define EXT_set_visibility
	#define GET_set_visibility(fl)  CAL_CMGETAPI( "set_visibility" ) 
	#define CAL_set_visibility  set_visibility
	#define CHK_set_visibility  TRUE
	#define EXP_set_visibility  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"set_visibility", (RTS_UINTPTR)set_visibility, 1, 0x0FD7B385, 0x03050D02) 
#elif defined(MIXED_LINK) && !defined(CMPEMICONLCD_EXTERNAL)
	#define USE_set_visibility
	#define EXT_set_visibility
	#define GET_set_visibility(fl)  CAL_CMGETAPI( "set_visibility" ) 
	#define CAL_set_visibility  set_visibility
	#define CHK_set_visibility  TRUE
	#define EXP_set_visibility  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"set_visibility", (RTS_UINTPTR)set_visibility, 1, 0x0FD7B385, 0x03050D02) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpEmiconLCDset_visibility
	#define EXT_CmpEmiconLCDset_visibility
	#define GET_CmpEmiconLCDset_visibility  ERR_OK
	#define CAL_CmpEmiconLCDset_visibility  set_visibility
	#define CHK_CmpEmiconLCDset_visibility  TRUE
	#define EXP_CmpEmiconLCDset_visibility  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"set_visibility", (RTS_UINTPTR)set_visibility, 1, 0x0FD7B385, 0x03050D02) 
#elif defined(CPLUSPLUS)
	#define USE_set_visibility
	#define EXT_set_visibility
	#define GET_set_visibility(fl)  CAL_CMGETAPI( "set_visibility" ) 
	#define CAL_set_visibility  set_visibility
	#define CHK_set_visibility  TRUE
	#define EXP_set_visibility  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"set_visibility", (RTS_UINTPTR)set_visibility, 1, 0x0FD7B385, 0x03050D02) 
#else /* DYNAMIC_LINK */
	#define USE_set_visibility  PFSET_VISIBILITY_IEC pfset_visibility;
	#define EXT_set_visibility  extern PFSET_VISIBILITY_IEC pfset_visibility;
	#define GET_set_visibility(fl)  s_pfCMGetAPI2( "set_visibility", (RTS_VOID_FCTPTR *)&pfset_visibility, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x0FD7B385, 0x03050D02)
	#define CAL_set_visibility  pfset_visibility
	#define CHK_set_visibility  (pfset_visibility != NULL)
	#define EXP_set_visibility   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"set_visibility", (RTS_UINTPTR)set_visibility, 1, 0x0FD7B385, 0x03050D02) 
#endif


uint32_t CDECL CmpEmiconLCD_puts(uint8_t n, uint8_t line, uint8_t pos, char *str);
typedef uint32_t (CDECL * PFCMPEMICONLCD_PUTS) (uint8_t n, uint8_t line, uint8_t pos, char *str);
#if defined(CMPEMICONLCD_NOTIMPLEMENTED) || defined(CMPEMICONLCD_PUTS_NOTIMPLEMENTED)
	#define USE_CmpEmiconLCD_puts
	#define EXT_CmpEmiconLCD_puts
	#define GET_CmpEmiconLCD_puts(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CmpEmiconLCD_puts(p0,p1,p2,p3)  (uint32_t)ERR_NOTIMPLEMENTED
	#define CHK_CmpEmiconLCD_puts  FALSE
	#define EXP_CmpEmiconLCD_puts  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CmpEmiconLCD_puts
	#define EXT_CmpEmiconLCD_puts
	#define GET_CmpEmiconLCD_puts(fl)  CAL_CMGETAPI( "CmpEmiconLCD_puts" ) 
	#define CAL_CmpEmiconLCD_puts  CmpEmiconLCD_puts
	#define CHK_CmpEmiconLCD_puts  TRUE
	#define EXP_CmpEmiconLCD_puts  CAL_CMEXPAPI( "CmpEmiconLCD_puts" ) 
#elif defined(MIXED_LINK) && !defined(CMPEMICONLCD_EXTERNAL)
	#define USE_CmpEmiconLCD_puts
	#define EXT_CmpEmiconLCD_puts
	#define GET_CmpEmiconLCD_puts(fl)  CAL_CMGETAPI( "CmpEmiconLCD_puts" ) 
	#define CAL_CmpEmiconLCD_puts  CmpEmiconLCD_puts
	#define CHK_CmpEmiconLCD_puts  TRUE
	#define EXP_CmpEmiconLCD_puts  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CmpEmiconLCD_puts", (RTS_UINTPTR)CmpEmiconLCD_puts, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpEmiconLCDCmpEmiconLCD_puts
	#define EXT_CmpEmiconLCDCmpEmiconLCD_puts
	#define GET_CmpEmiconLCDCmpEmiconLCD_puts  ERR_OK
	#define CAL_CmpEmiconLCDCmpEmiconLCD_puts pICmpEmiconLCD->ICmpEmiconLCD_puts
	#define CHK_CmpEmiconLCDCmpEmiconLCD_puts (pICmpEmiconLCD != NULL)
	#define EXP_CmpEmiconLCDCmpEmiconLCD_puts  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CmpEmiconLCD_puts
	#define EXT_CmpEmiconLCD_puts
	#define GET_CmpEmiconLCD_puts(fl)  CAL_CMGETAPI( "CmpEmiconLCD_puts" ) 
	#define CAL_CmpEmiconLCD_puts pICmpEmiconLCD->ICmpEmiconLCD_puts
	#define CHK_CmpEmiconLCD_puts (pICmpEmiconLCD != NULL)
	#define EXP_CmpEmiconLCD_puts  CAL_CMEXPAPI( "CmpEmiconLCD_puts" ) 
#else /* DYNAMIC_LINK */
	#define USE_CmpEmiconLCD_puts  PFCMPEMICONLCD_PUTS pfCmpEmiconLCD_puts;
	#define EXT_CmpEmiconLCD_puts  extern PFCMPEMICONLCD_PUTS pfCmpEmiconLCD_puts;
	#define GET_CmpEmiconLCD_puts(fl)  s_pfCMGetAPI2( "CmpEmiconLCD_puts", (RTS_VOID_FCTPTR *)&pfCmpEmiconLCD_puts, (fl), 0, 0)
	#define CAL_CmpEmiconLCD_puts  pfCmpEmiconLCD_puts
	#define CHK_CmpEmiconLCD_puts  (pfCmpEmiconLCD_puts != NULL)
	#define EXP_CmpEmiconLCD_puts  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CmpEmiconLCD_puts", (RTS_UINTPTR)CmpEmiconLCD_puts, 0, 0) 
#endif




uint32_t CDECL CmpEmiconLCD_display_screen(uint8_t n);
typedef uint32_t (CDECL * PFCMPEMICONLCD_DISPLAY_SCREEN) (uint8_t n);
#if defined(CMPEMICONLCD_NOTIMPLEMENTED) || defined(CMPEMICONLCD_DISPLAY_SCREEN_NOTIMPLEMENTED)
	#define USE_CmpEmiconLCD_display_screen
	#define EXT_CmpEmiconLCD_display_screen
	#define GET_CmpEmiconLCD_display_screen(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CmpEmiconLCD_display_screen(p0)  (uint32_t)ERR_NOTIMPLEMENTED
	#define CHK_CmpEmiconLCD_display_screen  FALSE
	#define EXP_CmpEmiconLCD_display_screen  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CmpEmiconLCD_display_screen
	#define EXT_CmpEmiconLCD_display_screen
	#define GET_CmpEmiconLCD_display_screen(fl)  CAL_CMGETAPI( "CmpEmiconLCD_display_screen" ) 
	#define CAL_CmpEmiconLCD_display_screen  CmpEmiconLCD_display_screen
	#define CHK_CmpEmiconLCD_display_screen  TRUE
	#define EXP_CmpEmiconLCD_display_screen  CAL_CMEXPAPI( "CmpEmiconLCD_display_screen" ) 
#elif defined(MIXED_LINK) && !defined(CMPEMICONLCD_EXTERNAL)
	#define USE_CmpEmiconLCD_display_screen
	#define EXT_CmpEmiconLCD_display_screen
	#define GET_CmpEmiconLCD_display_screen(fl)  CAL_CMGETAPI( "CmpEmiconLCD_display_screen" ) 
	#define CAL_CmpEmiconLCD_display_screen  CmpEmiconLCD_display_screen
	#define CHK_CmpEmiconLCD_display_screen  TRUE
	#define EXP_CmpEmiconLCD_display_screen  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CmpEmiconLCD_display_screen", (RTS_UINTPTR)CmpEmiconLCD_display_screen, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpEmiconLCDCmpEmiconLCD_display_screen
	#define EXT_CmpEmiconLCDCmpEmiconLCD_display_screen
	#define GET_CmpEmiconLCDCmpEmiconLCD_display_screen  ERR_OK
	#define CAL_CmpEmiconLCDCmpEmiconLCD_display_screen pICmpEmiconLCD->ICmpEmiconLCD_display_screen
	#define CHK_CmpEmiconLCDCmpEmiconLCD_display_screen (pICmpEmiconLCD != NULL)
	#define EXP_CmpEmiconLCDCmpEmiconLCD_display_screen  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CmpEmiconLCD_display_screen
	#define EXT_CmpEmiconLCD_display_screen
	#define GET_CmpEmiconLCD_display_screen(fl)  CAL_CMGETAPI( "CmpEmiconLCD_display_screen" ) 
	#define CAL_CmpEmiconLCD_display_screen pICmpEmiconLCD->ICmpEmiconLCD_display_screen
	#define CHK_CmpEmiconLCD_display_screen (pICmpEmiconLCD != NULL)
	#define EXP_CmpEmiconLCD_display_screen  CAL_CMEXPAPI( "CmpEmiconLCD_display_screen" ) 
#else /* DYNAMIC_LINK */
	#define USE_CmpEmiconLCD_display_screen  PFCMPEMICONLCD_DISPLAY_SCREEN pfCmpEmiconLCD_display_screen;
	#define EXT_CmpEmiconLCD_display_screen  extern PFCMPEMICONLCD_DISPLAY_SCREEN pfCmpEmiconLCD_display_screen;
	#define GET_CmpEmiconLCD_display_screen(fl)  s_pfCMGetAPI2( "CmpEmiconLCD_display_screen", (RTS_VOID_FCTPTR *)&pfCmpEmiconLCD_display_screen, (fl), 0, 0)
	#define CAL_CmpEmiconLCD_display_screen  pfCmpEmiconLCD_display_screen
	#define CHK_CmpEmiconLCD_display_screen  (pfCmpEmiconLCD_display_screen != NULL)
	#define EXP_CmpEmiconLCD_display_screen  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CmpEmiconLCD_display_screen", (RTS_UINTPTR)CmpEmiconLCD_display_screen, 0, 0) 
#endif



#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/




typedef struct
{
	IBase_C *pBase;
	PFCMPEMICONLCD_PUTS ICmpEmiconLCD_puts;
 	PFCMPEMICONLCD_DISPLAY_SCREEN ICmpEmiconLCD_display_screen;
 } ICmpEmiconLCD_C;

#ifdef CPLUSPLUS
class ICmpEmiconLCD : public IBase
{
	public:
		virtual uint32_t CDECL ICmpEmiconLCD_puts(uint8_t n, uint8_t line, uint8_t pos, char *str) =0;
		virtual uint32_t CDECL ICmpEmiconLCD_display_screen(uint8_t n) =0;
};
	#ifndef ITF_CmpEmiconLCD
		#define ITF_CmpEmiconLCD static ICmpEmiconLCD *pICmpEmiconLCD = NULL;
	#endif
	#define EXTITF_CmpEmiconLCD
#else	/*CPLUSPLUS*/
	typedef ICmpEmiconLCD_C		ICmpEmiconLCD;
	#ifndef ITF_CmpEmiconLCD
		#define ITF_CmpEmiconLCD
	#endif
	#define EXTITF_CmpEmiconLCD
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPEMICONLCDITF_H_*/
