#pragma once

namespace At
{
	namespace Core
	{
		namespace Math
		{
			struct Matrix4x4;
			struct Quaternion
			{
				float x;
				float y;
				float z;
				float w;

				Quaternion( const float x_/*i*/, const float y_/*j*/, const float z_/*k*/, const float w_ );
				Quaternion( const Float3& euler );
				Quaternion( const Quaternion& rhs );
				Quaternion( const Float3& axis, const float angle );
				Quaternion();
				
				virtual ~Quaternion();

				const Quaternion& operator = ( const Quaternion& rhs );	

				void operator += ( const Quaternion& rhs );
				void operator -= ( const Quaternion& rhs );
				void operator *= ( const float scalar );
				void operator /= ( const float scalar );

				const Matrix4x4 ToMatrix() const;

				const Quaternion Conjugate() const;
				
				const Float3 Axis() const;
				const Float3 ToEuler() const;
				static const Quaternion e;
			};

			const float Length( const Quaternion& rhs );

			const float Dot( const Quaternion& lhs, const Quaternion& rhs );
			static const Quaternion e_quat( 0.0f, 0.0f, 0.0f, 1.0f );
			Core::Math::Float3 operator * ( const Core::Math::Float3& lhs, const Core::Math::Quaternion& rhs );
			Core::Math::Float4 operator * ( const Core::Math::Float4& lhs, const Core::Math::Quaternion& rhs );
			Core::Math::Quaternion operator + ( const Core::Math::Quaternion& lhs, const Core::Math::Quaternion& rhs );
			Core::Math::Quaternion operator * ( const Core::Math::Quaternion& lhs, const Core::Math::Quaternion& rhs );
			Core::Math::Quaternion operator * ( const float scalar, const Core::Math::Quaternion& rhs );
			Core::Math::Quaternion operator * ( const Core::Math::Quaternion& lhs, const float scalar );
			Core::Math::Quaternion operator / ( const Core::Math::Quaternion& lhs, const float scalar );
			const bool operator == ( const Core::Math::Quaternion& lhs, const Core::Math::Quaternion& rhs );
			const bool operator != ( const Core::Math::Quaternion& lhs, const Core::Math::Quaternion& rhs );
		}

	}
}