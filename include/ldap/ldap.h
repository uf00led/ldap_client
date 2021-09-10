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

#ifndef _LDAP_H
#define _LDAP_H

/* pull in lber */
#include "lber.h"

/* include version and API feature defines */
#include "ldap_features.h"

LDAP_BEGIN_DECL

#define LDAP_VERSION3	3

#define LDAP_VERSION_MIN	LDAP_VERSION2
#define	LDAP_VERSION		LDAP_VERSION2
#define LDAP_VERSION_MAX	LDAP_VERSION3

#define LDAP_API_VERSION	3001
#define LDAP_VENDOR_NAME	"OpenLDAP"

/* OpenLDAP API Features */
#define LDAP_API_FEATURE_X_OPENLDAP LDAP_VENDOR_VERSION

#if defined( LDAP_API_FEATURE_X_OPENLDAP_REENTRANT ) || \
	( defined( LDAP_THREAD_SAFE ) && \
		defined( LDAP_API_FEATURE_X_OPENLDAP_THREAD_SAFE ) )
	/* -lldap may or may not be thread safe */
	/* -lldap_r, if available, is always thread safe */
#	define	LDAP_API_FEATURE_THREAD_SAFE 		1
#	define  LDAP_API_FEATURE_SESSION_THREAD_SAFE	1
#	define  LDAP_API_FEATURE_OPERATION_THREAD_SAFE	1
#endif
#if defined( LDAP_THREAD_SAFE ) && \
	defined( LDAP_API_FEATURE_X_OPENLDAP_THREAD_SAFE )
/* #define LDAP_API_FEATURE_SESSION_SAFE	1	*/
/* #define LDAP_API_OPERATION_SESSION_SAFE	1	*/
#endif


#define LDAP_PORT		389		/* ldap:///		default LDAP port */
#define LDAPS_PORT		636		/* ldaps:///	default LDAP over TLS port */

#define LDAP_ROOT_DSE				""
#define LDAP_NO_ATTRS				"1.1"
#define LDAP_ALL_USER_ATTRIBUTES	"*"
#define LDAP_ALL_OPERATIONAL_ATTRIBUTES	"+" /* RFC 3673 */

/* RFC 4511:  maxInt INTEGER ::= 2147483647 -- (2^^31 - 1) -- */
#define LDAP_MAXINT (2147483647)

/*
 * LDAP_OPTions
 *	0x0000 - 0x0fff reserved for api options
 *	0x1000 - 0x3fff reserved for api extended options
 *	0x4000 - 0x7fff reserved for private and experimental options
 */

#define LDAP_OPT_API_INFO			0x0000
#define LDAP_OPT_DESC				0x0001 /* historic */
#define LDAP_OPT_DEREF				0x0002
#define LDAP_OPT_SIZELIMIT			0x0003
#define LDAP_OPT_TIMELIMIT			0x0004
/* 0x05 - 0x07 not defined */
#define LDAP_OPT_REFERRALS			0x0008
#define LDAP_OPT_RESTART			0x0009
/* 0x0a - 0x10 not defined */
#define LDAP_OPT_PROTOCOL_VERSION		0x0011
#define LDAP_OPT_SERVER_CONTROLS		0x0012
#define LDAP_OPT_CLIENT_CONTROLS		0x0013
/* 0x14 not defined */
#define LDAP_OPT_API_FEATURE_INFO		0x0015
/* 0x16 - 0x2f not defined */
#define LDAP_OPT_HOST_NAME			0x0030
#define LDAP_OPT_RESULT_CODE			0x0031
#define LDAP_OPT_ERROR_NUMBER			LDAP_OPT_RESULT_CODE
#define LDAP_OPT_DIAGNOSTIC_MESSAGE		0x0032
#define LDAP_OPT_ERROR_STRING			LDAP_OPT_DIAGNOSTIC_MESSAGE
#define LDAP_OPT_MATCHED_DN			0x0033
/* 0x0034 - 0x3fff not defined */
/* 0x0091 used by Microsoft for LDAP_OPT_AUTO_RECONNECT */
#define LDAP_OPT_SSPI_FLAGS			0x0092
/* 0x0093 used by Microsoft for LDAP_OPT_SSL_INFO */
/* 0x0094 used by Microsoft for LDAP_OPT_REF_DEREF_CONN_PER_MSG */
#define LDAP_OPT_SIGN				0x0095
#define LDAP_OPT_ENCRYPT			0x0096
#define LDAP_OPT_SASL_METHOD			0x0097
/* 0x0098 used by Microsoft for LDAP_OPT_AREC_EXCLUSIVE */
#define LDAP_OPT_SECURITY_CONTEXT		0x0099
/* 0x009A used by Microsoft for LDAP_OPT_ROOTDSE_CACHE */
/* 0x009B - 0x3fff not defined */

/* API Extensions */
#define LDAP_OPT_API_EXTENSION_BASE 0x4000  /* API extensions */

/* OpenLDAP TLS options */
#define LDAP_OPT_X_TLS				0x6000
#define LDAP_OPT_X_TLS_CTX			0x6001	/* OpenSSL CTX* */
#define LDAP_OPT_X_TLS_CACERTFILE	0x6002
#define LDAP_OPT_X_TLS_CACERTDIR	0x6003
#define LDAP_OPT_X_TLS_CERTFILE		0x6004
#define LDAP_OPT_X_TLS_KEYFILE		0x6005
#define LDAP_OPT_X_TLS_REQUIRE_CERT	0x6006
#define LDAP_OPT_X_TLS_PROTOCOL_MIN	0x6007
#define LDAP_OPT_X_TLS_CIPHER_SUITE	0x6008
#define LDAP_OPT_X_TLS_RANDOM_FILE	0x6009
#define LDAP_OPT_X_TLS_SSL_CTX		0x600a	/* OpenSSL SSL* */
#define LDAP_OPT_X_TLS_CRLCHECK		0x600b
#define LDAP_OPT_X_TLS_CONNECT_CB	0x600c
#define LDAP_OPT_X_TLS_CONNECT_ARG	0x600d
#define LDAP_OPT_X_TLS_DHFILE		0x600e
#define LDAP_OPT_X_TLS_NEWCTX		0x600f
#define LDAP_OPT_X_TLS_CRLFILE		0x6010	/* GNUtls only */
#define LDAP_OPT_X_TLS_PACKAGE		0x6011
#define LDAP_OPT_X_TLS_ECNAME		0x6012

#define LDAP_OPT_X_TLS_NEVER	0
#define LDAP_OPT_X_TLS_HARD		1
#define LDAP_OPT_X_TLS_DEMAND	2
#define LDAP_OPT_X_TLS_ALLOW	3
#define LDAP_OPT_X_TLS_TRY		4

#define LDAP_OPT_X_TLS_CRL_NONE	0
#define LDAP_OPT_X_TLS_CRL_PEER	1
#define LDAP_OPT_X_TLS_CRL_ALL	2

/* for LDAP_OPT_X_TLS_PROTOCOL_MIN */
#define LDAP_OPT_X_TLS_PROTOCOL(maj,min)	(((maj) << 8) + (min))
#define LDAP_OPT_X_TLS_PROTOCOL_SSL2		(2 << 8)
#define LDAP_OPT_X_TLS_PROTOCOL_SSL3		(3 << 8)
#define LDAP_OPT_X_TLS_PROTOCOL_TLS1_0		((3 << 8) + 1)
#define LDAP_OPT_X_TLS_PROTOCOL_TLS1_1		((3 << 8) + 2)
#define LDAP_OPT_X_TLS_PROTOCOL_TLS1_2		((3 << 8) + 3)

/* OpenLDAP SASL options */
#define LDAP_OPT_X_SASL_MECH			0x6100
#define LDAP_OPT_X_SASL_REALM			0x6101
#define LDAP_OPT_X_SASL_AUTHCID			0x6102
#define LDAP_OPT_X_SASL_AUTHZID			0x6103
#define LDAP_OPT_X_SASL_SSF				0x6104 /* read-only */
#define LDAP_OPT_X_SASL_SSF_EXTERNAL	0x6105 /* write-only */
#define LDAP_OPT_X_SASL_SECPROPS		0x6106 /* write-only */
#define LDAP_OPT_X_SASL_SSF_MIN			0x6107
#define LDAP_OPT_X_SASL_SSF_MAX			0x6108
#define LDAP_OPT_X_SASL_MAXBUFSIZE		0x6109
#define LDAP_OPT_X_SASL_MECHLIST		0x610a /* read-only */
#define LDAP_OPT_X_SASL_NOCANON			0x610b
#define LDAP_OPT_X_SASL_USERNAME		0x610c /* read-only */
#define LDAP_OPT_X_SASL_GSS_CREDS		0x610d

/* OpenLDAP GSSAPI options */
#define LDAP_OPT_X_GSSAPI_DO_NOT_FREE_CONTEXT      0x6200
#define LDAP_OPT_X_GSSAPI_ALLOW_REMOTE_PRINCIPAL   0x6201

/*
 * OpenLDAP per connection tcp-keepalive settings
 * (Linux only, ignored where unsupported)
 */
#define LDAP_OPT_X_KEEPALIVE_IDLE		0x6300
#define LDAP_OPT_X_KEEPALIVE_PROBES		0x6301
#define LDAP_OPT_X_KEEPALIVE_INTERVAL	0x6302

/* Private API Extensions -- reserved for application use */
#define LDAP_OPT_PRIVATE_EXTENSION_BASE 0x7000  /* Private API inclusive */

/*
 * ldap_get_option() and ldap_set_option() return values.
 * As later versions may return other values indicating
 * failure, current applications should only compare returned
 * value against LDAP_OPT_SUCCESS.
 */
#define LDAP_OPT_SUCCESS	0
#define	LDAP_OPT_ERROR		(-1)

/* option on/off values */
#define LDAP_OPT_ON		((void *) &ber_pvt_opt_on)
#define LDAP_OPT_OFF	((void *) 0)

typedef struct ldapapiinfo {
	int		ldapai_info_version;		/* version of LDAPAPIInfo */
#define LDAP_API_INFO_VERSION	(1)
	int		ldapai_api_version;			/* revision of API supported */
	int		ldapai_protocol_version;	/* highest LDAP version supported */
	char	**ldapai_extensions;		/* names of API extensions */
	char	*ldapai_vendor_name;		/* name of supplier */
	int		ldapai_vendor_version;		/* supplier-specific version * 100 */
} LDAPAPIInfo;

typedef struct ldap_apifeature_info {
	int		ldapaif_info_version;		/* version of LDAPAPIFeatureInfo */
#define LDAP_FEATURE_INFO_VERSION (1)	/* apifeature_info struct version */
	char*	ldapaif_name;				/* LDAP_API_FEATURE_* (less prefix) */
	int		ldapaif_version;			/* value of LDAP_API_FEATURE_... */
} LDAPAPIFeatureInfo;

/*
 * LDAP Control structure
 */
typedef struct ldapcontrol {
	char *			ldctl_oid;			/* numericoid of control */
	struct berval	ldctl_value;		/* encoded value of control */
	char			ldctl_iscritical;	/* criticality */
} LDAPControl;

/* LDAP Controls */
/*	standard track controls */
#define LDAP_CONTROL_MANAGEDSAIT	"2.16.840.1.113730.3.4.2"  /* RFC 3296 */
#define LDAP_CONTROL_PROXY_AUTHZ	"2.16.840.1.113730.3.4.18" /* RFC 4370 */
#define LDAP_CONTROL_SUBENTRIES		"1.3.6.1.4.1.4203.1.10.1"  /* RFC 3672 */

#define LDAP_CONTROL_VALUESRETURNFILTER "1.2.826.0.1.3344810.2.3"/* RFC 3876 */

#define LDAP_CONTROL_ASSERT				"1.3.6.1.1.12"			/* RFC 4528 */
#define LDAP_CONTROL_PRE_READ			"1.3.6.1.1.13.1"		/* RFC 4527 */
#define LDAP_CONTROL_POST_READ			"1.3.6.1.1.13.2"		/* RFC 4527 */

#define LDAP_CONTROL_SORTREQUEST    "1.2.840.113556.1.4.473" /* RFC 2891 */
#define LDAP_CONTROL_SORTRESPONSE	"1.2.840.113556.1.4.474" /* RFC 2891 */

/*	non-standard track controls */
#define LDAP_CONTROL_PAGEDRESULTS	"1.2.840.113556.1.4.319"   /* RFC 2696 */

/* LDAP Content Synchronization Operation -- RFC 4533 */
#define LDAP_SYNC_OID			"1.3.6.1.4.1.4203.1.9.1"
#define LDAP_CONTROL_SYNC		LDAP_SYNC_OID ".1"
#define LDAP_CONTROL_SYNC_STATE	LDAP_SYNC_OID ".2"
#define LDAP_CONTROL_SYNC_DONE	LDAP_SYNC_OID ".3"
#define LDAP_SYNC_INFO			LDAP_SYNC_OID ".4"

#define LDAP_SYNC_NONE					0x00
#define LDAP_SYNC_REFRESH_ONLY			0x01
#define LDAP_SYNC_RESERVED				0x02
#define LDAP_SYNC_REFRESH_AND_PERSIST	0x03

#define LDAP_SYNC_REFRESH_PRESENTS		0
#define LDAP_SYNC_REFRESH_DELETES		1

#define LDAP_TAG_SYNC_NEW_COOKIE		((ber_tag_t) 0x80U)
#define LDAP_TAG_SYNC_REFRESH_DELETE	((ber_tag_t) 0xa1U)
#define LDAP_TAG_SYNC_REFRESH_PRESENT	((ber_tag_t) 0xa2U)
#define	LDAP_TAG_SYNC_ID_SET			((ber_tag_t) 0xa3U)

#define LDAP_TAG_SYNC_COOKIE			((ber_tag_t) 0x04U)
#define LDAP_TAG_REFRESHDELETES			((ber_tag_t) 0x01U)
#define LDAP_TAG_REFRESHDONE			((ber_tag_t) 0x01U)
#define LDAP_TAG_RELOAD_HINT			((ber_tag_t) 0x01U)

#define LDAP_SYNC_PRESENT				0
#define LDAP_SYNC_ADD					1
#define LDAP_SYNC_MODIFY				2
#define LDAP_SYNC_DELETE				3
#define LDAP_SYNC_NEW_COOKIE			4

/* LDAP Experimental (works in progress) Features */
#define LDAP_FEATURE_SUBORDINATE_SCOPE \
	"1.3.6.1.4.1.4203.666.8.1" /* "children" */
#define LDAP_FEATURE_CHILDREN_SCOPE LDAP_FEATURE_SUBORDINATE_SCOPE
/* sasl methods */
#define LDAP_SASL_SIMPLE	((char*)0)
#define LDAP_SASL_NULL		("")

/* authentication methods available */
#define LDAP_AUTH_NONE   ((ber_tag_t) 0x00U) /* no authentication */
#define LDAP_AUTH_SIMPLE ((ber_tag_t) 0x80U) /* context specific + primitive */
#define LDAP_AUTH_SASL   ((ber_tag_t) 0xa3U) /* context specific + constructed */
#define LDAP_AUTH_KRBV4  ((ber_tag_t) 0xffU) /* means do both of the following */
#define LDAP_AUTH_KRBV41 ((ber_tag_t) 0x81U) /* context specific + primitive */
#define LDAP_AUTH_KRBV42 ((ber_tag_t) 0x82U) /* context specific + primitive */

/* search scopes */
#define LDAP_SCOPE_BASE			((ber_int_t) 0x0000)
#define LDAP_SCOPE_BASEOBJECT	LDAP_SCOPE_BASE
#define LDAP_SCOPE_ONELEVEL		((ber_int_t) 0x0001)
#define LDAP_SCOPE_ONE			LDAP_SCOPE_ONELEVEL
#define LDAP_SCOPE_SUBTREE		((ber_int_t) 0x0002)
#define LDAP_SCOPE_SUB			LDAP_SCOPE_SUBTREE
#define LDAP_SCOPE_SUBORDINATE	((ber_int_t) 0x0003) /* OpenLDAP extension */
#define LDAP_SCOPE_CHILDREN		LDAP_SCOPE_SUBORDINATE
#define LDAP_SCOPE_DEFAULT		((ber_int_t) -1)	 /* OpenLDAP extension */

/* substring filter component types */
#define LDAP_SUBSTRING_INITIAL	((ber_tag_t) 0x80U)	/* context specific */
#define LDAP_SUBSTRING_ANY		((ber_tag_t) 0x81U)	/* context specific */
#define LDAP_SUBSTRING_FINAL	((ber_tag_t) 0x82U)	/* context specific */

/*
 * LDAP Result Codes
 */
#define LDAP_SUCCESS				0x00

#define LDAP_RANGE(n,x,y)	(((x) <= (n)) && ((n) <= (y)))

#define LDAP_OPERATIONS_ERROR		0x01
#define LDAP_PROTOCOL_ERROR			0x02
#define LDAP_TIMELIMIT_EXCEEDED		0x03
#define LDAP_SIZELIMIT_EXCEEDED		0x04
#define LDAP_COMPARE_FALSE			0x05
#define LDAP_COMPARE_TRUE			0x06
#define LDAP_AUTH_METHOD_NOT_SUPPORTED	0x07
#define LDAP_STRONG_AUTH_NOT_SUPPORTED	LDAP_AUTH_METHOD_NOT_SUPPORTED
#define LDAP_STRONG_AUTH_REQUIRED	0x08
#define LDAP_STRONGER_AUTH_REQUIRED	LDAP_STRONG_AUTH_REQUIRED
#define LDAP_PARTIAL_RESULTS		0x09	/* LDAPv2+ (not LDAPv3) */

#define	LDAP_REFERRAL				0x0a /* LDAPv3 */
#define LDAP_ADMINLIMIT_EXCEEDED	0x0b /* LDAPv3 */
#define	LDAP_UNAVAILABLE_CRITICAL_EXTENSION	0x0c /* LDAPv3 */
#define LDAP_CONFIDENTIALITY_REQUIRED	0x0d /* LDAPv3 */
#define	LDAP_SASL_BIND_IN_PROGRESS	0x0e /* LDAPv3 */

#define LDAP_ATTR_ERROR(n)	LDAP_RANGE((n),0x10,0x15) /* 16-21 */

#define LDAP_NO_SUCH_ATTRIBUTE		0x10
#define LDAP_UNDEFINED_TYPE			0x11
#define LDAP_INAPPROPRIATE_MATCHING	0x12
#define LDAP_CONSTRAINT_VIOLATION	0x13
#define LDAP_TYPE_OR_VALUE_EXISTS	0x14
#define LDAP_INVALID_SYNTAX			0x15

#define LDAP_NAME_ERROR(n)	LDAP_RANGE((n),0x20,0x24) /* 32-34,36 */

#define LDAP_NO_SUCH_OBJECT			0x20
#define LDAP_ALIAS_PROBLEM			0x21
#define LDAP_INVALID_DN_SYNTAX		0x22
#define LDAP_IS_LEAF				0x23 /* not LDAPv3 */
#define LDAP_ALIAS_DEREF_PROBLEM	0x24

#define LDAP_SECURITY_ERROR(n)	LDAP_RANGE((n),0x2F,0x32) /* 47-50 */

#define LDAP_X_PROXY_AUTHZ_FAILURE	0x2F /* LDAPv3 proxy authorization */
#define LDAP_INAPPROPRIATE_AUTH		0x30
#define LDAP_INVALID_CREDENTIALS	0x31
#define LDAP_INSUFFICIENT_ACCESS	0x32

#define LDAP_SERVICE_ERROR(n)	LDAP_RANGE((n),0x33,0x36) /* 51-54 */

#define LDAP_BUSY					0x33
#define LDAP_UNAVAILABLE			0x34
#define LDAP_UNWILLING_TO_PERFORM	0x35
#define LDAP_LOOP_DETECT			0x36

#define LDAP_UPDATE_ERROR(n)	LDAP_RANGE((n),0x40,0x47) /* 64-69,71 */

#define LDAP_NAMING_VIOLATION		0x40
#define LDAP_OBJECT_CLASS_VIOLATION	0x41
#define LDAP_NOT_ALLOWED_ON_NONLEAF	0x42
#define LDAP_NOT_ALLOWED_ON_RDN		0x43
#define LDAP_ALREADY_EXISTS			0x44
#define LDAP_NO_OBJECT_CLASS_MODS	0x45
#define LDAP_RESULTS_TOO_LARGE		0x46 /* CLDAP */
#define LDAP_AFFECTS_MULTIPLE_DSAS	0x47

#define LDAP_VLV_ERROR				0x4C

#define LDAP_OTHER					0x50

/* LCUP operation codes (113-117) - not implemented */
#define LDAP_CUP_RESOURCES_EXHAUSTED	0x71
#define LDAP_CUP_SECURITY_VIOLATION		0x72
#define LDAP_CUP_INVALID_DATA			0x73
#define LDAP_CUP_UNSUPPORTED_SCHEME		0x74
#define LDAP_CUP_RELOAD_REQUIRED		0x75

/* Cancel operation codes (118-121) */
#define LDAP_CANCELLED				0x76
#define LDAP_NO_SUCH_OPERATION		0x77
#define LDAP_TOO_LATE				0x78
#define LDAP_CANNOT_CANCEL			0x79

/* Assertion control (122) */ 
#define LDAP_ASSERTION_FAILED		0x7A

/* Proxied Authorization Denied (123) */ 
#define LDAP_PROXIED_AUTHORIZATION_DENIED		0x7B

/* Experimental result codes */
#define LDAP_E_ERROR(n)	LDAP_RANGE((n),0x1000,0x3FFF)

/* LDAP Sync (4096) */
#define LDAP_SYNC_REFRESH_REQUIRED		0x1000


/* Private Use result codes */
#define LDAP_X_ERROR(n)	LDAP_RANGE((n),0x4000,0xFFFF)

#define LDAP_X_SYNC_REFRESH_REQUIRED	0x4100 /* defunct */
#define LDAP_X_ASSERTION_FAILED			0x410f /* defunct */

/* for the LDAP No-Op control */
#define LDAP_X_NO_OPERATION				0x410e

/* for the Chaining Behavior control (consecutive result codes requested;
 * see <draft-sermersheim-ldap-chaining> ) */
#ifdef LDAP_CONTROL_X_CHAINING_BEHAVIOR
#define	LDAP_X_NO_REFERRALS_FOUND		0x4110
#define LDAP_X_CANNOT_CHAIN			0x4111
#endif

/* for Distributed Procedures (see <draft-sermersheim-ldap-distproc>) */
#ifdef LDAP_X_DISTPROC_BASE
#define LDAP_X_INVALIDREFERENCE			0x4112
#endif

/* API Error Codes
 *
 * Based on draft-ietf-ldap-c-api-xx
 * but with new negative code values
 */
#define LDAP_API_ERROR(n)		((n)<0)
#define LDAP_API_RESULT(n)		((n)<=0)

#define LDAP_SERVER_DOWN				(-1)
#define LDAP_LOCAL_ERROR				(-2)
#define LDAP_ENCODING_ERROR				(-3)
#define LDAP_DECODING_ERROR				(-4)
#define LDAP_TIMEOUT					(-5)
#define LDAP_AUTH_UNKNOWN				(-6)
#define LDAP_FILTER_ERROR				(-7)
#define LDAP_USER_CANCELLED				(-8)
#define LDAP_PARAM_ERROR				(-9)
#define LDAP_NO_MEMORY					(-10)
#define LDAP_CONNECT_ERROR				(-11)
#define LDAP_NOT_SUPPORTED				(-12)
#define LDAP_CONTROL_NOT_FOUND			(-13)
#define LDAP_NO_RESULTS_RETURNED		(-14)
#define LDAP_MORE_RESULTS_TO_RETURN		(-15)	/* Obsolete */
#define LDAP_CLIENT_LOOP				(-16)
#define LDAP_REFERRAL_LIMIT_EXCEEDED	(-17)
#define	LDAP_X_CONNECTING			(-18)


/*
 * This structure represents both ldap messages and ldap responses.
 * These are really the same, except in the case of search responses,
 * where a response has multiple messages.
 */

typedef struct ldapmsg LDAPMessage;

/* for modifications */
typedef struct ldapmod {
	int		mod_op;

#define LDAP_MOD_OP			(0x0007)
#define LDAP_MOD_ADD		(0x0000)
#define LDAP_MOD_DELETE		(0x0001)
#define LDAP_MOD_REPLACE	(0x0002)
#define LDAP_MOD_INCREMENT	(0x0003) /* OpenLDAP extension */
#define LDAP_MOD_BVALUES	(0x0080)
/* IMPORTANT: do not use code 0x1000 (or above),
 * it is used internally by the backends!
 * (see ldap/servers/slapd/slap.h)
 */

	char		*mod_type;
	union mod_vals_u {
		char		**modv_strvals;
		struct berval	**modv_bvals;
	} mod_vals;
#define mod_values	mod_vals.modv_strvals
#define mod_bvalues	mod_vals.modv_bvals
} LDAPMod;

/*
 * structure representing an ldap session which can
 * encompass connections to multiple servers (in the
 * face of referrals).
 */
typedef struct ldap LDAP;

#define LDAP_DEREF_NEVER		0x00
#define LDAP_DEREF_SEARCHING	0x01
#define LDAP_DEREF_FINDING		0x02
#define LDAP_DEREF_ALWAYS		0x03

#define LDAP_NO_LIMIT			0

/* how many messages to retrieve results for */
#define LDAP_MSG_ONE			0x00
#define LDAP_MSG_ALL			0x01
#define LDAP_MSG_RECEIVED		0x02

/*
 * types for ldap URL handling
 */
typedef struct ldap_url_desc {
	struct ldap_url_desc *lud_next;
	char	*lud_scheme;
	char	*lud_host;
	int		lud_port;
	char	*lud_dn;
	char	**lud_attrs;
	int		lud_scope;
	char	*lud_filter;
	char	**lud_exts;
	int		lud_crit_exts;
} LDAPURLDesc;

#define LDAP_URL_SUCCESS		0x00	/* Success */
#define LDAP_URL_ERR_MEM		0x01	/* can't allocate memory space */
#define LDAP_URL_ERR_PARAM		0x02	/* parameter is bad */

#define LDAP_URL_ERR_BADSCHEME	0x03	/* URL doesn't begin with "ldap[si]://" */
#define LDAP_URL_ERR_BADENCLOSURE 0x04	/* URL is missing trailing ">" */
#define LDAP_URL_ERR_BADURL		0x05	/* URL is bad */
#define LDAP_URL_ERR_BADHOST	0x06	/* host port is bad */
#define LDAP_URL_ERR_BADATTRS	0x07	/* bad (or missing) attributes */
#define LDAP_URL_ERR_BADSCOPE	0x08	/* scope string is invalid (or missing) */
#define LDAP_URL_ERR_BADFILTER	0x09	/* bad or missing filter */
#define LDAP_URL_ERR_BADEXTS	0x0a	/* bad or missing extensions */

/*
 * LDAP sync (RFC4533) API
 */

typedef struct ldap_sync_t ldap_sync_t;

typedef enum {
	/* these are private - the client should never see them */
	LDAP_SYNC_CAPI_NONE		= -1,

	LDAP_SYNC_CAPI_PHASE_FLAG	= 0x10U,
	LDAP_SYNC_CAPI_IDSET_FLAG	= 0x20U,
	LDAP_SYNC_CAPI_DONE_FLAG	= 0x40U,

	/* these are passed to ls_search_entry() */
	LDAP_SYNC_CAPI_PRESENT		= LDAP_SYNC_PRESENT,
	LDAP_SYNC_CAPI_ADD		= LDAP_SYNC_ADD,
	LDAP_SYNC_CAPI_MODIFY		= LDAP_SYNC_MODIFY,
	LDAP_SYNC_CAPI_DELETE		= LDAP_SYNC_DELETE,

	/* these are passed to ls_intermediate() */
	LDAP_SYNC_CAPI_PRESENTS		= ( LDAP_SYNC_CAPI_PHASE_FLAG | LDAP_SYNC_CAPI_PRESENT ),
	LDAP_SYNC_CAPI_DELETES		= ( LDAP_SYNC_CAPI_PHASE_FLAG | LDAP_SYNC_CAPI_DELETE ),

	LDAP_SYNC_CAPI_PRESENTS_IDSET	= ( LDAP_SYNC_CAPI_PRESENTS | LDAP_SYNC_CAPI_IDSET_FLAG ),
	LDAP_SYNC_CAPI_DELETES_IDSET	= ( LDAP_SYNC_CAPI_DELETES | LDAP_SYNC_CAPI_IDSET_FLAG ),

	LDAP_SYNC_CAPI_DONE		= ( LDAP_SYNC_CAPI_DONE_FLAG | LDAP_SYNC_CAPI_PRESENTS )
} ldap_sync_refresh_t;

/*
 * Called when an entry is returned by ldap_result().
 * If phase is LDAP_SYNC_CAPI_ADD or LDAP_SYNC_CAPI_MODIFY,
 * the entry has been either added or modified, and thus
 * the complete view of the entry should be in the LDAPMessage.
 * If phase is LDAP_SYNC_CAPI_PRESENT or LDAP_SYNC_CAPI_DELETE,
 * only the DN should be in the LDAPMessage.
 */
typedef int (*ldap_sync_search_entry_f) LDAP_P((
	ldap_sync_t			*ls,
	LDAPMessage			*msg,
	struct berval			*entryUUID,
	ldap_sync_refresh_t		phase ));

/*
 * Called when a reference is returned; the client should know 
 * what to do with it.
 */
typedef int (*ldap_sync_search_reference_f) LDAP_P((
	ldap_sync_t			*ls,
	LDAPMessage			*msg ));

/*
 * Called when specific intermediate/final messages are returned.
 * If phase is LDAP_SYNC_CAPI_PRESENTS or LDAP_SYNC_CAPI_DELETES,
 * a "presents" or "deletes" phase begins.
 * If phase is LDAP_SYNC_CAPI_DONE, a special "presents" phase
 * with refreshDone set to "TRUE" has been returned, to indicate
 * that the refresh phase of a refreshAndPersist is complete.
 * In the above cases, syncUUIDs is NULL.
 *
 * If phase is LDAP_SYNC_CAPI_PRESENTS_IDSET or 
 * LDAP_SYNC_CAPI_DELETES_IDSET, syncUUIDs is an array of UUIDs
 * that are either present or have been deleted.
 */
typedef int (*ldap_sync_intermediate_f) LDAP_P((
	ldap_sync_t			*ls,
	LDAPMessage			*msg,
	BerVarray			syncUUIDs,
	ldap_sync_refresh_t		phase ));

/*
 * Called when a searchResultDone is returned.  In refreshAndPersist,
 * this can only occur if the search for any reason is being terminated
 * by the server.
 */
typedef int (*ldap_sync_search_result_f) LDAP_P((
	ldap_sync_t			*ls,
	LDAPMessage			*msg,
	int				refreshDeletes ));

/*
 * This structure contains all information about the persistent search;
 * the caller is responsible for connecting, setting version, binding, tls...
 */
struct ldap_sync_t {
	/* conf search params */
	char				*ls_base;
	int				ls_scope;
	char				*ls_filter;
	char				**ls_attrs;
	int				ls_timelimit;
	int				ls_sizelimit;

	/* poll timeout */
	int				ls_timeout;

	/* helpers - add as appropriate */
	ldap_sync_search_entry_f	ls_search_entry;
	ldap_sync_search_reference_f	ls_search_reference;
	ldap_sync_intermediate_f	ls_intermediate;
	ldap_sync_search_result_f	ls_search_result;

	/* set by the caller as appropriate */
	void				*ls_private;

	/* conn stuff */
	LDAP				*ls_ld;

	/* --- the parameters below are private - do not modify --- */

	/* FIXME: make the structure opaque, and provide an interface
	 * to modify the public values? */

	/* result stuff */
	int				ls_msgid;

	/* sync stuff */
	/* needed by refreshOnly */
	int				ls_reloadHint;

	/* opaque - need to pass between sessions, updated by the API */
	struct berval			ls_cookie;

	/* state variable - do not modify */
	ldap_sync_refresh_t		ls_refreshPhase;
};

/*
 * End of LDAP sync (RFC4533) API
 */

/*
 * Connection callbacks...
 */

struct ldap_conncb;
struct sockaddr;

/* Called after a connection is established */
typedef int (ldap_conn_add_f) LDAP_P(( LDAP *ld, Sockbuf *sb, LDAPURLDesc *srv, struct sockaddr *addr,
	struct ldap_conncb *ctx ));
/* Called before a connection is closed */
typedef void (ldap_conn_del_f) LDAP_P(( LDAP *ld, Sockbuf *sb, struct ldap_conncb *ctx ));

/* Callbacks are pushed on a stack. Last one pushed is first one executed. The
 * delete callback is called with a NULL Sockbuf just before freeing the LDAP handle.
 */
typedef struct ldap_conncb {
	ldap_conn_add_f *lc_add;
	ldap_conn_del_f *lc_del;
	void *lc_arg;
} ldap_conncb;

/*
 * The API draft spec says we should declare (or cause to be declared)
 * 'struct timeval'.   We don't.  See IETF LDAPext discussions.
 */
struct timeval;

/*
 * in options.c:
 */
LDAP_F( int )
ldap_get_option LDAP_P((
	LDAP *ld,
	int option,
	void *outvalue));

LDAP_F( int )
ldap_set_option LDAP_P((
	LDAP *ld,
	int option,
	LDAP_CONST void *invalue));

/* V3 URLLIST Function Callback Prototype */
typedef int (LDAP_URLLIST_PROC) LDAP_P((
	LDAP *ld, 
	LDAPURLDesc **urllist,
	LDAPURLDesc **url,
	void *params ));

/*
 * in dnssrv.c:
 */
LDAP_F( int )
ldap_domain2dn LDAP_P((
	LDAP_CONST char* domain,
	char** dn ));

/*
 * in sasl.c:
 */
LDAP_F( int )
ldap_sasl_bind LDAP_P((
	LDAP			*ld,
	LDAP_CONST char	*dn,
	LDAP_CONST char	*mechanism,
	struct berval	*cred,
	LDAPControl		**serverctrls,
	LDAPControl		**clientctrls,
	int				*msgidp ));

#define LDAP_SASL_AUTOMATIC		0U
#define LDAP_SASL_INTERACTIVE	1U
#define LDAP_SASL_QUIET			2U

typedef int (LDAP_SASL_INTERACT_PROC) LDAP_P((
	LDAP *ld, unsigned flags, void* defaults, void *interact ));

LDAP_F( int )
ldap_sasl_bind_s LDAP_P((
	LDAP			*ld,
	LDAP_CONST char	*dn,
	LDAP_CONST char	*mechanism,
	struct berval	*cred,
	LDAPControl		**serverctrls,
	LDAPControl		**clientctrls,
	struct berval	**servercredp ));

/*
 * in error.c:
 */
LDAP_F( int )
ldap_parse_result LDAP_P((
	LDAP			*ld,
	LDAPMessage		*res,
	int				*errcodep,
	char			**matcheddnp,
	char			**errmsgp,
	char			***referralsp,
	LDAPControl		***serverctrls,
	int				freeit ));

LDAP_F( char * )
ldap_err2string LDAP_P((
	int err ));

LDAP_F( int )
ldap_initialize LDAP_P((
	LDAP **ldp,
	LDAP_CONST char *url ));

/*
 * in tls.c
 */

LDAP_F( int )
ldap_start_tls LDAP_P((
	LDAP *ld,
	LDAPControl **serverctrls,
	LDAPControl **clientctrls,
	int *msgidp ));

LDAP_F( int )
ldap_start_tls_s LDAP_P((
	LDAP *ld,
	LDAPControl **serverctrls,
	LDAPControl **clientctrls ));

/*
 * in getentry.c:
 */
LDAP_F( LDAPMessage * )
ldap_first_entry LDAP_P((
	LDAP *ld,
	LDAPMessage *chain ));

LDAP_F( LDAPMessage * )
ldap_next_entry LDAP_P((
	LDAP *ld,
	LDAPMessage *entry ));

LDAP_F( int )
ldap_count_entries LDAP_P((
	LDAP *ld,
	LDAPMessage *chain ));

/*
 * in addentry.c
 */
LDAP_F( LDAPMessage * )
ldap_delete_result_entry LDAP_P((
	LDAPMessage **list,
	LDAPMessage *e ));

LDAP_F( void )
ldap_add_result_entry LDAP_P((
	LDAPMessage **list,
	LDAPMessage *e ));

/*
 * in getdn.c
 */
LDAP_F( char * )
ldap_get_dn LDAP_P((
	LDAP *ld,
	LDAPMessage *entry ));

/* DN formats */
#define LDAP_DN_FORMAT_LDAP			0x0000U
#define LDAP_DN_FORMAT_LDAPV3		0x0010U
#define LDAP_DN_FORMAT_LDAPV2		0x0020U
#define LDAP_DN_FORMAT_DCE			0x0030U
#define LDAP_DN_FORMAT_MASK			0x00F0U

LDAP_F( int )
ldap_get_dn_ber LDAP_P((
	LDAP *ld, LDAPMessage *e, BerElement **berout, struct berval *dn ));

LDAP_F( int )
ldap_get_attribute_ber LDAP_P((
	LDAP *ld, LDAPMessage *e, BerElement *ber, struct berval *attr,
	struct berval **vals ));

/*
 * in getattr.c
 */
LDAP_F( char * )
ldap_first_attribute LDAP_P((
	LDAP *ld,
	LDAPMessage *entry,
	BerElement **ber ));

LDAP_F( char * )
ldap_next_attribute LDAP_P((
	LDAP *ld,
	LDAPMessage *entry,
	BerElement *ber ));


/*
 * in getvalues.c
 */
LDAP_F( struct berval ** )
ldap_get_values_len LDAP_P((
	LDAP *ld,
	LDAPMessage *entry,
	LDAP_CONST char *target ));

LDAP_F( int )
ldap_count_values_len LDAP_P((
	struct berval **vals ));

LDAP_F( void )
ldap_value_free_len LDAP_P((
	struct berval **vals ));

/*
 * in result.c:
 */
LDAP_F( int )
ldap_result LDAP_P((
	LDAP *ld,
	int msgid,
	int all,
	struct timeval *timeout,
	LDAPMessage **result ));

LDAP_F( int )
ldap_msgfree LDAP_P((
	LDAPMessage *lm ));

LDAP_F( int )
ldap_msgdelete LDAP_P((
	LDAP *ld,
	int msgid ));


/*
 * in search.c:
 */
LDAP_F( int )
ldap_bv2escaped_filter_value LDAP_P(( 
	struct berval *in, 
	struct berval *out ));

LDAP_F( int )
ldap_search_ext LDAP_P((
	LDAP			*ld,
	LDAP_CONST char	*base,
	int				scope,
	LDAP_CONST char	*filter,
	char			**attrs,
	int				attrsonly,
	LDAPControl		**serverctrls,
	LDAPControl		**clientctrls,
	struct timeval	*timeout,
	int				sizelimit,
	int				*msgidp ));

LDAP_F( int )
ldap_search_ext_s LDAP_P((
	LDAP			*ld,
	LDAP_CONST char	*base,
	int				scope,
	LDAP_CONST char	*filter,
	char			**attrs,
	int				attrsonly,
	LDAPControl		**serverctrls,
	LDAPControl		**clientctrls,
	struct timeval	*timeout,
	int				sizelimit,
	LDAPMessage		**res ));

/*
 * in unbind.c
 */
LDAP_F( int )
ldap_unbind_ext LDAP_P((
	LDAP			*ld,
	LDAPControl		**serverctrls,
	LDAPControl		**clientctrls));

LDAP_F( int )
ldap_unbind_ext_s LDAP_P((
	LDAP			*ld,
	LDAPControl		**serverctrls,
	LDAPControl		**clientctrls));

LDAP_F( int )
ldap_destroy LDAP_P((
	LDAP			*ld));

/*
 * in free.c
 */

LDAP_F( void * )
ldap_memalloc LDAP_P((
	ber_len_t s ));

LDAP_F( void * )
ldap_memrealloc LDAP_P((
	void* p,
	ber_len_t s ));

LDAP_F( void * )
ldap_memcalloc LDAP_P((
	ber_len_t n,
	ber_len_t s ));

LDAP_F( void )
ldap_memfree LDAP_P((
	void* p ));

LDAP_F( void )
ldap_memvfree LDAP_P((
	void** v ));

LDAP_F( char * )
ldap_strdup LDAP_P((
	LDAP_CONST char * ));

LDAP_F( void )
ldap_mods_free LDAP_P((
	LDAPMod **mods,
	int freemods ));

/*
 * in url.c
 */
LDAP_F( int )
ldap_is_ldap_url LDAP_P((
	LDAP_CONST char *url ));

LDAP_F( int )
ldap_is_ldaps_url LDAP_P((
	LDAP_CONST char *url ));

LDAP_F( int )
ldap_is_ldapi_url LDAP_P((
	LDAP_CONST char *url ));

LDAP_F( int )
ldap_url_parse LDAP_P((
	LDAP_CONST char *url,
	LDAPURLDesc **ludpp ));

LDAP_F( char * )
ldap_url_desc2str LDAP_P((
	LDAPURLDesc *ludp ));

LDAP_F( void )
ldap_free_urldesc LDAP_P((
	LDAPURLDesc *ludp ));

/*
 * LDAP Who Am I?
 *	in whoami.c
 */

LDAP_F( int )
ldap_whoami LDAP_P(( LDAP *ld,
	LDAPControl		**sctrls,
	LDAPControl		**cctrls,
	int				*msgidp ));

LDAP_F( int )
ldap_whoami_s LDAP_P((
	LDAP *ld,
	struct berval **authzid,
	LDAPControl **sctrls,
	LDAPControl **cctrls ));

#endif /* _LDAP_H */
