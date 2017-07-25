int  t[5] = {0, 1, 2, 3, 4};

func_one(int v[], int pos) {
  v[pos] = 0;
}

int main() {

  func_one(t, 3);
  write t[3];
  
  return 1;
}
