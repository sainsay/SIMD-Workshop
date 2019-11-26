#include <intrin.h>
#include <random>

const int SCRHEIGHT = 720;
const int SCRWIDTH = 1280;
const float SCALE = 1.0f;

int main( int argn, char** args ) {
	_CRT_UNUSED( argn );
	_CRT_UNUSED( args );
	{
		/*
		based on https://www.shadertoy.com/view/Mdy3Dw
		float scale = 1 + cosf( t );
		t += 0.01f;
		for( int y = 0; y < SCRHEIGHT; y++ )
		{
			float yoffs = ((float)y / SCRHEIGHT - 0.5f) * scale;
			float xoffs = -0.5f * scale, dx = scale / SCRWIDTH;
			for( int x = 0; x < SCRWIDTH; x++, xoffs += dx )
			{
				float ox = 0, oy = 0, py;
				for( int i = 0; i < 99; i++ )
				{
					px = ox, py = oy,
						oy = -(py * py - px * px - 0.55f + xoffs),
						ox = -(px * py + py * px - 0.55f + yoffs);
				}
				int r = min( 255, max( 0, (int)(ox * 255) ) );
				int g = min( 255, max( 0, (int)(oy * 255) ) );
				screen->Plot( x, y, (r << 16) + (g << 8) );
			}
		}
		*/
		uint32_t* image = static_cast< uint32_t* >( malloc( SCRHEIGHT * SCRWIDTH * sizeof( uint32_t ) ) );
		if( image == nullptr )
		{
			return 1;
		}
		memset( image, 0, SCRHEIGHT * SCRWIDTH * sizeof( uint32_t ) );
		// based on http://www.cs.uu.nl/docs/vakken/magr/2017-2018/files/SIMD%20Tutorial.pdf
		for( int y = 0; y < SCRHEIGHT; y++ )
		{
			float yoffs = ( ( float )y / SCRHEIGHT - 0.5f ) * SCALE;
			float xoffs = -0.5f * SCALE;
			float dx = SCALE / SCRWIDTH;

			for( int x = 0; x < SCRWIDTH; x += 4, xoffs += dx * 4 )
			{
				union { __m128 ox4; float ox[4]; };
				union { __m128 oy4; float oy[4]; };
				ox4 = oy4 = _mm_setzero_ps();
				__m128 xoffs4 = _mm_setr_ps( xoffs, xoffs + dx,
					xoffs + dx * 2, xoffs + dx * 3 );
				__m128 yoffs4 = _mm_set_ps1( yoffs );
				for( int i = 0; i < 99; i++ )
				{
					__m128 px4 = ox4, py4 = oy4;
					oy4 = _mm_sub_ps( _mm_setzero_ps(), _mm_add_ps( _mm_sub_ps(
						_mm_sub_ps( _mm_mul_ps( py4, py4 ), _mm_mul_ps( px4, px4 ) ),
						_mm_set_ps1( 0.55f ) ), xoffs4 ) );
					ox4 = _mm_sub_ps( _mm_setzero_ps(), _mm_add_ps( _mm_sub_ps(
						_mm_add_ps( _mm_mul_ps( px4, py4 ), _mm_mul_ps( py4, px4 ) ),
						_mm_set_ps1( 0.55f ) ), yoffs4 ) );
				}
				for( int lane = 0; lane < 4; lane++ )
				{
					int r = std::min( 255, std::max( 0, ( int )( ox[lane] * 255 ) ) );
					int g = std::min( 255, std::max( 0, ( int )( oy[lane] * 255 ) ) );

					image[x + lane + y * SCRWIDTH] = ( r << 16 ) + ( g << 8 );
				}
			}
		}
	}
	return 0;
}