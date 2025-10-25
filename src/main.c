#include "../include/image.h"
#include "../include/print_image.h"
#include <stddef.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <image_path>\n", argv[0]);
    return 1;
  }

  const char *image_path = argv[1];

  Image img = load_image(image_path);

  if (!img.data) {
    return 1;
  }

  printf("Image loaded: %ld x %ld\n", img.width, img.height);
  printf("Image channels: %ld\n", img.channels);

  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  size_t new_width = w.ws_col;
  size_t new_height = (size_t)(new_width * img.height / img.width / 2.0);

  Image resized = resize_image(&img, new_width, new_height);

  if (!resized.data) {
    free_image(&img);
    return 1;
  }

  print_image(&resized);

  free_image(&img);
  free_image(&resized);

  return 0;
}
