#pragma once

#include "Vector3.h"

namespace At
{
	namespace Core
	{
		namespace Math
		{			
			struct Line
			{
				Line();
				Line( const Float3 x_, const Float3 y_ );
				const Float3 operator [] ( const unsigned int index );

				const float Length() const;
				const bool Has( const Float3& point ) const;
				const bool Has( const Line& line ) const;

				Float3 x;
				Float3 y;				
			};

			bool operator == ( const Line& lhs, const Line& rhs );

			bool operator != ( const Line& lhs, const Line& rhs );

			bool operator < ( const Line& lhs, const Line& rhs );

			bool operator > ( const Line& lhs, const Line& rhs );

			const float Length( const Line& line );
		}
	}
}