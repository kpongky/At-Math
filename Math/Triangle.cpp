#include <assert.h>
#include <math.h>
#include "../Type.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Triangle.h"
#include "Line.h"
#include "Matrix.h"
namespace At
{
	namespace Core
	{
		namespace Math
		{
			Triangle::Triangle()
				: x( 0.0f, 0.0f, 0.0f )
				, y( 0.0f, 1.0f, 0.0f )
				, z( 1.0f, 1.0f, 0.0f )
			{
			}

			Triangle::Triangle( const Triangle& rhs )
				: x( rhs.x )
				, y( rhs.y )
				, z( rhs.z )
			{
			}

			Triangle::Triangle( const Float3& x_, const Float3& y_, const Float3& z_ )
				: x( x_ )
				, y( y_ )
				, z( z_ )
			{
				assert( ( x!= y ) && ( y != z ) && ( z != x ) );
			}

			const Float3 Triangle::Normal() const
			{
				return Normalize( OutProduct( y - x, z - x ) );
			}

			const bool Triangle::Has( const Float3& point ) const
			{
				if ( ( point == x ) || ( point == y ) || ( point == z ) )
				{
					return true;
				}
				else
				{
					return false;
				}
			}

			const bool Triangle::Has( const Line& line ) const
			{
				if ( Line( x, y ) == line ) 
				{
					return true;
				} 
				else if ( Line( y, z ) == line ) 
				{
					return true;
				} 
				else if ( Line( z, x ) == line ) 
				{
					return true;
				}
				else 
				{
					return false;
				}
			}

			const bool Triangle::Has( const Triangle& triangle ) const
			{
				return triangle == *this;
			}

			const Float3 Triangle::operator [] ( const unsigned int index )
			{
				switch ( index )
				{
				case 0:
					return x;
				case 1:
					return y;
				case 2:
					return z;
				default:
					assert( 0 && L"There is no index." );
					throw;
				}
			}
						
			bool operator == ( const Triangle& lhs, const Triangle& rhs )
			{
				return ( ( lhs.x == rhs.x ) && ( lhs.y == rhs.y ) && ( lhs.z == rhs.z ) )
					|| ( ( lhs.x == rhs.y ) && ( lhs.y == rhs.z ) && ( lhs.z == rhs.x ) )
					|| ( ( lhs.x == rhs.z ) && ( lhs.y == rhs.x ) && ( lhs.z == rhs.y ) );
			}

			bool operator != ( const Triangle& lhs, const Triangle& rhs )
			{
				return !( lhs == rhs );
			}

			bool operator < ( const Triangle& lhs, const Triangle& rhs )
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
				else if ( lhs.y > rhs.y )
				{
					return false;
				}
				else if ( lhs.z < rhs.z )
				{
					return true;
				}
				else
				{
					return false;
				}
			}

			bool operator > ( const Triangle& lhs, const Triangle& rhs )
			{
				return rhs < lhs;
			}

			const Triangle operator * ( const Triangle& lhs, const Matrix4x4& rhs )
			{
				Triangle result;
				result.x = lhs.x * rhs;
				result.y = lhs.y * rhs;
				result.z = lhs.z * rhs;
				return result;
			}
		}
	}
}