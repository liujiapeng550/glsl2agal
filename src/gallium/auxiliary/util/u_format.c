/**************************************************************************
 *
 * Copyright 2010 VMware, Inc.
 * All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sub license, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT.
 * IN NO EVENT SHALL VMWARE AND/OR ITS SUPPLIERS BE LIABLE FOR
 * ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 **************************************************************************/

/**
 * @file
 * Pixel format accessor functions.
 *
 * @author Jose Fonseca <jfonseca@vmware.com>
 */

#include "u_format.h"


void
util_format_read_4f(enum pipe_format format,
                    float *dst, unsigned dst_stride,
                    const void *src, unsigned src_stride,
                    unsigned x, unsigned y, unsigned w, unsigned h)
{
   const struct util_format_description *format_desc;
   const uint8_t *src_row;
   float *dst_row;
   unsigned row_blocks;
   unsigned i;

   format_desc = util_format_description(format);

   assert(x % format_desc->block.width == 0);
   assert(y % format_desc->block.height == 0);

   src_row = (const uint8_t *)src + y*src_stride + x*(format_desc->block.bits/8);
   dst_row = dst;
   row_blocks = (w + format_desc->block.width - 1) / format_desc->block.width;

   for (i = 0; i < h; i += format_desc->block.height) {
      format_desc->unpack_float(dst_row, src_row, row_blocks);
      src_row += src_stride;
      dst_row += dst_stride/sizeof(*dst_row);
   }
}


void
util_format_write_4f(enum pipe_format format,
                     const float *src, unsigned src_stride,
                     void *dst, unsigned dst_stride,
                     unsigned x, unsigned y, unsigned w, unsigned h)
{
   const struct util_format_description *format_desc;
   uint8_t *dst_row;
   const float *src_row;
   unsigned row_blocks;
   unsigned i;

   format_desc = util_format_description(format);

   assert(x % format_desc->block.width == 0);
   assert(y % format_desc->block.height == 0);

   dst_row = (uint8_t *)dst + y*dst_stride + x*(format_desc->block.bits/8);
   src_row = src;
   row_blocks = (w + format_desc->block.width - 1) / format_desc->block.width;

   for (i = 0; i < h; i += format_desc->block.height) {
      format_desc->pack_float(dst_row, src_row, row_blocks);
      dst_row += dst_stride;
      src_row += src_stride/sizeof(*src_row);
   }
}


void
util_format_read_4ub(enum pipe_format format, uint8_t *dst, unsigned dst_stride, const void *src, unsigned src_stride, unsigned x, unsigned y, unsigned w, unsigned h)
{
   const struct util_format_description *format_desc;
   const uint8_t *src_row;
   uint8_t *dst_row;
   unsigned row_blocks;
   unsigned i;

   format_desc = util_format_description(format);

   assert(x % format_desc->block.width == 0);
   assert(y % format_desc->block.height == 0);

   src_row = (const uint8_t *)src + y*src_stride + x*(format_desc->block.bits/8);
   dst_row = dst;
   row_blocks = (w + format_desc->block.width - 1) / format_desc->block.width;

   for (i = 0; i < h; i += format_desc->block.height) {
      format_desc->unpack_8unorm(dst_row, src_row, row_blocks);
      src_row += src_stride;
      dst_row += dst_stride/sizeof(*dst_row);
   }
}


void
util_format_write_4ub(enum pipe_format format, const uint8_t *src, unsigned src_stride, void *dst, unsigned dst_stride, unsigned x, unsigned y, unsigned w, unsigned h)
{
   const struct util_format_description *format_desc;
   uint8_t *dst_row;
   const uint8_t *src_row;
   unsigned row_blocks;
   unsigned i;

   format_desc = util_format_description(format);

   assert(x % format_desc->block.width == 0);
   assert(y % format_desc->block.height == 0);

   dst_row = (uint8_t *)dst + y*dst_stride + x*(format_desc->block.bits/8);
   src_row = src;
   row_blocks = (w + format_desc->block.width - 1) / format_desc->block.width;

   for (i = 0; i < h; i += format_desc->block.height) {
      format_desc->pack_8unorm(dst_row, src_row, row_blocks);
      dst_row += dst_stride;
      src_row += src_stride/sizeof(*src_row);
   }
}
