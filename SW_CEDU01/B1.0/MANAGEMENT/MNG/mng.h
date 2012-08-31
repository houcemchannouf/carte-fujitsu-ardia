//############################################################################//
// HEAD : (c) ARDIA 2012 : " Any copie and re-utilisation of this file without  
//                           the written consent of ARDIA is forbidden "        
//        --------------------------------------------------------------------  
//        Classification :  (-)No   (-)Confident. ARDIA   (-)Confident. Client  
//        --------------------------------------------------------------------  
//        --------------------------------------------------------------------  
//        Module name : mng
//############################################################################//
// FILE : com_mng.h
//----------------------------------------------------------------------------//
// DESC : Module description
//----------------------------------------------------------------------------//
// LIST : * List of the functions
//----------------------------------------------------------------------------//
// HIST : Version |   Date   | Author | Description                             
//----------------------------------------------------------------------------//
//         01.10  |          |        | Creation of this file
//
//############################################################################//

void vCOM_MNG_DecodeTrame_exe(unsigned char ucRXCHAR);       
void vCOM_MNG_SEND_DATA_exe(void);
int vCOM_MNG_Verif_Parametre_exe(void);
int vCOM_MNG_Verif_Trame_exe(void);  
void vCOM_MNG_IHM_Espion_exe(void); 
void vCOM_MNG_Init_exe(void)  ;  

//############################################################################//
// structure de la trame
//############################################################################//

#define  SOF_CHAR     0x24 //$

#define  FR_REQ_ID    0x80 // request frame id  Pc --> espion
#define  FR_RES_ID    0x86 // response  frame id  espion --> pc
#define  FR_DATA_ID    0x90 // data broadcast frame id espion --> pc

// service ID
//----------------------------------------------------------------------------
// PC ----> ESPION      
        
#define  SID_START_CONNEXION                        0x00 //( Demande de connexion pc --> espion)
#define  SID_SET_PROTOCOL_SETTINGS_CAN              0x01 //( CAN PROTOCOL SETTINGS)
#define  SID_SET_PROTOCOL_SETTINGS_SPI              0x02 //(SPI PROTOCOL SETTINGS) ( Zone data à redéfinir )
#define  SID_SET_PROTOCOL_SETTINGS_I2C              0x03 //(I2C PROTOCOL SETTINGS) ( Zone data à redéfinir )
#define  SID_SET_PROTOCOL_SETTINGS_LIN              0x04  //(LIN PROTOCOL SETTINGS) ( Zone data à redéfinir )
#define  SID_START_DATA_BROADCAST                       0x05 //(START DATA  BROADCAST)
#define  SID_STOP_DATA_BROADCAST                          0x06 //(STOP DATA  BROADCAST)
        
// ESPION-----> PC  ( Positive responses)       
        
#define  SID_START_CONNEXION_PR                     0x30 //( espion ready)
#define  SID_SET_PROTOCOL_SETTINGS_PR               0x31 //(Correct protocol settings )
#define  SID_START_DATA_BROADCAST_PR                0x32 //(start data broadcast PR)
#define  SID_STOP_DATA_BROADCAST_PR                 0x33 //(stop data broadcast PR)

#define  SID_DATA_BROADCAST_CAN                     0x71 //( CAN DATA)
#define  SID_DATA_BROADCAST_SPI                     0x72 //( SPI DATA) ( uniquement pour test -zode data à redéfinir )
#define  SID_DATA_BROADCAST_I2C                     0x73 //( I2C DATA)  ( uniquement pour test -zode data à redéfinir )
#define  SID_DATA_BROADCAST_LIN                     0x74 //( LIN DATA)  ( uniquement pour test -zode data à redéfinir )
        
                
// ESPION-----> PC  ( NEGATIVE responses)       
        
#define  SID_START_CONNEXION_NR                     0x50 // (espion not ready)
#define  SID_SET_PROTOCOL_SETTINGS_NR_PNS           0x51  //( protocol not  supported)
#define  SID_SET_PROTOCOL_SETTINGS_NR_POR           0x52  //(parameter out of range)
#define  SID_START_DATA_BROADCAST_NR                0x53 // (data broadcast NR)
#define  SID_STOP_DATA_BROADCAST_NR                 0x54 // (stop data broadcast PR) espion not ready
        

//############################################################################//
// vCOM_MNG_DecodeTrame_exe   : liste des etats de l' automate
//############################################################################//

// cas possible de l'automate ucComMng_CurrentState

#define ucComMng_STATE_Decode_SOF          0
#define ucComMng_STATE_Decode_FrID         1
#define ucComMng_STATE_Decode_SrvID        2
#define ucComMng_STATE_Decode_Data_length  3
#define ucComMng_STATE_GET_Data            4
#define ucComMng_STATE_GET_CS              5
 



//############################################################################//
// vCOM_MNG_SEND_DATA_exe  : liste des etats de l' automate emission
//############################################################################//

// cas possible de l'automate ucComMng_CurrentSendState
 
#define  SEND_State_Repos                             0
#define  SEND_START_CONNEXION_PR                     1 //( espion ready)
#define  SEND_SET_PROTOCOL_SETTINGS_PR               2 //(Correct protocol settings )
#define  SEND_START_DATA_BROADCAST_PR                3 //(start data broadcast PR)
#define  SEND_STOP_DATA_BROADCAST_PR                 4 //(stop data broadcast PR)
#define  SEND_DATA_BROADCAST_CAN                     5 //( CAN DATA)
#define  SEND_DATA_BROADCAST_SPI                     6 //( SPI DATA) ( uniquement pour test -zode data à redéfinir )
#define  SEND_DATA_BROADCAST_I2C                     7 //( I2C DATA)  ( uniquement pour test -zode data à redéfinir )
#define  SEND_DATA_BROADCAST_LIN                     8 //( LIN DATA)  ( uniquement pour test -zode data à redéfinir )

#define  SEND_START_CONNEXION_NR                     9 // (espion not ready)
#define  SEND_SET_PROTOCOL_SETTINGS_NR_PNS           10  //( protocol not  supported)
#define  SEND_SET_PROTOCOL_SETTINGS_NR_POR           11  //(parameter out of range)
#define  SEND_START_DATA_BROADCAST_NR                12 // (data broadcast NR)
#define  SEND_STOP_DATA_BROADCAST_NR                 13 // (stop data broadcast PR) espion not ready


//############################################################################//
// vCOM_MNG_Espion_exe   : liste des etats de l' automate
//############################################################################//

// cas possible de l'automate ucEtat_IHM_Espion

#define Espion_Wait_Start_Frame                0
#define Espion_Wait_Setting_Frame              1
#define Espion_Wait_Start_Send_Data_Frame      2
#define Espion_Wait_Stop_Send_Data_Frame       3
#define Espion_BAD_CS                          4
#define Espion_START_CONNEXION_PR              5
#define Espion_START_CONNEXION_NR              6
#define Espion_SET_PROTOCOL_SETTINGS_PR        7
#define Espion_SET_PROTOCOL_SETTINGS_NR_PNS    8
#define Espion_SET_PROTOCOL_SETTINGS_NR_POR    9
#define Espion_START_DATA_BROADCAST_PR         10
#define Espion_STOP_DATA_BROADCAST_PR          11
#define Espion_IHM_IDLE                        12 // pas besoin de refaire l'affichage

//############################################################################//
// vCOM_MNG_DecodeTrame_exe   : liste des Baudrates CAN
//############################################################################//

#define Baudrate_100            0
#define Baudrate_125            1
#define Baudrate_250            2
#define Baudrate_500            3
#define Baudrate_1_M            4
//===================================
#define DulBTR_8M_20k8_24_66_4     0x7ECF     // BTR config 20.83 kBaud 
#define DulBTR_8M_33K0_22_68_4     0x6DCA     // BTR config 33.05 kBaud 
#define DulBTR_8M_33K3_20_70_4     0x7EC9     // BTR config 33.33 kBaud 
#define DulBTR_8M_83K3_24_66_4     0x7EC3     // BTR config 83.33 kBaud 
#define DulBTR_8M_100k_20_70_4     0x5CC3     // BTR config 100.0 kBaud 
#define DulBTR_8M_125k_16_68_3     0x4983     // BTR config 125.0 kBaud 
#define DulBTR_8M_250k_16_68_3     0x2B01     // BTR config 250.0 kBaud 
#define DulBTR_8M_500k_16_68_3     0x1B00    // BTR config 500.0 kBaud 
#define DulBTR_8M_1M00_16_68_3     0x2300     // BTR config   1.0 MBaud  
        