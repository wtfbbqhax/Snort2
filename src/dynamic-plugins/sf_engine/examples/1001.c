/*
 * VRT RULES
 *
 * Copyright (C) 2014-2022 Cisco and/or its affiliates. All rights reserved.
 * Copyright (C) 2005-2013 Sourcefire, Inc.
 *
 * This file is autogenerated via rules2c, by Brian Caswell <bmc@sourcefire.com>
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "sf_snort_plugin_api.h"
#include "sf_snort_packet.h"
#include "detection_lib_meta.h"

/* declare detection functions */
int rule1001eval(void *p);

/* declare rule data structures */
/* precompile the stuff that needs pre-compiled */
/* flow for sid 1001 */
/* flow:established, to_server; */
static FlowFlags rule1001flow1 =
{
    FLOW_ESTABLISHED|FLOW_TO_SERVER
};

static RuleOption rule1001option1 =
{
    OPTION_TYPE_FLOWFLAGS,
    { &rule1001flow1 }
};

/* content for sid 1001 */
// content:"/carbo.dll", payload uri;
static ContentInfo rule1001content2 =
{
    (u_int8_t *)("/carbo.dll"), /* pattern (now in snort content format) */
    0, /* depth */
    0, /* offset */
    CONTENT_BUF_URI, /* flags */ // XXX - need to add CONTENT_FAST_PATTERN support
    NULL, /* holder for boyer/moore PTR */
    NULL, /* more holder info - byteform */
    0, /* byteform length */
    0, /* increment length*/
    0,                      /* holder for fp offset */
    0,                      /* holder for fp length */
    0,                      /* holder for fp only */
    NULL, // offset_refId
    NULL, // depth_refId
    NULL, // offset_location
    NULL  // depth_location
};

static RuleOption rule1001option2 =
{
    OPTION_TYPE_CONTENT,
    { &rule1001content2 }
};

// content:"icatcommand=", nocase;
static ContentInfo rule1001content3 =
{
    (u_int8_t *)("icatcommand="), /* pattern (now in snort content format) */
    0, /* depth */
    0, /* offset */
    CONTENT_NOCASE|CONTENT_BUF_NORMALIZED, /* flags */ // XXX - need to add CONTENT_FAST_PATTERN support
    NULL, /* holder for boyer/moore PTR */
    NULL, /* more holder info - byteform */
    0, /* byteform length */
    0, /* increment length*/
    0,                      /* holder for fp offset */
    0,                      /* holder for fp length */
    0,                      /* holder for fp only */
    NULL, // offset_refId
    NULL, // depth_refId
    NULL, // offset_location
    NULL  // depth_location
};

static RuleOption rule1001option3 =
{
    OPTION_TYPE_CONTENT,
    { &rule1001content3 }
};


/* references for sid 1001 */
static RuleReference *rule1001refs[] =
{
    NULL
};

RuleOption *rule1001options[] =
{
    &rule1001option1,
    &rule1001option2,
    &rule1001option3,
    NULL
};

Rule rule1001 = {

   /* rule header, akin to => tcp any any -> any any               */{
       IPPROTO_TCP, /* proto */
       "$EXTERNAL_NET", /* SRCIP     */
       "any", /* SRCPORT   */
       0, /* DIRECTION */
       "$HTTP_SERVERS", /* DSTIP     */
       "$HTTP_PORTS", /* DSTPORT   */
   },
   /* metadata */
   {
       RULE_GID,  /* genid (HARDCODED!!!) */
       1001, /* sigid */
       7, /* revision */

       "attempted-recon", /* classification */
       0,  /* hardcoded priority XXX NOT PROVIDED BY GRAMMAR YET! */
       "WEB-MISC carbo.dll access",     /* message */
       rule1001refs, /* ptr to references */
       NULL /* Meta data */
   },
   rule1001options, /* ptr to rule options */
    NULL,                               /* Use internal eval func */
    0,                                  /* Not initialized */
    0,                                  /* Rule option count, used internally */
    0,                                  /* Flag with no alert, used internally */
    NULL /* ptr to internal data... setup during rule registration */
};



/* detection functions */

int rule1001eval(void *p) {
    /* cursors, formally known as doe_ptr */
    const u_int8_t *cursor_normal = 0;
    const u_int8_t *cursor_uri = 0;

    /* flow:established, to_server; */
    if (checkFlow(p, rule1001options[0]->option_u.flowFlags)) {
        // content:"/carbo.dll", payload uri;
        if (contentMatch(p, rule1001options[1]->option_u.content, &cursor_uri) > 0) {
            // content:"icatcommand=", nocase;
            if (contentMatch(p, rule1001options[2]->option_u.content, &cursor_normal) > 0) {
                return RULE_MATCH;
            }
        }
    }
    return RULE_NOMATCH;
}

