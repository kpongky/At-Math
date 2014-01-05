#pragma once

#include "Vector3.h"

namespace At
{
	namespace Core
	{
		namespace Math
		{
			struct Plane;
			struct Sphere;
			struct Triangle;
			struct Matrix4x4;
			struct Ray
			{
				struct ThroughFlag
				{
					enum Type
					{
						All = 0,
						CollideWithForward = 1,
						CollideWithBackward = 2,
					};
				};
				Ray( const Float3& initOrigin, const Float3& initDirection );
				const Float3 NearPointOf( const Float3& point ) const;
				Float3 origin;
				Float3 direction;
				const Float3 PointAt( const float t ) const;
				const Float3 ThroughPoint( const Plane& plane ) const;
				const Float3 ThroughPoint( const Sphere& sphere ) const;
				const bool IsThrough( const Plane& plane, const ThroughFlag::Type flag = ThroughFlag::All ) const;
				const bool IsThrough( const Sphere& sphere, const ThroughFlag::Type flag = ThroughFlag::All  ) const;
				const bool IsThrough( const Triangle& triangle, Float3& throughPoint, const ThroughFlag::Type flag = ThroughFlag::All ) const;				
				const Ray& operator *= ( const Matrix4x4& world );
			};

			const Ray operator * ( const Ray& lhs, const Matrix4x4& world );
		}
	}
}