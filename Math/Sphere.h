#pragma once

#include "IBound.h"
#include "Vector3.h"

namespace At
{
	namespace Core
	{
		namespace Math
		{
			struct Matrix4x4;
			struct BoundBox;
			struct Line;

			struct Sphere
				: public IBound
			{
				Sphere();
				Sphere( const Sphere& rhs );
				Sphere( const Float3& initCenter, float initRadius );				
				Sphere& operator = ( const Sphere& rhs );
								
				Float3 center;
				float radius;

				const Sphere& operator += ( const Sphere& rhs );
				friend bool operator < ( const Sphere& lhs, const Sphere& rhs );
				friend bool operator > ( const Sphere& lhs, const Sphere& rhs );
				friend bool operator <= ( const Sphere& lhs, const Sphere& rhs );
				friend bool operator >= ( const Sphere& lhs, const Sphere& rhs );				
				friend const Sphere operator + ( const Sphere& lhs, const Sphere& rhs );

				const Float3 NearPointOf( const Float3& point ) const;
				const bool IsInsight( const Float3& point ) const;
				const bool InsectWith( const IBound& other ) const;				
				const bool InsectWith( const Sphere& other ) const;
				const bool InsectWith( const BoundBox& other ) const;
				const bool InsectWith( const Line& line ) const;
			};

			const Sphere operator * ( const Sphere& lhs, const Matrix4x4& world );
		}
	}
}