namespace Mi {

    // Function to render all transparent objects
    std::vector<Mi::Renderable> GetTransparents(std::vector<Mi::Renderable> p) {

        std::vector<Mi::Renderable> res;

        for (int i = 0; i < p.size(); i++) {
            if (p[i].opacity < 1.f) res.push_back(p[i]);
        }
        return res;
    }

    std::vector<Mi::Renderable> GetSolids(std::vector<Mi::Renderable> p) {

        std::vector<Mi::Renderable> res;

        for (int i = 0; i < p.size(); i++) {
            if (p[i].opacity >= 1.f) res.push_back(p[i]);
        }
        return res;
    }

    std::vector<Mi::Renderable> RenderFurtherest(std::vector<Mi::Renderable> p, glm::vec3 camPosition) {
        
        std::vector<Mi::Renderable> result;
        std::vector<Mi::Renderable> c = p;

        int s = p.size();

        for (int i = 0; i < s; i++) {

            float max = 0;
            int index = 0;

            for (int j = 0; j < c.size(); j++) {
                
                glm::vec3 d = camPosition - c[j].position;
                float len = sqrt(pow(d.x, 2) + pow(d.y, 2) + pow(d.z, 2));
                if (max < len) {
                    index = j;
                    max = len;
                }
            }

            result.push_back(c[index]);
            c.erase(std::next(c.begin(), index));
        }

        return result;
    }
}