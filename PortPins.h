#ifndef PORTPINS_H_
#define PORTPINS_H_

//  LED2 - Red
#define LED2_R_PIN                  0
#define LED2_R_BIT                 (0x01 << LED2_R_PIN)
#define LED2_R_PORT                 P2
#define SET_LED2_R_AS_AN_OUTPUT     LED2_R_PORT->DIR |= LED2_R_BIT
#define TURN_ON_LED2_RED            LED2_R_PORT->OUT |= LED2_R_BIT
#define TURN_OFF_LED2_RED           LED2_R_PORT->OUT &= ~LED2_R_BIT
#define TOGGLE_LED2_RED             LED2_R_PORT->OUT ^= LED2_R_BIT

//  LED2 - Green
#define LED2_G_PIN                  1
#define LED2_G_BIT                  (0x01 << LED2_G_PIN)
#define LED2_G_PORT                 P2
#define SET_LED2_G_AS_AN_OUTPUT     LED2_G_PORT->DIR |= LED2_G_BIT
#define TURN_ON_LED2_GREEN          LED2_G_PORT->OUT |= LED2_G_BIT
#define TURN_OFF_LED2_GREEN         LED2_G_PORT->OUT &= ~LED2_G_BIT
#define TOGGLE_LED2_GREEN           LED2_G_PORT->OUT ^= LED2_G_BIT

//  LED2 - Blue
#define LED2_B_PIN                  2
#define LED2_B_BIT                  (0x01 << LED2_B_PIN)
#define LED2_B_PORT                 P2
#define SET_LED2_B_AS_AN_OUTPUT     LED2_B_PORT->DIR |= LED2_B_BIT
#define TURN_ON_LED2_BLUE           LED2_B_PORT->OUT |= LED2_B_BIT
#define TURN_OFF_LED2_BLUE          LED2_B_PORT->OUT &= ~LED2_B_BIT
#define TOGGLE_LED2_BLUE            LED2_B_PORT->OUT ^= LED2_B_BIT

// Pushbutton S1
#define PUSHBUTTON_S1_PIN                       1
#define PUSHBUTTON_S1_BIT                       (0x01 << PUSHBUTTON_S1_PIN)
#define PUSHBUTTON_S1_PORT                      P1
#define SET_PUSHBUTTON_S1_TO_AN_INPUT           PUSHBUTTON_S1_PORT->DIR &= ~PUSHBUTTON_S1_BIT
#define ENABLE_PULL_UP_PULL_DOWN_RESISTORS_S1   PUSHBUTTON_S1_PORT->REN |= PUSHBUTTON_S1_BIT
#define SELECT_PULL_UP_RESISTORS_S1             PUSHBUTTON_S1_PORT->OUT |= PUSHBUTTON_S1_BIT

// Pushbutton S2
#define PUSHBUTTON_S2_PIN                       4
#define PUSHBUTTON_S2_BIT                       (0x01 << PUSHBUTTON_S2_PIN)
#define PUSHBUTTON_S2_PORT                      P1
#define SET_PUSHBUTTON_S2_TO_AN_INPUT           PUSHBUTTON_S2_PORT->DIR &= ~PUSHBUTTON_S2_BIT
#define ENABLE_PULL_UP_PULL_DOWN_RESISTORS_S2   PUSHBUTTON_S2_PORT->REN |= PUSHBUTTON_S2_BIT
#define SELECT_PULL_UP_RESISTORS_S2             PUSHBUTTON_S2_PORT->OUT |= PUSHBUTTON_S2_BIT

#endif /* PORTPINS_H_ */
