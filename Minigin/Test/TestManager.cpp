#include "TestManager.h"

// Project includes
#include "SceneManager.h"
#include "Test1Component.h"
#include "Test2Component.h"

// Standard includes
#include <cassert>

namespace dae
{
    void TestManager::RunAllTests()
    {
        TestComponents();
        TestParentChildRelationship();
        TestScene();
    }

    void TestManager::TestComponents()
    {
        {
            // Test Description: Add a component to a game object.
            // Assert 1: The game object has the component family.
            // Assert 2: The game object has the component type.
            GameObject go;
            go.AddComponent<Test1Component>();
            assert(go.HasComponent(ComponentFamily::Test));
            assert(go.HasComponent(ComponentType::Test1));
        }
        {
            GameObject go;
            go.AddComponent<Test1Component>();
            assert(go.GetComponent<Test1Component>() != nullptr);
            assert(go.GetComponent(ComponentType::Test1) != nullptr);
            assert(go.GetComponents().size() == 1);
            assert(go.GetComponents(ComponentFamily::Test).size() == 1);
        }
        {
            GameObject go;
            go.AddComponent<Test1Component>();
            go.AddComponent<Test2Component>();
            assert(go.GetComponents().size() == 2);
            assert(go.GetComponents(ComponentFamily::Test).size() == 2);
        }
        {
            GameObject go1;
            GameObject go2;
            go1.AddComponent<Test1Component>();
            go2.AddComponent<Test1Component>();
            go2.SetParent(&go1);
            assert(go1.GetComponentsInChildren().size() == 2);
            assert(go1.GetComponentsInChildren<Test1Component>().size() == 2);
            assert(go1.GetComponentsInChildren(ComponentFamily::Test).size() == 2);
            assert(go1.GetComponentsInChildren(ComponentType::Test1).size() == 2);
        }
        {
            GameObject go1;
            GameObject go2;
            go1.AddComponent<Test1Component>();
            go2.AddComponent<Test2Component>();
            go2.SetParent(&go1);
            assert(go1.GetComponentsInChildren().size() == 2);
            assert(go1.GetComponentsInChildren<Test1Component>().size() == 1);
            assert(go1.GetComponentsInChildren<Test2Component>().size() == 1);
            assert(go1.GetComponentsInChildren(ComponentFamily::Test).size() == 2);
            assert(go1.GetComponentsInChildren(ComponentType::Test1).size() == 1);
            assert(go1.GetComponentsInChildren(ComponentType::Test2).size() == 1);
        }
        {
            GameObject go1;
            GameObject go2;
            go2.AddComponent<Test1Component>();
            go2.AddComponent<Test2Component>();
            go2.SetParent(&go1);
            assert(go1.GetComponentsInChildren().size() == 2);
            assert(go1.GetComponentsInChildren<Test1Component>().size() == 1);
            assert(go1.GetComponentsInChildren<Test2Component>().size() == 1);
            assert(go1.GetComponentsInChildren(ComponentFamily::Test).size() == 2);
            assert(go1.GetComponentsInChildren(ComponentType::Test1).size() == 1);
            assert(go1.GetComponentsInChildren(ComponentType::Test2).size() == 1);
        }
        {
            GameObject go;
            assert(go.GetComponentInParent<Test1Component>() == nullptr);
            assert(go.GetComponentInParent(ComponentType::Test1) == nullptr);
            assert(go.GetComponentInChildren<Test1Component>() == nullptr);
            assert(go.GetComponentInChildren(ComponentType::Test1) == nullptr);
        }
        {
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
            GameObject go;
            go.AddComponent<Test1Component>();
            go.AddComponent<Test1Component>();
            assert(go.GetComponents().size() == 1);
        }
        {
            GameObject go;
            go.AddComponent<Test1Component>();
            go.AddComponent<Test2Component>();
            go.RemoveComponent(ComponentType::Test1);
            assert(go.GetComponents().size() == 1);
        }
        {
            GameObject go;
            const auto component = go.AddComponent<Test1Component>();
            go.RemoveComponent(component);
            assert(go.GetComponents().empty());
        }
        {
            GameObject go;
            go.AddComponent<Test1Component>();
            go.AddComponent<Test2Component>();
            assert(go.RemoveComponents(ComponentFamily::Test) == 2);
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
            assert(go2.GetChildAt(0) == &go1);
            assert(go1.GetParent() == &go2);
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
    }

    void TestManager::TestScene()
    {
        {
            // Test Description: Create a scene and add a game object to it.
            // Assert 1: The scene has 1 game object.
            const auto scene = SceneManager::GetInstance().CreateScene("Test");
            scene->AddEmptyObject();
            assert(scene->GetObjectCount() == 1);
        }
        {
            // Test Description: Create a scene and add a game object to it and then remove the game object.
            // Assert 1: The scene has no game objects.
            const auto scene = SceneManager::GetInstance().CreateScene("Test");
            const auto go = scene->AddEmptyObject();
            scene->RemoveObject(go);
            assert(scene->GetObjectCount() == 0);
        }
        {
            // Test Description: Create a scene and add 2 game objects to it and then remove all game objects.
            // Assert 1: The scene has 2 game objects.
            // Assert 2: The scene has no game objects.
            const auto scene = SceneManager::GetInstance().CreateScene("Test");
            scene->AddEmptyObject();
            scene->AddEmptyObject();
            assert(scene->GetObjectCount() == 2);
            scene->RemoveAll();
            assert(scene->GetObjectCount() == 0);
        }
    }
}

