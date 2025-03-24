#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <string>
#include <memory>

// Forward declarations
class Entity;

class Component {
public:
    Component() = default;
    virtual ~Component() = default;
    
    virtual void Init(Entity* owner) = 0;
    virtual void Update(Entity* owner, float deltaTime) = 0;
    virtual void Draw(Entity* owner) = 0;
    
    // Component identification
    std::string GetType() const { return componentType; }
    
protected:
    std::string componentType;
};

#endif // COMPONENT_HPP