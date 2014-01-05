#include "../Type.h"
#include "Math.h"
namespace At
{
	namespace Core
	{
		namespace Math
		{
			const Plane Plane::xz = Plane( Core::Math::Float3( 0.0f, 0.0f, 0.0f ), Core::Math::Float3( 0.0f, 1.0f, 0.0f ) );
			const Plane Plane::xy = Plane( Core::Math::Float3( 0.0f, 0.0f, 0.0f ), Core::Math::Float3( 0.0f, 0.0f, 1.0f ) );
			const Plane Plane::yz = Plane( Core::Math::Float3( 0.0f, 0.0f, 0.0f ), Core::Math::Float3( 1.0f, 0.0f, 0.0f ) );
			const Plane Plane::xzBack = Plane( Core::Math::Float3( 0.0f, 0.0f, 0.0f ), Core::Math::Float3( 0.0f, -1.0f, 0.0f ) );
			const Plane Plane::xyBack = Plane( Core::Math::Float3( 0.0f, 0.0f, 0.0f ), Core::Math::Float3( 0.0f, 0.0f, -1.0f ) );
			const Plane Plane::yzBack = Plane( Core::Math::Float3( 0.0f, 0.0f, 0.0f ), Core::Math::Float3( -1.0f, 0.0f, 0.0f ) );

			Plane::Plane()
				: origin( 0, 0, 0 )
				, normal( 0, 1, 0 )
			{
			}
			Plane::Plane(  const Float3& initPoint, const Float3& initNormal )
				: origin( initPoint )
				, normal( initNormal )
			{
			}

			Plane::Plane( const Triangle& triangle )
				: origin( triangle.x )
				, normal( OutProduct( triangle.z - triangle.x, triangle.y - triangle.x ) )
			{
			}

			const Float3 Plane::NearPointOf( const Float3& point ) const
			{
				return point + ( Dot( origin - point, normal ) / Dot( normal, normal ) ) * normal;
			}

			const bool Plane::IsOver( const Float3& point ) const
			{
				return Dot( point - origin, normal ) > 0;
			}
			const bool Plane::IsOver( const Sphere& sphere ) const
			{
				if ( DistanceOf( *this, sphere.center ) - sphere.radius >= 0 )
				{
					return IsOver( sphere.center );
				}
				else
				{
					return false;
				}					
			}
			const bool Plane::IsOver( const Triangle& triangle ) const
			{
				return IsOver( triangle.x ) && IsOver( triangle.y ) && IsOver( triangle.z );
			}
		}
	}
}