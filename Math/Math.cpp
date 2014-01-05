#include <math.h>
#include <assert.h>
#include "../Type.h"
#include "Math.h"

namespace At
{
	namespace Core
	{
		namespace Math
		{
			const bool SolveSecondOrderEquation( const float a, const float b, const float c, float& solution1, float& solution2 )
			{
				const float d = ( b * b ) - ( 4 * a * c );

				if ( d < 0 )
				{
					return false;
				}
				else
				{
					solution1 = ( -b + pow( d, 0.5f ) ) / ( 2 * a );
					solution2 = ( -b - pow( d, 0.5f ) ) / ( 2 * a );
					return true;
				}
			}

			const Matrix4x4 ProjectionMatrix( float width, float height, float nearDistance, float farDistance, bool isPerspective )
			{
				if ( isPerspective )
				{
					const float q = farDistance / ( farDistance - nearDistance );
					return Matrix4x4( 2.0f * nearDistance / width, 0.0f, 0.0f, 0.0f
						, 0.0f, 2.0f * nearDistance / height, 0.0f, 0.0f
						, 0.0f, 0.0f, q, 1.0f
						, 0.0f, 0.0f, -q * nearDistance, 0.0f );
				}
				else
				{
					return Matrix4x4( 2.0f / width, 0.0f, 0.0f, 0.0f
						, 0.0f, 2.0f / height, 0.0f, 0.0f
						, 0.0f, 0.0f, 1.0f / ( farDistance - nearDistance ), 1.0f
						, 0.0f, 0.0f, -nearDistance / ( farDistance - nearDistance ), 0.0f );
				}
			}

			const Matrix4x4 TransMatrix( const float x, const float y, const float z )
			{
				return Matrix4x4( 1.0f, 0.0f, 0.0f, 0.0f
					, 0.0f, 1.0f, 0.0f, 0.0f
					, 0.0f, 0.0f, 1.0f, 0.0f
					, x, y, z, 1.0f );
			}

			const Matrix4x4 TransMatrix( const Float3& rhs )
			{
				return TransMatrix( rhs.x, rhs.y, rhs.z );
			}
			
			const Matrix4x4 EulerRotation( Axis::Type about, const float radian )
			{
				switch ( about )
				{
				case Axis::X:
					return EulerRotationX( radian );
				case Axis::Y:
					return EulerRotationY( radian );
				case Axis::Z:
					return EulerRotationZ( radian );
				default:
					assert( 0 && L"There are no axis." );
#ifdef EXCEPTION
					throw EXCEPTION(Core::Exception) << L"There are no axis." << std::endl;
#else
					throw;
#endif
				};
			}

			const Matrix4x4 EulerRotationX( const float radian )
			{
				return Matrix4x4( 1.0f, 0.0f, 0.0f, 0.0f 
					, 0.0f, cos( radian ), sin( radian ), 0.0f
					, 0.0f, -sin( radian ), cos( radian ), 0.0f
					, 0.0f, 0.0f, 0.0f, 1.0f );
			}

			const Matrix4x4 EulerRotationY( const float radian )
			{
				return Matrix4x4( cos( radian ), 0.0f, -sin( radian ), 0.0f 
					, 0.0f, 1.0f, 0.0f, 0.0f
					, sin( radian ), 0.0f, cos( radian ), 0.0f
					, 0.0f, 0.0f, 0.0f, 1.0f );
			}

			const Matrix4x4 EulerRotationZ( const float radian )
			{
				return Matrix4x4( cos( radian ), sin( radian ), 0.0f, 0.0f 
					, -sin( radian ), cos( radian ), 0.0f, 0.0f
					, sin( radian ), 0.0f, 1.0f, 0.0f
					, 0.0f, 0.0f, 0.0f, 1.0f );
			}

			const Matrix4x4 ScaleMatrix( const float scale )
			{
				return Matrix4x4( scale, 0.0f, 0.0f, 0.0f
					, 0.0f, scale, 0.0f, 0.0f
					, 0.0f, 0.0f, scale, 0.0f
					, 0.0f, 0.0f, 0.0f, 1.0f );
			}

			const Matrix4x4 ScaleMatrix( const Float3& scale )
			{
				return Matrix4x4( scale.x, 0.0f, 0.0f, 0.0f
					, 0.0f, scale.y, 0.0f, 0.0f
					, 0.0f, 0.0f, scale.z, 0.0f
					, 0.0f, 0.0f, 0.0f, 1.0f );
			}

			const Float3 ConvertToScale( const Matrix4x4& scaleMatrix )
			{
				return Float3( Length( scaleMatrix.GetX() ), Length( scaleMatrix.GetY() ), Length( scaleMatrix.GetZ() ) );
			}

			const float AspectRatio( const Matrix4x4& projectionMatrix )
			{
				return projectionMatrix.m11 / projectionMatrix.m00;
			}

			const uint32 Pow2UpperBoundOf( const uint32 in )
			{
				uint32 result = 1;

				while ( result < in )
				{
					result *= 2;
				}

				return result;
			}

			const float AngleBetween( const Float3& lhs, const Float3& rhs )
			{
				const float lhsLength = Length( lhs );
				const float rhsLength = Length( rhs );
				if ( ( 0 == lhsLength )
					|| ( 0 == rhsLength ) )
				{
					return 0.0f;
				}
				else
				{
					const float dotResult = Dot( lhs, rhs );
					const float cosValue = dotResult / lhsLength / rhsLength;
					if ( cosValue > 1.0f )
					{
						return 0.0f;
					}
					else
					{
						return acos( cosValue );
					}
				}
			}

			const Float3 OthogonalProjection( const Float3& source, const Float3& normal )
			{
				return source + normal * ( -1 * Dot( source, normal ) / Dot( normal, normal ) );
			}

			const float RadToDeg( const float radian )
			{
				return radian * 180.0f / pi;
			}

			const float DegToRad( const float deg )
			{
				return deg * pi / 180.0f;
			}

			const Float3 RadToDeg( const Float3& radian )
			{
				Float3 result;
				result.x = RadToDeg( radian.x );
				result.y = RadToDeg( radian.y );
				result.z = RadToDeg( radian.z );
				return result;
			}

			const Float3 DegToRad( const Float3& deg )
			{
				Float3 result;
				result.x = DegToRad( deg.x );
				result.y = DegToRad( deg.y );
				result.z = DegToRad( deg.z );
				return result;
			}

			const Quaternion ZDirToQuaterion( const Float3& zDir )
			{
				Quaternion result;
				ZDirToMatrix( zDir ).GetRotation( result );
				return result;
			}

			const Matrix4x4 ZDirToMatrix( const Float3& zDir )
			{
				const Math::Float3 dir = Math::Normalize( zDir );
				if ( Core::Math::Length( dir ) > 0.99f )
				{					
					Core::Math::Matrix4x4 invViewRot;
					if ( abs( dir.y ) < 0.99f )
					{
						const Core::Math::Float3 new_right = Core::Math::OutProduct( dir, Math::Float3( 0.0f, 1.0f, 0.0f ) );
						const Core::Math::Float3 new_up = Core::Math::OutProduct( new_right, dir );
						invViewRot.SetX( new_right );
						invViewRot.SetY( new_up );
						invViewRot.SetZ( dir );
					}
					else
					{
						const Core::Math::Float3 new_up = Core::Math::OutProduct( Math::Float3( 1.0f, 0.0f, 0.0f ), dir );
						const Core::Math::Float3 new_right = Core::Math::OutProduct( dir, new_up );
						invViewRot.SetX( new_right );
						invViewRot.SetY( new_up );
						invViewRot.SetZ( dir );
					}
					return invViewRot;
				}
				else
				{
					assert( 0 && L"Failed to normalize." );
#ifdef EXCEPTION
					throw EXCEPTION(  Core::Exception ) << L"Failed to normalize." << std::endl;
#else
					throw;
#endif
				}
			}
						
			template<>
			const Float3 Interpolation< Float3 >( const Float3& lhs, const Float3& rhs, const float rateFromLeft )
			{
				return LinearInterpolation< Float3 >( lhs, rhs, rateFromLeft );
			}

			template<>
			const Quaternion Interpolation< Quaternion >( const Quaternion& lhs, const Quaternion& rhs, const float rateFromLeft )
			{
				return SphericalInterpolation< Quaternion >( lhs, rhs, rateFromLeft );
			}
		}
	}
}