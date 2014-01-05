#pragma once

namespace At
{
	namespace Core
	{
		namespace Math
		{	
			template< typename T >
			struct Vector3;
			template< typename T >
			struct Vector4;
			typedef Vector4< float > Float4;
			typedef Vector4< uint32 > Uint4;
			typedef Vector4< int32 > Int4;
		
			template< typename T >
			struct Vector4
			{
				T x;
				T y;
				T z;
				T w;
				Vector4( const T x_, const T y_, const T z_, const T w_ )
					: x( x_ )
					, y( y_ )
					, z( z_ )
					, w( w_ )
				{
				}
				Vector4( const Vector4& rhs )
					: x( rhs.x )
					, y( rhs.y )
					, z( rhs.z )
					, w( rhs.w )
				{
				}
				Vector4( const Vector3< T >& rhs, const T w_ = 0 )
					: x( rhs.x )
					, y( rhs.y )
					, z( rhs.z )
					, w( w_ )
				{
				}
				Vector4()
					: x( 0 )
					, y( 0 )
					, z( 0 )
					, w( 0 )
				{
				}
				~Vector4()
				{
				}

				T& operator[]( const uint32 index )
				{
					return reinterpret_cast< T* >( this )[ index ];
				}
				
				const T& operator[]( const uint32 index ) const
				{
					return reinterpret_cast< const T* >( this )[ index ];
				}

				Vector4& operator = ( const Vector4& rhs )
				{
					x = rhs.x;
					y = rhs.y;
					z = rhs.z;
					w = rhs.w;
					return *this;
				}			
				void operator += ( const Vector4& rhs )
				{
					x += rhs.x;
					y += rhs.y;
					z += rhs.z;
					w += rhs.w;
				}
				void operator -= ( const Vector4& rhs )
				{
					x -= rhs.x;
					y -= rhs.y;
					z -= rhs.z;
					w -= rhs.w;
				}

				template< typename U >
				void operator *= ( const U scalar )
				{
					x = static_cast< T >( static_cast< U >( x ) * scalar );
					y = static_cast< T >( static_cast< U >( y ) * scalar );
					z = static_cast< T >( static_cast< U >( z ) * scalar );
					w = static_cast< T >( static_cast< U >( w ) * scalar );
				}

				template<>
				void operator *= ( const T scalar )
				{
					x *= scalar;
					y *= scalar;
					z *= scalar;
					w *= scalar;
				}

				template< typename U >
				void operator /= ( const U scalar )
				{
					x = static_cast< T >( static_cast< U >( x ) / scalar );
					y = static_cast< T >( static_cast< U >( y ) / scalar );
					z = static_cast< T >( static_cast< U >( z ) / scalar );
					w = static_cast< T >( static_cast< U >( w ) / scalar );
				}

				template<>
				void operator /= ( const T scalar )
				{
					x /= scalar;
					y /= scalar;
					z /= scalar;
					w /= scalar;
				}

			};
						
			template< typename T >
			const Vector4< T > operator * ( const Vector4< T >& lhs, const T scalar )
			{
				return Vector4< T >( lhs.x * scalar, lhs.y * scalar, lhs.z * scalar, lhs.w * scalar );
			}
			template< typename T, typename U  >
			const Vector4< T > operator * ( const Vector4< T >& lhs, const U scalar )
			{
				return Vector4< T >( static_cast< T >( static_cast< U >( lhs.x ) * scalar )
					, static_cast< T >( static_cast< U >( lhs.y ) * scalar )
					, static_cast< T >( static_cast< U >( lhs.z ) * scalar )
					, static_cast< T >( static_cast< U >( lhs.w ) * scalar ));
			}

			template< typename T, typename U >
			const Vector4< T > operator * ( const U scalar, const Vector4< T >& rhs )
			{
				return rhs * scalar;
			}
			
			template< typename T, typename U >
			const Vector4< T > operator / ( const Vector4< T >& lhs, const U scalar )
			{
				return Vector4< T >( static_cast< T >( static_cast< U >( lhs.x ) / scalar )
					, static_cast< T >( static_cast< U >( lhs.y ) / scalar ) 
					, static_cast< T >( static_cast< U >( lhs.z ) / scalar )
					, static_cast< T >( static_cast< U >( lhs.w ) / scalar ));
			}
						
			template< typename T >
			const Vector4< T > operator + ( const Vector4< T >& lhs, const Vector4< T >& rhs )
			{
				return Vector4< T >( lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w );
			}

			template< typename T >
			const Vector4< T > operator - ( const Vector4< T >& lhs, const Vector4< T >& rhs )
			{
				return Vector4< T >( lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w );
			}

			template< typename T >
			const Core::Math::Vector4< T > operator - ( const Core::Math::Vector4< T >& rhs )
			{
				return Core::Math::Float3( -rhs.x, -rhs.y, -rhs.z, -rhs.w );
			}

			template< typename T >
			const bool operator == ( const Vector4< T >& lhs, const Vector4< T >& rhs )
			{
				return ( ( lhs.x == rhs.x ) && ( lhs.y == rhs.y ) && ( lhs.z == rhs.z ) && ( lhs.w == rhs.w ) );
			}

			template< typename T >
			const bool operator != ( const Vector4< T >& lhs, const Vector4< T >& rhs )
			{
				return ( ( lhs.x != rhs.x ) || ( lhs.y != rhs.y ) || ( lhs.z != rhs.z ) || ( lhs.w != rhs.w ) );
			}

			template< typename T >
			const bool operator < ( const Vector4< T >& lhs, const Vector4< T >& rhs )
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
				else if ( lhs.z < rhs.z )
				{
					return true;
				}
				else if ( lhs.z > rhs.z )
				{
					return false;
				}
				else if ( lhs.w < rhs.w )
				{
					return true;
				}
				else if ( lhs.w > rhs.w )
				{
					return false;
				}
				else
				{
					return false;
				}
			}

			template< typename T >
			const bool operator > ( const Vector4< T >& lhs, const Vector4< T >& rhs )
			{
				return rhs < lhs;
			}

			template< typename T >
			const T Dot( const Vector4< T >& lhs, const Vector4< T >& rhs )
			{
				return ( lhs.x * rhs.x ) + ( lhs.y * rhs.y ) + ( lhs.z * rhs.z ) + ( lhs.w * rhs.w );
			}
			
			template< typename T >
			const float Length( const Vector4< T >& rhs )
			{
				return pow( Dot( rhs, rhs ), 0.5f );
			}

			template< typename T >
			const float DistanceOf( const Vector4< T >& lhs, const Vector4< T >& rhs )
			{
				return Length( lhs - rhs );
			}

			template< typename T >
			void Normalize( const Vector4< T >& input, Vector4< T >& output )
			{
				output = input / Length( input );
			}

			template< typename T >
			const Vector4< T > Normalize( const Vector4< T >& input )
			{
				return input / Length( input );
			}
			
			static const Float4 zero_float4( 0.0f, 0.0f, 0.0f, 0.0f );
		}
	}
}