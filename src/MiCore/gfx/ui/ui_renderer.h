namespace mi_ui {

    class UIRenderer {
    private:

        mi_inheritable::UIElement* _uiElements[1000];
        int nbElements;
    public: 

        UIRenderer() {
            nbElements = 0;
        }

        void AddUIElement(mi_inheritable::UIElement* uiElement) {
            _uiElements[nbElements] = uiElement;
        }
    };
}