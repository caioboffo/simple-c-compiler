
int main() {
  int a = 3;
  int result = 0 ;

  if ((a % 2) == 1) {
    int b = 3;
    result = a + b;
    write "point a  ", result;
  } else {
    write "point b ", result;
  }

  
  if (result > 0) {
    result += a;
    write "point c ", result;

    if (result == 9) {
       int k = -1;
       result -= k;
       write "this result is awesome ", result; 
    }

  }
  
  return 0;
}
