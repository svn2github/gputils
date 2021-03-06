/* messaging functions
   Copyright (C) 2003, 2004, 2005
   Craig Franklin

This file is part of gputils.

gputils is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

gputils is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with gputils; see the file COPYING.  If not, write to
the Free Software Foundation, 59 Temple Place - Suite 330,
Boston, MA 02111-1307, USA.  */

#include "stdhdr.h"
#include "libgputils.h"

#ifdef STDC_HEADERS
#include <stdarg.h>
#endif

gp_boolean gp_quiet           = false;
gp_boolean gp_message_disable = false;
gp_boolean gp_debug_disable   = true;

int gp_num_errors   = 0;
int gp_num_warnings = 0;
int gp_num_messages = 0;

static int _real_num_errors   = 0;
static int _real_num_warnings = 0;
static int _real_num_messages = 0;

/*------------------------------------------------------------------------------------------------*/

void
gp_error(const char* Format, ...)
{
  va_list args;
  char    buffer[BUFSIZ];

  _real_num_errors++;

  if (gp_message_disable) {
    return;
  }

  gp_num_errors++;

  if (gp_quiet) {
    return;
  }

  va_start(args, Format);
  vsnprintf(buffer, sizeof(buffer), Format, args);
  va_end(args);

  printf("error: %s\n", buffer);
}

/*------------------------------------------------------------------------------------------------*/

void
gp_warning(const char* Format, ...)
{
  va_list args;
  char    buffer[BUFSIZ];

  _real_num_warnings++;

  if (gp_message_disable) {
    return;
  }

  gp_num_warnings++;

  if (gp_quiet) {
    return;
  }

  va_start(args, Format);
  vsnprintf(buffer, sizeof(buffer), Format, args);
  va_end(args);

  printf("warning: %s\n", buffer);
}

/*------------------------------------------------------------------------------------------------*/

void
gp_message(const char* Format, ...)
{
  va_list args;
  char    buffer[BUFSIZ];

  _real_num_messages++;

  if (gp_message_disable) {
    return;
  }

  gp_num_messages++;

  if (gp_quiet) {
    return;
  }

  va_start(args, Format);
  vsnprintf(buffer, sizeof(buffer), Format, args);
  va_end(args);

  printf("message: %s\n", buffer);
}

/*------------------------------------------------------------------------------------------------*/

void
gp_debug(const char* Format, ...)
{
  va_list args;
  char    buffer[BUFSIZ];

  if (gp_debug_disable) {
    return;
  }

  if (gp_quiet) {
    return;
  }

  va_start(args, Format);
  vsnprintf(buffer, sizeof(buffer), Format, args);
  va_end(args);

  printf("debug: %s\n", buffer);
}

/*------------------------------------------------------------------------------------------------*/

int
gp_real_num_errors(void)
{
  return _real_num_errors;
}

/*------------------------------------------------------------------------------------------------*/

int
gp_real_num_warnings(void)
{
  return _real_num_warnings;
}

/*------------------------------------------------------------------------------------------------*/

int
gp_real_num_messages(void)
{
  return _real_num_messages;
}
