#include <stdlib.h>

typedef struct {
  size_t width;
  size_t height;
  size_t channels;
  double* data;
} Image;

Image load_image(const char* file_path);
void free_image(Image* img);


