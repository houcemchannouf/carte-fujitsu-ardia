/************************************************************************/
/*               (C) Fujitsu Microelectronics Europe GmbH               */
/*                                                                      */
/* The following software deliverable is intended for and must only be  */
/* used in an evaluation laboratory environment.                        */
/* It is provided without charge and therefore provided on an as-is     */
/* basis, subject to alterations.                                       */
/*                                                                      */
/* The software deliverable is to be used exclusively in connection     */
/* with FME products.                                                   */
/* In the event the software deliverable includes the use of open       */
/* source components, the provisions of the governing open source       */
/* license agreement shall apply with respect to such software          */
/* deliverable.                                                         */
/* FME does not warrant that the deliverables do not infringe any       */
/* third party intellectual property right (IPR). In the event that     */
/* the deliverables infringe a third party IPR it is the sole           */
/* responsibility of the customer to obtain necessary licenses to       */
/* continue the usage of the deliverable.                               */
/*                                                                      */
/* To the maximum extent permitted by applicable law FME disclaims all  */
/* warranties, whether express or implied, in particular, but not       */
/* limited to, warranties of merchantability and fitness for a          */
/* particular purpose for which the deliverable is not designated.      */
/*                                                                      */
/* To the maximum extent permitted by applicable law, FME's liability   */
/* is restricted to intention and gross negligence.                     */
/* FME is not liable for consequential damages.                         */
/*                                                                      */
/* (V1.2)                                                               */
/************************************************************************/

/* -------------------------------------------------------------------------
  VECTORS.C
  - Interrupt level (priority) setting
  - Interrupt vector definition
-----------------------------------------------------------------------------*/


extern void InitIrqLevels(void);

extern  __interrupt void DefaultIRQHandler (void);
extern  __interrupt void IRQHandler_EI0 (void);



 


extern  __interrupt  void vVec_eEXT0_Isr (void);
extern  __interrupt  void vVec_eEXT1_Isr (void);

extern  __interrupt  void vVec_eEXT2_Isr (void);
extern  __interrupt  void vVec_eEXT3_Isr (void);
extern  __interrupt void RX_USART0_isr(void);

extern  __interrupt void TX_USART0_isr(void); 
extern  __interrupt void vVec_eCAN0RX_Isr(void);