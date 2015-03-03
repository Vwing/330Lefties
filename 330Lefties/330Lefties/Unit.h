#include "GameObject.h"
// #include "AI.h"

// 'Unit' objects are non-UI objects that can have AI or physics actions.
// They are stored in the environment
class Unit : public GameObject
{
public:
// AI* ai;
  enableAI = false;
  enablePhysics = false;

};
