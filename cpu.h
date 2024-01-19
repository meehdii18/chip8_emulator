#ifndef CHIP8_CPU_H
#define CHIP8_CPU_H

#include "ram.h"
#include <assert.h>
#include <SDL2/SDL.h>
#include <stdint.h>
#include "display/display.h"
#include "display/sprite.h"
#include "speaker/speaker.h"
#include "keyboard/keyboard.h"


/**
 * \file cpu.h
 * \brief Contains the processor data structure and all related functions declarations
 */

/**
 * \struct Processor
 * \brief Processor of the emulated CHIP8
 */
typedef struct Processor{
    uint8_t V[16]; /*!< 16 general purpose 8-bit registers, referred to as V0, V1, ..., VF */
    uint16_t I; /*!< used to store memory addresses */
    uint8_t ST; /*!< Sound timer register */
    uint8_t DT; /*!< Delay timer register */
    uint16_t PC; /*!< a 16-bit register, called program counter or PC, used to store the address of the instruction currently being executed */
    uint8_t SP; /*!< Pointer to the topmost level of the stack */
    uint16_t stack[16]; /*!< a 16 16-bit values array to store the addresses that the interpreter should return to when a subroutine terminates */
    struct RAM* ram; /*!< Pointer to the RAM memory linked to the cpu */
    // Attached I/O devices
} Processor;


/**
 * Initializes the processor structure
 * @return A pointer to the initialized Processor structure, NULL if failed
 */
Processor* newProcessor(RAM* ram);

/**
 *
 * @param cpu A pointer to the processor to delete
 */
void deleteProcessor(Processor* cpu);

/**
 * Clear the display
 * @param display
 */
void CLS(struct Display* display);

/**
 * Sets the program counter to the address at the top of the stack, then subtracts 1 from the stack pointer.
 * @param cpu The processor that will execute the instruction
 */
void RET(Processor* cpu);

/**
 * Sets the program counter to adr.
 * @param cpu The processor that will execute the instruction
 * @param adr The address to use
 */
void JP_addr(Processor* cpu,u_int16_t adr);

/**
 * Increments the stack pointer, then puts the current PC on the top of the stack. The PC is then set to adr.
 * @param cpu The processor that will execute the instruction
 * @param adr The address that to
 */
void CALL_addr(Processor* cpu, uint16_t adr);

/**
 * Compares register Vx to kk, and if they are equal, increments the program counter by 2.
 * @param cpu
 * @param value
 * @param x
 */
void SE_Vx(Processor* cpu, uint8_t value,uint8_t x);

/**
 * Compares register Vx to kk, and if they are not equal, increments the program counter by 2.
 * @param cpu
 * @param value
 * @param x
 */
void SNE_Vx(Processor* cpu, uint8_t value,uint8_t x);

/**
 * Compares register Vx to register Vy, and if they are equal, increments the program counter by 2.
 * @param cpu
 * @param x
 * @param y
 */
void SE_Vx_Vy(Processor* cpu, uint8_t x, uint8_t y);

/**
 * Puts the value kk into register Vx.
 * @param cpu
 * @param x
 * @param value
 */
void LD_Vx_Byte(Processor* cpu, uint8_t x, uint8_t value);

/**
 * Adds the value kk to the value of register Vx, then stores the result in Vx.
 * @param cpu
 * @param x
 * @param value
 */
void ADD_Vx_Byte(Processor* cpu, uint8_t x, uint8_t value);

/**
 * Stores the value of register Vy in register Vx.
 * @param cpu
 * @param x
 * @param y
 */
void LD_Vx_Vy(Processor* cpu, uint8_t x, uint8_t y);

/**
 * Performs a bitwise OR on the values of Vx and Vy, then stores the result in Vx. A bitwise OR compares the corresponding
 * bits from two values, and if either bit is 1, then the same bit in the result is also 1. Otherwise, it is 0.
 * @param cpu
 * @param x
 * @param y
 */
void OR_Vx_Vy(Processor* cpu, uint8_t x, uint8_t y);

/**
 * Performs a bitwise AND on the values of Vx and Vy, then stores the result in Vx. A bitwise AND compares the corresponding
 * bits from two values, and if both bits are 1, then the same bit in the result is also 1. Otherwise, it is 0.
 * @param cpu
 * @param x
 * @param y
 */
void AND_Vx_Vy(Processor* cpu, uint8_t x, uint8_t y);

/**
 * Performs a bitwise exclusive OR on the values of Vx and Vy, then stores the result in Vx. An exclusive OR compares the corresponding
 * bits from two values, and if the bits are not both the same, then the corresponding bit in the result is set to 1. Otherwise, it is 0.
 * @param cpu
 * @param x
 * @param y
 */
void XOR_Vx_Vy(Processor* cpu, uint8_t x, uint8_t y);

/**
 * The values of Vx and Vy are added together. If the result is greater than 8 bits (i.e., > 255,) VF is set to 1, otherwise 0.
 * Only the lowest 8 bits of the result are kept, and stored in Vx.
 * @param cpu
 * @param x
 * @param y
 */
void ADD_Vx_Vy(Processor* cpu, uint8_t x, uint8_t y);

/**
 * If Vx > Vy, then VF is set to 1, otherwise 0. Then Vy is subtracted from Vx, and the results stored in Vx.
 * @param cpu
 * @param x
 * @param y
 */
void SUB_Vx_Vy(Processor* cpu, uint8_t x, uint8_t y);

/**
 * If the least-significant bit of Vx is 1, then VF is set to 1, otherwise 0. Then Vx is divided by 2.
 * @param cpu
 * @param x
 */
void SHR_Vx(Processor *cpu, uint8_t x, uint8_t y);

/**
 * If Vy > Vx, then VF is set to 1, otherwise 0. Then Vx is subtracted from Vy, and the results stored in Vx.
 * @param cpu
 * @param x
 * @param y
 */
void SUBN_Vx_Vy(Processor* cpu, uint8_t x, uint8_t y);

/**
 * If the most-significant bit of Vx is 1, then VF is set to 1, otherwise to 0. Then Vx is multiplied by 2.
 * @param cpu
 * @param x
 */
void SHL_Vx(Processor* cpu, uint8_t x, uint8_t y);

/**
 * The values of Vx and Vy are compared, and if they are not equal, the program counter is increased by 2.
 * @param cpu
 * @param x
 * @param y
 */
void SNE_Vx_Vy(Processor* cpu, uint8_t x,uint8_t y);

/**
 * The value of register I is set to nnn.
 * @param cpu
 * @param value
 */
void LD_I(Processor* cpu, uint16_t value);

/**
 * The program counter is set to nnn plus the value of V0.
 * @param cpu
 * @param value
 */
void JP_V0(Processor* cpu, uint16_t value);

/**
 * The interpreter generates a random number from 0 to 255, which is then ANDed with the value kk. The results are stored in Vx.
 * @param cpu
 * @param x
 * @param kkk
 */
void RND_Vx(Processor* cpu, uint8_t x, uint8_t kkk);

/**
 * The interpreter reads n bytes from memory, starting at the address stored in I. These bytes are then displayed as sprites on screen at coordinates (Vx, Vy).
 * Sprites are XORed onto the existing screen. If this causes any pixels to be erased, VF is set to 1, otherwise it is set to 0.
 * If the sprite is positioned so part of it is outside the coordinates of the display, it wraps around to the opposite side of the screen.
 * @param cpu
 * @param x
 * @param y
 * @param n
 */
void DRW_Vx_Vy(Processor* cpu, struct Display* display, uint8_t x, uint8_t y, uint8_t n);

/**
 * Checks the keyboard, and if the key corresponding to the value of Vx is currently in the down position, PC is increased by 2.
 * @param cpu
 * @param x
 */
void SKP_Vx(Processor* cpu,struct Keyboard* keyboard,uint8_t x);

/**
 * Checks the keyboard, and if the key corresponding to the value of Vx is currently in the up position, PC is increased by 2.
 * @param cpu
 * @param x
 */
void SNKP_Vx(Processor* cpu,struct Keyboard* keyboard,uint8_t x);

/**
 * The value of DT is placed into Vx.
 * @param cpu
 * @param x
 */
void LD_Vx_DT(Processor* cpu,uint8_t x);

/**
 * All execution stops until a key is pressed, then the value of that key is stored in Vx.
 * @param cpu
 * @param x
 */
void LD_Vx_K(Processor* cpu, struct Keyboard* keyboard, uint8_t x);

/**
 * DT is set equal to the value of Vx.
 * @param cpu
 * @param x
 */
void LD_DT_Vx(Processor* cpu, uint8_t x);

/**
 * ST is set equal to the value of Vx.
 * @param cpu
 * @param x
 */
void LD_ST_Vx(Processor* cpu, uint8_t x);

/**
 * The values of I and Vx are added, and the results are stored in I.
 * @param cpu
 * @param x
 */
void ADD_I_Vx(Processor* cpu, uint8_t x);

/**
 * The value of I is set to the location for the hexadecimal sprite corresponding to the value of Vx.
 * @param cpu
 * @param x
 */
void LD_F_Vx(Processor* cpu, uint8_t x);

/**
 * The interpreter takes the decimal value of Vx, and places the hundreds digit in memory at location in I, the tens digit at location I+1, and the ones digit at location I+2.
 * @param cpu
 * @param x
 */
void LD_B_Vx(Processor* cpu, uint8_t x);

/**
 * The interpreter copies the values of registers V0 through Vx into memory, starting at the address in I.
 * @param cpu
 * @param x
 */
void LD_I_Vx(Processor* cpu,uint8_t x);

/**
 * The interpreter reads values from memory starting at location I into registers V0 through Vx.
 * @param cpu
 * @param x
 */
void LD_Vx_I(Processor* cpu, uint8_t x);

/**
 * Fetches, decodes, and executes the next instruction in the RAM.
 * @param cpu
 */
void fetch_decode_execute(Processor *cpu, struct Display *display, struct Keyboard *keyboard);

/**
 * Load default sprites into the ram.
 * @param cpu
 */
void Load_sprite(Processor* cpu);

/**
 * Decrement sound and delay timers by 1.
 * @param cpu
 */
void decrement_timers(Processor* cpu);

#endif //CHIP8_CPU_H