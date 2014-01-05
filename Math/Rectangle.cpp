#include "../Type.h"
#include "Math.h"

namespace At
{
	namespace Core
	{
		namespace Math
		{
			const UintRect Convert( const FloatRect& floatRect, const Uint2& screenSize )
			{
				return UintRect( static_cast< unsigned long >( ( floatRect.left + 1.0f ) / 2.0f * screenSize.x )
					, static_cast< unsigned long >( ( floatRect.top + 1.0f ) / 2.0f * screenSize.x )
					, static_cast< unsigned long >( ( floatRect.right + 1.0f ) / 2.0f * screenSize.x )
					, static_cast< unsigned long >( ( floatRect.bottom + 1.0f ) / 2.0f * screenSize.x ) );
			}
			const FloatRect Convert( const UintRect& uintRect, const Uint2& screenSize )
			{
				return FloatRect( static_cast< float >( uintRect.left ) / screenSize.x * 2.0f - 1.0f
					, static_cast< float >( uintRect.top ) / screenSize.x * 2.0f - 1.0f
					, static_cast< float >( uintRect.right ) / screenSize.x * 2.0f - 1.0f
					, static_cast< float >( uintRect.bottom ) / screenSize.x * 2.0f - 1.0f );
			}
		}
	}
}