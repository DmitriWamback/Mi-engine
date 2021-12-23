namespace mi_ui {

    void UIElementAssignShader(mi_inheritable::UIElement* elem, Shader shader) {
        elem->shaderName = shader.shaderName;
    }

    class UIRenderer {
    private:

        mi_inheritable::UIElement* _uiElements[1000];
        int nbElements;
    public: 

        std::string name;
        UIRenderer() {}

        UIRenderer(std::string name) {
            this->name = name;
            nbElements = 0;
        }

        void AddUIElement(mi_inheritable::UIElement* uiElement) {
            _uiElements[nbElements] = uiElement;
            nbElements++;
        }

        void Update() {

            for (int i = 0; i < nbElements; i++) {
                mi_inheritable::UIElement* elem = _uiElements[i];
                glDepthMask(GL_TRUE);
                elem->Render(mi_core::all_shaders[elem->shaderName]);
            }
        }
    };
}