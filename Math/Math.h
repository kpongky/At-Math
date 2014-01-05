#pragma once

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Quaternion.h"
#include "Matrix.h"
#include "Rectangle.h"

#ifdef USEATTYPE
namespace At
{
	typedef At::Core::Math::Float2 float2;
	typedef At::Core::Math::Uint2 uint2;
	typedef At::Core::Math::Int2 int2;
	typedef At::Core::Math::Float3 float3;
	typedef At::Core::Math::Float4 float4;
	typedef At::Core::Math::Quaternion quat;
	typedef At::Core::Math::Matrix4x4 matrix4x4;
	typedef At::Core::Math::Rectangle< At::int32 > intrect;	
}
#endif


namespace At
{
	namespace Core
	{
		namespace Math
		{
			struct Axis
			{
				enum Type
				{
					X = 0,
					Y,
					Z,
					XYZ,
					XZY,
					YXZ,
					YZX,
					ZXY,
					ZYX,					
				};
			};

			
			template< typename T >
			void Swap( T& lhs, T& rhs )
			{
				T temp = lhs;
				lhs = rhs;
				rhs = temp;
			}
			const bool SolveSecondOrderEquation( const float a, const float b, const float c, float& solution1, float& solution2 );

			const Matrix4x4 ProjectionMatrix( float width, float height, float nearDistance, float farDistance, bool isPerspective = true );

			const Matrix4x4 TransMatrix( const float x, const float y, const float z );
			const Matrix4x4 TransMatrix( const Float3& rhs );			

			const Matrix4x4 EulerRotation( Axis::Type about, const float radian );
			const Matrix4x4 EulerRotationX( const float radian );
			const Matrix4x4 EulerRotationY( const float radian );
			const Matrix4x4 EulerRotationZ( const float radian );

			const Matrix4x4 ScaleMatrix( const float scale );
			const Matrix4x4 ScaleMatrix( const Float3& scale );
			const Float3 ConvertToScale( const Matrix4x4& scaleMatrix );

			const float AspectRatio( const Matrix4x4& projectionMatrix );

			const uint32 Pow2UpperBoundOf( const uint32 in );

			const float AngleBetween( const Float3& lhs, const Float3& rhs );

			const Float3 OthogonalProjection( const Float3& source, const Float3& normal );

			const float pi = 3.14159265f;

			const float RadToDeg( const float radian );
			const float DegToRad( const float deg );

			const Float3 RadToDeg( const Float3& radian );
			const Float3 DegToRad( const Float3& deg );
			const Quaternion ZDirToQuaterion( const Float3& zDir );
			const Matrix4x4 ZDirToMatrix( const Float3& zDir );

			//±¸ÇöÀº MathUtility.cpp

			template< typename T >
			const T SphericalInterpolation( const T& lhs, const T& rhs, float rateFromLeft )
			{
				T result;
				
				float dotResult = Math::Dot( lhs, rhs );

				float arg = 0.0f;

				bool inv = false;

				if ( dotResult < 0.0f )
				{					
					dotResult = -dotResult;

					inv = true;
				}

				if ( rateFromLeft == 0.0f )
				{
					result = lhs;

					return result;
				}

				if ( dotResult >= 1.0f )
				{
					if ( inv )
					{
						result = ( ( 1 - rateFromLeft ) * lhs + rateFromLeft * ( rhs * -1.0f ) );
					}
					else
					{
						result = ( ( 1 - rateFromLeft ) * lhs + rateFromLeft * rhs );
					}
				}
				else
				{								
					arg = acos( dotResult );
					
					float sinArg = sin( arg );

					float lhsRotConst = sin( arg * ( 1 - rateFromLeft ) );

					float rhsRotConst = sin( arg * rateFromLeft );

					if ( inv )
					{
						result = ( lhsRotConst * lhs + rhsRotConst * ( rhs * -1.0f ) ) / sinArg;
					}
					else
					{
						result = ( lhsRotConst * lhs + rhsRotConst * rhs ) / sinArg;
					}
				}

				return result;
			}
			
			template< typename T >
			const T LinearInterpolation( const T& lhs, const T& rhs, float rateFromLeft )
			{
				return lhs * ( 1 - rateFromLeft ) + rhs * rateFromLeft;
			}

			template< typename T >
			const T Interpolation( const T& lhs, const T& rhs, const float rateFromLeft );

			template<>
			const Float3 Interpolation< Float3 >( const Float3& lhs, const Float3& rhs, const float rateFromLeft );

			template<>
			const Quaternion Interpolation< Quaternion >( const Quaternion& lhs, const Quaternion& rhs, const float rateFromLeft );
		}
	}
}