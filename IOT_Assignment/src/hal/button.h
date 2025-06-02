#ifndef BUTTON_H
#define BUTTON_H
#include <Arduino.h>

#define BUTTON_PIN GPIO_NUM_12

// ============================== README BEFORE USE ==============================
// Button pin need to pull down
// ===============================================================================

/**
 * @brief Debouce loop (10ms).
 *
 * @return
 *     - None
 */
void deboucing_run();

/**
 * @brief Get the button state.
 *
 * @return
 *     - 1 if the button is pressed
 *     - 0 if the button is not pressed
 */
uint8_t get_button_state();
#endif // BUTTON_H