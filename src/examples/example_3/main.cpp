#include <intrin.h>
#include <random>
#include <vector>

const size_t VEC_COUNT = 50;

int main( int argn, char** args ) {
	_CRT_UNUSED( argn );
	_CRT_UNUSED( args );
	{
		{
			// every vec3 as a _m128, last value of _m128 is not used.
			__m128* vec3_arr = static_cast< __m128* >( malloc( VEC_COUNT * sizeof( __m128 ) ) );
			if( vec3_arr == nullptr ) {
				return 1;
			}

			for( size_t i = 0; i < VEC_COUNT; ++i )
			{
				vec3_arr[i] = _mm_set_ps( float( std::rand() ), float( std::rand() ), float( std::rand() ), 0.0f );
			}

			__m128* vec3_result_arr = static_cast< __m128* >( malloc( VEC_COUNT * sizeof( __m128 ) ) );
			if( vec3_result_arr == nullptr ) {
				return 1;
			}
			auto sub_vec3 = _mm_set_ps( 4.0f, 3.0f, 2.0f, 0.0f );
			for( size_t i = 0; i < VEC_COUNT; ++i )
			{
				vec3_result_arr[i] = _mm_sub_ps( vec3_arr[i], sub_vec3 );
			}
		}
		{
			// group each axis as a _m128, 
			size_t corrected_count = VEC_COUNT + ( VEC_COUNT % 4 == 0 ? 0 : 4 - VEC_COUNT % 4 );

			__m128* x_arr = static_cast< __m128* >( malloc( corrected_count * sizeof( __m128 ) ) );
			__m128* y_arr = static_cast< __m128* >( malloc( corrected_count * sizeof( __m128 ) ) );
			__m128* z_arr = static_cast< __m128* >( malloc( corrected_count * sizeof( __m128 ) ) );

			if( x_arr == nullptr || y_arr == nullptr || z_arr == nullptr )
			{
				return 1;
			}
			for( size_t i = 0; i < corrected_count / 4; i++ )
			{
				x_arr[i] = _mm_set_ps( float( std::rand() ), float( std::rand() ), float( std::rand() ), float( std::rand() ) );
				y_arr[i] = _mm_set_ps( float( std::rand() ), float( std::rand() ), float( std::rand() ), float( std::rand() ) );
				z_arr[i] = _mm_set_ps( float( std::rand() ), float( std::rand() ), float( std::rand() ), float( std::rand() ) );
			}

			auto sub_x = _mm_set_ps( 4.0f, 4.0f, 4.0f, 4.0f );
			auto sub_y = _mm_set_ps( 3.0f, 3.0f, 3.0f, 3.0f );
			auto sub_z = _mm_set_ps( 2.0f, 2.0f, 2.0f, 2.0f );

			__m128* x_result_arr = static_cast< __m128* >( malloc( corrected_count * sizeof( __m128 ) ) );
			__m128* y_result_arr = static_cast< __m128* >( malloc( corrected_count * sizeof( __m128 ) ) );
			__m128* z_result_arr = static_cast< __m128* >( malloc( corrected_count * sizeof( __m128 ) ) );

			if( x_result_arr == nullptr || y_result_arr == nullptr || z_result_arr == nullptr )
			{
				return 1;
			}

			{ // every axis at the same time
				for( size_t i = 0; i < corrected_count / 4; i++ )
				{
					x_result_arr[i] = _mm_sub_ps( x_arr[i], sub_x );
					y_result_arr[i] = _mm_sub_ps( y_arr[i], sub_y );
					z_result_arr[i] = _mm_sub_ps( z_arr[i], sub_z );
				}
			}
			{ // 3 seperate loops.
				for( size_t i = 0; i < corrected_count / 4; i++ ) x_result_arr[i] = _mm_sub_ps( x_arr[i], sub_x );
				for( size_t i = 0; i < corrected_count / 4; i++ ) y_result_arr[i] = _mm_sub_ps( y_arr[i], sub_y );
				for( size_t i = 0; i < corrected_count / 4; i++ ) z_result_arr[i] = _mm_sub_ps( z_arr[i], sub_z );

			}
		}
	}
	return 0;
}