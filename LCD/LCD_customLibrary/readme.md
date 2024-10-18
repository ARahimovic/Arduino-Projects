## 4-bit Mode LCD Initialization Sequence (HD44780)

The **initialization sequence** for a character LCD using the **HD44780** controller in **4-bit mode** involves several key steps to configure the LCD properly.

### Steps for Initialization Sequence:

1. **Wait for Power Stabilization**:
   - After powering on the LCD, wait **at least 15 milliseconds** for the power to stabilize.

2. **Send Initial Commands in 8-bit Mode**:
   - The LCD starts in 8-bit mode by default, so you need to send the following command sequence:
     - Send `0x30` three times with delays between each:
       - Wait **4.1 ms** after the first command.
       - Wait **100 µs** after the second command.
     - This step resets the LCD to ensure it's in a known state.

3. **Set 4-bit Mode**:
   - Send `0x20` to set the LCD to operate in 4-bit mode. Now, it expects further commands to be in 4-bit format.

4. **Function Set**:
   - Send the function set command `0x28` to configure the display:
     - 4-bit mode.
     - 2-line display.
     - 5x8 dot character font.

5. **Display Control**:
   - Send `0x0C` to turn the display on:
     - Display ON.
     - Cursor OFF.
     - Blink OFF.

6. **Clear Display**:
   - Send the clear display command `0x01` to reset the display.

7. **Entry Mode Set**:
   - Send `0x06` to configure the entry mode:
     - Cursor moves to the right after each character.
     - Display does not shift.

---

## Common Commands in the HD44780

Here’s a list of commonly used commands for the HD44780 LCD controller and their corresponding bits:

### Function Set Command (`0x20` - `0x2F`)
This command sets the interface data length, number of display lines, and character font.

| Bit   | 7   | 6   | 5   | 4   | 3    | 2     | 1     | 0   |
|-------|-----|-----|-----|-----|------|-------|-------|-----|
| Value | 0   | 0   | 1   | DL  | N    | F     | 0     | 0   |

- **DL**: Data length (0 = 4-bit mode, 1 = 8-bit mode).
- **N**: Number of lines (0 = 1-line, 1 = 2-line).
- **F**: Font size (0 = 5x8, 1 = 5x10).

### Display Control Command (`0x08` - `0x0F`)
Controls the display, cursor visibility, and cursor blink.

| Bit   | 7   | 6   | 5   | 4   | 3    | 2     | 1     | 0   |
|-------|-----|-----|-----|-----|------|-------|-------|-----|
| Value | 0   | 0   | 0   | 0   | 1    | D     | C     | B   |

- **D**: Display ON/OFF (1 = ON, 0 = OFF).
- **C**: Cursor ON/OFF (1 = ON, 0 = OFF).
- **B**: Blink ON/OFF (1 = ON, 0 = OFF).

### Entry Mode Set Command (`0x04` - `0x07`)
Sets the cursor move direction and specifies whether the display shifts.

| Bit   | 7   | 6   | 5   | 4   | 3    | 2     | 1     | 0   |
|-------|-----|-----|-----|-----|------|-------|-------|-----|
| Value | 0   | 0   | 0   | 0   | 0    | 1     | I/D   | S   |

- **I/D**: Increment/Decrement cursor (1 = Increment, 0 = Decrement).
- **S**: Shift (1 = Display shift, 0 = No shift).

### Clear Display Command (`0x01`)
Clears the display and returns the cursor to the home position.

### Return Home Command (`0x02`)
Returns the cursor to the home position without clearing the display.

---

## Summary of Initialization Commands

1. `0x30` - Function Set (sent 3 times to reset the LCD in 8-bit mode).
2. `0x20` - Set 4-bit mode.
3. `0x28` - Function Set (4-bit mode, 2-line display, 5x8 dots).
4. `0x0C` - Display ON, Cursor OFF, Blink OFF.
5. `0x01` - Clear Display.
6. `0x06` - Entry Mode Set (increment cursor, no display shift).