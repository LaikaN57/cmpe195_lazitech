/**
 * @file output.h
 * @author  Alex Kennedy <alexzanderkennedy@gmail.com>
 * @version 1.0
 *
 * @section DESCRIPTION
 *
 * The interface for the output module. This will be called by the decoder.
 */

#ifndef OUTPUT_H
#define OUTPUT_H

/**
 * This function will handle all physical interactions of the laser cutter to cut a line.
 *
 * @param x1 The x component of the starting coordinate of the line to be cut.
 * @param y1 The y component of the starting coordinate of the line to be cut.
 * @param x2 The x component of the ending coordinate of the line to be cut.
 * @param y2 The y component of the ending coordinate of the line to be cut.
 * @return Zero.
 */
uint32_t cut_line(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2);

/**
 *
 */
uint32_t cut_curve(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t x3, uint32_t y3, uint32_t x4, uint32_t y4);

#endif

