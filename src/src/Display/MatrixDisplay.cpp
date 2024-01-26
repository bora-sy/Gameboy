#include "Pinout.h"

namespace MatrixDisplay
{
  uint8_t pic[8];

  const uint8_t heightFullBits = (uint8_t)pow(2, 7);

  void Clear(bool state = false)
  {
    for (uint8_t i = 0; i < 8; i++)
    {
      pic[i] = state ? 255 : 0;
    }
  }

  void Init()
  {
    pinMode(PIN_SRDATA, OUTPUT);
    pinMode(PIN_SRCLOCK, OUTPUT);
    pinMode(PIN_SRLATCH, OUTPUT);

    Clear();
  }

  void TriggerLatch()
  {
    digitalWrite(PIN_SRLATCH, HIGH);
    //delayMicroseconds(10);
    digitalWrite(PIN_SRLATCH, LOW);
    //delayMicroseconds(10);
  }
  
  void Periodic()
  {
    for (uint8_t i = 0; i < 8; i++)
    {
      shiftOut(PIN_SRDATA, PIN_SRCLOCK, LSBFIRST, ~pic[i]);
      shiftOut(PIN_SRDATA, PIN_SRCLOCK, LSBFIRST, heightFullBits >> i);
      TriggerLatch();
    }
  }

  void SetPixel(uint8_t X, uint8_t Y, bool state)
  {
    if (X < 0 || X > 7 || Y < 0 || Y > 7)
      return;

    if (state)
    {
      pic[Y] |= 128 >> X;
    }
    else
    {
      pic[Y] &= ~(128 >> X);
    }
  }

  void SetLine(uint8_t Y, uint8_t value)
  {
    if (Y < 0 || Y > 7)
      return;
    if (value < 0 || value > 255)
      return;


    pic[Y] = value;
  }

  void Set(uint8_t* value)
  {
    for (uint8_t i = 0; i < 8; i++)
    {
      Serial.println(value[i]);
      pic[i] = value[i];
    }
  }
}