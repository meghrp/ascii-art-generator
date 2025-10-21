#include <stdio.h>
#include <stdlib.h>

#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"

typedef struct {
  int width;
  int height;
  unsigned char *data;
} Image;

Image* read_image(const char *filename) {
  Image *image = malloc(sizeof(Image));
  if (!image) {
    perror("Error allocating memory");
    return NULL;
  }

  int channels;
  image->data = stbi_load(filename, &image->width, &image->height, &channels, 3);
  
  if (!image->data) {
    fprintf(stderr, "Error loading image: %s\n", stbi_failure_reason());
    free(image);
    return NULL;
  }

  return image;
}

void free_image(Image *img) {
  if (img) {
    stbi_image_free(img->data);
    free(img);
  }
}

int main(void) {
  Image *img = read_image("waterfall.jpg");
  if (!img) return 1;

  printf("Image loaded: %dx%d\n", img->width, img->height);

  int y = 2000;
  int scale = 8; // adjust for terminal width

  for (int x = 0; x < img->width; x += scale) {
    int index = (y * img->width + x) * 3;
    unsigned char r = img->data[index];
    unsigned char g = img->data[index + 1];
    unsigned char b = img->data[index + 2];

    printf("\033[48;2;%d;%d;%dm \033[0m", r, g, b);
  }

  printf("\n");
  free_image(img);
  return 0;
}
