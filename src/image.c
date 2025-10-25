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

Image resize_image(const Image *src, size_t new_width, size_t new_height) {
  size_t channels = src->channels;

  double *data = calloc(new_width * new_height * channels, sizeof(*data));
  if (!data) {
    fprintf(stderr, "error: failed to alloc mem for data\n");
    return (Image){0};
  }

  for (size_t y = 0; y < new_height; y++) {
    for (size_t x = 0; x < new_width; x++) {
      size_t x_old = (size_t)(x * src->width / new_width);
      size_t y_old = (size_t)(y * src->height / new_height);

      size_t src_index = (y_old * src->width + x_old) * channels;
      size_t dst_index = (y * new_width + x) * channels;

      for (size_t c = 0; c < channels; c++) {
        data[dst_index + c] = src->data[src_index + c];
      }
    }
  }

  return (Image){.data = data,
                 .width = new_width,
                 .height = new_height,
                 .channels = channels};
}
