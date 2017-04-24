
int v[10];

/*
        Procedimento de ordenação por troca
        Observe como um parâmetro de arranjo é declarado.
*/

void bubblesort(int v[], int n) {
    int i=0, j;
    bool trocou = true;
    while (i < n-1 && trocou) {
        trocou = false;
        for (j=0; j< n-i-1; j+=1) {
            if (v[j] > v[j+1]) {
                int aux;
                aux = v[j];
                v[j] = v[j+1];
                v[j+1] = aux;
                trocou = true;
            }
        }
        i += 1;
    }
}

void main() {
    int i;
    for (i=0; i < 10; i+=1) {
        read v[i];
    }
    bubblesort(v, 10);
    for (i=0; i < 10; i+=1) {
        write v[i], " ";
    }
}