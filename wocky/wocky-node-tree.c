/*
 * wocky-node-tree.c - Source for WockyNodeTree
 * Copyright (C) 2006-2010 Collabora Ltd.
 * @author Sjoerd Simons <sjoerd@luon.net>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "wocky-node-tree.h"

G_DEFINE_TYPE(WockyNodeTree, wocky_node_tree, G_TYPE_OBJECT)

/* properties */
enum {
  PROP_TOP_NODE = 1,
};

struct _WockyNodeTreePrivate
{
  gboolean dispose_has_run;
};

static void
wocky_node_tree_init (WockyNodeTree *self)
{
  self->priv = G_TYPE_INSTANCE_GET_PRIVATE (self, WOCKY_TYPE_NODE_TREE,
      WockyNodeTreePrivate);
  /* allocate any data required by the object here */
  self->node = NULL;
}

static void wocky_node_tree_dispose (GObject *object);
static void wocky_node_tree_finalize (GObject *object);

static void
wocky_node_tree_set_property (GObject *object,
    guint property_id,
    const GValue *value,
    GParamSpec *pspec)
{
  WockyNodeTree *self = WOCKY_NODE_TREE (object);

  switch (property_id)
    {
      case PROP_TOP_NODE:
        self->node = g_value_get_pointer (value);
        g_warn_if_fail (self->node != NULL);
        break;
      default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
        break;
    }
}

static void
wocky_node_tree_get_property (GObject *object,
    guint property_id,
    GValue *value,
    GParamSpec *pspec)
{
  WockyNodeTree *self = WOCKY_NODE_TREE (object);

  switch (property_id)
    {
      case PROP_TOP_NODE:
        g_value_set_pointer (value, self->node);
        break;
      default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
        break;
    }
}

static void
wocky_node_tree_class_init (WockyNodeTreeClass *wocky_node_tree_class)
{
  GObjectClass *object_class = G_OBJECT_CLASS (wocky_node_tree_class);
  GParamSpec *param_spec;

  g_type_class_add_private (wocky_node_tree_class,
    sizeof (WockyNodeTreePrivate));

  object_class->dispose = wocky_node_tree_dispose;
  object_class->finalize = wocky_node_tree_finalize;

  object_class->set_property = wocky_node_tree_set_property;
  object_class->get_property = wocky_node_tree_get_property;

  param_spec = g_param_spec_pointer ("top-node", "top-node",
    "The topmost node of the node-tree",
    G_PARAM_CONSTRUCT_ONLY | G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS);

  g_object_class_install_property (object_class, PROP_TOP_NODE,
    param_spec);
}

void
wocky_node_tree_dispose (GObject *object)
{
  WockyNodeTree *self = WOCKY_NODE_TREE (object);
  WockyNodeTreePrivate *priv = self->priv;

  if (priv->dispose_has_run)
    return;

  priv->dispose_has_run = TRUE;

  /* release any references held by the object here */

  if (G_OBJECT_CLASS (wocky_node_tree_parent_class)->dispose)
    G_OBJECT_CLASS (wocky_node_tree_parent_class)->dispose (object);
}

void
wocky_node_tree_finalize (GObject *object)
{
  WockyNodeTree *self = WOCKY_NODE_TREE (object);

  /* free any data held directly by the object here */
  wocky_node_free (self->node);

  G_OBJECT_CLASS (wocky_node_tree_parent_class)->finalize (object);
}