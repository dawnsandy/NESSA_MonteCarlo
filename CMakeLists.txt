cmake_minimum_required(VERSION 3.16...3.27)
project(NESSA_Geant4)

# Find Geant4
option(WITH_GEANT4_UIVIS "Build with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

include(${Geant4_USE_FILE})

# Source and headers
include_directories(${PROJECT_SOURCE_DIR}/include)
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

# Build
add_executable(nessa_sim main.cc ${sources} ${headers})
target_link_libraries(nessa_sim ${Geant4_LIBRARIES})

# Copy runtime files
set(NESSA_SCRIPTS
  macros/run.mac
  macros/vis.mac
  macros/init_vis.mac
  macros/detectors.mac
  macros/scorers.mac
  macros/plot_results.C
  data/adelphi_source.dat
)

foreach(_script ${NESSA_SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
  )
endforeach()

install(TARGETS nessa_sim DESTINATION bin)
