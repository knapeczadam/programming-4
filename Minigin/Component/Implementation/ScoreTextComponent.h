#pragma once

// Project includes
#include "IObserver.h"
#include "TextComponent.h"

namespace dae
{
    class ScoreTextComponent final : public TextComponent, public IObserver
    {
    public:
        ScoreTextComponent() = default;
        virtual ~ScoreTextComponent() override = default;

        ScoreTextComponent(const ScoreTextComponent& other)            = delete;
        ScoreTextComponent(ScoreTextComponent&& other)                 = delete;
        ScoreTextComponent& operator=(const ScoreTextComponent& other) = delete;
        ScoreTextComponent& operator=(ScoreTextComponent&& other)      = delete;

        void Notify(const std::string& event, Subject* subject) override;
    };
}
