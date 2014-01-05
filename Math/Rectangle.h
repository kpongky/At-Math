#pragma once
namespace At
{
	namespace Core
	{
		namespace Math
		{
			template< typename T >
			struct Rectangle
			{
				Rectangle()
					: left( 0 )
					, top( 0 )
					, right( 0 )
					, bottom( 0 )
				{
				}

				Rectangle( const T& left_, const T& top_, const T& right_, const T& bottom_ )
					: left( left_ )
					, top( top_ )
					, right( right_ )
					, bottom( bottom_ )
				{
					if ( left > right )
					{
						Swap( left, right );						
					}

					if ( top > bottom )
					{
						Swap( left, right );
					}
				}

				const T Width() const
				{
					return right - left;
				}

				const T Height() const
				{
					return bottom - right;
				}

				T left;
				T top;
				T right;
				T bottom;								
			};

			typedef Rectangle< unsigned long > UintRect;
			typedef Rectangle< float > FloatRect;			

			const UintRect Convert( const FloatRect& floatRect, const Uint2& screenSize );
			const FloatRect Convert( const UintRect& uintRect, const Uint2& screenSize );
		}
	}
}