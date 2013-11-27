/*  
 * This file provides the api of bitmap.
 * bitmap: a form of hash, using one bit to present an int number.
 *
 *  FileName:    bitmap.h
 *  Description: bitmap related functions  api declarations.
 *  Author:      wzb (zhongbo.wzb@alibaba-inc.com)
 *  Date:        2013-11-25 16:12
 *  Version:     0.1
 *
 * */

#ifndef _BITMAP_H__
#define _BITMAP_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct _bitmap {
  /* bitmap: byte array */
  unsigned char *bitmap; 

  /* bitmap bit size: bytes = (size >> 3) + ((size & 0x7) ? 1 : 1)*/                
  size_t size;           

  /* set bitmap the index-th bit to 1 */
  void (*set)(struct _bitmap *bitmap, size_t index);

  /* clear bitmap the index-th bit to 0 */
  void (*clear)(struct _bitmap *bitmap, size_t index);

  /* set all bits of bitmap  to 1 */
  void (*set_all)(struct _bitmap *bitmap);

  /* clear all bits of bitmap  to 0 */
  void (*clear_all)(struct _bitmap *bitmap);
  
  /* test bitmap the index-th bit is 1 or 0 */
  int  (*test)(struct _bitmap *bitmap, size_t index);

} bitmap_t;


/* create size bits bitmap */
bitmap_t *bitmap_create(size_t size);

/* destroy the unused bitmap */
void bitmap_destroy(bitmap_t *bitmap);

/* set bitmap the index-th bit to 1 */
void bitmap_set(bitmap_t *bitmap, size_t index);

/* clear bitmap the index-th bit to 0 */
void bitmap_clear(bitmap_t *bitmap, size_t index);

/* test bitmap the index-th bit is 1 or 0 */
int  bitmap_test(bitmap_t *bitmap, size_t index);

/* set all bits of bitmap  to 1 */
void bitmap_set_all(bitmap_t *bitmap);

/* clear all bits of bitmap  to 0 */
void bitmap_clear_all(bitmap_t *bitmap);


#endif /* endif of _BITMAP_H__ */
