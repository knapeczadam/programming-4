#include "TestManager.h"

// Project includes
#include "SceneManager.h"
#include "Test1Component.h"
#include "Test2Component.h"

// Standard includes
#include <cassert>
#include <backends/imgui_impl_opengl3.h>

namespace dae
{
    void TestManager::RunAllTests()
    {
        TestComponents();
        TestParentChildRelationship();
        TestScene();
        TestPosition();
    }

    void TestManager::TestComponents()
    {
        {
            // Test Description: Add a component (Test1) to a game object.
            // Assert 1: The game object has the component family.
            // Assert 2: The game object has the component type.
            GameObject go;
            go.AddComponent<Test1Component>();
            assert(go.HasComponent(ComponentFamily::Test));
            assert(go.HasComponent(ComponentType::Test1));
        }
        {
            // Test Description: Add a component (Test1) to a game object.
            // Assert 1: The game object has the Test1Component - template version.
            // Assert 2: The game object has the Test1Component - type version.
            // Assert 3: The game object has 1 component.
            // Assert 4: The game object has 1 component in the Test family.
            GameObject go;
            go.AddComponent<Test1Component>();
            assert(go.GetComponent<Test1Component>() != nullptr);
            assert(go.GetComponent(ComponentType::Test1) != nullptr);
            assert(go.GetComponents().size()                      == 1);
            assert(go.GetComponents(ComponentFamily::Test).size() == 1);
        }
        {
            // Test Description: Add 2 components (Test1, Test2) to a game object.
            // Assert 1: The game object has 2 components.
            // Assert 2: The game object has 2 components in the Test family.
            GameObject go;
            go.AddComponent<Test1Component>();
            go.AddComponent<Test2Component>();
            assert(go.GetComponents().size()                      == 2);
            assert(go.GetComponents(ComponentFamily::Test).size() == 2);
        }
        {
            // Test Description: Add 1 component (Test1) to game object 1 and 2 and set game object 2 as a child of game object 1.
            // Assert 1: Game object 1 has 2 components - generic version.
            // Assert 2: Game object 1 has 2 components - template version.
            // Assert 3: Game object 1 has 2 components in the Test family.
            // Assert 4: Game object 1 has 2 components of type Test1 - type version.
            GameObject go1;
            GameObject go2;
            go1.AddComponent<Test1Component>();
            go2.AddComponent<Test1Component>();
            go2.SetParent(&go1);
            assert(go1.GetComponentsInChildren().size()                      == 2);
            assert(go1.GetComponentsInChildren<Test1Component>().size()      == 2);
            assert(go1.GetComponentsInChildren(ComponentFamily::Test).size() == 2);
            assert(go1.GetComponentsInChildren(ComponentType::Test1).size()  == 2);
        }
        {
            // Test Description: Add 1 component (Test1) to game object 1 and 1 component (Test2) to game object 2 and set game object 2 as a child of game object 1.
            // Assert 1: Game object 1 has 2 components - generic version.
            // Assert 2: Game object 1 has 1 component of type Test1 - template version.
            // Assert 3: Game object 1 has 1 component of type Test2 - template version.
            // Assert 4: Game object 1 has 2 components in the Test family.
            // Assert 5: Game object 1 has 1 component of type Test1 - type version.
            // Assert 6: Game object 1 has 1 component of type Test2 - type version.
            GameObject go1;
            GameObject go2;
            go1.AddComponent<Test1Component>();
            go2.AddComponent<Test2Component>();
            go2.SetParent(&go1);
            assert(go1.GetComponentsInChildren().size()                      == 2);
            assert(go1.GetComponentsInChildren<Test1Component>().size()      == 1);
            assert(go1.GetComponentsInChildren<Test2Component>().size()      == 1);
            assert(go1.GetComponentsInChildren(ComponentFamily::Test).size() == 2);
            assert(go1.GetComponentsInChildren(ComponentType::Test1).size()  == 1);
            assert(go1.GetComponentsInChildren(ComponentType::Test2).size()  == 1);
        }
        {
            // Test Description: Add 2 components (Test1, Test2) to game object 2 and set game object 2 as a child of game object 1.
            // Assert 1: Game object 1 has 2 components - generic version.
            // Assert 2: Game object 1 has 1 component of type Test1 - template version.
            // Assert 3: Game object 1 has 1 component of type Test2 - template version.
            // Assert 4: Game object 1 has 2 components in the Test family.
            // Assert 5: Game object 1 has 1 component of type Test1 - type version.
            // Assert 6: Game object 1 has 1 component of type Test2 - type version.
            GameObject go1;
            GameObject go2;
            go2.AddComponent<Test1Component>();
            go2.AddComponent<Test2Component>();
            go2.SetParent(&go1);
            assert(go1.GetComponentsInChildren().size() == 2);
            assert(go1.GetComponentsInChildren<Test1Component>().size()      == 1);
            assert(go1.GetComponentsInChildren<Test2Component>().size()      == 1);
            assert(go1.GetComponentsInChildren(ComponentFamily::Test).size() == 2);
            assert(go1.GetComponentsInChildren(ComponentType::Test1).size()  == 1);
            assert(go1.GetComponentsInChildren(ComponentType::Test2).size()  == 1);
        }
        {
            // Test Description: Empty game object.
            // Assert 1: The game object has no component in parent - template version.
            // Assert 2: The game object has no component in parent - type version.
            // Assert 3: The game object has no component in children - template version.
            // Assert 4: The game object has no component in children - type version.
            GameObject go;
            assert(go.GetComponentInParent<Test1Component>() == nullptr);
            assert(go.GetComponentInParent(ComponentType::Test1) == nullptr);
            assert(go.GetComponentInChildren<Test1Component>() == nullptr);
            assert(go.GetComponentInChildren(ComponentType::Test1) == nullptr);
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
            GameObject go;
            assert(go.GetComponentsInParent().empty());
            assert(go.GetComponentsInParent<Test1Component>().empty());
            assert(go.GetComponentsInParent(ComponentFamily::Test).empty());
            assert(go.GetComponentsInParent(ComponentType::Test1).empty());
            assert(go.GetComponentsInChildren().empty());
            assert(go.GetComponentsInChildren<Test1Component>().empty());
            assert(go.GetComponentsInChildren(ComponentFamily::Test).empty());
            assert(go.GetComponentsInChildren(ComponentType::Test1).empty());
        }
        {
            // Test Description: Add the same component twice to a game object.
            // Assert 1: The game object has 1 component.
            GameObject go;
            go.AddComponent<Test1Component>();
            go.AddComponent<Test1Component>();
            assert(go.GetComponents().size() == 1);
        }
        {
            // Test Description: Add 2 components (Test1, Test2) to a game object and remove 1 component (Test1).
            // Assert 1: The game object has 1 component.
            GameObject go;
            go.AddComponent<Test1Component>();
            go.AddComponent<Test2Component>();
            go.RemoveComponent(ComponentType::Test1);
            assert(go.GetComponents().size() == 1);
        }
        {
            // Test Component: Add 1 component (Test1) to a game object and remove it.
            // Assert 1: The game object has no components.
            GameObject go;
            const auto component = go.AddComponent<Test1Component>();
            go.RemoveComponent(component);
            assert(go.GetComponents().empty());
        }
        {
            // Test Description: Add 2 components (Test1, Test2) to a game object and remove both components.
            // Assert 1: The game object has no components.
            // Assert 2: The game object has removed 2 components.
            GameObject go;
            go.AddComponent<Test1Component>();
            go.AddComponent<Test2Component>();
            const int count = go.RemoveComponents(ComponentFamily::Test);
            assert(go.GetComponents().empty());
            assert(count == 2);
        }
        {
            // Test Description: Add 1 component (Test1) to game object 1 and remove it from game object 2.
            // Assert 1: The game object has no components.
            GameObject go1;
            GameObject go2;
            const auto comp = go1.AddComponent<Test1Component>();
            const int count = go2.RemoveComponent(comp);
            assert(count == 0);
        }
    }

    void TestManager::TestParentChildRelationship()
    {
        {
            // Test Description: A game object cannot be its own parent.
            // Assert 1: The game object cannot set itself as its parent.
            // Assert 2: The game object has no parent.
            GameObject go;
            assert(not go.SetParent(&go));
            assert(go.GetParent() == nullptr);
        }
        {
            // Test Description: Set a game object as a child of another game object.
            // Assert 1: The child game object has been set as a child of the parent game object.
            // Assert 2: The parent game object has the child game object as a child.
            // Assert 3: The parent game object has 1 child.
            // Assert 4: The parent game object's first child is the child game object.
            // Assert 5: The child game object has the parent game object as its parent.
            GameObject go1;
            GameObject go2;
            assert(go1.SetParent(&go2));
            assert(go2.HasChild(&go1));
            assert(go2.GetChildCount() == 1);
            assert(go2.GetChildAt(0)   == &go1);
            assert(go1.GetParent()     == &go2);
        }
        {
            // Test Description: Set a game object as a child of another game object and then remove the parent.
            // Assert 1: The child game object has been set as a child of the parent game object.
            // Assert 2: The child game object has no parent.
            // Assert 3: The child game object has no children.
            GameObject go1;
            GameObject go2;
            assert(go1.SetParent(&go2));
            assert(go1.SetParent(nullptr));
            assert(go1.GetParent() == nullptr);
        }
        {
            // Test Description: Set a game object as a child of another game object and then try to set the parent as a child of the child.
            // Assert 1: The child game object has been set as a child of the parent game object.
            // Assert 2: The parent game object has been set as a child of the child game object.
            // Assert 3: The parent game object has no parent.
            GameObject go1;
            GameObject go2;
            GameObject go3;
            assert(go3.SetParent(&go2));
            assert(go2.SetParent(&go1));
            assert(not go1.SetParent(&go3));
        }
        {
            // Test Description:
            // Assert 1:
            // Assert 2:
            GameObject go1;
            GameObject go2;
            GameObject go3;
            GameObject go4;
            go2.SetParent(&go1);
            go4.SetParent(&go3);
            go4.SetParent(&go2);
            assert(go2.HasChild(&go4));
            assert(go3.GetChildCount() == 0);
        }
    }

    void TestManager::TestScene()
    {
        {
            // Test Description: Create a scene and add a game object to it.
            // Assert 1: The scene has 1 game object.
            const auto scene = SceneManager::GetInstance().CreateScene("Test");
            scene->AddGameObject();
            assert(scene->GetGameObjectCount() == 1);
        }
        {
            // Test Description: Create a scene and add a game object to it and then remove the game object.
            // Assert 1: The scene has no game objects.
            const auto scene = SceneManager::GetInstance().CreateScene("Test");
            const auto go = scene->AddGameObject();
            scene->RemoveGameObject(go);
            assert(scene->GetGameObjectCount() == 0);
        }
        {
            // Test Description: Create a scene and add 2 game objects to it and then remove all game objects.
            // Assert 1: The scene has 2 game objects.
            // Assert 2: The scene has no game objects.
            const auto scene = SceneManager::GetInstance().CreateScene("Test");
            scene->AddGameObject();
            scene->AddGameObject();
            assert(scene->GetGameObjectCount() == 2);
            scene->RemoveAll();
            assert(scene->GetGameObjectCount() == 0);
        }
    }

    void TestManager::TestPosition()
    {
        constexpr glm::vec3 pos1 = {10.0f, 10.0f, 10.0f };
        constexpr glm::vec3 pos2 = {20.0f, 20.0f, 20.0f };
        {
            // Test Description: Set the local position of a game object and update the world position.
            // Assert 1: World position is equal to local position.
            GameObject go;
            go.SetLocalPosition(pos1);
            go.UpdateWorldPosition();
            assert(go.GetWorldPosition() == pos1);
        }
        {
            // Test Description: 
            // Assert 1: World position is equal to local position.
            // Assert 2: World position is equal to the child's world position.
            GameObject go1;
            GameObject go2;
            go1.SetLocalPosition(pos1);
            go2.SetLocalPosition(pos2);
            go2.SetParent(&go1);
            go1.UpdateWorldPosition();
            go2.UpdateWorldPosition();
            assert(go1.GetWorldPosition() == pos1);
            assert(go2.GetWorldPosition() == pos2);
        }
        {
            // Test Description: 
            // Assert 1: World position is equal to local position.
            // Assert 2: 
            GameObject go1;
            GameObject go2;
            go1.SetLocalPosition(pos1);
            go2.SetLocalPosition(pos2);
            go2.SetParent(&go1, false);
            go1.UpdateWorldPosition();
            go2.UpdateWorldPosition();
            assert(go1.GetWorldPosition() == pos1);
            assert(go2.GetWorldPosition() == pos1 + pos2);
        }
        {
            // Test Description:
            // Assert 1: World position is equal to local position.
            // Assert 2:
            // Assert 3:
            GameObject go1;
            GameObject go2;
            GameObject go3;
            go1.SetLocalPosition(pos1);
            go2.SetLocalPosition(pos2);
            go3.SetLocalPosition(pos2);
            go2.SetParent(&go1, false);
            go3.SetParent(&go2, false);
            go1.UpdateWorldPosition();
            go2.UpdateWorldPosition();
            go3.UpdateWorldPosition();
            assert(go1.GetWorldPosition() == pos1);
            assert(go2.GetWorldPosition() == pos1 + pos2);
            assert(go3.GetWorldPosition() == pos1 + pos2 + pos2);
        }
    }
}

