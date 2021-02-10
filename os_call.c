int disp_str     		= 0xa0006400;
int ut_gets      		= 0xa0006404;
int ut_getc      		= 0xa0006408;
int ut_putc      		= 0xa000640c;
int wait_ms      		= 0xa0006410;
int Pset         		= 0xa0006414;
int Pget         		= 0xa0006418;
int GetTickCount 		= 0xa000641c;
int cursor_set   		= 0xa0006420;
int display_xn   		= 0xa0006424;
int printf       		= 0xa0006428;
int SYS_FS_FileOpen		= 0xa000642c;
int SYS_FS_FileClose	= 0xa0006430;
int SYS_FS_FileRead		= 0xa0006434;
int SYS_FS_FileWrite	= 0xa0006438;
int ut_error_msg		= 0xa000643c;



int scrn_clear()
{
	memset((char*)0xa0000000, 0, 0x6400);
}
