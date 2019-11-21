#include <intrin.h>
#include <random>

int main(int argn, char** args) {
	_CRT_UNUSED(argn);
	_CRT_UNUSED(args);
	{
		// accessing your integer values
		__m128i simd_vec = _mm_set_epi32(rand(), rand(), rand(), rand());

	}
	return 0;
}