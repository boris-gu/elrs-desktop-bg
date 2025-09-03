#include <stdio.h>
#include <string.h>
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"

typedef enum{
  EVT_VIRTUAL_ENTER,  // Нажатие на колесо
  EVT_VIRTUAL_EXIT,   // Нажатие RTN
  EVT_VIRTUAL_NEXT,   // Прокрутка колеса
  EVT_VIRTUAL_PREV    // Прокрутка колеса
} virtual_events;

typedef enum{
  MIDSIZE,
  BLINK,
  RIGHT,
  INVERS,
  GREY_DEFAULT
} draw_text_flags;

typedef enum{
  SOLID,
  DOTTED
} draw_line_patterns;

void register_const (lua_State *L);

int main() {
  lua_State *L = luaL_newstate();
  luaL_openlibs(L);

  register_const(L);

  // Загружаем и выполняем скрипт
  if (luaL_dofile(L, ".\\scripts\\elrsV3.lua") != LUA_OK) {
    printf("%s\n", lua_tostring(L, -1));
    lua_pop(L, 1);
    lua_close(L);
    return 1;
  }

  if (!lua_istable(L, -1)) {
    printf("Script didn't return a table\n");
    lua_pop(L, 1);
    lua_close(L);
    return 2;
  }

  // Функция init
  // Загружаем в стек и выполняем
  if (lua_getfield(L, -1, "init") == LUA_TFUNCTION) { // XXX: Возвращает тип только с Lua 5.3!!!
    if (lua_pcall(L, 0, 0, 0) != LUA_OK) {
      printf("Error calling init(): %s\n", lua_tostring(L, -1));
      lua_pop(L, 1);
    }
  } else {
    printf("\"init\" is not a function\n");
    lua_pop(L, 1);
  }

  // Функция run
  // XXX: Запускаем при каждом событии?
  if (lua_getfield(L, -1, "run") == LUA_TFUNCTION) {
    lua_pushinteger(L, 4100);
    lua_pushnil(L);
    if (lua_pcall(L, 2, 1, 0) != LUA_OK) {
      printf("Error calling run(): %s\n", lua_tostring(L, -1));
      lua_pop(L, 1);
    } else {
      int lua_run_f_return = lua_tointeger(L, -1);
      lua_pop(L, 1);
      printf("C run return %d", lua_run_f_return);
    }
  }else {
    printf("\"run\" is not a function\n");
    lua_pop(L, 1);
  }

  printf("C END\n");
  lua_settop (L, 0);
  lua_close(L);
  return 0;
}

void register_const(lua_State *L) {
  // virtual_events
  lua_pushinteger(L, EVT_VIRTUAL_ENTER);
  lua_setglobal(L, "EVT_VIRTUAL_ENTER");
  lua_pushinteger(L, EVT_VIRTUAL_EXIT);
  lua_setglobal(L, "EVT_VIRTUAL_EXIT");
  lua_pushinteger(L, EVT_VIRTUAL_NEXT);
  lua_setglobal(L, "EVT_VIRTUAL_NEXT");
  lua_pushinteger(L, EVT_VIRTUAL_PREV);
  lua_setglobal(L, "EVT_VIRTUAL_PREV");
  // draw_text_flags
  lua_pushinteger(L, MIDSIZE);
  lua_setglobal(L, "MIDSIZE");
  lua_pushinteger(L, BLINK);
  lua_setglobal(L, "BLINK");
  lua_pushinteger(L, RIGHT);
  lua_setglobal(L, "RIGHT");
  lua_pushinteger(L, INVERS);
  lua_setglobal(L, "INVERS");
  lua_pushinteger(L, GREY_DEFAULT);
  lua_setglobal(L, "GREY_DEFAULT");
  // draw_line_patterns
  lua_pushinteger(L, SOLID);
  lua_setglobal(L, "SOLID");
  lua_pushinteger(L, DOTTED);
  lua_setglobal(L, "DOTTED");
}