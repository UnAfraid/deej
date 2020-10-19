const int NUM_SLIDERS = 5;
const int NUM_BUTTONS = 1;
const int analogInputs[NUM_SLIDERS] = {A0, A1, A2, A3, A4};
const int digitalInputs[NUM_BUTTONS] = {2};

int analogSliderValues[NUM_SLIDERS];
int buttonStates[NUM_BUTTONS];
int buttonValues[NUM_BUTTONS];

int lastAnalogSliderValues[NUM_SLIDERS];
long lastButtonDebounce[NUM_BUTTONS];
int lastButtonValues[NUM_BUTTONS];

int currentButtonState;
unsigned long debounceDelay = 50;
unsigned long updateRepeatDelay = 1 * 1000;

int lastWrittenButtonValues[NUM_BUTTONS];
int lastWrittenSliderValues[NUM_SLIDERS];
unsigned long lastWrittenSliders;
unsigned long lastWrittenButtons;

float sliderDifferenceThreshold = 25;

void setup()
{
  for (int i = 0; i < NUM_SLIDERS; i++)
  {
    pinMode(analogInputs[i], INPUT);
  }

  for (int i = 0; i < NUM_BUTTONS; i++)
  {
    pinMode(digitalInputs[i], INPUT_PULLUP);
  }

  Serial.begin(9600);
}

void loop()
{
  updateSliderValues();
  updateButtonValues();
  sendSliderValues();
  sendButtonValues();
  // delay(10);
}

void updateSliderValues()
{
  for (int i = 0; i < NUM_SLIDERS; i++)
  {
    analogSliderValues[i] = analogRead(analogInputs[i]);
  }
}

void updateButtonValues()
{
  for (int i = 0; i < NUM_BUTTONS; i++)
  {
    currentButtonState = digitalRead(digitalInputs[i]);

    if (currentButtonState != lastButtonValues[i])
    {
      lastButtonDebounce[i] = millis();
    }

    if ((millis() - lastButtonDebounce[i]) > debounceDelay)
    {
      if (currentButtonState != buttonStates[i])
      {
        buttonStates[i] = currentButtonState;

        if (buttonStates[i] == HIGH)
        {
          if (buttonValues[i] == LOW)
          {
            buttonValues[i] = HIGH;
          }
          else
          {
            buttonValues[i] = LOW;
          }
        }
      }
    }

    lastButtonValues[i] = currentButtonState;
  }
}

void sendButtonValues()
{
  bool needsUpdate = (millis() - lastWrittenButtons) > updateRepeatDelay;
  String objects[NUM_SLIDERS];
  int objectLen = 0;
  for (int i = 0; i < NUM_BUTTONS; i++)
  {
    if (lastWrittenButtonValues[i] != buttonValues[i] || needsUpdate)
    {
      String builtString = String("{\"type\": \"button\", \"value\": ");
      builtString += String(buttonValues[i]);
      builtString += String(", \"index\": ");
      builtString += String(i);
      builtString += String("}");

      objects[objectLen] = builtString;
      objectLen++;
      lastWrittenButtonValues[i] = buttonValues[i];
    }
  }

  if (needsUpdate)
  {
    lastWrittenButtons = millis();
  }

  if (objectLen != 0)
  {
    String builtString = String("[");
    for (int i = 0; i < objectLen; i++)
    {
      builtString += objects[i];
      if (i < objectLen - 1)
      {
        builtString += String(",");
      }
    }
    builtString += String("]");
    Serial.println(builtString);
  }
}

void sendSliderValues()
{
  bool needsUpdate = (millis() - lastWrittenSliders) > updateRepeatDelay;
  String objects[NUM_SLIDERS];
  int objectLen = 0;
  for (int i = 0; i < NUM_SLIDERS; i++)
  {
    if (abs(lastWrittenSliderValues[i] - analogSliderValues[i]) > sliderDifferenceThreshold || needsUpdate)
    {
      String builtString = String("{\"type\": \"slider\", \"value\": ");
      builtString += String(analogSliderValues[i]);
      builtString += String(", \"index\": ");
      builtString += String(i);
      builtString += String("}");

      objects[objectLen] = builtString;
      objectLen++;
      lastWrittenSliderValues[i] = analogSliderValues[i];
    }
  }

  if (needsUpdate)
  {
    lastWrittenSliders = millis();
  }

  if (objectLen != 0)
  {
    String builtString = String("[");
    for (int i = 0; i < objectLen; i++)
    {
      builtString += objects[i];
      if (i < objectLen - 1)
      {
        builtString += String(",");
      }
    }
    builtString += String("]");
    Serial.println(builtString);
  }
}
