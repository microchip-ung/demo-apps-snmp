/*

  Vitesse Switch API software.

 Copyright (c) 2002-2013 Vitesse Semiconductor Corporation "Vitesse". All
 Rights Reserved.

 Unpublished rights reserved under the copyright laws of the United States of
 America, other countries and international treaties. Permission to use, copy,
 store and modify, the software and its source code is granted. Permission to
 integrate into other products, disclose, transmit and distribute the software
 in an absolute machine readable format (e.g. HEX file) is also granted.  The
 source code of the software may not be disclosed, transmitted or distributed
 without the written permission of Vitesse. The software and its source code
 may only be used in products utilizing the Vitesse switch products.

 This copyright notice must appear in any copy, modification, disclosure,
 transmission or distribution of the software. Vitesse retains all ownership,
 copyright, trade secret and proprietary rights in the software.

 THIS SOFTWARE HAS BEEN PROVIDED "AS IS," WITHOUT EXPRESS OR IMPLIED WARRANTY
 INCLUDING, WITHOUT LIMITATION, IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS
 FOR A PARTICULAR USE AND NON-INFRINGEMENT.

*/

//#include <vtss_types.h>

#include <vtss/appl/types.h>
#include <misc_api.h>
#include <conf_api.h>
/* #include <cyg/infra/diag.h> */
#ifdef VTSS_SW_OPTION_ICFG
#include <icfg_api.h>
#endif

#include "demo_api.h"

extern "C" void demo_mib_init();
extern "C" void demo_json_init();

extern "C" int demo_icli_cmd_register();

mesa_rc demo_init(vtss_init_data_t *data)
{

    switch (data->cmd) {

    case INIT_CMD_INIT:

#ifdef VTSS_SW_OPTION_PRIVATE_MIB
      demo_mib_init();
#endif
      
#ifdef VTSS_SW_OPTION_JSON_RPC
      demo_json_init();
#endif

      demo_icli_cmd_register();
        break;

    default:
        break;
    }


    return VTSS_RC_OK;
}
