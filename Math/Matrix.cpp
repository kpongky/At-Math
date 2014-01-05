#include <math.h>

#include "../Type.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Quaternion.h"
#include "Matrix.h"

namespace At
{
	namespace Core
	{
		namespace Math
		{
			const Matrix4x4 Matrix4x4::e( 1, 0, 0, 0
										, 0, 1, 0, 0
										, 0, 0, 1, 0
										, 0, 0, 0, 1 );	
			Matrix4x4::Matrix4x4()
			{
				m00 = 1.0f;
				m01 = 0.0f;
				m02 = 0.0f;
				m03 = 0.0f;

				m10 = 0.0f;
				m11 = 1.0f;
				m12 = 0.0f;
				m13 = 0.0f;

				m20 = 0.0f;
				m21 = 0.0f;
				m22 = 1.0f;
				m23 = 0.0f;

				m30 = 0.0f;
				m31 = 0.0f;
				m32 = 0.0f;
				m33 = 1.0f;
			}

			Matrix4x4::Matrix4x4( const Matrix4x4& rhs )
			{
				m00 = rhs.m00;
				m01 = rhs.m01;
				m02 = rhs.m02;
				m03 = rhs.m03;

				m10 = rhs.m10;
				m11 = rhs.m11;
				m12 = rhs.m12;
				m13 = rhs.m13;

				m20 = rhs.m20;
				m21 = rhs.m21;
				m22 = rhs.m22;
				m23 = rhs.m23;

				m30 = rhs.m30;
				m31 = rhs.m31;
				m32 = rhs.m32;
				m33 = rhs.m33;
			}

			Matrix4x4::Matrix4x4( Element _11, Element _12, Element _13, Element _14
				, Element _21, Element _22, Element _23, Element _24
				, Element _31, Element _32, Element _33, Element _34
				, Element _41, Element _42, Element _43, Element _44 )					
			{
				m00 = _11;
				m01 = _12;
				m02 = _13;
				m03 = _14;

				m10 = _21;
				m11 = _22;
				m12 = _23;
				m13 = _24;

				m20 = _31;
				m21 = _32;
				m22 = _33;
				m23 = _34;

				m30 = _41;
				m31 = _42;
				m32 = _43;
				m33 = _44;
			}

			const Matrix4x4 Matrix4x4::T() const
			{
				return Matrix4x4( m00, m10, m20, m30
				, m01, m11, m21, m31
				, m02, m12, m22, m32
				, m03, m13, m23, m33 );
			}

			void Matrix4x4::SetT( const Vector3& position )
			{
				m30 = position.x;
				m31 = position.y;
				m32 = position.z;
			}
					
			void Matrix4x4::SetX( const Vector3& axis )
			{
				m00 = axis.x;
				m01 = axis.y;
				m02 = axis.z;
			}	
				
			void Matrix4x4::SetY( const Vector3& axis )
			{
				m10 = axis.x;
				m11 = axis.y;
				m12 = axis.z;
			}
				
			void Matrix4x4::SetZ( const Vector3& axis )
			{
				m20 = axis.x;
				m21 = axis.y;
				m22 = axis.z;
			}
			const Matrix4x4::Vector3 Matrix4x4::GetT() const
			{
				return Vector3( m30, m31, m32 );
			}

			const Matrix4x4::Vector3 Matrix4x4::GetX() const
			{
				return Vector3( m00, m01, m02 );
			}				
			const Matrix4x4::Vector3 Matrix4x4::GetY() const
			{
				return Vector3( m10, m11, m12 );
			}
			const Matrix4x4::Vector3 Matrix4x4::GetZ() const
			{
				return Vector3( m20, m21, m22 );
			}

			void Matrix4x4::GetRotation( Quaternion& result ) const
			{					
				float tr = m00 + m11 + m22;

				Quaternion& q = result;
				if (tr > 0)
				{ 
					float S = sqrt( tr + 1.0f ) * 2.0f; // S=4*qw 
					q.w = 0.25f * S;
					q.x = (m12 - m21) / S;
					q.y = (m20 - m02) / S; 
					q.z = (m01 - m10) / S; 
				} 
				else if ((m00 > m11)&(m00 > m22)) 
				{ 
					float S = sqrt( 1.0f + m00 - m11 - m22 ) * 2.0f; // S=4*qx 
					q.w = (m12 - m21) / S;
					q.x = 0.25f * S;
					q.y = (m10 + m01) / S; 
					q.z = (m20 + m02) / S; 
				} 
				else if (m11 > m22) 
				{ 
					float S = sqrt(1.0f + m11 - m00 - m22) * 2.0f; // S=4*qy
					q.w = (m20 - m02) / S;
					q.x = (m10 + m01) / S; 
					q.y = 0.25f * S;
					q.z = (m21 + m12) / S; 
				} 
				else 
				{ 
					float S = sqrt(1.0f + m22 - m00 - m11) * 2.0f; // S=4*qz
					q.w = (m01 - m10) / S;
					q.x = (m20 + m02) / S;
					q.y = (m21 + m12) / S;
					q.z = 0.25f * S;
				}
			}
			const Matrix4x4 Matrix4x4::Inverse() const
			{
				Element fA0 = m00 * m11 - m01 * m10;
				Element fA1 = m00 * m12 - m02 * m10;
				Element fA2 = m00 * m13 - m03 * m10;
				Element fA3 = m01 * m12 - m02 * m11;
				Element fA4 = m01 * m13 - m03 * m11;
				Element fA5 = m02 * m13 - m03 * m12;

				Element fB0 = m20 * m31 - m21 * m30;
				Element fB1 = m20 * m32 - m22 * m30;
				Element fB2 = m20 * m33 - m23 * m30;
				Element fB3 = m21 * m32 - m22 * m31;
				Element fB4 = m21 * m33 - m23 * m31;
				Element fB5 = m22 * m33 - m23 * m32;

				Element det = fA0 * fB5 - fA1 * fB4 + fA2 * fB3 + fA3 * fB2 - fA4 * fB1 + fA5 * fB0;

				if ( 0.0f == det )
				{
					return Matrix4x4( 0.0f, 0.0f, 0.0f, 0.0f
						, 0.0f, 0.0f, 0.0f, 0.0f
						, 0.0f, 0.0f, 0.0f, 0.0f
						, 0.0f, 0.0f, 0.0f, 0.0f );
				}

				Matrix4x4 result;

				result.m00 = m11 * fB5 - m12 * fB4 + m13 * fB3;
				result.m10 = -m10 * fB5 + m12 * fB2 - m13 * fB1;
				result.m20 = m10 * fB4 - m11 * fB2 + m13 * fB0;
				result.m30 = -m10 * fB3 + m11 * fB1 - m12 * fB0;

				result.m01 = -m01 * fB5 + m02 * fB4 - m03 * fB3;
				result.m11 = m00 * fB5 - m02 * fB2 + m03 * fB1;
				result.m21 = -m00 * fB4 + m01 * fB2 - m03 * fB0;
				result.m31 = m00 * fB3 - m01 * fB1 + m02 * fB0;

				result.m02 = m31 * fA5 - m32 * fA4 + m33 * fA3;
				result.m12 = -m30 * fA5 + m32 * fA2 - m33 * fA1;
				result.m22 = m30 * fA4 - m31 * fA2 + m33 * fA0;
				result.m32 = -m30 * fA3 + m31 * fA1 - m32 * fA0;

				result.m03 = -m21 * fA5 + m22 * fA4 - m23 * fA3;
				result.m13 = m20 * fA5 - m22 * fA2 + m23 * fA1;
				result.m23 = -m20 * fA4 + m21 * fA2 - m23 * fA0;
				result.m33 = m20 * fA3 - m21 * fA1 + m22 * fA0;

				return result * ( 1.0f/ det );
			}
			
			void Matrix4x4::operator *= ( const Scalar rhs )
			{
				*this = rhs * ( *this );
			}

			void Matrix4x4::operator *= ( const Matrix4x4& matrix )
			{
				*this = ( *this ) * matrix;
			}
			void Matrix4x4::operator += ( const Matrix4x4& matrix )
			{
				*this = ( *this ) + matrix;
			}	
			void Matrix4x4::operator -= ( const Matrix4x4& matrix )
			{
				*this = ( *this ) - matrix;
			}		
			
			const Matrix4x4 operator * ( const Matrix4x4::Scalar lhs, const Matrix4x4& rhs )
			{
				return Matrix4x4( lhs * rhs.m00, lhs * rhs.m01, lhs * rhs.m02, lhs * rhs.m03
					, lhs * rhs.m10, lhs * rhs.m11, lhs * rhs.m12, lhs * rhs.m13
					, lhs * rhs.m20, lhs * rhs.m21, lhs * rhs.m22, lhs * rhs.m23
					, lhs * rhs.m30, lhs * rhs.m31, lhs * rhs.m32, lhs * rhs.m33 );
			}

			const Matrix4x4 operator * ( const Matrix4x4& lhs, const Matrix4x4::Scalar rhs )
			{
				return rhs * lhs;
			}

			const Matrix4x4 operator * ( const Matrix4x4& lhs, const Matrix4x4& rhs )
			{
				return Matrix4x4( lhs.m00 * rhs.m00 + lhs.m01 * rhs.m10 + lhs.m02 * rhs.m20 + lhs.m03 * rhs.m30
					, lhs.m00 * rhs.m01 + lhs.m01 * rhs.m11 + lhs.m02 * rhs.m21 + lhs.m03 * rhs.m31
					, lhs.m00 * rhs.m02 + lhs.m01 * rhs.m12 + lhs.m02 * rhs.m22 + lhs.m03 * rhs.m32
					, lhs.m00 * rhs.m03 + lhs.m01 * rhs.m13 + lhs.m02 * rhs.m23 + lhs.m03 * rhs.m33

					, lhs.m10 * rhs.m00 + lhs.m11 * rhs.m10 + lhs.m12 * rhs.m20 + lhs.m13 * rhs.m30
					, lhs.m10 * rhs.m01 + lhs.m11 * rhs.m11 + lhs.m12 * rhs.m21 + lhs.m13 * rhs.m31
					, lhs.m10 * rhs.m02 + lhs.m11 * rhs.m12 + lhs.m12 * rhs.m22 + lhs.m13 * rhs.m32
					, lhs.m10 * rhs.m03 + lhs.m11 * rhs.m13 + lhs.m12 * rhs.m23 + lhs.m13 * rhs.m33
					
					, lhs.m20 * rhs.m00 + lhs.m21 * rhs.m10 + lhs.m22 * rhs.m20 + lhs.m23 * rhs.m30
					, lhs.m20 * rhs.m01 + lhs.m21 * rhs.m11 + lhs.m22 * rhs.m21 + lhs.m23 * rhs.m31
					, lhs.m20 * rhs.m02 + lhs.m21 * rhs.m12 + lhs.m22 * rhs.m22 + lhs.m23 * rhs.m32
					, lhs.m20 * rhs.m03 + lhs.m21 * rhs.m13 + lhs.m22 * rhs.m23 + lhs.m23 * rhs.m33
					
					, lhs.m30 * rhs.m00 + lhs.m31 * rhs.m10 + lhs.m32 * rhs.m20 + lhs.m33 * rhs.m30
					, lhs.m30 * rhs.m01 + lhs.m31 * rhs.m11 + lhs.m32 * rhs.m21 + lhs.m33 * rhs.m31
					, lhs.m30 * rhs.m02 + lhs.m31 * rhs.m12 + lhs.m32 * rhs.m22 + lhs.m33 * rhs.m32
					, lhs.m30 * rhs.m03 + lhs.m31 * rhs.m13 + lhs.m32 * rhs.m23 + lhs.m33 * rhs.m33 );					
			}

			const Matrix4x4 operator + ( const Matrix4x4& lhs, const Matrix4x4& rhs )
			{
				return Matrix4x4( lhs.m00 + rhs.m00, lhs.m01 + rhs.m01, lhs.m02 + rhs.m02, lhs.m03 + rhs.m03
					, lhs.m10 + rhs.m10, lhs.m11 + rhs.m11, lhs.m12 + rhs.m12, lhs.m13 + rhs.m13
					, lhs.m20 + rhs.m20, lhs.m21 + rhs.m21, lhs.m22 + rhs.m22, lhs.m23 + rhs.m23
					, lhs.m30 + rhs.m30, lhs.m31 + rhs.m31, lhs.m32 + rhs.m32, lhs.m33 + rhs.m33 );
			}
			const Matrix4x4 operator - ( const Matrix4x4& lhs, const Matrix4x4& rhs )
			{
				return Matrix4x4( lhs.m00 - rhs.m00, lhs.m01 - rhs.m01, lhs.m02 - rhs.m02, lhs.m03 - rhs.m03
								, lhs.m10 - rhs.m10, lhs.m11 - rhs.m11, lhs.m12 - rhs.m12, lhs.m13 - rhs.m13
								, lhs.m20 - rhs.m20, lhs.m21 - rhs.m21, lhs.m22 - rhs.m22, lhs.m23 - rhs.m23
								, lhs.m30 - rhs.m30, lhs.m31 - rhs.m31, lhs.m32 - rhs.m32, lhs.m33 - rhs.m33 );
			}
			const Matrix4x4::Vector3 operator * ( const Matrix4x4::Vector3& lhs, const Matrix4x4& rhs )
			{
				return Matrix4x4::Vector3(   lhs.x * rhs.m00 + lhs.y * rhs.m10 + lhs.z * rhs.m20 + rhs.m30
										   , lhs.x * rhs.m01 + lhs.y * rhs.m11 + lhs.z * rhs.m21 + rhs.m31
										   , lhs.x * rhs.m02 + lhs.y * rhs.m12 + lhs.z * rhs.m22 + rhs.m32 );
			}

			const Matrix4x4::Vector4 operator * ( const Matrix4x4::Vector4& lhs, const Matrix4x4& rhs )
			{
				return Matrix4x4::Vector4(   lhs.x * rhs.m00 + lhs.y * rhs.m10 + lhs.z * rhs.m20 + lhs.w * rhs.m30 
										   , lhs.x * rhs.m01 + lhs.y * rhs.m11 + lhs.z * rhs.m21 + lhs.w * rhs.m31
										   , lhs.x * rhs.m02 + lhs.y * rhs.m12 + lhs.z * rhs.m22 + lhs.w * rhs.m32
										   , lhs.x * rhs.m03 + lhs.y * rhs.m13 + lhs.z * rhs.m23 + lhs.w * rhs.m33 );
			}
		}
	}
}