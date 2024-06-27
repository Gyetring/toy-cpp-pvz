#ifndef UTILS_HPP__
#define UTILS_HPP__

#include <random>
#include <string>

// This relative path on Mac OS is different from that on other OS, because the
// way Xcode organizes the project files is different from others.
// Change it if the program fails to load assets. You may also use an absolute
// path.
#ifdef __APPLE__
static const std::string ASSET_DIR = "../../assets/";
#else
static const std::string ASSET_DIR = "../assets/";
#endif // __APPLE__

// Returns a random integer within [min, max] (inclusive).
inline int randInt(int min, int max) {
  if (max < min)
    std::swap(max, min);
  static std::random_device rd;
  static std::mt19937 generator(rd());
  std::uniform_int_distribution<> distro(min, max);
  return distro(generator);
}

enum class LevelStatus { ONGOING, LOSING };

enum class KeyCode {
  NONE,
  ENTER, // Enter
  QUIT   // Esc
};

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

const int LAWN_GRID_WIDTH = 80;
const int LAWN_GRID_HEIGHT = 100;

const int FIRST_ROW_CENTER = 75;
const int FIRST_COL_CENTER = 75;
const int GAME_ROWS = 5;
const int GAME_COLS = 9;

using ImageID = int;

const ImageID IMGID_NONE = -1;
const ImageID IMGID_BACKGROUND = 0;
const ImageID IMGID_SUN = 1;
const ImageID IMGID_SHOVEL = 2;
const ImageID IMGID_COOLDOWN_MASK = 3;
const ImageID IMGID_SUNFLOWER = 10;
const ImageID IMGID_PEASHOOTER = 11;
const ImageID IMGID_WALLNUT = 12;
const ImageID IMGID_CHERRY_BOMB = 13;
const ImageID IMGID_REPEATER = 14;
const ImageID IMGID_WALLNUT_CRACKED = 15;
const ImageID IMGID_SEED_SUNFLOWER = 20;
const ImageID IMGID_SEED_PEASHOOTER = 21;
const ImageID IMGID_SEED_WALLNUT = 22;
const ImageID IMGID_SEED_CHERRY_BOMB = 23;
const ImageID IMGID_SEED_REPEATER = 24;
const ImageID IMGID_REGULAR_ZOMBIE = 30;
const ImageID IMGID_BUCKET_HEAD_ZOMBIE = 31;
const ImageID IMGID_POLE_VAULTING_ZOMBIE = 32;
const ImageID IMGID_PEA = 40;
const ImageID IMGID_EXPLOSION = 41;
const ImageID IMGID_ZOMBIES_WON = 99;

using AnimID = int;

const AnimID ANIMID_NO_ANIMATION = -1;
const AnimID ANIMID_IDLE_ANIM = 0;
const AnimID ANIMID_WALK_ANIM = 1;
const AnimID ANIMID_EAT_ANIM = 2;
const AnimID ANIMID_RUN_ANIM = 3;
const AnimID ANIMID_JUMP_ANIM = 4;

const int MAX_LAYERS = 7;
using LayerID = int;

const LayerID LAYER_SUN = 0;
const LayerID LAYER_COOLDOWN_MASK = 1;
const LayerID LAYER_INTERACTIVE = 2;
const LayerID LAYER_PROJECTILES = 3;
const LayerID LAYER_ZOMBIE = 4;
const LayerID LAYER_PLANTS = 5;
const LayerID LAYER_BACKGROUND = 6;

const int MS_PER_FRAME = 33;


#endif // !UTILS_HPP__


#ifndef VALUES__
#define VALUES__

constexpr auto SUNSHOW_X = 60;
constexpr auto SUNSHOW_Y = 520;

constexpr auto INIT_SUN_NUM = 50;
constexpr auto INIT_SUN_STR = "50";
constexpr auto SKYTIMER_INIT_MIN = 180;
constexpr auto SKYTIMER_INIT_MAX = 210;
constexpr auto ZOMBIETIMER_INIT_MIN = 600;
constexpr auto ZOMBIETIMER_INIT_MAX = 600;
constexpr auto SKYTIMER_MIN = 180;
constexpr auto SKYTIMER_MAX = 210;
constexpr auto ZOMBIETIMER_MIN = 300;
constexpr auto ZOMBIETIMER_MAX = 400;


constexpr auto SKYSUN_START_LEFT = 50;
constexpr auto SKYSUN_START_RIGHT = WINDOW_WIDTH - 50;
constexpr auto SKYSUN_START_DOWN = 50 + WINDOW_HEIGHT;
constexpr auto SKYSUN_START_UP = 2 * WINDOW_HEIGHT - 50;
const int SUN_WIDTH = 80;
const int SUN_HEIGHT = 80;
const int SUN_GAIN = 25;
const int SUN_FROM_FLOWER_TIME = 10;
const int SUN_FROM_FLOWER_VELOCITY = 2;
const int SUN_FROM_SKY_VELOCITY = 5;
const int SUN_FROM_SKY_TIME = 120;

constexpr auto ZOMBIE_WIDTH = 40;
constexpr auto ZOMBIE_HEIGHT = 70;
constexpr auto ZOMBIE_START_X = WINDOW_WIDTH + 25;
constexpr auto ZOMBIE_PASS_X = -25;

const int SHOVEL_WIDTH = 70;
const int SHOVEL_HEIGHT = 72;
constexpr auto SHOVEL_X = 600;
constexpr auto SHOVEL_Y = 564;

constexpr auto BACKGROUND_WIDTH = 0;
constexpr auto BACKGROUND_HEIGHT = 0;
constexpr auto PEA_WIDTH = 0;
constexpr auto PEA_HEIGHT = 0;
constexpr auto EXPLOSION_WIDTH = 3 * LAWN_GRID_WIDTH;
constexpr auto EXPLOSION_HEIGHT = 3 * LAWN_GRID_HEIGHT;

constexpr auto FIRST_SERIAL_X = 125;
constexpr auto FIRST_SERIAL_Y = 555;
constexpr auto SERIAL_WIDTH = 50;
constexpr auto SERIAL_HEIGHT = 70;

constexpr auto PEA_HIT = 40;
constexpr auto PEA_VELOCITY = 10;
constexpr auto EXPLOSION_HIT = 114514;
constexpr auto EXPLOSION_DELAY = 10;

constexpr auto PLANT_WIDTH = 100;
constexpr auto PLANT_HEIGHT = 70;
constexpr auto NO_SHOOT_DURATION = 0;

constexpr auto SUNFLOWER_HP = 300;
constexpr auto PEASHOOTER_HP = 300;
constexpr auto WALLNUT_HP = 4000;
constexpr auto WALLNUT_CRACK_HP = 2000;
constexpr auto CHERRYBOMB_HP = 114514;

constexpr auto SUNFLOWER_SHOOTDURATION_INIT_MIN = 90;
constexpr auto SUNFLOWER_SHOOTDURATION_INIT_MAX = 300;
constexpr auto SUNFLOWER_SHOOTDURATION_MIN = 600;
constexpr auto SUNFLOWER_SHOOTDURATION_MAX = 750;

constexpr auto PEASHOOTER_SHOOTDURATION_MIN = 40;
constexpr auto PEASHOOTER_SHOOTDURATION_MAX = 45;

constexpr auto CHERRYBOMB_DELAY = 10;

constexpr auto REGULAR_ZOMBIE_VELOCITY = 1;
constexpr auto REGULAR_ZOMBIE_HIT = 2;
constexpr auto REGULAR_ZOMBIE_HP = 200;

const int SUNFLOWER_COOLDOWN = 250;
const int SUNFLOWER_COST = 50;
const int SUNFLOWER_SERIAL = 0;

const int PEASHOOTER_SERIAL = 1;
const int PEASHOOTER_COST = 100;
const int PEASHOOTER_COOLDOWN = 250;

const int WALLNUT_COST = 50;
const int WALLNUT_CRACK = 2000;
const int WALLNUT_SERIAL = 2;
const int WALLNUT_COOLDOWN = 500;

const int CHERRYBOMB_COST = 150;
const int CHERRYBOMB_SERIAL = 3;
const int CHERRYBOMB_COOLDOWN = 500;

#endif // !VALUES__
