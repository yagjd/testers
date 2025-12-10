/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marhuber <falcino@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 21:28:43 by marhuber          #+#    #+#             */
/*   Updated: 2025/12/06 20:46:27 by marhuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H
# include "linalg.h"

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}			t_color;

typedef struct s_param
{
	int		cols;		// nbr of columns in input file, also maximal x range
	int		rows;		// nbr of rows in input file, also y range
	float	z_min;		// height of the lowest point in the input
	float	z_max;		// height of the highest point in the input
	float	z_diff;
	int		colorseed;
	int		yaw;
	int		roll;
	int		oblique_mode;
	int		yaw_obl;
	int		roll_obl;
	int		depth;
	int		skew;
	float	u_min;		// left bound in the first plane
	float	u_max;		// right
	float	v_min;		// low
	float	v_max;		// up	
	float	factor;		// scale to multiply centered coordinates with
	t_2dv	fr_center;	// center between left/right, up/down
	t_color	lcolor;		// color for the lowest points
	t_color	hcolor;		// color for the highest points
	t_2dv	*plane;		// points to the array of points in the plane
	t_3dv	*map;		// pointer to the cols-by-rows map read from the input
	void	*mlx;		// results from mlx init
	void	*win;		// results from mlx window creation
	char	*title;
}			t_param;

typedef struct s_image
{
	int		bpp; // bits per pixel
	int		line_len;
	void	*img;		// results from mlx new image
	char	*addr;
}			t_image;

typedef struct s_pixel
{
	int	j;		// x coordinate on the pixel imag
	int	k;		// y
	int	c;		// color according to mlx
}		t_pixel;

typedef struct s_points_pair
{
	int		id_a;
	int		id_b;
	int		rot;		// rotation applied for alignement, in quarters of turns
	float	sl;			// slope (after alignement)
	float	ic;			// intercept
	float	h_start;	// heigt of the first point (for color purposes)
	float	h_end;		// heigt of the second point (for color purposes)
	float	h_diff;
	int		j_start;	// first pixel column
	int		j_end;		// last pixel column
	float	j_diff;
	int		nbr_p;		// number of pixels needed to represent the segment
	t_2dv	a;			// first point (gets aligned)
	t_2dv	b;			// second point 
	t_pixel	*pixels;	// pointer to the series of pixel that build the segment
}			t_ppair;

typedef struct s_position
{
	int		x;
	int		y;
	t_3dv	*v3;
}			t_pos;

// width of the window/images in pixel
# ifndef WWIDTH
#  define WWIDTH 1600
# endif
// height of the window/images in pixel
# ifndef WHEIGHT
#  define WHEIGHT 1200
# endif
// segment width in pixel
# ifndef SEGW
#  define SEGW 3
# endif
// padding around the content within the first image in pixel
# ifndef PAD
#  define PAD 5
# endif
// linear granularity by which to divide any examined pixel
# ifndef DV
#  define DV 4
# endif
// translation step in pixel
# ifndef STEP
#  define STEP 140
# endif
// pi
# ifndef M_PI
#  define M_PI 3.141593
# endif
// denominator of the pi fraction used as step in orthogonal rotations
# ifndef DE
#  define DE 20
# endif
# ifndef PIFR
#  define PIFR 0.15707965
# endif

#endif // #ifndef MAIN_H
