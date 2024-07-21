#pragma once

void add1(int n, int *a, int *b, int *c);

void add2(int n, int *__restrict__ a, int *__restrict__ b, int *__restrict__ c);

void add3(int n, int *a, int *b, int *c);
