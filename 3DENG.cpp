/*****************************************************************/
/*                                                               */
/*   CASIO fx-9860G SDK Library                                  */
/*                                                               */
/*   File name : [ProjectName].c                                 */
/*                                                               */
/*   Copyright (c) 2006 CASIO COMPUTER CO., LTD.                 */
/*                                                               */
/*****************************************************************/

extern "C"{
#include "string.h"
#define __KEYBIOS_H__
#include "fxlib.h"
#define KEY_CHAR_0 71
#define KEY_CHAR_1 72
#define KEY_CHAR_2 62
#define KEY_CHAR_3 52
#define KEY_CHAR_4 73
#define KEY_CHAR_5 63
#define KEY_CHAR_6 53
#define KEY_CHAR_7 74
#define KEY_CHAR_8 64
#define KEY_CHAR_9 54
#define KEY_CHAR_DP 61
#define KEY_CHAR_EXP 51
#define KEY_CHAR_PMINUS 41
#define KEY_CHAR_PLUS 42
#define KEY_CHAR_MINUS 32
#define KEY_CHAR_MULT 43
#define KEY_CHAR_DIV 33
#define KEY_CHAR_FRAC 75
#define KEY_CHAR_LPAR 55
#define KEY_CHAR_RPAR 45
#define KEY_CHAR_COMMA 35
#define KEY_CHAR_STORE 25
#define KEY_CHAR_LOG 66
#define KEY_CHAR_LN 56
#define KEY_CHAR_SIN 46
#define KEY_CHAR_COS 36
#define KEY_CHAR_TAN 26
#define KEY_CHAR_SQUARE 67
#define KEY_CHAR_POW 57
#define KEY_CTRL_EXE 31
#define KEY_CTRL_DEL 44
#define KEY_CTRL_AC 32
#define KEY_CTRL_FD 65
#define KEY_CTRL_EXIT 47
#define KEY_CTRL_SHIFT 78
#define KEY_CTRL_ALPHA 77
#define KEY_CTRL_OPTN 68
#define KEY_CTRL_VARS 58
#define KEY_CTRL_UP 28
#define KEY_CTRL_DOWN 37
#define KEY_CTRL_LEFT 38
#define KEY_CTRL_RIGHT 27
#define KEY_CTRL_F1 79
#define KEY_CTRL_F2 69
#define KEY_CTRL_F3 59
#define KEY_CTRL_F4 49
#define KEY_CTRL_F5 39
#define KEY_CTRL_F6 29
#define KEY_CTRL_MENU 48
#ifndef OS2Change
#define OS2Change
#ifndef OS2Change_GetOS2
#define OS2Change_GetOS2
typedef int(*sc_i2cp2sip)(char*, char*, short int*, short int*);
const unsigned int sc0015[] = { 0xD201D002, 0x422B0009, 0x80010070, 0x0015 };
#define GlibGetOSVersionInfo (*(sc_i2cp2sip)sc0015)
int OSVersionAsInt(void)
{
unsigned char mainversion;
unsigned char minorversion;
unsigned short release;
unsigned short build;
GlibGetOSVersionInfo( (char *)&mainversion, (char *)&minorversion, (short *)&release, (short *)&build );
return ( ( mainversion << 24 ) & 0xFF000000 ) | ( ( minorversion << 16 ) & 0x00FF0000 ) | ( release & 0x0000FFFF );
}
#define isOS2 (OSVersionAsInt() >= 0x02020000)
#define OS2(x,y) ((OSVersionAsInt() >= 0x02020000)?y:x)
#endif
#ifndef OS2Change_Keyboard
#define OS2Change_Keyboard
void delay(void)
{
char i;
for (i=0; i<5; i++){};
}
unsigned char CheckKeyRow(unsigned char code)
{
unsigned char result=0;
short*PORTB_CTRL=(short*)0xA4000102;
short*PORTM_CTRL=(short*)0xA4000118;
char*PORTB=(char*)0xA4000122;
char*PORTM=(char*)0xA4000138;
char*PORTA=(char*)0xA4000120;
short smask;
char cmask;
unsigned char column, row;
column = code>>4;
row = code &0x0F;
smask = 0x0003 << (( row %8)*2);
cmask = ~( 1 << ( row %8) );
if(row <8)
{
  *PORTB_CTRL = 0xAAAA ^ smask;
  *PORTM_CTRL = (*PORTM_CTRL & 0xFF00 ) | 0x00AA;
  delay();
  *PORTB = cmask;
  *PORTM = (*PORTM & 0xF0 ) | 0x0F;
}
else
{
  *PORTB_CTRL = 0xAAAA;
  *PORTM_CTRL = ((*PORTM_CTRL & 0xFF00 ) | 0x00AA)  ^ smask;
  delay();
  *PORTB = 0xFF;
  *PORTM = (*PORTM & 0xF0 ) | cmask;
}

delay();
result = (~(*PORTA))>>column & 1;
delay();
*PORTB_CTRL = 0xAAAA;
*PORTM_CTRL = (*PORTM_CTRL & 0xFF00 ) | 0x00AA;
delay();
*PORTB_CTRL = 0x5555;
*PORTM_CTRL = (*PORTM_CTRL & 0xFF00 ) | 0x0055;
delay();

return result;
}

unsigned char KeyDown(unsigned char keycode)
{
unsigned short key[8];
const unsigned short* keyboardregister = (unsigned short*)0xA44B0000;
if(isOS2)
{
  unsigned char row = keycode%10;
  memcpy(key, keyboardregister, sizeof(unsigned short) << 3);
 
  return (0 != (key[row >> 1] & 1 << keycode / 10 - 1 + ((row & 1) << 3)));
}
else
{
  return CheckKeyRow((keycode % 10) + ((keycode / 10 - 1) << 4));
}
}
unsigned char GetKeyMod(unsigned int *key)
{
unsigned char x, ret;

ret = GetKey(key);

for(x = 0; x < 80; x++)
{
  if(KeyDown(x))
  {
   *key = x;
   break;
  }
}
return ret;
}
#define IsKeyDown(x) KeyDown(x)
#define IsKeyUp(x) !KeyDown(x)
#define GetKey(x) GetKeyMod(x)
#endif
#endif
}

extern "C"{
#include "fxlib.h"
#include "stdio.h"
#include "stdlib.h"
#include "timer.h"
}
#include "engine.h"

//****************************************************************************
//  AddIn_main (Sample program main function)
//
//  param   :   isAppli   : 1 = This application is launched by MAIN MENU.
//                        : 0 = This application is launched by a strip in eACT application.
//
//              OptionNum : Strip number (0~3)
//                         (This parameter is only used when isAppli parameter is 0.)
//
//  retval  :   1 = No error / 0 = Error
//
//****************************************************************************

unsigned int key1, key2, unused;
Mesh* mesh;
Mesh* meshes[1];
bool rotating = false;
int rotation_counter = 0;

#define LEFT  0
#define RIGHT 1
#define UP    2
#define DOWN  3

extern "C"{
    
    void rotate(int direction, double rotation){
        switch(direction){
            case LEFT:
                mesh->rotation.z-=rotation;
                break;
            case RIGHT:
                mesh->rotation.z+=rotation;
                break;
            case UP:
                break;
            case DOWN:
                break;
        }
    }
    
    void rotate_left(){
        rotating = true;
        mesh->rotation.z -= 0.08;
        if(rotation_counter >= 20){
            KillTimer(ID_USER_TIMER1);
            rotating = false;
            rotation_counter = 0;
            mesh->rotation.z = 0.0;
        }
        rotation_counter++;
    }
    
    void rotate_right(){
        rotating = true;
        mesh->rotation.z += 0.08;
        if(rotation_counter >= 20){
            KillTimer(ID_USER_TIMER1);
            rotating = false;
            rotation_counter = 0;
            mesh->rotation.z = 0.0;
        }
        rotation_counter++;
    }
    
    void rotate_down(){
        rotating = true;
        mesh->rotation.x += 0.08;
        if(rotation_counter >= 20){
            KillTimer(ID_USER_TIMER1);
            rotating = false;
            rotation_counter = 0;
            mesh->rotation.x = 0.0;
        }
        rotation_counter++;
    }
    
    void rotate_up(){
        rotating = true;
        mesh->rotation.x -= 0.08;
        if(rotation_counter >= 20){
            KillTimer(ID_USER_TIMER1);
            rotating = false;
            rotation_counter = 0;
            mesh->rotation.x = 0.0;
        }
        rotation_counter++;
    }
    
    bool handle_keys(){
        if(IsKeyDown(KEY_CTRL_MENU) || IsKeyDown(KEY_CTRL_EXIT)){
            return false;
        }
        
        /*if(IsKeyDown(KEY_CTRL_LEFT)){
            if(!rotating){
                SetTimer(ID_USER_TIMER1, 1, rotate_left);
                rotation_counter = 0;
            }
        }
        
        if(IsKeyDown(KEY_CTRL_RIGHT)){
            if(!rotating){
                SetTimer(ID_USER_TIMER1, 1, rotate_right);
                rotation_counter = 0;
            }
        }
        
        if(IsKeyDown(KEY_CTRL_UP)){
            if(!rotating){
                SetTimer(ID_USER_TIMER1, 1, rotate_up);
                rotation_counter = 0;
            }
        }
        
        if(IsKeyDown(KEY_CTRL_DOWN)){
            if(!rotating){
                SetTimer(ID_USER_TIMER1, 1, rotate_down);
                rotation_counter = 0;
            }
        }*/
        
        return true;
    }
    
    void draw_text(unsigned char* text, int x, int y){
        locate(x,y);
        Print(text);
    }
    
    int itoa(int value, char *sp, int radix)
{
    char tmp[16];// be careful with the length of the buffer
    char *tp = tmp;
    int i;
    unsigned v;

    int sign = (radix == 10 && value < 0);    
    if (sign)
        v = -value;
    else
        v = (unsigned)value;

    while (v || tp == tmp)
    {
        i = v % radix;
        v /= radix; // v/=radix uses less CPU clocks than v=v/radix does
        if (i < 10)
          *tp++ = i+'0';
        else
          *tp++ = i + 'a' - 10;
    }

    int len = tp - tmp;

    if (sign) 
    {
        *sp++ = '-';
        len++;
    }

    while (tp > tmp)
        *sp++ = *--tp;

    return len;
    }
}

void main(){
    Engine eng = Engine();
    Camera cam = Camera();
	mesh = new Mesh(8, 12, 0);
    mesh->vertices[0] = Vector3(-1, 1, 1); 
    mesh->vertices[1] = Vector3(1, 1, 1); 
    mesh->vertices[2] = Vector3(-1,-1,1);
    mesh->vertices[3] = Vector3(1,-1,1);
    mesh->vertices[4] = Vector3(-1, 1, -1);
    mesh->vertices[5] = Vector3(1,1,-1);
    mesh->vertices[6] = Vector3(1,-1,-1);
    mesh->vertices[7] = Vector3(-1,-1,-1);
    
    mesh->faces[0] = Face(0, 1, 2);
    mesh->faces[1] = Face(1, 2, 3);
    mesh->faces[2] = Face(1, 3, 6);
    mesh->faces[3] = Face(1, 5, 6);
    mesh->faces[4] = Face(0, 1, 4);
    mesh->faces[5] = Face(1, 4, 5);

    mesh->faces[6] = Face(2, 3, 7);
    mesh->faces[7] = Face(3, 6, 7);
    mesh->faces[8] = Face(0, 2, 7);
    mesh->faces[9] = Face(0, 4, 7);
    mesh->faces[10]= Face(4, 5, 6);
    mesh->faces[11]= Face(4, 6, 7);
    
    meshes[0] = mesh;
    cam.position = Vector3(0,0,10);
    cam.target = Vector3(0,0,0);
    mesh->position = Vector3(0,0,0);
    while(handle_keys()){
        
        eng.clear();
        mesh->rotation.x += 0.02;
        mesh->rotation.y += 0.02;
        
        eng.render(cam, meshes);
        
        eng.present();
    }
    
}




extern "C"{
    int AddIn_main(int isAppli, unsigned short OptionNum)
    {
        main();

        return 1;
    }
}




//****************************************************************************
//**************                                              ****************
//**************                 Notice!                      ****************
//**************                                              ****************
//**************  Please do not change the following source.  ****************
//**************                                              ****************
//****************************************************************************


#pragma section _BR_Size
unsigned long BR_Size;
#pragma section


#pragma section _TOP

//****************************************************************************
//  InitializeSystem
//
//  param   :   isAppli   : 1 = Application / 0 = eActivity
//              OptionNum : Option Number (only eActivity)
//
//  retval  :   1 = No error / 0 = Error
//
//****************************************************************************
int InitializeSystem(int isAppli, unsigned short OptionNum)
{
    return INIT_ADDIN_APPLICATION(isAppli, OptionNum);
}

#pragma section

