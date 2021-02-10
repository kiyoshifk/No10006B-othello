#define macrox(pos) ((pos)%9)	/* pos Ç©ÇÁÇwç¿ïWÇ÷ÇÃïœä∑ x=1Å`8	*/
#define macroy(pos) ((pos)/9)	/* pos Ç©ÇÁÇxç¿ïWÇ÷ÇÃïœä∑ y=1Å`8	*/
#define macropos(x,y) ((x)+(y)*9)	/* X,Y ç¿ïWÇ©ÇÁ pos Ç÷ÇÃïœä∑	*/
#define macroinv(koma) ((koma)==ISHI_K ? ISHI_S : ISHI_K)
#define abs1(x) ((x)<0 ? -(x) : (x))

#define ISHI_N		0
#define ISHI_K		1
#define ISHI_S		2
#define ISHI_O		3

#define UP    0x112
#define DOWN  0x113
#define RIGHT 0x114
#define LEFT  0x115


#define VIDEO	0xa0000000


	int tekazu;
	int teban;
	int white;						//0:cpu, 1:human
	int black;						//0:cpu, 1:human
	char goban[100];
	char msg1[50];
	char msg2[50];
	char msg3[50];
	int timesetting;
	int brink_flag;
//	int *dir3;
	long eva_cnt;
//	long *tenpat_std;
//	long *tenpat_test;
//	long *tenpat_end;
	unsigned rnd_init;
int dir3[8]={-8,-9,-10,-1,1,8,9,10};



#define T1 8000
#define T2 (-250)
#define T3 30
#define T4 0
#define T5 (-2000)
#define T6 (-10)
#define T7 (-10)
#define T8 (-10)
#define T9 (-10)
#define Ta (-10)
long tenpat_std[85]={0,0,0,0,0,0,0,0,0,0,
               T1,T2,T3,T4,T4,T3,T2,T1,0,
               T2,T5,T6,T7,T7,T6,T5,T2,0,
               T3,T6,T8,T9,T9,T8,T6,T3,0,
               T4,T7,T9,Ta,Ta,T9,T7,T4,0,
               T4,T7,T9,Ta,Ta,T9,T7,T4,0,
               T3,T6,T8,T9,T9,T8,T6,T3,0,
               T2,T5,T6,T7,T7,T6,T5,T2,0,
               T1,T2,T3,T4,T4,T3,T2,T1,0,
               };

#define U1 8000
#define U2 (-250)
#define U3 30
#define U4 0
#define U5 (-2000)
#define U6 (-10)
#define U7 (-10)
#define U8 (-10)
#define U9 (-10)
#define Ua (-10)
long tenpat_test[85]={0,0,0,0,0,0,0,0,0,0,
               U1,U2,U3,U4,U4,U3,U2,U1,0,
               U2,U5,U6,U7,U7,U6,U5,U2,0,
               U3,U6,U8,U9,U9,U8,U6,U3,0,
               U4,U7,U9,Ua,Ua,U9,U7,U4,0,
               U4,U7,U9,Ua,Ua,U9,U7,U4,0,
               U3,U6,U8,U9,U9,U8,U6,U3,0,
               U2,U5,U6,U7,U7,U6,U5,U2,0,
               U1,U2,U3,U4,U4,U3,U2,U1,0,
               };

long tenpat_end[85] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				T1, T1, T1, T1, T1, T1, T1, T1, 0,
				T1, T1, T1, T1, T1, T1, T1, T1, 0,
				T1, T1, T1, T1, T1, T1, T1, T1, 0,
				T1, T1, T1, T1, T1, T1, T1, T1, 0,
				T1, T1, T1, T1, T1, T1, T1, T1, 0,
				T1, T1, T1, T1, T1, T1, T1, T1, 0,
				T1, T1, T1, T1, T1, T1, T1, T1, 0,
				T1, T1, T1, T1, T1, T1, T1, T1, 0,
};


#include "os_call.c"
#include "string.c"
#include "disp.c"
#include "MC.c"


/********************************************************************************/
/*		MAINtask																*/
/*      â~ÇÃècâ°î‰ : 1.19                                                        */
/********************************************************************************/

int main()
{
//long eva_cnt;
	int c;

	disp_str("\nOthello Game V300.1.00 2021.1.13\n");
	for(;;){
		disp_str("Black:cpu,   White:cpu  (y)");
		c = ut_getc(); ut_putc('\n');
		if(c=='y'){
			black = 0;
			white = 0;
			break;
		}
		disp_str("Black:human, White:human(y)");
		c = ut_getc(); ut_putc('\n');
		if(c=='y'){
			black = 1;
			white = 1;
			break;
		}
		disp_str("Black:cpu,   white:human(y)");
		c = ut_getc(); ut_putc('\n');
		if(c=='y'){
			black = 0;
			white = 1;
			break;
		}
		disp_str("Black:hunam, White:cpu  (y)");
		c = ut_getc(); ut_putc('\n');
		if(c=='y'){
			black = 1;
			white = 0;
			break;
		}
	}
	ut_putc('\n');
	for(;;){
		disp_str("strong (y)");
		c = ut_getc(); ut_putc('\n');
		if(c=='y'){
			timesetting = 1000; 
			break;
		}
		disp_str("normal (y)");
		c = ut_getc(); ut_putc('\n');
		if(c=='y'){
			timesetting = 30; 
			break;
		}
		disp_str("weak   (y)");
		c = ut_getc(); ut_putc('\n');
		if(c=='y'){
			timesetting = 3; 
			break;
		}
	}
	ut_putc('\n');
	for(;;){
		disp_str("brink ON  (y)");
		c = ut_getc(); ut_putc('\n');
		if(c=='y'){
			brink_flag = 1; 
			break;
		}
		disp_str("brink OFF (y)");
		c = ut_getc(); ut_putc('\n');
		if(c=='y'){
			brink_flag = 0; 
			break;
		}
	}
	
	game_init();
	game();

}
/********************************************************************************/
/*		koma0																	*/
/*		êŒñ≥ÇµÇÃãÓ																*/
/********************************************************************************/
int koma0(int x, int y)
{
	if(x<1 || x>8 || y<1 || y>8)
		return;
	
	boxfill(x*28+180, y*32, x*28+208, y*32+32, 0);	// clear
	/***	òg	***/
	line1(x*28+180, y*32, x*28+180, y*32+32, 1);
	line1(x*28+208, y*32, x*28+208, y*32+32, 1);
	line1(x*28+180, y*32, x*28+208, y*32, 1);
	line1(x*28+180, y*32+32, x*28+208, y*32+32, 1);
}

/********************************************************************************/
/*		koma1																	*/
/*		çïãÓ																	*/
/********************************************************************************/
int koma1(int x, int y)
{
	if(x<1 || x>8 || y<1 || y>8)
		return;
	koma0(x, y);
	circle2(x*28+180+14, y*32+16, 12, 14, 1);
}

/********************************************************************************/
/*		koma2																	*/
/*		îíãÓ																	*/
/********************************************************************************/
int koma2(int x, int y)
{
	if(x<1 || x>8 || y<1 || y>8)
		return;
	koma0(x, y);
	circlefill2(x*28+180+14, y*32+16, 12, 14, 1);
}

/********************************************************************************/
/*		koma3																	*/
/*		è¨çïä€																	*/
/********************************************************************************/
int koma3(int x, int y)
{
	if(x<1 || x>8 || y<1 || y>8)
		return;
	circlefill(x*28+180+14, y*32+16, 6, 0);
}

/********************************************************************************/
/*		koma4																	*/
/*		è¨îíä€																	*/
/********************************************************************************/
int koma4(int x, int y)
{
	if(x<1 || x>8 || y<1 || y>8)
		return;
	circlefill(x*28+180+14, y*32+16, 6, 1);
}

/********************************************************************************/
/*		dispban																	*/
/********************************************************************************/
int dispban(char *ban, int pos)
{
	int x, y, p, k;
	char buf[10];
	
//	memset((char *)video, 0, sizeof(uint32_t)*321*20);
	for(x=1; x<=8; x++){
		for(y=1; y<=8; y++){
			p = macropos(x,y);
			k = ban[p];
			if(k==ISHI_N)
				koma0(x,y);
			else if(k==ISHI_K)
				koma1(x,y);
			else if(k==ISHI_S)
				koma2(x,y);
		}
	}
    for(x=1; x<=8; x++){
		buf[0] = 'A'+x+1;
		buf[1] = 0;
		display_xn(x*28+180+8, 32-24, buf, 2);
    }
    for(y=1; y<=8; y++){
		buf[0] = '1'+y-1;
		display_xn(28+180-20, y*32+8, buf, 2);
    }
    x = macrox(pos);
    y = macroy(pos);
    if(ban[pos]==ISHI_K || ban[pos]==ISHI_N)
    	koma4(x,y);							// è¨îíä€
    else if(ban[pos]==ISHI_S)
    	koma3(x,y);							// è¨çïä€
    
    for(y=80; y<120+16; y++){
		for(x=0; x<28+180-20; x++){
			Pset(x,y,0);					// clear
		}
	}
//    display(0,40,msg1);
//    display(0,50,msg2);
//    display(0,60,msg3);

	cursor_set(0, 5);
	disp_str(msg1);
	cursor_set(0, 10);
	disp_str(msg2);
	cursor_set(0, 15);
	disp_str(msg3);
}
/********************************************************************************/
/*		Dispbug																	*/
/********************************************************************************/
int Dispbug()
{
	disp_str("\n\nFATAL error\n");
    for(;;);
}
/********************************************************************************/
/*		msg_main_printf															*/
/********************************************************************************/
//int msg_main_printf(const char *fmt, ...)
//{
//	char buf[50];
//	va_list ap;
//	
//	va_start(ap, fmt);
//	vsprintf(buf, fmt, ap);				/* ï∂éöóÒçÏê¨ÉTÉuÉãÅ[É`Éì				*/
//	va_end(ap);
//
//    erase_line(300,320);
//    cursor_set(0, 30);
//    disp_str(buf);
//}
/********************************************************************************/
/*		human_input																*/
/********************************************************************************/
int human_input(int pos)
{
	int x, y, p, key;
	
	x = macrox(pos);
	y = macroy(pos);
	for(;;){
		p = macropos(x,y);
		dispban(goban, p);
//        keywait();
//		key = keyinwait();
		key = ut_getc();				// get 1 charactor
		if(key==UP){
			if(--y <= 0)
				y = 1;
		}
		else if(key==DOWN){
			if(++y >= 9)
				y = 8;
		}
		else if(key==LEFT){
			if(--x <= 0)
				x = 1;
		}
		else if(key==RIGHT){
			if(++x >= 9)
				x = 8;
		}
		else if(key=='\n'){
			return macropos(x,y);
		}
	}
}
/********************************************************************************/
/*      brinking                                                                */
/********************************************************************************/
int brinking(int k, int pos)
{
    int i, x, y;
    
    x = macrox(pos);
    y = macroy(pos);
    for(i=0; i<3; i++){
        if(k==ISHI_K)
            koma1(x,y);
        else
            koma2(x,y);
        wait_ms(500);
        koma0(x,y);
        wait_ms(500);
    }
}
/********************************************************************************/
/*		line1																	*/
/********************************************************************************/
int line1(int x1, int y1, int x2, int y2, int color)
{
	int sx,sy,dx,dy,i;
	int e;

	if(x2>x1){
		dx=x2-x1;
		sx=1;
	}
	else{
		dx=x1-x2;
		sx=-1;
	}
	if(y2>y1){
		dy=y2-y1;
		sy=1;
	}
	else{
		dy=y1-y2;
		sy=-1;
	}
	if(dx>=dy){
		e=-dx;
		for(i=0;i<=dx;i++){
			Pset(x1,y1,color);
			x1+=sx;
			e+=dy*2;
			if(e>=0){
				y1+=sy;
				e-=dx*2;
			}
		}
	}
	else{
		e=-dy;
		for(i=0;i<=dy;i++){
			Pset(x1,y1,color);
			y1+=sy;
			e+=dx*2;
			if(e>=0){
				x1+=sx;
				e-=dy*2;
			}
		}
	}
}
/********************************************************************************/
/*		circle1																	*/
/*		(x0,y0) ÇíÜêSÇ…ÅAîºåa r ÇÃâ~Çï`Ç≠										*/
/********************************************************************************/
int circle1(int x0, int y0, int r, int color)
{
	int x,y,f;
	x=r;
	y=0;
	f=-2*r+3;
	while(x>=y){
		Pset(x0-x,y0-y,color);
		Pset(x0-x,y0+y,color);
		Pset(x0+x,y0-y,color);
		Pset(x0+x,y0+y,color);
		Pset(x0-y,y0-x,color);
		Pset(x0-y,y0+x,color);
		Pset(x0+y,y0-x,color);
		Pset(x0+y,y0+x,color);
		if(f>=0){
			x--;
			f-=x*4;
		}
		y++;
		f+=y*4+2;
	}
}
/********************************************************************************/
/*		circle2																	*/
/*		(x0,y0) ÇíÜêSÇ…ÅAîºåa r ÇÃâ~Çï`Ç≠										*/
/********************************************************************************/
int circle2(int x0, int y0, int rx, int ry, int color)
{
	int x,y,f;
	x=rx;
	y=0;
	f=(3-rx-ry)*rx*ry;
//    f = -(rx+ry)*rx*ry/2;
	while(x*ry*ry >= y*rx*rx){
		Pset(x0-x,y0-y,color);
		Pset(x0-x,y0+y,color);
		Pset(x0+x,y0-y,color);
		Pset(x0+x,y0+y,color);
		if(f>=0){
			x--;
			f-=x*4*ry*ry;
		}
		y++;
		f+=y*4*rx*rx;
	}
	Pset(x0-x,y0-y,color);
	Pset(x0-x,y0+y,color);
	Pset(x0+x,y0-y,color);
	Pset(x0+x,y0+y,color);

	y=ry;
	x=0;
	f=(3-rx-ry)*rx*ry;
//    f = -(rx+ry)*rx*ry/2;
	while(y*rx*rx >= x*ry*ry){
		Pset(x0-x,y0-y,color);
		Pset(x0-x,y0+y,color);
		Pset(x0+x,y0-y,color);
		Pset(x0+x,y0+y,color);
		if(f>=0){
			y--;
			f-=y*4*rx*rx;
		}
		x++;
		f+=x*4*ry*ry;
	}
	Pset(x0-x,y0-y,color);
	Pset(x0-x,y0+y,color);
	Pset(x0+x,y0-y,color);
	Pset(x0+x,y0+y,color);
}
/********************************************************************************/
/*		boxfill																	*/
/*		(x1,y1),(x2,y2)ÇëŒäpê¸Ç∆Ç∑ÇÈÉJÉâÅ[cÇ≈ìhÇÁÇÍÇΩí∑ï˚å`Çï`âÊ				*/
/********************************************************************************/
/*	âëúìx 448x320     */
#define Y_MAX	319
#define X_MAX	447

int boxfill(int x1, int y1, int x2, int y2, int c)
{
	int temp;
	if(x1>x2){
		temp=x1;
		x1=x2;
		x2=temp;
	}
	if(x2<0 || x1>=X_MAX) return;
	if(y1>y2){
		temp=y1;
		y1=y2;
		y2=temp;
	}
	if(y2<0 || y1>=Y_MAX) return;
	if(y1<0) y1=0;
	if(y2>=Y_MAX) y2=Y_MAX-1;
	while(y1<=y2){
		line1(x1,y1,x2,y1,c);
        y1++;
	}
}
/********************************************************************************/
/*		circlefill																*/
/*		(x0,y0)ÇíÜêSÇ…ÅAîºåarÅAÉJÉâÅ[cÇ≈ìhÇÁÇÍÇΩâ~Çï`âÊ						*/
/********************************************************************************/
int circlefill(int x0, int y0, int r, int c)
{
	int x,y,f;
	x=r;
	y=0;
	f=-2*r+3;
	while(x>=y){
		line1(x0-x,y0-y,x0+x,y0-y,c);
		line1(x0-x,y0+y,x0+x,y0+y,c);
		line1(x0-y,y0-x,x0+y,y0-x,c);
		line1(x0-y,y0+x,x0+y,y0+x,c);
		if(f>=0){
			x--;
			f-=x*4;
		}
		y++;
		f+=y*4+2;
	}
}
/********************************************************************************/
/*		circlefill																*/
/*		(x0,y0)ÇíÜêSÇ…ÅAîºåarÅAÉJÉâÅ[cÇ≈ìhÇÁÇÍÇΩâ~Çï`âÊ						*/
/********************************************************************************/
int circlefill2(int x0, int y0, int rx, int ry, int c)
{
	int x,y,f;
	x=rx;
	y=0;
//	f=(3-rx-ry)*rx*ry;
    f = -(rx+ry)*rx*ry/2;
	while(x*ry*ry >= y*rx*rx){
		line1(x0-x,y0-y,x0+x,y0-y,c);
		line1(x0-x,y0+y,x0+x,y0+y,c);
		if(f>=0){
			x--;
			f-=x*4*ry*ry;
		}
		y++;
		f+=y*4*rx*rx;
	}
	line1(x0-x,y0-y,x0+x,y0-y,c);
	line1(x0-x,y0+y,x0+x,y0+y,c);

	y=ry;
	x=0;
//	f=(3-rx-ry)*rx*ry;
    f = -(rx+ry)*rx*ry/2;
	while(y*rx*rx >= x*ry*ry){
		line1(x0-x,y0-y,x0+x,y0-y,c);
		line1(x0-x,y0+y,x0+x,y0+y,c);
		if(f>=0){
			y--;
			f-=y*4*rx*rx;
		}
		x++;
		f+=x*4*ry*ry;
	}
	line1(x0-x,y0-y,x0+x,y0-y,c);
	line1(x0-x,y0+y,x0+x,y0+y,c);
}
