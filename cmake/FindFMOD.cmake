# - Find fmod
# Find the fmod includes and library
#
#  FMOD_INCLUDE_DIR - Where to find fmod includes
#  FMOD_LIBRARIES   - List of libraries when using fmod
#  FMOD_FOUND       - True if fmod was found

IF(FMOD_INCLUDE_DIR)
  SET(FMOD_FIND_QUIETLY TRUE)
ENDIF(FMOD_INCLUDE_DIR)

FIND_PATH(FMOD_INCLUDE_DIR "fmod_studio.hpp"
  PATHS
  $ENV{FMOD_HOME}/inc
  $ENV{EXTERNLIBS}/fmod/studio/inc
  ~/Library/Frameworks
  /Library/Frameworks
  /usr/include/
  /usr
  /sw # Fink
  /opt/local # DarwinPorts
  /opt/csw # Blastwave
  /opt
  DOC "fmod - Headers"
)
FIND_PATH(FMOD_LL_INCLUDE_DIR "fmod.h"
  PATHS
  $ENV{FMOD_HOME}/inc
  $ENV{EXTERNLIBS}/FMOD
  ~/Library/Frameworks
  /Library/Frameworks
  /usr/include/
  /usr
  /sw # Fink
  /opt/local # DarwinPorts
  /opt/csw # Blastwave
  /opt
  DOC "fmod - Headers"
)

SET(FMOD_NAMES libfmod.so)
SET(FMOD_DBG_NAMES libfmodL.so)

FIND_LIBRARY(FMOD_LIBRARY NAMES ${FMOD_NAMES}
  PATHS
  $ENV{FMOD_HOME}
  $ENV{EXTERNLIBS}/FMOD/
  ~/Library/Frameworks
  /Library/Frameworks
  /usr/lib/x86_64-linux-gnu
  /usr
  /sw
  /opt/local
  /opt/csw
  /opt
  DOC "fmod_event - Library"
)

FIND_LIBRARY(FMOD_LIBRARY_DEBUG NAMES ${FMOD_DBG_NAMES}
  PATHS
  $ENV{FMOD_HOME}
  $ENV{EXTERNLIBS}/fmod/studio/lib
  /usr/lib/x86_64-linux-gnu
  DOC "fmod - Library (Debug)"
)

INCLUDE(FindPackageHandleStandardArgs)


IF(FMOD_LIBRARY_DEBUG AND FMOD_LIBRARY)
  SET(FMOD_LIBRARIES optimized ${FMOD_LIBRARY} debug ${FMOD_LIBRARY_DEBUG})
ENDIF(FMOD_LIBRARY_DEBUG AND FMOD_LIBRARY)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(FMOD DEFAULT_MSG FMOD_LIBRARY FMOD_LIBRARY_DEBUG FMOD_INCLUDE_DIR)

MARK_AS_ADVANCED(FMOD_LIBRARY FMOD_LIBRARY_DEBUG FMOD_INCLUDE_DIR)


IF(FMOD_FOUND)
  SET(FMOD_INCLUDE_DIRS ${FMOD_INCLUDE_DIR} ${FMOD_LL_INCLUDE_DIR})
ENDIF(FMOD_FOUND)
