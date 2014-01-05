#pragma once

namespace At
{
	namespace Core
	{
		namespace Math
		{	
			template< typename T >
			struct Vector2
			{
				T x;
				T y;
				Vector2( const T initX, const T initY )
					: x( initX )
					, y( initY )
				{
				}
				Vector2( const Vector2& rhs )
					: x( rhs.x )
					, y( rhs.y )
				{
				}
				Vector2()
					: x( 0 )
					, y( 0 )
				{
				}
				~Vector2()
				{
				}

				Vector2& operator = ( const Vector2& rhs )
				{
					x = rhs.x;
					y = rhs.y;
					return *this;
				}			
				void operator += ( const Vector2& rhs )
				{
					x += rhs.x;
					y += rhs.y;
				}
				void operator -= ( const Vector2& rhs )
				{
					x -= rhs.x;
					y -= rhs.y;
				}

				template< typename U >
				void operator *= ( const U scalar )
				{
					x = static_cast< T >( static_cast< U >( x ) * scalar );
					y = static_cast< T >( static_cast< U >( y ) * scalar );
				}

				template<>
				void operator *= ( const T scalar )
				{
					x *= scalar;
					y *= scalar;
				}

				template< typename U >
				void operator /= ( const U scalar )
				{
					x = static_cast< T >( static_cast< U >( x ) / scalar );
					y = static_cast< T >( static_cast< U >( y ) / scalar );
				}

				template<>
				void operator /= ( const T scalar )
				{
					x /= scalar;
					y /= scalar;
				}

			};

			template< typename T >
			const Vector2< T > operator * ( const Vector2< T >& lhs, const T scalar )
			{
				return Vector2< T >( lhs.x * scalar, lhs.y * scalar );
			}
			template< typename T, typename U  >
			const Vector2< T > operator * ( const Vector2< T >& lhs, const U scalar )
			{
				return Vector2< T >( static_cast< T >( static_cast< U >( lhs.x ) * scalar )
					, static_cast< T >( static_cast< U >( lhs.y ) * scalar ) );
			}

			template< typename T, typename U >
			const Vector2< T > operator * ( const U scalar, const Vector2< T >& rhs )
			{
				return rhs * scalar;
			}
			
			template< typename T, typename U >
			const Vector2< T > operator / ( const Vector2< T >& lhs, const U scalar )
			{
				return Vector2< T >( static_cast< T >( static_cast< U >( lhs.x ) / scalar )
					, static_cast< T >( static_cast< U >( lhs.y ) / scalar ) );
			}
						
			template< typename T >
			const Vector2< T > operator + ( const Vector2< T >& lhs, const Vector2< T >& rhs )
			{
				return Vector2< T >( lhs.x + rhs.x, lhs.y + rhs.y );
			}

			template< typename T >
			const Vector2< T > operator - ( const Vector2< T >& lhs, const Vector2< T >& rhs )
			{
				return Vector2< T >( lhs.x - rhs.x, lhs.y - rhs.y );
			}

			template< typename T >
			const bool operator == ( const Vector2< T >& lhs, const Vector2< T >& rhs )
			{
				return ( ( lhs.x == rhs.x ) && ( lhs.y == rhs.y ) );
			}

			template< typename T >
			const bool operator != ( const Vector2< T >& lhs, const Vector2< T >& rhs )
			{
				return ( ( lhs.x != rhs.x ) || ( lhs.y != rhs.y ) );
			}

			template< typename T >
			const bool operator < ( const Vector2< T >& lhs, const Vector2< T >& rhs )
			{
				if ( lhs.x < rhs.x )
				{
					return true;
				}
				else if ( lhs.x > rhs.x )
				{
					return false;
				}
				else if ( lhs.y < rhs.y )
				{
					return true;
				}
				else if ( lhs.y > rhs.y )
				{
					return false;
				}
				else
				{
					return false;
				}
			}

			template< typename T >
			const bool operator > ( const Vector2< T >& lhs, const Vector2< T >& rhs )
			{
				return rhs < lhs;
			}

			template< typename T >
			const T Dot( const Vector2< T >& lhs, const Vector2< T >& rhs )
			{
				return ( lhs.x * rhs.x ) + ( lhs.y * rhs.y );
			}

			template< typename T >
			const float Length( const Vector2< T >& rhs )
			{
				return pow( Dot( rhs, rhs ), 0.5f );
			}

			template< typename T >
			const float DistanceOf( const Vector2< T >& lhs, const Vector2< T >& rhs )
			{
				return Length( lhs - rhs );
			}

			template< typename T >
			void Normalize( const Vector2< T >& input, Vector2< T >& output )
			{
				output = input / Length( input );
			}

			template< typename T >
			const Vector2< T > Normalize( const Vector2< T >& input )
			{
				return input / Length( input );
			}

			typedef Vector2< float > Float2;
			typedef Vector2< uint32 > Uint2;
			typedef Vector2< int32 > Int2;
		}
	}
}