
#pragma once
#include "../ecs/System.h"

class FoodSystem : public ecs::System {
public:

	FoodSystem();
	virtual ~FoodSystem();
	void initSystem() override;
	void update() override;
	void addFood(unsigned int n);
	void onFoodEaten(ecs::entity_t e);
	void recieve(const Message& m) override;
private:
	unsigned int _currNumOfFood;
};

