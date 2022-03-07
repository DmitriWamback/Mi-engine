namespace Mi {    
    int p[512] = {
        151,160,137,91,90,105,
        131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,203,
        190,126,148,247,120,234,75,0,6,197,62,94,252,219,203,117,35,11,32,57,177,133,
        88,237,149,56,87,174,20,125,136,171,168,68,175,74,15,71,134,139,48,27,166,177,
        146,158,21,83,111,229,12,60,211,133,230,220,105,92,41,55,46,245,40,244,102,143,
        54,65,25,63,161,111,216,80,73,209,76,132,187,208,89,18,169,200,196,135,130,116,
        188,159,86,164,100,109,198,173,186,223,64,52,217,226,250,124,123,5,202,38,147,
        118,126,255,182,185,212,207,206,59,227,147,16,58,17,182,189,28,142,223,183,170,
        213,119,248,152,222,4,154,163,70,221,153,101,155,167,43,172,119,129,222,39,253,
        19,98,108,110,189,113,224,232,178,185,112,104,218,246,97,228,
        251,134,242,193,238,210,144,12,191,179,162,241,181,151,145,25,249,14,29,107,
        49,192,214,131,181,199,106,57,184,84,204,176,115,121,150,145,127,24,150,254,
        138,236,205,93,222,114,167,229,224,172,243,141,128,195,178,166,215,161,156,180,
        151,160,137,91,90,105,131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,
        8,99,37,240,21,10,203,190,126,148,247,120,234,75,0,6,197,62,94,252,219,203,
        117,35,11,32,57,177,133,88,237,149,56,87,174,20,125,136,171,168,68,175,74,15,
        71,134,139,48,27,166,177,146,158,21,83,111,229,12,60,211,133,230,220,105,92,41,
        55,46,245,40,244,102,143,54,65,25,63,161,111,216,80,73,209,76,132,187,208, 
        89,18,169,200,196,135,130,116,188,159,86,164,100,109,198,173,186,223,64,52,217,
        226,250,124,123,5,202,38,147,118,126,255,182,185,212,207,206,59,227,147,16,
        58,17,182,189,28,142,223,183,170,213,119,248,152,222,4,154,163,170,221,153,101,
        155,167,43,172,119,129,222,39,253,19,98,108,110,189,113,224,232,178,185,
        112,104,218,246,97,228,251,134,242,193,238,210,144,12,191,179,162,241,181,151,
        145,25,249,14,29,107,49,192,214,131,181,199,106,57,184,84,204,176,115,121,
        150,145,127,24,150,254,138,236,205,93,222,114,167,229,224,172,243,141,128,195,
        178,166,215,161,156,180
    };
    
    double fade(double t) {
        return t * t * t * (t * (t * 6 - 15) + 10);
    }

    double lerp(double t, double a, double b) {
        return a + t * (b - a);
    }

    double gradient(int hash, double x, double y, double z) {
        int h = hash & 15;
        double u = h < 8 ? x : y;
        double v = h < 4 ? y : h == 12 || h == 14 ? x : z;

        return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
    }
    
    double noise(double x, double y, double z) {

        int x1 = (int)floor(x) & 255,
            y1 = (int)floor(y) & 255,
            z1 = (int)floor(z) & 255;

        x -= floor(x);
        y -= floor(y);
        z -= floor(z);

        double x2 = fade(x),
               y2 = fade(y),
               z2 = fade(z);

        int A = p[x1] + y1, AA = p[A] + z1, AB = p[A + 1] + z1,      // HASH COORDINATES OF
            B = p[x1 + 1] + y1, BA = p[B] + z1, BB = p[B + 1] + z1;      // THE 8 CUBE CORNERS,

        return lerp(z2, lerp(y2, lerp(x2, gradient(p[AA],     x,     y,     z),
                                          gradient(p[BA],     x - 1, y,     z)),
                                 lerp(x2, gradient(p[AB],     x,     y - 1, z),
                                          gradient(p[BB],     x - 1, y - 1, z))),
                        lerp(y2, lerp(x2, gradient(p[AA + 1], x,     y,     z - 1),
                                          gradient(p[BA + 1], x - 1, y,     z - 1)),
                                 lerp(x2, gradient(p[AB + 1], x,     y - 1, z - 1),
                                          gradient(p[BB + 1], x - 1, y - 1, z - 1))));
    }

    double noise_layer(float x, float y, float lacunarity, float persistance, float seed, int octaves) {

        float n = 0;
        float ampl = 10;
        float freq = 0.05;

        for (int i = 0; i < octaves; i++) {
            n += noise(x * freq, y * freq, seed) * ampl;
            freq *= lacunarity;
            ampl *= persistance;
        }

        return n;
    }

    double abs_noise_layer(float x, float y, float lacunarity, float persistance, float seed, int octaves) {

        float n = 0;
        float ampl = 20;
        float freq = 0.05;

        for (int i = 0; i < octaves; i++) {
            n += (1 - abs(noise(x * freq, y * freq, seed))) * ampl;
            freq *= lacunarity;
            ampl *= persistance;
        }

        return n - 30;
    }

    float get_noise_density_at(int x, int y, int z, float seed, float freq) {
        float xNoise, yNoise, zNoise;
        xNoise = noise(y/freq, z/freq, seed);
        yNoise = noise(x/freq, z/freq, seed);
        zNoise = noise(x/freq, y/freq, seed);

        return xNoise + yNoise + zNoise;
    }
}