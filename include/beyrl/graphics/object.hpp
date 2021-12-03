#pragma once

#include "transform.hpp"
#include "model.hpp"

namespace beyrl {

class Object : public Transform {
    Model m_model;

    friend class Window;

public:
    Object(Model model, Transform transform = {}) : Transform(transform), m_model(model) {}
};

}