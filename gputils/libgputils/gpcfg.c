/* gpcfg.c - header file for pic object files
   Copyright (C) 2006
   Michael Ballbach

    Copyright (C) 2014 Molnar Karoly <molnarkaroly@users.sf.net>

This file is part of gputils.

Gputils is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

Gputils is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with gputils; see the file COPYING. If not, write to
the Free Software Foundation, 59 Temple Place - Suite 330,
Boston, MA 02111-1307, USA.  */

#include "stdhdr.h"

#include "gpcfg.h"

/*------------------------------------------------------------------------------------------------*/

static int
cmp(const void *P1, const void *P2) {
  const gp_cfg_device_t *d1 = P1;
  const gp_cfg_device_t *d2 = P2;

  return strcasecmp(d1->name, d2->name);
}

/*------------------------------------------------------------------------------------------------*/

/* Locate a PIC configuration device structure by name. */

const gp_cfg_device_t *
gp_cfg_find_pic(const char *Pic) {
  gp_cfg_device_t fake_dev = { NULL, 0, NULL };

  fake_dev.name = Pic;
  return (const gp_cfg_device_t *)bsearch(&fake_dev, gp_cfg_devices, gp_cfg_device_count,
                                          sizeof(gp_cfg_device_t), cmp);
}

/*------------------------------------------------------------------------------------------------*/

/* Locate a PIC by name, pass a list of names to use, try each in order. */

const gp_cfg_device_t *
gp_cfg_find_pic_multi_name(unsigned int Count, const char *const *Pics) {
  unsigned int t;

  for (t = 0; t < Count; t++) {
    const gp_cfg_device_t *dev = gp_cfg_find_pic(Pics[t]);

    if (dev != NULL) {
      return dev;
    }
  }

  return NULL;
}

/*------------------------------------------------------------------------------------------------*/

/* Find a configuration directive in a processor's config db. */

const gp_cfg_directive_t *
gp_cfg_find_directive(const gp_cfg_device_t *Device, const char *Dname,
                      unsigned int *Out_config_addr, unsigned short *Out_def_value) {
  unsigned int t, u;
  const gp_cfg_addr_t *addr;
  const gp_cfg_directive_t *dir;

  for (t = Device->address_count, addr = Device->addresses; t; ++addr, --t) {
    for (u = addr->directive_count, dir = addr->directives; u; ++dir, --u) {
      if (strcasecmp(Dname, dir->name) == 0) {
        if (Out_config_addr != NULL) {
          *(Out_config_addr) = addr->address;
        }

        if (Out_def_value != NULL) {
          *(Out_def_value) = addr->def_value;
        }

        return dir;
      }
    }
  }

  return NULL;
}

/*------------------------------------------------------------------------------------------------*/

/* Locate an option for a directive. Return it or NULL. */

const gp_cfg_option_t *
gp_cfg_find_option(const gp_cfg_directive_t *Directive, const char *Option) {
  unsigned int t;
  const gp_cfg_option_t **opt;

  for (t = Directive->option_count, opt = Directive->options; t; ++opt, --t) {
    if (strcasecmp((*opt)->name, Option) == 0) {
      return *opt;
    }
  }

  return NULL;
}

/*------------------------------------------------------------------------------------------------*/

/* Return 0xffff or the default for the address and device passed. */

unsigned short
gp_cfg_get_default(const gp_cfg_device_t *Device, unsigned int Address) {
  unsigned int t;
  const gp_cfg_addr_t *addr;

  for (t = Device->address_count, addr = Device->addresses; t; ++addr, --t) {
    if (addr->address == Address) {
      return addr->def_value;
    }
  }

  return 0xFFFF;
}
