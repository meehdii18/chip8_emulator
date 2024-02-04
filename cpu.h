#ifndef CPU_HEADER_GUARD
#define CPU_HEADER_GUARD

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "ram.h"
#include "display/display.h"
#include "display/sprite.h"
#include "keyboard/keyboard.h"
#include "misc/error.h"
#include "speaker/speaker.h"

/** \typedef Cpu
 *
 * \brief A virtual processor for Chip 8 emulator.
 *
 */
typedef struct Cpu {
    uint8_t V[16];

    uint16_t I;

    uint8_t ST;

    uint8_t DT;

    uint16_t PC;

    uint8_t SP;

    uint16_t stack[16];

    Ram *memory;

    struct Display *display;

    struct Keyboard *keyboard;

    struct Speaker *speaker;

} Cpu;

/** \name Cpu_new
 *
 * \brief Creates a new virtual processor, allocates memory to it, initialize it and return a pointer to it.
 *
 * @return Pointer to the newly created processor
 */
Cpu *Cpu_new(void);

/** \name Cpu_init
 *
 * \brief Initialize the given processor
 *
 * @param processor : The processor that needs to be initialized
 */
void Cpu_init(Cpu *processor);

/** \name Cpu_delete
 *
 * \brief Deletes the given processor, free the memory allocated to it.
 *
 * @param processor : the processor thats needs to be deleted
 */
void Cpu_delete(Cpu *processor);

/** \name Cpu_destroy
 *
 * \brief Does nothing.
 *
 * @param processor
 */
void Cpu_destroy(Cpu *processor);

/** \name fetch-decode-execute
 *
 * \brief This function does three action that comes together. First, it reads 4 bytes in memory at the address stored in the program counter of the processor. Second, it find if those bytes correspond to an instruction interpretable by the Chip 8. Third, if the second is true, it executes the corresponding instruction.
 *
 * @param processor : the virtual processor on which you execute your program
 */
void fetch_decode_execute(Cpu *processor);

//------------------------------------------------------------
//-----------------Instructions-------------------------------
//------------------------------------------------------------

/** \instruction 00E0 - CLS
 *
 * \brief Clear the display.
 *
 * @param processor : virtual CPU of the machine
 */
void CLS(Cpu *processor);

/** \instruction 00E0 - RET
 *
 * \brief Return from a subroutine. The interpreter sets the program counter to the address at the top of the stack, then subtracts 1 from the stack pointer.
 *
 * @param processor : virtual CPU of the machine
 */
void RET(Cpu *processor);

/** \instruction 1nnn - JP addr
 *
 * \brief Jump to location nnn. The interpreter sets the program counter to nnn.
 *
 * @param processor : virtual CPU of the machine
 * @param addr : address to jump to in the virtual RAM of the processor
 */
void JP_addr(Cpu *processor, uint16_t addr);

/** \instruction 2nnn - CALL addr
 *
 * \brief Call subroutine at nnn. The interpreter increments the stack pointer, then puts the current PC on the top of the stack. The PC is then set to nnn.
 *
 * @param processor : virtual CPU of the machine
 * @param addr : address to call in the virtual RAM of the processor
 */
void CALL_addr(Cpu *processor, uint16_t addr);

/** \instruction 3xkk - SE Vx, byte
 *
 * \brief Skip next instruction if Vx = kk. The interpreter compares register Vx to kk, and if they are equal, increments the program counter by 2.
 *
 * @param processor : virtual CPU of the machine
 * @param x : register number of the CPU register Vx
 * @param byte : a value between 0 and 255
 */
void SE_Vx_byte(Cpu *processor, uint8_t x, uint8_t byte);

/** \instruction 4xkk - SNE Vx, byte
 *
 * \brief Skip next instruction if Vx != kk. The interpreter compares register Vx to kk, and if they are not equal, increments the program counter by 2.
 *
 * @param processor : virtual CPU of the machine
 * @param x : register number of the CPU register Vx
 * @param byte : a value between 0 and 255
 */
void SNE_Vx_byte(Cpu *processor, uint8_t x, uint8_t byte);

/** \instruction 5xy0 - SE Vx,Vy
 *
 * \brief Skip next instruction if Vx = Vy. The interpreter compares register Vx to register Vy, and if they are equal, increments the program counter by 2.
 *
 * @param processor : virtual CPU of the machine
 * @param x : register number of the CPU register Vx
 * @param y : register number of the CPU register Vy
 */
void SE_Vx_Vy(Cpu *processor, uint8_t x, uint8_t y);

/**  \instruction 6xkk - LD Vx, byte
 *
 * \brief Set Vx = kk. The interpreter puts the value kk into register Vx.
 *
 * @param processor : virtual CPU of the machine
 * @param x : register number of the CPU register Vx
 * @param byte : a value between 0 and 255
 */
void LD_Vx_byte(Cpu *processor, uint8_t x, uint8_t byte);

/** \instrution 7xkk - ADD Vx, byte
 *
 * \brief Set Vx = Vx + kk. Adds the value kk to the value of register Vx, then stores the result in Vx.
 *
 * @param processor : virtual CPU of the machine
 * @param x : register number of the CPU register Vx
 * @param byte : a value between 0 and 255
 */
void ADD_Vx_byte(Cpu *processor, uint8_t x, uint8_t byte);

/** \instruction 8xy0 - LD Vx, Vy
 *
 * \brief Set Vx = Vy. Stores the value of register Vy in register Vx.
 *
 * @param processor : virtual CPU of the machine
 * @param x : register number of the CPU register Vx
 * @param y : register number of the CPU register Vy
 */
void LD_Vx_Vy(Cpu *processor, uint8_t x, uint8_t y);

/** \instruction 8xy1 - OR Vx, Vy
 *
 * \brief Set Vx = Vx OR Vy. Performs a bitwise OR on the values of Vx and Vy, then stores the result in Vx. A bitwise OR compares the corrseponding bits from two values, and if either bit is 1, then the same bit in the result is also 1. Otherwise, it is 0.
 *
 * @param processor : virtual CPU of the machine
 * @param x : register number of the CPU register Vx
 * @param y : register number of the CPU register Vy
 */
void OR_Vx_Vy(Cpu *processor, uint8_t x, uint8_t y);

/** \instruction 8xy2 - AND Vx, Vy
 *
 * \brief Set Vx = Vx AND Vy. Performs a bitwise AND on the values of Vx and Vy, then stores the result in Vx. A bitwise AND compares the corrseponding bits from two values, and if both bits are 1, then the same bit in the result is also 1. Otherwise, it is 0.
 *
 * @param processor : virtual CPU of the machine
 * @param x : register number of the CPU register Vx
 * @param y : register number of the CPU register Vy
 */
void AND_Vx_Vy(Cpu *processor, uint8_t x, uint8_t y);

/** \instruction 8xy3 - XOR Vx, Vy
 *
 * \brief Set Vx = Vx XOR Vy. Performs a bitwise exclusive OR on the values of Vx and Vy, then stores the result in Vx. An exclusive OR compares the corrseponding bits from two values, and if the bits are not both the same, then the corresponding bit in the result is set to 1. Otherwise, it is 0.
 *
 * @param processor : virtual CPU of the machine
 * @param x : register number of the CPU register Vx
 * @param y : register number of the CPU register Vy
 */
void XOR_Vx_Vy(Cpu *processor, uint8_t x, uint8_t y);

/** \instruction 8xy4 - ADD Vx, Vy
 *
 * \brief Set Vx = Vx + Vy, set VF = carry. The values of Vx and Vy are added together. If the result is greater than 8 bits (i.e., > 255,) VF is set to 1, otherwise 0. Only the lowest 8 bits of the result are kept, and stored in Vx.
 *
 * @param processor : virtual CPU of the machine
 * @param x : register number of the CPU register Vx
 * @param y : register number of the CPU register Vy
 */
void ADD_Vx_Vy(Cpu *processor, uint8_t x, uint8_t y);

/** \instruction 8xy5 - SUB Vx, Vy
 *
 * \brief Set Vx = Vx - Vy, set VF = NOT borrow. If Vx > Vy, then VF is set to 1, otherwise 0. Then Vy is subtracted from Vx, and the results stored in Vx.
 *
 * @param processor : virtual CPU of the machine
 * @param x : register number of the CPU register Vx
 * @param y : register number of the CPU register Vy
 */
void SUB_Vx_Vy(Cpu *processor, uint8_t x, uint8_t y);

/** \instruction 8xy6 - SHR Vx , Vy
 *
 * \brief Set Vx = Vy SHR 1. f the least-significant bit of Vy is 1, then VF is set to 1, otherwise 0. Then Vx = Vy divided by 2.
 *
 * @param processor : virtual CPU of the machine
 * @param x : register number of the CPU register Vx
 * @param y : register number of the CPU register Vy
 */
void SHR_Vx(Cpu *processor, uint8_t x, uint8_t y);

/** \instruction 8xy7 - SUBN Vx, Vy
 *
 * \brief Set Vx = Vy - Vx, set VF = NOT borrow. If Vy > Vx, then VF is set to 1, otherwise 0. Then Vx is subtracted from Vy, and the results stored in Vx.
 *
 * @param processor : virtual CPU of the machine
 * @param x : register number of the CPU register Vx
 * @param y : register number of the CPU register Vy
 */
void SUBN_Vx_Vy(Cpu *processor, uint8_t x, uint8_t y);

/** \instruction 8xyE - SHL Vx , Vy
 *
 * \brief Set Vx = Vy SHL 1. If the most-significant bit of Vy is 1, then VF is set to 1, otherwise to 0. Then Vx = Vy multiplied by 2.
 *
 * @param processor : virtual CPU of the machine
 * @param x : register number of the CPU register Vx
 * @param y : register number of the CPU register Vy
 */
void SHL_Vx(Cpu *processor, uint8_t x, uint8_t y);

/** \instruction 9xy0 - SNE Vx, Vy
 *
 * \brief Skip next instruction if Vx != Vy. The values of Vx and Vy are compared, and if they are not equal, the program counter is increased by 2.
 *
 * @param processor : virtual CPU of the machine
 * @param x : register number of the CPU register Vx
 * @param y : register number of the CPU register Vy
 */
void SNE_Vx_Vy(Cpu *processor, uint8_t x, uint8_t y);

/** \instruction Annn - LD I, addr
 *
 * \brief Set I = nnn. The value of register I is set to nnn.
 *
 * @param processor : virtual CPU of the machine
 * @param addr : address to load in the I register of the processor
 */
void LD_I_addr(Cpu *processor, uint16_t addr);

/** \instruction Bnnn - JP V0, addr
 *
 * \brief Jump to location nnn + V0. The program counter is set to nnn plus the value of V0.
 *
 * @param processor : virtual CPU of the machine
 * @param addr : address to add to register V0 before jumping to it
 */
void JP_V0_addr(Cpu *processor, uint16_t addr);

/** \instruction Cxkk - RND Vx, byte
 *
 * \brief Set Vx = random byte AND kk. The interpreter generates a random number from 0 to 255, which is then ANDed with the value kk. The results are stored in Vx. See instruction 8xy2 for more information on AND.
 *
 * @param processor : virtual CPU of the machine
 * @param x : register number of the CPU register Vx
 * @param byte : a value between 0 and 255
 */
void RND_Vx_byte(Cpu *processor, uint8_t x, uint8_t byte);

/** \instruction Dxyn - DRW Vx, Vy, nibble
 *
 * \brief Display n-byte sprite starting at memory location I at (Vx, Vy), set VF = collision. The interpreter reads n bytes from memory, starting at the address stored in I. These bytes are then displayed as sprites on screen at coordinates (Vx, Vy). Sprites are XORed onto the existing screen. If this causes any pixels to be erased, VF is set to 1, otherwise it is set to 0. If the sprite is positioned so part of it is outside the coordinates of the display, it wraps around to the opposite side of the screen. See instruction 8xy3 for more information on XOR.
 *
 * @param processor : virtual CPU of the machine
 * @param x : register number of the CPU register Vx
 * @param y : register number of the CPU register Vy
 * @param nibble : number of bytes the sprite to draw is stored into
 */
void DRW_Vx_Vy_nibble(Cpu *processor, uint8_t x, uint8_t y, uint8_t nibble);

/** \instruction Ex9E - SKP Vx
 *
 * \brief Skip next instruction if key with the value of Vx is pressed. Checks the keyboard, and if the key corresponding to the value of Vx is currently in the down position, PC is increased by 2.
 *
 * @param processor : virtual CPU of the machine
 * @param x : register number of the CPU register Vx
 */
void SKP_Vx(Cpu *processor, uint8_t x);

/** \instruction ExA1 - SKNP Vx
 *
 * \brief Skip next instruction if key with the value of Vx is not pressed. Checks the keyboard, and if the key corresponding to the value of Vx is currently in the up position, PC is increased by 2.
 *
 * @param processor : virtual CPU of the machine
 * @param x : register number of the CPU register Vx
 */
void SKNP_Vx(Cpu *processor, uint8_t x);

/** \instruction Fx07 - LD Vx, DT
 *
 * \brief Set Vx = delay timer value. The value of DT is placed into Vx.
 *
 * @param processor : virtual CPU of the machine
 * @param x : register number of the CPU register Vx
 */
void LD_Vx_DT(Cpu *processor, uint8_t x);

/** \instruction Fx0A - LD Vx, K
 *
 * \brief Wait for a key press, store the value of the key in Vx. All execution stops until a key is pressed, then the value of that key is stored in Vx.
 *
 * @param processor : virtual CPU of the machine
 * @param x : register number of the CPU register Vx
 */
void LD_Vx_K(Cpu *processor, uint8_t x);

/** \instruction Fx15 - LD DT, Vx
 *
 * \brief Set delay timer = Vx. DT is set equal to the value of Vx.
 *
 * @param processor : virtual CPU of the machine
 * @param x : register number of the CPU register Vx
 */
void LD_DT_Vx(Cpu *processor, uint8_t x);

/** \instruction Fx18 - LD ST, Vx
 *
 * \brief Set sound timer = Vx. ST is set equal to the value of Vx.
 *
 * @param processor : virtual CPU of the machine
 * @param x : register number of the CPU register Vx
 */
void LD_ST_Vx(Cpu *processor, uint8_t x);

/** \instruction Fx1E - ADD I, Vx
 *
 * \brief Set I = I + Vx. The values of I and Vx are added, and the results are stored in I.
 *
 * @param processor : virtual CPU of the machine
 * @param x : register number of the CPU register Vx
 */
void ADD_I_Vx(Cpu *processor, uint8_t x);

/** \instruction Fx29 - LD F, Vx
 *
 * \brief Set I = location of sprite for digit Vx. The value of I is set to the location for the hexadecimal sprite corresponding to the value of Vx. See section 2.4, Display, for more information on the Chip-8 hexadecimal font.
 *
 * @param processor : virtual CPU of the machine
 * @param x : register number of the CPU register Vx
 */
void LD_F_Vx(Cpu *processor, uint8_t x);

/** \instruction Fx33 - LD B, Vx
 *
 * \brief Store BCD representation of Vx in memory locations I, I+1, and I+2. The interpreter takes the decimal value of Vx, and places the hundreds digit in memory at location in I, the tens digit at location I+1, and the ones digit at location I+2.
 *
 * @param processor : virtual CPU of the machine
 * @param x : register number of the CPU register Vx
 */
void LD_B_Vx(Cpu *processor, uint8_t x);

/** \instruction Fx55 - LD [I], Vx
 *
 * \brief Store registers V0 through Vx in memory starting at location I. The interpreter copies the values of registers V0 through Vx into memory, starting at the address in I.
 *
 * @param processor : virtual CPU of the machine
 * @param x : register number of the CPU register Vx
 */
void LD_I_Vx(Cpu *processor, uint8_t x);

/** \instruction Fx65 - LD Vx, [I]
 *
 * \brief Read registers V0 through Vx from memory starting at location I. The interpreter reads values from memory starting at location I into registers V0 through Vx.
 *
 * @param processor : virtual CPU of the machine
 * @param x : register number of the CPU register Vx
 */
void LD_Vx_I(Cpu *processor, uint8_t x);

#endif