namespace Mi { namespace UI {

    void UIElementAssignShader(Mi::Inheritable::UIElement* elem, Shader shader) {
        elem->shaderName = shader.shaderName;
    }

    class UIRenderer {
    private:

        Mi::Inheritable::UIElement* _uiElements[1000];
        int nbElements;
    public: 

        std::string name;
        UIRenderer() {}

        UIRenderer(std::string name) {
            this->name = name;
            nbElements = 0;
        }

        void AddUIElement(Mi::Inheritable::UIElement* uiElement) {
            _uiElements[nbElements] = uiElement;
            nbElements++;
        }

        void Update() {

            for (int i = 0; i < nbElements; i++) {
                Mi::Inheritable::UIElement* elem = _uiElements[i];
                glDepthMask(GL_TRUE);
                elem->Render(Mi::Engine::FindShader(elem->shaderName));
            }
        }
    };
}}