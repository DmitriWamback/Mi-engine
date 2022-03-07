namespace Mi {

float find_biggest_comp(glm::vec3 vec) {
    if (vec.x > vec.y && vec.x > vec.z) return vec.x;
    if (vec.y > vec.x && vec.y > vec.z) return vec.y;
    if (vec.z > vec.y && vec.z > vec.x) return vec.z;
    return 0;
}

}