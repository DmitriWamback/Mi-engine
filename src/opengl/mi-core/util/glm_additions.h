namespace miGLM {

    glm::mat4 eulerAngles(glm::vec3 rotation_deg) {

        float x_rad = glm::radians(rotation_deg.x);
        float y_rad = glm::radians(rotation_deg.y);
        float z_rad = glm::radians(rotation_deg.z);

        glm::mat4 x_rot = glm::mat4(
            glm::vec4( cos(x_rad), -sin(x_rad),  0,  0),
            glm::vec4( sin(x_rad),  cos(x_rad),  0,  0),
            glm::vec4( 0,           0,           1,  0),
            glm::vec4( 0,           0,           0,  1));

        glm::mat4 y_rot = glm::mat4(
            glm::vec4( cos(y_rad),  0,  sin(y_rad),  0),
            glm::vec4( 0,           1,  0,           0),
            glm::vec4(-sin(y_rad),  0,  cos(y_rad),  0),
            glm::vec4( 0,           0,  0,           1));

        glm::mat4 z_rot = glm::mat4(
            glm::vec4( 1,  0,           0,           0),
            glm::vec4( 0,  cos(z_rad), -sin(z_rad),  0),
            glm::vec4( 0,  sin(z_rad),  cos(z_rad),  0),
            glm::vec4( 0,  0,           0,           1));

        return x_rot * y_rot * z_rot;
    }
}