//############################################################################//
// HEAD : (c) ARDIA 2012 : " Any copie and re-utilisation of this file without  
//                           the written consent of ARDIA is forbidden "        
//        --------------------------------------------------------------------  
//        Classification :  (-)No   (-)Confident. ARDIA   (-)Confident. Client  
//        --------------------------------------------------------------------  
//        --------------------------------------------------------------------  
//        Module name : CLV_DRV  
//############################################################################//
// FILE : CLV_DRV.C (SOURCE)
//----------------------------------------------------------------------------//
// DESC : Module description
//----------------------------------------------------------------------------//
// LIST : * List of the functions
//----------------------------------------------------------------------------//
// HIST : Version |   Date   | Author           | Description                             
//----------------------------------------------------------------------------//
//         01.00  | 12/08/12 |  Ghariani Ahmed  | Creation of this file
//
//############################################################################//

//****************************************************************************//
// INCLIB
//****************************************************************************//

//****************************************************************************//
// INCUSER
//****************************************************************************//

#include "..\SW_CEDU01\B1.0\DRIVERS\CLV_DRV\CLV_DRV.h"

unsigned char FlagSw2;
unsigned char FlagSw3;
unsigned char FlagSw4;
unsigned char FlagSw5;



//============================================================================
// NAME : vCLV_iClvInitButtons_Cmd
//============================================================================
// ROLE : Initialiser le clavier
//----------------------------------------------------------------------------
// INPUT  : void 
//----------------------------------------------------------------------------
// OUTPUT : void
//----------------------------------------------------------------------------
// RESOURCES :
//----------------------------------------------------------------------------
// HIST : Version |   Date   | Author           | Description                           
//        --------------------------------------------------------------------
//         01.00  | 12/08/12 |  Ghariani Ahmed  | Creation of this function              
//============================================================================



void vCLV_iClvInitButtons_Cmd(void)
{
  vCLV_InitExtInt0_Cmd();
  vCLV_InitExtInt1_Cmd();
  vCLV_InitExtInt2_Cmd();
  vCLV_InitExtInt3_Cmd();
}


//============================================================================
// NAME : vCLV_InitExtInt0_Cmd
//============================================================================
// ROLE : initialiser le bouton SW2 
//----------------------------------------------------------------------------
// INPUT  : void
//----------------------------------------------------------------------------
// OUTPUT : void
//----------------------------------------------------------------------------
// RESOURCES :
//----------------------------------------------------------------------------
// HIST : Version |   Date   | Author           | Description                           
//        --------------------------------------------------------------------
//         01.00  | 12/08/12 |  Ghariani Ahmed  | Creation of this function              
//============================================================================



void vCLV_InitExtInt0_Cmd(void)
{
  iClv_PinSw2  = 0;    
  iDirClv_D0   = 0; // Button INT0 as input
  iClv_input0  = 1; // Enable Button INT0 as input
  iClv_EXT0B   = 1;   // LB0, LA0 = 11 -> Hight level
  iClv_EXT0A   = 1;
  iClv_FlagSw2 = 0;   // reset interrupt request
  iClv_ENBLSw2 = 1;   // enable interrupt request
  FlagSw2  = 0;  
}


//============================================================================
// NAME : vCLV_InitExtInt1_Cmd
//============================================================================
// ROLE : initialiser le bouton SW3 
//----------------------------------------------------------------------------
// INPUT  :void
//----------------------------------------------------------------------------
// OUTPUT : void
//----------------------------------------------------------------------------
// RESOURCES :
//----------------------------------------------------------------------------
// HIST : Version |   Date   | Author           | Description                           
//        --------------------------------------------------------------------
//         01.00  | 12/08/12 |  Ghariani Ahmed  | Creation of this function              
//============================================================================



void vCLV_InitExtInt1_Cmd(void)
{
  iClv_PinSw3  = 0;    
  iDirClv_D1   = 0; 
  iClv_input1  = 1;
  iClv_EXT1B   = 1; 
  iClv_EXT1A   = 1;
  iClv_FlagSw3 = 0;
  iClv_ENBLSw3 = 1; 
  FlagSw3 = 0; 
}


//============================================================================
// NAME : vCLV_InitExtInt2_Cmd
//============================================================================
// ROLE : initialiser le bouton SW4 
//----------------------------------------------------------------------------
// INPUT  : void
//----------------------------------------------------------------------------
// OUTPUT : void
//----------------------------------------------------------------------------
// RESOURCES :
//----------------------------------------------------------------------------
// HIST : Version |   Date   | Author          | Description                           
//        --------------------------------------------------------------------
//         01.00  | 12/08/12 |  Ghariani Ahmed | Creation of this function              
//============================================================================



void vCLV_InitExtInt2_Cmd(void)
{
  iClv_PinSw4  = 0;   
  iDirClv_D2   = 0;
  iClv_input2  = 1;
  iClv_EXT2B   = 1;
  iClv_EXT2A   = 1;
  iClv_FlagSw4 = 0;
  iClv_ENBLSw4 = 1;
  FlagSw4   = 0; 
}



//============================================================================
// NAME : vCLV_InitExtInt3_Cmd
//============================================================================
// ROLE : initialiser le bouton SW5 
//----------------------------------------------------------------------------
// INPUT  : void
//----------------------------------------------------------------------------
// OUTPUT : void
//----------------------------------------------------------------------------
// RESOURCES :
//----------------------------------------------------------------------------
// HIST : Version |   Date   | Author          | Description                           
//        --------------------------------------------------------------------
//         01.00  | 12/08/12 |  Ghariani Ahmed | Creation of this function              
//============================================================================


void vCLV_InitExtInt3_Cmd(void)
{
  iClv_PinSw5  = 0;    
  iDirClv_D3   = 0;
  iClv_input3  = 1;
  iClv_EXT3B   = 1;
  iClv_EXT3A   = 1;
  iClv_FlagSw5 = 0;
  iClv_ENBLSw5 = 1;
  FlagSw5 = 0; 
}


//============================================================================
// NAME : vCLV_eSW2_Isr
//============================================================================
// ROLE : Traitement de l'interruption sur le bouton SW2
//----------------------------------------------------------------------------
// INPUT  :void
//----------------------------------------------------------------------------
// OUTPUT : void
//----------------------------------------------------------------------------
// RESOURCES :
//----------------------------------------------------------------------------
// HIST : Version |   Date   | Author           | Description                           
//        --------------------------------------------------------------------
//         01.00  | 12/08/12 |  Ghariani Ahmed  | Creation of this function              
//============================================================================


void vCLV_eSW2(void)
{
  
    if (iClv_FlagSw2)     // check valid interrupt
  {
   iClv_FlagSw2 = 0;
    FlagSw2 = 1; 
    
  }
}


//============================================================================
// NAME : vCLV_eSW3_Isr
//============================================================================
// ROLE : Traitement de l'interruption sur le bouton SW3
//----------------------------------------------------------------------------
// INPUT  :void
//----------------------------------------------------------------------------
// OUTPUT : void
//----------------------------------------------------------------------------
// RESOURCES :
//----------------------------------------------------------------------------
// HIST : Version |   Date   | Author          | Description                           
//        --------------------------------------------------------------------
//         01.00  | 12/08/12 |  Ghariani Ahmed | Creation of this function              
//============================================================================



void vCLV_eSW3(void)
{
  
    if (iClv_FlagSw3)     // check valid interrupt
  {
    iClv_FlagSw3 = 0;
    FlagSw3 = 1; 
  
  }
}


//============================================================================
// NAME : vCLV_eSW4_Isr
//============================================================================
// ROLE : Traitement de l'interruption sur le bouton SW4
//----------------------------------------------------------------------------
// INPUT  :void
//----------------------------------------------------------------------------
// OUTPUT : void
//----------------------------------------------------------------------------
// RESOURCES :
//----------------------------------------------------------------------------
// HIST : Version |   Date   | Author          | Description                           
//        --------------------------------------------------------------------
//         01.00  | 12/08/12 |  Ghariani Ahmed | Creation of this function              
//============================================================================

  void vCLV_eSW4(void)
{
  
    if (iClv_FlagSw4)     // check valid interrupt
  {
    iClv_FlagSw4 = 0;
    FlagSw4   = 1; 
      }
}
  
//============================================================================
// NAME : vCLV_eSW5_Isr
//============================================================================
// ROLE : Traitement de l'interruption sur le bouton SW5
//----------------------------------------------------------------------------
// INPUT  :void
//----------------------------------------------------------------------------
// OUTPUT : void
//----------------------------------------------------------------------------
// RESOURCES :
//----------------------------------------------------------------------------
// HIST : Version |   Date   | Author          | Description                           
//        --------------------------------------------------------------------
//         01.00  | 12/08/12 |  Ghariani Ahmed | Creation of this function              
//============================================================================


  void vCLV_eSW5(void)
{
  
    if (iClv_FlagSw5)     // check valid interrupt
  {
    iClv_FlagSw5 = 0;
    FlagSw5   = 1; 
     }
}



