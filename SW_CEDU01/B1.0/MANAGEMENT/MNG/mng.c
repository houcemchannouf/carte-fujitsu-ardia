//############################################################################//
// HEAD : (c) ARDIA 2010 : " Any copie and re-utilisation of this file without  
//                           the written consent of ARDIA is forbidden "        
//        --------------------------------------------------------------------  
//        Classification :  (-)No   (-)Confident. ARDIA   (-)Confident. Client  
//        --------------------------------------------------------------------  
//        --------------------------------------------------------------------  
//        Module name : com_mng
//############################################################################//
// FILE : com_mng.c
//----------------------------------------------------------------------------//
// DESC : Module description
//----------------------------------------------------------------------------//
// LIST : * List of the functions
//----------------------------------------------------------------------------//
// HIST : Version |   Date   | Author | Description                             
//----------------------------------------------------------------------------//
//         01.00  |          |        | Creation of this file
//
//############################################################################//
#include "..\..\..\Systeme\Reg\mb96346rs.h"
#include "..\..\..\MANAGEMENT\COM_MNG\B1.0\com_mng.h"
#include "..\..\..\systeme\variables\near_var.h"
#include "..\..\..\DRIVERS\AS0_DRV\B1.0\AS0_DRV.h"
#include "..\..\..\DRIVERS\LCD_DRV\B1.0\LCD_DRV.h"


//############################################################################//
// Function :   vCOM_MNG_DecodeTrame_exe
// INPUT : 
// OUTPUT : 
//----------------------------------------------------------------------------//
// HIST : Version |   Date   | Author | Description                             
//----------------------------------------------------------------------------//
//         01.00  |          |        | Creation of this function
//############################################################################//
//pour envoyer une chaine de caratères 

void vCOM_MNG_Init_exe(void)       
{

   ucComMng_CurrentState=ucComMng_STATE_Decode_SOF;
   ucComMng_CurrentSendState =SEND_State_Repos;
   ucEtat_IHM_Espion=Espion_Wait_Start_Frame;


}

//############################################################################//
// Function :   vCOM_MNG_Verif_Parametre_exe
// INPUT : 
// OUTPUT : 
//----------------------------------------------------------------------------//
// HIST : Version |   Date   | Author | Description                             
//----------------------------------------------------------------------------//
//         01.00  |          |        | Creation of this function
//############################################################################//

int vCOM_MNG_Verif_Parametre_exe(void)
{

 if(ucAS0_RXbuf[4]==0x00)
 {
  ucFlag_CAN=1;
//  CAN_EXTENDED=0;
 }
 else if (ucAS0_RXbuf[4]==0x01)
 {
  //CAN_EXTENDED=1;
  ucFlag_CAN=0;
 }
 else
  return 0;
 switch (ucAS0_RXbuf[5])
 { 
  case Baudrate_100:
       ulBaudRate=DulBTR_8M_100k_20_70_4;
       break;
  case Baudrate_125:
       ulBaudRate=DulBTR_8M_125k_16_68_3;
       break;
  case Baudrate_250:
       ulBaudRate=DulBTR_8M_250k_16_68_3;
       break;
  case Baudrate_500:
       ulBaudRate=DulBTR_8M_500k_16_68_3;
       break;
  case Baudrate_1_M:
       ulBaudRate=DulBTR_8M_1M00_16_68_3;
       break;
  default: return 0; break;
 }
 // Mask 01 :
CAN_MASK1= 0x00000000;
CAN_MASK1= ucAS0_RXbuf[9];
CAN_MASK1 = (CAN_MASK1 << 8) + ucAS0_RXbuf[8];
CAN_MASK1 = (CAN_MASK1 << 8) + ucAS0_RXbuf[7];
CAN_MASK1 = (CAN_MASK1 << 8) + ucAS0_RXbuf[6];
 // Mask 02 :
CAN_MASK2= 0x00000000;
CAN_MASK2= ucAS0_RXbuf[13];
CAN_MASK2 = (CAN_MASK2 << 8) + ucAS0_RXbuf[12];
CAN_MASK2 = (CAN_MASK2 << 8) + ucAS0_RXbuf[11];
CAN_MASK2 = (CAN_MASK2 << 8) + ucAS0_RXbuf[10];
 // Mask 03 :
CAN_MASK3= 0x00000000;
CAN_MASK3= ucAS0_RXbuf[17];
CAN_MASK3 = (CAN_MASK3 << 8) + ucAS0_RXbuf[16];
CAN_MASK3 = (CAN_MASK3 << 8) + ucAS0_RXbuf[15];
CAN_MASK3 = (CAN_MASK3 << 8) + ucAS0_RXbuf[14]; 
// Mask 04 :
CAN_MASK4= 0x00000000;
CAN_MASK4= ucAS0_RXbuf[21];
CAN_MASK4 = (CAN_MASK4 << 8) + ucAS0_RXbuf[20];
CAN_MASK4 = (CAN_MASK4 << 8) + ucAS0_RXbuf[19];
CAN_MASK4 = (CAN_MASK4 << 8) + ucAS0_RXbuf[18]; 
 return 1; 
}


//############################################################################//
// Function :   vCOM_MNG_Verif_Trame_exe
// INPUT : 
// OUTPUT : 
//----------------------------------------------------------------------------//
// HIST : Version |   Date   | Author | Description                             
//----------------------------------------------------------------------------//
//         01.00  |          |        | Creation of this function
//############################################################################//

int vCOM_MNG_Verif_Trame_exe(void)
{
unsigned char ln =0;
unsigned char cs =0; 
unsigned char indice =0; 
unsigned char sid;
 
ln = ucAS0_RXbuf[3];
//----------------------------------------------------------------------------
//-  step 1 verif cs
//----------------------------------------------------------------------------
if(!ln) // cas len =0
{
cs = ucAS0_RXbuf[4];
if(cs)
        {
  ucEtat_IHM_Espion= Espion_BAD_CS;     
  return(0);
  }
}else // len differenr de 0 donc calcul cs
{
                                                
                        
                        for(indice=3;indice<2+ln;indice++)                      
                        cs=cs+ucAS0_RXbuf[indice];//CS update
 
if(cs!=ucAS0_RXbuf[3+ln])
        {
   ucEtat_IHM_Espion= Espion_BAD_CS; 
   return(0);
  }
                
}

//----------------------------------------------------------------------------
//-  step 2 verif sid
//----------------------------------------------------------------------------
sid = ucAS0_RXbuf[2];

switch (sid)
{
        
case  SID_START_CONNEXION :
        
if(!ucAS0_RXbuf[3])
{
  ucEtat_IHM_Espion= Espion_START_CONNEXION_PR; 
  ucComMng_CurrentSendState =SEND_START_CONNEXION_PR    ;
}
else
{
  ucEtat_IHM_Espion= Espion_START_CONNEXION_NR;
  ucComMng_CurrentSendState =SEND_START_CONNEXION_NR    ;
}
break;

case  SID_SET_PROTOCOL_SETTINGS_CAN :

if(vCOM_MNG_Verif_Parametre_exe())
{
 ucEtat_IHM_Espion= Espion_SET_PROTOCOL_SETTINGS_PR; 
 ucComMng_CurrentSendState =    SEND_SET_PROTOCOL_SETTINGS_PR;
}
else
{
 ucEtat_IHM_Espion= Espion_SET_PROTOCOL_SETTINGS_NR_PNS;
 ucComMng_CurrentSendState =    SEND_SET_PROTOCOL_SETTINGS_NR_PNS;
 //ucComMng_CurrentSendState =  SEND_SET PROTOCOL_SETTINGS_NR_POR;
}
break;
        
case  SID_SET_PROTOCOL_SETTINGS_SPI : 
        
ucEtat_IHM_Espion= Espion_SET_PROTOCOL_SETTINGS_PR; 
ucComMng_CurrentSendState =     SEND_SET_PROTOCOL_SETTINGS_PR;
// cas de la réponse nagative à définr
// ajouter verif parametres spi si ok reponse positive sinon négative
//ucComMng_CurrentSendState =   SEND_SET_PROTOCOL_SETTINGS_NR_PNS;
//ucComMng_CurrentSendState =   SEND_SET PROTOCOL_SETTINGS_NR_POR;

case  SID_SET_PROTOCOL_SETTINGS_I2C :

ucEtat_IHM_Espion= Espion_SET_PROTOCOL_SETTINGS_PR; 
ucComMng_CurrentSendState =     SEND_SET_PROTOCOL_SETTINGS_PR;
// cas de la réponse nagative à définr
// ajouter verif parametres i2c si ok reponse positive sinon négative
//ucComMng_CurrentSendState =   SEND_SET_PROTOCOL_SETTINGS_NR_PNS;
//ucComMng_CurrentSendState =   SEND_SET PROTOCOL_SETTINGS_NR_POR;

case  SID_SET_PROTOCOL_SETTINGS_LIN :

ucEtat_IHM_Espion= Espion_SET_PROTOCOL_SETTINGS_PR; 
ucComMng_CurrentSendState =     SEND_SET_PROTOCOL_SETTINGS_PR;
// cas de la réponse nagative à définr
// ajouter verif parametres lin si ok reponse positive sinon négative
//ucComMng_CurrentSendState =   SEND_SET_PROTOCOL_SETTINGS_NR_PNS;
//ucComMng_CurrentSendState =   SEND_SET PROTOCOL_SETTINGS_NR_POR;      

case  SID_START_DATA_BROADCAST :

ucEtat_IHM_Espion= Espion_START_DATA_BROADCAST_PR; 
ucComMng_CurrentSendState =     SEND_START_DATA_BROADCAST_PR;
// cas de la réponse nagative à définr
//ucComMng_CurrentSendState =   SEND_START_DATA_BROADCAST_NR;
break;

case  SID_STOP_DATA_BROADCAST :

ucEtat_IHM_Espion= Espion_STOP_DATA_BROADCAST_PR; 
ucComMng_CurrentSendState =     SEND_STOP_DATA_BROADCAST_PR;
// cas de la réponse nagative à définr
//ucComMng_CurrentSendState =   SEND_STOP_DATA_BROADCAST_NR;
break;
        
        
default: ucEtat_IHM_Espion=Espion_Wait_Start_Frame;break;
}
return(0);
  
}
      


//############################################################################//
// Function :   vCOM_MNG_SEND_DATA_exe
// INPUT : 
// OUTPUT : 
//----------------------------------------------------------------------------//
// HIST : Version |   Date   | Author | Description                             
//----------------------------------------------------------------------------//
//         01.00  |          |        | Creation of this function
//############################################################################//

void vCOM_MNG_DecodeTrame_exe(unsigned char ucRXCHAR)       
{

switch(ucComMng_CurrentState)
{

case ucComMng_STATE_Decode_SOF:
      if(ucRXCHAR==SOF_CHAR) //$
      {
      ucAS0_RXptr=0;
      ucAS0_RXbuf[ucAS0_RXptr]=ucRXCHAR;
      ucComMng_CurrentState =ucComMng_STATE_Decode_FrID;
      }      
      break;
                
case ucComMng_STATE_Decode_FrID:
      if(ucRXCHAR==0x80)
      {
      ucAS0_RXptr++;
      ucAS0_RXbuf[ucAS0_RXptr]=ucRXCHAR;
      ucComMng_CurrentState =ucComMng_STATE_Decode_SrvID;
      }
      else
      ucComMng_CurrentState =ucComMng_STATE_Decode_SOF;
      break;
                
case ucComMng_STATE_Decode_SrvID:

      ucAS0_RXptr++;
      ucAS0_RXbuf[ucAS0_RXptr]=ucRXCHAR;
      ucComMng_CurrentState =ucComMng_STATE_Decode_Data_length;

      break;
case ucComMng_STATE_Decode_Data_length:

      ucAS0_RXptr++;
      ucAS0_RXbuf[ucAS0_RXptr]=ucRXCHAR;
      ucNb_Data_ToReceive=ucRXCHAR;
      
      if(ucNb_Data_ToReceive)
      ucComMng_CurrentState =ucComMng_STATE_GET_Data;
      else
      ucComMng_CurrentState =ucComMng_STATE_GET_CS;

  
      break;
                
case ucComMng_STATE_GET_Data:
     
      ucAS0_RXptr++;
      ucAS0_RXbuf[ucAS0_RXptr]=ucRXCHAR;
      ucNb_Data_ToReceive--;
      
      if(!ucNb_Data_ToReceive)
      ucComMng_CurrentState =ucComMng_STATE_GET_CS;
      
 
      break;
                
case ucComMng_STATE_GET_CS:
      
      ucAS0_RXptr++;       
      
      ucAS0_RXbuf[ucAS0_RXptr]=ucRXCHAR;
     
      vCOM_MNG_Verif_Trame_exe();
        

      ucComMng_CurrentState =ucComMng_STATE_Decode_SOF;
   
      break;
                

                

                
default:ucComMng_CurrentState =ucComMng_STATE_Decode_SOF ; break;
}

// automate réception


}




//############################################################################//
// Function :   vCOM_MNG_SEND_DATA_exe
// INPUT : 
// OUTPUT : 
//----------------------------------------------------------------------------//
// HIST : Version |   Date   | Author | Description                             
//----------------------------------------------------------------------------//
//         01.00  |          |        | Creation of this function
//############################################################################//
 

void vCOM_MNG_SEND_DATA_exe()        
{
unsigned char indice;
unsigned char indiceCS;
indice =0;
indiceCS=0;
 switch(ucComMng_CurrentSendState)
 {
 case   SEND_START_CONNEXION_PR:
        
                        ucAS0_TXbuf[indice++]=SOF_CHAR;
                        ucAS0_TXbuf[indice++]=FR_RES_ID;
                        ucAS0_TXbuf[indice++]=SID_START_CONNEXION_PR;
                        ucAS0_TXbuf[indice++]=0x00; // data len
                        ucAS0_TXbuf[indice++]=0x00; //cs
 
                        vAS0_PutString_exe( ucAS0_TXbuf ,indice+1);
                        ucComMng_CurrentSendState=SEND_State_Repos;
                
                        break;
                        
 case   SEND_SET_PROTOCOL_SETTINGS_PR:
        
                        ucAS0_TXbuf[indice++]=SOF_CHAR;
                        ucAS0_TXbuf[indice++]=FR_RES_ID;
                        ucAS0_TXbuf[indice++]=SID_SET_PROTOCOL_SETTINGS_PR;
                        ucAS0_TXbuf[indice++]=0x00; // data len
                        ucAS0_TXbuf[indice++]=0x00; //cs
 
                        vAS0_PutString_exe( ucAS0_TXbuf ,indice+1);
                        ucComMng_CurrentSendState=SEND_State_Repos;
                
                        break;
                        
 case   SEND_START_DATA_BROADCAST_PR:
        
                        ucAS0_TXbuf[indice++]=SOF_CHAR;
                        ucAS0_TXbuf[indice++]=FR_RES_ID;
                        ucAS0_TXbuf[indice++]=SID_START_DATA_BROADCAST_PR;
                        ucAS0_TXbuf[indice++]=0x00; // data len
                        ucAS0_TXbuf[indice++]=0x00; //cs
 
                        vAS0_PutString_exe( ucAS0_TXbuf ,indice+1);
                        ucComMng_CurrentSendState=SEND_DATA_BROADCAST_CAN;
                
                        break;

 case   SEND_STOP_DATA_BROADCAST_PR:
        
                        ucAS0_TXbuf[indice++]=SOF_CHAR;
                        ucAS0_TXbuf[indice++]=FR_RES_ID;
                        ucAS0_TXbuf[indice++]=SID_STOP_DATA_BROADCAST_PR;
                        ucAS0_TXbuf[indice++]=0x00; // data len
                        ucAS0_TXbuf[indice++]=0x00; //cs
 
                        vAS0_PutString_exe( ucAS0_TXbuf ,indice+1);
                        ucComMng_CurrentSendState=SEND_State_Repos;
                
                        break;
                                                                        
 case   SEND_DATA_BROADCAST_CAN:
        
                        ucAS0_TXbuf[indice++]=SOF_CHAR;
                        ucAS0_TXbuf[indice++]=FR_DATA_ID;
                        ucAS0_TXbuf[indice++]=SID_DATA_BROADCAST_CAN;
                        ucAS0_TXbuf[indice++]=13   ; // data len
                        ucAS0_TXbuf[indice++]=(unsigned char)(CAN_Receive_ID>>24); // data 0 // can id byte 3      à remplacer par CAN_Receive_ID byte 3
                        ucAS0_TXbuf[indice++]=(unsigned char)(CAN_Receive_ID>>16);  // data 1 // can id byte 2      à remplacer par CAN_Receive_ID byte 2
                        ucAS0_TXbuf[indice++]=(unsigned char)(CAN_Receive_ID>>8);   // data 2 // can id byte 1      à remplacer par CAN_Receive_ID byte 1
                        ucAS0_TXbuf[indice++]=(unsigned char)(CAN_Receive_ID);   // data 3 // can id byte 0      à remplacer par CAN_Receive_ID  byte 0
                        ucAS0_TXbuf[indice++]=CAN_Receive_Data[0];    // data 4 // can data byte 7        à remplacer par CAN_Receive_Data[0]
                        ucAS0_TXbuf[indice++]=CAN_Receive_Data[1];    // data 5 // can data byte 6        à remplacer par CAN_Receive_Data[1]
                        ucAS0_TXbuf[indice++]=CAN_Receive_Data[2];    // data 6 // can data byte 5      
                        ucAS0_TXbuf[indice++]=CAN_Receive_Data[3];    // data 7 // can data byte 4      
                        ucAS0_TXbuf[indice++]=CAN_Receive_Data[4];    // data 8 // can data byte 3      
                        ucAS0_TXbuf[indice++]=CAN_Receive_Data[5];    // data 9 // can data byte 2      
                        ucAS0_TXbuf[indice++]=CAN_Receive_Data[6];    // data 10 // can data byte 1     
                        ucAS0_TXbuf[indice++]=CAN_Receive_Data[7];    // data 11 // can data byte 0   à remplacer par CAN_Receive_Data[8]
                        ucAS0_TXbuf[indice++]=CAN_Receive_Data[8];    // data 11 // can data byte 0   à remplacer par CAN_Receive_Data[8]
                        ucAS0_TXbuf[indice]=0;    // data 12 // CS                                                      
                        
                        for(indiceCS=3;indiceCS<indice;indiceCS++)                      
                        ucAS0_TXbuf[indice]=ucAS0_TXbuf[indice]+ucAS0_TXbuf[indiceCS];//CS update
 
                        vAS0_PutString_exe( ucAS0_TXbuf ,indice+1);
                        //ucComMng_CurrentSendState reste inchangée
                        //ucComMng_CurrentSendState=SEND_DATA_BROADCAST_CAN;
                  ucComMng_CurrentSendState=SEND_State_Repos; // on attend la procaine trame can
                        break;

 case   SEND_DATA_BROADCAST_SPI:
        
                        ucAS0_TXbuf[indice++]=SOF_CHAR;
                        ucAS0_TXbuf[indice++]=FR_DATA_ID;
                        ucAS0_TXbuf[indice++]=SID_DATA_BROADCAST_SPI;
                        ucAS0_TXbuf[indice++]=0x06; // data len
                        ucAS0_TXbuf[indice++]=0xAA; // data 0  
                        ucAS0_TXbuf[indice++]=0xAA; // data 1  
                        ucAS0_TXbuf[indice++]=0xAA; // data 2  
                        ucAS0_TXbuf[indice++]=0xAA; // data 3  
                        ucAS0_TXbuf[indice++]=0xAA; // data 4  
                        ucAS0_TXbuf[indice++]=0;    // data 5  //Cs
                                                
                        
                        for(indiceCS=3;indiceCS<indice-1;indiceCS++)                    
                        ucAS0_TXbuf[indice-1]=ucAS0_TXbuf[indice-1]+ucAS0_TXbuf[indiceCS];//cs update
 
                        vAS0_PutString_exe( ucAS0_TXbuf ,indice);
                        ucComMng_CurrentSendState=SEND_State_Repos;
                
                        break;


 case   SEND_DATA_BROADCAST_I2C:
        
                        ucAS0_TXbuf[indice++]=SOF_CHAR;
                        ucAS0_TXbuf[indice++]=FR_DATA_ID;
                        ucAS0_TXbuf[indice++]=SID_DATA_BROADCAST_I2C;
                        ucAS0_TXbuf[indice++]=0x06; // data len
                        ucAS0_TXbuf[indice++]=0xBB; // data 0  
                        ucAS0_TXbuf[indice++]=0xBB; // data 1  
                        ucAS0_TXbuf[indice++]=0xBB; // data 2  
                        ucAS0_TXbuf[indice++]=0xBB; // data 3  
                        ucAS0_TXbuf[indice++]=0xBB; // data 4  
                        ucAS0_TXbuf[indice++]=0;    // data 5  //Cs
                                                
                        
                        for(indiceCS=3;indiceCS<indice-1;indiceCS++)                    
                        ucAS0_TXbuf[indice-1]=ucAS0_TXbuf[indice-1]+ucAS0_TXbuf[indiceCS];//cs update
 
                        vAS0_PutString_exe( ucAS0_TXbuf ,indice);
                        ucComMng_CurrentSendState=SEND_State_Repos;
                
                        break;

 case   SEND_DATA_BROADCAST_LIN:
        
                        ucAS0_TXbuf[indice++]=SOF_CHAR;
                        ucAS0_TXbuf[indice++]=FR_DATA_ID;
                        ucAS0_TXbuf[indice++]=SID_DATA_BROADCAST_LIN;
                        ucAS0_TXbuf[indice++]=0x06; // data len
                        ucAS0_TXbuf[indice++]=0xCC; // data 0  
                        ucAS0_TXbuf[indice++]=0xCC; // data 1  
                        ucAS0_TXbuf[indice++]=0xCC; // data 2  
                        ucAS0_TXbuf[indice++]=0xCC; // data 3  
                        ucAS0_TXbuf[indice++]=0xCC; // data 4  
                        ucAS0_TXbuf[indice++]=0;    // data 5  //Cs
                                                
                        
                        for(indiceCS=3;indiceCS<indice-1;indiceCS++)                    
                        ucAS0_TXbuf[indice-1]=ucAS0_TXbuf[indice-1]+ucAS0_TXbuf[indiceCS];//cs update
 
                        vAS0_PutString_exe( ucAS0_TXbuf ,indice);
                        ucComMng_CurrentSendState=SEND_State_Repos;
                
                        break;                  

 case   SEND_START_CONNEXION_NR:
        
                        ucAS0_TXbuf[indice++]=SOF_CHAR;
                        ucAS0_TXbuf[indice++]=FR_RES_ID;
                        ucAS0_TXbuf[indice++]=SID_START_CONNEXION_NR;
                        ucAS0_TXbuf[indice++]=0x00; // data len
                        ucAS0_TXbuf[indice++]=0x00;    //Cs
                                                
                        vAS0_PutString_exe( ucAS0_TXbuf ,indice+1);
                        ucComMng_CurrentSendState=SEND_State_Repos;
                
                        break; 

 case   SEND_SET_PROTOCOL_SETTINGS_NR_PNS:
        
                        ucAS0_TXbuf[indice++]=SOF_CHAR;
                        ucAS0_TXbuf[indice++]=FR_RES_ID;
                        ucAS0_TXbuf[indice++]=SID_SET_PROTOCOL_SETTINGS_NR_PNS;
                        ucAS0_TXbuf[indice++]=0x00; // data len
                        ucAS0_TXbuf[indice++]=0x00;    //Cs
                                                
                        vAS0_PutString_exe( ucAS0_TXbuf ,indice+1);
                        ucComMng_CurrentSendState=SEND_State_Repos;
                
                        break; 
                        
 case   SEND_SET_PROTOCOL_SETTINGS_NR_POR:
        
                        ucAS0_TXbuf[indice++]=SOF_CHAR;
                        ucAS0_TXbuf[indice++]=FR_RES_ID;
                        ucAS0_TXbuf[indice++]=SID_SET_PROTOCOL_SETTINGS_NR_POR ;
                        ucAS0_TXbuf[indice++]=0x00; // data len
                        ucAS0_TXbuf[indice++]=0x00;    //Cs
                                                
                        vAS0_PutString_exe( ucAS0_TXbuf ,indice+1);
                        ucComMng_CurrentSendState=SEND_State_Repos;
                
                        break; 
                        
 case   SEND_START_DATA_BROADCAST_NR:
        
                        ucAS0_TXbuf[indice++]=SOF_CHAR;
                        ucAS0_TXbuf[indice++]=FR_RES_ID;
                        ucAS0_TXbuf[indice++]=SID_START_DATA_BROADCAST_NR;
                        ucAS0_TXbuf[indice++]=0x00; // data len
                        ucAS0_TXbuf[indice++]=0x00;    //Cs
                                                
                        vAS0_PutString_exe( ucAS0_TXbuf ,indice+1);
                        ucComMng_CurrentSendState=SEND_State_Repos;
                
                        break; 
                        
 case   SEND_STOP_DATA_BROADCAST_NR:
        
                        ucAS0_TXbuf[indice++]=SOF_CHAR;
                        ucAS0_TXbuf[indice++]=FR_RES_ID;
                        ucAS0_TXbuf[indice++]=SID_STOP_DATA_BROADCAST_NR;
                        ucAS0_TXbuf[indice++]=0x00; // data len
                        ucAS0_TXbuf[indice++]=0x00;    //Cs
                                                
                        vAS0_PutString_exe( ucAS0_TXbuf ,indice+1);
                        ucComMng_CurrentSendState=SEND_State_Repos;
                
                        break; 
                                                                        
default:  ucComMng_CurrentSendState=SEND_State_Repos;  break;
}


}


//############################################################################//
// Function :   vCOM_MNG_PrintChaine_exe
// INPUT : 
// OUTPUT : 
//----------------------------------------------------------------------------//
// HIST : Version |   Date   | Author | Description                             
//----------------------------------------------------------------------------//
//         01.00  |          |        | Creation of this function
//############################################################################//


void vCOM_MNG_PrintChaine_exe(char *ch)
{
 char First_Line[16] ="                ";
 char Second_Line[16]="                ";
 int lg=0;
 int i;
 lg=strlen(ch);
 for(i=0;i<lg;i++)
 {
  if(i<16)
   First_Line[i]=ch[i];
  else
   Second_Line[i-16]=ch[i];
 }
 vLCD_initLcd_Cmd(); 
 vLCD_iLcdGoto_Cmd(DucLCD_1st_line);
 vLCD_iLcdPrintChaine_Cmd(First_Line);
 vLCD_iLcdGoto_Cmd(DucLCD_2nd_line); 
 vLCD_iLcdPrintChaine_Cmd(Second_Line);
}
 

//############################################################################//
// Function :   vCOM_MNG_Espion_exe
// INPUT : 
// OUTPUT : 
//----------------------------------------------------------------------------//
// HIST : Version |   Date   | Author | Description                             
//----------------------------------------------------------------------------//
//         01.00  |          |        | Creation of this function
//############################################################################//


void vCOM_MNG_IHM_Espion_exe()
{

switch (ucEtat_IHM_Espion)
{

      
case  Espion_Wait_Start_Frame:  // il faut optimiser le code qui se répéte
      
      vCOM_MNG_PrintChaine_exe("Wait Start Frame....");

      break;            
case Espion_Wait_Setting_Frame:

      vCOM_MNG_PrintChaine_exe("Wait   setting  frame....");
     
      break;           
case Espion_Wait_Start_Send_Data_Frame:

      vCOM_MNG_PrintChaine_exe("Wait Start send Data....");

      break;   
case Espion_Wait_Stop_Send_Data_Frame:

      vCOM_MNG_PrintChaine_exe("Wait Stop Send  Data....");

      break;
      
case Espion_BAD_CS: 

      vCOM_MNG_PrintChaine_exe("Bad CS          error");

      break;
      
case Espion_START_CONNEXION_PR:

      vCOM_MNG_PrintChaine_exe("Start Connexion Success");

      break;

case Espion_START_CONNEXION_NR:

      vCOM_MNG_PrintChaine_exe("Start Connexion Failed");

      break;
      
case Espion_SET_PROTOCOL_SETTINGS_PR:

      vCOM_MNG_PrintChaine_exe("PROTOCOL SETTING OK");

      break;
      
      
case Espion_SET_PROTOCOL_SETTINGS_NR_PNS:

      vCOM_MNG_PrintChaine_exe("PROTOCOL SETTING NOK-PNS");

      break;
      
      
case Espion_SET_PROTOCOL_SETTINGS_NR_POR:

      vCOM_MNG_PrintChaine_exe("PROTOCOL SETTING NOK-POR");

      break;
      
case Espion_START_DATA_BROADCAST_PR:
     
      vCOM_MNG_PrintChaine_exe("start  Data     broadcast     OK");
      vCAN0_TEST_EXE(); // on initialise le can pour transmettre ce qu'on reçoit dans l'it CAN
      flag_stop_data=1;
      break;
      
case Espion_STOP_DATA_BROADCAST_PR:

      flag_stop_data=0;
      vCOM_MNG_PrintChaine_exe("Stop  Data      broadcast     OK");

      break;
      
default:ucEtat_IHM_Espion=Espion_Wait_Start_Frame; break;     
}

ucEtat_IHM_Espion=Espion_IHM_IDLE;
}
