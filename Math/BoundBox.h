#pragma once
#include <vector>
#include "Vector3.h"
#include "IBound.h"
namespace At
{
	namespace Core
	{
		namespace Math
		{	
			struct Line;
			struct Triangle;
			typedef std::vector< Triangle > Triangles;
			typedef std::vector< Line > Lines;
			typedef std::vector< Plane > Planes;

			struct BoundBox
				: public IBound
			{
				BoundBox( const Float3& initOrigin, const Float3& initPitchVector, const Float3& initRightVector
					, float initWidth, float initHeight, float initPitch );				
				Float3 origin;
				Float3 pitchVector;
				Float3 rightVector;
				Float3 heightVector;
				float width;
				float height;
				float pitch;
				
				void GetPoints( std::vector< Float3 >& points ) const;
				void GetPolygons( Triangles& triangles ) const;
				void GetPlanes( std::vector< Plane >& planes ) const;
				void GetLines( std::vector< Line >& lines ) const;

				const Float3 NearPointOf( const Float3& point ) const;
				const bool IsInsight( const Float3& point ) const;
				const bool InsectWith( const IBound& other ) const;				
				const bool InsectWith( const Sphere& other ) const;
				const bool InsectWith( const BoundBox& other ) const;
			};
		}
	}
}