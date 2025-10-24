#include "../include/image.h"
#include <stddef.h>
#include <stdio.h>

int main() {
  Image img = load_image("waterfall.jpg");

  if (!img.data) {
    return 1;
  }

  printf("Image loaded: %ld x %ld\n", img.width, img.height);
  printf("Image channels: %ld\n", img.channels);

  free_image(&img);

  return 0;
}
