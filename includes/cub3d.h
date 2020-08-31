/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 14:12:20 by awerebea          #+#    #+#             */
/*   Updated: 2020/08/31 10:53:57 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H

# define CUB3D_H

# define MIN_X_WIN_SIZE 100
# define MIN_Y_WIN_SIZE 100

# define SP_SCALE_X 0.8
# define SP_SCALE_Y 0.8
# define SP_VERT_OFFSET 380

# define FOV_ANGLE 66

# include "cub3d_common_structs.h"

# ifdef BONUS

#  include "cub3d_bonus_part.h"
#  define MOVE_SPEED 4
#  define ROTATE_SPEED 120
#  define MOUSE_SENSITIVITY 1.2

#  define MINIMAP_MAX_WDTH_FACTOR 0.35
#  define MINIMAP_MAX_HGHT_FACTOR 0.35
#  define MINIMAP_SQUARE_SIDE 15
#  define VRAD 1

# else

#  include "cub3d_mandatory_part.h"
#  define MOVE_SPEED 0.1
#  define ROTATE_SPEED 3

# endif

# include "cub3d_common_functions.h"

#endif
