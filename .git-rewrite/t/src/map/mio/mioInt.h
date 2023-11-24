/**CFile****************************************************************

  FileName    [mioInt.h]

  PackageName [MVSIS 2.0: Multi-valued logic synthesis system.]

  Synopsis    [File reading/writing for technology mapping.]

  Author      [MVSIS Group]
  
  Affiliation [UC Berkeley]

  Date        [Ver. 1.0. Started - September 8, 2003.]

  Revision    [$Id: mioInt.h,v 1.4 2004/06/28 14:20:25 alanmi Exp $]

***********************************************************************/

#ifndef ABC__map__mio__mioInt_h
#define ABC__map__mio__mioInt_h


////////////////////////////////////////////////////////////////////////
///                          INCLUDES                                ///
////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "src/misc/vec/vec.h"
#include "src/misc/mem/mem.h"
#include "src/misc/st/st.h"
#include "mio.h"
 
ABC_NAMESPACE_HEADER_START


////////////////////////////////////////////////////////////////////////
///                         PARAMETERS                               ///
////////////////////////////////////////////////////////////////////////

#define    MIO_STRING_GATE       "GATE"
#define    MIO_STRING_PIN        "PIN"
#define    MIO_STRING_NONINV     "NONINV"
#define    MIO_STRING_INV        "INV"
#define    MIO_STRING_UNKNOWN    "UNKNOWN"

#define    MIO_STRING_CONST0     "CONST0"
#define    MIO_STRING_CONST1     "CONST1"
 
// the bit masks
#define    MIO_MASK(n)         ((~((unsigned)0)) >> (32-(n)))
#define    MIO_FULL             (~((unsigned)0))

////////////////////////////////////////////////////////////////////////
///                    STRUCTURE DEFINITIONS                         ///
////////////////////////////////////////////////////////////////////////

struct  Mio_LibraryStruct_t_
{
    char *             pName;       // the name of the library
    int                nGates;      // the number of the gates
    Mio_Gate_t **      ppGates0;    // the array of gates in the original order
    Mio_Gate_t **      ppGatesName; // the array of gates sorted by name
    Mio_Gate_t *       pGates;      // the linked list of all gates in no particular order
    Mio_Gate_t *       pGate0;      // the constant zero gate
    Mio_Gate_t *       pGate1;      // the constant one gate
    Mio_Gate_t *       pGateBuf;    // the buffer
    Mio_Gate_t *       pGateInv;    // the inverter
    Mio_Gate_t *       pGateNand2;  // the NAND2 gate
    Mio_Gate_t *       pGateAnd2;   // the AND2 gate
    st_table *         tName2Gate;  // the mapping of gate names into their pointer
//    DdManager *        dd;          // the nanager storing functions of gates
    Mem_Flex_t *       pMmFlex;     // the memory manaqer for SOPs
    Vec_Str_t *        vCube;       // temporary cube
}; 

struct  Mio_GateStruct_t_
{
    // information derived from the genlib file
    char *             pName;       // the name of the gate
    double             dArea;       // the area of the gate
    char *             pForm;       // the formula describing functionality of the gate
    Mio_Pin_t *        pPins;       // the linked list of all pins (one pin if info is the same)
    char *             pOutName;    // the name of the output pin 
    // the library to which this gate belongs
    Mio_Library_t *    pLib; 
    // the next gate in the list
    Mio_Gate_t *       pNext;    

    // the derived information
    int                nInputs;     // the number of inputs
    double             dDelayMax;   // the maximum delay
//    DdNode *           bFunc;       // the functionality
    char *             pSop;        // sum-of-products
    Vec_Int_t *        vExpr;       // boolean expression
    union { word       uTruth;      // truth table
    word *             pTruth; };   // pointer to the truth table
    int                Value;       // user's information
};

struct  Mio_PinStruct_t_
{
    char *             pName;
    Mio_PinPhase_t     Phase;
    double             dLoadInput;
    double             dLoadMax;
    double             dDelayBlockRise;
    double             dDelayFanoutRise;
    double             dDelayBlockFall;
    double             dDelayFanoutFall;
    double             dDelayBlockMax;
    Mio_Pin_t *        pNext;     
};


////////////////////////////////////////////////////////////////////////
///                       GLOBAL VARIABLES                           ///
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
///                       MACRO DEFINITIONS                          ///
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
///                     FUNCTION DEFINITIONS                         ///
////////////////////////////////////////////////////////////////////////

/*=== mio.c =============================================================*/
/*=== mioRead.c =============================================================*/
/*=== mioUtils.c =============================================================*/


ABC_NAMESPACE_HEADER_END

#endif

////////////////////////////////////////////////////////////////////////
///                       END OF FILE                                ///
////////////////////////////////////////////////////////////////////////
