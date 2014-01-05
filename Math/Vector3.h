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
			typedef Vector3< float > Float3;
			typedef Vector3< uint32 > Uint3;
			typedef Vector3< int32 > Int3;
		
			template< typename T >
			struct Vector3
			{
				T x;
				T y;
				T z;
				Vector3( const T initX, const T initY, const T initZ )
					: x( initX )
					, y( initY )
					, z( initZ )
				{
				}
				Vector3( const Vector3& rhs )
					: x( rhs.x )
					, y( rhs.y )
					, z( rhs.z )
				{
				}
				Vector3( const Vector4< T >& rhs )
					: x( rhs.x )
					, y( rhs.y )
					, z( rhs.z )
				{
				}
				Vector3()
					: x( 0 )
					, y( 0 )
					, z( 0 )
				{
				}
				~Vector3()
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

				Vector3& operator = ( const Vector3& rhs )
				{
					x = rhs.x;
					y = rhs.y;
					z = rhs.z;
					return *this;
				}

				Vector3& operator = ( const Vector4<T>& rhs )
				{
					x = rhs.x;
					y = rhs.y;
					z = rhs.z;
					return *this;
				}	

				void operator += ( const Vector3& rhs )
				{
					x += rhs.x;
					y += rhs.y;
					z += rhs.z;
				}
				void operator -= ( const Vector3& rhs )
				{
					x -= rhs.x;
					y -= rhs.y;
					z -= rhs.z;
				}

				template< typename U >
				void operator *= ( const U scalar )
				{
					x = static_cast< T >( static_cast< U >( x ) * scalar );
					y = static_cast< T >( static_cast< U >( y ) * scalar );
					z = static_cast< T >( static_cast< U >( z ) * scalar );
				}

				template<>
				void operator *= ( const T scalar )
				{
					x *= scalar;
					y *= scalar;
					z *= scalar;
				}

				template< typename U >
				void operator /= ( const U scalar )
				{
					x = static_cast< T >( static_cast< U >( x ) / scalar );
					y = static_cast< T >( static_cast< U >( y ) / scalar );
					z = static_cast< T >( static_cast< U >( z ) / scalar );
				}

				template<>
				void operator /= ( const T scalar )
				{
					x /= scalar;
					y /= scalar;
					z /= scalar;
				}

			};
						
			template< typename T >
			const Vector3< T > operator * ( const Vector3< T >& lhs, const T scalar )
			{
				return Vector3< T >( lhs.x * scalar, lhs.y * scalar, lhs.z * scalar );
			}
			template< typename T, typename U  >
			const Vector3< T > operator * ( const Vector3< T >& lhs, const U scalar )
			{
				return Vector3< T >( static_cast< T >( static_cast< U >( lhs.x ) * scalar )
					, static_cast< T >( static_cast< U >( lhs.y ) * scalar )
					, static_cast< T >( static_cast< U >( lhs.z ) * scalar ) );
			}

			template< typename T, typename U >
			const Vector3< T > operator * ( const U scalar, const Vector3< T >& rhs )
			{
				return rhs * scalar;
			}
			
			template< typename T, typename U >
			const Vector3< T > operator / ( const Vector3< T >& lhs, const U scalar )
			{
				return Vector3< T >( static_cast< T >( static_cast< U >( lhs.x ) / scalar )
					, static_cast< T >( static_cast< U >( lhs.y ) / scalar ) 
					, static_cast< T >( static_cast< U >( lhs.z ) / scalar ) );
			}
						
			template< typename T >
			const Vector3< T > operator + ( const Vector3< T >& lhs, const Vector3< T >& rhs )
			{
				return Vector3< T >( lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z );
			}

			template< typename T >
			const Vector3< T > operator - ( const Vector3< T >& lhs, const Vector3< T >& rhs )
			{
				return Vector3< T >( lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z );
			}

			template< typename T >
			const Core::Math::Vector3< T > operator - ( const Core::Math::Vector3< T >& rhs )
			{
				return Core::Math::Float3( -rhs.x, -rhs.y, -rhs.z );
			}

			template< typename T >
			const bool operator == ( const Vector3< T >& lhs, const Vector3< T >& rhs )
			{
				return ( ( lhs.x == rhs.x ) && ( lhs.y == rhs.y ) && ( lhs.z == rhs.z ) );
			}

			template< typename T >
			const bool operator != ( const Vector3< T >& lhs, const Vector3< T >& rhs )
			{
				return ( ( lhs.x != rhs.x ) || ( lhs.y != rhs.y ) || ( lhs.z != rhs.z ) );
			}

			template< typename T >
			const bool operator < ( const Vector3< T >& lhs, const Vector3< T >& rhs )
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
				else
				{
					return false;
				}
			}

			template< typename T >
			const bool operator > ( const Vector3< T >& lhs, const Vector3< T >& rhs )
			{
				return rhs < lhs;
			}

			template< typename T >
			const T Dot( const Vector3< T >& lhs, const Vector3< T >& rhs )
			{
				return ( lhs.x * rhs.x ) + ( lhs.y * rhs.y ) + ( lhs.z * rhs.z );
			}
			
#ifdef LH_OUTPRODUCT
#	define OutProduct( a, b ) OutProductL( a, b )
#else
#	define OutProduct( a, b ) OutProductR( a, b )
#endif
			template< typename T >
			const Vector3< T > OutProductR( const Vector3< T >& lhs, const Vector3< T >& rhs )
			{
				return Float3( lhs.z * rhs.y - lhs.y * rhs.z, lhs.x * rhs.z - lhs.z * rhs.x, lhs.y * rhs.x - lhs.x * rhs.y );
			}
			
			template< typename T >
			const Vector3< T > OutProductL( const Vector3< T >& lhs, const Vector3< T >& rhs )
			{
				return Float3( rhs.z * lhs.y - rhs.y * lhs.z, rhs.x * lhs.z - rhs.z * lhs.x, rhs.y * lhs.x - rhs.x * lhs.y );
			}

			template< typename T >
			const float Length( const Vector3< T >& rhs )
			{
				return pow( Dot( rhs, rhs ), 0.5f );
			}

			template< typename T >
			const float DistanceOf( const Vector3< T >& lhs, const Vector3< T >& rhs )
			{
				return Length( lhs - rhs );
			}

			template< typename T >
			void Normalize( const Vector3< T >& input, Vector3< T >& output )
			{
				output = input / Length( input );
			}

			template< typename T >
			const Vector3< T > Normalize( const Vector3< T >& input )
			{
				return input / Length( input );
			}
			
			static const Float3 zero_float3( 0.0f, 0.0f, 0.0f );
			static const Float3 axis_x( 1.0f, 0.0f, 0.0f );
			static const Float3 axis_y( 0.0f, 1.0f, 0.0f );
			static const Float3 axis_z( 0.0f, 0.0f, 1.0f );
		}
	}
}