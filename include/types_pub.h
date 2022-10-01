#pragma once 

// IMPLEMENTATION DETAIL. DO NOT IMPORT DIRECTLY.
// This header describes the various libgs/psxgs datatypes.

#include <psxgte.h>

// Retains model position between animation frames (?).
typedef struct {
    VECTOR scale;
    SVECTOR rotate;
    VECTOR trans;
} GsCOORD2PARAM;

// A coordinate system (for example for a 3D object or the WORLD)
typedef struct GsCOORDINATE2 {
    // Marker for invalidating cached calculations in case coord is changed
    unsigned long flg;
    // Actual coordinates (?)
    MATRIX coord;
    // Result of multiplying this with WORLD
    MATRIX workm;
    // Rotation, scale, transform params (Used only for TOD animation)
    GsCOORD2PARAM *param;
    // Pointer to the superior coordinate system (typically to WORLD)
    struct GsCOORDINATE2 *super;
    // Unimplemented by Sony, only here to remain compatible with Sony's definition
    struct GsCOORDINATE2 *sub;
} GsCOORDINATE2;

// A handle for manipulating a 3D model object.
typedef struct {
    // TODO: Use this
    unsigned long attribute;
    //
    GsCOORDINATE2 *coord2;
    unsigned long *tmd;
    unsigned long id;
} GsDOBJ2;

// An object sorting table entry.
typedef struct {
    // The 24 LSB of pointer to next OT entry (which is also a GsOT_TAG)
    unsigned p : 24;
    // Number of 32-bit words in current GPU primitive packet
    unsigned char num : 8;
} GsOT_TAG;

// Header of a primitive ordering table.
typedef struct {
    // This field's name is a bit misleading. It actually refers to the Z-precision
    // of the table (in bits), not the actual number of entries.
    unsigned long length;
    // Pointer to beginning of table in memory
    GsOT_TAG *org;
    // Unused, only here to remain compatible with Sony's definition
    unsigned long offset;
    // Specifies the priority of where to sort this table
    unsigned long point;
    // Pointer to table entry at which drawing starts
    GsOT_TAG *tag;
} GsOT;

// Rectangle/box primitive.
typedef struct {
    // Various flags, see Sony manual for details.
    unsigned long attribute;
    // Top-left of the rectangle, in screen coordinates.
    short x, y;
    // Size of the rectangle, as width and height.
    unsigned short w, h;
    // Color of the rectangle.
    unsigned char r, g, b;
} GsBOXF;

// Supposed to be a GPU primitive packet, but Sony defines it like this
// (which doesn't make sense, as packets are variable size and way larger than a char).
typedef unsigned char PACKET;

// A viewpoint/camera (simple version, doesn't support having a reference point).
typedef struct {
    // The viewpoint's world-to-screen matrix.
    MATRIX view;
    // The coordinate system of the viewpoint.
    GsCOORDINATE2 *super;
} GsVIEW;

// A viewpoint/camera (more complex version).
typedef struct {
    // Viewpoint's coordinates in the super coordinate system.
    long vpx, vpy, vpz;
    // Reference point's coordinates in the super coordinate system.
    long vrx, vry, vrz;
    // The screen's inclination on the Z axis on the line between the viewpoint and reference point (4096~1 degree).
    long rz;
    // The coordinate system to which all the structure's coordinates are relative to.
    GsCOORDINATE2 *super;
} GsRVIEW;