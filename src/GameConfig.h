#ifndef GameConfig_h
#define GameConfig_h

#include <SDL.h>
#include <SDL_ttf.h>


constexpr int MS_PER_SEC      = 1000;
constexpr int SEC_PER_MIN     = 60;
constexpr int FPS             = 1000 / 60;       // 60 FPS chuẩn
constexpr int SCREEN_TICKS_PER_FRAME = 1000 / FPS;

constexpr int Width           = 1024;      // Chiều rộng màn hình
constexpr int Height          = 520;       // Chiều cao màn hình
constexpr int Level_Width     = 1024;
constexpr int Level_Height    = 4023;

// ==========================================
// 2. MÀU SẮC & UI (Colors & Alpha)
// ==========================================
constexpr Uint8 COLOR_BLACK       = 0;
constexpr Uint8 COLOR_WHITE       = 255;
constexpr Uint8 ALPHA_OPAQUE      = 255;
constexpr Uint8 ALPHA_DIM         = 60;
constexpr Uint8 TEXT_ALPHA_NORMAL = 200;
const SDL_Color TEXT_COLOR_HIGHLIGHT = {255, 155, 0, 255};

// UI Font Sizes
constexpr int FONT_SIZE_SMALL     = 13;
constexpr int FONT_SIZE_LARGE     = 20;

// UI Ability Colors (RGB)
constexpr int COLOR_ABILITY_R     = 100;
constexpr int COLOR_ABILITY_G     = 200;
constexpr int COLOR_ABILITY_B     = 255;

// Popup Messages
constexpr int NO_AMMO_POPUP_MS    = 1000;
constexpr int NO_AMMO_POPUP_X     = 30;
constexpr int NO_AMMO_POPUP_Y     = 100;
constexpr int ABILITY_UI_OFFSET_Y = 35;

// ==========================================
// 3. MENU CONSTANTS
// ==========================================
constexpr int MENU_MAX_ITEMS             = 5;
constexpr int MENU_FONT_SIZE             = 40;
constexpr int MENU_START_X               = 100;
constexpr int MENU_START_Y               = 100;
constexpr int MENU_SPACING               = 45;
constexpr int MENU_HIGHLIGHT_OFFSET      = 15;
constexpr float MENU_BG_TARGET_WIDTH_RATIO = 0.92f;

// ==========================================
// 4. LEADERBOARD CONSTANTS
// ==========================================
constexpr int LB_MAX_ENTRIES      = 10;
constexpr int LB_TOTAL_TEXT_ITEMS = 12;
constexpr int LB_FONT_SIZE        = 40;
constexpr int LB_START_X          = 50;
constexpr int LB_START_Y          = 10;
constexpr int LB_ITEM_SPACING     = 40;
constexpr int LB_HEADER_SPACING   = 60;
constexpr int LB_INDENT_X         = 100;
constexpr int TOP_SCORES_COUNT    = 10;

// ==========================================
// 5. TUTORIAL & SETTINGS CONSTANTS
// ==========================================
// Tutorial
constexpr int TUT_FONT_SIZE       = 40;
constexpr int TUT_START_X         = 50;
constexpr int TUT_START_Y         = 10;
constexpr int TUT_SPACING         = 45;
constexpr int TUT_INDENT_X        = 100;
constexpr int TUT_HEADER_SPACING  = 70;

// Settings
constexpr int SET_FONT_SIZE       = 40;
constexpr int SET_START_X         = 200;
constexpr int SET_START_Y         = 150;
constexpr int SET_SPACING         = 70;
constexpr int SET_MAIN_ITEMS      = 3;
constexpr int SET_SUB_ITEMS       = 4;

// ==========================================
// 6. KÍCH THƯỚC SPRITE (Sprites)
// ==========================================
constexpr int Bullet_w        = 5;
constexpr int Bullet_h        = 13;
constexpr int Plane_w         = 50;
constexpr int Plane_h         = 60;
constexpr int Plane2_w        = 85;
constexpr int Plane2_h        = 90;
constexpr int Rocket_w        = 20;
constexpr int Rocket_h        = 47;
constexpr int hp_w            = 30;
constexpr int hp_h            = 31;
constexpr int Explosion_w     = 512;
constexpr int Explosion_h     = 512;

// ==========================================
// 7. GAMEPLAY: SPAWN & PHYSICS
// ==========================================
constexpr int max1            = 100;
constexpr int min1            = 1;
constexpr int SPAWN_RAND_EXTRA   = 50;
constexpr int SINH_TIME_DIV_30K  = 30000;
constexpr int SINH_TIME_DIV_60K  = 60000;

// Máy bay phe ta (Player)
constexpr int PLANE_MAX_SPEED_X      = 3;
constexpr int PLANE_MAX_SPEED_Y      = 2;
constexpr int PLANE_HP               = 100;
constexpr int PLANE_MAX_BULLETS      = 20;
constexpr int PLANE_FIRE_DELAY_MS    = 100;
constexpr int PLANE_BULLET_REGEN_MS  = 2500;
constexpr int PLANE_RECOVERY_MS      = 30000;
constexpr int PLANE_RECOVERY_BONUS   = 10;
constexpr int PLANE_ABILITY1_CD_MS   = 20000;
constexpr int PLANE_ABILITY2_CD_MS   = 30000;

// Laser Skills
constexpr int LASER1_DAMAGE_BASE     = 50;
constexpr int LASER1_DAMAGE_PER_MIN  = 10;
constexpr int LASER2_DAMAGE_BASE     = 30;
constexpr int LASER2_DAMAGE_PER_MIN  = 20;
constexpr int LASER_DURATION_MS      = 500;
constexpr int LASER1_W               = 10;
constexpr int LASER1_H               = 80;
constexpr int LASER2_W               = 8;
constexpr int LASER2_H               = 100;
constexpr int LASER_OFFSET_Y         = 55;
constexpr int LASER_SPREAD           = 15;
constexpr int LASER_COLOR_R          = 0;
constexpr int LASER_COLOR_G          = 255;
constexpr int LASER_COLOR_B          = 255;

// ==========================================
// 8. DAMAGE & SCORE SYSTEM
// ==========================================
// Damage
constexpr int DAMAGE_PLANE_HIT_ENEMY1  = 30;
constexpr int DAMAGE_PLANE_HIT_ENEMY2  = 50;
constexpr int DAMAGE_BULLET_HIT_ENEMY  = 10;
constexpr int DAMAGE_BULLET_HIT_ROCKET = 20;
constexpr int DAMAGE_ROCKET_HIT_PLANE  = 50;
constexpr int DAMAGE_ENEMY_BULLET      = 10;
constexpr int HP_BOX_HEAL              = 20;

// Score
constexpr int SCORE_FINISH_LINE = 100;
constexpr int SCORE_ENEMY1      = 30;
constexpr int SCORE_ENEMY2      = 50;
constexpr int SCORE_LASER_KILL  = 200;

// ==========================================
// 9. ENTITY BEHAVIOR
// ==========================================
// Hộp máu rơi
constexpr int HP_DROP_RAND_MOD = 15;
constexpr int HP_DROP_RAND_VAL = 10;
constexpr int HP_BOX_SPEED_DIV = 4;

// BigBang (Animation nổ)
constexpr int EXPLOSION_FRAME_W   = 128;
constexpr int EXPLOSION_FRAME_H   = 128;
constexpr int EXPLOSION_GRID      = 4;
constexpr int EXPLOSION_MAX_FRAME = 15;
constexpr int TIMING_DIV          = 10;

// Rocket (Tên lửa địch)
constexpr int ROCKET_HP           = 100;
constexpr int ROCKET_VY_DIV       = 2;
constexpr int ROCKET_DIFF_DIV     = 60000;
constexpr int ROCKET_DIFF_MUL     = 2;

// Đạn địch (EnemyBullet)
constexpr int ENEMY_BULLET_SPEED_DIV = 3;
constexpr int ENEMY_BULLET_DIFF_DIV  = 30000;

// Đạn ta (MyBullet)
constexpr int MY_BULLET_SPEED_DIV    = 2;

// Địch loại 1 (EnemyPlane)
constexpr int ENEMY1_HP              = 30;
constexpr int ENEMY1_VX_BASE         = 1;
constexpr int ENEMY1_DIFF_DIV        = 50000;
constexpr int ENEMY1_FIRE_INTERVAL   = 200;
constexpr int ENEMY1_VY              = 1;

// Địch loại 2 (EnemyPlane2)
constexpr int ENEMY2_HP                 = 50;
constexpr int ENEMY2_VX_BASE            = 1;
constexpr int ENEMY2_DIFF_DIV           = 50000;
constexpr int ENEMY2_FIRE_INTERVAL_BASE = 200;
constexpr int ENEMY2_FIRE_INTERVAL_DEC  = 50;
constexpr int ENEMY2_FIRE_INTERVAL_DIV  = 30000;
constexpr int ENEMY2_FIRE_INTERVAL_MIN  = 50;
constexpr int ENEMY2_ENTRY_SPEED        = 2;

// Màu chữ mặc định
const SDL_Color Color = {255, 255, 255};
#endif
