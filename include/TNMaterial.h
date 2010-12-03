#ifndef TNMATERIAL_H
#define TNMATERIAL_H

class TNMaterial
{
    public:
        TNMaterial();
        virtual ~TNMaterial();
        void render();

        void setAmbient(float r,  float b, float g, float a);
        void setSpecular(float r,  float b, float g, float a);
        void setDiffuse(float r,  float b, float g, float a);
        void setShiny(float s);


    protected:
    private:
        float mAmbient[4];
        float mSpecular[4];
        float mDiffuse[4];
        float mShiny;
};

#endif // TNMATERIAL_H
