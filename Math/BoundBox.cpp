#include "../Type.h"
#include "BoundBox.h"
#include "Sphere.h"
#include "Plane.h"
#include "Line.h"
#include "Triangle.h"
namespace At
{
	namespace Core
	{
		namespace Math
		{
			BoundBox::BoundBox( const Float3& initOrigin, const Float3& initPitchVector, const Float3& initRightVector, float initWidth
				, float initHeight, float initPitch )
				: origin( initOrigin )
				, pitchVector( Normalize( initPitchVector ) )
				, rightVector( Normalize( initRightVector ) )
				, heightVector( Normalize( OutProduct( pitchVector, rightVector ) ) )
				, width( initWidth )
				, height( initHeight )
				, pitch( initPitch )
			{
			}
			
			void BoundBox::GetPoints( std::vector< Float3 >& points ) const
			{
				points.reserve( points.size() + 8 );

				points.push_back( origin );
				points.push_back( origin + rightVector * width );
				points.push_back( origin + heightVector * height );
				points.push_back( origin + rightVector * width + heightVector * height );
				points.push_back( origin + pitchVector * pitch );
				points.push_back( origin + rightVector * width + pitchVector * pitch );
				points.push_back( origin + heightVector * height + pitchVector * pitch );
				points.push_back( origin + rightVector * width + heightVector * height + pitchVector * pitch );			
			}

			void BoundBox::GetPolygons( Triangles& triangles ) const
			{
				std::vector< Float3 > points;
				GetPoints( points );

				triangles.reserve( triangles.size() + 12 );

				triangles.push_back( Triangle( points[ 0 ], points[ 1 ], points[ 2 ] ) );
				triangles.push_back( Triangle( points[ 3 ], points[ 2 ], points[ 4 ] ) );
				triangles.push_back( Triangle( points[ 1 ], points[ 5 ], points[ 2 ] ) );
				triangles.push_back( Triangle( points[ 2 ], points[ 5 ], points[ 6 ] ) );
				triangles.push_back( Triangle( points[ 2 ], points[ 6 ], points[ 4 ] ) );
				triangles.push_back( Triangle( points[ 4 ], points[ 6 ], points[ 8 ] ) );
				triangles.push_back( Triangle( points[ 4 ], points[ 8 ], points[ 3 ] ) );
				triangles.push_back( Triangle( points[ 3 ], points[ 8 ], points[ 7 ] ) );
				triangles.push_back( Triangle( points[ 3 ], points[ 7 ], points[ 1 ] ) );
				triangles.push_back( Triangle( points[ 1 ], points[ 7 ], points[ 5 ] ) );
				triangles.push_back( Triangle( points[ 5 ], points[ 7 ], points[ 6 ] ) );
				triangles.push_back( Triangle( points[ 6 ], points[ 7 ], points[ 8 ] ) );
			}

			void BoundBox::GetPlanes( std::vector< Plane >& planes ) const
			{
				planes.push_back( Plane( origin, pitchVector ) );
				planes.push_back( Plane( origin, rightVector ) );
				planes.push_back( Plane( origin, heightVector ) );
				Float3 upperSideOrigin = origin + rightVector * width + heightVector * height + pitchVector * pitch;
				planes.push_back( Plane( upperSideOrigin, -pitchVector ) );
				planes.push_back( Plane( upperSideOrigin, -rightVector ) );
				planes.push_back( Plane( upperSideOrigin, -heightVector ) );
			}

			void BoundBox::GetLines( Lines& lines ) const
			{
				std::vector< Float3 > points;
				GetPoints( points );
				lines.push_back( Line( points[ 0 ], points[ 1 ] ) );
				lines.push_back( Line( points[ 0 ], points[ 2 ] ) );
				lines.push_back( Line( points[ 0 ], points[ 4 ] ) );
				lines.push_back( Line( points[ 1 ], points[ 3 ] ) );
				lines.push_back( Line( points[ 1 ], points[ 5 ] ) );
				lines.push_back( Line( points[ 2 ], points[ 3 ] ) );
				lines.push_back( Line( points[ 2 ], points[ 6 ] ) );
				lines.push_back( Line( points[ 3 ], points[ 7 ] ) );
				lines.push_back( Line( points[ 4 ], points[ 5 ] ) );
				lines.push_back( Line( points[ 4 ], points[ 6 ] ) );
				lines.push_back( Line( points[ 5 ], points[ 7 ] ) );
				lines.push_back( Line( points[ 6 ], points[ 7 ] ) );
			}

			const Float3 BoundBox::NearPointOf( const Float3& point ) const
			{
				Planes planes;
				GetPlanes( planes );

				Float3 result = planes[ 0 ].NearPointOf( point );

				float distanceWithResult = Length( result - point );

				for ( unsigned int index = 0; index < planes.size(); ++index )
				{
					Float3 nearPoint = planes[ index ].NearPointOf( point );

					float length = Length( nearPoint - point );
					if ( length < distanceWithResult )
					{
						result = nearPoint;
						distanceWithResult = length;
					}
				}
				return result;
			}

			const bool BoundBox::IsInsight( const Float3& point ) const
			{
				Float3 distanceVector = point - origin;
				if( Dot( distanceVector, rightVector ) / Length( rightVector ) >= width )
				{
					return false;
				}
				if( Dot( distanceVector, pitchVector ) / Length( pitchVector ) >= pitch )
				{
					return false;
				}
				if( Dot( distanceVector, heightVector ) / Length( heightVector ) >= height )
				{
					return false;
				}
				return true;
			}

			const bool BoundBox::InsectWith( const IBound& other ) const
			{
				return other.InsectWith( *this );
			}
						
			const bool BoundBox::InsectWith( const Sphere& other ) const
			{
				Planes planes;

				planes.push_back( Plane( origin, pitchVector ) );
				planes.push_back( Plane( origin, rightVector ) );
				planes.push_back( Plane( origin, heightVector ) );
				Float3 upperSideOrigin = origin + rightVector * width + heightVector * height + pitchVector * pitch;
				planes.push_back( Plane( upperSideOrigin, -pitchVector ) );
				planes.push_back( Plane( upperSideOrigin, -rightVector ) );
				planes.push_back( Plane( upperSideOrigin, -heightVector ) );

				for ( size_t index = 0; index < planes.size(); ++index )
				{
					if ( planes[ index ].IsOver( other ) )
					{
						return true;
					}
				}

				Lines lines;
				GetLines( lines );

				for ( size_t index = 0; index < lines.size(); ++index )
				{
					if ( other.InsectWith( lines[ index ] ) )
					{
						return false;
					}
				}

				return true;
			}
			
			const bool BoundBox::InsectWith( const BoundBox& other ) const
			{
//OBB
				other;
				return false;
			}
		}
	}
}