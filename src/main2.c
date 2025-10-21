#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"

int main() {
    int width, height, channels;
    unsigned char *raw_data = stbi_load("waterfall.jpg", &width, &height, &channels, 0);
    if (!raw_data) {
        fprintf(stderr, "Error loading image: %s\n", stbi_failure_reason());
        return 1;
    }

    size_t total_size = width * height * channels;
    double *data = calloc(total_size, sizeof(*data));
    for (int i = 0; i < total_size; i++) {
        data[i] = raw_data[i] / 255.0;
    }

    stbi_image_free(raw_data);
    return 0;
}