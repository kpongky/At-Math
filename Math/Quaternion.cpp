#include <math.h>
#include <assert.h>
#include "../Type.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix.h"
#include "Quaternion.h"
namespace At
{
	namespace Core
	{
		namespace Math
		{
			const Quaternion Quaternion::e( 0.0f, 0.0f, 0.0f, 1.0f );
			Quaternion::Quaternion( const float x_/*i*/, const float y_/*j*/, const float z_/*k*/, const float w_ )
				: x( x_ )
				, y( y_ )
				, z( z_ )
				, w( w_ )
			{
			}

			Quaternion::Quaternion( const Float3& euler )
			{
				float c1 = cos( euler.y / 2 );
				float s1 = sin( euler.y / 2 );
				float c2 = cos( euler.z / 2 );
				float s2 = sin( euler.z / 2 );
				float c3 = cos( euler.x / 2 );
				float s3 = sin( euler.x / 2 );

				w = c1 * c2 * c3 - s1 * s2 * s3;
				x = c1 * c2 * s3 + s1 * s2 * c3;
				y = s1 * c2 * c3 + c1 * s2 * s3;
				z = c1 * s2 * c3 - s1 * c2 * s3;
			}

			Quaternion::Quaternion( const Quaternion& rhs )
				: x( rhs.x )
				, y( rhs.y )
				, z( rhs.z )
				, w( rhs.w )
			{
			}

			Quaternion::Quaternion( const Float3& axis, const float angle )
			{
				const Float3 normalizedAxis = Normalize( axis );
				const float s = sin( angle / 2 );
				x = normalizedAxis.x * s;
				y = normalizedAxis.y * s;
				z = normalizedAxis.z * s;
				w = cos( angle / 2 );
			}

			Quaternion::Quaternion()
				: x( 0.0f )
				, y( 0.0f )
				, z( 0.0f )
				, w( 1.0f )
			{
			}

			Quaternion::~Quaternion()
			{
			}

			const Quaternion& Quaternion::operator = ( const Quaternion& rhs )
			{
				x = rhs.x;
				y = rhs.y;
				z = rhs.z;
				w = rhs.w;
				return *this;
			}

			void Quaternion::operator += ( const Quaternion& rhs )
			{
				x += rhs.x;
				y += rhs.y;
				z += rhs.z;
				w += rhs.w;
			}

			void Quaternion::operator -= ( const Quaternion& rhs )
			{
				x -= rhs.x;
				y -= rhs.y;
				z -= rhs.z;
				w -= rhs.w;
			}

			void Quaternion::operator *= ( const float scalar )
			{
				x *= scalar;
				y *= scalar;
				z *= scalar;
				w *= scalar;
			}

			void Quaternion::operator /= ( const float scalar )
			{
				x /= scalar;
				y /= scalar;
				z /= scalar;
				w /= scalar;
			}

			const Matrix4x4 Quaternion::ToMatrix() const
			{
				const float x2 = x * x;
				const float y2 = y * y;
				const float z2 = z * z;
				const float w2 = w * w;
				//return Matrix4x4( w2 + x2 - y2 - z2, 2.0f * ( x * y - w * z ), 2.0f * ( x * z + w * y ), 0.0f
				//				, 2.0f * ( x * y + w * z ), w2 - x2 + y2 - z2, 2.0f * ( y * z - w * x ), 0.0f
				//				, 2.0f * ( x * z - w * y ), 2.0f * ( y * z + w * x ), w2 - x2 - y2 + z2, 0.0f 
				//				, 0.0f, 0.0f, 0.0f, 1.0f );
				return Matrix4x4( w2 + x2 - y2 - z2, 2.0f * ( x * y + w * z ), 2.0f * ( x * z - w * y ), 0.0f
								, 2.0f * ( x * y - w * z ), w2 - x2 + y2 - z2, 2.0f * ( y * z + w * x ), 0.0f
								, 2.0f * ( x * z + w * y ), 2.0f * ( y * z - w * x ), w2 - x2 - y2 + z2, 0.0f 
								, 0.0f, 0.0f, 0.0f, 1.0f );
			}

			const Quaternion Quaternion::Conjugate() const
			{
				return Quaternion( -x, -y, -z, w );
			}

			const Float3 Quaternion::Axis() const
			{
				const float s = pow( 1 - w * w, 0.5f );
				return Float3( x/s, y/s, z/s );
			}

			const Float3 Quaternion::ToEuler() const
			{
				const float pole = ( x * y + z * w ) / Length( *this );
				static const float poleZ = asin( 1.0f );
				if ( ( pole != 0.5f ) && ( pole != -0.5f ) )
				{
					const float eulerX = atan2( 2.0f * ( x * w - y * z ) , w * w - x * x + y * y - z * z );
					const float eulerY = atan2( 2.0f * ( y * w - x * z ) , w * w  + x * x - y * y - z * z );
					const float eulerZ = asin( 2.0f * pole );
					return Float3( eulerX, eulerY, eulerZ );
				}
				else if ( 0.5f == pole )
				{					
					const float eulerY = 2.0f * atan2( x, w );
					return Float3( 0.0f, eulerY, poleZ );
				}
				else if ( -0.5f == pole )
				{					
					const float eulerY = -2.0f * atan2( x, w );
					return Float3( 0.0f, eulerY, poleZ );
				}
				else
				{
					assert( 0 && L"This code is impossible." );
					return Float3( 0.0f, 0.0f, 0.0f );
				}				
			}

			const float Length( const Quaternion& rhs )
			{
				return pow( rhs.x * rhs.x + rhs.y * rhs.y + rhs.z * rhs.z + rhs.w * rhs.w, 0.5f );
			}

			const float Dot( const Quaternion& lhs, const Quaternion& rhs )
			{
				return ( lhs.x * rhs.x ) + ( lhs.y * rhs.y ) + ( lhs.z * rhs.z ) + ( lhs.w * rhs.w );
			}

			Core::Math::Float3 operator * ( const Core::Math::Float3& lhs, const Core::Math::Quaternion& rhs )
			{
				auto result = rhs.Conjugate() * Core::Math::Quaternion( lhs.x, lhs.y, lhs.z, 0 ) * rhs;
				return Core::Math::Float3( result.x, result.y, result.z );
			}

			Core::Math::Float4 operator * ( const Core::Math::Float4& lhs, const Core::Math::Quaternion& rhs )
			{
				auto result = rhs.Conjugate() * Core::Math::Quaternion( lhs.x, lhs.y, lhs.z, 0 ) * rhs;
				return Core::Math::Float4( result.x, result.y, result.z, lhs.w );
			}

			Core::Math::Quaternion operator + ( const Core::Math::Quaternion& lhs, const Core::Math::Quaternion& rhs )
			{
				return Core::Math::Quaternion( lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w );
			}

			Core::Math::Quaternion operator - ( const Core::Math::Quaternion& lhs, const Core::Math::Quaternion& rhs )
			{
				return Core::Math::Quaternion( lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w );
			}

			Core::Math::Quaternion operator * ( const Core::Math::Quaternion& lhs, const Core::Math::Quaternion& rhs )
			{
				return Core::Math::Quaternion( rhs.w * lhs.x + rhs.x * lhs.w + rhs.y * lhs.z - rhs.z * lhs.y
												 , rhs.w * lhs.y + rhs.y * lhs.w + rhs.z * lhs.x - rhs.x * lhs.z
												 , rhs.w * lhs.z + rhs.z * lhs.w + rhs.x * lhs.y - rhs.y * lhs.x
												 , rhs.w * lhs.w - rhs.x * lhs.x - rhs.y * lhs.y - rhs.z * lhs.z );
				//return Core::Math::Quaternion( lhs.w * rhs.x + lhs.x * rhs.w + lhs.y * rhs.z - lhs.z * rhs.y
				//								 , lhs.w * rhs.y + lhs.y * rhs.w + lhs.z * rhs.x - lhs.x * rhs.z
				//								 , lhs.w * rhs.z + lhs.z * rhs.w + lhs.x * rhs.y - lhs.y * rhs.x
				//								 , lhs.w * rhs.w - lhs.x * rhs.x - lhs.y * rhs.y - lhs.z * rhs.z );
			}

			Core::Math::Quaternion operator * ( const float scalar, const Core::Math::Quaternion& rhs )
			{
				return Core::Math::Quaternion( rhs.x * scalar, rhs.y * scalar, rhs.z * scalar, rhs.w * scalar );
			}

			Core::Math::Quaternion operator * ( const Core::Math::Quaternion& lhs, const float scalar )
			{
				return Core::Math::Quaternion( lhs.x * scalar, lhs.y * scalar, lhs.z * scalar, lhs.w * scalar );
			}

			Core::Math::Quaternion operator / ( const Core::Math::Quaternion& lhs, const float scalar )
			{
				return Core::Math::Quaternion( lhs.x / scalar, lhs.y / scalar, lhs.z / scalar, lhs.w / scalar );
			}

			const bool operator == ( const Core::Math::Quaternion& lhs, const Core::Math::Quaternion& rhs )
			{
				return ( ( lhs.x == rhs.x ) && ( lhs.y == rhs.y ) && ( lhs.z == rhs.z ) && ( lhs.w == rhs.w ) );
			}

			const bool operator != ( const Core::Math::Quaternion& lhs, const Core::Math::Quaternion& rhs )
			{
				return !( lhs == rhs );
			}
		}
	}
}