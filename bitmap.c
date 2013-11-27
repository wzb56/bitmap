/*  
 * This file provides the implementation of the api of bitmap.
 * bitmap: a form of hash, using one bit to present an int number.
 *
 *  FileName:    bitmap.c
 *  Description: bitmap related  api implementation.
 *  Author:      wzb (zhongbo.wzb@alibaba-inc.com)
 *  Date:        2013-11-25 16:13
 *  Version:     0.1
 *
 * */

#include "bitmap.h"

/* 1st: used the index to locate the 8 bits block( bytes index);
 *
 * 2nd: used the index to locate the offset in the 8 bits block;
 *
 * */

/* 1 byte = 8 bits = 2^3 bits */
#define SHIFT 3  
#define MASK 0x7

static void set(bitmap_t *bitmap, size_t index) 
{
  bitmap->bitmap[index >> SHIFT] |= 1 << (index & MASK);
}

static void clear(bitmap_t *bitmap, size_t index) 
{
  bitmap->bitmap[index >> SHIFT] &= ~(1 << (index & MASK));
}

static int test(bitmap_t *bitmap, size_t index) 
{
  return (bitmap->bitmap[index >> SHIFT] & (1 << (index & MASK))) >> (index & MASK);
}

static void set_all(bitmap_t *bitmap) 
{
  memset(bitmap->bitmap, 0xff, (bitmap->size >> SHIFT) + ((bitmap->size & MASK) ? 1 : 1));
}

static void clear_all(bitmap_t *bitmap) 
{
  memset(bitmap->bitmap, 0x00, (bitmap->size >> SHIFT) + ((bitmap->size & MASK) ? 1 : 1));
}

/**
 * N.B.: if bitmap.size == 2^power, the problem is :
 *  1.if bitmap allocate bytes = (bitmap.size >> 3) + ((bitmap.size & 0x7) ? 1 : 0);
 *    eg: bitmap.size = 8 bits, bitmap allocate bytes = (8 >> 3) + ((8 & 0x7) ? 1 : 0) = 1 + 0 = 1;
 *    only 1 bytes allocated, 
 *    namely 8bits: bit:0 bit:1 bit:2 bit:3 bit:4 bit:5 bit:6 bit:7, 
 *    not include bit:8, therefore, we can't do bitmap_set(bitmap, bitmap.size);
 *
 * 2. resolve the above problem (edge case):
 *  bitmap allocate bytes = (bitmap.size >> 3) + ((bitmap.size & 0x7) ? 1 : 1);
 *  when bitmap.size == 2^power, we also allocate another extra bytes too.
 *
 * */

bitmap_t *bitmap_create(size_t size) 
{
  if(size == 0) return NULL;

  bitmap_t *bitmap = (bitmap_t *) malloc(sizeof(bitmap_t));
  if (bitmap == NULL) {
    fprintf(stderr, "Error: out of memory, memory not enough!\n");
    exit(0);
  }

  size_t bytes = (size >> SHIFT) + ((size & MASK) ? 1 : 1);
  void *map = malloc(bytes);
  if (map == NULL) {
    free(bitmap);
    fprintf(stderr, "Error: out of memory, memory not enough!\n");
    exit(0);
  }
  memset(map, 0, bytes);

  bitmap->bitmap = map;
  bitmap->size   = size;
  bitmap->set    = set;
  bitmap->clear  = clear;
  bitmap->test   = test;

  bitmap->set_all   = set_all;
  bitmap->clear_all = clear_all;

  return bitmap;
}

void bitmap_destroy(bitmap_t *bitmap)
{
  if (bitmap) {
    if (bitmap->bitmap) {
      free(bitmap->bitmap);
    }
    free(bitmap);
  }
}

void bitmap_set(bitmap_t *bitmap, size_t index)
{
  bitmap->set(bitmap, index);
}

void bitmap_clear(bitmap_t *bitmap, size_t index)
{
  bitmap->clear(bitmap, index);
}

int bitmap_test(bitmap_t *bitmap, size_t index)
{
  return bitmap->test(bitmap, index);
}

void bitmap_set_all(bitmap_t *bitmap)
{
  bitmap->set_all(bitmap);
}

void bitmap_clear_all(bitmap_t *bitmap)
{
  bitmap->clear_all(bitmap);
}

