#ifndef IMAGE_H
#define IMAGE_H

#include <stdlib.h>

typedef struct {
  size_t width;
  size_t height;
  size_t channels;
  double *data;
} Image;

Image load_image(const char *file_path);
void free_image(Image *img);

Image resize_image(const Image *src, size_t new_width, size_t new_height);

#endif