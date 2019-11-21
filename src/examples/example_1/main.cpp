#include <intrin.h>
#include <random>

int main(int argn, char** args) {
	_CRT_UNUSED(argn);
	_CRT_UNUSED(args);
	
	{
		// arrays of 4 ints
		int vec_1[] = { rand(),rand(),rand(),rand() };
		int vec_2[] = { rand(),rand(),rand(),rand() };

		// object representing 128 bits in Integer layout. Here assigning 4 * 32 bit int.
		__m128i simd_vec_1 = _mm_set_epi32(rand(), rand(), rand(), rand());
		__m128i simd_vec_2 = _mm_set_epi32(rand(), rand(), rand(), rand());

		// element-wise adding the 2 arrays together
		int add_vec[] = { vec_1[0] + vec_2[0],
							vec_1[1] + vec_2[1],
							vec_1[2] + vec_2[2],
							vec_1[3] + vec_2[3], };

		// same opperation. This uses the SSE2 instruction set
		__m128i simd_add_vec = _mm_add_epi32(simd_vec_1, simd_vec_2);
	}
	return 0;
}
