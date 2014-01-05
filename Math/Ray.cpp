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
			Ray::Ray( const Float3& initOrigin, const Float3& initDirection )
				: origin( initOrigin )
				, direction( initDirection )
			{
			}
			const Float3 Ray::NearPointOf( const Float3& point ) const
			{
				return origin + direction * Dot( direction, point - origin ) / Dot( direction, direction );
			}

			const Float3 Ray::PointAt( const float t ) const
			{
				return origin + direction * t;
			}

			const Float3 Ray::ThroughPoint( const Plane& plane ) const
			{
				const float dot = Dot( direction, plane.normal );
				if ( dot != 0 )
				{
					return origin + direction * ( Dot( plane.origin - origin, plane.normal ) / dot );
				}
				else
				{
					return plane.origin;
				}
			}

			const Float3 Ray::ThroughPoint( const Sphere& sphere ) const
			{
				const Float3 o = origin - sphere.center;
				float a = Length( direction );
				a *= a;
				const float b = 2 * Dot( o, direction );
				float c = Length( o );
				c *= c;
				c -= ( sphere.radius * sphere.radius );
				float sol1, sol2;
				if  ( SolveSecondOrderEquation( a, b, c, sol1, sol2 ) )
				{
					if ( abs( sol1 ) < abs( sol2 ) )
					{
						return origin + sol1 * direction;
					}
					else
					{
						return origin + sol2 * direction;
					}
				}
				else
				{
					return sphere.center;
				}
			}

			const bool Ray::IsThrough( const Plane& plane, const ThroughFlag::Type flag ) const
			{
				switch ( flag )
				{
				case ThroughFlag::All:
					return Dot( plane.normal, direction ) != 0;
				case ThroughFlag::CollideWithForward:
					return ( ( Dot( plane.normal, direction ) < 0 ) && plane.IsOver( origin ) )
						|| ( ( Dot( plane.normal, direction ) > 0 ) && ( plane.IsOver( origin ) == false ) );
				case ThroughFlag::CollideWithBackward:
					return ( ( Dot( plane.normal, direction ) > 0 ) && plane.IsOver( origin ) )
						|| ( ( Dot( plane.normal, direction ) < 0 ) && ( plane.IsOver( origin ) == false ) );
				default:
					assert( 0 && L"There is no matched flag." );
					return false;
				}
			}

			const bool Ray::IsThrough( const Sphere& sphere, const ThroughFlag::Type flag ) const
			{
				if ( DistanceOf( sphere.center, origin ) <= sphere.radius )
				{
					return true;
				}
				else if ( DistanceOf( *this, sphere ) <= 0 )
				{
					switch ( flag )
					{
					case ThroughFlag::All:
						return true;
					case ThroughFlag::CollideWithForward:													
						return Dot( sphere.center - origin, direction ) > 0;
					case ThroughFlag::CollideWithBackward:
						return Dot( sphere.center - origin, direction ) < 0;
					default:
						assert( 0 && L"There is no matched flag." );
						return false;
					}
				}
				else
				{
					return false;
				}
			}

			const bool Ray::IsThrough( const Triangle& triangle, Float3& throughPoint, const ThroughFlag::Type flag ) const
			{
				const Float3 triangleNormal( triangle.Normal() );
				if ( Dot( direction, triangleNormal ) == 0 )
				{
					return false;
				}

				Plane firstPlane( Triangle( origin, triangle.x, triangle.y ) );
				Plane secondPlane( Triangle( origin, triangle.y, triangle.z ) );
				Plane thirdPlane( Triangle( origin, triangle.z, triangle.x ) );

				throughPoint = ThroughPoint( Plane( triangle.x, triangleNormal ) );
				switch ( flag )
				{
				case ThroughFlag::All:
					if ( Dot( throughPoint - origin, direction ) == 0 )
					{
						return false;
					}
					break;
				case ThroughFlag::CollideWithForward:
					if ( Dot( throughPoint - origin, direction ) < 0 )
					{
						return false;
					}
					break;
				case ThroughFlag::CollideWithBackward:
					if ( Dot( throughPoint - origin, direction ) > 0 )
					{
						return false;
					}
					break;
				default:
					assert( 0 && L"There is no matched flag." );
					return false;
				}
				if ( firstPlane.IsOver(	throughPoint ) || secondPlane.IsOver( throughPoint ) || thirdPlane.IsOver( throughPoint ) )
				{
					return false;
				}
				else
				{
					return true;
				}
			}

			const Ray& Ray::operator *= ( const Matrix4x4& world )
			{
				*this = *this * world;
				return *this;
			}

			const Ray operator * ( const Ray& lhs, const Matrix4x4& world )
			{
				const Float3 origin = lhs.origin * world;
				const Float3 direction = ( Float4( lhs.direction, 0 ) * world );
				Ray result( origin, direction );
				return result;
			}
		}
	}
}