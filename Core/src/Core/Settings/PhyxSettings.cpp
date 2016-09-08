#include "Core/Settings/PhyxSettings.h"

PhyxSettings::PhyxSettings()
	:Settings()
	, gravity( 9.81f )
	, velocityInterpolation( 8 )
	, positionInterpolation( 3 ) {}
PhyxSettings::~PhyxSettings() {}

void PhyxSettings::SetGravity( float gravity ) { this->gravity = gravity; }
float PhyxSettings::GetGravity() { return this->gravity; }

void PhyxSettings::SetVelocityInterpolation( int interpolation ) { this->velocityInterpolation = interpolation; }
int PhyxSettings::GetVelocityInterpolation() const { return this->velocityInterpolation; }
void PhyxSettings::SetPositionInterpolation( int interpolation ) { this->positionInterpolation = interpolation; }
int PhyxSettings::GetPositionInterpolation() const { return this->positionInterpolation; }

void PhyxSettings::ParseSettingsFile( const std::tstring& valueName, const std::tstring& valueData ) {
	if( valueName == _T( "GRAVITY" ) )
		SetGravity( ( float )_tstof( valueData.c_str() ) );
	else if( valueName == _T( "VELOCITYITERATION" ) )
		SetVelocityInterpolation( _tstoi( valueData.c_str() ) );
	else if( valueName == _T( "POSITIONITERATION" ) )
		SetPositionInterpolation( _tstoi( valueData.c_str() ) );
}