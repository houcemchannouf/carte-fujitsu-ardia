//############################################################################//
// HEAD : (c) ARDIA 2012 : " Any copie and re-utilisation of this file without  
//                           the written consent of ARDIA is forbidden "        
//        --------------------------------------------------------------------  
//        Classification :  (-)No   (-)Confident. ARDIA   (-)Confident. Client  
//        --------------------------------------------------------------------  
//        --------------------------------------------------------------------  
//        Module name : ADC_DRV  
//############################################################################//
// FILE : ADC_DRV.C (SOURCE)
//----------------------------------------------------------------------------//
// DESC : Module description
//----------------------------------------------------------------------------//
// LIST : * List of the functions
//----------------------------------------------------------------------------//
// HIST : Version |   Date   |   Author         | Description                             
//----------------------------------------------------------------------------//
//         01.00  | 20/08/12|  Ghariani Ahmed  | Creation of this file
//
//############################################################################//

//****************************************************************************//
// INCLIB
//****************************************************************************//

//****************************************************************************//
// INCUSER
//****************************************************************************//

#include "..\SW_CEDU01\B1.0\SYSTEME\REG\mb96348rs.h"
#include "..\SW_CEDU01\B1.0\DRIVERS\ADC_DRV\ADC_DRV.cfg"

void InitADC (void);
void vIrq_ADC(void);