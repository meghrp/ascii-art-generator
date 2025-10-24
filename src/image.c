#define STB_IMAGE_IMPLEMENTATION
#include "../include/image.h"
#include "../include/stb_image.h"

Image load_image(const char *file_path) {
  int height, width, channels;
  unsigned char *raw = stbi_load(file_path, &width, &height, &channels, 0);

  if (!raw) {
    fprintf(stderr, "Error: failed to load image '%s': %s!\n", file_path,
            stbi_failure_reason());
    return (Image){0};
  }

  size_t total_size = (size_t)width * height * channels;
  double *data = calloc(total_size, sizeof(*data));

  if (!data) {
    fprintf(stderr, "error: failed to alloc mem for data\n");
    stbi_image_free(raw);
    return (Image){0};
  }

  for (size_t i = 0; i < total_size; i++) {
    data[i] = raw[i] / 255.0;
  }

  stbi_image_free(raw);

  return (Image){
      .data = data, .width = width, .height = height, .channels = channels};
}

void free_image(Image *img) {
  if (img && img->data) {
    free(img->data);
    img->data = NULL;
    img->width = img->height = img->channels = 0;
  }
}
