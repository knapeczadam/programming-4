#pragma once

// GLM includes
#include <glm/glm.hpp>

namespace dae
{
    class Transform final
    {
    public:
        const glm::vec3& GetWorldPosition() const { return m_worldPosition; }
        const glm::vec3& GetLocalPosition() const { return m_localPosition; }
        
        void SetWorldPosition(float x, float y);
        void SetWorldPosition(float x, float y, float z);
        void SetWorldPosition(const glm::vec2& position);
        void SetWorldPosition(const glm::vec3& position);

        void SetLocalPosition(float x, float y);
        void SetLocalPosition(float x, float y, float z);
        void SetLocalPosition(const glm::vec2& position);
        void SetLocalPosition(const glm::vec3& position);

    private:
        glm::vec3 m_worldPosition = {};
        glm::vec3 m_localPosition = {};
    };
}
