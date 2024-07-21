void add1(int n, int *a, int *b, int *c) {
  for (int i = 0; i < n; ++i) {
    c[i] = a[i] + b[i];
  }
}

void add2(int n, int *__restrict__ a, int *__restrict__ b, int *__restrict__ c) {
  for (int i = 0; i < n; ++i) {
    c[i] = a[i] + b[i];
  }
}

void add3(int n, int *a, int *b, int *c) {
  int i = 0;
  for (; i + 16 < n;) {
    c[i] = a[i] + b[i];
    ++i;
    c[i] = a[i] + b[i];
    ++i;
    c[i] = a[i] + b[i];
    ++i;
    c[i] = a[i] + b[i];
    ++i;
    c[i] = a[i] + b[i];
    ++i;
    c[i] = a[i] + b[i];
    ++i;
    c[i] = a[i] + b[i];
    ++i;
    c[i] = a[i] + b[i];
    ++i;
    c[i] = a[i] + b[i];
    ++i;
    c[i] = a[i] + b[i];
    ++i;
    c[i] = a[i] + b[i];
    ++i;
    c[i] = a[i] + b[i];
    ++i;
    c[i] = a[i] + b[i];
    ++i;
    c[i] = a[i] + b[i];
    ++i;
    c[i] = a[i] + b[i];
    ++i;
    c[i] = a[i] + b[i];
    ++i;
  }
  for (; i < n; ++i) {
    c[i] = a[i] + b[i];
  }
}
