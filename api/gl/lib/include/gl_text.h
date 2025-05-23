/****************************************************************************
**
** Copyright (C) ${COPYRIGHT_YEAR} MikroElektronika d.o.o.
** Contact: https://www.mikroe.com/contact
**
** This file is part of the mikroSDK package
**
** Commercial License Usage
**
** Licensees holding valid commercial NECTO compilers AI licenses may use this
** file in accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The MikroElektronika Company.
** For licensing terms and conditions see
** https://www.mikroe.com/legal/software-license-agreement.
** For further information use the contact form at
** https://www.mikroe.com/contact.
**
**
** GNU Lesser General Public License Usage
**
** Alternatively, this file may be used for
** non-commercial projects under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation: https://www.gnu.org/licenses/lgpl-3.0.html.
**
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
** OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
** OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
**
****************************************************************************/

/**
 * @file gl_text.h
 * @brief API for text drawing. After setting desired font (generated by NECTO Studio) drawing and taking information can be performed.
 */
#ifndef _GL_TEXT_H_
#define _GL_TEXT_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "generic_pointer.h"
#include "gl_types.h"

/** @addtogroup apigroup API
 *  @brief API
 *  @{
 */

/**
 * @addtogroup glgroup Graphic Library
 * @brief Graphic Library
 * @{
 */



/**
 * @brief Draws single character to display driver with top left pixel situated at given @p x and @p y coordinates.
 *
 * @details Character look depends on currently active font, pen, and orientation. Background color can also be specified.
 *
 * @param[in] ch Character to draw.
 * @param[in] x X coordinate. See @ref gl_coord_t definition for detailed explanation.
 * @param[in] y Y coordinate. See @ref gl_coord_t definition for detailed explanation.
 *
 * @pre Before calling this function, be sure to initialize driver using @ref gl_set_driver.
 *
 * @sa @ref gl_set_font @ref gl_set_font_orientation @ref gl_set_pen @ref gl_set_font_background_color @ref gl_set_font_background
 */
void gl_draw_char(uint8_t ch, gl_coord_t x, gl_coord_t y);

/**
 * @brief Draws text to display driver with top left pixel situated at given @p x and @p y coordinates using current font and pen.
 *
 * @details To draw text with background use @ref gl_set_font_background and @ref gl_set_font_background_color.
 * It is possible to choose text orientation by using @ref gl_set_font_orientation.
 *
 * @param[in] text Text to draw.
 * @param[in] x X coordinate. See @ref gl_coord_t definition for detailed explanation.
 * @param[in] y Y coordinate. See @ref gl_coord_t definition for detailed explanation.
 *
 * @pre Before calling this function, be sure to initialize driver using @ref gl_set_driver.
 *
 * @sa @ref gl_set_font, @ref gl_set_font_orientation, @ref gl_set_pen, @ref gl_set_font_background_color, @ref gl_set_font_background.
 */
void gl_draw_text(const uint8_t * __generic_ptr text, gl_coord_t x, gl_coord_t y);


/**
 * @brief Calculates text dimension for current font.
 *
 * @details The size of the @p text depends on the font which has been set by @ref gl_set_font.
 *
 * @param[in] text Text to measure.
 *
 * @return Size of @p text if font is set, otherwise returns size = {0, 0}. See @ref gl_size_t definition for detailed explanation.
 *
 * @pre Before calling this function, be sure to initialize font by calling @ref gl_set_font.
 *
 * @sa @ref gl_draw_text, @ref gl_draw_char, @ref gl_set_font.
 */
gl_size_t gl_get_text_dimensions(const uint8_t * __generic_ptr text);

#ifdef __cplusplus
} // extern "C"
#endif

/** @} */ // glgroup
/** @} */ // apigroup

#endif // _GL_TEXT_H_
// ------------------------------------------------------------------------- END
