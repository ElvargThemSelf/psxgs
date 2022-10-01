#pragma once

#include <psxgte.h>
#include <stdio.h>

// A TMD file's master header.
typedef struct {
    unsigned long id;
    unsigned long flags;
    unsigned long nobj;
} GsTMDHeader;

// A TMD object entry. Describes where to find the
// various components of an object.
typedef struct {
    unsigned long id, flags, nobj;

    // Pointer to beginning of vertex data
    unsigned long *vertop;
    // Number of vertices
    unsigned long vern;
    // Pointer to beginning of normal data
    unsigned long *nortop;
    // Number of normals
    unsigned long norn;
    // Pointer to beginning of TMD primitive packet data
    unsigned long *primtop;
    // Number of TMD primitive packets
    unsigned long primn;
    // Object scaler (see Sony doc for details).
    long scale;
} GsTMDObject;

// Header of a TMD primitive packet.
// Not the same as a GPU packet, but a GPU packet is generated from this.
typedef struct {
    // Length of the generated GPU primitive packet in 32 bit machine words
    unsigned char olen;
    // Length of the TMD packet (without header) in 32 bit machine words
    unsigned char ilen;
    /* Flags for color gradation,
       double or single-facedness of poly,
       and lighting
    */
    unsigned char flag;
    // Type of primitive and primitive-specific flags
    unsigned char mode;
} GsTMDPacketHeader;

// Flat (untextured) triangle TMD primitive packet.
typedef struct {
    GsTMDPacketHeader hdr;
    // Red
    unsigned char r0;
    // Green
    unsigned char g0;
    // Blue
    unsigned char b0;
    // Identical to mode in the header
    unsigned char mode_copy;
    // Offset from start of object's normals to 0th normal
    unsigned short norm0;
    // Offset from start of object's vertices to 0th vertex
    unsigned short vert0;
    // Offset from start of object's vertices to 1st vertex
    unsigned short vert1;
    // Offset from start of object's vertices to 2nd vertex
    unsigned short vert2;
} GsTMDPF3;

// Flat (untextured) quad TMD primitive packet.
typedef struct {
    GsTMDPacketHeader hdr;
    // Red
    unsigned char r0;
    // Green
    unsigned char g0;
    // Blue
    unsigned char b0;
    // Identical to mode in the header
    unsigned char mode_copy;
    // Offset from start of object's normals to 0th normal
    unsigned short norm0;
    // Offset from start of object's vertices to 0th vertex
    unsigned short vert0;
    // Offset from start of object's vertices to 1st vertex
    unsigned short vert1;
    // Offset from start of object's vertices to 2nd vertex
    unsigned short vert2;
    // Offset from start of object's vertices to 3rd vertex
    unsigned short vert3;
} GsTMDPF4;

// The various TMD primitive types.
typedef enum {
    // Flat, untextured, solid colored triangle
    GS_TMD_PRIMITIVE_F3,
    // Flat, untextured, solid colored quad
    GS_TMD_PRIMITIVE_F4,
    // Unknown primitive
    GS_TMD_PRIMITIVE_UNKNOWN,
} GsTMD_Prim;

// Return a pointer to the nth object in the given TMD.
GsTMD *GsLookupTMDObj(const unsigned long *tmd, const size_t n);
// Return the nth vertex of the given TMD object.
SVECTOR GsLookupTMDVert(const GsTMDObject *obj, const size_t n);
// Return the nth normal of the given TMD object.
SVECTOR GsLookupTMDNorm(const GsTMDObject *obj, const size_t n);
// Scale the given vector according to the TMD format's scale field.
void GsScaleTMDVert(SVECTOR *vert, const long scale);
// Parse header of a TMD primitive packet.
GsTMDPacketHeader GsParseTMDPacketHeader(const unsigned long hdr_int);
// Parse an untextured triangle TMD primitive.
GsTMDPF3 GsParsePolyF3Prim(const unsigned long *prim_data);
// Parse an untextured quad TMD primitive.
GsTMDPF4 GsParsePolyF4Prim(const unsigned long *prim_data);
// Figure out what kind of primitive we're dealing with.
GsTMD_Prim GsParseTMDPrim(const unsigned long *tmd_prim);