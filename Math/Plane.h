#pragma once

namespace At
{
	namespace Core
	{
		namespace Math
		{	
			struct Triangle;
			struct Sphere;
			struct Plane
			{
				Plane();
				Plane( const Float3& initPoint, const Float3& initNormal );
				Plane( const Triangle& triangle );
				const Float3 NearPointOf( const Float3& point ) const;
				const bool IsOver( const Float3& point ) const;
				const bool IsOver( const Sphere& sphere ) const;
				const bool IsOver( const Triangle& triangle ) const;
				
				Float3 origin;
				Float3 normal;

				static const Plane xz;
				static const Plane xy;
				static const Plane yz;
				static const Plane xzBack;
				static const Plane xyBack;
				static const Plane yzBack;
			};
		}
	}
}