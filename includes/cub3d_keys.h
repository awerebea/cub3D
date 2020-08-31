/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_keys.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/20 20:07:40 by awerebea          #+#    #+#             */
/*   Updated: 2020/08/31 19:23:09 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_KEYS_H

# define CUB3D_KEYS_H

# ifdef LINUX

#  define XK_MISCELLANY
#  define XK_LATIN1
#  include <X11/keysymdef.h>

#  define KEY_ESC XK_Escape
#  define KEY_W XK_w
#  define KEY_A XK_a
#  define KEY_S XK_s
#  define KEY_D XK_d
#  define KEY_M XK_m
#  define KEY_LEFT XK_Left
#  define KEY_RIGHT XK_Right
#  define KEY_KP_MINUS XK_KP_Subtract
#  define KEY_KP_PLUS XK_KP_Add
#  define KEY_SHIFT_L XK_Shift_Left
#  define KEY_SPACE XK_Space

# else

#  define KEY_ESC 53
#  define KEY_W 13
#  define KEY_A 0
#  define KEY_S 1
#  define KEY_D 2
#  define KEY_M 46
#  define KEY_LEFT 123
#  define KEY_RIGHT 124
#  define KEY_KP_MINUS 78
#  define KEY_KP_PLUS 69
#  define KEY_SHIFT_L 257
#  define KEY_SPACE 49

# endif

#endif
