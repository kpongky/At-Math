#pragma once

namespace At
{
	namespace Core
	{
		namespace Math
		{	
			struct Line;
			struct Triangle
			{		
				Triangle();
				Triangle( const Triangle& rhs );
				Triangle( const Float3& x_, const Float3& y_, const Float3& z_ );				
				const Float3 Normal() const;
				const bool Has( const Float3& point ) const;
				const bool Has( const Line& line ) const;
				const bool Has( const Triangle& triangle ) const;

				const Float3 operator [] ( const unsigned int index );
				
				Float3 x;
				Float3 y;
				Float3 z;
			};

			bool operator == ( const Triangle& lhs, const Triangle& rhs );

			bool operator != ( const Triangle& lhs, const Triangle& rhs );

			bool operator < ( const Triangle& lhs, const Triangle& rhs );

			bool operator > ( const Triangle& lhs, const Triangle& rhs );

			struct Matrix4x4;

			const Triangle operator * ( const Triangle& lhs, const Matrix4x4& rhs );
		}
	}
}