//========= Copyright Valve Corporation, All rights reserved. ============//
#if !defined(POSIX)
#ifndef Min
    #define Min(a,b)  (((a) < (b)) ? (a) : (b))
#endif
#ifndef Max
    #define Max(a,b)  (((a) > (b)) ? (a) : (b))
#endif
#endif
