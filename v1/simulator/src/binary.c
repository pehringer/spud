#include"binary.h"








int binary_write(const char *filepath, const struct binary *bin) {
  FILE *file = fopen(filepath, "wb");
  if(!file)
    return 0;
  fwrite(&(bin->size), sizeof(int), 1, file);
  fwrite(bin->data, sizeof(int), bin->size, file);
  fclose(file);
  return 1;
}

struct binary* binary_read(const char *filepath) {
  FILE *file = fopen(filepath, "rb");
  if(!file)
    return 0;
  int size = 0;
  fread(&size, sizeof(int), 1, file);
  int *data = malloc(sizeof(int) * size);
  fread(data, sizeof(int), size, file);
  fclose(file);
  struct binary *bin = malloc(sizeof(struct binary));
  bin->size = size;
  bin->data = data;
  return bin;
}

void binary_free(struct binary *bin) {
  free(bin->data);
  free(bin);
}
