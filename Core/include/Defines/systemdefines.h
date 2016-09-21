#ifndef _SYSTEMDEFINES_H

#include "Helpers\Singleton.h"
#include "Core\System\Manager\SystemManager.h"

#define GetSystem(x, y) dynamic_cast< x* >( Singleton<SystemManager>::GetInstance().getSystem( y ) )

#endif // !_SYSTEMDEFINES_H
