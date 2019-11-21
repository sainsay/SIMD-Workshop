#include <intrin.h>
#include <random>

int main(int argn, char** args) {
	_CRT_UNUSED(argn);
	_CRT_UNUSED(args);

	int vec_1[] = { rand(),rand(),rand(),rand() };
	int vec_2[] = { rand(),rand(),rand(),rand() };

	union
	{
		__m128i simd_vec_1 = _mm_set_epi32(rand(), rand(), rand(), rand());
		int simd_vec_1_v[4];
	};

	union
	{
		__m128i simd_vec_2;
		int simd_vec_2_v[4];
	};

	simd_vec_2 = _mm_set_epi32(rand(), rand(), rand(), rand());

	int add_vec[] = { vec_1[0] + vec_2[0],
						vec_1[1] + vec_2[1],
						vec_1[2] + vec_2[2],
						vec_1[3] + vec_2[3], };

	union
	{
		__m128i simd_add_vec;
		int simd_add_vec_v[4];
	};

	simd_add_vec = _mm_add_epi32(simd_vec_1, simd_vec_2);

	
	return 0;
}
