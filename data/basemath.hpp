#include <cmath>
#include <cstdint>

float abs_c(float x) {
	int32_t y = *((int32_t*)&x);
	y = y & 0x7fffffff; // Remove the signature bit
	x = *((float*)&y);
	return x;
}

double abs_c(double x) {
	int64_t y = *((int64_t*)&x);
	y = y & 0x7fffffffffffffff; // Remove the signature bit
	x = *((double*)&y);
	return x;
}

short abs_c(short x) {
	return (((x > 0)<<1)-1)*x;
}

int abs_c(int x) {
	return (((x > 0)<<1)-1)*x;
}

long abs_c(long x) {
	return (((x > 0)<<1)-1)*x;
}

long long abs_c(long long x) {
	return (((x > 0)<<1)-1)*x;
}