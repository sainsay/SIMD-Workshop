#include <intrin.h>
#include <random>
#include <vector>

const size_t VEC_COUNT = 50;

int main(int argn, char** args) {
	_CRT_UNUSED(argn);
	_CRT_UNUSED(args);
	{

		// every vec3 as a _m128, last value of _m128 is not used.
		__m128* vec3_arr = static_cast<__m128*>(malloc(VEC_COUNT * sizeof(__m128)));
		if (vec3_arr == nullptr) {
			return 1;
		}

		for (size_t i = 0; i < VEC_COUNT; ++i)
		{
			vec3_arr[i] = _mm_set_ps( float(std::rand()), float(std::rand()) ,float(std::rand()) , 0.0f);
		}


		// group each axis as a _m128, 
		size_t corrected_count = VEC_COUNT + (VEC_COUNT % 4 == 0 ? 0 : 4 - VEC_COUNT % 4);

		__m128* x_arr = static_cast<__m128*>(malloc(corrected_count * sizeof(__m128)));
		__m128* y_arr = static_cast<__m128*>(malloc(corrected_count * sizeof(__m128)));
		__m128* z_arr = static_cast<__m128*>(malloc(corrected_count * sizeof(__m128)));

		if (x_arr == nullptr || y_arr == nullptr || z_arr == nullptr)
		{
			return 1;
		}
		for (size_t i = 0; i < corrected_count / 4; i++)
		{
			x_arr[i] = _mm_set_ps(float(std::rand()), float(std::rand()), float(std::rand()), float(std::rand()));
			y_arr[i] = _mm_set_ps(float(std::rand()), float(std::rand()), float(std::rand()), float(std::rand()));
			z_arr[i] = _mm_set_ps(float(std::rand()), float(std::rand()), float(std::rand()), float(std::rand()));
		}





	}
	return 0;
}