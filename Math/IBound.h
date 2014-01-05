#pragma once

namespace At
{
	namespace Core
	{
		namespace Math
		{
			template< typename T >
			struct Vector3;
			typedef Vector3< float > Float3;

			struct Plane;
			struct Sphere;
			struct BoundBox;
			struct IBound
			{
			public:
				virtual const Float3 NearPointOf( const Float3& point ) const = 0;
				virtual const bool IsInsight( const Float3& point ) const = 0;
				virtual const bool InsectWith( const IBound& other ) const = 0;				
				virtual const bool InsectWith( const Sphere& other ) const = 0;
				virtual const bool InsectWith( const BoundBox& other ) const = 0;
			};
		}
	}
}