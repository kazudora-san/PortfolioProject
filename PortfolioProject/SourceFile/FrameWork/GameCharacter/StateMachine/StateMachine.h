#include <functional>
#include <memory>

class State;
class GameCharacter;

// State‚Ì‘JˆÚæ‚ÆğŒ‚ğŠi”[‚·‚é
struct Transition
{
    State* from;
    State* to;
    std::function<bool()> condition;
};

class StateMachine
{
private:
    std::vector<std::unique_ptr<State>> m_States;
    std::vector<Transition> m_Transitions;
    State* m_CurrentState = nullptr;

public:
    void Update();

    template <typename T>
    T* AddState(GameCharacter* owner)
    {
        auto state = std::make_unique<T>(owner);
        T* ptr = state.get();
        m_States.push_back(std::move(state));

        if (!m_CurrentState)
        {
            m_CurrentState = ptr;
        }

        return ptr;
    }

    void AddTransition(State* from, State* to, std::function<bool()> condition)
    {
        // condition = ŠÖ”‚ğ“ü‚ê‚é
        m_Transitions.push_back({ from, to, condition });
    }

    void ChangeState(State* state);
};