//=========================================================
// src/InitDevice.c: generated by Hardware Configurator
//
// This file will be regenerated when saving a document.
// leave the sections inside the "$[...]" comment tags alone
// or they will be overwritten!
//=========================================================

// USER INCLUDES
#include "HWinit_loc.h"

// USER PROTOTYPES
// USER FUNCTIONS

// $[Library includes]
#include "em_system.h"
#include "em_emu.h"
#include "em_cmu.h"
#include "em_device.h"
#include "em_chip.h"
#include "em_aes.h"
#include "em_gpio.h"
#include "em_rtc.h"
#include "em_timer.h"
#include "em_usart.h"
// [Library includes]$

//==============================================================================
// enter_DefaultMode_from_RESET
//==============================================================================
extern void enter_DefaultMode_from_RESET(void) {
	// $[Config Calls]
	CMU_enter_DefaultMode_from_RESET();
	RTC_enter_DefaultMode_from_RESET();
	USART0_enter_DefaultMode_from_RESET();
	USART1_enter_DefaultMode_from_RESET();
	TIMER1_enter_DefaultMode_from_RESET();
	PORTIO_enter_DefaultMode_from_RESET();
	// [Config Calls]$

}

//================================================================================
// HFXO_enter_DefaultMode_from_RESET
//================================================================================
extern void HFXO_enter_DefaultMode_from_RESET(void) {
	// $[HFXO]
	// [HFXO]$

}

//================================================================================
// LFXO_enter_DefaultMode_from_RESET
//================================================================================
extern void LFXO_enter_DefaultMode_from_RESET(void) {
	// $[Use oscillator source]
	// [Use oscillator source]$

	// $[LFXO Boost Percent]
	// [LFXO Boost Percent]$

	// $[REDLFXO Boost]
	// [REDLFXO Boost]$

}

//================================================================================
// CMU_enter_DefaultMode_from_RESET
//================================================================================
extern void CMU_enter_DefaultMode_from_RESET(void) {
	// $[LFXO enable]
	// [LFXO enable]$

	// $[HFXO enable]
	// [HFXO enable]$

	// $[LFACLK Setup]
	/* Enable LFRCO oscillator */
	CMU_OscillatorEnable(cmuOsc_LFRCO, true, true);

	/* Select LFRCO as clock source for LFACLK */
	CMU_ClockSelectSet(cmuClock_LFA, cmuSelect_LFRCO);

	// [LFACLK Setup]$

	// $[High Frequency Clock select]
	/* Using HFRCO at 14MHz as high frequency clock, HFCLK */
	CMU_ClockSelectSet(cmuClock_HF, cmuSelect_HFRCO);
	// [High Frequency Clock select]$

	// $[Peripheral Clock enables]
	/* Enable clock for AES */
	CMU_ClockEnable(cmuClock_AES, true);

	/* Enable clock for RTC */
	CMU_ClockEnable(cmuClock_RTC, true);

	/* Enable clock for TIMER1 */
	CMU_ClockEnable(cmuClock_TIMER1, true);

	/* Enable clock for USART0 */
	CMU_ClockEnable(cmuClock_USART0, true);

	/* Enable clock for USART1 */
	CMU_ClockEnable(cmuClock_USART1, true);

	/* Enable clock for GPIO by default */
	CMU_ClockEnable(cmuClock_GPIO, true);

	// [Peripheral Clock enables]$

	// $[LF clock tree setup]
	/* Enable LF clocks */
	CMU_ClockEnable(cmuClock_CORELE, true);
	CMU_ClockSelectSet(cmuClock_LFA, cmuSelect_LFRCO);
	// [LF clock tree setup]$

}

//================================================================================
// ADC0_enter_DefaultMode_from_RESET
//================================================================================
extern void ADC0_enter_DefaultMode_from_RESET(void) {
	// $[ADC_Init]
	// [ADC_Init]$

	// $[ADC_InitSingle]
	// [ADC_InitSingle]$

	// $[ADC_InitScan]
	// [ADC_InitScan]$

}

//================================================================================
// ACMP0_enter_DefaultMode_from_RESET
//================================================================================
extern void ACMP0_enter_DefaultMode_from_RESET(void) {
	// $[ACMP Initialization]
	// [ACMP Initialization]$

	// $[ACMP Channel config]
	// [ACMP Channel config]$

}

//================================================================================
// IDAC0_enter_DefaultMode_from_RESET
//================================================================================
extern void IDAC0_enter_DefaultMode_from_RESET(void) {
	// $[IDAC Initialization]
	// [IDAC Initialization]$

	// $[IDAC optional configurations]
	// [IDAC optional configurations]$

	// $[IDAC enable]
	// [IDAC enable]$

}

//================================================================================
// RTC_enter_DefaultMode_from_RESET
//================================================================================
extern void RTC_enter_DefaultMode_from_RESET(void) {
	// $[RTC_Init]
	RTC_Init_TypeDef init = RTC_INIT_DEFAULT;

	init.debugRun = 0;
	init.comp0Top = 1;

	RTC_Init(&init);
	// [RTC_Init]$

}

//================================================================================
// USART0_enter_DefaultMode_from_RESET
//================================================================================
extern void USART0_enter_DefaultMode_from_RESET(void) {
	// $[USART_InitAsync]
	// [USART_InitAsync]$

	// $[USART_InitSync]
	USART_InitSync_TypeDef initsync = USART_INITSYNC_DEFAULT;

	initsync.baudrate = 5000000;
	initsync.databits = usartDatabits8;
	initsync.master = 1;
	initsync.msbf = 1;
	initsync.clockMode = usartClockMode0;
#if defined( USART_INPUT_RXPRS ) && defined( USART_TRIGCTRL_AUTOTXTEN )
	initsync.prsRxEnable = 0;
	initsync.prsRxCh = 0;
	initsync.autoTx = 0;
#endif

	USART_InitSync(USART0, &initsync);
	// [USART_InitSync]$

	// $[USART_InitPrsTrigger]
	USART_PrsTriggerInit_TypeDef initprs = USART_INITPRSTRIGGER_DEFAULT;

	initprs.rxTriggerEnable = 0;
	initprs.txTriggerEnable = 0;
	initprs.prsTriggerChannel = usartPrsTriggerCh0;

	USART_InitPrsTrigger(USART0, &initprs);
	// [USART_InitPrsTrigger]$

}

//================================================================================
// USART1_enter_DefaultMode_from_RESET
//================================================================================
extern void USART1_enter_DefaultMode_from_RESET(void) {
	// $[USART_InitAsync]
	USART_InitAsync_TypeDef initasync = USART_INITASYNC_DEFAULT;

	initasync.baudrate = 115200;
	initasync.databits = usartDatabits8;
	initasync.parity = usartEvenParity;
	initasync.stopbits = usartStopbits1;
	initasync.oversampling = usartOVS16;
#if defined( USART_INPUT_RXPRS ) && defined( USART_CTRL_MVDIS )
	initasync.mvdis = 0;
	initasync.prsRxEnable = 0;
	initasync.prsRxCh = 0;
#endif

	USART_InitAsync(USART1, &initasync);
	// [USART_InitAsync]$

	// $[USART_InitSync]
	// [USART_InitSync]$

	// $[USART_InitPrsTrigger]
	USART_PrsTriggerInit_TypeDef initprs = USART_INITPRSTRIGGER_DEFAULT;

	initprs.rxTriggerEnable = 0;
	initprs.txTriggerEnable = 0;
	initprs.prsTriggerChannel = usartPrsTriggerCh0;

	USART_InitPrsTrigger(USART1, &initprs);
	// [USART_InitPrsTrigger]$

}

//================================================================================
// LEUART0_enter_DefaultMode_from_RESET
//================================================================================
extern void LEUART0_enter_DefaultMode_from_RESET(void) {
	// $[LEUART0 initialization]
	// [LEUART0 initialization]$

}

//================================================================================
// VCMP_enter_DefaultMode_from_RESET
//================================================================================
extern void VCMP_enter_DefaultMode_from_RESET(void) {
	// $[VCMP_Init]
	// [VCMP_Init]$

}

//================================================================================
// WDOG_enter_DefaultMode_from_RESET
//================================================================================
extern void WDOG_enter_DefaultMode_from_RESET(void) {
	// $[CMU_ClockEnable]
	// [CMU_ClockEnable]$

	// $[CMU_OscillatorEnable]
	// [CMU_OscillatorEnable]$

	// $[WDOG_Init]
	// [WDOG_Init]$

}

//================================================================================
// I2C0_enter_DefaultMode_from_RESET
//================================================================================
extern void I2C0_enter_DefaultMode_from_RESET(void) {
	// $[I2C0 initialization]
	// [I2C0 initialization]$

}

//================================================================================
// TIMER0_enter_DefaultMode_from_RESET
//================================================================================
extern void TIMER0_enter_DefaultMode_from_RESET(void) {
	// $[TIMER0 initialization]
	// [TIMER0 initialization]$

	// $[TIMER0 CC0 init]
	// [TIMER0 CC0 init]$

	// $[TIMER0 CC1 init]
	// [TIMER0 CC1 init]$

	// $[TIMER0 CC2 init]
	// [TIMER0 CC2 init]$

	// $[TIMER0 DTI init]
	// [TIMER0 DTI init]$

}

//================================================================================
// TIMER1_enter_DefaultMode_from_RESET
//================================================================================
extern void TIMER1_enter_DefaultMode_from_RESET(void) {
	// $[TIMER1 initialization]
	TIMER_Init_TypeDef init = TIMER_INIT_DEFAULT;

	init.enable = 1;
	init.debugRun = 0;
	init.dmaClrAct = 0;
	init.sync = 0;
	init.clkSel = timerClkSelHFPerClk;
	init.prescale = timerPrescale1;
	init.fallAction = timerInputActionNone;
	init.riseAction = timerInputActionNone;
	init.mode = timerModeUp;
	init.quadModeX4 = 0;
	init.oneShot = 0;
	init.count2x = 0;
	init.ati = 0;
	TIMER_Init(TIMER1, &init);
	// [TIMER1 initialization]$

	// $[TIMER1 CC0 init]
	TIMER_InitCC_TypeDef initCC0 = TIMER_INITCC_DEFAULT;

	initCC0.prsInput = false;
	initCC0.prsSel = timerPRSSELCh0;
	initCC0.edge = timerEdgeRising;
	initCC0.mode = timerCCModeOff;
	initCC0.eventCtrl = timerEventEveryEdge;
	initCC0.filter = 0;
	initCC0.cofoa = timerOutputActionNone;
	initCC0.cufoa = timerOutputActionNone;
	initCC0.cmoa = timerOutputActionNone;
	initCC0.coist = 0;
	initCC0.outInvert = 0;
	TIMER_InitCC(TIMER1, 0, &initCC0);
	// [TIMER1 CC0 init]$

	// $[TIMER1 CC1 init]
	TIMER_InitCC_TypeDef initCC1 = TIMER_INITCC_DEFAULT;

	initCC1.prsInput = false;
	initCC1.prsSel = timerPRSSELCh0;
	initCC1.edge = timerEdgeRising;
	initCC1.mode = timerCCModeOff;
	initCC1.eventCtrl = timerEventEveryEdge;
	initCC1.filter = 0;
	initCC1.cofoa = timerOutputActionNone;
	initCC1.cufoa = timerOutputActionNone;
	initCC1.cmoa = timerOutputActionNone;
	initCC1.coist = 0;
	initCC1.outInvert = 0;
	TIMER_InitCC(TIMER1, 1, &initCC1);
	// [TIMER1 CC1 init]$

	// $[TIMER1 CC2 init]
	TIMER_InitCC_TypeDef initCC2 = TIMER_INITCC_DEFAULT;

	initCC2.prsInput = false;
	initCC2.prsSel = timerPRSSELCh0;
	initCC2.edge = timerEdgeRising;
	initCC2.mode = timerCCModeOff;
	initCC2.eventCtrl = timerEventEveryEdge;
	initCC2.filter = 0;
	initCC2.cofoa = timerOutputActionNone;
	initCC2.cufoa = timerOutputActionNone;
	initCC2.cmoa = timerOutputActionNone;
	initCC2.coist = 0;
	initCC2.outInvert = 0;
	TIMER_InitCC(TIMER1, 2, &initCC2);
	// [TIMER1 CC2 init]$

}

//================================================================================
// PCNT0_enter_DefaultMode_from_RESET
//================================================================================
extern void PCNT0_enter_DefaultMode_from_RESET(void) {
	// $[PCNT0 initialization]
	// [PCNT0 initialization]$

}

//================================================================================
// PRS_enter_DefaultMode_from_RESET
//================================================================================
extern void PRS_enter_DefaultMode_from_RESET(void) {
	// $[PRS initialization]
	// [PRS initialization]$

}

extern void PORTIO_enter_DefaultMode_from_RESET(void) {

	// $[Port A Configuration]

	/* Pin PA0 is configured to Input enabled */
	GPIO->P[0].MODEL = (GPIO->P[0].MODEL & ~_GPIO_P_MODEL_MODE0_MASK)
			| GPIO_P_MODEL_MODE0_INPUT;

	/* Pin PA1 is configured to Push-pull */
	GPIO->P[0].DOUT |= (1 << 1);
	GPIO->P[0].MODEL = (GPIO->P[0].MODEL & ~_GPIO_P_MODEL_MODE1_MASK)
			| GPIO_P_MODEL_MODE1_PUSHPULL;

	/* Pin PA2 is configured to Push-pull */
	GPIO->P[0].MODEL = (GPIO->P[0].MODEL & ~_GPIO_P_MODEL_MODE2_MASK)
			| GPIO_P_MODEL_MODE2_PUSHPULL;
	// [Port A Configuration]$

	// $[Port B Configuration]

	/* Pin PB11 is configured to Push-pull */
	GPIO->P[1].MODEH = (GPIO->P[1].MODEH & ~_GPIO_P_MODEH_MODE11_MASK)
			| GPIO_P_MODEH_MODE11_PUSHPULL;

	/* Pin PB13 is configured to Push-pull */
	GPIO->P[1].MODEH = (GPIO->P[1].MODEH & ~_GPIO_P_MODEH_MODE13_MASK)
			| GPIO_P_MODEH_MODE13_PUSHPULL;

	/* Pin PB14 is configured to Push-pull */
	GPIO->P[1].MODEH = (GPIO->P[1].MODEH & ~_GPIO_P_MODEH_MODE14_MASK)
			| GPIO_P_MODEH_MODE14_PUSHPULL;
	// [Port B Configuration]$

	// $[Port C Configuration]

	/* Pin PC0 is configured to Push-pull */
	GPIO->P[2].MODEL = (GPIO->P[2].MODEL & ~_GPIO_P_MODEL_MODE0_MASK)
			| GPIO_P_MODEL_MODE0_PUSHPULL;

	/* Pin PC1 is configured to Push-pull */
	GPIO->P[2].MODEL = (GPIO->P[2].MODEL & ~_GPIO_P_MODEL_MODE1_MASK)
			| GPIO_P_MODEL_MODE1_PUSHPULL;

	/* Pin PC14 is configured to Input enabled */
	GPIO->P[2].MODEH = (GPIO->P[2].MODEH & ~_GPIO_P_MODEH_MODE14_MASK)
			| GPIO_P_MODEH_MODE14_INPUT;

	/* Pin PC15 is configured to Input enabled */
	GPIO->P[2].MODEH = (GPIO->P[2].MODEH & ~_GPIO_P_MODEH_MODE15_MASK)
			| GPIO_P_MODEH_MODE15_INPUT;
	// [Port C Configuration]$

	// $[Port D Configuration]

	/* Pin PD5 is configured to Push-pull */
	GPIO->P[3].MODEL = (GPIO->P[3].MODEL & ~_GPIO_P_MODEL_MODE5_MASK)
			| GPIO_P_MODEL_MODE5_PUSHPULL;

	/* Pin PD6 is configured to Input enabled */
	GPIO->P[3].MODEL = (GPIO->P[3].MODEL & ~_GPIO_P_MODEL_MODE6_MASK)
			| GPIO_P_MODEL_MODE6_INPUT;

	/* Pin PD7 is configured to Push-pull */
	GPIO->P[3].MODEL = (GPIO->P[3].MODEL & ~_GPIO_P_MODEL_MODE7_MASK)
			| GPIO_P_MODEL_MODE7_PUSHPULL;
	// [Port D Configuration]$

	// $[Port E Configuration]

	/* Pin PE10 is configured to Push-pull */
	GPIO->P[4].MODEH = (GPIO->P[4].MODEH & ~_GPIO_P_MODEH_MODE10_MASK)
			| GPIO_P_MODEH_MODE10_PUSHPULL;

	/* Pin PE11 is configured to Input enabled */
	GPIO->P[4].MODEH = (GPIO->P[4].MODEH & ~_GPIO_P_MODEH_MODE11_MASK)
			| GPIO_P_MODEH_MODE11_INPUT;

	/* Pin PE12 is configured to Push-pull */
	GPIO->P[4].MODEH = (GPIO->P[4].MODEH & ~_GPIO_P_MODEH_MODE12_MASK)
			| GPIO_P_MODEH_MODE12_PUSHPULL;

	/* Pin PE13 is configured to Push-pull */
	GPIO->P[4].DOUT |= (1 << 13);
	GPIO->P[4].MODEH = (GPIO->P[4].MODEH & ~_GPIO_P_MODEH_MODE13_MASK)
			| GPIO_P_MODEH_MODE13_PUSHPULL;
	// [Port E Configuration]$

	// $[Port F Configuration]

	/* Pin PF2 is configured to Push-pull */
	GPIO->P[5].MODEL = (GPIO->P[5].MODEL & ~_GPIO_P_MODEL_MODE2_MASK)
			| GPIO_P_MODEL_MODE2_PUSHPULL;
	// [Port F Configuration]$

	// $[Route Configuration]

	/* Module PCNT0 is configured to location 0 */
	PCNT0->ROUTE = (PCNT0->ROUTE & ~_PCNT_ROUTE_LOCATION_MASK)
			| PCNT_ROUTE_LOCATION_LOC0;

	/* Enable signals CLK, RX, TX */
	USART0->ROUTE |= USART_ROUTE_CLKPEN | USART_ROUTE_RXPEN | USART_ROUTE_TXPEN;

	/* Module USART1 is configured to location 3 */
	USART1->ROUTE = (USART1->ROUTE & ~_USART_ROUTE_LOCATION_MASK)
			| USART_ROUTE_LOCATION_LOC3;

	/* Enable signals RX, TX */
	USART1->ROUTE |= USART_ROUTE_RXPEN | USART_ROUTE_TXPEN;
	// [Route Configuration]$

}

