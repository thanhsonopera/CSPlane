#ifndef PATHS_H
#define PATHS_H

#include <string>

// Centralized resource path configuration.
// Change these values if you move asset folders later.
static const std::string ASSET_ROOT = ""; // if assets are at project root, leave empty
static const std::string IMG_DIR = "img/"; // base image folder under project root or ASSET_ROOT

// Subfolders under IMG_DIR
static const std::string IMG_BG = "backgrounds/";
static const std::string IMG_UI = "ui/";
static const std::string IMG_PLANES = "planes/";
static const std::string IMG_BULLETS = "bullets/";
static const std::string IMG_ROCKETS = "rockets/";
static const std::string IMG_EFFECTS = "effects/";

inline std::string imgPath(const std::string &subdir, const std::string &name)
{
    return ASSET_ROOT + IMG_DIR + subdir + name;
}

// Convenience wrappers for common categories
inline std::string imgBg(const std::string &name) { return imgPath(IMG_BG, name); }
inline std::string imgUI(const std::string &name) { return imgPath(IMG_UI, name); }
inline std::string imgPlanes(const std::string &name) { return imgPath(IMG_PLANES, name); }
inline std::string imgBullets(const std::string &name) { return imgPath(IMG_BULLETS, name); }
inline std::string imgRockets(const std::string &name) { return imgPath(IMG_ROCKETS, name); }
inline std::string imgEffects(const std::string &name) { return imgPath(IMG_EFFECTS, name); }

#endif
