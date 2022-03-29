namespace Mi {
    
    std::vector<Mi::Inheritable::Renderable*> t_renderables;

    // Adds transparent objects to render separately
    void AddTransparent(Mi::Inheritable::Renderable* transparent) {
        t_renderables.push_back(transparent);
    }

    // Function to render all transparent objects
    void RenderTransparent() {

        //Shader _tShader = Mi::Core::all_shaders[]
    }
}