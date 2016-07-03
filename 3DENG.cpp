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
#include "fxlib.h"
#include "stdio.h"
#include "stdlib.h"
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
Mesh mesh = Mesh(8);
Mesh meshes[1];

extern "C"{
    bool handle_keys(){
        //Bkey_GetKeyWait(&key1, &key2, KEYWAIT_HALTOFF_TIMEROFF, 0, 1, &unused);
        if(key1 == 4 && key2 == 8){
            return false;
        }
        if(key1 == 4 && key2 == 9){
            return false;
        }
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
    mesh.vertices[0] = Vector3(-1, 1, 1); 
    mesh.vertices[1] = Vector3(1, 1, 1); 
    mesh.vertices[2] = Vector3(-1,-1,1);
    mesh.vertices[3] = Vector3(1,-1,1);
    mesh.vertices[4] = Vector3(-1, 1, -1);
    mesh.vertices[5] = Vector3(1,1,-1);
    mesh.vertices[6] = Vector3(1,-1,-1);
    mesh.vertices[7] = Vector3(-1,-1,-1);
    
    mesh.faces[0] = Face(0, 1, 2);
    mesh.faces[1] = Face(1, 2, 3);
    mesh.faces[2] = Face(1, 3, 6);
    mesh.faces[3] = Face(1, 5, 6);
    mesh.faces[4] = Face(0, 1, 4);
    mesh.faces[5] = Face(1, 4, 5);

    mesh.faces[6] = Face(2, 3, 7);
    mesh.faces[7] = Face(3, 6, 7);
    mesh.faces[8] = Face(0, 2, 7);
    mesh.faces[9] = Face(0, 4, 7);
    mesh.faces[10]= Face(4, 5, 6);
    mesh.faces[11]= Face(4, 6, 7);
    
    meshes[0] = mesh;
    cam.position = Vector3(0,0,10);
    cam.target = Vector3(0,0,0);
    mesh.position = Vector3(0,0,0);
    while(handle_keys()){
        
        eng.clear();
        mesh.rotation.x += 0.02;
        mesh.rotation.y += 0.02;
        meshes[0] = mesh;
        
        eng.render(cam, meshes);
        
        eng.present();
    }
    
}




extern "C"{
    int AddIn_main(int isAppli, unsigned short OptionNum)
    {
        /*unsigned int key;

        Bdisp_AllClr_DDVRAM();

        locate(1,4);
        Print((unsigned char*)"This application is");
        locate(1,5);
        Print((unsigned char*)" sample Add-In.");

        while(1){
            GetKey(&key);
        }*/
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

