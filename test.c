#include "bitmap.h"


int main(int argc, char *argv[]) 
{
  size_t size;

  for (size = 0; size <= 1024; ++size) {
    bitmap_t *bitmap = bitmap_create(size);

    if (bitmap == NULL) {
      if (size == 0)  {
        continue;
      }

      fprintf(stderr, " NULL pointer, as size = %ld\n", size);
      exit(1);
    }

    size_t index;

#if 0
    printf("\n\n\nbegin set:\n");
    for (index = 0; index < 20; ++index) {
      printf("index = %ld\n", index);
      bitmap->set(bitmap, index); 
      printf("after set index = %ld, bitmap[%ld] = %d \n", 
          index, index >> 3, bitmap->bitmap[index >> 3]);
      printf("test(bitmap, %ld) = %d\n\n", index, bitmap->test(bitmap, index));
    }

    printf("\n\n\nbegin clear:\n");
    for (index = 0; index < 20; ++index) {
      printf("index = %ld\n", index);
      bitmap->clear(bitmap, index); 
      printf("after clear index = %ld, bitmap[%ld] = %d\n", 
          index, index >> 3, bitmap->bitmap[index >> 3]);
      printf("test(bitmap, %ld) = %d\n\n", index, bitmap->test(bitmap, index));
    }
#else
#if 0 
    printf("\n\n\nbegin set:\n");
    size_t index;
    for (index = 0; index < 20; ++index) {
      printf("index = %ld\n", index);
      bitmap_set(bitmap, index); 
      printf("after set index = %ld, bitmap[%ld] = %d \n", 
          index, index >> 3, bitmap->bitmap[index >> 3]);
      printf("test(bitmap, %ld) = %d\n\n", index, bitmap_test(bitmap, index));
    }

    printf("\n\n\nbegin clear:\n");
    for (index = 0; index < 20; ++index) {
      printf("index = %ld\n", index);
      bitmap_clear(bitmap, index); 
      printf("after clear index = %ld, bitmap[%ld] = %d\n", 
          index, index >> 3, bitmap->bitmap[index >> 3]);
      printf("test(bitmap, %ld) = %d\n\n", index, bitmap_test(bitmap, index));
    }
#endif
#endif

    //default bitmap all zeros bits: test api: bitmap_test();
    for (index = 0; index <= bitmap->size; ++index)
    {
      if (bitmap_test(bitmap, index)) {
        fprintf(stderr, "bitmap_test() not worked at index: %ld\n", index);
        exit(1);
      }
    }

    // test api: bitmap_set();
    for (index = 0; index <= bitmap->size; ++index)
    {
      bitmap_set(bitmap, index);
      if (!bitmap_test(bitmap, index)) {
        fprintf(stderr, "bitmap_set() not worked at index: %ld\n", index);
        exit(1);
      }
    }

    // test api: bitmap_clear();
    for (index = 0; index <= bitmap->size; ++index)
    {
      bitmap_clear(bitmap, index);
      if (bitmap_test(bitmap, index)) {
        fprintf(stderr, "bitmap_clear() not worked at index: %ld\n", index);
        exit(1);
      }
    }

    // test api: bitmap_set_all();
    bitmap_set_all(bitmap);
    for (index = 0; index <= bitmap->size; ++index)
    {
      if (!bitmap_test(bitmap, index)) {
        fprintf(stderr, "bitmap_set_all() not worked at index: %ld\n", index);
        exit(1);
      }
    }
    
    // test api: bitmap_clear_all()
    bitmap_clear_all(bitmap);
    for (index = 0; index <= bitmap->size; ++index)
    {
      if (bitmap_test(bitmap, index)) {
        fprintf(stderr, "bitmap_clear_all() not worked at index: %ld\n", index);
        exit(1);
      }
    }

    bitmap_destroy(bitmap);
  }

  return 0;
}
