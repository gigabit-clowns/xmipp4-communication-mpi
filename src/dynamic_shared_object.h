
#include <xmipp4/core/platform/dynamic_shared_object.h>

/**
 * @def XMIPP4_COMPUTE_MPI_API
 * @brief Declares that the function is part of the public core API of 
 * this plugin.
 * 
 */
#if defined(XMIPP4_COMPUTE_MPI_EXPORTING)
    #define XMIPP4_COMPUTE_MPI_API XMIPP4_EXPORT
#else
    #define XMIPP4_COMPUTE_MPI_API XMIPP4_IMPORT
#endif