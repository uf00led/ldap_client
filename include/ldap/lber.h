/* $OpenLDAP$ */
/* This work is part of OpenLDAP Software <http://www.openldap.org/>.
 *
 * Copyright 1998-2020 The OpenLDAP Foundation.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted only as authorized by the OpenLDAP
 * Public License.
 *
 * A copy of this license is available in file LICENSE in the
 * top-level directory of the distribution or, alternatively, at
 * <http://www.OpenLDAP.org/license.html>.
 */
/* Portions Copyright (c) 1990 Regents of the University of Michigan.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted
 * provided that this notice is preserved and that due credit is given
 * to the University of Michigan at Ann Arbor. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
 */

#ifndef _LBER_H
#define _LBER_H

#include "lber_types.h"
#include <string.h>

LDAP_BEGIN_DECL

#define LBER_OPT_SUCCESS	(0)
#define LBER_OPT_ERROR		(-1)

typedef struct berelement BerElement;
typedef struct sockbuf    Sockbuf;
typedef struct sockbuf_io Sockbuf_IO;

typedef struct berval {
	ber_len_t	bv_len;
	char		*bv_val;
} BerValue;

typedef BerValue *BerVarray;	/* To distinguish from a single bv */

LBER_F( void )
ber_free LDAP_P((
	BerElement *ber,
	int freebuf ));

LDAP_END_DECL

#endif /* _LBER_H */
