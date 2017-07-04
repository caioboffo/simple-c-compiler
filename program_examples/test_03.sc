
int n[10];

print_array(int p[], int size) {
  int i;
  int k;
  for (i = 0; i < size; i += 1) {
    write p[i];
    if (i < size) {
      int aix;
      write ", ";
    }
  }
}

int main() {
  int size = 4;
  int n[4] = { 0, 1, 2, 3 };
  print_array(n, size);
  return 0;
}
