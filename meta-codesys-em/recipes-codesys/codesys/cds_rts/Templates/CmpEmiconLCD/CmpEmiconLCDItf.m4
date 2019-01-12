/**
 * <interfacename>CmpEmiconLCD</interfacename>
 * <description></description>
 *
 * <copyright></copyright>
 */

SET_INTERFACE_NAME(`CmpEmiconLCD')

/** EXTERN LIB SECTION BEGIN **/
/*  Comments are ignored for m4 compiler so restructured text can be used. changecom(`/*', `*/') */

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

DEF_API(`void',`CDECL',`display_screen',`(display_screen_struct *p)',1,0x46B0648F,0x03050D02)

/**
 *
 * * Возвращает номер отображаемого экрана на LCD.
 * 
 */
typedef struct tagget_current_screen_struct
{
	RTS_IEC_USINT get_current_screen;	/* VAR_OUTPUT */	
} get_current_screen_struct;

DEF_API(`void',`CDECL',`get_current_screen',`(get_current_screen_struct *p)',1,0xB05F91C6,0x03050D02)

/**
 *
 * * Возвращает номер экрана по умолчанию.
 * 
 */
typedef struct tagget_default_screen_struct
{
	RTS_IEC_USINT get_default_screen;	/* VAR_OUTPUT */	
} get_default_screen_struct;

DEF_API(`void',`CDECL',`get_default_screen',`(get_default_screen_struct *p)',1,0xBC400E09,0x03050D02)

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

DEF_API(`void',`CDECL',`lcd_puts',`(lcd_puts_struct *p)',1,0xA74BD7B7,0x03050D02)

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

DEF_API(`void',`CDECL',`menu_item_create',`(menu_item_create_struct *p)',1,0x4B583CD3,0x03050D02)

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

DEF_API(`void',`CDECL',`set_default_screen',`(set_default_screen_struct *p)',1,0x99CC3DB4,0x03050D02)

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

DEF_API(`void',`CDECL',`set_visibility',`(set_visibility_struct *p)',1,0x0FD7B385,0x03050D02)

DEF_ITF_API(`uint32_t',`CDECL',`CmpEmiconLCD_puts',`(uint8_t n, uint8_t line, uint8_t pos, char *str)')

DEF_ITF_API(`uint32_t',`CDECL',`CmpEmiconLCD_display_screen',`(uint8_t n)')
#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/

