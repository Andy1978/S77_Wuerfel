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
  1    -> 0b0111
  2    -> 0b1110
  3    -> 0b0110
  4    -> 0b1010
  5    -> 0b0010
  6    -> 0b1000

  * Switch gegen GND an PB5, Pull-Up aktivieren
  * Phototransistor BPW40 an PB4 (ADC2)

***********************************************************************/

#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>

ISR(TIM0_COMPA_vect) //1kHz
{

}

ISR(ADC_vect) //ca. 125kHz
{
  //momentan keine Verwendung für den ADC
  //int16_t temp=ADC-512;
}

int main(void)
{
  // Die 4 Pins an denen die LEDs hängen sind Ausgänge
  DDRB = _BV(PB0) |  _BV(PB1) | _BV(PB2) | _BV(PB3);

  // Pull-Up für den Taster
  PORTB = 0x2F;

  /*** TIMER0 ***/
  OCR0A = 250;
  //CTC = Clear Timer on Compare match S.80
  //Normal port operation, OC0A disconnected
  TCCR0A = _BV(WGM01);

  //Prescaler=64 -> clk=250kHz
  TCCR0B = _BV(CS01) | _BV(CS00);

  //On Compare match Interrupt Enable for timer 0
  TIMSK0 |= _BV(OCIE0A);

  /*** ADC ***/
  //Prescaler 128 = 125kHz ADC Clock, AutoTrigger, Interrupts enable
  ADCSRA = _BV(ADEN) | _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2) | _BV(ADATE) | _BV(ADSC) | _BV(ADIE);

  //AVCC with external capacitor at AREF, internal 2.56V bandgap
  //siehe S. 215
  //ADMUX = (_BV(REFS0) | _BV(REFS1)) + 2;
  //ADC in Free Running mode
  //SFIOR &= ~(_BV(ADTS2) | _BV(ADTS1) | _BV(ADTS0));

  //enable global interrupts
  sei();

  for (;;)    /* main event loop */
    {
      //
    }
    return 0;
}
