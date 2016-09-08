#ifndef _ABSTRACTGAME_H
#define _ABSTRACTGAME_H

class AbstractGame {
public:
	// Default constructor
	AbstractGame();
	// Virtual deconstructor
	virtual ~AbstractGame();
	// Pure virtaul initialization funcition 
	virtual bool Initialize() = 0;
	// Pure virtual shutdown function
	virtual bool Shutdown() = 0;
}; // AbstractGame

#endif // !_ABSTRACTGAME_H