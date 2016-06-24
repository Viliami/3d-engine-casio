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

class Rectangle {
    int width, height;
    public:
        void set_values (int,int);
        int area (void);
};

extern "C"{
    void clear_screen(){
        Bdisp_AllClr_DDVRAM();
    }
}

void main(){
    clear_screen();
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

