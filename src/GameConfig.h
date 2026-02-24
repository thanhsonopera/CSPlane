#ifndef GameConfig_h
#define GameConfig_h

/*
 * ============================================================
 * FILE CẤU HÌNH GAME - Chỉnh các số tại đây để tùy chỉnh game
 * ============================================================
 */

// ---------- Màn hình & Level ----------
const int Width          = 1024;
const int Height         = 520;
const int Level_Width    = 1024;
const int Level_Height   = 4023;
const int FPS            = 1000 / 60;

// ---------- Kích thước sprite (pixel) ----------
const int Bullet_w       = 5;
const int Bullet_h       = 13;
const int Plane_w        = 50;
const int Plane_h        = 60;
const int Plane2_w       = 85;
const int Plane2_h       = 90;
const int Rocket_w       = 20;
const int Rocket_h       = 47;
const int hp_w           = 30;
const int hp_h           = 31;
const int Explosion_w    = 512;
const int Explosion_h    = 512;

// ---------- Spawn / random (sinh địch) ----------
const int max1           = 100;
const int min1           = 1;

// ---------- Máy bay phe ta ----------
const int PLANE_MAX_SPEED_X     = 3;    // tốc độ tối đa trái-phải (pixel/frame)
const int PLANE_MAX_SPEED_Y     = 2;    // tốc độ tối đa lên-xuống
const int PLANE_HP              = 100;  // máu ban đầu
const int PLANE_MAX_BULLETS     = 20;   // đạn tối đa
const int PLANE_FIRE_DELAY_MS   = 100;  // khoảng cách giữa 2 viên đạn (ms)
const int PLANE_BULLET_REGEN_MS = 2500; // mỗi 2.5s hồi 1 viên đạn
const int PLANE_RECOVERY_MS     = 30000;// mỗi 30s hồi 50% đạn + tăng max
const int PLANE_RECOVERY_BONUS  = 10;   // mỗi 30s tăng max đạn thêm
const int PLANE_ABILITY1_CD_MS  = 20000;// Laser đơn (X): cooldown 20s
const int PLANE_ABILITY2_CD_MS  = 30000;// Laser ba (C): cooldown 30s

// ---------- Laser ----------
const int LASER1_DAMAGE_BASE    = 50;   // damage Laser đơn cơ bản
const int LASER1_DAMAGE_PER_MIN = 10;   // +damage mỗi phút
const int LASER2_DAMAGE_BASE    = 30;   // damage Laser ba cơ bản
const int LASER2_DAMAGE_PER_MIN = 20;   // +damage mỗi phút
const int LASER_DURATION_MS     = 500;  // thời gian tồn tại (ms)
const int LASER1_W              = 10;   // chiều rộng Laser đơn
const int LASER1_H              = 80;   // chiều cao Laser đơn
const int LASER2_W              = 8;    // chiều rộng Laser ba (2 bên)
const int LASER2_H              = 100;  // chiều cao Laser ba
const int LASER_OFFSET_Y        = 55;   // vị trí laser phía trên máy bay
const int LASER_SPREAD          = 15;   // khoảng cách 3 tia (pixel)

// ---------- Damage va chạm ----------
const int DAMAGE_PLANE_HIT_ENEMY1  = 30;  // máy bay đụng địch loại 1
const int DAMAGE_PLANE_HIT_ENEMY2  = 50;  // máy bay đụng địch loại 2
const int DAMAGE_BULLET_HIT_ENEMY  = 10;  // đạn ta bắn trúng địch
const int DAMAGE_BULLET_HIT_ROCKET = 20;  // đạn ta bắn trúng tên lửa
const int DAMAGE_ROCKET_HIT_PLANE  = 50;  // tên lửa đụng máy bay
const int DAMAGE_ENEMY_BULLET      = 10;  // đạn địch trúng máy bay
const int HP_BOX_HEAL              = 20;  // hộp máu hồi

// ---------- Điểm số ----------
const int SCORE_FINISH_LINE = 100;  // qua vạch đích
const int SCORE_ENEMY1      = 30;   // tiêu diệt địch loại 1
const int SCORE_ENEMY2      = 50;   // tiêu diệt địch loại 2
const int SCORE_LASER_KILL  = 200;  // tiêu diệt bằng laser

// ---------- Spawn (sinh địch / tên lửa) ----------
const int SPAWN_RAND_EXTRA   = 50;   // rand max khi sinh rocket (max1 + 50 - min1)
const int SINH_TIME_DIV_30K  = 30000;// chia realTime cho spawn rate
const int SINH_TIME_DIV_60K  = 60000;

// ---------- Rơi hộp máu (khi địch chết) ----------
const int HP_DROP_RAND_MOD = 15;     // rand() % 15
const int HP_DROP_RAND_VAL = 10;    // if (t1 == 10) rơi HP

// ---------- UI / Font ----------
const int FONT_SIZE_SMALL   = 13;   // font chữ nhỏ
const int FONT_SIZE_LARGE   = 20;   // font chữ lớn
const int NO_AMMO_POPUP_MS  = 1000; // thời gian hiện "No Ammo!" (ms)
const int NO_AMMO_POPUP_X   = 30;
const int NO_AMMO_POPUP_Y   = 100;
const int ABILITY_UI_OFFSET_Y = 35;  // vị trí dòng chữ skill dưới BulletInfo
const int TOP_SCORES_COUNT   = 10;   // số bản ghi high score lưu
const int TIMING_DIV         = 10;   // chia cho timing (explosion update)

// ---------- Màu (R, G, B) - dùng cho UI ----------
const int COLOR_ABILITY_R = 100;
const int COLOR_ABILITY_G = 200;
const int COLOR_ABILITY_B = 255;

// ---------- BigBang (vụ nổ) ----------
const int EXPLOSION_FRAME_W   = 128;   // chiều rộng 1 frame trong sprite
const int EXPLOSION_FRAME_H   = 128;   // chiều cao 1 frame
const int EXPLOSION_GRID      = 4;     // lưới 4x4 frame
const int EXPLOSION_MAX_FRAME = 15;    // frame cuối (0..15)

// ---------- Rocket (tên lửa) ----------
const int ROCKET_HP         = 100;   // máu tên lửa
const int ROCKET_VY_DIV     = 2;     // vy = vt / ROCKET_VY_DIV + ...
const int ROCKET_DIFF_DIV   = 60000; // chia diff (ms) cho tốc độ tăng
const int ROCKET_DIFF_MUL   = 2;     // nhân tốc độ theo thời gian

// ---------- Đạn địch (EnemyBullet) ----------
const int ENEMY_BULLET_SPEED_DIV = 3;    // td = vt / 3 + ...
const int ENEMY_BULLET_DIFF_DIV  = 30000;// chia diff (ms)

// ---------- Hộp máu (HP) ----------
const int HP_BOX_SPEED_DIV = 4;  // tốc độ rơi = vt / 4

// ---------- Đạn phe ta (MyBullet) ----------
const int MY_BULLET_SPEED_DIV = 2;  // tốc độ bay = vt / 2

// ---------- Địch loại 1 (EnemyPlane) ----------
const int ENEMY1_HP           = 30;    // máu
const int ENEMY1_VX_BASE      = 1;     // vx cơ bản
const int ENEMY1_DIFF_DIV     = 50000; // diff / 50000 tăng vx
const int ENEMY1_FIRE_INTERVAL= 200;   // bắn mỗi 200 pixel y
const int ENEMY1_VY           = 1;     // tốc độ rơi (pixel/frame)

// ---------- Địch loại 2 (EnemyPlane2) ----------
const int ENEMY2_HP            = 50;   // máu
const int ENEMY2_VX_BASE       = 1;    // vx cơ bản
const int ENEMY2_DIFF_DIV      = 50000;// diff / 50000 tăng vx
const int ENEMY2_FIRE_INTERVAL_BASE = 200;  // khoảng bắn ban đầu (frame)
const int ENEMY2_FIRE_INTERVAL_DEC  = 50;   // giảm mỗi 30s
const int ENEMY2_FIRE_INTERVAL_DIV  = 30000;// mỗi 30s giảm
const int ENEMY2_FIRE_INTERVAL_MIN  = 50;  // tối thiểu
const int ENEMY2_ENTRY_SPEED   = 2;    // tốc độ xuất hiện (y += 2)

// ---------- Laser (màu vẽ) ----------
const int LASER_COLOR_R = 0;
const int LASER_COLOR_G = 255;
const int LASER_COLOR_B = 255;

#endif
