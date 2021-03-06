
#ifndef DELAUNAY_H
#define DELAUNAY_H
#define DEL_CIRCLE

#ifdef __cplusplus
extern "C" {
#endif

typedef double real;

typedef struct
{
    real	x, y, z;
} del_point2d_t;

typedef struct
{

    unsigned int	num_points;   /** input points count */
    del_point2d_t*	points;       /** the input points */
    unsigned int	num_faces;    /** number of returned faces */

    /** the faces are given as a sequence: num verts, verts indices, num verts, verts indices...
     * the first face is the external face */
    unsigned int*	faces;
} delaunay2d_t;

/*
 * build the 2D Delaunay triangulation given a set of points of at least 3 points
 *
 * @points: mno�ina bod� dan� jako sekvence parovanych bou x0, y0, x1, y1, ....
 * @num_points: cislo bodu
 * @preds: the incircle predicate
 * @faces: the triangles given as a sequence: num verts, verts indices, num verts, verts indices.
 *	Note that the first face is the external face
 * @return: the created topology
 */
delaunay2d_t*			delaunay2d_from(del_point2d_t *points, unsigned int num_points);

/*
 * release a delaunay2d object
 */
void				delaunay2d_release(delaunay2d_t* del);


typedef struct
{

    unsigned int	num_points;/** input points count */
    del_point2d_t*	points;/** input points */
    unsigned int	num_triangles;/** number of triangles */
    unsigned int*	tris;/** the triangles indices v0,v1,v2, v0,v1,v2 .... */
} tri_delaunay2d_t;

/**
 * build a tri_delaunay2d_t out of a delaunay2d_t object
 */
tri_delaunay2d_t*		tri_delaunay2d_from(delaunay2d_t* del);

/**
 * release a tri_delaunay2d_t object
 */
void				tri_delaunay2d_release(tri_delaunay2d_t* tdel);

#ifdef __cplusplus
}
#endif

#endif // DELAUNAY_H
