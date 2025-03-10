#pragma once

class FigtherFacade {
public:
	FigtherFacade() {}
	virtual ~FigtherFacade() {}
	void virtual create_figther() = 0;
	void virtual reset_figther() = 0;
	void virtual reset_lives() = 0;
	int virtual update_lives(int n) = 0;
};