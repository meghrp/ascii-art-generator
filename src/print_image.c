#include <stdio.h>
#include <stdlib.h>

#include "../include/image.h"

#define VALUE_CHARS " .-=+*x#$&X@"
#define VALUES_COUNT (sizeof(VALUE_CHARS) - 1)

char get_ascii_char(double luminance) {
  size_t index = (size_t)(luminance * VALUES_COUNT);

  if (index >= VALUES_COUNT) {
    return VALUE_CHARS[VALUES_COUNT - 1];
  }

  return VALUE_CHARS[index];
}

void print_image(const Image *img) {

  for (size_t y = 0; y < img->height; y++) {
    for (size_t x = 0; x < img->width; x++) {
      size_t index = (y * img->width + x) * img->channels;
      double r, g, b;

      double lum;
      if (img->channels >= 3) {
        r = img->data[index + 0];
        g = img->data[index + 1];
        b = img->data[index + 2];
        lum = 0.2126 * r + 0.7152 * g + 0.0722 * b;
      } else {
        lum = img->data[index];
      }

      char ascii_char = get_ascii_char(lum);

      printf("\x1b[38;2;%d;%d;%dm%c", (int)(r * 255), (int)(g * 255),
             (int)(b * 255), ascii_char);
    }
    printf("\n");
  }
}