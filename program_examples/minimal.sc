/* simple program in cmm language */

int v[10];

int main() {

  int i;
  for (i = 0; i < 10; i +=1) {
    v[i] = i;
  }

  while (i > 0) {
    write i;
    i -= 1;
  }
  
  return 0;
}
