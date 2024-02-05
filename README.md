# AVR_ADMUX_PWM
Avr application that uses ADC to measure analog signal, converts the ADC value to a square wave with proportional duty cycle <fast non-inverting PWM> in C.
the project utilizes LCD -4-bit mode- for logging read values.
This was a project for the Logic/microprocessor course, last semester.
## It relies on : 
 - atmega328p embedded in the Arduino Uno R3 board
 - running on 16MHz clock_frequency for the CPU
 - 1024 as prescaler to obtain cycle with 16 ms width for the timer fast PWM wave generation non-inverting
 - 128 as ADC clock prescaler
 - uses LCD in 4-bit mode to show adc value and calculated Duty Cycle -DC-
 ## Wiring
   I don't have a schematic right now, The wiring is pretty straightforward.
    - the analog input supplied to PC0
    - the LCD data lines -Dx.- are connected as follows:
    
      - D4 to D7 are connected to PD0 to PD3 on Arduino
      - RS to PD5
      - E to PD7
  The rest are just VCC/GND/simple wiring available online
  I hope to provide the circuit soon.

Feel free to contact me and ask for any clarification if you wanna build your own "D
---------------------------------------------
![alt text](https://github.com/Mahmoussam/AVR_ADMUX_PWM/blob/master/poc.jpg)
