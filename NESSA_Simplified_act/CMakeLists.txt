#============================================================================
# CMakeLists.txt for NESSA Neutron Beamline Geant4 Simulation
# Uppsala University - Division of Applied Nuclear Physics
# NESSA (NEutron Source in UppSAla) D-T Generator Facility
#============================================================================
cmake_minimum_required(VERSION 3.16...3.27)
project(NESSA VERSION 1.0.0 LANGUAGES CXX)

#--- Find Geant4 with required components ----
option(WITH_GEANT4_UIVIS "Build with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

#--- Setup Geant4 include dirs and compile definitions
include(${Geant4_USE_FILE})

#--- Source and header files ---
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

#--- Build executable ---
add_executable(nessa_sim nessa_sim.cc ${sources} ${headers})
target_include_directories(nessa_sim PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(nessa_sim ${Geant4_LIBRARIES})

#--- Copy macro files to build directory ---
set(NESSA_MACROS
  macros/run.mac
  macros/vis.mac
  macros/gps_source.mac
  macros/init_vis.mac
  macros/detectors.mac
  macros/vis_raytracer.mac
  macros/plot_nessa.C
  )

foreach(_macro ${NESSA_MACROS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_macro}
    ${PROJECT_BINARY_DIR}/${_macro}
    COPYONLY
    )
endforeach()

#--- Install target ---
install(TARGETS nessa_sim DESTINATION bin)
