#include "../Type.h"
#include "Sphere.h"
#include "BoundBox.h"
#include "Line.h"
#include "Ray.h"
#include "Matrix.h"

namespace At
{
	namespace Core
	{
		namespace Math
		{
			Sphere::Sphere()
				: radius( 0.0f )
			{
			}

			Sphere::Sphere( const Sphere& rhs )
				: center( rhs.center ), radius( rhs.radius )
			{
			}

			Sphere::Sphere( const Float3& initCenter, float initRadius )
				: center( initCenter ), radius( initRadius )
			{
			}

			Sphere& Sphere::operator = ( const Sphere& rhs )
			{
				center = rhs.center;
				radius = rhs.radius;
				return *this;
			}
						
			const Sphere& Sphere::operator += ( const Sphere& rhs )
			{
				float distance = DistanceOf( center, rhs.center );	

				if ( distance + radius <= rhs.radius )
				{
					center = rhs.center;
					radius = rhs.radius;
					return *this;
				}
				else if ( distance + rhs.radius <= radius )
				{
					return *this;
				}
				else
				{
					center += ( ( rhs.radius - radius ) / distance + 1 ) * ( rhs.center - center ) / 2;
					radius = ( distance + radius + rhs.radius ) / 2;
					return *this;					
				}
			}
		
			bool operator < ( const Sphere& lhs, const Sphere& rhs )
			{
				return DistanceOf( lhs.center, rhs.center ) + lhs.radius < rhs.radius; 
			}
			bool operator > ( const Sphere& lhs, const Sphere& rhs )
			{
				return DistanceOf( lhs.center, rhs.center ) + rhs.radius < lhs.radius; 
			}
			bool operator <= ( const Sphere& lhs, const Sphere& rhs )
			{
				return DistanceOf( lhs.center, rhs.center ) + lhs.radius <= rhs.radius; 
			}
			bool operator >= ( const Sphere& lhs, const Sphere& rhs )
			{
				return DistanceOf( lhs.center, rhs.center ) + rhs.radius <= lhs.radius; 
			}
				
			const Sphere operator + ( const Sphere& lhs, const Sphere& rhs )
			{
				const float distance = DistanceOf( lhs.center, rhs.center );

				if ( distance + lhs.radius <= rhs.radius )
				{
					return rhs;
				}
				else if ( distance + rhs.radius <= lhs.radius )
				{
					return lhs;
				}
				else
				{
					return Sphere( lhs.center + ( ( rhs.radius - lhs.radius ) / distance + 1 ) * ( rhs.center - lhs.center ) / 2, ( distance + lhs.radius + rhs.radius ) / 2 );
				}

			}
			
			const Float3 Sphere::NearPointOf( const Float3& point ) const
			{
				Float3 dir = Normalize( point - center );

				return center + dir * radius;
			}

			const bool Sphere::IsInsight( const Float3& point ) const
			{
				return DistanceOf( point, center ) < radius;
			}
			
			const bool Sphere::InsectWith( const IBound& other ) const
			{
				return other.InsectWith( *this );
			}
						
			const bool Sphere::InsectWith( const Sphere& other ) const
			{
				return Length( other.center - center ) < radius + other.radius;
			}
			
			const bool Sphere::InsectWith( const BoundBox& other ) const
			{
				return other.InsectWith( *this );
			}

			const bool Sphere::InsectWith( const Line& line ) const
			{
				Ray ray( line.x, line.y - line.x );
				if ( ray.IsThrough( *this, Ray::ThroughFlag::CollideWithForward ) )
				{
					Float3 point = ray.ThroughPoint( *this );
					return DistanceOf( line.x, point ) < line.Length();
				}
				else
				{
					return false;
				}
			}

			const Sphere operator * ( const Sphere& lhs, const Matrix4x4& world )
			{
				return Sphere( lhs.center * world, lhs.radius );
			}
		}
	}
}