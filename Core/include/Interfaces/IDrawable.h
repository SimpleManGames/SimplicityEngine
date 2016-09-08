#ifndef _IDRAWABLE_H
#define _IDRAWABLE_H

class IDrawable {
public:
	IDrawable();
	virtual ~IDrawable();

	virtual void Draw() = 0;

	void SetCanDraw( bool Draw );
	bool GetCanDraw() const;

private:
	bool canDraw;
};

#endif