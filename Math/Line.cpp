#include <assert.h>
#include <math.h>
#include "../Type.h"
#include "Line.h"
namespace At
{
	namespace Core
	{
		namespace Math
		{			
			Line::Line()
				: x( 0.0f, 0.0f, 0.0f )
				, y( 1.0f, 0.0f, 0.0f )
			{								
			}

			Line::Line( const Float3 x_, const Float3 y_ )
				: x( x_ )
				, y( y_ )
			{
				assert( x!= y );
			}

			const Float3 Line::operator [] ( const unsigned int index )
			{
				if ( 0 == index )
				{
					return x;
				}
				else if ( 1 == index )
				{
					return y;
				}
				else
				{
					assert( 0 && L"There is no index." );
#ifdef EXCEPTION
					throw Core::Exception( L"There is no index." );
#else
					throw;
#endif
				}
			}

			const bool Line::Has( const Float3& point ) const
			{
				if ( ( point == x ) || ( point == y ) )
				{
					return true;
				}
				else
				{
					return false;
				}
			}

			const bool Line::Has( const Line& line ) const
			{
				return line == *this;
			}

			bool operator == ( const Line& lhs, const Line& rhs )
			{
				return ( ( lhs.x == rhs.x ) && ( lhs.y == rhs.y ) ) || ( ( lhs.x == rhs.y ) || ( lhs.y == rhs.x ) );
			}

			bool operator != ( const Line& lhs, const Line& rhs )
			{
				return !( lhs == rhs );
			}

			bool operator < ( const Line& lhs, const Line& rhs )
			{
				if ( lhs.x < rhs.x )
				{
					return true;
				}
				else if ( lhs.x > rhs.x )
				{
					return false;
				}
				else if ( lhs.y < rhs.y )
				{
					return true;
				}
				else
				{
					return false;
				}
			}

			bool operator > ( const Line& lhs, const Line& rhs )
			{
				return rhs < lhs;
			}

			const float Line::Length() const
			{
				return Math::Length( y - x );
			}

			const float Length( const Line& line )
			{
				return line.Length();
			}
		}
	}
}