#include "stdio.h"
#include "stdlib.h"
#include "stm32f10x.h"


#include "delay.h"
#include "led.h"
#include "lua_uart.h"
#include "malloc.h"

#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"




static int lua_led_on(lua_State *L) {
	GPIO_ResetBits(GPIOE,GPIO_Pin_5); 
	return 1;
}

 

static int lua_led_off(lua_State *L) {
	GPIO_SetBits(GPIOE,GPIO_Pin_5);
	return 1;
}

 

static int lua_delay(lua_State *L) {
	int num;
	num = lua_tointeger(L, 1);
	Delay_ms(num);
	return 1;
}

 

static const struct luaL_Reg mylib[] = {
	 {"led_on",lua_led_on},
	 {"led_off",lua_led_off},
	 {"delay",lua_delay},
	 {NULL,NULL}
};

 

int luaopen_mylib(lua_State *L) { 
#if 1
	//lua_newtable(L);
	luaL_setfuncs(L, mylib, 0);
#else
	luaL_newlib(L, mylib);
#endif
	return 1;
}

 

const char LUA_SCRIPT_GLOBAL[] ="  \
off = 500     \
on = 500       \
while 1 do \
	print(\"Hello,I am lua!\\n--this is newline\\n\") \
	led_off() \
	delay(off)    \
	led_on()        \
	delay(on)      \
end";



int main(void) {
	int ret = 0;
	lua_State *L = NULL;
	Uart1_Init(115200);
	LED_Init();
	SysTick_Init();
	mem_init(SRAMIN);		//初始化内部内存池
	L = luaL_newstate();
	printf("L = %x\n", L);
	if(L == NULL) {
		abort();
	}
	 
    //luaL_openlibs(L);  
	luaopen_base(L);

	luaopen_mylib(L);

 

	ret = luaL_dostring(L, LUA_SCRIPT_GLOBAL);

	printf("ret = %x\n", ret);
	if (ret != 0) {
		abort();
	}

	lua_close(L);

	//abort();

	for(;;) {
		;
	}  

}