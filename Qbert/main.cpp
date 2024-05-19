// Visual Leak Detector
#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

// Project includes
#include "core/level_config_manager.h"
#include "core/qbert_scene_manager.h"
#include "core/resources.h"
#include "core/services.h"
#include "core/sprites.h"
#include "minigin/core/engine.h"
#include "minigin/test/test_manager.h"

// Standard includes
#include <cassert>

// SDL includes
#include <SDL.h>

void load()
{
	qbert::init_resources();
	qbert::init_sprites();
	qbert::register_services();
	qbert::level_config_manager::instance().load_level_config("../Data/configs/level_config.json");
	qbert::qbert_scene_manager::instance().load_scenes();
}

int main(int, char *[])
{
    mngn::engine engine("../Data/");
	
#ifndef NDEBUG
    mngn::test_manager::instance().run_all_tests();
#endif
	
    engine.run(load);
	
    return 0;
}
