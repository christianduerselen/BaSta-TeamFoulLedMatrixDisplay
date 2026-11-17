# BaSta-TeamFoulLedMatrixDisplay

A basketball scoreboard accessory that displays a team's foul count on an RGB LED matrix panel. The firmware runs on an **Arduino Zero** and uses the [Adafruit Protomatter](https://github.com/adafruit/Adafruit_Protomatter) library to drive a 64×32 HUB75 LED matrix.

The foul count received from a Stramatel scoreboard controller is rendered in white using the "Bebas Neue" font. When the team reaches the bonus foul limit and the game clock is running, the entire display turns solid red. A switch selects whether the home or guest team fouls are shown. If no valid Stramatel frame is received for 3 seconds the display falls back to the default "/".

## Hardware

| Component | Details |
|---|---|
| Microcontroller | Arduino Zero |
| Display | 64×32 HUB75 RGB LED matrix |
| Library | Adafruit Protomatter |
| Team selection switch | Pin 13 (active low, internal pull-up) |
| Force team fouls button | Pin 12 (active low, internal pull-up) |
| Serial input | Serial1 RX (pin 0), 19200 baud, Stramatel protocol |

### Matrix wiring (HUB75)

| Signal | Arduino Zero pin |
|---|---|
| R1, G1, B1, R2, G2, B2 | 2, 3, 4, 5, 6, 7 |
| A, B, C, D | A0, A1, A2, A3 |
| CLK | 8 |
| LAT | 10 |
| OE | 9 |

## Usage

1. Wire the LED matrix, a toggle switch, and a momentary push-button to the Arduino Zero as described above.
2. Connect the Stramatel scoreboard data line to the Serial1 RX pin (pin 0).
3. Open `src/BaSta-TeamFoulLedMatrix/BaSta-TeamFoulLedMatrix.ino` in the Arduino IDE.
4. Install the **Adafruit Protomatter** library via the Library Manager.
5. Select **Arduino Zero** as the target board and upload the sketch.

At runtime:

- Toggle the **team selection switch** to choose between displaying home and guest team fouls.
- Press and hold the **force team fouls button** to immediately show the solid red bonus screen, regardless of the data received.
- The current foul count (0–4) is shown in white using the Bebas Neue font.
- When the team reaches the bonus foul limit and the game clock is running, the display turns **solid red**.
- Five fouls and more show the solid red screen as well.
- A frame whose team-foul byte is not a digit (a sender that does not transmit team fouls leaves it blank) shows the default "/".
- If no valid Stramatel frame is received for 3 seconds, the display falls back to "/". Stray bytes on the line do not count as a signal.

## License

See [LICENSE](LICENSE).
