# C API необходимые реализации
Описание работы скриптов на EdgeTX  
https://luadoc.edgetx.org/2.10/part_i_-_script_type_overview/one-time_scripts


## Специальные символы

https://luadoc.edgetx.org/lua-api-reference/constants/special-character-constants  
`CHAR_UP`  
`CHAR_DOWN`

Как-то связано с CHAR_UP/CHAR_DOWN, но если они определены, то не нужно  
`__opentx`
`__opentx.CHAR_UP`
`__opentx.CHAR_DOWN`


## Виртуальные события

https://luadoc.edgetx.org/2.10/part_iii_-_opentx_lua_api_reference/constants/key_events#virtual-events  
`EVT_VIRTUAL_ENTER`   - Нажатие на колесо  
`EVT_VIRTUAL_EXIT`    - Нажатие RTN  
`EVT_VIRTUAL_NEXT`    - Прокрутка колеса  
`EVT_VIRTUAL_PREV`    - Прокрутка колеса  


## События касания

https://luadoc.edgetx.org/2.10/part_iii_-_opentx_lua_api_reference/constants/touch-event-constants  
`EVT_TOUCH_TAP` - Отрыв пальца после быстрого касания  


## Библиотека для побитовых операций

Своя реализация не нужна !!! Добавлена в Lua 5.2  
`bit32.lshift(result, 8)`                 - Сдвиг влево  
`bit32.rshift(value, 8*i)`                - Сдвиг вправо  
`bit32.band(field.value, bandval)`        - Побитовое AND  
`bit32.btest(fieldData[offset+1], 0x80)`  - Сравнение побитового AND с нулем  


## Отправка данных через телеметрию

https://luadoc.edgetx.org/2.10/part_iii_-_opentx_lua_api_reference/general-functions-less-than-greater-than-luadoc-begin-general/crossfiretelemetrypush

Реализация:  
https://github.com/EdgeTX/edgetx/blob/0f69f1d40977eff77c0cba90cbcc5f75c2874799/radio/src/lua/api_general.cpp#L1191  
`crossfireTelemetryPush(0x2D, { deviceId, handsetId, field.id, field.status })`


## Извлечение пакета телеметрии из очереди

Реализация:  
https://github.com/EdgeTX/edgetx/blob/0f69f1d40977eff77c0cba90cbcc5f75c2874799/radio/src/lua/api_general.cpp#L1149  
`crossfireTelemetryPop()`


## Все, что связано с экраном

`lcd.drawText(LCD_W - 5, barTextSpacing, goodBadPkt, RIGHT + BOLD + CUSTOM_COLOR)`  
`lcd.RGB(0x43, 0x61, 0xAA)`  
`lcd.setColor(CUSTOM_COLOR, EGREEN)` - Только цветные  
`lcd.drawRectangle(0, 0, LCD_W, LCD_H, CUSTOM_COLOR)`  
`lcd.drawFilledRectangle(0, 0, LCD_W, barHeight, CUSTOM_COLOR)`  
`lcd.drawLine(LCD_W - 10, 0, LCD_W - 10, barHeight-1, SOLID, INVERS)`  
`lcd.drawGauge(0, 0, COL2, barHeight, fields_count - #loadQ, fields_count, 0)`  
`lcd.sizeText("Qg")`  
`lcd.clear()` 

`BOLD`  
`LCD_W` - Возможно не нужно  
`LCD_H` - Аналогично  
`CUSTOM_COLOR`  - Только цветные  
`WHITE`         - Только цветные  
`RIGHT`  
`SOLID`  
`INVERS`  
`GREY_DEFAULT`  
`EBLUE` - Только цветные?  
`BLINK`  
`MIDSIZE`  
`COLOR_THEME_DISABLED` - Только цветные  

`popupConfirmation(t, e)`

## Системные?

`getTime()`
`getVersion()`
`loadScript("mockup/elrsmock.lua")`
`model.getModule(modIdx)`




``` C
local function setLCDvar()
  -- Set the title function depending on if LCD is color, and free the other function and
  -- set textselection unit function, use GetLastPost or sizeText
  if (lcd.RGB ~= nil) then
    lcd_title = lcd_title_color
    functions[10].display = fieldTextSelDisplay_color
  else
    lcd_title = lcd_title_bw
    functions[10].display = fieldTextSelDisplay_bw
    touch2evt = nil
  end
  lcd_title_color = nil
  lcd_title_bw = nil
  fieldTextSelDisplay_bw = nil
  fieldTextSelDisplay_color = nil
  -- Determine if popupConfirmation takes 3 arguments or 2
  -- if pcall(popupConfirmation, "", "", EVT_VIRTUAL_EXIT) then
  -- major 1 is assumed to be FreedomTX
  local _, _, major = getVersion()
  if major ~= 1 then
    popupCompat = popupConfirmation
  end
  ```