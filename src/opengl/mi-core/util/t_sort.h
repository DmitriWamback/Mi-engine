namespace Mi {
    
    std::vector<Mi::Renderable> t_renderables;

    // Adds transparent objects to render separately
    void AddTransparent(Mi::Renderable transparent) {
        t_renderables.push_back(transparent);
    }

    // Function to render all transparent objects
    void RenderTransparent() {

        //Shader _tShader = Mi::Core::all_shaders[]
    }
}