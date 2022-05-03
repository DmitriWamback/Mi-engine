float Map(float v, float fromMin, float fromMax, float toMin, float toMax) {

    float decreaseScale = abs(fromMin) + abs(fromMax);
    float n = (v + abs(fromMin)) / decreaseScale;

    float increaseScale = abs(2 * toMin) + abs(toMax);
    n *= increaseScale;
    n -= abs(toMin);

    return n;
}