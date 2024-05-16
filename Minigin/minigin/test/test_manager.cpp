#include "test_manager.h"

// Project includes
#include "test1_component.h"
#include "test2_component.h"
#include "minigin/core/game_object.h"
#include "minigin/core/scene.h"
#include "minigin/core/scene_manager.h"

// Standard includes
#include <cassert>
#include <backends/imgui_impl_opengl3.h>

namespace mngn
{
    void test_manager::run_all_tests()
    {
        test_components();
        test_parent_child_relationship();
        test_scene();
        test_position();
    }

    void test_manager::test_components()
    {
        {
            // Test Description: Add a component (Test1) to a game object.
            // Assert 1: The game object has the component family.
            // Assert 2: The game object has the component type.
            game_object go;
            go.add_component<test1_component>();
            assert(go.has_component(component_family::test));
            assert(go.has_component<test1_component>());
        }
        {
            // Test Description: Add a component (Test1) to a game object.
            // Assert 1: The game object has the Test1Component - template version.
            // Assert 2: The game object has the Test1Component - type version.
            // Assert 3: The game object has 1 component.
            // Assert 4: The game object has 1 component in the Test family.
            game_object go;
            go.add_component<test1_component>();
            assert(go.component<test1_component>() != nullptr);
            assert(go.components().size()                       == 1);
            assert(go.components(component_family::test).size() == 1);
        }
        {
            // Test Description: Add 2 components (Test1, Test2) to a game object.
            // Assert 1: The game object has 2 components.
            // Assert 2: The game object has 2 components in the Test family.
            game_object go;
            go.add_component<test1_component>();
            go.add_component<test2_component>();
            assert(go.components().size()                       == 2);
            assert(go.components(component_family::test).size() == 2);
        }
        {
            // Test Description: Add 1 component (Test1) to game object 1 and 2 and set game object 2 as a child of game object 1.
            // Assert 1: Game object 1 has 2 components - generic version.
            // Assert 2: Game object 1 has 2 components - template version.
            // Assert 3: Game object 1 has 2 components in the Test family.
            // Assert 4: Game object 1 has 2 components of type Test1 - type version.
            game_object go1;
            game_object go2;
            go1.add_component<test1_component>();
            go2.add_component<test1_component>();
            go2.set_parent(&go1);
            assert(go1.components_in_children().size()                       == 2);
            assert(go1.components_in_children<test1_component>().size()      == 2);
            assert(go1.components_in_children(component_family::test).size() == 2);
        }
        {
            // Test Description: Add 1 component (Test1) to game object 1 and 1 component (Test2) to game object 2 and set game object 2 as a child of game object 1.
            // Assert 1: Game object 1 has 2 components - generic version.
            // Assert 2: Game object 1 has 1 component of type Test1 - template version.
            // Assert 3: Game object 1 has 1 component of type Test2 - template version.
            // Assert 4: Game object 1 has 2 components in the Test family.
            // Assert 5: Game object 1 has 1 component of type Test1 - type version.
            // Assert 6: Game object 1 has 1 component of type Test2 - type version.
            game_object go1;
            game_object go2;
            go1.add_component<test1_component>();
            go2.add_component<test2_component>();
            go2.set_parent(&go1);
            assert(go1.components_in_children().size()                       == 2);
            assert(go1.components_in_children<test1_component>().size()      == 1);
            assert(go1.components_in_children<test2_component>().size()      == 1);
            assert(go1.components_in_children(component_family::test).size() == 2);
            assert(go1.components_in_children<test1_component>().size()      == 1);
            assert(go1.components_in_children<test2_component>().size()      == 1);
        }
        {
            // Test Description: Add 2 components (Test1, Test2) to game object 2 and set game object 2 as a child of game object 1.
            // Assert 1: Game object 1 has 2 components - generic version.
            // Assert 2: Game object 1 has 1 component of type Test1 - template version.
            // Assert 3: Game object 1 has 1 component of type Test2 - template version.
            // Assert 4: Game object 1 has 2 components in the Test family.
            // Assert 5: Game object 1 has 1 component of type Test1 - type version.
            // Assert 6: Game object 1 has 1 component of type Test2 - type version.
            game_object go1;
            game_object go2;
            go2.add_component<test1_component>();
            go2.add_component<test2_component>();
            go2.set_parent(&go1);
            assert(go1.components_in_children().size() == 2);
            assert(go1.components_in_children<test1_component>().size()      == 1);
            assert(go1.components_in_children<test2_component>().size()      == 1);
            assert(go1.components_in_children(component_family::test).size() == 2);
            assert(go1.components_in_children<test1_component>().size()      == 1);
            assert(go1.components_in_children<test2_component>().size()      == 1);
        }
        {
            // Test Description: Empty game object.
            // Assert 1: The game object has no component in parent - template version.
            // Assert 2: The game object has no component in parent - type version.
            // Assert 3: The game object has no component in children - template version.
            // Assert 4: The game object has no component in children - type version.
            game_object go;
            assert(go.component_in_parent<test1_component>()   == nullptr);
            assert(go.component_in_children<test1_component>() == nullptr);
        }
        {
            // Test Description: Empty game object.
            // Assert 1: The game object has no components in parent - generic version.
            // Assert 2: The game object has no components in parent - template version.
            // Assert 3: The game object has no components in parent in the Test family.
            // Assert 4: The game object has no components in parent - type version.
            // Assert 5: The game object has no components in children - generic version.
            // Assert 6: The game object has no components in children - template version.
            // Assert 7: The game object has no components in children in the Test family.
            // Assert 8: The game object has no components in children - type version.
            game_object go;
            assert(go.components_in_parent().empty());
            assert(go.components_in_parent<test1_component>().empty());
            assert(go.components_in_parent(component_family::test).empty());
            assert(go.components_in_children().empty());
            assert(go.components_in_children<test1_component>().empty());
            assert(go.components_in_children(component_family::test).empty());
        }
        {
            // Test Description: Add the same component twice to a game object.
            // Assert 1: The game object has 1 component.
            game_object go;
            go.add_component<test1_component>();
            go.add_component<test1_component>();
            assert(go.components().size() == 1);
        }
        {
            // Test Description: Add 2 components (Test1, Test2) to a game object and remove 1 component (Test1).
            // Assert 1: The game object has 1 component.
            game_object go;
            go.add_component<test1_component>();
            go.add_component<test2_component>();
            go.remove_component<test1_component>();
            assert(go.components().size() == 1);
        }
        {
            // Test Component: Add 1 component (Test1) to a game object and remove it.
            // Assert 1: The game object has no components.
            game_object go;
            auto const component = go.add_component<test1_component>();
            go.remove_component(component);
            assert(go.components().empty());
        }
        {
            // Test Description: Add 2 components (Test1, Test2) to a game object and remove both components.
            // Assert 1: The game object has no components.
            // Assert 2: The game object has removed 2 components.
            game_object go;
            go.add_component<test1_component>();
            go.add_component<test2_component>();
            // const int count = go.RemoveComponents(ComponentFamily::Test);
            assert(go.remove_components<game_component>() == 2);
            assert(go.components().empty());
        }
        {
            // Test Description: Add 1 component (Test1) to game object 1 and remove it from game object 2.
            // Assert 1: The game object has no components.
            game_object go1;
            game_object go2;
            assert(go2.remove_component(go1.add_component<test1_component>()) == 0);
        }
    }

    void test_manager::test_parent_child_relationship()
    {
        {
            // Test Description: A game object cannot be its own parent.
            // Assert 1: The game object cannot set itself as its parent.
            // Assert 2: The game object has no parent.
            game_object go;
            assert(not go.set_parent( &go));
            assert(go.parent() == nullptr);
        }
        {
            // Test Description: Set a game object as a child of another game object.
            // Assert 1: The child game object has been set as a child of the parent game object.
            // Assert 2: The parent game object has the child game object as a child.
            // Assert 3: The parent game object has 1 child.
            // Assert 4: The parent game object's first child is the child game object.
            // Assert 5: The child game object has the parent game object as its parent.
            game_object go1;
            game_object go2;
            assert(go1.set_parent( &go2));
            assert(go2.has_child( &go1));
            assert(go2.child_count() == 1);
            assert(go2.child_at(0)   == &go1);
            assert(go1.parent()      == &go2);
        }
        {
            // Test Description: Set a game object as a child of another game object and then remove the parent.
            // Assert 1: The child game object has been set as a child of the parent game object.
            // Assert 2: The child game object has no parent.
            // Assert 3: The child game object has no children.
            game_object go1;
            game_object go2;
            assert(go1.set_parent( &go2));
            assert(go1.set_parent(nullptr));
            assert(go1.parent() == nullptr);
        }
        {
            // Test Description: Set a game object as a child of another game object and then try to set the parent as a child of the child.
            // Assert 1: The child game object has been set as a child of the parent game object.
            // Assert 2: The parent game object has been set as a child of the child game object.
            // Assert 3: The parent game object has no parent.
            game_object go1;
            game_object go2;
            game_object go3;
            assert(go3.set_parent( &go2));
            assert(go2.set_parent( &go1));
            assert(not go1.set_parent( &go3));
        }
        {
            // Test Description:
            // Assert 1:
            // Assert 2:
            game_object go1;
            game_object go2;
            game_object go3;
            game_object go4;
            go2.set_parent(&go1);
            go4.set_parent(&go3);
            go4.set_parent(&go2);
            assert(go2.has_child( &go4));
            assert(go3.child_count() == 0);
        }
    }

    void test_manager::test_scene()
    {
        {
            // Test Description: Create a scene and add a game object to it.
            // Assert 1: The scene has 1 game object.
            auto const scene = scene_manager::instance().create("Test");
            scene->create();
            assert(scene->count() == 1);
        }
        {
            // Test Description: Create a scene and add a game object to it and then remove the game object.
            // Assert 1: The scene has no game objects.
            auto const scene = scene_manager::instance().create("Test");
            auto const go = scene->create();
            scene->remove(go);
            assert(scene->count() == 0);
        }
        {
            // Test Description: Create a scene and add 2 game objects to it and then remove all game objects.
            // Assert 1: The scene has 2 game objects.
            // Assert 2: The scene has no game objects.
            auto const scene = scene_manager::instance().create("Test");
            scene->create();
            scene->create();
            assert(scene->count() == 2);
            scene->remove_all();
            assert(scene->count() == 0);
        }
    }

    void test_manager::test_position()
    {
        constexpr glm::vec3 pos1 = {10.0f, 10.0f, 10.0f };
        constexpr glm::vec3 pos2 = {20.0f, 20.0f, 20.0f };
        {
            // Test Description: Set the local position of a game object and update the world position.
            // Assert 1: World position is equal to local position.
            game_object go;
            go.set_local_position(pos1);
            go.update_world_position();
            assert(go.world_position() == pos1);
        }
        {
            // Test Description: 
            // Assert 1: World position is equal to local position.
            // Assert 2: World position is equal to the child's world position.
            game_object go1;
            game_object go2;
            go1.set_local_position(pos1);
            go2.set_local_position(pos2);
            go2.set_parent(&go1);
            go1.update_world_position();
            go2.update_world_position();
            assert(go1.world_position() == pos1);
            assert(go2.world_position() == pos2);
        }
        {
            // Test Description: 
            // Assert 1: World position is equal to local position.
            // Assert 2: 
            game_object go1;
            game_object go2;
            go1.set_local_position(pos1);
            go2.set_local_position(pos2);
            go2.set_parent(&go1, false);
            go1.update_world_position();
            go2.update_world_position();
            assert(go1.world_position() == pos1);
            assert(go2.world_position() == pos1 + pos2);
        }
        {
            // Test Description:
            // Assert 1: World position is equal to local position.
            // Assert 2:
            // Assert 3:
            game_object go1;
            game_object go2;
            game_object go3;
            go1.set_local_position(pos1);
            go2.set_local_position(pos2);
            go3.set_local_position(pos2);
            go2.set_parent(&go1, false);
            go3.set_parent(&go2, false);
            go1.update_world_position();
            go2.update_world_position();
            go3.update_world_position();
            assert(go1.world_position() == pos1);
            assert(go2.world_position() == pos1 + pos2);
            assert(go3.world_position() == pos1 + pos2 + pos2);
        }
    }
}

