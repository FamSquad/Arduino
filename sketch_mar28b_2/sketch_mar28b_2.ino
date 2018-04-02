
 
#include<NeoPixelBus.h>
#include <NeoPixelAnimator.h>


const uint16_t PixelCount = 150; 
const uint16_t PixelPin1 = 12;
const uint16_t PixelPin2 = 13;
const uint16_t AnimCount = PixelCount / 5 * 2 + 1; 
const uint16_t PixelFadeDuration = 300; 
const uint16_t NextPixelMoveDuration = 1000 / PixelCount;

NeoGamma<NeoGammaTableMethod> colorGamma; 

NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip1(PixelCount, PixelPin1);
NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip2(PixelCount, PixelPin2);

struct MyAnimationState
{
    RgbColor StartingColor;
    RgbColor EndingColor;
    uint16_t IndexPixel; 
};

NeoPixelAnimator animations(AnimCount); 
MyAnimationState animationState[AnimCount];
uint16_t frontPixel = 0;  
RgbColor frontColor; 

void SetRandomSeed()
{
    uint32_t seed;

   
    seed = analogRead(0);
    delay(1);

    for (int shifts = 3; shifts < 31; shifts += 3)
    {
        seed ^= analogRead(0) << shifts;
        delay(1);
    }

    // Serial.println(seed);
    randomSeed(seed);
}

void FadeOutAnimUpdate(const AnimationParam& param)
{
    
    RgbColor updatedColor = RgbColor::LinearBlend(
        animationState[param.index].StartingColor,
        animationState[param.index].EndingColor,
        param.progress);
    
    strip1.SetPixelColor(animationState[param.index].IndexPixel, colorGamma.Correct(updatedColor));
    strip2.SetPixelColor(animationState[param.index].IndexPixel, colorGamma.Correct(updatedColor));
}

void LoopAnimUpdate(const AnimationParam& param)
{
    
    if (param.state == AnimationState_Completed)
    {
       
        animations.RestartAnimation(param.index);

       
        frontPixel = (frontPixel + 1) % PixelCount; 
        if (frontPixel == 0)
        {
            
            frontColor = HslColor(random(360) / 360.0f, 1.0f, 0.25f);
        }

        uint16_t indexAnim;
    
        if (animations.NextAvailableAnimation(&indexAnim, 1))
        {
            animationState[indexAnim].StartingColor = frontColor;
            animationState[indexAnim].EndingColor = RgbColor(0, 0, 0);
            animationState[indexAnim].IndexPixel = frontPixel;

            animations.StartAnimation(indexAnim, PixelFadeDuration, FadeOutAnimUpdate);
        }
    }
}

void setup()
{
    strip1.Begin();
    strip1.Show();

    strip2.Begin();
    strip2.Show();

    SetRandomSeed();

    
    animations.StartAnimation(0, NextPixelMoveDuration, LoopAnimUpdate);
}


void loop()
{
   
    animations.UpdateAnimations();
    strip1.Show();
    strip2.Show();
}


