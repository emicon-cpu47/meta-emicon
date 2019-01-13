Не забываем вручную добавлять в м4 интерфейсы:

...
DEF_ITF_API(`uint32_t',`CDECL',`CmpEmiconLCD_puts',`(uint8_t n, uint8_t line, uint8_t pos, char *str)')

DEF_ITF_API(`uint32_t',`CDECL',`CmpEmiconLCD_display_screen',`(uint8_t n)')
#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/

