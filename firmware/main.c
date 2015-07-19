/*
    Copyright 2015 Andreas Weber <section77@tech-chat.de>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/**********************************************************************

  Section 77 Würfel
  Firmware für ATTiny13A

  Autor: Andreas Weber
  src: https://github.com/Andy1978/S77_Wuerfel/firmware
  changelog: 06.07.2015 angelegt

  Schaltplan in ../kicad.
  Es gibt 4 LED Gruppen (Im Schematic G0..G3):
  G0 an PB0, G1 and PB1 usw. bis G3 an PB3

  (0)       (2)

  (1)  (3)  (1)

  (2)       (0)

  Somit ergibt sich:
  Wert -> low tetrade PORTB
  1    -> 0b0111 = 0x7
  2    -> 0b1110 = 0xE
  3    -> 0b0110 = 0x6
  4    -> 0b1010 = 0xA
  5    -> 0b0010 = 0x2
  6    -> 0b1000 = 0x8

  * Phototransistor BPW40 an PB4 (ADC2)

***********************************************************************/

#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

// Siehe Erklärung oben
char numbers[7] = {0xF, 0x7, 0xE, 0x6, 0xA, 0x2, 0x8};

// F_CPU ist 1.2 MHz (interner RC Oszillator, s.a. Makefile)
// Clk-Prescaler ist 8 (siehe TCCR0B)
// OCR0A ist 150
//
// Damit ergibt sich eine Aufruffrequenz von
// 1200000 / 8 / 150 = 1kHz

ISR(TIM0_COMPA_vect)
{
  /*
  // Im Sekundentakt von 0..6 zählen
  static int c=0;
  static int step=0;
  c++;

  if (c==1000)
    {
      PORTB = (PORTB & 0xF0) | numbers[step++];

      if (step>6)
        step = 0;
      c = 0;
    }
  */
}

// Eine normale Wandlung dauert 13 clock cycles
// -> Aufruf mit ca. 1200000/128/13 = 721Hz

ISR(ADC_vect)
{
  // Wenn der analoge Eingang über einen Schwellwert (0.5 * VCC) steigt,
  // schnell durchzählen
  static int num = 1;
  if (ADC > 512)
    {
      PORTB = (PORTB & 0xF0) | numbers[num++];

      if (num > 6)
        num = 1;
    }
}

int main(void)
{
  // Die 4 Pins an denen die LEDs hängen sind Ausgänge
  DDRB = _BV(PB0) |  _BV(PB1) | _BV(PB2) | _BV(PB3);

  /*** TIMER0 ***/
  OCR0A = 150;
  //CTC = Clear Timer on Compare match S.80
  //Normal port operation, OC0A disconnected
  TCCR0A = _BV(WGM01);

  //Prescaler=8 -> clk=150kHz
  TCCR0B = _BV(CS01);

  //On Compare match Interrupt Enable for timer 0
  TIMSK0 |= _BV(OCIE0A);

  /*** ADC ***/
  //Prescaler 128 = 9.375kHz ADC Clock, AutoTrigger, Interrupts enable
  ADCSRA = _BV(ADEN) | _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2) | _BV(ADATE) | _BV(ADSC) | _BV(ADIE);

  //ADC Auto Trigger Source = Free Running
  //ACME = 0
  ADCSRB = 0;

  // REFS0 = 0 : Vcc used as analog reference
  // ADLAR = 0
  // MUX = ADC2 (PB4)
  ADMUX = 2;

  //enable global interrupts
  sei();

  for (;;)    /* main event loop */
    {
      // nichts tun, es wird alles in den Interrupts erledigt
      ;
    }
  return 0;
}
