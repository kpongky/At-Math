#pragma once

namespace At
{
	namespace Core
	{
		namespace Math
		{
			struct Quaternion;
			struct Matrix4x4
			{
				typedef float Element;
				typedef float Scalar;
				typedef Float3 Vector3;
				typedef Float4 Vector4;

				Element m00, m01, m02, m03;
				Element m10, m11, m12, m13;
				Element m20, m21, m22, m23;
				Element m30, m31, m32, m33;

				Matrix4x4();
				Matrix4x4( const Matrix4x4& rhs );
				Matrix4x4( Element _11, Element _12, Element _13, Element _14
					, Element _21, Element _22, Element _23, Element _24
					, Element _31, Element _32, Element _33, Element _34
					, Element _41, Element _42, Element _43, Element _44 );

				const Matrix4x4 T() const;

				void SetT( const Vector3& position );					
				void SetX( const Vector3& axis );
				void SetY( const Vector3& axis );
				void SetZ( const Vector3& axis );

				const Vector3 GetT() const;
				const Vector3 GetX() const;				
				const Vector3 GetY() const;
				const Vector3 GetZ() const;

				void GetRotation( Quaternion& quat ) const;

				const Matrix4x4 Inverse() const;
				
				void operator *= ( const Scalar rhs );
				void operator *= ( const Matrix4x4& matrix );
				void operator += ( const Matrix4x4& matrix );
				void operator -= ( const Matrix4x4& matrix );
				
				static const Matrix4x4 e;
			};	
			
			const Matrix4x4 operator * ( const Matrix4x4::Scalar lhs, const Matrix4x4& rhs );

			const Matrix4x4 operator * ( const Matrix4x4& lhs, const Matrix4x4::Scalar rhs );

			const Matrix4x4 operator * ( const Matrix4x4& lhs, const Matrix4x4& rhs );

			const Matrix4x4 operator + ( const Matrix4x4& lhs, const Matrix4x4& rhs );

			const Matrix4x4 operator - ( const Matrix4x4& lhs, const Matrix4x4& rhs );

			const Matrix4x4::Vector3 operator * ( const Matrix4x4::Vector3& lhs, const Matrix4x4& rhs );

			const Matrix4x4::Vector4 operator * ( const Matrix4x4::Vector4& lhs, const Matrix4x4& rhs );				
		}	
	}
}