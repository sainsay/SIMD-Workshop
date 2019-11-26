#include <intrin.h>
#include <random>

int main( int argn, char** args ) {
	_CRT_UNUSED( argn );
	_CRT_UNUSED( args );
	{
		// accessing your integer values
		__m128i simd_vec = _mm_set_epi32( rand(), rand(), rand(), rand() );


		// (1)
		__int32 first_int = simd_vec.m128i_i32[0]; //Recommended way BUT potential Undefined Behaviour: Type punning.


		// (2)
		first_int = reinterpret_cast< __int32* >( &simd_vec )[0]; // Undefined Behaviour: Type punning.


		// (3)
		__int32 int_vec[4];
		std::memcpy( int_vec, &simd_vec, sizeof( __m128i ) );
		first_int = int_vec[0]; // no Type punning but more typing.


		// (4)
		// The cool kids way
		union vec4
		{
			__m128i m;
			__int32 v[4];
#pragma warning(push)
#pragma warning(disable : 4201)
			struct
			{
				__int32 x;
				__int32 y;
				__int32 z;
				__int32 w;
			};
		};
#pragma warning(pop)
		vec4 simd_vec2;
		simd_vec2.m = _mm_set_epi32( rand(), rand(), rand(), rand() );

		first_int = simd_vec2.x;
	}
	return 0;
}