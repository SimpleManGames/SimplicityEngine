#ifndef _PHYXSETTINGS_H
#define _PHYXSETTINGS_H

#include "Settings.h"

#ifndef _STRING_H
#include "Defines/string.h"
#endif

class PhyxSettings : public Settings {
public:
	PhyxSettings();
	virtual ~PhyxSettings();

	void SetGravity( float gravity );
	float GetGravity();

	void SetVelocityInterpolation( int interpolation );
	int GetVelocityInterpolation() const;
	void SetPositionInterpolation( int interpolation );
	int GetPositionInterpolation() const;

protected:
	virtual void ParseSettingsFile( const std::tstring& valueName, const std::tstring& valueData );

private:

	float gravity;

	int velocityInterpolation;
	int positionInterpolation;
};

#endif // _PHYSXSETTINGS_H
