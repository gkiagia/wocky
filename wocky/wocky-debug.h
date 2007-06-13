
#ifndef __DEBUG_H__
#define __DEBUG_H__

#include "config.h"

#include <glib.h>

#include "wocky-xmpp-stanza.h"

#ifdef ENABLE_DEBUG

G_BEGIN_DECLS

typedef enum
{
  DEBUG_TRANSPORT         = 1 << 0,
  DEBUG_NET               = 1 << 1,
  DEBUG_XMPP_READER       = 1 << 2,
  DEBUG_XMPP_WRITER       = 1 << 3,
  DEBUG_SASL              = 1 << 4,
  DEBUG_SSL               = 1 << 5,
  DEBUG_RMULTICAST        = 1 << 6,
  DEBUG_RMULTICAST_SENDER = 1 << 7,
  DEBUG_MUC_CONNECTION    = 1 << 8,
} DebugFlags;

#define DEBUG_XMPP (DEBUG_XMPP_READER | DEBUG_XMPP_WRITER)

void wocky_debug_set_flags_from_env ();
void wocky_debug_set_flags (DebugFlags flags);
gboolean wocky_debug_flag_is_set (DebugFlags flag);
void wocky_debug (DebugFlags flag, const gchar *format, ...)
    G_GNUC_PRINTF (2, 3);
void wocky_debug_stanza (DebugFlags flag, WockyXmppStanza *stanza,
    const gchar *format, ...)
    G_GNUC_PRINTF (3, 4);

#ifdef DEBUG_FLAG

#define DEBUG(format, ...) \
  wocky_debug(DEBUG_FLAG, "%s: " format, G_STRFUNC, ##__VA_ARGS__)

#define DEBUG_STANZA(stanza, format, ...) \
  wocky_debug_stanza(DEBUG_FLAG, stanza, "%s: " format, G_STRFUNC,\
      ##__VA_ARGS__)

#define DEBUGGING debug_flag_is_set(DEBUG_FLAG)

#endif /* DEBUG_FLAG */

#else /* ENABLE_DEBUG */

#ifdef DEBUG_FLAG

#define DEBUG(format, ...)

#define DEBUG_STANZA(stanza, format, ...)

#define DEBUGGING 0

#define NODE_DEBUG(n, s)

#endif /* DEBUG_FLAG */

#endif /* ENABLE_DEBUG */

G_END_DECLS

#endif