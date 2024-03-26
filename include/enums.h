enum class TypeObject { NONE, PLAYER, ENEMY, ITEM, SHOT, EFFECT };
enum class TypeEffect { NONE, TORNADO, BLEEDING, EXPLOSION };
enum class TypeShot { NONE, BASE, RICOCHET, THROUGHT };
enum class TypeItem { SHOT, EFFECT, STAT };
enum class TypeMessage { MOVE, CREATE, DEATH, CREATE_EFFECT, EFFECT, END_EFFECT, ITEM, END_GAME };
enum class TypeEndGame { DEATH_HERO, WIN };