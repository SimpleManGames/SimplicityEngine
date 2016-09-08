#ifndef _IFILLABLESHAPE_H
#define _IFILLABLESHAPE_H

class IFillableShape {
public:
	IFillableShape() {}
	virtual ~IFillableShape() {}

	virtual void SetFill( bool fill ) = 0;
	virtual bool GetFill() const = 0;

protected:
	bool fill;
};

#endif