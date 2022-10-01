#ifndef PSXGS_MATH_H
#define PSXGS_MATH_H

// Integer power function, because apparently it's acceptable for a systems language to lack one
int GsIPOW(int base, int exp);
// Long integer power function, because apparently it's acceptable for a systems language to lack one
long GsLIPOW(long base, long exp);

// Long integer abs function
long GsAbsLong(long x);

#endif