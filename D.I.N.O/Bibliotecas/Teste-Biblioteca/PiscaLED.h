#ifndef PiscaLED_h
#define PiscaLED_h

class PiscaLED {
    public:
        PiscaLED(int pino1, int pino2);
        void piscar();
    private:
        int pino1_;
        int pino2_;
};

#endif
